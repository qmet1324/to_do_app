#include "tasklistwidget.h"
#include "tasklistmodel.h"
#include <QMessageBox>
#include <QPushButton>
#include <qmessagebox.h>
#include <qpushbutton.h>

TaskListWidget::TaskListWidget(const QString &columnName, QWidget *parent)
    : QListView(parent) {
  m_taskModel = new TaskListModel(columnName, this);
  setModel(m_taskModel);

  setSelectionMode(QAbstractItemView::SingleSelection);
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::DragDrop);

  setEditTriggers(QAbstractItemView::NoEditTriggers);

  connect(m_taskModel, &TaskListModel::taskMoved, this,
          &TaskListWidget::taskMoved);

  connect(this, &QListView::doubleClicked, this,
          [this](const QModelIndex &index) {
            if (!index.isValid())
              return;

            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Task Options");
            msgBox.setText("What would you like to do with this task?");

            QPushButton *editText =
                msgBox.addButton("Edit", QMessageBox::AcceptRole);
            QPushButton *deleteButton =
                msgBox.addButton("Delete", QMessageBox::DestructiveRole);
            QPushButton *cancelButton =
                msgBox.addButton("Cancel", QMessageBox::RejectRole);
            msgBox.exec();

            if (msgBox.clickedButton() == editText) {
              edit(index);
            } else if (msgBox.clickedButton() == deleteButton) {
              m_taskModel->removeRow(index.row());
            }
          });
}

void TaskListWidget::addTask(const QString &taskText) {
  if (!taskText.isEmpty()) {
    auto *item = new QStandardItem(taskText);
    m_taskModel->appendRow(item);
  }
}

TaskListModel *TaskListWidget::taskModel() const { return m_taskModel; }
