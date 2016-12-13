#include "DopplerGateItem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

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
		this->setPos(rect_.left() , 0);
		break;
	case GATE_MODE_LINE_VERTICAL:
		this->setPos(0 , rect_.top());
		break;
	default:
		break;
	}
}
