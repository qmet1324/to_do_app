#include "addtaskdialog.h"

#include <QBoxLayout>

QString AddTaskDialog::taskName() const { return m_taskInput->text(); }

AddTaskDialog::AddTaskDialog(QWidget *parent) : QDialog(parent) {
  auto mainDialogLayout = new QVBoxLayout(this);
  auto inputDialogLayout = new QHBoxLayout;
  auto buttonsDialogLayout = new QHBoxLayout;

  m_dialogTitle = new QLabel("Add Task:");
  m_taskInput = new QLineEdit;
  m_saveButton = new QPushButton("Save");
  m_closeButton = new QPushButton("Close");

  inputDialogLayout->addWidget(m_dialogTitle);
  inputDialogLayout->addWidget(m_taskInput);

  buttonsDialogLayout->addWidget(m_closeButton);
  buttonsDialogLayout->addWidget(m_saveButton);

  mainDialogLayout->addLayout(inputDialogLayout);
  mainDialogLayout->addLayout(buttonsDialogLayout);

  connect(m_closeButton, &QPushButton::clicked, this,
          &QDialog::reject);
  connect(m_saveButton, &QPushButton::clicked, this,
          &QDialog::accept);
}

AddTaskDialog::~AddTaskDialog() {}
