#include "DopplerDrawCScan.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <gHeader.h>


DopplerDrawCScanH::DopplerDrawCScanH(QObject *parent) : DopplerDrawScan(parent)
{
	m_PosStart = 0  ;
	m_PosStop  = 0  ;
	for(int i = 0  ; i < 256 ; i++)
		m_afScale[i] = 1.0  ;
}

void DopplerDrawCScanH::UpdateDrawInfo()
{
	m_hMutex.lock();
	UpdateDrawInfo_private();
	m_hMutex.unlock();
}

void DopplerDrawCScanH::UpdateDrawInfo_private()
{
	int _nGroupId = m_cInfo.nGroupId  ;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nFrameOffset = _process->GetTotalDataSize() ;
	int _nGroupOffset = _process->GetGroupDataOffset(_nGroupId);

	m_CScanInfo.nFrameSize	= _nFrameOffset  ;
    m_CScanInfo.nGroupOffset = _nGroupOffset  ;
	m_CScanInfo.nLawQty	 = _process->GetGroupLawQty(_nGroupId) ;
    m_CScanInfo.nPointQty  = _process->GetGroupPointQty(_nGroupId);
	m_CScanInfo.pData	   = _process->GetShadowDataPointer() ;

    GROUP_CONFIG* _group   = _process->GetGroupConfig(_nGroupId)  ;
	m_CScanInfo.bRFmode	   =  _group->eRectifier  ;
	if( m_CScanInfo.eType < CSCAN_POS_I )  return ;

	m_CScanInfo.nWedgeDelay   = _process->GetGroupWedgeDelay (m_cInfo.nGroupId) ;
	m_CScanInfo.nPulserWidth  = _process->GetGroupPulserWidth(m_cInfo.nGroupId) ;
	m_CScanInfo.pBeamDelay	= _process->GetGroupBeamDelay(m_cInfo.nGroupId)  ;

	m_CScanInfo.nThicknessStart = (int)(_process->GetCScanThicknessStart(_nGroupId) * 1000);
	m_CScanInfo.nThicknessStop = (int)(_process->GetCScanThicknessStop(_nGroupId) * 1000);

	int _nLawQty = _process->GetGroupLawQty(_nGroupId) ;
	float _fAngle ;
	for(int i = 0 ; i < _nLawQty ; i++)
	{
		_fAngle = _process->GetLawAngle(_nGroupId , i);
		m_afScale[i] = cos(DEGREE_TO_ARCH(_fAngle));
	}

	float _fGScale =  255.0 / 100.0;
	switch (m_CScanInfo.eType)
	{
		case CSCAN_POS_I :  m_CScanInfo.nGateHeight1  =  _group->gate[setup_GATE_I].nThreshold * _fGScale;   break;
		case CSCAN_POS_A :  m_CScanInfo.nGateHeight1  =  _group->gate[setup_GATE_A].nThreshold * _fGScale;   break;
		case CSCAN_POS_B :  m_CScanInfo.nGateHeight1  =  _group->gate[setup_GATE_B].nThreshold * _fGScale;   break;
		case CSCAN_POS_AI :
			m_CScanInfo.nGateHeight1  =  _group->gate[setup_GATE_A].nThreshold * _fGScale;
			m_CScanInfo.nGateHeight2  =  _group->gate[setup_GATE_I].nThreshold * _fGScale;
			break;
		case CSCAN_POS_BI :
			m_CScanInfo.nGateHeight1  =  _group->gate[setup_GATE_B].nThreshold * _fGScale;
			m_CScanInfo.nGateHeight2  =  _group->gate[setup_GATE_I].nThreshold * _fGScale;
			break;
		case CSCAN_POS_BA :
			m_CScanInfo.nGateHeight1  =  _group->gate[setup_GATE_B].nThreshold * _fGScale;
			m_CScanInfo.nGateHeight2  =  _group->gate[setup_GATE_A].nThreshold * _fGScale;
			break;
		default:
			break;
	};
}

float* DopplerDrawCScanH::GetAngleScaleRate()
{
	return m_afScale  ;
}

void DopplerDrawCScanH::SetCScanType(CSCAN_TYPE eType_)
{
	m_CScanInfo.eType  = eType_ ;
}

