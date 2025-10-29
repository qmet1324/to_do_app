#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include "tasklistmodel.h"
#include <QListView>

class TaskListWidget : public QListView {
  Q_OBJECT

public:
  explicit TaskListWidget(const QString &columnName, QWidget *parent = nullptr);

  void addTask(const QString &taskText);

  TaskListModel *taskModel() const;

signals:
  void taskMoved(QString taskName, QString columnOrigin,
                 QString columnTransfer);

private:
  TaskListModel *m_taskModel;
};
#endif // TASKLISTWIDGET_H
