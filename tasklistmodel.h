// tasklistmodel.h
#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QDate>
#include <QDebug>
#include <QMimeData>
#include <QStandardItemModel>
#include <qvariant.h>

class TaskListModel : public QStandardItemModel {
  Q_OBJECT
public:
  enum TaskRoles {
    TextRole = Qt::UserRole + 1,
    DueDateRole,
    PriorityRole,
  };
  QHash<int, QByteArray> roleNames() const override;

  explicit TaskListModel(const QString &columnName, QObject *parent = nullptr);

  QMimeData *mimeData(const QModelIndexList &indexes) const override;
  QStringList mimeTypes() const override;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent) override;
  QVariant data(const QModelIndex &index, int role) const override;

  Qt::DropActions supportedDropActions() const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void addTask(const QString &taskText, const QDate &dueDate,
               const QString &priority);
signals:
  void taskMoved(const QString &task, const QString &from, const QString &to);

private:
  QString m_columnName;
};

#endif // TASKLISTMODEL_H
