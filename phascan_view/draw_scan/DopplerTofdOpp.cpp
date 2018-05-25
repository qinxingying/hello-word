#include "DopplerTofdOpp.h"
#include <math.h>
#include <stdlib.h>


WDATA g_TofdAlignBuff[8192] ;


DopplerTofdOpp::DopplerTofdOpp(QObject *parent) :
	QObject(parent)
{
	m_nGroupId = -1;
	m_pTofd	= NULL;
	m_pGroup   = NULL;
	m_pScanner = NULL;

	m_pConfig = DopplerConfigure::Instance() ;
	m_process = ParameterProcess::Instance();
	SetGroupId(0);
}

void DopplerTofdOpp::SetGroupId(int nGroupId_)
{
	if(m_nGroupId != nGroupId_) {
		m_nGroupId = nGroupId_ ;
		m_pTofd	   = m_pConfig->GetTofdConfig(m_nGroupId) ;
		m_pGroup   = &m_pConfig->group[m_nGroupId]  ;
		m_pScanner = &m_pConfig->common.scanner;
		//m_iPosMax  = m_process->SAxisDistToIndex(m_pScanner->fScanStop);
	}
}

TOFD_PRO_STATUS DopplerTofdOpp::TofdDragProStatus(int nGroupId_)
{
	SetGroupId(nGroupId_);
	TOFD_PRO_STATUS _st = TOFD_PRO_NONE;
	if(m_pGroup->eTxRxMode == setup_TX_RX_MODE_TOFD )
	{
	if(m_pConfig->AppEvn.iTofdDataProMode)
	{
		_st = m_pTofd->eProingST;
	}
	}
	return _st;
}

int DopplerTofdOpp::TofdSearchPos(WDATA* pSource_, int iStart_, int iMax_, int iMin_, int iEdge_)
{
	if(pSource_ == NULL)
		return 0;
	int   _iEnd = m_pGroup->nPointQty;
	int _iStart = iStart_;

	int _iPos = _iStart;
	int _iData = 0;
	bool _bSearchStart = false;

	if(iEdge_ == 1) {
		int _iMax = 0;
		for(int i = _iStart; i < _iEnd; i++) {
			_iData = pSource_[i] * 2 | 1;
			if(!_bSearchStart) {
				if(_iData < iMin_)
					_bSearchStart = true;
			} else {
				if(_iData > _iMax && _iMax < iMax_) {
					_iMax = _iData;
					_iPos = i;
				}
			}
		}
	} else {
        int _iMin = 511;
		for(int i = _iStart; i < _iEnd; i++) {
            _iData = pSource_[i] * 2 | 1;
			if(!_bSearchStart) {
				if(_iData > iMax_)
					_bSearchStart = true;
			} else {
				if(_iData < _iMin && _iMin > iMin_) {
					_iMin = _iData;
					_iPos = i;
				}
			}
		}
	}
	return _iPos;
}

int DopplerTofdOpp::TofdDragProStart(int nGroupId_, TOFD_PRO_STATUS proSt_)
{
	SetGroupId(nGroupId_);

	for(int i = 0; i < m_pTofd->iProCnt; i++) {
		if(m_pTofd->proInfo[i].eType == proSt_) {
			return -1;
		}
	}

	int _ret = -1;
	m_pTofd->eProingST = TOFD_PRO_NONE;
	if(m_pConfig->AppEvn.iTofdDataProMode)
	{
		m_pTofd->eProingST = proSt_;
		_ret = 0;
	}
	return _ret;
}

int DopplerTofdOpp::TofdDragProcess(int nGroupId_, AREAF rcArea_)
{
	SetGroupId(nGroupId_);

	GYRECT _rect;
	_rect.left   = m_process->DistMmToDotPos(m_nGroupId, 0, rcArea_.x);
	_rect.right  = m_process->DistMmToDotPos(m_nGroupId, 0, rcArea_.x + rcArea_.width);
	_rect.top	= m_process->SAxisDistToIndex(rcArea_.y);
	_rect.bottom = m_process->SAxisDistToIndex(rcArea_.y + rcArea_.height);

	TofdDataProStart(m_nGroupId, m_pTofd->eProingST, &_rect);
	int _ret = TofdDataToShadow(m_nGroupId);
	TofdClearDragStatus(m_nGroupId);
	return _ret;
}

