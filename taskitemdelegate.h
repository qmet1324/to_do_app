#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class TaskItemDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit TaskItemDelegate(QObject *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;

  QWidget *createEditor(QWidget *editor, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;

  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
};
