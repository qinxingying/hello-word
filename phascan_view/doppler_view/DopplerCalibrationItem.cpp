#include "DopplerCalibrationItem.h"
#include <process/ParameterProcess.h>

DopplerCalibrationItem::DopplerCalibrationItem(const QColor& cColor_): DopplerLineItem(cColor_)
{

}

void DopplerCalibrationItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    ParameterProcess* _pProcess = ParameterProcess::Instance();
    //******** to change the background color of when mouse is rect
    QColor fillColor = (item->state & QStyle::State_Selected) ? m_cColor.dark(50) : m_cColor;
    if (item->state & QStyle::State_MouseOver)
    fillColor = fillColor.light(50);
    //******** get the enlarged rate, and by which to determine whether draw the details
    //******** the real display size diliver real size (in pixels)
    //const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    switch (m_eLineType)
    {
    case LINE_VERTICAL:
        {
            QGraphicsScene* _pScene = scene () ;
            if(_pScene)
            m_nHeight = _pScene->height() ;
        }
        m_nWidth  = 0 ;
        break;
    case LINE_HORIZENTAL:
        {
            QGraphicsScene* _pScene = scene () ;
            if(_pScene)
            m_nWidth = _pScene->width() ;
        }
        m_nHeight = 0 ;
        break;
    default:
        break;
    };
    painter->save();


    QPen _NewPen ;
    QVector<qreal> dashes;
    _NewPen.setColor(fillColor);
    _NewPen.setWidth(2);

    dashes << 1 << 4 << 1 << 4 ;
    _NewPen.setDashPattern(dashes);
    painter->setPen(_NewPen);
    painter->drawLine(0, 0 , m_nWidth , m_nHeight );

    QString _str;
    double buff = _pProcess->transTofdHalfSoundPathToDepth(m_pDataView->GetGroupId(),  m_Geometry.left());
    DrawLabel(painter, _str.sprintf("%.1f", buff));

    painter->restore();
}

void DopplerCalibrationItem::DrawLabel(QPainter *painter, QString str)
{
    QPen _pen = painter->pen();
    _pen.setColor(m_cColor) ;
    painter->setPen(_pen);

    QPointF _ptScene = GetItemScenePos();
    int _iWidth = m_cSize.width();
    int _iHeight = m_cSize.height();
    int _x, _y;
    int _W = 16;
    int _H = 10;

    switch (m_eLineType)
    {
    case LINE_VERTICAL:
        if(_ptScene.x() > _iWidth/2) {
            _x = 0 - _W - 2;  _y = _iHeight - _H - 1;
        } else {
            _x = 2; _y = _iHeight - _H - 1;
        }
        break;
    case LINE_HORIZENTAL:
        if(_ptScene.y() > _iHeight/2) {
            _x = _iWidth - _W - 1;	_y = -12;
        } else {
            _x = _iWidth - _W - 1; _y = 2;
        }
        break;
    default:
        return;
    };
    _x += 1;
    _y += 1 + 5;
    painter->drawText( _x, _y, str );
}