int DopplerTofdOpp::TofdDataProStart(int nGroupId_, TOFD_PRO_STATUS proSt_, GYRECT* pRect_)
{
	SetGroupId(nGroupId_);

	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
		return -1 ;

	for(int i = 0; i < m_pTofd->iProCnt; i++) {
		if(m_pTofd->proInfo[i].eType == proSt_) {
			return -1;
		}
	}

	int _ret = 0;
	int i = m_pTofd->iProCnt;

	int _nScanOff = m_process->GetScanOff(nGroupId_) ;
	//-----------------------------------------------
	// ��¼ƫ��ǰ��λ��
	if(pRect_ == NULL) {
		int _nScanMax = m_process->GetRealScanMax();
		GYRECT _rect;

		_rect.left   = 0;
		_rect.top	 = 0;
		_rect.right  = m_pGroup->nPointQty;
		_rect.bottom = _nScanMax;
		m_pTofd->proInfo[i].rcArea = _rect;
		//m_pTofd->proInfo[i].fY = m_process->SAxisDistToIndex(m_pConfig->common.scanner.fScanPos) + 0.5;

		int _iY = m_process->SAxisDistToIndex(m_pConfig->common.scanner.fScanPos) + 0.5;
		_iY -= _nScanOff;
		if(_iY < 0)				_iY = 0;
		if(_iY >= _nScanMax)	_iY = _nScanMax - 1;
		m_pTofd->proInfo[i].fY = _iY;
	} else {
		GYRECT _rect;

		_rect = *pRect_;
		_rect.top    -= _nScanOff;
		_rect.bottom -= _nScanOff;
		m_pTofd->proInfo[i].rcArea = _rect;
		m_pTofd->proInfo[i].fY     = _rect.top;
	}
	//-----------------------------------------------

	switch(proSt_)
	{
	case TOFD_PRO_STRAIGHT:
		m_pTofd->proInfo[i].fX = m_process->DistMmToDotPos(m_nGroupId, 0, m_pGroup->afCursor[setup_CURSOR_TFOD_LW]) + 0.5;
		break;
	case TOFD_PRO_BOTTOM:
		m_pTofd->proInfo[i].fX = m_process->DistMmToDotPos(m_nGroupId, 0, m_pGroup->afCursor[setup_CURSOR_TFOD_BW]) + 0.5;
		break;
	case TOFD_PRO_DIFFERENC:
   //	m_pTofd->proInfo[i].fY = 10;
		break;
	case TOFD_PRO_SAFT:
		m_pTofd->proInfo[i].iDots = 10;
		TofdSAFTInit(m_nGroupId, &m_pTofd->proInfo[i], m_pTofd->iSaftBuf);
		break;
	default:
		return -1;
	}

	m_pTofd->proInfo[i].eType = proSt_;
	m_pTofd->iProCnt++;

	for(i = m_pTofd->iProCnt; i < setup_MAX_TOFD_PRO_N; i++) {
		m_pTofd->proInfo[i].eType = TOFD_PRO_NONE;
	}

	return _ret;
}

int DopplerTofdOpp::TofdDataToShadow(int nGroupId_)
{
	SetGroupId(nGroupId_);
	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
		return -1;
	if(m_pTofd->iProCnt < 1)
		return -1;

	WDATA* _pSource = m_process->GetDataPointer();
	WDATA* _pShadow = m_process->GetShadowDataPointer();
	int   _nScanOff = m_process->GetScanOff(nGroupId_);

	TofdDataProcess(m_nGroupId, &m_pTofd->proInfo[0], _pSource, _pShadow);

	if(m_pTofd->iProCnt > 1)
	{
		WDATA* _pWaveBuf = new WDATA[m_pConfig->common.nDataSize+10];
		//---------------------------------------------
		WDATA* _pS = NULL;
		WDATA* _pD = NULL;
		int i;
		for(i = 1; i < m_pTofd->iProCnt; i++)
		{
			if(i%2){_pS = _pShadow ; _pD = _pWaveBuf;}
			else   {_pS = _pWaveBuf; _pD = _pShadow ;}
			TofdDataProcess(m_nGroupId, &m_pTofd->proInfo[i], _pS, _pD);
		}

		if(i%2 == 0)
		{
			m_process->GroupDataMove(m_nGroupId, _pWaveBuf, _pShadow, _nScanOff, _nScanOff);
		}
		//---------------------------------------------
		delete _pWaveBuf;
	}

	return 0;
}

