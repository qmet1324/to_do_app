#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QComboBox>

class AddTaskDialog : public QDialog {
  Q_OBJECT

public:
  explicit AddTaskDialog(QWidget *parent = nullptr);
  ~AddTaskDialog();

  QString taskName() const;
  QDate taskDueDate() const;
  QString taskPriority() const;

private:
  QLineEdit *m_taskInput;
  QLabel *m_dialogTitle;
  QPushButton *m_closeButton;
  QPushButton *m_saveButton;
  QLabel *m_dueDateDialogTitle;
  QDateTimeEdit *m_dueDateInput;
  QComboBox *m_priorityBox;
  QLabel *m_priorityTitle;
};
#endif // ADDTASKDIALOG_H