void  DopplerDrawCScanH::Draw (QImage* pImage_)
{
	m_hMutex.lock();
	if(!pImage_) {
		m_hMutex.unlock();
		return ;
	}

	switch (m_CScanInfo.eType)
	{
		case CSCAN_AMP_A :
			DrawGateAmplitude (pImage_ , GATE_A);
			break;
		case CSCAN_AMP_B :
			DrawGateAmplitude (pImage_ , GATE_B);
			break;
		case CSCAN_POS_I :
			DrawGatePos (pImage_ , GATE_I , GATE_NONE);
			break;
		case CSCAN_POS_A :
			DrawGatePos (pImage_ , GATE_A , GATE_NONE);
			break;
		case CSCAN_POS_B :
			DrawGatePos (pImage_ , GATE_B , GATE_NONE);
			break;
		case CSCAN_POS_AI :
			DrawGatePos (pImage_ , GATE_A , GATE_I);
			break;
		case CSCAN_POS_BI :
			DrawGatePos(pImage_ , GATE_B , GATE_I);
			break;
		case CSCAN_POS_BA :
			DrawGatePos(pImage_ , GATE_B , GATE_A);
			break;
		default:
			break;
	};
	m_hMutex.unlock();
}

void DopplerDrawCScanH::DrawGateAmplitude(QImage* pImage_ , GATE_TYPE eGate_)
{
	U32 _aGateValue[256] ;
	memset(_aGateValue, 0x00, sizeof(_aGateValue));
	int _nHeight   = pImage_->height();
	int _nWidth	   = pImage_->width() ;

	U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp;// , *_pColorTmp;
	int _nWidthStep   = pImage_->bytesPerLine() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nLawQty	  = m_CScanInfo.nLawQty   ;
	int _nLawSpaceQty = _nLawQty - 1 ;
	int _nScanPos	 = _process->GetScanIndexPos()  ;
	UpdateScanPos(2, _nWidth , _nScanPos) ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	U32 _nTmpValue ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;

	for(i = m_PosStart , j = 0 ; i <= m_PosStop && j < _nWidth; i++ , j++) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			GetPixValueInfo(i, eGate_, _aGateValue);
			for(k = 0 ; k < _nHeight ; k++) {
				_pImageTmp = _pImageBits + k * _nWidthStep + j * 3 ;
				_nTmpValue = (0xFF & _aGateValue[k * _nLawSpaceQty / _nHeight])  * _fScale ;
				if(_nTmpValue > 255)	_nTmpValue = 255 ;
				memcpy(_pImageTmp, &m_pColor[_nTmpValue], 3);
			}
		} else {
			_pImageTmp = _pImageBits + j * 3 ;
			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
				for(k = 0 ; k < _nHeight ; k++) {
					_pImageTmp = _pImageBits + k * _nWidthStep + j * 3 ;
					memset(_pImageTmp, 0, 3);
				}
			}
		}
	}
}

void DopplerDrawCScanH::DrawGatePos(QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_)
{
	U32 _aGateValue1[256] ;
	U32 _aGateValue2[256] ;
	memset(_aGateValue1, 0x00, sizeof(_aGateValue1));
	memset(_aGateValue2, 0x00, sizeof(_aGateValue2));
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;

	U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp , *_pColorTmp;
	int _nWidthStep   = pImage_->bytesPerLine() ;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
	int _nLawSpaceQty = _nLawQty - 1 ;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nScanPos	 = _process->GetScanIndexPos()  ;
    UpdateScanPos(2, _nWidth , _nScanPos);

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;
	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetScanMax();

	for(i = m_PosStart , j = 0 ; i <= m_PosStop && j < _nWidth; i++ , j++) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			if(eGate2_)	{
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
				GetPixValueDistance(_aGateValue1, _aGateValue2);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValuePos(_aGateValue1);
			}

			for(k = 0 ; k < _nHeight ; k++) {
				_pImageTmp	   = _pImageBits + k * _nWidthStep + j * 3 ;
				_pColorTmp	   = m_pColor[_aGateValue1[k * _nLawSpaceQty / _nHeight]] ;
				memcpy(_pImageTmp, _pColorTmp, 3);
			}
		} else {
			_pImageTmp = _pImageBits + j * 3 ;
			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
				for(k = 0 ; k < _nHeight ; k++)
				{
					_pImageTmp = _pImageBits + k * _nWidthStep + j * 3 ;
					memset(_pImageTmp, 0x00, 3);
				}
			}
		}
	}
}

