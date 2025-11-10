#include "mainwindow.h"
#include "addtaskdialog.h"
#include "tasklistmodel.h"
#include "tasklistwidget.h"

#include <QDialog>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qpushbutton.h>

void MainWindow::openAddTaskDialog() {
  AddTaskDialog taskDialog(this);
  if (taskDialog.exec() == QDialog::Accepted) {
    QString newTask = taskDialog.taskName();
    QDate taskDueDate = taskDialog.taskDueDate();
    QString taskPriority = taskDialog.taskPriority();
    toDoList->addTask(newTask, taskDueDate, taskPriority);
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Confirm Close",
                                "Are you sure you want to quit?",
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    event->accept();
  } else {
    event->ignore();
  }
}

void MainWindow::handleTaskMoved(QString taskText, QString columnOrigin,
                                 QString columnTransfer) {
  qDebug() << "Drop event triggered from: " << columnOrigin << "\n\tto "
           << columnTransfer << "\n\ttext: " << taskText;
}

void MainWindow::loadTasksFromFile() {
  QFile file("build/tasks.json");
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray taskArray = doc.object()["tasks"].toArray();

    for (auto taskIndex : taskArray) {
      QJsonObject taskObject = taskIndex.toObject();
      QString taskText = taskObject["text"].toString();
      QString taskColumn = taskObject["column"].toString();
      QDate taskDueDate = QDate::fromString(taskObject["dueDate"].toString(), Qt::ISODate);
      QString taskPriority = taskObject["priorityLevel"].toString();

      if (columnsMap.contains(taskColumn)) {
        columnsMap[taskColumn]->addTask(taskText, taskDueDate, taskPriority);
      }
    }
  }
}

void MainWindow::saveTasksToFile() {
  QJsonArray taskArray;
  for (auto mapI = columnsMap.begin(); mapI != columnsMap.end(); ++mapI) {
    QString columnName = mapI.key();
    TaskListWidget *listWidget = mapI.value();
    TaskListModel *listModel = listWidget->taskModel();

    for (int row = 0; row < listModel->rowCount(); ++row) {
      QModelIndex index = listModel->index(row, 0);
      QString taskText = listModel->data(index, TaskListModel::TextRole).toString();
      QDate taskDueDate = listModel->data(index, TaskListModel::DueDateRole).toDate();
      QString taskPriority = listModel->data(index, TaskListModel::PriorityRole).toString();

      QJsonObject taskObject;
      taskObject["text"] = taskText;
      taskObject["column"] = columnName;
      taskObject["dueDate"] = taskDueDate.toString(Qt::ISODate);
      taskObject["priorityLevel"] = taskPriority;
      taskArray.append(taskObject);
    }
  }

  QJsonObject root;
  root["tasks"] = taskArray;

  QJsonDocument doc(root);
  QFile file("build/tasks.json");
  if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toJson());
    file.close();
  }
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  toDoColumn = new QGroupBox("To-Do");
  QString toDoColumnName = toDoColumn->title();
  toDoList = new TaskListWidget(toDoColumnName);

  inProgressColumn = new QGroupBox("In Progress");
  QString inProgressColumnName = inProgressColumn->title();
  inProgressList = new TaskListWidget(inProgressColumnName);

  doneColumn = new QGroupBox("Done");
  QString doneColumnName = doneColumn->title();
  doneList = new TaskListWidget(doneColumnName);

  addTaskButton = new QPushButton("+");

  columnsMap = {{toDoColumn->title(), toDoList},
                {inProgressColumn->title(), inProgressList},
                {doneColumn->title(), doneList}};

  // Create To-Do column
  auto toDoColumnLayout = new QVBoxLayout;
  toDoColumnLayout->addWidget(addTaskButton);
  toDoColumnLayout->addWidget(toDoList);
  toDoColumn->setLayout(toDoColumnLayout);
  toDoColumn->setAlignment(Qt::AlignCenter);

  // Create In Progress Column
  auto inProgressColumnLayout = new QVBoxLayout;
  inProgressColumnLayout->addWidget(inProgressList);
  inProgressColumn->setLayout(inProgressColumnLayout);
  inProgressColumn->setAlignment(Qt::AlignCenter);

  // Create Done Column
  auto doneColumnLayout = new QVBoxLayout;
  doneColumnLayout->addWidget(doneList);
  doneColumn->setLayout(doneColumnLayout);
  doneColumn->setAlignment(Qt::AlignCenter);

  // Set Horizontal Layout for all columns
  auto mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(toDoColumn);
  mainLayout->addWidget(inProgressColumn);
  mainLayout->addWidget(doneColumn);

  // Open a Dialog upon pressing the '+' button
  connect(addTaskButton, &QPushButton::clicked, this,
          &MainWindow::openAddTaskDialog);

  // Columns are emitting informative signals to the MainWindow
  connect(toDoList, &TaskListWidget::taskMoved, this,
          &MainWindow::handleTaskMoved);
  connect(inProgressList, &TaskListWidget::taskMoved, this,
          &MainWindow::handleTaskMoved);
  connect(doneList, &TaskListWidget::taskMoved, this,
          &MainWindow::handleTaskMoved);

  QFile file("build/tasks.json");
  if (file.exists()) {
    loadTasksFromFile();
  }
}

MainWindow::~MainWindow() { saveTasksToFile(); }
