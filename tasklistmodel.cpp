#include "tasklistmodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qtmetamacros.h>
#include <strings.h>

static constexpr const char *TASK_MIME_TYPE = "application/x-task-item";

QHash<int, QByteArray> TaskListModel::roleNames() const {
  return {
      {TextRole, "text"}, {DueDateRole, "dueDate"}, {PriorityRole, "priority"}};
}

QStringList TaskListModel::mimeTypes() const { return {TASK_MIME_TYPE}; }

QVariant TaskListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  QStandardItem *item = itemFromIndex(index);

  switch (role) {
  case TextRole:
    return item->data(TextRole).isValid() ? item->data(TextRole)
                                          : item->data(Qt::DisplayRole);
  case DueDateRole:
    return item->data(DueDateRole);
  case PriorityRole:
    return item->data(PriorityRole);
  default:
    return QStandardItemModel::data(index, role);
  }
}

TaskListModel::TaskListModel(const QString &columnName, QObject *parent)
    : QStandardItemModel(parent), m_columnName(columnName) {}

QMimeData *TaskListModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *mimeData = new QMimeData;
  if (indexes.isEmpty()) {
    return mimeData;
  }

  const QModelIndex &index = indexes.first();
  if (index.isValid()) {
    QJsonObject taskData;
    taskData["text"] = data(index, TaskRoles::TextRole).toString();
    taskData["dueDate"] = data(index, TaskRoles::DueDateRole).toString();
    taskData["priority"] = data(index, TaskRoles::PriorityRole).toString();
    taskData["originColumn"] = m_columnName;

    QJsonDocument doc(taskData);
    mimeData->setData(TASK_MIME_TYPE, doc.toJson());
  }
  return mimeData;
}

bool TaskListModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                 int row, int column,
                                 const QModelIndex &parent) {
  if (!data->hasFormat(TASK_MIME_TYPE)) {
    return false;
  }

  QByteArray jsonData = data->data(TASK_MIME_TYPE);
  QJsonDocument doc = QJsonDocument::fromJson(jsonData);
  QJsonObject obj = doc.object();

  QString taskText = obj["text"].toString();
  QDate dueDate = QDate::fromString(obj["dueDate"].toString(), Qt::ISODate);
  QString priority = obj["priority"].toString();
  QString originColum = obj["originColumn"].toString();
  QString transferColumn = m_columnName;

  addTask(taskText, dueDate, priority);
  emit taskMoved(taskText, originColum, transferColumn);
  return true;
}

void TaskListModel::addTask(const QString &taskText, const QDate &dueDate,
                            const QString &priority) {
  auto *item = new QStandardItem();
  if (!taskText.isEmpty()) {
    item->setText(taskText);
    item->setData(taskText, TaskListModel::TextRole);
    item->setData(dueDate, TaskListModel::DueDateRole);
    item->setData(priority, TaskListModel::PriorityRole);
    appendRow(item);
  }
}

Qt::DropActions TaskListModel::supportedDropActions() const {
  return Qt::MoveAction;
}

Qt::ItemFlags TaskListModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
  if (index.isValid()) {
    defaultFlags |= Qt::ItemIsDragEnabled;
  }
  defaultFlags |= Qt::ItemIsDropEnabled;
  return defaultFlags;
}
