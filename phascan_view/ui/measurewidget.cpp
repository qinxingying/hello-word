#include "measurewidget.h"
#include "ui_measurewidget.h"
#include "DopplerConfigure.h"
#include "CalcMeasurement.h"
#include <QStandardItemModel>

ItemDelegate::ItemDelegate( int width, QObject *parent) :
    QStyledItemDelegate(parent), m_sizeWidth(width)
{

}

ItemDelegate::~ItemDelegate()
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid()){
        painter->save();
        QVariant variant = index.data(Qt::UserRole);
        ItemData data = variant.value<ItemData>();

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        //rect.setWidth( option.rect.width()-1);
        rect.setWidth( m_sizeWidth);
        rect.setHeight(option.rect.height()-1);

        const qreal radius = 7;
        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));

        painter->setPen(QPen(Qt::gray));
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);

        QRect typeRect  = QRect(rect.left() +10, rect.top()+10, rect.width()-30, 20);
        QRect valueRect = QRect(rect.left() +10, rect.bottom()-25, rect.width()-10, 20);

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(typeRect,Qt::AlignLeft,data.type);

        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Times", 10));
        painter->drawText(valueRect,Qt::AlignRight,data.value);

        painter->restore();
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize( m_sizeWidth, 60);
}

MeasureWidget::MeasureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureWidget), m_curGroupId(-1)
{
    ui->setupUi(this);
    //int _width = size().width() - 20;
    int _width = ui->measureListView->size().width() - 5;
    m_delegate = new ItemDelegate( _width, this);
    m_model = new QStandardItemModel();
    ui->measureListView->setItemDelegate(m_delegate);
    ui->measureListView->setModel(m_model);
}

MeasureWidget::~MeasureWidget()
{
    delete ui;
}

void MeasureWidget::loadViewList(int groupId)
{
    if(groupId == m_curGroupId) return;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    m_curGroupId = groupId;
    m_model->clear();
    int* _pMeasure;
    if(_pConfig->group[groupId].measureGateStatus){
        _pMeasure = _pConfig->group[groupId].measuregateType;
    }else{
        _pMeasure = _pConfig->group[groupId].aeMeasureType;
    }
    for(int i = 0; i < setup_MAX_MEASURE_QTY; i++){
        if(_pMeasure[i]){
            QStandardItem *Item = new QStandardItem;
            ItemData itemData;
            itemData.index = _pMeasure[i];
            itemData.type  = CalcMeasurement::GetMeasureString( groupId, (FEILD_VALUE_INDEX)_pMeasure[i]);
            Item->setData(QVariant::fromValue(itemData),Qt::UserRole);
            m_model->appendRow(Item);
        }
    }
    updateMeasureValue();
}

void MeasureWidget::updateMeasureValue()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int lawId = _pConfig->group[m_curGroupId].afCursor[setup_CURSOR_LAW];
    int number = m_model->rowCount();
    for(int i = 0; i < number; i++){
        QStandardItem *item = m_model->item(i);
        ItemData data = item->data(Qt::UserRole).value<ItemData>();
        int index = data.index;
        data.value = CalcMeasurement::GetMeasureValueWithUnit( m_curGroupId, lawId, (FEILD_VALUE_INDEX)index);
        item->setData(QVariant::fromValue(data),Qt::UserRole);
    }
}

void MeasureWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    //int width = size().width() - 20;

    int width = ui->measureListView->size().width() - 5;
    //qDebug()<<"in"<<width;
    m_delegate->setSizeWidth(width);
    //ui->measureListView->repaint();
}