#define MAX_SCAN_INDEX  10000
void DopplerDrawCScanH::UpdateScanPos(int nType_, int nRangle_ , int nPos_)
{
	if(nPos_ < 0) nPos_ = 0;

	if(nPos_<= m_PosStart)
	{
		m_PosStart = nPos_  ;
		m_PosStop  = m_PosStart + nRangle_ - 1 ;
		if(m_PosStop > MAX_SCAN_INDEX)
		{
			m_PosStart = MAX_SCAN_INDEX -  nRangle_ + 1 ;
			m_PosStop  = MAX_SCAN_INDEX;
		}
		//emit signalScanRangeMove(nType_, m_PosStart, m_PosStop) ;
	}
	else if(nPos_ >= m_PosStop)
	{
		m_PosStop = nPos_  ;
		m_PosStart  = m_PosStop - nRangle_ + 1 ;

		if(m_PosStart < 0)
		{
			m_PosStart = 0  ;
			m_PosStop  = nRangle_ - 1  ;
		}
		//emit signalScanRangeMove(nType_, m_PosStart, m_PosStop) ;
	}
	emit signalScanRangeMove(nType_, m_PosStart, m_PosStop) ;
}

void DopplerDrawCScanH::GetPixValueInfo(int nScanPos_, GATE_TYPE eGate_, U32* pBuff_)
{
	UpdateDrawInfo_private();
	setup_GATE_NAME _eGate;

	switch(eGate_)
	{
	case GATE_A: _eGate = setup_GATE_A; break;
	case GATE_B: _eGate = setup_GATE_B; break;
	case GATE_I: _eGate = setup_GATE_I; break;
	default:  return;
	}

	int	 _nBeamQty = m_CScanInfo.nLawQty;

	ParameterProcess* _process = ParameterProcess::Instance();
	PEAK_CONFIG _info[setup_GATE_MAX];
	for(int i = 0 ; i < _nBeamQty ; i++)
	{
		_process->GetGatePeakInfos(m_cInfo.nGroupId, nScanPos_, i, _info);
		pBuff_[i] = (_info[_eGate].fD * 1000);
		pBuff_[i] = (pBuff_[i] << 8) | ((U8)(_info[_eGate].iY));
	}
}

void DopplerDrawCScanH::GetPixValuePos(U32* pBuff_)
{
	U32	_nBeamQty = m_CScanInfo.nLawQty;
	U32		_nMin = m_CScanInfo.nThicknessStart;
	U32		_nMax = m_CScanInfo.nThicknessStop;
	U32	  _nRange = _nMax - _nMin;
	U32 _nGateHeight = m_CScanInfo.nGateHeight1;

	U32 _nData  = 0;
	U32 _nPeak  = 0;
	U32 _nDepth = 0;
	for(U32 i = 0; i < _nBeamQty; i++)
	{
		_nData  = pBuff_[i];
		_nPeak  = _nData & 0xFF;
		if(_nPeak < _nGateHeight)
		{
			//pBuff_[i] = 255 ;
			pBuff_[i] = 0 ;
		}
		else
		{
			_nDepth = _nData >> 8;
			if(_nDepth < _nMin)
				pBuff_[i] = 0 ;
			else if(_nDepth > _nMax)
				pBuff_[i] = 255 ;
			else
			{
				pBuff_[i] = 255 * (_nDepth - _nMin) / _nRange ;
				if(pBuff_[i] > 255)
					pBuff_[i] = 255;
			}
		}
	}
}

