#include "DopplerLineItem.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <process/ParameterProcess.h>

const int g_nRectSize = 2 ;
static int g_nZValue = 50 ;
DopplerLineItem::DopplerLineItem(const QColor& cColor_)
{
	m_nWidth  = 100;
	m_nHeight = 100;

	double _nPos1  = 10 ;
	double _nPos2  = 10 ;
	m_rect.setLeft(_nPos1 - g_nRectSize) ;
	m_rect.setRight(_nPos1 + g_nRectSize);
	m_rect.setTop(_nPos2 - g_nRectSize);
	m_rect.setBottom(_nPos2 + g_nRectSize);

	m_cColor   = cColor_;
	setZValue(g_nZValue);
    SetMoveType(LINE_MOVE_NO);
    m_eStype = Qt::SolidLine;
    m_eLineType = LINE_TYPE::LINE_FREE;
    m_tofdDepth = false;
    m_wheelAble = false;
}

void DopplerLineItem::SetLineType(LINE_TYPE eType_)
{
	double _nPos1  = 10 ;
	double _nPos2  = 10 ;
	m_eLineType = eType_  ;

	switch (m_eLineType)
	{
	case LINE_VERTICAL:
		_nPos1 = 0;
		setCursor(QCursor(Qt::SizeHorCursor));
		break;
	case LINE_HORIZENTAL:
		_nPos2 = 0;
		setCursor(QCursor(Qt::SizeVerCursor));
		break;
	default:
		break;
	};

	m_rect.setLeft(_nPos1 - g_nRectSize) ;
	m_rect.setRight(_nPos1 + g_nRectSize);
	m_rect.setTop(_nPos2 - g_nRectSize);
	m_rect.setBottom(_nPos2 + g_nRectSize);

}

DopplerLineItem::LINE_TYPE DopplerLineItem::GetLineType() const
{
	return m_eLineType;
}

void DopplerLineItem::SetMoveType(LINE_MOVE_TYPE eType_)
{
	m_eMoveType = eType_  ;
	if(m_eMoveType)
		setFlags(ItemIsSelectable | ItemIsMovable);
	else
		setFlags(ItemIsPanel);
}


void DopplerLineItem::SetLineStyle(Qt::PenStyle eStype_)
{
	m_eStype = eStype_  ;
	update() ;
}

QRectF DopplerLineItem::boundingRect() const
{
	QRectF _rect ;
	switch (m_eLineType)
	{
	case LINE_FREE:
		_rect = QRectF(-g_nRectSize , -g_nRectSize , m_nWidth+ g_nRectSize, m_nHeight+ g_nRectSize);
		break;
	case LINE_VERTICAL:
	case LINE_HORIZENTAL:
		_rect = QRectF( -g_nRectSize , -g_nRectSize , m_nWidth + 2 * g_nRectSize , m_nHeight + 2 * g_nRectSize) ;
		break;
	default:
		break;
	};

	return _rect;
}

QPainterPath DopplerLineItem::shape() const
{
	QPainterPath path;
	QRectF _rct(0 , 0 , 0 , 0 ) ;
	if(!(flags() & QGraphicsItem::ItemIsPanel))
		_rct = boundingRect () ;

	path.addRect(_rct) ;
	return path;
}

void DopplerLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* /*widget*/)
{


    //******** to change the background color of when mouse is rect
    QColor fillColor = (option->state & QStyle::State_Selected) ? m_cColor.dark(50) : m_cColor;
    if (option->state & QStyle::State_MouseOver)
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
    _NewPen.setWidth(0);
    _NewPen.setColor(fillColor);
    _NewPen.setStyle(m_eStype);
    painter->setPen(_NewPen);
    painter->drawLine(0, 0 , m_nWidth , m_nHeight );

    //if(m_eMoveType)
    //{
    //_NewPen.setStyle(Qt::SolidLine) ;
    //painter->setPen(_NewPen);
    //painter->drawRect(m_rect);
    //}
    DrawLabel(painter) ;
    painter->restore();
}
QPointF ptTmp;
QRectF  rcTmp;
void DopplerLineItem::DrawLabel(QPainter *painter)
{
    ParameterProcess* _pProcess = ParameterProcess::Instance();
	QPen _pen = painter->pen();
	_pen.setColor(m_cColor) ;
	painter->setPen(_pen);
//    double scaleFactor = 1.0 / painter->matrix().m11();
//    painter->scale(scaleFactor, scaleFactor);
	QString _str ;
//    QFont resetFont = painter->font();
//    int fontSize = 100.0/painter->matrix().m11();
//    resetFont.setStretch(fontSize);
//    painter->setFont(resetFont);

	QPointF _ptScene = GetItemScenePos();
/*
	int _x0 = 0;
	int _y0 = 0;
	int _iWidth = m_cSize.width();
	int _iHeight = m_cSize.height();
	QPoint center(_iWidth/2, _iWidth / 2);
*/
	int _x0 = m_rcWnd.left();
	int _y0 = m_rcWnd.top();
	int _iWidth = m_rcWnd.width();
	int _iHeight = m_rcWnd.height();
	QPoint center(_x0+_iWidth/2, _y0+_iHeight / 2);

	QFontMetrics _fm = painter->fontMetrics();
	QRect _rcFont;

	int _x, _y, _W, _H;
    double buff;
	switch (m_eLineType)
	{
	case LINE_VERTICAL:
        if(m_tofdDepth){
            buff = _pProcess->transTofdHalfSoundPathToDepth( m_Geometry.left(), m_pcs);
        }else{
            buff = m_Geometry.left();
        }
        _str.sprintf("%.1f", buff);
		_rcFont = _fm.boundingRect(_str);
        _W = _rcFont.width();
        _H = _rcFont.height();
//        _W = 20;
//        _H = 10;

		if(m_nId % 2 == 0)	_y = _y0 + 2;
		else				_y = _y0 + _iHeight - (_H - 4);

		if(_ptScene.x() > center.x())	_x = - (_W + 4);
		else							_x = 1;
		break;
	case LINE_HORIZENTAL:
        if(m_tofdDepth){
            buff = _pProcess->transTofdHalfSoundPathToDepth( m_Geometry.top(), m_pcs);
        }else{
            buff = m_Geometry.top();
        }
        _str.sprintf("%.1f", buff);
		_rcFont = _fm.boundingRect(_str);
        _W = _rcFont.width();
        _H = _rcFont.height();
//        _W = 20;
//        _H = 10;

		if(m_nId % 2 == 0)	_x = _x0;
		else				_x = _x0 + _iWidth - _W - 2;

		if(_ptScene.y() > center.y())	_y = -(_H - 3);
		else							_y = 5;
		break;
	default:
		return;
	};

	bool bBackground = true;
/*
	if(m_pDataView != NULL) {
		int _nDisp = m_pDataView->GetDataViewDrawType();
		if(_nDisp != setup_DISPLAY_MODE_A_H
		|| _nDisp != setup_DISPLAY_MODE_A_V) {
			bBackground = false;
		}
	}
*/
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
void DopplerLineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DopplerGraphicsItem::mousePressEvent(event);
    mouseMoveEvent(event) ;
}
void DopplerLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
	/*
	if(m_eMoveType) {
		QPointF  _posItem = event->pos()  ;
		QPointF _posScene = event->scenePos() ;
		int _x = _posScene.x() ;
		int _y = _posScene.y() ;
		const int _nAdjustOff = 20;

		if(_x < 0 - _nAdjustOff) {
			_posScene.setX(0 - _nAdjustOff);
		} else if(_x > m_cSize.width() + _nAdjustOff) {
			_posScene.setX(m_cSize.width() + _nAdjustOff);
		}
		if(_y < 0 - _nAdjustOff) {
			_posScene.setY(0 - _nAdjustOff);
		} else if(_y > m_cSize.height() + _nAdjustOff) {
			_posScene.setY(m_cSize.height() + _nAdjustOff);
		}
		setPos(_posScene) ;
		double _fX  = _posItem.x() ;
		double _fY  = _posItem.y() ;
		m_rect.setLeft(_fX - g_nRectSize) ;
		m_rect.setRight(_fX + g_nRectSize);
		m_rect.setTop(_fY - g_nRectSize);
		m_rect.setBottom(_fY + g_nRectSize);
	}*/
	setSelected(false);
	update();
}
void DopplerLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_eMoveType)  return ;

    QPointF  _posItem = event->pos()  ;
    QPointF _posScene = event->scenePos() ;

    int _x = _posScene.x() ;
    int _y = _posScene.y() ;

    const int _nAdjustOff = 20;

    if(_x < 0 - _nAdjustOff) {
        _posScene.setX(0 - _nAdjustOff);
    } else if(_x > m_cSize.width() + _nAdjustOff) {
        _posScene.setX(m_cSize.width() + _nAdjustOff);
    }

    if(_y < 0 - _nAdjustOff) {
        _posScene.setY(0 - _nAdjustOff);
    } else if(_y > m_cSize.height() + _nAdjustOff) {
        _posScene.setY(m_cSize.height() + _nAdjustOff);
    }
    /*
    if(_x < 0 ) {
        _posScene.setX(0);
    } else if(_x > m_cSize.width() - 2) {
        _posScene.setX(m_cSize.width() - 2);
    }

    if(_y < 1 ) {
        _posScene.setY(1);
    } else if(_y > m_cSize.height() - 2) {
        _posScene.setY(m_cSize.height() - 2);
    }
    */

    switch (m_eMoveType)
    {
    case LINE_MOVE_VERTICAL:
        _posScene.setX(0.0);
        _posItem.setY(0);
        break;
    case LINE_MOVE_HORIZENTAL:
        _posScene.setY(0.0);
        _posItem.setX(0);
        break;
    default:
        break;
    }
    setPos(_posScene);
    double _fX  = _posItem.x();
    double _fY  = _posItem.y();
    m_rect.setLeft(_fX - g_nRectSize);
    m_rect.setRight(_fX + g_nRectSize);
    m_rect.setTop(_fY - g_nRectSize);
    m_rect.setBottom(_fY + g_nRectSize);
}

