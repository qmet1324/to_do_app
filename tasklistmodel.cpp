#include "tasklistmodel.h"
#include <qlogging.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <strings.h>

TaskListModel::TaskListModel(const QString &columnName, QObject *parent)
    : QStandardItemModel(parent), m_columnName(columnName) {}

QStringList TaskListModel::mimeTypes() const {
  return {"application/x-task-item"};
}

QMimeData *TaskListModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData();

  if (!indexes.isEmpty()) {
    QString text = data(indexes.first(), Qt::DisplayRole).toString();
    if (!text.isEmpty()) {
      mimeData->setText(text);
      mimeData->setData("application/x-task-item", text.toUtf8());
      mimeData->setData("application/x-origin-column", m_columnName.toUtf8());
    }
  }
  return mimeData;
}

bool TaskListModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                 int row, int column,
                                 const QModelIndex &parent) {
  Q_UNUSED(column)
  Q_UNUSED(parent)

  if (action == Qt::IgnoreAction) {
    return true;
  }
  if (!data->hasFormat("application/x-task-item")) {
    return false;
  }

  QString taskText = QString::fromUtf8(data->data("application/x-task-item"));
  QString originColumnName =
      QString::fromUtf8(data->data("application/x-origin-column"));
  QString targetColumnName = m_columnName;

  QStandardItem *newItem = new QStandardItem(taskText);
  if (row < 0) {
    row = rowCount();
  }
  insertRow(row, newItem);

  emit taskMoved(taskText, originColumnName, targetColumnName);
  return true;
}

Qt::DropActions TaskListModel::supportedDropActions() const {
  return Qt::MoveAction;
}
