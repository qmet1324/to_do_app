#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include <QDrag>
#include <QDropEvent>
#include <QGroupBox>
#include <QListWidget>
#include <QMimeData>
#include <qevent.h>
#include <qmimedata.h>
#include <qnamespace.h>

class TaskListWidget : public QListWidget {
  Q_OBJECT

public:
  explicit TaskListWidget(QString columnName, QWidget *parent = nullptr);
  ~TaskListWidget();

signals:
  void taskMoved(QString &taskName, QString &columnOrigin,
                 QString &columnTransfer);

protected:
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);
  void startDrag(Qt::DropActions supportedActions);
  void dragEnterEvent(QDragEnterEvent *event);
  Qt::DropAction supportedDropActions();

private:
  QString m_columnName;
};
#endif // TASKLISTWIDGET_H
