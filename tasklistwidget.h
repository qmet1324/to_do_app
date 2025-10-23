#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include <QDrag>
#include <QDropEvent>
#include <QGroupBox>
#include <QListWidget>
#include <QMimeData>
#include <qmimedata.h>

class TaskListWidget : public QListWidget {
  Q_OBJECT

public:
  explicit TaskListWidget(QString columnName, QWidget *parent = nullptr);
  ~TaskListWidget();

signals:
  void taskMoved(QString taskName, QString columnOrigin,
                 QString columnTransfer);

protected:
  void dropEvent(QDropEvent *event) override;
  QMimeData *mimeData(const QList<QListWidgetItem *> &items) const override;

private:
  QString m_columnName;
};
#endif // TASKLISTWIDGET_H
