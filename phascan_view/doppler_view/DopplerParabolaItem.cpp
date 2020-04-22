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
    m_scaleH  = 1;
    m_scaleV  = 1;
}

void DopplerParabolaItem::SetPoint(QPointF pos_)
{
	m_cPos = pos_ ;
}

void DopplerParabolaItem::Set_Scale(float scaleH, float scaleV)
{
    m_scaleH  = scaleH;
    m_scaleV  = scaleV;
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
const int FITTED_CURVE_LEN_MAX = 41;
void DopplerParabolaItem::paint (QPainter *painter, const QStyleOptionGraphicsItem* , QWidget* )
{
	if(!m_pDataView)  return ;
	int _nLaw ;
	m_pDataView->GetDataViewConfigure(&m_nGroup , &_nLaw , &m_nDisp);

	ParameterProcess* _process = ParameterProcess::Instance();

	float _fPrecX;
	float _fPrecY;
	float _fTX0;
    int   _iDots = 20;
	GetPrecInfo(&_fPrecX, &_fPrecY, &_fTX0);

    QPointF _ptFittedCurve[FITTED_CURVE_LEN_MAX];
//    if(m_nDisp == setup_DISPLAY_MODE_B_V ){
        //_process->FittedCurveGetPoints(m_nGroup, _fPrecX, _fPrecY, _fTX0,  _iDots, m_scaleH, m_scaleV, _ptFittedCurve);
//    }else{

//    }
    update_parabola_points(m_nGroup, _ptFittedCurve);

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
        *precX_ = _pGroup->fSampleRange / _C / _sizeWidget.width();
        *precY_ = _pConfig->common.scanner.fScanStep;
		*pTX0_  = m_cPos.x()/_C + _fZeroTime;
	}
	else if(m_nDisp == setup_DISPLAY_MODE_B_V )
	{
        *precX_ = _pGroup->fSampleRange / _C / _sizeWidget.height();
        *precY_ = _pConfig->common.scanner.fScanStep;
		*pTX0_  = m_cPos.y()/_C + _fZeroTime;
	}
}

void DopplerParabolaItem::update_parabola_points( int nGroupId_, QPointF* pPoints_)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _process->CalculateTofdPcs(nGroupId_);
    QSize _sizeWidget = m_pDataView->GetViewSize();
    GROUP_CONFIG& group = _pConfig->group[nGroupId_];
    COMMON_CONFIG& _common = _pConfig->common;


    TOFD_PARA* _pTofd = _pConfig->GetTofdConfig( nGroupId_);
    double pcs = _pTofd->fPCS;
    double utCursorPos, utRatio, scanRatio;
    double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop;
    if(m_nDisp == setup_DISPLAY_MODE_B_H ){
        utCursorPos = m_cPos.x();
        utRatio = _sizeWidget.width() / ( group.fSampleRange);
        m_pDataView->GetRulerRange(&_fScanStart, &_fScanStop, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
        if(_common.scanner.eScanEncoderType == setup_ENCODER_TYPE_TIMER){
            scanRatio = _sizeWidget.height() / (abs(_fScanStop - _fScanStart)* _common.scanner.fPrf);
        }else{
            scanRatio = _sizeWidget.height() / abs(_fScanStop - _fScanStart);
        }
    }else{
        utCursorPos = m_cPos.y();
        utRatio = _sizeWidget.height() / ( group.fSampleRange);
        m_pDataView->GetRulerRange(&_fScanStart, &_fScanStop, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
        if(_common.scanner.eScanEncoderType == setup_ENCODER_TYPE_TIMER){
            scanRatio = _sizeWidget.width() / (abs(_fScanStop - _fScanStart)* _common.scanner.fPrf);
        }else{
            scanRatio = _sizeWidget.width() / abs(_fScanStop - _fScanStart);
        }
    }

    float _C = group.fVelocity / 1000.0f;
    if(group.eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
        utCursorPos *= 2;
    }else{
        utCursorPos *= _C;
    }

    if ( utCursorPos <= pcs) {
            return;
    }

    double scanPos = 0.0;
    double utPos = 0.0;
    const int halfPointsCount = 20;
    const double pointRes = 1.0;
    for (int i = 0; i <= halfPointsCount; ++i) {
        scanPos = i * pointRes;
        utPos = sqrt( pow(utCursorPos / 2, 2) + pow(scanPos, 2));
        utPos -= (group.fSampleStart);
        double x = utPos * utRatio*m_scaleH;
        double y = scanPos * scanRatio;
        pPoints_[i+20].setX(x);
        pPoints_[i+20].setY(y);
        pPoints_[20-i].setX(x);
        pPoints_[20-i].setY(-y);
    }
    double offset = pPoints_[20].x();
    for(int i = 0; i < 41; i++){
        double x = pPoints_[i].x() - offset;
        pPoints_[i].setX(x);
    }
}
