#include "DopplerDrawAScan.h"
#include <process/ParameterProcess.h>
#include <QPainter>
#include <math.h>
double RL_EL_SL[5]={0};
extern int Phascan_Version;

WDATA setPdata( WDATA data)
{
    if(Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6)
    {
        return data;
    }
    else
    {
        int _data = (int)data * 2 | 1;
        if( _data > WAVE_MAX)
        {
            return WAVE_MAX;
        }
        else
        {
            return (WDATA)_data;
        }
    }
}

DopplerDrawAScanH::DopplerDrawAScanH():DopplerDrawScan()
{
	bDrawLimit = 0 ;
	Lines.clear();
	LimitHigh.clear() ;
	LimitLow.clear()  ;

	for(int i = 0; i < CURVES_CNT; i++)
	{
		m_linCurves[i].clear();
		m_iPtCnt[i] = 0;
	}
	m_dashes << 3 << 1 << 3 << 1 ;

	color[0] = QColor(255 , 255 , 0) ;
	color[1] = QColor(0   , 255 , 128) ;
	color[2] = QColor(0   , 128 , 255) ;
}

void DopplerDrawAScanH::UpdateDrawInfo()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	m_AScanInfo.nPointQty  = _process->GetGroupPointQty(m_cInfo.nGroupId) ;
	//------
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	SYSTEM_ENVIRMENT&  _appEvn = _pConfig->AppEvn;

	m_AScanInfo.fDRangeS = -1;
	if(_appEvn.bTrueDepth_A_S_Sync) {
		GROUP_CONFIG& _group = _pConfig->group[m_cInfo.nGroupId] ;
		if(_group.eTravelMode == setup_TRAVEL_MODE_TRUE_DEPTH) {
			float _fS, _fE;
			_process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fS ,  &_fE);
			m_AScanInfo.fDRangeS        = _fE - _fS;
		}
	}
	//------
}

void DopplerDrawAScanH::Draw(QImage* pImage_)
{
	if(!pImage_)  return ;
    unsigned char* Image_pData = pImage_->bits() ;
    memset(Image_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	ParameterProcess* _process = ParameterProcess::Instance();
    WDATA* _pData = _process->GetLawDataPointer( m_cInfo.nGroupId, m_cInfo.nBeamId);
    if (_pConfig->group[m_cInfo.nGroupId].coupleMonitoringState && _pConfig->group[m_cInfo.nGroupId].bShowCoupleInAScan) {
        DrawCoupleCurve(pImage_);
        return;
    }
	if(!_pData)  return ;

	int  _nPointQty = m_AScanInfo.nPointQty ;
	m_nWidth  = pImage_->width();
	m_nHeight = pImage_->height();
	double _nHeight = (double)m_nHeight;
	double  _nWidth = (double)m_nWidth ;

    QPainter painter(pImage_) ;
    ClearAll(&painter);

	//int _nScanPos = _process->GetScanIndexPos();
	//U8*  _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	//if(!_pMarker[_nScanPos])
		//return ;
    float  _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	double _fX , _fY;
    double _fXRatio = _nWidth / (_nPointQty - 1);
	double _fYRatio = _nHeight / 255  ;
	//---------------
    if(m_AScanInfo.fDRangeS > 0){
		ParameterProcess* _process = ParameterProcess::Instance();
		double _fCurDepthRange = _process->GetSampleRange(m_cInfo.nGroupId, m_cInfo.nBeamId) ;
		_nWidth = _nWidth * _fCurDepthRange / m_AScanInfo.fDRangeS;
        _fXRatio = _nWidth / (_nPointQty -1);

    }
	//---------------
    float _nStart = _process->GetSampleStart(m_cInfo.nGroupId,m_cInfo.nBeamId);
    float _fS, _fE;
    float start;
    if(0 == _process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fS ,  &_fE))
    {
     start = (float)m_nWidth * (_nStart - _fS) / m_AScanInfo.fDRangeS;
    }
    else
    start = 0;
    if(_process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_HALF_PATH ||
            _process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_TIME){
        start = 0;
    }


    int _nFrameOffset = _process->GetTotalDataSize() ;//一帧数据偏移量
    int cursorOffset=1;
    if(m_pGroup->m_mode==D_MODE)
      {
        cursorOffset=m_pGroup->afCursor[ setup_CURSOR_S_MES ]- m_pGroup->afCursor[setup_CURSOR_S_REF];
        if(cursorOffset<0)cursorOffset=-cursorOffset;
        if(cursorOffset==0)cursorOffset=1;

      }

    int i,j;
    double _tempfY=0.0;
     WDATA* _tempData= _pData;

    for(i = 0 ; i < _nPointQty ; i++)
    {
        _fX = i * _fXRatio +start;
        _tempfY=0.0;
        for(j=0;j<cursorOffset;j++)
        {
             _pData= _tempData+j*_nFrameOffset;
             _fY = _process->GetRefGainScaleData(_pData[i], _fScale, _bRectify);
             if(_fY>_tempfY)
             {
               _tempfY=_fY;
             }
        }

        _fY = _nHeight -_tempfY * _fYRatio;
        Lines<<QPointF(_fX , _fY);
    }


    QPen NewPen(color[0]);
    NewPen.setWidth( 0);
    painter.setPen(NewPen);
    painter.drawPolyline(Lines);

	if(bDrawLimit)
	{
		for(i = 0 ; i < _nPointQty ; i++)
		{
            WDATA buff = setPdata(_pData[i]);
            if( buff > aLimitHigh[i]) aLimitHigh[i] = buff;
            if( buff < aLimitLow [i]) aLimitLow [i] = buff;
		}

		double _fY1;
		for(i = 0 ; i < _nPointQty  ; i++)
		{
			_fX  = i * _fXRatio ;
            _fY  = _nHeight - aLimitHigh[i] * _fYRatio;
            _fY1 = _nHeight - aLimitLow[i] * _fYRatio;
			LimitHigh<<QPointF(_fX , _fY);
			LimitLow<<QPointF(_fX , _fY1);
		}
        QPen _NewPen(color[0]);
        _NewPen.setWidth( 0);
        painter.setPen( _NewPen);
		painter.drawPolyline(LimitHigh);
		painter.drawPolyline(LimitLow);
	}

    if(m_pGroup->bShowCurve) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_DAC);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_DAC);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_TCG,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_TCG,0);
            break;
        default:
            break;
        }
    }
    if(CUR_RES.bShowRL) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_RL);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_RL);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_RL,1);
            break;
        default:
            break;
        }
    }
    else {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_RL,0);
            break;
        default:
            break;
        }
    }
    if(CUR_RES.bShowEL) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_EL);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_EL);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_EL,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_EL,0);
            break;
        default:
            break;
        }
    }
    if(CUR_RES.bShowSL) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_SL);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_SL);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_SL,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_SL,0);
            break;
        default:
            break;
        }
    }
}

