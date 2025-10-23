#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tasklistwidget.h"

#include <QGroupBox>
#include <QWidget>
#include <qgroupbox.h>
#include <qlistwidget.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpushbutton.h>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void openAddTaskDialog();
  void handleTaskMoved(QString taskText, QString columnOrigin,
                       QString columnTransfer);

private:
  QGroupBox *toDoColumn;
  QGroupBox *inProgressColumn;
  QGroupBox *doneColumn;
  TaskListWidget *toDoList;
  TaskListWidget *inProgressList;
  TaskListWidget *doneList;
  QPushButton *addTaskButton;
};
#endif // MAINWINDOW_H
