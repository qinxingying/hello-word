#include "dopplercscanlinemark.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include "DopplerConfigure.h"

const int g_nRectSize = 2 ;

DopplerCScanLineMark::DopplerCScanLineMark(const QColor &cColor_, QObject *parent) :
    QObject(parent),
    DopplerLineItem(cColor_)
{

}

DopplerCScanLineMark::~DopplerCScanLineMark()
{

}

void DopplerCScanLineMark::SendSignalIndex(int index)
{
    emit SignalChangeSScanLawMarkIndex(index);
}


void DopplerCScanLineMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* /*widget*/)
{
    QColor fillColor = (option->state & QStyle::State_Selected) ? m_cColor.dark(75) : m_cColor;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(50);
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


    dashes << 1 << 3 << 1 << 3 ;
    _NewPen.setDashPattern(dashes);
    painter->setPen(_NewPen);
    painter->drawLine(0, 0 , m_nWidth , m_nHeight );
    DrawLabel(painter);
    painter->restore();
}

void DopplerCScanLineMark::DrawLabel(QPainter *painter)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QPen _pen = painter->pen();
    _pen.setColor(m_cColor) ;
    painter->setPen(_pen);
    QString _str ;

    QPointF _ptScene = GetItemScenePos();

    int _x0 = m_rcWnd.left();
    int _y0 = m_rcWnd.top();
    int _iWidth = m_rcWnd.width();
    int _iHeight = m_rcWnd.height();
    QPoint center(_x0+_iWidth/2, _y0+_iHeight / 2);

    QFontMetrics _fm = painter->fontMetrics();
    QRect _rcFont;

    int _x, _y, _W, _H;
    switch (m_eLineType)
    {
    case LINE_VERTICAL:
        _str.sprintf("%.1f", m_Geometry.left())  ;
        if( _pConfig->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
            _str.prepend("ang:");
        }else{
            _str.append("mm");
        }
        _rcFont = _fm.boundingRect(_str);
        _W = _rcFont.width();
        _H = _rcFont.height();

        if(m_nId % 2 == 0)	_y = _y0 + 2;
        else				_y = _y0 + _iHeight - (_H - 4);

        if(_ptScene.x() > center.x())	_x = - (_W + 4);
        else							_x = 1;
        break;
    case LINE_HORIZENTAL:
        _str.sprintf("%.1f", m_Geometry.top())  ;
        if( _pConfig->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
            _str.prepend("ang:");
        }else{
            _str.append("mm");
        }

        _rcFont = _fm.boundingRect(_str);
        _W = _rcFont.width();
        _H = _rcFont.height();

        if(m_nId % 2 == 0)	_x = _x0;
        else				_x = _x0 + _iWidth - _W - 12;

        if(_ptScene.y() > center.y())	_y = -(_H - 3);
        else							_y = 5;
        break;
    default:
        return;
    };

    bool bBackground = true;

    if(bBackground) {
        QBrush _brush(QColor(0,0,0));
        painter->setBackground(_brush);
        painter->setBackgroundMode(Qt::OpaqueMode);
    } else {
        painter->setBackgroundMode(Qt::TransparentMode);
    }

    _x += 1;
    _y += 1 + (g_nRectSize + 3);
    painter->drawText( _x, _y, _str );
}

