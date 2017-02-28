#include "DopplerRulerBar.h"
#include <QPainter>
#include <math.h>
#include <QDragEnterEvent>

const int g_nBaseLineOffset = 3 ;
const int g_nMinMarkerLength= 3 ;
const int g_nMidMarkerLength= 5 ;
const int g_nMaxMarkerLength= 7 ;

const int g_nSliderCellMin  = 10;

DopplerRulerBar::DopplerRulerBar(QWidget *parent , RULER_BAR_TYPE eType_) :
	QWidget(parent)
{
	m_eType = eType_  ;
	setAutoFillBackground(true);
	if(RULER_BAR_LEFT == m_eType || RULER_BAR_RIGHT == m_eType)
		setFixedWidth(DOPPLER_RULER_WIDTH);
	else
		setFixedHeight(DOPPLER_RULER_WIDTH);
	// marker color
	m_cFgColor = QColor(255, 255 , 255);
	m_cSlider  = QColor(100, 100 , 100);
	// backgroud color
	QColor _cColor(0, 0 , 0) ;
	SetBackgroudColor(&_cColor);
	m_nSliderStart = m_nStart  =  0   ;
	m_nSliderEnd = m_nEnd	=  100 ;
	m_strUnit =  QString("") ;
	m_bSliderON = false;
	m_bSliderDrag = false;
	setAcceptDrops(false);
	setMouseTracking(true);
}



void DopplerRulerBar::SetBackgroudColor(QColor* cColor_)
{
	m_cBgColor = *cColor_ ;
	QPalette pal = this->palette();
	pal.setColor(QPalette::Background , *cColor_);
	setPalette(pal);
	update();
}

void DopplerRulerBar::SetMarkerColor(QColor* cColor_)
{
	m_cFgColor = *cColor_ ;
	update();
}

void DopplerRulerBar::SetMarkerRange(double nStart_ , double nStop_, double nSliderStart_ , double nSliderStop_)
{
	m_nStart = nStart_ ;
	m_nEnd   = nStop_  ;

	m_nSliderStart = nSliderStart_ ;
	m_nSliderEnd   = nSliderStop_  ;
	update();
}

void DopplerRulerBar::GetMarkerRange(double* nStart_ , double* nStop_, double* nSliderStart_ , double* nSliderStop_)
{
	*nStart_ = m_nStart;
	*nStop_  = m_nEnd;

	*nSliderStart_ = m_nSliderStart;
	*nSliderStop_  = m_nSliderEnd;
}

void DopplerRulerBar::SetMarkerUnit(QString* strUnit_)
{
	m_strUnit = *strUnit_  ;
	update();
}


void DopplerRulerBar::paintEvent(QPaintEvent*)
{
	QPainter painter(this) ;
/*
	if(m_bSliderON) {
		CalSliderArea();
		CalSliderRect();
		drawSlider(painter);
	}
*/
	QPen _OldPen = painter.pen()  ;
	QPen _NewPen = _OldPen ;
	_NewPen.setColor(m_cFgColor);
	painter.setPen(_NewPen);
	switch(m_eType)
	{
	case RULER_BAR_LEFT:
		drawLeftRuler(painter);
		break;
	case RULER_BAR_RIGHT:
		drawRightRuler(painter);
		break;
	case RULER_BAR_BOTTOM:
		drawBottomRuler(painter);
		break;
	case RULER_BAR_TOP:
		break;
	default:
		break;
	}
	painter.setPen(_OldPen);
}


int DopplerRulerBar::getRulerMarkQty(int nLength_)
{
	int _nMarkQty = 20 ;
	if(   nLength_ >= 500)
	{
		nLength_ = (nLength_ / 500) * 500 ;
		_nMarkQty = nLength_ / 5 ;
	}
	else if ((nLength_ >= 300)&&(nLength_ < 500))
		_nMarkQty = 100;
	else if ((nLength_ >  200)&&(nLength_ < 300))
		_nMarkQty = 60;
	else if ((nLength_ >  100)&&(nLength_ < 200))
		_nMarkQty = 40;
	else
		_nMarkQty = 20;

	return _nMarkQty ;
}

