#include "addtaskdialog.h"
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qwindowdefs.h>

AddTaskDialog::AddTaskDialog(QWidget *parent) : QDialog(parent) {
  auto mainDialogLayout = new QVBoxLayout(this);
  auto inputDialogLayout = new QHBoxLayout;
  auto buttonsDialogLayout = new QHBoxLayout;

  m_dialogTitle = new QLabel("Add Task:");
  m_taskInput = new QLineEdit;
  m_saveButton = new QPushButton("Save");
  m_clearButton = new QPushButton("Clear");

  inputDialogLayout->addWidget(m_dialogTitle);
  inputDialogLayout->addWidget(m_taskInput);

  buttonsDialogLayout->addWidget(m_clearButton);
  buttonsDialogLayout->addWidget(m_saveButton);

  mainDialogLayout->addLayout(inputDialogLayout);
  mainDialogLayout->addLayout(buttonsDialogLayout);
}

AddTaskDialog::~AddTaskDialog() {}