void DopplerDrawAScanH::SetColor(QColor* pColor_ , A_SCAN_LINE_TYPE eLineType_ )
{
	if(eLineType_ >= A_SCAN_LINE_TYPE_MAX)  return  ;
	color[eLineType_]  = *pColor_  ;
}

void DopplerDrawAScanH::EndAbleLineDrawing(A_SCAN_LINE_TYPE eLineType_ , bool enalbe_ )
{
	if(eLineType_ == A_SCAN_DRAW_LIMIT)
	{
		bDrawLimit = enalbe_  ;
		if(enalbe_)
		{
			bDrawLimit = false;
			memset((void*) aLimitHigh , 0 , A_SCAN_LIMIT_BUFF_SIZE) ;
			memset((void*) aLimitLow  , 0 , A_SCAN_LIMIT_BUFF_SIZE) ;
		}
	}
}

void DopplerDrawAScanH::DrawDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode)
{
	CURVES& _curve = m_pGroup->curve;

	int _nWidth  = nWidth_;
	int _nHeight = nHeight_;

	int   _nBeamNo = m_cInfo.nBeamId;
	float _fTStart = m_pGroup->nTimeStart / 1000.0f;
	float _fTRange = m_pGroup->nTimeRange / 1000.0f;
	int _nPointQty = _curve.nPointQty;
	int _nPointPos = _curve.nPointPos;

	float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);

	float _ptX[18] ;
	float _ptY[18] ;

	memset(_ptX, 0x00, sizeof(_ptX));
	memset(_ptY, 0x00, sizeof(_ptY));

	float _nStepRate[5];

	_nStepRate[0] = 1;
    _nStepRate[1] = pow(10.0, (CUR_RES.CurRL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[2] = pow(10.0, (CUR_RES.CurEL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[3] = pow(10.0, (CUR_RES.CurSL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
	_nStepRate[4] = 1 / _nStepRate[2];

	//------------------------------------------
	_ptX[0] = 0;
	_ptY[0] = _nHeight * _curve.faAmpRef[_nBeamNo] * _fRefAmpOff;

	for(int i = 1; i < _nPointQty+1; i++) {
		_ptX[i] = _nWidth * (_curve.faPosition[_nBeamNo][i - 1] - _fTStart) / _fTRange;
		_ptY[i] = _fRefAmpOff * _nHeight * _curve.faAmp[_nBeamNo][i - 1] / 100.0f;
	}
	_ptX[_nPointQty+1] = m_nWidth;
	_ptY[_nPointQty+1] = _ptY[_nPointQty];


		for(int i = 0; i <= _nPointQty+1; i++) {
            m_linCurves[mode]<<QPointF(_ptX[i], _nHeight - _nStepRate[mode] * _ptY[i]) ;
		}

	//------------------------------------------
        //------------------------------------------
        QColor _Color ;
        if(mode == setup_DAC)
        {
            _Color = QColor(0, 100, 0);
        }
        else if(mode == setup_RL)
        {
            _Color = QColor(255, 0, 0);
        }
        else if(mode == setup_EL)
        {
            _Color = QColor(0, 0, 255);
        }
        else if(mode == setup_SL)
        {
            _Color = QColor(125, 125, 125);
        }
	QPen _NewPen ;

	_NewPen.setColor(_Color);
	_NewPen.setDashPattern(m_dashes);
	painter->setPen(_NewPen);


        painter->drawPolyline(m_linCurves[mode]);

	//------------------------------------------
	m_iPtCnt[0] = _nPointQty;
    if(mode == setup_DAC)
    {
	for(int i = 0; i < _nPointQty; i++)
	{
		m_ptPos[0][i].setX(_ptX[i+1]);
		m_ptPos[0][i].setY(_nHeight - _ptY[i+1]);
		if(i == _nPointPos) {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 0 , 0));
		} else {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 200 , 200));
		}
	}
    }
	//------------------------------------------
}

void DopplerDrawAScanH::DrawLinearDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode)
{
	CURVES& _curve = m_pGroup->curve;

	int _nWidth  = nWidth_;
	int _nHeight = nHeight_;

	float _fTStart = m_pGroup->nTimeStart / 1000.0f;
	float _fTRange = m_pGroup->nTimeRange / 1000.0f;
	int _nPointQty = 10;

	float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);

	float _ptX[18] ;
	float _ptY[18] ;

	memset(_ptX, 0x00, sizeof(_ptX));
	memset(_ptY, 0x00, sizeof(_ptY));

	float _nStepRate[5];
	_nStepRate[0] = 1;
    _nStepRate[1] = pow(10.0, (CUR_RES.CurRL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[2] = pow(10.0, (CUR_RES.CurEL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[3] = pow(10.0, (CUR_RES.CurSL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
	_nStepRate[4] = 1 / _nStepRate[2];
	//------------------------------------------
	_ptX[0] = 0;
	_ptY[0] = _nHeight * _curve.fAmpOffsetLinear * _fRefAmpOff;

	for(int i = 1; i < _nPointQty + 1; i++)
	{
		_ptX[i] = _nWidth * (_curve.faAmpPosition[i - 1] - _fTStart) / _fTRange;
		_ptY[i] = _fRefAmpOff * _nHeight * _curve.faAmpLinear[i - 1] / 100.0f;
	}
	_ptX[_nPointQty+1] = m_nWidth;
	_ptY[_nPointQty+1] = _ptY[_nPointQty];



		for(int i = 0; i <= _nPointQty+1; i++)
		{
            m_linCurves[mode]<<QPointF(_ptX[i], _nHeight - _nStepRate[mode] * _ptY[i]) ;
		}

	//------------------------------------------
        QColor _Color ;
        if(mode == setup_DAC)
        {
            _Color = QColor(0, 100, 0);
        }
        else if(mode == setup_RL)
        {
            _Color = QColor(255, 0, 0);
        }
        else if(mode == setup_EL)
        {
            _Color = QColor(0, 0, 255);
        }
        else if(mode == setup_SL)
        {
            _Color = QColor(125, 125, 125);
        }
	QPen _NewPen ;

	_NewPen.setColor(_Color);
	_NewPen.setDashPattern(m_dashes);
	painter->setPen(_NewPen);


        painter->drawPolyline(m_linCurves[mode]);

	//------------------------------------------
}
#include <qdebug.h>
void DopplerDrawAScanH::DrawTcgCurve(QPainter *painter, int nWidth_, int nHeight_,int mode,int flag)
{
	CURVES& _curve = m_pGroup->curve;

	int _nWidth  = nWidth_;
	int _nHeight = nHeight_;

	int   _nBeamNo = m_cInfo.nBeamId;
	float _fTStart = m_pGroup->nTimeStart / 1000.0f;
	float _fTRange = m_pGroup->nTimeRange / 1000.0f;
	int _nPointQty = _curve.nPointQty;
	int _nPointPos = _curve.nPointPos;

	float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);

	float _ptX[18] ;
	float _ptY[18] ;
    QColor _Color ;
    QString str;
    if(mode == setup_TCG)
    {
        _Color = QColor(0, 100, 0);
        str = "TCG";
    }
    else if(mode == setup_RL)
    {
        _Color = QColor(255, 0, 0);
        str = "RL";
    }
    else if(mode == setup_EL)
    {
        _Color = QColor(125, 125, 125);
        str = "EL";
    }
    else if(mode == setup_SL)
    {
        _Color = QColor(0, 0, 255);
        str = "SL";
    }
    QPen _NewPen ;

    _NewPen.setColor(_Color);
    _NewPen.setDashPattern(m_dashes);
    painter->setPen(_NewPen);
    if(mode == setup_TCG)
    {
        if(flag == 0)
            return;
	memset(_ptX, 0x00, sizeof(_ptX));
	memset(_ptY, 0x00, sizeof(_ptY));
	//------------------------------------------
	_ptX[0] = 0;
	_ptY[0] = _fRefAmpOff * _nHeight * _curve.faAmpRef[_nBeamNo];
	for(int i = 1; i < _nPointQty+1; i++ )
	{
		_ptX[i] = _nWidth * (_curve.faPosition[_nBeamNo][i-1] - _fTStart) / _fTRange;
		_ptY[i] = _fRefAmpOff * _nHeight * (_curve.faAmp[_nBeamNo][i-1] / 100.0f);
	}
	_ptX[_nPointQty+1] = m_nWidth;
	_ptY[_nPointQty+1] = _ptY[_nPointQty];

	for(int i = _nPointQty+1; i >= 0 ; i--)
	{
		_ptY[i] = _nHeight - fabs(_ptY[i] - _ptY[0]);
	}
	//**************************************************************



	//------------------------------------------
	for(int i = 0; i <= _nPointQty+1 ; i++)
	{
        m_linCurves[mode]<<QPointF(_ptX[i] , _ptY[i]) ;
	}
    painter->drawPolyline(m_linCurves[mode]);
    painter->drawText(nWidth_,_ptY[_nPointQty+1],str);
	//------------------------------------------
	m_iPtCnt[0] = _nPointQty;
	for(int i = 0; i < _nPointQty; i++)
	{
		m_ptPos[0][i].setX(_ptX[i+1]);
		m_ptPos[0][i].setY(_ptY[i+1]);
		if(i == _nPointPos) {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 0 , 0));
		} else {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 200 , 200));
		}
	}
    }
    else
    {
        float midx,midy;
        midx = pow(10.0,(CUR_RES.REF_Gain[m_cInfo.nGroupId])/20.0);
        midx = midx * 0.8;
        if(mode == setup_RL)
        {
            midy = pow(10.0,(CUR_RES.CurRL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
            midy = midx * midy;
        }
        else if(mode == setup_EL)
        {
            midy = pow(10.0,(CUR_RES.CurEL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
            midy = midx * midy;
        }
        else if(mode == setup_SL)
        {
            midy = pow(10.0,(CUR_RES.CurSL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
            midy = midx * midy;
        }
        m_linCurves[mode]<<QPointF(0 ,(1 - midy) * m_nHeight) ;
        m_linCurves[mode]<<QPointF(m_nWidth , (1 -midy) * m_nHeight) ;
        RL_EL_SL[mode] = midy;
        if(flag)
        {
            painter->drawPolyline(m_linCurves[mode]);
            painter->drawText(nWidth_,(1 -midy) * m_nHeight,str);
        }

    }
    //------------------------------------------
}

void DopplerDrawAScanH::DrawCoupleCurve(QImage* pImage_)
{
    ParameterProcess* _process = ParameterProcess::Instance();
//    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    WDATA*              _pData = _process->GetCoupleDataPointer(m_cInfo.nGroupId);
    float coupleStart = m_pConfig->group[m_cInfo.nGroupId].coupleMonitoringVelocity * m_pConfig->group[m_cInfo.nGroupId].nTimeStart/2000000.0;
    float coupleDepth = m_pConfig->group[m_cInfo.nGroupId].coupleMonitoringVelocity * m_pConfig->group[m_cInfo.nGroupId].nTimeRange/2000000.0;
    if(coupleDepth <= 0)
    {
        return;
    }
    int  _nPointQty = m_AScanInfo.nPointQty ;
    m_nWidth  = pImage_->width();
    m_nHeight = pImage_->height();
    double _nHeight = (double)m_nHeight;
    double  _nWidth = (double)m_nWidth ;

    QPainter painter(pImage_) ;

    ClearAll(&painter);

    float  _fScale =  pow(10.0,CUR_RES.Couple_Com_Gain[m_cInfo.nGroupId]/20.0);
    bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

    double _fX , _fY;
    double _fXRatio = _nWidth / (_nPointQty -1)  ;
    double _fYRatio = _nHeight / 255;
    //---------------
    float _fS, _fE;
    int start = 0;
    float maxDepth = 0.0;
    int loopQty = 0;
    if(0 ==_process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fS ,  &_fE))
    {
        maxDepth = _fE - _fS;
        if( maxDepth <= 0 || coupleStart + coupleDepth < _fS || coupleStart > _fE){
            return;
        }
        //开始处截断
        if( _fS > coupleStart){
            start = ( _fS - coupleStart ) / coupleDepth * _nPointQty;
            coupleDepth = coupleDepth - ( _fS - coupleStart);
        } else {
            start = ( coupleStart - _fS) / maxDepth * _nWidth;
            _nWidth -= start;
            maxDepth = maxDepth - ( coupleStart - _fS);
        }

        //尾部截断
        if( maxDepth > coupleDepth){
            loopQty = _nPointQty;
            _nWidth = coupleDepth / maxDepth * _nWidth;
        } else {
            loopQty  = _nPointQty * maxDepth / coupleDepth;
        }
    }

    if(_process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_HALF_PATH ||
            _process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_TIME){
        start = 0;
    }
    //---------------
    _fXRatio = _nWidth / (loopQty - 1) ;

    int i  ;
    for(i = 0 ; i < loopQty ; i++)
    {
        _fX = i * _fXRatio + start;
        _fY = _process->GetRefGainScaleData(_pData[i], _fScale, _bRectify);
        _fY = _nHeight - _fY * _fYRatio ;

        Lines<<QPointF(_fX , _fY) ;
    }
    painter.setPen(QPen(color[0]));
    painter.drawPolyline(Lines);
}

void DopplerDrawAScanH::DrawPointRectangle(QPainter *painter_, float x_, float y_, QColor color_)
{
	const int HWIDTH = 3;
	QBrush _brush(color_);//(QColor(130,130,130) );
	QRectF _rect;

	_rect.setLeft(x_ - HWIDTH);
	_rect.setTop(y_ - HWIDTH);
	_rect.setRight(x_ + HWIDTH);
	_rect.setBottom(y_ + HWIDTH);

	painter_->fillRect(_rect, _brush);
}

WDATA* DopplerDrawAScanH::GetLimitValueHigh()
{
	return aLimitHigh  ;
}

WDATA* DopplerDrawAScanH::GetLimitValueLow()
{
	return aLimitLow;
}

void DopplerDrawAScanH::ClearAll(QPainter *painter)
{
	QPen pen ;
	pen.setWidth(0);
	painter->setPen(QPen(Qt::black));

	painter->drawPolyline(Lines);
	Lines.clear();

	painter->drawPolyline(LimitHigh);
	LimitHigh.clear();

	painter->drawPolyline(LimitLow);
	LimitLow.clear();

	for(int i = 0; i < CURVES_CNT; i++)
	{
		painter->drawPolyline(m_linCurves[i]);
		m_linCurves[i].clear();

		for(int k = 0; k < m_iPtCnt[i]; k++)
		{
			DrawPointRectangle(painter, m_ptPos[0][k].x() , m_ptPos[0][k].y(), QColor(0 , 0 , 0));
		}
		m_iPtCnt[i] = 0;
	}

}
//********************************************************************************************************************
//********************************************************************************************************************
DopplerDrawAScanV::DopplerDrawAScanV():DopplerDrawAScanH()
{
}

void DopplerDrawAScanV::Draw (QImage* pImage_)
{
	if(!pImage_)  return ;
    unsigned char* Image_pData = pImage_->bits() ;
    memset(Image_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
	ParameterProcess* _process = ParameterProcess::Instance();
    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    WDATA*			  _pData = _process->GetLawDataPointer(m_cInfo.nGroupId , m_cInfo.nBeamId)  ;
    if (_pConfig->group[m_cInfo.nGroupId].coupleMonitoringState && _pConfig->group[m_cInfo.nGroupId].bShowCoupleInAScan) {
        DrawCoupleCurve(pImage_);
        return;
    }
	if(!_pData)  return ;

	int  _nPointQty = m_AScanInfo.nPointQty ;
	m_nWidth  = pImage_->width();
	m_nHeight = pImage_->height();
	double _nHeight = (double)m_nHeight;
	double  _nWidth = (double)m_nWidth ;

	QPainter painter(pImage_) ;

	ClearAll(&painter);

	//int _nScanPos = _process->GetScanIndexPos();
	//U8*  _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	//if(!_pMarker[_nScanPos])
	//	return ;

	float  _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	double _fX , _fY;
	double _fXRatio = _nWidth / 255  ;
	double _fYRatio = _nHeight / (_nPointQty -1) ;
	//---------------
	if(m_AScanInfo.fDRangeS > 0) {
		ParameterProcess* _process = ParameterProcess::Instance();
		double _fCurDepthRange = _process->GetSampleRange(m_cInfo.nGroupId, m_cInfo.nBeamId) ;
		_nHeight = _nHeight * _fCurDepthRange / m_AScanInfo.fDRangeS;
		_fYRatio = _nHeight / (_nPointQty -1) ;
	}
	//---------------
    float _nStart = _process->GetSampleStart(m_cInfo.nGroupId,m_cInfo.nBeamId);
    float _fS, _fE;
    float start;
    if(0 ==_process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fS ,  &_fE))
    {
     start = (float)m_nHeight*(_nStart - _fS) / m_AScanInfo.fDRangeS;
    }
    else
        start =0;

    if(_process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_HALF_PATH ||
            _process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_TIME){
        start = 0;
    }


//    int i  ;
//	for(i = 0 ; i < _nPointQty  ; i++)
//	{
//        _fY = i * _fYRatio + start;
//		_fX = _process->GetRefGainScaleData(_pData[i], _fScale, _bRectify);
//		_fX = _fX * _fXRatio ;

//		Lines<<QPointF(_fX , _fY) ;
//	}

    int _nFrameOffset = _process->GetTotalDataSize() ;//一帧数据偏移量
    int cursorOffset=1;

    if(m_pGroup->m_mode==D_MODE&&m_pGroup->afCursor[ setup_CURSOR_S_MES ]<m_pConfig->comTmp.nRecMax&&m_pGroup->afCursor[setup_CURSOR_S_REF]<m_pConfig->comTmp.nRecMax)
      {
        cursorOffset=m_pGroup->afCursor[ setup_CURSOR_S_MES ]- m_pGroup->afCursor[setup_CURSOR_S_REF];
        if(cursorOffset<0)cursorOffset=-cursorOffset;
        if(cursorOffset==0)cursorOffset=1;

      }

    int i,j;
    double _tempfX=0.0;
    WDATA* _tempData= _pData;

    for(i = 0 ; i < _nPointQty ; i++)
    {
        _fY = i * _fYRatio + start;
        _tempfX=0.0;
        for(j=0;j<cursorOffset;j++)
        {
             _pData= _tempData+j*_nFrameOffset;
             _fX = _process->GetRefGainScaleData(_pData[i], _fScale, _bRectify);
             if(_fX>_tempfX)
             {
               _tempfX=_fX;
             }
        }

        _fX = _tempfX * _fXRatio;
        Lines<<QPointF(_fX , _fY);
    }


	painter.setPen(QPen(color[0]));
	painter.drawPolyline(Lines);
    //qDebug()<<"Adata"<<_nPointQty<<_nHeight<<_nWidth;

	if(bDrawLimit)
	{
		for(i = 0 ; i < _nPointQty ; i++)
		{
            WDATA buff = setPdata(_pData[i]);
            if( buff > aLimitHigh[i]) aLimitHigh[i] = buff;
            if( buff < aLimitLow [i]) aLimitLow [i] = buff;
		}
		double _fX1;
		for(i = 0 ; i < _nPointQty  ; i++)
		{
			_fY = i * _fYRatio ;
			_fX = aLimitHigh[i] * _fXRatio ;
			_fX1 = aLimitLow[i]  * _fXRatio ;
			LimitHigh<<QPointF(_fX , _fY)  ;
			LimitLow <<QPointF(_fX1 , _fY)  ;
		}
		painter.setPen(QPen(color[1]));
		painter.drawPolyline(LimitHigh);
		painter.drawPolyline(LimitLow);
	}

    if(m_pGroup->bShowCurve) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_DAC);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_DAC);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_TCG,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_TCG,0);
            break;
        default:
            break;
        }
    }
    if(CUR_RES.bShowRL) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_RL);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_RL);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_RL,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_RL,0);
            break;
        default:
            break;
        }
    }
    if(CUR_RES.bShowEL) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_EL);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_EL);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_EL,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_EL,0);
            break;
        default:
            break;
        }
    }
    if(CUR_RES.bShowSL) {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_DAC:
            DrawDacCurve(&painter, _nWidth, _nHeight,setup_SL);
            break;
        case setup_CURVE_TYPE_LINEAR_DAC:
            DrawLinearDacCurve(&painter, _nWidth, _nHeight,setup_SL);
            break;
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_SL,1);
            break;
        default:
            break;
        }
    }
    else    {
        switch(m_pGroup->curve.eType)
        {
        case setup_CURVE_TYPE_TCG:
            DrawTcgCurve(&painter, _nWidth, _nHeight,setup_SL,0);
            break;
        default:
            break;
        }
    }

}
#include <DopplerDataView.h>
void DopplerDrawAScanV::DrawDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode)
{
	CURVES& _curve = m_pGroup->curve;

	int _nWidth  = nWidth_;
	int _nHeight = nHeight_;

	int   _nBeamNo = m_cInfo.nBeamId;
	float _fTStart = m_pGroup->nTimeStart / 1000.0f;
	float _fTRange = m_pGroup->nTimeRange / 1000.0f;
	int _nPointQty = _curve.nPointQty;
	int _nPointPos = _curve.nPointPos;

	float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);

	float _ptX[18] ;
	float _ptY[18] ;

	memset(_ptX, 0x00, sizeof(_ptX));
	memset(_ptY, 0x00, sizeof(_ptY));

	float _nStepRate[5];

	_nStepRate[0] = 1;
    _nStepRate[1] = pow(10.0, (CUR_RES.CurRL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[2] = pow(10.0, (CUR_RES.CurEL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[3] = pow(10.0, (CUR_RES.CurSL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
	_nStepRate[4] = 1 / _nStepRate[2];

	//------------------------------------------
	_ptX[0] = _nWidth * _curve.faAmpRef[_nBeamNo] * _fRefAmpOff;
	_ptY[0] = 0;

	for(int i = 1; i < _nPointQty+1; i++) {
		_ptX[i] = _fRefAmpOff * _nWidth * _curve.faAmp[_nBeamNo][i - 1] / 100.0f;
		_ptY[i] = _nHeight * (_curve.faPosition[_nBeamNo][i - 1] - _fTStart) / _fTRange;
	}
	_ptX[_nPointQty+1] = _ptX[_nPointQty];
	_ptY[_nPointQty+1] = m_nHeight;

		for(int i = 0; i <= _nPointQty+1; i++) {
            m_linCurves[mode]<<QPointF(_nStepRate[mode] * _ptX[i], _ptY[i]) ;
		}
    QString _str ;
	//------------------------------------------
    QColor _Color ;
    if(mode == setup_DAC)
    {
        _Color = QColor(0, 100, 0);
        _str.sprintf("%s", "DAC")  ;
    }
    else if(mode == setup_RL)
    {
        _Color = QColor(255, 0, 0);
        _str.sprintf("%s", "RL")  ;
    }
    else if(mode == setup_EL)
    {
        _Color = QColor(0, 0, 255);
        _str.sprintf("%s", "EL")  ;
    }
    else if(mode == setup_SL)
    {
        _Color = QColor(125, 125, 125);
        _str.sprintf("%s", "SL")  ;
    }
	QPen _NewPen ;

	_NewPen.setColor(_Color);
	_NewPen.setDashPattern(m_dashes);
	painter->setPen(_NewPen);

        painter->drawPolyline(m_linCurves[mode]);

	//------------------------------------------
	m_iPtCnt[0] = _nPointQty;
    if(mode == setup_DAC)
    {
	for(int i = 0; i < _nPointQty; i++)
	{
		m_ptPos[0][i].setX(_ptX[i+1]);
		m_ptPos[0][i].setY(_ptY[i+1]);
		if(i == _nPointPos) {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 0 , 0));
		} else {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 200 , 200));
		}
	}
    }
	//------------------------------------------
}

void DopplerDrawAScanV::DrawLinearDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode)
{
	CURVES& _curve = m_pGroup->curve;

	int _nWidth  = nWidth_;
	int _nHeight = nHeight_;

	float _fTStart = m_pGroup->nTimeStart / 1000.0f;
	float _fTRange = m_pGroup->nTimeRange / 1000.0f;
	int _nPointQty = 10;

	float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);

	float _ptX[18] ;
	float _ptY[18] ;

	memset(_ptX, 0x00, sizeof(_ptX));
	memset(_ptY, 0x00, sizeof(_ptY));

	float _nStepRate[5];
	_nStepRate[0] = 1;
    _nStepRate[1] = pow(10.0, (CUR_RES.CurRL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[2] = pow(10.0, (CUR_RES.CurEL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
    _nStepRate[3] = pow(10.0, (CUR_RES.CurSL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
	_nStepRate[4] = 1 / _nStepRate[2];
	//------------------------------------------
	_ptX[0] = _nWidth * _curve.fAmpOffsetLinear * _fRefAmpOff;
	_ptY[0] = 0;

	for(int i = 1; i < _nPointQty + 1; i++)
	{
		_ptX[i] = _fRefAmpOff * _nWidth * _curve.faAmpLinear[i - 1] / 100.0f;
		_ptY[i] = _nHeight * (_curve.faAmpPosition[i - 1] - _fTStart) / _fTRange;
	}
	_ptX[_nPointQty+1] = _ptX[_nPointQty];
	_ptY[_nPointQty+1] = m_nHeight;


		for(int i = 0; i <= _nPointQty+1; i++)
		{
            m_linCurves[mode]<<QPointF(_nStepRate[mode] * _ptX[i], _ptY[i]) ;
		}

	//------------------------------------------
        QColor _Color ;
        if(mode == setup_DAC)
        {
            _Color = QColor(0, 100, 0);
        }
        else if(mode == setup_RL)
        {
            _Color = QColor(255, 0, 0);
        }
        else if(mode == setup_EL)
        {
            _Color = QColor(0, 0, 255);
        }
        else if(mode == setup_SL)
        {
            _Color = QColor(125, 125, 125);
        }
	QPen _NewPen ;

	_NewPen.setColor(_Color);
	_NewPen.setDashPattern(m_dashes);
	painter->setPen(_NewPen);


        painter->drawPolyline(m_linCurves[mode]);

	//------------------------------------------
}

void DopplerDrawAScanV::DrawTcgCurve(QPainter *painter, int nWidth_, int nHeight_,int mode,int flag)
{
	CURVES& _curve = m_pGroup->curve;

	int _nWidth  = nWidth_;
	int _nHeight = nHeight_;

	int   _nBeamNo = m_cInfo.nBeamId;
	float _fTStart = m_pGroup->nTimeStart / 1000.0f;
	float _fTRange = m_pGroup->nTimeRange / 1000.0f;
	int _nPointQty = _curve.nPointQty;
	int _nPointPos = _curve.nPointPos;

	float _fRefAmpOff = pow(10, _curve.fAmpOffsetAmp / 2.0f);
    //qDebug()<<"dddee"<<_curve.fAmpOffsetAmp<<_fRefAmpOff;

	float _ptX[18] ;
	float _ptY[18] ;
    QColor _Color ;
    QString str;
    if(mode == setup_TCG)
    {
        _Color = QColor(0, 100, 0);
        str = "TCG";
    }
    else if(mode == setup_RL)
    {
        _Color = QColor(255, 0, 0);
        str = "RL";
    }
    else if(mode == setup_EL)
    {
        _Color = QColor(125, 125, 125);
        str = "EL";
    }
    else if(mode == setup_SL)
    {
        _Color = QColor(0, 0, 255);
        str = "SL";
    }
    QPen _NewPen ;

    _NewPen.setColor(_Color);
    _NewPen.setDashPattern(m_dashes);
    painter->setPen(_NewPen);
    if(mode == setup_TCG)
    {
        if(flag == 0)
            return;
	memset(_ptX, 0x00, sizeof(_ptX));
	memset(_ptY, 0x00, sizeof(_ptY));
	//------------------------------------------
    _ptX[0] = _fRefAmpOff * _nWidth * _curve.faAmpRef[_nBeamNo];
	_ptY[0] = 0;
	for(int i = 1; i < _nPointQty+1; i++ )
	{
		_ptX[i] = _fRefAmpOff * _nWidth * (_curve.faAmp[_nBeamNo][i-1] / 100.0f);
		_ptY[i] = _nHeight * (_curve.faPosition[_nBeamNo][i-1] - _fTStart) / _fTRange;
	}
	_ptX[_nPointQty+1] = _ptX[_nPointQty];
	_ptY[_nPointQty+1] = m_nHeight;

	for(int i = _nPointQty+1; i >= 0 ; i--)
	{
		_ptX[i] = fabs(_ptX[i] - _ptX[0]);
	}
	//**************************************************************
	QColor _Color = QColor(0, 100, 0);
	QPen _NewPen ;

	_NewPen.setColor(_Color);
	_NewPen.setDashPattern(m_dashes);
	painter->setPen(_NewPen);

	//------------------------------------------
	for(int i = 0; i <= _nPointQty+1 ; i++)
	{
		m_linCurves[0]<<QPointF(_ptX[i] , _ptY[i]) ;
	}
    painter->drawPolyline(m_linCurves[0]);
    painter->drawText(_ptX[_nPointQty+1],nHeight_,str);
	//------------------------------------------
	m_iPtCnt[0] = _nPointQty;
	for(int i = 0; i < _nPointQty; i++)
	{
		m_ptPos[0][i].setX(_ptX[i+1]);
		m_ptPos[0][i].setY(_ptY[i+1]);
		if(i == _nPointPos) {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 0 , 0));
		} else {
			DrawPointRectangle(painter, m_ptPos[0][i].x() , m_ptPos[0][i].y(), QColor(200 , 200 , 200));
		}
	}
    }
    else
    {
        float midx,midy;
        midx = pow(10.0,(CUR_RES.REF_Gain[m_cInfo.nGroupId])/20.0);
        midx = midx * 0.8;
        if(mode == setup_RL)
        {
            midy = pow(10.0,(CUR_RES.CurRL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
            midy = midx * midy;
        }
        else if(mode == setup_EL)
        {
            midy = pow(10.0,(CUR_RES.CurEL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
            midy = midx * midy;
        }
        else if(mode == setup_SL)
        {
            midy = pow(10.0,(CUR_RES.CurSL[m_cInfo.nGroupId] + CUR_RES.CurSS[m_cInfo.nGroupId])/20.0);
            midy = midx * midy;
        }
        m_linCurves[mode]<<QPointF( midy * m_nWidth,0) ;
        m_linCurves[mode]<<QPointF( midy * m_nWidth , m_nHeight) ;
        RL_EL_SL[mode] = midy;
        if(flag)
        {
            painter->drawPolyline(m_linCurves[mode]);
            painter->drawText(midy * m_nWidth,nHeight_,str);
        }

    }
    //------------------------------------------
}

void DopplerDrawAScanV::DrawCoupleCurve(QImage *pImage_)
{
    ParameterProcess* _process = ParameterProcess::Instance();
//    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    WDATA*              _pData = _process->GetCoupleDataPointer(m_cInfo.nGroupId);
    float coupleStart = m_pConfig->group[m_cInfo.nGroupId].coupleMonitoringVelocity * m_pConfig->group[m_cInfo.nGroupId].nTimeStart/2000000.0;
    float coupleDepth = m_pConfig->group[m_cInfo.nGroupId].coupleMonitoringVelocity * m_pConfig->group[m_cInfo.nGroupId].nTimeRange/2000000.0;
    if(coupleDepth <= 0)
    {
        return;
    }
    int  _nPointQty = m_AScanInfo.nPointQty ;
    m_nWidth  = pImage_->width();
    m_nHeight = pImage_->height();
    double _nHeight = (double)m_nHeight;
    double  _nWidth = (double)m_nWidth ;

    QPainter painter(pImage_) ;

    ClearAll(&painter);

    float  _fScale = pow(10.0, CUR_RES.Couple_Com_Gain[m_cInfo.nGroupId]/20.0);
    bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

    double _fX , _fY;
    double _fXRatio = _nWidth / 255  ;
    double _fYRatio = _nHeight / (_nPointQty -1) ;
    //---------------
    float _fS, _fE;
    int start = 0;
    float maxDepth = 0.0;
    int loopQty = 0;
    if(0 ==_process->GetSScanVerticalRange(m_cInfo.nGroupId , &_fS ,  &_fE))
    {
        maxDepth = _fE - _fS;
        if( maxDepth <= 0 || coupleStart + coupleDepth < _fS || coupleStart > _fE){
            return;
        }
        //开始处截断
        if( _fS > coupleStart){
            start = ( _fS - coupleStart ) / coupleDepth * _nPointQty;
            coupleDepth = coupleDepth - ( _fS - coupleStart);
        } else {
            start = ( coupleStart - _fS) / maxDepth * _nHeight;
            _nHeight -= start;
            maxDepth = maxDepth - ( coupleStart - _fS);
        }

        //尾部截断
        if( maxDepth > coupleDepth){
            loopQty = _nPointQty;
            _nHeight = coupleDepth / maxDepth * _nHeight;
        } else {
            loopQty  = _nPointQty * maxDepth / coupleDepth;
        }
    }

    if(_process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_HALF_PATH ||
            _process->getTravelMode(m_cInfo.nGroupId) == setup_TRAVEL_MODE_TIME){
        start = 0;
    }
    //---------------
    _fYRatio = _nHeight / (loopQty - 1) ;

    int i  ;
    for(i = 0 ; i < loopQty ; i++)
    {
        _fY = i * _fYRatio + start;
        _fX = _process->GetRefGainScaleData(_pData[i], _fScale, _bRectify);
        _fX = _fX * _fXRatio ;

        Lines<<QPointF(_fX , _fY) ;
    }
    painter.setPen(QPen(color[0]));
    painter.drawPolyline(Lines);
}
