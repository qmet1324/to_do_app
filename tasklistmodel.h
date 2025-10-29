// tasklistmodel.h
#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QDebug>
#include <QMimeData>
#include <QStandardItemModel>

class TaskListModel : public QStandardItemModel {
  Q_OBJECT
public:
  explicit TaskListModel(const QString &columnName, QObject *parent = nullptr);

  Qt::DropActions supportedDropActions() const override;
  QStringList mimeTypes() const override;

  QMimeData *mimeData(const QModelIndexList &indexes) const override;

  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent) override;

signals:
  void taskMoved(const QString &task, const QString &from, const QString &to);

private:
  QString m_columnName;
};

#endif // TASKLISTMODEL_H
