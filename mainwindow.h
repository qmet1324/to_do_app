#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addtaskdialog.h"

#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void openAddTaskDialog();

private:
  AddTaskDialog *taskDialog;
};
#endif // MAINWINDOW_H
