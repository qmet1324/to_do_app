#include "mainwindow.h"
#include "addtaskdialog.h"
#include "tasklistwidget.h"

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <qmimedata.h>

void MainWindow::openAddTaskDialog() {
  AddTaskDialog taskDialog(this);
  if (taskDialog.exec() == QDialog::Accepted) {
    QString newTask = taskDialog.taskName();
    toDoList->addItem(newTask);
  }
}

void MainWindow::handleTaskMoved(QString taskText, QString columnOrigin,
                                 QString columnTransfer) {
  // std::cout << "The task has been moved" << std::endl;
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  toDoColumn = new QGroupBox("To-Do");
  toDoList = new TaskListWidget("To-Do");

  inProgressColumn = new QGroupBox("In Progress");
  inProgressList = new TaskListWidget("In Progress");

  doneColumn = new QGroupBox("Done");
  doneList = new TaskListWidget("Done");

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
  connect(toDoList, &TaskListWidget::taskMoved, this, &MainWindow::handleTaskMoved);
  connect(inProgressList, &TaskListWidget::taskMoved, this, &MainWindow::handleTaskMoved);
  connect(doneList, &TaskListWidget::taskMoved, this, &MainWindow::handleTaskMoved);
}

MainWindow::~MainWindow() {}