double DopplerRulerBar::getRulerMarInterval(int nMarkQty_ , double nRange_)
{
	if(nRange_ < 0.0000001)  return 0.0;
	double _nInterval = nRange_ / nMarkQty_  ;
	// get proper mark interval
	if	  (_nInterval < 0.1 )					   _nInterval = 0.1 ;
	else if ( 0.1 <_nInterval   && _nInterval < 0.5 )  _nInterval = 0.5 ;
	else if ( 0.5 <_nInterval   && _nInterval <= 1.5  )  _nInterval =   1 ;
	else if (_nInterval > 1.5   && _nInterval <= 2.5)  _nInterval =   2 ;
	else if (_nInterval > 2.5   && _nInterval <= 7.5)  _nInterval =   5 ;
	else if (_nInterval > 7.5   && _nInterval <= 10 )  _nInterval = 10  ;
	else if (_nInterval > 10	&& _nInterval < 50  )  _nInterval = 10 * (1 + (int)(_nInterval / 10)) ;
	else if (_nInterval >= 50   && _nInterval <= 100)  _nInterval = 100 ;
	else if (_nInterval > 100   && _nInterval <= 200)  _nInterval = 200 ;
	else if (_nInterval > 200)						 _nInterval = 100 * (1 + (int)(_nInterval / 100)) ;

	return _nInterval ;
}


void DopplerRulerBar::drawLeftRuler(QPainter& painter)
{
	//***** if start == end , do not draw anything
	if(m_nStart == m_nEnd)	 return ;
	//QPainter painter(this);

	double _nStart , _nStop , _nCurrentPos , _nRange;
	int i , _nStartIndex , _nPos , _nDirection ;
	int _nWidth   = width();
	int _nHeight  = height();

	int _nMarkQty = getRulerMarkQty(_nHeight) ;
	_nRange = fabs(m_nStart - m_nEnd) ;
	double _nInterval = getRulerMarInterval(_nMarkQty , _nRange) ;
	double _nPixelPerUnit = _nHeight / _nRange ;

	int _nBaseLinePos = _nWidth - g_nBaseLineOffset  - 1 ;
	int _nMinLineLeftPos = _nBaseLinePos - g_nMinMarkerLength ;
	int _nMidLineLeftPos = _nBaseLinePos - g_nMidMarkerLength ;
	int _nMaxLineLeftPos = _nBaseLinePos - g_nMaxMarkerLength ;

	if(m_nStart > m_nEnd)
	{
	   _nDirection = 1 ;
	   _nStart = m_nEnd ;
	   _nStop  = m_nStart ;
	}
	else
	{
	   _nDirection = 0 ;
	   _nStart = m_nStart ;
	   _nStop  = m_nEnd   ;
	}
	_nStartIndex = _nStart / _nInterval ;
	if(_nStart > 0)
	{
		_nStartIndex +=  1 ;
	}
	_nCurrentPos = _nStart  ;
	QString _str ;
	for(i = _nStartIndex ; _nCurrentPos < _nStop ; i++)
	{
		_nCurrentPos = i * _nInterval ;
		_nPos = (_nCurrentPos - _nStart) * _nPixelPerUnit ;
		if(_nDirection)
		{
		   _nPos  = _nHeight - _nPos - 1 ;
		}
		_nPos += 0.5 ;
		if(i % 10 == 0)
		{
			painter.drawLine(QPointF(_nMaxLineLeftPos ,_nPos) , QPointF(_nBaseLinePos , _nPos));
			_str.sprintf("%.0f", _nCurrentPos);
			painter.save();
			painter.translate(13 , _nPos - 2);
			painter.rotate(-90.0);
			painter.drawText(0 , 0 , _str );
			painter.restore();
			_str.clear();
		}
		else if(i%5 == 0)
		{
			painter.drawLine(QPointF(_nMidLineLeftPos , _nPos) , QPointF(_nBaseLinePos ,  _nPos));
		}
		else
		{
			painter.drawLine(QPointF(_nMinLineLeftPos , _nPos) , QPointF(_nBaseLinePos , _nPos));
		}
	}
	painter.drawLine(QPointF(_nBaseLinePos,  0 ) , QPointF(_nBaseLinePos , _nHeight));
	//***** draw ruler unit marker
	if(!m_strUnit.isEmpty())
	{
		painter.save();
		painter.translate(8 , _nHeight - 10);
		painter.rotate(-90.0);
		painter.drawText(0 , 0 , m_strUnit );
		painter.restore();
	}
}

