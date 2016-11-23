#include "DopplerParabolaItem.h"
#include <QPainterPath>
#include <QPen>
#include <QPainter>
#include <configure/DopplerConfigure.h>
#include <math.h>

const int g_nParabolaWidth = 10 ;
DopplerParabolaItem::DopplerParabolaItem()
{
	setFlags(ItemIsPanel );
	setZValue(100);
	m_cColor = QColor(0 , 0 , 255);
	m_nDisp   = 0	  ;
	m_nGroup  = 0	 ;
}

void DopplerParabolaItem::SetPoint(QPointF pos_)
{
	m_cPos = pos_ ;
}

QRectF DopplerParabolaItem::boundingRect() const
{

	QRectF _rect = QRectF(0, 0 , 0  , 0);
	return _rect ;
}

QPainterPath DopplerParabolaItem::shape() const
{
	QPainterPath path;
	QRectF   _rct = boundingRect () ;
	path.addRect(_rct) ;
	return path;
}
#include "../process/ParameterProcess.h"
const int FITTED_CURVE_LEN_MAX = 101;
void DopplerParabolaItem::paint (QPainter *painter, const QStyleOptionGraphicsItem* , QWidget* )
{
	if(!m_pDataView)  return ;
	int _nLaw ;
	m_pDataView->GetDataViewConfigure(&m_nGroup , &_nLaw , &m_nDisp);

	ParameterProcess* _process = ParameterProcess::Instance();

	float _fPrecX;
	float _fPrecY;
	float _fTX0;
	int   _iDots = 10;
	GetPrecInfo(&_fPrecX, &_fPrecY, &_fTX0);

	QPointF _ptFittedCurve[FITTED_CURVE_LEN_MAX];
	_process->FittedCurveGetPoints(m_nGroup, _fPrecX, _fPrecY, _fTX0,  _iDots, _ptFittedCurve);

	if(m_nDisp == setup_DISPLAY_MODE_B_V )
	{
		int _x, _y;
		for(int i = 0; i < 2*_iDots+1; i++)
		{
			_x = _ptFittedCurve[i].x();
			_y = _ptFittedCurve[i].y();
			_ptFittedCurve[i].setX(_y);
			_ptFittedCurve[i].setY(_x);
		}
	}

	QPen _pen = painter->pen();
	_pen.setColor(m_cColor);
	painter->setPen(_pen);
	for(int i = 0 ; i < 2*_iDots ; i ++) {
		painter->drawLine(_ptFittedCurve[i] , _ptFittedCurve[i+1]);
	}
}

void DopplerParabolaItem::GetPrecInfo(float* precX_, float* precY_, float* pTX0_)
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	GROUP_CONFIG*	   _pGroup = &_pConfig->group[m_nGroup]  ;
	QSize		   _sizeWidget = m_pDataView->GetViewSize() ;
	float				    _C = _pGroup->fVelocity / 1000.0f;
	float		    _fZeroTime = (float)((double)_pGroup->nWedgeDelay / 1000.0);

	if(m_nDisp == setup_DISPLAY_MODE_B_H )
	{
		*precX_ = _pGroup->fSampleRange / _C / _sizeWidget.width() ;
		*precY_ = _pConfig->common.scanner.fScanStep;
		*pTX0_  = m_cPos.x()/_C + _fZeroTime;
	}
	else if(m_nDisp == setup_DISPLAY_MODE_B_V )
	{
		*precX_ = _pGroup->fSampleRange / _C / _sizeWidget.height() ;
		*precY_ = _pConfig->common.scanner.fScanStep;
		*pTX0_  = m_cPos.y()/_C + _fZeroTime;
	}
}
