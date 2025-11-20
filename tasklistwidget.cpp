#include "tasklistwidget.h"
#include "taskitemdelegate.h"
#include "tasklistmodel.h"

#include <QGuiApplication>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <qmenu.h>

TaskListWidget::TaskListWidget(const QString &columnName, QWidget *parent)
    : QListView(parent) {
  // Object Model Init
  m_taskModel = new TaskListModel(columnName, this);
  setModel(m_taskModel);
  setContextMenuPolicy(Qt::CustomContextMenu);

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

  setEditTriggers(QAbstractItemView::DoubleClicked |
                  QAbstractItemView::EditKeyPressed);

  connect(m_taskModel, &TaskListModel::taskMoved, this,
          &TaskListWidget::taskMoved);
  connect(this, &QListView::customContextMenuRequested, this,
          &TaskListWidget::showContextMenu);
}

void TaskListWidget::showContextMenu(const QPoint &pos) {
  QModelIndex index = indexAt(pos);
  if (!index.isValid()) return;

  QMenu contextMenu(this);

  QAction *deleteAction = contextMenu.addAction("Delete Task");
  QAction *selectedAction = contextMenu.exec(mapToGlobal(pos));

  if (selectedAction == deleteAction) {
    taskModel()->removeRow(index.row());
  }
}

void TaskListWidget::addTask(const QString &taskText, const QDate &dueDate,
                             const QString &priority) {
  taskModel()->addTask(taskText, dueDate, priority);
}

TaskListModel *TaskListWidget::taskModel() const { return m_taskModel; }
