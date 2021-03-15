#ifndef MEASUREWIDGET_H
#define MEASUREWIDGET_H

#include <QWidget>
#include <QStyledItemDelegate>
namespace Ui {
class MeasureWidget;
}
class QStandardItemModel;

struct ItemData{
    int index;
    QString type;
    QString value;
};

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate( int width, QObject *parent = 0);
    ~ItemDelegate();
    void setSizeWidth(int width){m_sizeWidth = width;}
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    int m_sizeWidth;
};

class MeasureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeasureWidget(QWidget *parent = 0);    
    ~MeasureWidget();
    void loadViewList(int groupId);
    void updateMeasureValue();
    void setFlashFlag(){m_curGroupId = -1;}//打开文件时候调用这个接口，将原来数据设为失效
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MeasureWidget *ui;
    QStandardItemModel *m_model;
    ItemDelegate *m_delegate;
    int m_curGroupId;
};
Q_DECLARE_METATYPE(ItemData)
#endif // MEASUREWIDGET_H