void DopplerDrawCScanH::GetPixValueDistance(U32* pBuff1_ , U32* pBuff2_)
{
	U32	 _nBeamQty = m_CScanInfo.nLawQty;
	U32		 _nMin = m_CScanInfo.nThicknessStart;
	U32		 _nMax = m_CScanInfo.nThicknessStop;
	U32	   _nRange = _nMax - _nMin;
	U32 _nGateHeight1 = m_CScanInfo.nGateHeight1;
	U32 _nGateHeight2 = m_CScanInfo.nGateHeight2;

	U32 _nData1, _nData2;
	U32 _nPeak1, _nPeak2;
	U32 _nDepth1, _nDepth2;
	for(U32 i = 0; i < _nBeamQty; i++)
	{
		_nData1  = pBuff1_[i];	  _nData2  = pBuff2_[i];
		_nPeak1  = _nData1 & 0xFF;  _nPeak2  = _nData2 & 0xFF;
		if(_nPeak1 >= _nGateHeight1 && _nPeak2 >= _nGateHeight2)
		{
			_nDepth1 = _nData1 >> 8;
			_nDepth2 = _nData2 >> 8;

			_nDepth1 = abs((int)(_nDepth2 - _nDepth1));

			if(_nDepth1 < _nMin)
				pBuff1_[i] = 0 ;
			else if(_nDepth1 > _nMax)
				pBuff1_[i] = 255 ;
			else
			{
				pBuff1_[i] = 255 * (_nDepth1 - _nMin) / _nRange ;
				if(pBuff1_[i] > 255)
					pBuff1_[i] = 255;
			}
		}
		else
		{
			pBuff1_[i] = 255 ;
		}
	}
}

DopplerDrawCScanV::DopplerDrawCScanV(QObject *parent) : DopplerDrawCScanH(parent)
{
}

void DopplerDrawCScanV::DrawGateAmplitude(QImage* pImage_ , GATE_TYPE eGate_)
{
	U32 _aGateValue[256] ;
	memset(_aGateValue, 0x00, sizeof(_aGateValue));
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;

	U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp1 , *_pImageTmp2;
	int _nWidthStep   = pImage_->bytesPerLine() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nScanPos	 = _process->GetScanIndexPos()  ;
	UpdateScanPos(3, _nHeight , _nScanPos) ;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
	int _nLawSpaceQty = _nLawQty - 1 ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	U32 _nTmpValue ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;

	for(i = m_PosStart , j = _nHeight - 1 ; i <= m_PosStop && j >= 0; i++ , j--) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			GetPixValueInfo(i, eGate_, _aGateValue);
			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;

			for(k = 0 ; k < _nWidth ; k++) {
				_pImageTmp2 = _pImageTmp1 + k * 3 ;
				_nTmpValue = (0xFF & _aGateValue[k * _nLawSpaceQty / _nWidth])  * _fScale ;
				if(_nTmpValue > 255) _nTmpValue = 255 ;
                memcpy(_pImageTmp2, &m_pColor[_nTmpValue], 3);
			}
		} else {
			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
			if( *_pImageTmp1 || *(_pImageTmp1 + 1) || *(_pImageTmp1+2)) {
				memset(_pImageTmp1 , 0 , _nWidthStep);
			}
		}
	}
}

void DopplerDrawCScanV::DrawGatePos(QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_)
{
	U32 _aGateValue1[256] ;
	U32 _aGateValue2[256] ;
	memset(_aGateValue1, 0x00, sizeof(_aGateValue1));
	memset(_aGateValue2, 0x00, sizeof(_aGateValue2));
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;

	U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp1 , *_pImageTmp2 , *_pColorTmp;
	int _nWidthStep   = pImage_->bytesPerLine() ;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
	int _nLawSpaceQty = _nLawQty - 1 ;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nScanPos	 = _process->GetScanIndexPos()  ;
	UpdateScanPos(3, _nHeight , _nScanPos) ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetScanMax();

	for(i = m_PosStart , j = _nHeight - 1 ; i <= m_PosStop && j >= 0; i++ , j--) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			if(eGate2_) {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
				GetPixValueDistance(_aGateValue1, _aGateValue2);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValuePos(_aGateValue1);
			}

			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;

			for(k = 0 ; k < _nWidth ; k++) {
				_pImageTmp2 = _pImageTmp1 + k * 3 ;
				_pColorTmp = m_pColor[_aGateValue1[k * _nLawSpaceQty / _nWidth]] ;
                memcpy(_pImageTmp2, _pColorTmp, 3);
			}
		} else {
			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
			if( *_pImageTmp1 || *(_pImageTmp1 + 1) || *(_pImageTmp1+2)) {
				memset(_pImageTmp1 , 0 , _nWidthStep);
			}
		}
	}
}
