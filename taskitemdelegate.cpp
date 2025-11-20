#include "taskitemdelegate.h"
#include "tasklistmodel.h"

#include <QApplication>
#include <QDate>
#include <QPainterPath>
#include <QTextLayout>
#include <qcoreevent.h>
#include <qevent.h>
#include <qfontmetrics.h>
#include <qnamespace.h>
#include <qpoint.h>
#include <qwidget.h>
#include <QMenu>

TaskItemDelegate::TaskItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

QWidget *TaskItemDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
  QWidget *editor = new QWidget(parent);
  editor->setAutoFillBackground(true);
  editor->setObjectName("taskEditor");

  // Layouts Init
  auto *mainLayout = new QVBoxLayout(editor);
  mainLayout->setContentsMargins(4, 4, 4, 4);
  auto *bottomLayout = new QHBoxLayout(editor);
  bottomLayout->setSpacing(8);

  // Objects Init
  auto *taskEdit = new QLineEdit(editor);
  taskEdit->setObjectName("taskEdit");
  taskEdit->setMaxLength(50);
  taskEdit->setPlaceholderText("Edit Task");
  auto *dueDateEdit = new QDateEdit(editor);
  dueDateEdit->setObjectName("dueDateEdit");
  dueDateEdit->setCalendarPopup(true);
  dueDateEdit->setDisplayFormat("yyyy-MM-dd");
  auto *priorityBox = new QComboBox(editor);
  priorityBox->setObjectName("priorityBox");
  priorityBox->addItems({"Low", "Medium", "High"});

  bottomLayout->addWidget(dueDateEdit);
  bottomLayout->addWidget(priorityBox);

  mainLayout->addWidget(taskEdit);
  mainLayout->addLayout(bottomLayout);

  return editor;
}

void TaskItemDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
  auto *taskEdit = editor->findChild<QLineEdit *>("taskEdit");
  auto *dueDateEdit = editor->findChild<QDateEdit *>("dueDateEdit");
  auto *priorityBox = editor->findChild<QComboBox *>("priorityBox");

  QString taskText = index.data(TaskListModel::TextRole).toString();
  QDate dueDate = index.data(TaskListModel::DueDateRole).toDate();
  QString taskPriority = index.data(TaskListModel::PriorityRole).toString();

  taskEdit->setText(taskText);
  if (dueDate.isValid()) {
    dueDateEdit->setDate(dueDate);
  }
  priorityBox->setCurrentText(taskPriority);
}

void TaskItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {
  auto *taskEdit = editor->findChild<QLineEdit *>("taskEdit");
  auto *dueDateEdit = editor->findChild<QDateEdit *>("dueDateEdit");
  auto *priorityBox = editor->findChild<QComboBox *>("priorityBox");

  QString taskText = taskEdit->text();
  QDate dueDate = dueDateEdit->date();
  QString taskPriority = priorityBox->currentText();

  if (taskText.isEmpty()) {
    model->removeRow(index.row());
  } else {
    model->setData(index, taskText, TaskListModel::TextRole);
    model->setData(index, dueDate, TaskListModel::DueDateRole);
    model->setData(index, taskPriority, TaskListModel::PriorityRole);
  }
}

void TaskItemDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
  editor->setGeometry(option.rect);
}

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

  // Colors Init - Tokyo Night Storm palette
  QColor bgNormal("#2e3440");
  QColor bgHover("#3b4261");
  QColor bgSelected("#7aa2f7");
  QColor textColor("#c0caf5");
  QColor dueDateColor("#7aa2f7");
  QColor borderColor("#414868");

  QColor highPriority("#f7768e");
  QColor mediumPriority("#e0af68");
  QColor lowPriority("#9ece6a");

  QColor bgColor = bgNormal;
  if (option.state & QStyle::State_Selected) {
    bgColor = bgColor.darker(110);
  } else if (option.state & QStyle::State_MouseOver) {
    bgColor = bgHover;
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

  // Calculate badge width to reserve space
  int badgeWidth = 60;
  int badgeMargin = 8;
  int rightPadding = 10;

  // Create text rect that stops before the priority badge
  QRectF textRect =
      rect.adjusted(10, 8, -(badgeWidth + badgeMargin + rightPadding), -25);

  // Draw the elided text to handle overflow
  QFontMetrics fm(titleFont);
  QString elidedText =
      fm.elidedText(taskText, Qt::ElideRight, textRect.width());
  painter->drawText(textRect, Qt::AlignLeft, elidedText);

  // Render due date
  painter->setFont(option.font);
  painter->setPen(dueDateColor);
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

  painter->setPen(Qt::black);
  painter->setFont(option.font);
  painter->drawText(badgeRect, Qt::AlignCenter, taskPriority);

  painter->restore();
}

QSize TaskItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
  return QSize(200, 70);
}
