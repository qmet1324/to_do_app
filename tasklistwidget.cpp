#include "tasklistwidget.h"
#include "tasklistmodel.h"

TaskListWidget::TaskListWidget(const QString &columnName, QWidget *parent)
    : QListView(parent) {
  m_taskModel = new TaskListModel(columnName, this);
  setModel(m_taskModel);

  setSelectionMode(QAbstractItemView::SingleSelection);
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::DragDrop);

  connect(m_taskModel, &TaskListModel::taskMoved, this,
          &TaskListWidget::taskMoved);
}

void TaskListWidget::addTask(const QString &taskText) {
  if (!taskText.isEmpty()) {
    auto *item = new QStandardItem(taskText);
    m_taskModel->appendRow(item);
  }
}

TaskListModel *TaskListWidget::taskModel() const { return m_taskModel; }
