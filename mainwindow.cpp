#include "mainwindow.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  auto toDoColumn = new QGroupBox("To-Do");
  auto toDoList = new QListWidget;

  auto inProgressColumn = new QGroupBox("In Progress");
  auto inProgressList = new QListWidget;

  auto doneColumn = new QGroupBox("Done");
  auto doneList = new QListWidget;

  auto addTaskButton = new QPushButton("+");

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
}

MainWindow::~MainWindow() {}