int DopplerTofdOpp::TofdDataProRepeal(int nGroupId_)
{
	SetGroupId(nGroupId_);
	int _ret = -1;
	if(m_pTofd->iProCnt > 0) {
		m_pTofd->iProCnt--;
		if(m_pTofd->iProCnt>0)
		{
			TofdDataToShadow(m_nGroupId);
		}
		else
		{
			m_process->PutRecDataToShadow(m_nGroupId);
		}
		_ret = 0;
	}

	return _ret;
}

int DopplerTofdOpp::TofdDataProRedo(int nGroupId_)
{
	SetGroupId(nGroupId_);

	int _ret = -1;
	int	i = m_pTofd->iProCnt;

	if(m_pTofd->iProCnt < setup_MAX_TOFD_PRO_N && m_pTofd->proInfo[i].eType != TOFD_PRO_NONE) {
		m_pTofd->iProCnt++;
		TofdDataToShadow(m_nGroupId);
		_ret = 0;
	}

	return _ret;
}

void DopplerTofdOpp::TofdClearDragStatus(int nGroupId_)
{
	SetGroupId(nGroupId_);
	m_pTofd->eProingST = TOFD_PRO_NONE;
}

int DopplerTofdOpp::TofdProStr(int nGroupId_, char* pStr_)
{
	SetGroupId(nGroupId_);

	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
		return -1;

	TOFD_PRO_INFO* _pInfo = m_pTofd->proInfo;
	int _cnt = m_pTofd->iProCnt;

	if(_cnt > 0)
	{
		char _str[256];
		strcpy(pStr_, "");
		for(int i = 0; i < _cnt; i++)
		{
			switch(_pInfo[i].eType)
			{
			case TOFD_PRO_STRAIGHT:	sprintf(_str, "%sLW", pStr_); break;
			case TOFD_PRO_BOTTOM:	sprintf(_str, "%sBW", pStr_); break;
			case TOFD_PRO_DIFFERENC:	sprintf(_str, "%sLR", pStr_); break;
			case TOFD_PRO_SAFT:		sprintf(_str, "%sSF", pStr_); break;
			default:	return -1;
			}
			strcpy(pStr_, _str);
			if(i < _cnt-1)
			{
				sprintf(_str, "%s + ", pStr_);
				strcpy(pStr_, _str);
			}
		}
		return 0;
	}
	return -1;
}

int DopplerTofdOpp::TofdDragProStr(int nGroupId_, char* pStr_)
{
	SetGroupId(nGroupId_);

	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
		return -1;

	TOFD_PRO_STATUS _st = TofdDragProStatus(m_nGroupId);

	switch(_st)
	{
	case TOFD_PRO_STRAIGHT:	strcpy(pStr_, "LW Straitening"); break;
	case TOFD_PRO_BOTTOM:	strcpy(pStr_, "BW Straitening"); break;
	case TOFD_PRO_DIFFERENC:	strcpy(pStr_, "LW Removal"); break;
	case TOFD_PRO_SAFT:		strcpy(pStr_, "SAFT"); break;
	default:	return -1;
	}

	return 0;
}

int DopplerTofdOpp::TofdDataProcess(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_)
{
	SetGroupId(nGroupId_);
	int  _nScanOff = m_process->GetScanOff(nGroupId_);

	m_process->GroupDataMove(nGroupId_, pSource_, pDest_, _nScanOff, _nScanOff);
	switch(pInfo_->eType)
	{
	case TOFD_PRO_STRAIGHT:
		TofdLwStraitening(nGroupId_, pInfo_, pSource_, pDest_);
		break;
	case TOFD_PRO_BOTTOM:
		TofdBwStraitening(nGroupId_, pInfo_, pSource_, pDest_);
		break;
	case TOFD_PRO_DIFFERENC:
		TofdDifference(nGroupId_, pInfo_, pSource_, pDest_);
		break;
	case TOFD_PRO_SAFT:
		TofdSaft(nGroupId_, pInfo_, pSource_, pDest_);
		break;
	default:
		return -1;
	}
	return 0;
}