void DopplerLineItem::SetItemGeometry (QRectF& rect_)
{
	QGraphicsScene* _pScene = scene () ;
	if(m_eLineType == LINE_VERTICAL)
	{
		m_nWidth = 0 ;
		if(_pScene)
			m_nHeight = _pScene->height() ;
		else
			m_nHeight = 1000 ;
		rect_.setTop(0);
	}
	else if(m_eLineType == LINE_HORIZENTAL)
	{
		m_nHeight = 0 ;

		if(_pScene)
            m_nWidth = _pScene->width() ;
		else
			m_nWidth = 1000 ;

		rect_.setLeft(0);
	}

	this->setPos(rect_.topLeft());
}

void DopplerLineItem::SetScenceSize(QSize size_)
{
	m_cSize = size_ ;
}

//----------------------------------------------------------
//  wuhan cursor 2015-05-19
QRectF DopplerLineItem::GetCursorValidArea()
{
	QPointF _pos = GetItemScenePos();
    QRectF _rect(0, 0, 0, 0);
    QGraphicsScene* _pScene = scene();

    switch(m_eLineType)
    {
    case LINE_FREE:
        break;
    case LINE_VERTICAL:
        _rect.setLeft(_pos.x() - g_nRectSize);
        _rect.setTop(0);
        _rect.setWidth(2*g_nRectSize);
        _rect.setHeight(_pScene->height());
        break;
	case LINE_HORIZENTAL:
        _rect.setLeft(0);
        _rect.setTop(_pos.y()-g_nRectSize);
        _rect.setWidth(_pScene->width());
        _rect.setHeight(2*g_nRectSize);
        break;
	};

	return _rect;
}

