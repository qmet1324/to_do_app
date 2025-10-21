#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addtaskdialog.h"

#include <QGroupBox>
#include <QWidget>
#include <qgroupbox.h>
#include <qlistwidget.h>
#include <qpushbutton.h>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void openAddTaskDialog();

private:
  QGroupBox *toDoColumn;
  QGroupBox *inProgressColumn;
  QGroupBox *doneColumn;
  QListWidget *toDoList;
  QListWidget *inProgressList;
  QListWidget *doneList;
  QPushButton *addTaskButton;
};
#endif // MAINWINDOW_H