int DopplerTofdOpp::TofdLwStraitening(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_)
{
	SetGroupId(nGroupId_);

	int _nScanOff = m_process->GetScanOff(nGroupId_) ;
	int _nY       = (int)(pInfo_->fY + _nScanOff);
	WDATA*  _pScr =  m_process->GetDataAbsolutePosPointer(m_nGroupId, _nY, 0, pSource_);
	WDATA*  _pDst =  NULL;

    int	 _iMax = 256 + 256 * 0.1;
    int	 _iMin = 256 - 256 * 0.1;
	int	_iEdge = 0;
	int   _iStart = (int)pInfo_->fX;
	int	_iBase = TofdSearchPos(_pScr, _iStart, _iMax, _iMin, _iEdge);

	GYRECT    _rect = pInfo_->rcArea;
	_rect.top    += _nScanOff;
	_rect.bottom += _nScanOff;

	int _iDot = 0;
	for(int i = _rect.top; i < _rect.bottom; i++)
	{
		_pScr = m_process->GetDataAbsolutePosPointer(m_nGroupId, i, 0, pSource_);
		_pDst = m_process->GetDataAbsolutePosPointer(m_nGroupId, i, 0, pDest_);
		_iDot = TofdSearchPos(_pScr, _iStart, _iMax, _iMin, _iEdge);
		TofdWavAlign(_iBase, _iDot, _pScr, _pDst, _rect);
	}
	return 0;
}

int DopplerTofdOpp::TofdBwStraitening(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_)
{
	SetGroupId(nGroupId_);

	int _nScanOff = m_process->GetScanOff(nGroupId_) ;
	int _nY       = (int)(pInfo_->fY + _nScanOff);
	WDATA*  _pScr =  m_process->GetDataAbsolutePosPointer(m_nGroupId, _nY, 0, pSource_);
	WDATA*  _pDst =  NULL;

    int	 _iMax = 256 + 256 * 0.2;
    int	 _iMin = 256 - 256 * 0.5;
	int	_iEdge = 0;
	int   _iStart = (int)pInfo_->fX;
	int	_iBase = TofdSearchPos(_pScr, _iStart, _iMax, _iMin, _iEdge);

	GYRECT    _rect = pInfo_->rcArea;
	_rect.top    += _nScanOff;
	_rect.bottom += _nScanOff;
	int _iDot = 0;
	for(int i = _rect.top; i < _rect.bottom; i++)
	{
		_pScr = m_process->GetDataAbsolutePosPointer(m_nGroupId, i, 0, pSource_);
		_pDst = m_process->GetDataAbsolutePosPointer(m_nGroupId, i, 0, pDest_);
		_iDot = TofdSearchPos(_pScr, _iStart, _iMax, _iMin, _iEdge);
		TofdWavAlign(_iBase, _iDot, _pScr, _pDst, _rect);
	}
	return 0;
}

int DopplerTofdOpp::TofdDifference(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_)
{
	SetGroupId(nGroupId_);

	int _nScanOff = m_process->GetScanOff(nGroupId_) ;
	GYRECT    _rect = pInfo_->rcArea;
	_rect.top    += _nScanOff;
	_rect.bottom += _nScanOff;

	int _nY        = (int)(pInfo_->fY + _nScanOff);
	WDATA*  _pBase =  m_process->GetDataAbsolutePosPointer(m_nGroupId, _nY, 0, pSource_);

	WDATA*  _pScr =  NULL;
	WDATA*  _pDst =  NULL;

	int _nStart   = _rect.top;
	int _nStop    = _rect.bottom;
	int _nScanMax = m_process->GetScanMax();

	if(_nStop > _nScanMax)
		_nStop = _nScanMax;

	int x, y;
    float _fHalf = 511/2.0f;
	float _fData, _fPeak0, _fPeak1;
    int fdata;
	for(y = _nStart; y < _nStop; y++)
	{
		_pScr = m_process->GetDataAbsolutePosPointer(m_nGroupId, y, 0, pSource_);
		_pDst = m_process->GetDataAbsolutePosPointer(m_nGroupId, y, 0, pDest_);

		for(x = _rect.left; x < _rect.right; x++)
		{
            _fPeak0 = (float)(_pBase[x] * 2 | 1) - _fHalf;
            _fPeak1 = (float)(_pScr[x] * 2 | 1) - _fHalf;

			_fData =  _fPeak1 - _fPeak0;

			if(_fData < -_fHalf )	_fData = -_fHalf;
			if(_fData >= _fHalf )	_fData = _fHalf;

			_fData += _fHalf;
            if(_fData > 511)	_fData = WAVE_MAX;
            fdata = _fData / 2;
            _pDst[x] = fdata;
		}
	}
	return 0;
}

