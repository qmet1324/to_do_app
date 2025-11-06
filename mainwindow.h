#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tasklistwidget.h"

#include <QGroupBox>
#include <QPushButton>
#include <QWidget>
#include <qcontainerfwd.h>
#include <qevent.h>
#include <QFile>
#include <qmap.h>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void saveTasksToFile();
  void loadTasksFromFile();

private slots:
  void openAddTaskDialog();
  void handleTaskMoved(QString taskText, QString columnOrigin,
                       QString columnTransfer);

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  QGroupBox *toDoColumn;
  QGroupBox *inProgressColumn;
  QGroupBox *doneColumn;
  TaskListWidget *toDoList;
  TaskListWidget *inProgressList;
  TaskListWidget *doneList;
  QMap<QString, TaskListWidget*> columnsMap;
  QPushButton *addTaskButton;
};
#endif // MAINWINDOW_H