void DopplerRulerBar::drawBottomRuler(QPainter& painter)
{
	//***** if start == end , do not draw anything
	if(m_nStart == m_nEnd)	 return ;

	//QPainter painter(this);
	double _nStart , _nStop , _nCurrentPos , _nRange;
	int i , _nStartIndex , _nPos , _nDirection ;
	int _nWidth = width();
	int _nMarkQty = getRulerMarkQty(_nWidth) ;
	_nRange = fabs(m_nStart - m_nEnd) ;
	double _nInterval = getRulerMarInterval(_nMarkQty , _nRange) ;
	double _nPixelPerUnit = _nWidth / _nRange ;

	int _nBaseLinePos =  g_nBaseLineOffset   ;
	int _nMinLineToptPos = _nBaseLinePos + g_nMinMarkerLength ;
	int _nMidLineToptPos = _nBaseLinePos + g_nMidMarkerLength ;
	int _nMaxLineTopPos  = _nBaseLinePos + g_nMaxMarkerLength ;


	if(m_nStart > m_nEnd)
	{
	   _nDirection = 1 ;
	   _nStart = m_nEnd ;
	   _nStop  = m_nStart ;
	}
	else
	{
	   _nDirection = 0 ;
	   _nStart = m_nStart ;
	   _nStop  = m_nEnd   ;
	}
	_nStartIndex = _nStart / _nInterval ;
	if(_nStart > 0)
	{
		_nStartIndex +=  1 ;
	}
	_nCurrentPos = _nStart  ;
	QString _str ;
	for(i = _nStartIndex ; _nCurrentPos < _nStop ; i++)
	{
		_nCurrentPos = i * _nInterval ;
		_nPos = (_nCurrentPos - _nStart) * _nPixelPerUnit ;
		if(_nDirection)
		{
		   _nPos  = _nWidth - _nPos - 1 ;
		}
		_nPos += 0.5 ;
		if(i % 10 == 0)
		{
			painter.drawLine(QPointF(_nPos + 0.5 , _nBaseLinePos) , QPointF(_nPos + 0.5 , _nMaxLineTopPos));
			_str.sprintf("%.0f", _nCurrentPos);
			painter.drawText( _nPos + 2 , 14 , _str );
			_str.clear();
		}
		else if(i%5 == 0)
		{
			painter.drawLine(QPointF( _nPos , _nBaseLinePos) , QPointF( _nPos , _nMidLineToptPos));
		}
		else
		{
			painter.drawLine(QPointF( _nPos , _nBaseLinePos) , QPointF( _nPos , _nMinLineToptPos));
		}
	}
	painter.drawLine(QPointF(0 ,  _nBaseLinePos ) , QPointF(_nWidth , _nBaseLinePos));
	//***** draw ruler unit marker
	if(!m_strUnit.isEmpty())
	{
		painter.drawText(10 , 19 , m_strUnit );
	}
}