int DopplerTofdOpp::TofdSaft(int nGroupId_, TOFD_PRO_INFO* pInfo_, WDATA* pSource_, WDATA* pDest_)
{
	SetGroupId(nGroupId_);

	int _nScanOff = m_process->GetScanOff(nGroupId_) ;
	int _nScanMax = m_process->GetScanMax();

	GYRECT    _rect = pInfo_->rcArea;
	_rect.top    += _nScanOff;
	_rect.bottom += _nScanOff;

	int	 _iDots = (int)pInfo_->iDots;
	int _iCurveLen = 2*_iDots+1;

	WDATA*  _pScr[40];
	WDATA*  _pDst =  NULL;

	int _nStart = _rect.top;
	int _nStop  = _rect.bottom;

	if(_nStart < _nScanOff)	_nStart = _nScanOff;
	if(_nStop > _nScanMax)	_nStop  = _nScanMax;

    int x, y, i, n, _iData, _iAv;
	for(y = _nStart; y < _nStop; y++)
	{
		for(i = 0; i < _iCurveLen; i++)
		{
			n = y - _iDots + i;
			if(n < _nScanOff || n > _nScanMax)
				_pScr[i] = NULL;
			else
				_pScr[i] = m_process->GetDataAbsolutePosPointer(m_nGroupId, n, 0, pSource_);
		}
		_pDst = m_process->GetDataAbsolutePosPointer(m_nGroupId, y, 0, pDest_);

		for(x = _rect.left; x < _rect.right; x++)
		{
			_iData = _iAv = 0;
			for(i = 0; i < _iCurveLen; i++)
			{
				if(_pScr[i])
				{
					n = x + m_pTofd->iSaftBuf[_iCurveLen * x + i];
					if(n >= 0 && n < m_pGroup->nPointQty)
					{
                        _iData += _pScr[i][n] * 2 | 1;
						_iAv++;
					}
				}
			}

			if(_iAv < 1)		_iAv = 1;
			_iData /= _iAv;
			if(_iData < 0)		_iData = 0;
            if(_iData > 511)   _iData = 511;
            _iData = _iData / 2;
			_pDst[x] = _iData;
		}
	}
	return 0;
}

int DopplerTofdOpp::TofdSAFTInit(int nGroupId_, TOFD_PRO_INFO* pInfo_, int* pCurveBuf_)
{
	SetGroupId(nGroupId_);

	float   _fZero = (float)((double)m_pGroup->nWedgeDelay / 1000.0);
	float	   _C = m_pGroup->fVelocity / 1000.0f;
	float _fTStart = m_pGroup->fSampleStart / _C;
	float  _fPrecX = m_pGroup->fSampleRange / _C / m_pGroup->nPointQty;
	float  _fPrecY = m_pConfig->common.scanner.fScanStep;
	int	 _iDots = (int)pInfo_->iDots;


	QPointF _ptCurve[21];

	int  _index = 0;
	float _fTX0 = 0;
	for(int i = 0; i < m_pGroup->nPointQty; i++) {
		_fTX0 = i * _fPrecX + _fTStart + _fZero;
		m_process->FittedCurveGetPoints(m_nGroupId, _fPrecX, _fPrecY, _fTX0,  _iDots, _ptCurve);

		_index = i * (2 * _iDots + 1);
		for(int k = 0; k < 2 * _iDots + 1; k++) {
			pCurveBuf_[_index + i] = _ptCurve[i].x();
		}

	}

	return 0;
}

void DopplerTofdOpp::TofdWavAlign(int iBase_, int iDot_, WDATA* pSource_, WDATA* pDest_, GYRECT rect_)
{
	if(pSource_ && pDest_) {
		int  _iDelta = iDot_ - iBase_;
		WDATA* _pTmp = g_TofdAlignBuff;

		memcpy(pDest_, pSource_, m_pGroup->nPointQty);

		int i = rect_.left;
		if(i < 0) i = 0;
		int _len = rect_.right - rect_.left;
		if(_iDelta > 0) {
			int  _off = _iDelta;
			int  _len = m_pGroup->nPointQty - _off;
			memcpy(_pTmp,		&pSource_[_off] , _len);
			memcpy(&_pTmp[_len], &pSource_[_len] , _off);

			memcpy(&pDest_[i], &_pTmp[i] , _len);
		} else if(_iDelta < 0) {
			int  _off = - _iDelta;
			memcpy(&_pTmp[_off], pSource_,  m_pGroup->nPointQty - _off);
			memcpy(_pTmp,		pSource_,  _off);

			memcpy(&pDest_[i], &_pTmp[i] , _len);
		}
	}
}


