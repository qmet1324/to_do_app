#include "tasklistwidget.h"
#include "taskitemdelegate.h"
#include "tasklistmodel.h"

#include <QMessageBox>
#include <QPushButton>

TaskListWidget::TaskListWidget(const QString &columnName, QWidget *parent)
    : QListView(parent) {
  // Object Model Init
  m_taskModel = new TaskListModel(columnName, this);
  setModel(m_taskModel);

  // Enable Drag/Drop Functionality
  setSelectionMode(QAbstractItemView::SingleSelection);
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::DragDrop);
  setDefaultDropAction(Qt::MoveAction);

  // Init Custom Delegate for the TaskListWidget Items
  setItemDelegate(new TaskItemDelegate(this));
  setUniformItemSizes(false);
  setMouseTracking(true);

  setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

  connect(m_taskModel, &TaskListModel::taskMoved, this,
          &TaskListWidget::taskMoved);
}

void TaskListWidget::addTask(const QString &taskText, const QDate &dueDate,
                             const QString &priority) {
  taskModel()->addTask(taskText, dueDate, priority);
}

TaskListModel *TaskListWidget::taskModel() const { return m_taskModel; }
