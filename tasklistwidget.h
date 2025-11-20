#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include "tasklistmodel.h"
#include <QListView>

class TaskListWidget : public QListView {
  Q_OBJECT

public:
  explicit TaskListWidget(const QString &columnName, QWidget *parent = nullptr);

  void addTask(const QString &taskText, const QDate &dueDate, const QString &priority);
  void showContextMenu(const QPoint &pos);

  TaskListModel *taskModel() const;

signals:
  void taskMoved(QString taskName, QString columnOrigin,
                 QString columnTransfer);

private:
  TaskListModel *m_taskModel;
};
#endif // TASKLISTWIDGET_H
