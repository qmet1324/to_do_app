#include "tasklistwidget.h"
#include <qdrag.h>
#include <qevent.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qlogging.h>
#include <qmimedata.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qwidget.h>

TaskListWidget::TaskListWidget(QString columnName, QWidget *parent)
    : QListWidget(parent), m_columnName(columnName) {
  // Enable drag and drop behavior
  setSelectionMode(QAbstractItemView::SingleSelection);
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::DragDrop);

  // Move one task from one column to another without copying it
  setDefaultDropAction(Qt::MoveAction);
}

void TaskListWidget::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasFormat("application/x-item") &&
      event->source() != this) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
  } else {
    event->ignore();
  }
}

void TaskListWidget::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasFormat("application/x-item")) {
    event->accept();
    event->setDropAction(Qt::MoveAction);

    QListWidgetItem *item = new QListWidgetItem;
    QString taskName = event->mimeData()->data("application/x-item");
    QString originColumnName =
        event->mimeData()->data("application/x-origin-column");
    QString targetColumnName = m_columnName;
    item->setText(taskName);
    addItem(item);

    emit taskMoved(taskName, originColumnName, targetColumnName);
  } else {
    event->ignore();
  }
}

void TaskListWidget::startDrag(Qt::DropActions supportedActions) {
  QListWidgetItem *item = currentItem();
  if (!item) return;

  QMimeData *mimeData = new QMimeData();
  QByteArray ba;
  ba = item->text().toLatin1().data();
  mimeData->setData("application/x-item", ba);
  mimeData->setData("application/x-origin-column", m_columnName.toUtf8());
  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);

  qDebug() << "Formats available:" << mimeData->formats();

  if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
    delete takeItem(row(item));
  }
}

void TaskListWidget::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasFormat("application/x-item")) {
    event->accept();
  } else {
    event->ignore();
  }
}

TaskListWidget::~TaskListWidget() {}
