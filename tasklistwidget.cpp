#include "tasklistwidget.h"
#include <qobject.h>
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

void TaskListWidget::dropEvent(QDropEvent *event) {
  QListWidget::dropEvent(event);

  const QMimeData *mime = event->mimeData();
  if (!mime->hasText()) {
    qDebug() << "No text data in mime";
    return;
  }

  QString taskText = mime->text();
  QString originColumn =
      QString::fromUtf8(mime->data("application/x-column-name"));
  QString targetColumn = m_columnName;

  qDebug() << "Drop event triggered from: " << originColumn << "\n\t to "
           << targetColumn << "\n\ttext: " << taskText;

  emit taskMoved(taskText, originColumn, targetColumn);
}

QMimeData *
TaskListWidget::mimeData(const QList<QListWidgetItem *> &items) const {
  QMimeData *mimeData = new QMimeData;
  if (!items.isEmpty() && items.first()) {
    QString text = items.first()->text();
    mimeData->setText(text);
    mimeData->setData("application/x-column-name", m_columnName.toUtf8());
  }
  return mimeData;
}

TaskListWidget::~TaskListWidget() {}