void DopplerRulerBar::drawRightRuler(QPainter& painter)
{
	//***** if start == end , do not draw anything
	if(m_nStart == m_nEnd)	 return ;
	//QPainter painter(this);

	double _nStart , _nStop , _nCurrentPos , _nRange;
	int i , _nStartIndex , _nPos , _nDirection ;
	int _nHeight= height();

	int _nMarkQty = getRulerMarkQty(_nHeight) ;
	_nRange = fabs(m_nStart - m_nEnd) ;
	double _nInterval = getRulerMarInterval(_nMarkQty , _nRange) ;
	double _nPixelPerUnit = _nHeight / _nRange ;

	int _nBaseLinePos = g_nBaseLineOffset   ;
	int _nMinLineRightPos = _nBaseLinePos + g_nMinMarkerLength ;
	int _nMidLineRightPos  = _nBaseLinePos + g_nMidMarkerLength ;
	int _nMaxLineRightPos  = _nBaseLinePos + g_nMaxMarkerLength ;

	if(m_nStart > m_nEnd)
	{
	   _nDirection = 1 ;
	   _nStart = m_nEnd ;
	   _nStop  = m_nStart ;
	}
	else
	{
	   _nDirection = 0 ;
	   _nStart = m_nStart ;
	   _nStop  = m_nEnd   ;
	}
	_nStartIndex = _nStart / _nInterval ;
	if(_nStart > 0)
	{
		_nStartIndex +=  1 ;
	}
	_nCurrentPos = _nStart  ;
	QString _str ;
	for(i = _nStartIndex ; _nCurrentPos < _nStop ; i++)
	{
		_nCurrentPos = i * _nInterval ;
		_nPos = (_nCurrentPos - _nStart) * _nPixelPerUnit ;
		if(_nDirection)
		{
		   _nPos  = _nHeight - _nPos - 1 ;
		}
		_nPos += 0.5 ;
		if(i % 10 == 0)
		{
			painter.drawLine(QPointF(_nBaseLinePos , _nPos) , QPointF(_nMaxLineRightPos, _nPos));
			_str.sprintf("%.0f", _nCurrentPos);
			painter.save();
			painter.translate(14 , _nPos - 1);
			painter.rotate(-90.0);
			painter.drawText(0, 0 , _str );
			painter.restore();
			_str.clear();
		}
		else if(i%5 == 0)
		{
			painter.drawLine(QPointF(_nBaseLinePos ,_nPos) , QPointF(_nMidLineRightPos , _nPos));
		}
		else
		{
			painter.drawLine(QPointF(_nBaseLinePos , _nPos) , QPointF(_nMinLineRightPos , _nPos));
		}
	}
	painter.drawLine(QPointF(_nBaseLinePos,  0 ) , QPointF(_nBaseLinePos , _nHeight));
	//*****  draw ruler unit mark
	if(!m_strUnit.isEmpty())
	{
		painter.save();
		painter.translate(19 , _nHeight - 20);
		painter.rotate(-90.0);
		painter.drawText(0 , 0 , m_strUnit );
		painter.restore();
	}
}

void DopplerRulerBar::drawSlider(QPainter& painter)
{
	QPen _OldPen = painter.pen()  ;
	QPen _NewPen = _OldPen ;
	_NewPen.setColor(m_cSlider);
	painter.setPen(_NewPen);

	switch(m_eType)
	{
	case RULER_BAR_LEFT:
		drawLeftSlider(painter);
		break;
	case RULER_BAR_RIGHT:
		drawRightSlider(painter);
		break;
	case RULER_BAR_BOTTOM:
		drawBottomSlider(painter);
		break;
	case RULER_BAR_TOP:
		break;
	default:
		break;
	}
	painter.setPen(_OldPen);
}

void DopplerRulerBar::drawLeftSlider(QPainter& painter)
{
	float _x0 = m_rcSlider.x();
	float _y0 = m_rcSlider.y();
	float _width  = m_rcSlider.width();
	float _height = m_rcSlider.height();

	QRectF rect0(_x0+1, _y0,     _width-1, _height);
	QRectF rect1(_x0,   _y0 + 1, _width,   _height - 3);

	QBrush _brush(m_cSlider);
	painter.setBrush(_brush);
	painter.fillRect(rect0, _brush);
	painter.drawRect(rect1);
}

void DopplerRulerBar::drawRightSlider(QPainter& painter)
{
	float _x0 = m_rcSlider.x();
	float _y0 = m_rcSlider.y();
	float _width  = m_rcSlider.width();
	float _height = m_rcSlider.height();

	QRectF rect0(_x0+1, _y0,     _width, _height);
	QRectF rect1(_x0,   _y0 + 1, _width+1,   _height - 3);

	QBrush _brush(m_cSlider);
	painter.setBrush(_brush);
	painter.fillRect(rect0, _brush);
	painter.drawRect(rect1);
}

void DopplerRulerBar::drawBottomSlider(QPainter& painter)
{
	float _x0 = m_rcSlider.x();
	float _y0 = m_rcSlider.y();
	float _width  = m_rcSlider.width();
	float _height = m_rcSlider.height();

	QRectF rect0(_x0+1, _y0,     _width-1, _height+1);
	QRectF rect1(_x0,   _y0 + 1, _width,   _height-2);

	QBrush _brush(m_cSlider);
	painter.setBrush(_brush);
	painter.fillRect(rect0, _brush);
	painter.drawRect(rect1);
}