Qt::CursorShape DopplerLineItem::GetCursorShape(QPointF posCursor_)
{
	if(!m_eMoveType)  return Qt::ArrowCursor;

//	QPointF _pos = GetItemScenePos();
	QRectF _rect = GetCursorValidArea();

	if(posCursor_.x() < _rect.left())		return Qt::ArrowCursor;
	if(posCursor_.x() >= _rect.right())		return Qt::ArrowCursor;
	if(posCursor_.y() < _rect.top())		return Qt::ArrowCursor;
	if(posCursor_.y() >= _rect.bottom())	return Qt::ArrowCursor;


	switch (m_eLineType)
	{
	case LINE_VERTICAL:		return Qt::SizeHorCursor;
	case LINE_HORIZENTAL:   return Qt::SizeVerCursor;
	default:			return Qt::ArrowCursor;
	};
	ptTmp = posCursor_;
	rcTmp = _rect;
	this->update();
}
//-----------------------------------------------------------
//黑色虚线，在B，C视图中显示当前的扫查帧，和滑块联动
DopplerScanMarker::DopplerScanMarker(const QColor& cColor_) : DopplerLineItem(cColor_){}

void DopplerScanMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* /*widget*/)
{
    //******** to change the background color of when mouse is rect
    QColor fillColor =(option->state & QStyle::State_Selected)?m_cColor.dark(50) : m_cColor;
    if(option->state & QStyle::State_MouseOver)
      fillColor = fillColor.light(50);
    //******** get the enlarged rate, and by which to determine whether draw the details
    //******** the real display size diliver real size (in pixels)
    //const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    switch(m_eLineType)
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

    dashes << 1 << 4 << 1 << 4;
    _NewPen.setDashPattern(dashes);
    painter->setPen(_NewPen);
    painter->drawLine(0, 0 , m_nWidth , m_nHeight );
    painter->restore();
}

DopplerCalibrationMark::DopplerCalibrationMark(const QColor& cColor_) : DopplerLineItem(cColor_){}

void DopplerCalibrationMark::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* /*widget*/)
{
    //******** to change the background color of when mouse is rect
    QColor fillColor = (option->state & QStyle::State_Selected) ? m_cColor.dark(50) : m_cColor;
    if (option->state & QStyle::State_MouseOver)
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

    switch(m_nId)
    {
    case setup_CURSOR_TFOD_LW:	DrawLabel(painter, (char*)"LW");	break;
    case setup_CURSOR_TFOD_BW:	DrawLabel(painter, (char*)"BW");	break;
    }

    painter->restore();
}

void DopplerCalibrationMark::DrawLabel(QPainter *painter, char* str_)
{
	QPen _pen = painter->pen();
	_pen.setColor(m_cColor) ;  //(QColor(255 , 255 , 0));
	painter->setPen(_pen);
	QString _str = QString(QObject::tr(str_));

	QPointF _ptScene = GetItemScenePos();
	//float _fData;
	int _iWidth = m_cSize.width();
	int _iHeight = m_cSize.height();
	int _x, _y;
	int _W = 16;
	int _H = 10;

	switch (m_eLineType)
	{
	case LINE_VERTICAL:
		if(_ptScene.x() > _iWidth/2) {
		//	_x = 0 - _W - 2;  _y = 1;
			_x = 0 - _W - 2;  _y = _iHeight - _H - 1;
		} else {
		//	_x = 2; _y = 1;
			_x = 2; _y = _iHeight - _H - 1;
		}
		break;
	case LINE_HORIZENTAL:
		if(_ptScene.y() > _iHeight/2) {
		//	_x = 1; _y = -12;
			_x = _iWidth - _W - 1;	_y = -12;
		} else {
		//	_x = 1; _y = 2;
			_x = _iWidth - _W - 1; _y = 2;
		}
		break;
	default:
		return;
	};
	//QBrush _brush(QColor(0,0,0));//(QColor(130,130,130) );
	//QRectF _rcStr;
	//_rcStr.setLeft(_x);
	//_rcStr.setTop(_y);
	//_rcStr.setWidth(_W);
	//_rcStr.setHeight(_H);
	_x += 1;
	_y += 1 + (g_nRectSize + 3);
	//painter->fillRect(_rcStr, _brush);
	painter->drawText( _x, _y, _str );
}

