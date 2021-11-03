#include "DopplerGateItem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QVarLengthArray>

const int g_nGateMarkerHeight = 5;
static int g_nDfZValue = 100 ;
DopplerGateItem::DopplerGateItem(const QColor& cColor_)
{

	m_nWidth  = 10;
	m_nHeight = 5;

	m_cColor   = cColor_;
	m_eMode	= GATE_MODE_GATE_HORIZENTAL  ;
	setZValue(g_nDfZValue);
//	setFlags(ItemIsPanel);
    setFlags(/*ItemIsPanel */ItemIsSelectable | ItemIsMovable);
    setCursor(QCursor(Qt::SizeAllCursor));
    setAcceptHoverEvents(true);
}

void DopplerGateItem::SetDrawMode(GATE_DRAW_MODE eMode_)
{
    m_eMode  = eMode_  ;
}

void DopplerGateItem::setCurveGate(QVector<QPointF> start, QVector<QPointF> end)
{
    m_gateStart = start;
    m_gateEnd = end;
    this->setPos(0, 0);
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
    int _nLineWidth;
	QColor fillColor;
	if(option->state & QStyle::State_Selected) {
		fillColor = m_cColor.dark(150) ;
		_nLineWidth = 2;
	} else {
		fillColor = m_cColor ;
		_nLineWidth = 3 ;
	}

	if (option->state & QStyle::State_MouseOver)
		fillColor = fillColor.light(125);

	painter->save();
	QPen _NewPen ;

	_NewPen.setWidth(0);
	_NewPen.setColor(fillColor);

	switch (m_eMode)
	{
	case GATE_MODE_GATE_HORIZENTAL :
		{
            int nTmp = (g_nGateMarkerHeight + 1) / 2 ;

            painter->setPen(_NewPen);
            painter->drawLine(QPointF(0 , - nTmp) , QPointF(0 , nTmp));
            painter->drawLine(QPointF(m_nWidth + 1, -nTmp) , QPointF(m_nWidth + 1, nTmp));

            _NewPen.setWidth(_nLineWidth);
            painter->setPen(_NewPen);
            painter->drawLine(QPointF(0, 0) , QPointF(m_nWidth  , 0));
		}
		break;
	case GATE_MODE_GATE_VERTICAL:
		{
            int nTmp = (g_nGateMarkerHeight + 1) / 2 ;

            painter->setPen(_NewPen);
            painter->drawLine(QPointF(-nTmp , 0) , QPointF(nTmp , 0));
            painter->drawLine(QPointF(-nTmp , m_nHeight + 1) , QPointF(nTmp , m_nHeight + 1));

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
    case GATE_MODE_S_TRUEDEPTH:
        {
            QGraphicsScene* _pScene = scene ();
            if(_pScene)
                m_nWidth = _pScene->width();

            QVector<qreal> dashes;
            dashes << 1 << 4 << 1 <<4 ;
            _NewPen.setDashPattern(dashes);
            painter->setPen(_NewPen);

            if(m_gateStart.size() == 0){
                QVarLengthArray<QLineF, 2> lines;
                lines.append(QLineF(0 , 0 , m_nWidth -1 ,  0 ));
                lines.append(QLineF(0 , m_nHeight + 1 , m_nWidth -1, m_nHeight + 1));
                painter->drawLines(lines.data() , 2);
            }else{
                for(int i = 0; i < m_gateStart.size() - 1; i++){
                    painter->drawLine(m_gateStart[i], m_gateStart[i+1]);
                    painter->drawLine(m_gateEnd[i], m_gateEnd[i+1]);
                }
            }
        }
        break;
    case GATE_MODE_S_SOUNDPATH:
        {
            QGraphicsScene* _pScene = scene ();
            if(_pScene)
                m_nHeight = _pScene->height();

            QVector<qreal> dashes;
            dashes << 1 << 4 << 1 <<4 ;
            _NewPen.setDashPattern(dashes);
            painter->setPen(_NewPen);

            if(m_gateStart.size() == 0){
                QVarLengthArray<QLineF, 2> lines;
                lines.append(QLineF(0 , 0 , 0 , m_nHeight-1  ));
                lines.append(QLineF(m_nWidth + 1 , 0 , m_nWidth + 1, m_nHeight-1 ));
                //qDebug()<<"QLineF"<<lines.data()[0]<<lines.data()[1];
                painter->drawLines(lines.data() , 2);
            }else{
                for(int i = 0; i < m_gateStart.size() - 1; i++){
                    painter->drawLine(m_gateStart[i], m_gateStart[i+1]);
                    painter->drawLine(m_gateEnd[i], m_gateEnd[i+1]);
                }
            }
        }
        break;
	default:
		break;
	}

	//DrawLabel(painter, fillColor, false);
	painter->restore();

}

void DopplerGateItem::DrawLabel(QPainter *painter, QColor& cColor_, bool bSel_)
{
    Q_UNUSED(bSel_);
	QPen _pen = painter->pen();
	_pen.setColor(cColor_) ;
	painter->setPen(_pen);

	QString _str ;
	_str.sprintf("%d", m_nId+1)  ;
	painter->drawText(0 , -4 , _str );
}

void DopplerGateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF posScene = event->scenePos() ;
    QPointF  posItem = event->pos()  ;
    int x = posScene.x() ;
    int y = posScene.y() ;

    if (cursor().shape() == Qt::SizeAllCursor) {
        this->setPos(x - m_mouseDownPos.x(), y - m_mouseDownPos.y());
    } else {
        switch (m_eMode)
        {
        case GATE_MODE_GATE_HORIZENTAL :
            if (posItem.x() < 0) {
                return;
            }
            m_nWidth += posItem.x() - m_nWidth;
            break;
        case GATE_MODE_GATE_VERTICAL:
            if (posItem.y() < 0) {
                return;
            }
            m_nHeight += posItem.y() - m_nHeight;
            break;
        default:
            break;
        }
    }
}

void DopplerGateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_eMode)
    {
    case GATE_MODE_GATE_HORIZENTAL :
    case GATE_MODE_GATE_VERTICAL:
        m_mouseDownPos = event->pos();
        DopplerGraphicsItem::mousePressEvent(event) ;
        break;
    default:
        event->ignore();
        break;
    }

}

void DopplerGateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    setSelected(false);
    update();
}

void DopplerGateItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF p = event->pos();
    switch (m_eMode)
    {
    case GATE_MODE_GATE_HORIZENTAL :
        if (p.x() > m_nWidth - 3) {
            setCursor(QCursor(Qt::PointingHandCursor));
        } else {
            setCursor(QCursor(Qt::SizeAllCursor));
        }
        break;
    case GATE_MODE_GATE_VERTICAL:
        if (p.y() > m_nHeight - 3) {
            setCursor(QCursor(Qt::PointingHandCursor));
        } else {
            setCursor(QCursor(Qt::SizeAllCursor));
        }
        break;
    default:
        unsetCursor();
        setAcceptHoverEvents(false);
        break;
    }
}

void DopplerGateItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF p = event->pos();
    switch (m_eMode)
    {
    case GATE_MODE_GATE_HORIZENTAL :
        if (p.x() > m_nWidth - 3) {
            setCursor(QCursor(Qt::PointingHandCursor));
        } else {
            setCursor(QCursor(Qt::SizeAllCursor));
        }
        break;
    case GATE_MODE_GATE_VERTICAL:
        if (p.y() > m_nHeight - 3) {
            setCursor(QCursor(Qt::PointingHandCursor));
        } else {
            setCursor(QCursor(Qt::SizeAllCursor));
        }
        break;
    default:
        unsetCursor();
        setAcceptHoverEvents(false);
        break;
    }
}

void DopplerGateItem::SetItemGeometry (QRectF& rect_)
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
    {
        QGraphicsScene* _pScene = scene () ;
        if(_pScene)
            m_nHeight = _pScene->height() ;
		this->setPos(rect_.left() , 0);
    }
		break;
    case GATE_MODE_LINE_VERTICAL:
    {
        QGraphicsScene* _pScene = scene () ;
        if(_pScene)
            m_nWidth = _pScene->width() ;
		this->setPos(0 , rect_.top());
		break;
    }
    case GATE_MODE_S_TRUEDEPTH:
    {
        QGraphicsScene* _pScene = scene ();
        if(_pScene)
            m_nWidth = _pScene->width();
        this->setPos(0 , rect_.top());
    }
        break;
    case GATE_MODE_S_SOUNDPATH:
    {
        QGraphicsScene* _pScene = scene () ;
        if(_pScene)
            m_nHeight = _pScene->height() ;
        this->setPos(rect_.left() , 0);
    }
        break;
	default:
		break;
    }
}
