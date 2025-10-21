#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class AddTaskDialog : public QDialog {
  Q_OBJECT

public:
  explicit AddTaskDialog(QWidget *parent = nullptr);
  ~AddTaskDialog();

  QString taskName() const;

private:
  QLineEdit *m_taskInput;
  QLabel *m_dialogTitle;
  QPushButton *m_closeButton;
  QPushButton *m_saveButton;
};
#endif // ADDTASKDIALOG_H
