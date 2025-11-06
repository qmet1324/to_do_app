#include "addtaskdialog.h"

#include <QBoxLayout>

QString AddTaskDialog::taskName() const { return m_taskInput->text(); }

QDate AddTaskDialog::taskDueDate() const {return m_dueDateInput->date();}

QString AddTaskDialog::taskPriority() const {return m_priorityBox->currentText();}

AddTaskDialog::AddTaskDialog(QWidget *parent) : QDialog(parent) {
  auto mainDialogLayout = new QVBoxLayout(this);
  auto inputDialogLayout = new QHBoxLayout;
  auto buttonsDialogLayout = new QHBoxLayout;
  auto dateInputDialogLayout = new QHBoxLayout;
  auto priorityInputDialogLayout = new QHBoxLayout;

  m_dialogTitle = new QLabel("Task:");
  m_dueDateDialogTitle = new QLabel("Due Date:");
  m_priorityTitle = new QLabel("Priority:");

  m_taskInput = new QLineEdit;

  m_dueDateInput = new QDateTimeEdit(QDate::currentDate());
  m_dueDateInput->setCalendarPopup(true);

  m_priorityBox = new QComboBox;
  QStringList priorityList = {"High", "Medium", "Low"};
  m_priorityBox->addItems(priorityList);

  m_saveButton = new QPushButton("Save");
  m_closeButton = new QPushButton("Close");

  inputDialogLayout->addWidget(m_dialogTitle);
  inputDialogLayout->addWidget(m_taskInput);

  dateInputDialogLayout->addWidget(m_dueDateDialogTitle);
  dateInputDialogLayout->addWidget(m_dueDateInput);

  priorityInputDialogLayout->addWidget(m_priorityTitle);
  priorityInputDialogLayout->addWidget(m_priorityBox);

  buttonsDialogLayout->addWidget(m_saveButton);
  buttonsDialogLayout->addWidget(m_closeButton);

  mainDialogLayout->addLayout(inputDialogLayout);
  mainDialogLayout->addLayout(dateInputDialogLayout);
  mainDialogLayout->addLayout(priorityInputDialogLayout);
  mainDialogLayout->addLayout(buttonsDialogLayout);

  connect(m_closeButton, &QPushButton::clicked, this, &QDialog::reject);
  connect(m_saveButton, &QPushButton::clicked, this, &QDialog::accept);
}

AddTaskDialog::~AddTaskDialog() {}