void DopplerRulerBar::enterEvent(QEvent* event)
{
    Q_UNUSED(event);
	QPoint _point =  this->mapFromGlobal(QCursor::pos());
	sliderDispPro(_point);
	update();
}

void DopplerRulerBar::leaveEvent(QEvent* event)
{
    Q_UNUSED(event);
	if(!m_bSliderDrag)
		m_bSliderON = false;
	update();
}
#include <MainWindow.h>
//extern MainWindow* g_pMainWnd = NULL;
void DopplerRulerBar::mouseMoveEvent(QMouseEvent* event)
{
	QPoint _point = event->pos();
	if(m_bSliderDrag) {
		SliderMovePro(_point);
	} else {
		sliderDispPro(_point);
		update();
	}
}

void DopplerRulerBar::mousePressEvent(QMouseEvent* event)
{
	QPoint _point = event->pos();
	sliderDispPro(_point);
	if(m_bSliderON) {
		if(m_rcSlider.contains(_point)) {
			m_bSliderDrag = true;
			m_ptDrag = _point;
			m_rcDrag = m_rcSlider;
		}
	}
	update();
}

void DopplerRulerBar::mouseReleaseEvent(QMouseEvent* event)
{
	QPoint _point = event->pos();
	sliderDispPro(_point);
	m_bSliderDrag = false;
	update();
}

void DopplerRulerBar::sliderDispPro(QPoint mousePos_)
{
	CalSliderArea();
	if(m_rcSlArea.contains(mousePos_)) {
		m_bSliderON = true;
	} else {
		m_bSliderON = false;
	}
}

void DopplerRulerBar::CalSliderArea()
{
	int _nWidth   = width();
	int _nHeight  = height();

	switch(m_eType)
	{
	case RULER_BAR_LEFT:
		{
			float _right = _nWidth - g_nBaseLineOffset - 3;
			float  _left = 3;//_right - g_nMaxMarkerLength;

			float _x0     = _left;
			float _y0     = 1;
			float _width  = _right - _left;
			float _height = _nHeight - 2;

			m_rcSlArea = QRectF(_x0, _y0, _width, _height);
		}
		break;
	case RULER_BAR_RIGHT:
		{
			float  _left = g_nBaseLineOffset + 2;
			float _right = _nWidth - 4;

			float _x0     = _left;
			float _y0     = 1;
			float _width  = _right - _left;
			float _height = _nHeight - 2;

			m_rcSlArea = QRectF(_x0, _y0, _width, _height);
		}
		break;
	case RULER_BAR_BOTTOM:
		{
			int _nWidth   = width();
			int _nHeight  = height();

			float    _top = g_nBaseLineOffset + 2;
			float _bottom = _nHeight - 4;

			float _x0     = 1;
			float _y0     = _top;
			float _width  = _nWidth - 2;
			float _height = _bottom - _top;

			m_rcSlArea = QRectF(_x0, _y0, _width, _height);
		}
		break;
	case RULER_BAR_TOP:
		break;
	default:
		break;
	}
}

