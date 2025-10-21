#include "mainwindow.h"
#include "addtaskdialog.h"

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

void MainWindow::openAddTaskDialog() {
  AddTaskDialog taskDialog(this);
  if (taskDialog.exec() == QDialog::Accepted) {
    QString newTask = taskDialog.taskName();
    toDoList->addItem(newTask);
  }
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  toDoColumn = new QGroupBox("To-Do");
  toDoList = new QListWidget;

  inProgressColumn = new QGroupBox("In Progress");
  inProgressList = new QListWidget;

  doneColumn = new QGroupBox("Done");
  doneList = new QListWidget;

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

  // Enable drag and drop behavior
  toDoList->setSelectionMode(QAbstractItemView::SingleSelection);
  inProgressList->setSelectionMode(QAbstractItemView::SingleSelection);
  doneList->setSelectionMode(QAbstractItemView::SingleSelection);

  toDoList->setDragEnabled(true);
  inProgressList->setDragEnabled(true);
  doneList->setDragEnabled(true);

  toDoList->setAcceptDrops(true);
  inProgressList->setAcceptDrops(true);
  doneList->setAcceptDrops(true);

  toDoList->setDropIndicatorShown(true);
  inProgressList->setDropIndicatorShown(true);
  doneList->setDropIndicatorShown(true);

  toDoList->setDragDropMode(QAbstractItemView::DragDrop);
  inProgressList->setDragDropMode(QAbstractItemView::DragDrop);
  doneList->setDragDropMode(QAbstractItemView::DragDrop);

  // Move one task from one column to another without copying it
  toDoList->setDefaultDropAction(Qt::MoveAction);
  inProgressList->setDefaultDropAction(Qt::MoveAction);
  doneList->setDefaultDropAction(Qt::MoveAction);
}

MainWindow::~MainWindow() {}
