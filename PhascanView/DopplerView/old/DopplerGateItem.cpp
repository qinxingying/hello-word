#include "DopplerGateItem.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QColor>
#include <QList>
#include <QVarLengthArray>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
const int g_nGateMarkerHeight = 5;

static int g_nZValue = 100 ;
DopplerGateItem::DopplerGateItem(const QColor& cColor_)
{

    m_nWidth  = 10;
    m_nHeight = 5;
    m_cColor   = cColor_;
    m_eMode    = GATE_MODE_GATE_HORIZENTAL  ;
    setZValue(g_nZValue--);
    setFlags(ItemIsPanel);
    //setFlags(/*ItemIsPanel */ItemIsSelectable | ItemIsMovable);
}

void DopplerGateItem::SetDrawMode(GATE_DRAW_MODE eMode_)
{
    m_eMode  = eMode_  ;
}

QRectF DopplerGateItem::boundingRect() const
{
    QRectF _rect ;
    switch (m_eMode)
    {
    case GATE_MODE_GATE_HORIZENTAL :
        {
            int _nHeight = (g_nGateMarkerHeight + 1) / 2 ;
            _rect = QRectF(0, - _nHeight , m_nWidth , 2 * _nHeight + 1);
        }
        break;
    case GATE_MODE_GATE_VERTICAL:
        {
            int _nWidth = (g_nGateMarkerHeight + 1) / 2 ;
            _rect = QRectF( -_nWidth , 0,  2 * _nWidth + 1 , m_nHeight );
        }
        break;
    case GATE_MODE_LINE_HORIZENTAL:
    case GATE_MODE_LINE_VERTICAL:
            _rect = QRectF( 0 , 0,  m_nWidth , m_nHeight );
        break;
    default:
        break;
    }

    return _rect ;
}

QPainterPath DopplerGateItem::shape() const
{
    QPainterPath path;
    QRectF _rct(0 , 0 , 0 , 0 ) ;
    if(!(flags() & QGraphicsItem::ItemIsPanel))
        _rct = boundingRect () ;

    path.addRect(_rct) ;
    return path;
}

void DopplerGateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* /*widget*/)
{
	//m_eMode    = GATE_MODE_LINE_HORIZENTAL  ;
	int _nLineWidth = 3 ;
    //******** to change the background color of when mouse is rect
    QColor fillColor ;
    if(option->state & QStyle::State_Selected)
    {
        fillColor = m_cColor.dark(150) ;
		_nLineWidth = 2;
    }
    else
        fillColor = m_cColor ;
    // = (option->state & QStyle::State_Selected) ? { m_cColor.dark(150) ; _nLineWidth = 2}: m_cColor;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);
    //******** get the enlarged rate, and by which to determine whether draw the details
    //******** the real display size diliver real size (in pixels)
    //const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    QPen _OldPen = painter->pen();
    QPen _NewPen = _OldPen ;

    _NewPen.setWidth(0);
    _NewPen.setColor(fillColor);


    switch (m_eMode)
    {
    case GATE_MODE_GATE_HORIZENTAL :
        {
            painter->setPen(_NewPen);
            int nTmp = (g_nGateMarkerHeight + 1) / 2 ;
            QVarLengthArray<QLineF, 2> lines;
            lines.append(QLineF(0 , - nTmp , 0 , nTmp ));
            lines.append(QLineF(m_nWidth + 1, -nTmp , m_nWidth + 1, nTmp));
            painter->drawLines(lines.data() , 2);
            _NewPen.setWidth(_nLineWidth);
            painter->setPen(_NewPen);
            painter->drawLine(QPointF(0, 0) , QPointF(m_nWidth  , 0));
        }
        break;
    case GATE_MODE_GATE_VERTICAL:
        {
            painter->setPen(_NewPen);
            int nTmp = (g_nGateMarkerHeight + 1) / 2 ;
            QVarLengthArray<QLineF, 2> lines;
            lines.append(QLineF(-nTmp , 0 , nTmp , 0 ));
            lines.append(QLineF(-nTmp , m_nHeight + 1, nTmp , m_nHeight + 1)) ;
            painter->drawLines(lines.data() , 2);
            _NewPen.setWidth(_nLineWidth);
            painter->setPen(_NewPen);
            painter->drawLine(QPointF(0 , 0) , QPointF( 0, m_nHeight));
        }
        break;
    case GATE_MODE_LINE_HORIZENTAL:
        {
            QGraphicsScene* _pScene = scene () ;
            if(_pScene)
                m_nHeight = _pScene->height() ;

            QVector<qreal> dashes;
            dashes << 1 << 4 << 1 <<4 ;
            _NewPen.setDashPattern(dashes);
            painter->setPen(_NewPen);
            QVarLengthArray<QLineF, 2> lines;
            lines.append(QLineF(0 , 0 , 0 , m_nHeight-1  ));
            lines.append(QLineF(m_nWidth + 1 , 0 , m_nWidth + 1, m_nHeight-1 ));
            painter->drawLines(lines.data() , 2);
        }
        break;
    case GATE_MODE_LINE_VERTICAL:
        {
            QGraphicsScene* _pScene = scene () ;
            if(_pScene)
                m_nWidth = _pScene->width() ;

            QVector<qreal> dashes;
            dashes << 1 << 4 << 1 <<4 ;
            _NewPen.setDashPattern(dashes);
            painter->setPen(_NewPen);
            QVarLengthArray<QLineF, 2> lines;
            lines.append(QLineF(0 , 0 , m_nWidth -1 ,  0 ));
            lines.append(QLineF(0 , m_nHeight + 1 , m_nWidth -1, m_nHeight + 1));
            painter->drawLines(lines.data() , 2);
        }
        break;
    default:
        break;
    }

    painter->setPen(_OldPen);
}

void DopplerGateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DopplerGraphicsItem::mousePressEvent(event) ;
    QGraphicsItem::mousePressEvent(event);
}

void DopplerGateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}
//
//void DopplerGateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsItem::mouseReleaseEvent(event);//
//
//}

void DopplerGateItem::SetItemGeometry(QRectF& rect_)
{
    m_nWidth  = rect_.width();
    m_nHeight = rect_.height();
    switch (m_eMode)
    {
    case GATE_MODE_GATE_HORIZENTAL :
    case GATE_MODE_GATE_VERTICAL:
        this->setPos(rect_.topLeft());
        break;
    case GATE_MODE_LINE_HORIZENTAL:
        this->setPos(rect_.left() , 0);
        break;
    case GATE_MODE_LINE_VERTICAL:
        this->setPos(0 , rect_.top());
        break;
    default:
        break;
    }
}
