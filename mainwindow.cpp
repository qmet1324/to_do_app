#include "mainwindow.h"
#include "addtaskdialog.h"
#include "tasklistwidget.h"

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

void MainWindow::openAddTaskDialog() {
  AddTaskDialog taskDialog(this);
  if (taskDialog.exec() == QDialog::Accepted) {
    QString newTask = taskDialog.taskName();
    toDoList->addTask(newTask);
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
}

MainWindow::~MainWindow() {}
