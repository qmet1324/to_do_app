#include "taskitemdelegate.h"
#include "tasklistmodel.h"

#include <QApplication>
#include <QDate>
#include <QPainterPath>
#include <qcolor.h>
#include <qnamespace.h>
#include <qpoint.h>

TaskItemDelegate::TaskItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void TaskItemDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
  painter->save();

  // Data Fetch
  QString taskText = index.data(TaskListModel::TextRole).toString();
  QDate dueDate = index.data(TaskListModel::DueDateRole).toDate();
  QString taskPriority = index.data(TaskListModel::PriorityRole).toString();
  if (taskText.isEmpty() | !dueDate.isValid() | taskPriority.isEmpty()) {
    qDebug() << "ERROR: The data hasn't been fetched.";
    return;
  }

  // Colors Init
  QColor baseColor = option.palette.base().color();
  QColor bgColor = option.state & QStyle::State_Selected ? QColor("#A0C4FF")
                                                         : QColor("#FFFFFF");
  QColor borderColor = QColor("#D0D0D0");
  QColor textColor = QColor("#202020");
  QColor dateColor = QColor("#666666");

  if (option.state & QStyle::State_MouseOver) {
    bgColor = bgColor.lighter(110);
  }

  // Render rounded background
  QRectF rect = option.rect.adjusted(4, 4, -4, -4);
  QPainterPath path;
  path.addRoundedRect(rect, 8, 8);

  painter->setRenderHint(QPainter::Antialiasing);
  painter->fillPath(path, bgColor);
  painter->setPen(borderColor);
  painter->drawPath(path);

  // Render task text
  QFont titleFont = option.font;
  titleFont.setBold(true);
  painter->setFont(titleFont);
  painter->setPen(textColor);
  QRectF textRect = rect.adjusted(10, 8, -10, -25);
  painter->drawText(textRect, Qt::TextWordWrap, taskText);

  // Render due date
  painter->setFont(option.font);
  painter->setPen(dateColor);
  QString dateText = "Due: " + dueDate.toString("MMM dd");
  QRectF dateRect = rect.adjusted(10, rect.height() - 28, -10, -6);
  painter->drawText(dateRect, Qt::AlignLeft, dateText);

  // Render priority badge
  QColor badgeColor;
  if (taskPriority == "High") {
    badgeColor = QColor("#EF476F");
  } else if (taskPriority == "Medium") {
    badgeColor = QColor("#FFD166");
  } else if (taskPriority == "Low") {
    badgeColor = QColor("#06D6A0");
  }

  QRect badgeRect(rect.right() - 60, rect.top() + 8, 50, 20);
  painter->setBrush(badgeColor);
  painter->setPen(Qt::NoPen);
  painter->drawRoundedRect(badgeRect, 10, 10);

  painter->setPen(Qt::white);
  painter->setFont(option.font);
  painter->drawText(badgeRect, Qt::AlignCenter, taskPriority);

  painter->restore();
}

QSize TaskItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
  return QSize(200, 70);
}