void DopplerRulerBar::CalSliderRect()
{
	m_rcSlider = m_rcSlArea;
	double _fSliderRange = fabs(m_nSliderEnd - m_nSliderStart);
	double _fRange       = fabs(m_nEnd - m_nStart);

	if(_fRange >= _fSliderRange)
		return;

	double _fStart       = (m_nStart < m_nEnd) ? m_nStart : m_nEnd;
	double _fSliderStart = (m_nSliderStart < m_nSliderEnd) ? m_nSliderStart : m_nSliderEnd;
	double _fWidth       = m_rcSlArea.width();
	double _fHeight      = m_rcSlArea.height();

	switch(m_eType)
	{
	case RULER_BAR_RIGHT:
	case RULER_BAR_LEFT:
		{
			double  _fH = _fRange * _fHeight / _fSliderRange;
			if(_fH < g_nSliderCellMin)
				_fH = g_nSliderCellMin;

			_fSliderRange -= _fRange;
			_fStart       -= _fSliderStart;

			double _fS = _fStart * (_fHeight - _fH) / _fSliderRange;
			if(m_nStart < m_nEnd) {
				m_rcSlider.setTop(m_rcSlArea.top() + _fS);
				m_rcSlider.setHeight(_fH);
			} else {
				m_rcSlider.setTop(m_rcSlArea.top() - (_fS + _fH));
				m_rcSlider.setHeight(_fH);
			}
		}
		break;
	case RULER_BAR_BOTTOM:
		{
			float  _fW = _fRange * _fWidth / _fSliderRange;;
			if(_fW < g_nSliderCellMin)
				_fW = g_nSliderCellMin;

			_fSliderRange -= _fRange;
			_fStart       -= _fSliderStart;

			int _fS = _fStart * (_fWidth - _fW) / _fSliderRange;
			if(m_nStart < m_nEnd) {
				m_rcSlider.setLeft(m_rcSlArea.left() + _fS);
				m_rcSlider.setWidth(_fW);
			} else {
				m_rcSlider.setLeft(m_rcSlArea.top() - (_fS + _fW));
				m_rcSlider.setWidth(_fW);
			}
		}
		break;
	case RULER_BAR_TOP:
		break;
	default:
		break;
	}
}

void DopplerRulerBar::SliderMovePro(QPoint point_)
{
	double _fSliderRange = fabs(m_nSliderEnd - m_nSliderStart);
	double _fRange       = fabs(m_nEnd - m_nStart);

	double _fSliderStart = (m_nSliderStart < m_nSliderEnd) ? m_nSliderStart : m_nSliderEnd;
	double _fStart;
	double _fStop;

	QRectF rect = m_rcDrag;
	switch(m_eType)
	{
	case RULER_BAR_RIGHT:
	case RULER_BAR_LEFT:
		{
			double _fH = rect.height();
			double _fD = point_.y() - m_ptDrag.y();

			double _top    = rect.top();
			double _bottom = rect.bottom();

			_top    += _fD;
			_bottom += _fD;
			if(_top < m_rcSlArea.top()) {
				_top    = m_rcSlArea.top();
				_bottom = _top + _fH;
			} else if(_bottom > m_rcSlArea.bottom()) {
				_bottom = m_rcSlArea.bottom();
				_top    = _bottom - _fH;
			}

			double _fHeight = m_rcSlArea.height();
			_fSliderRange -= _fRange;
			if(m_nStart < m_nEnd) {
				_fStart = _fSliderStart + _fSliderRange * fabs(_top - m_rcSlArea.top()) / (_fHeight - _fH);
				_fStop  = _fStart + _fRange;
			} else {
				_fStart = _fSliderStart + _fSliderRange * fabs(_bottom - m_rcSlArea.bottom()) / (_fHeight - _fH);
				_fStop  = _fStart + _fRange;
			}
			m_nStart = _fStart;
			m_nEnd   = _fStop;
		}
		break;
	case RULER_BAR_BOTTOM:
		{
			double _fW = rect.width();
			double _fD = point_.x() - m_ptDrag.x();

			double _left  = rect.left();
			double _right = rect.right();

			_left  += _fD;
			_right += _fD;
			if(_left < m_rcSlArea.left()) {
				_left  = m_rcSlArea.left();
				_right = _left + _fW;
			} else if(_right > m_rcSlArea.right()) {
				_right = m_rcSlArea.right();
				_left  = _right - _fW;
			}

			double _fWidth = m_rcSlArea.width();
			_fSliderRange -= _fRange;
			if(m_nStart < m_nEnd) {
				_fStart = _fSliderStart + _fSliderRange * fabs(_left - m_rcSlArea.left()) / (_fWidth - _fW);
				_fStop  = _fStart + _fRange;
			} else {
				_fStart = _fSliderStart + _fSliderRange * fabs(_right - m_rcSlArea.right()) / (_fWidth - _fW);
				_fStop  = _fStart + _fRange;
			}
			m_nStart = _fStart;
			m_nEnd   = _fStop;
		}
		break;
	case RULER_BAR_TOP:
		return;
	default:
		return;
	}

	emit signalRulerMoved(m_nStart, m_nEnd);
}

