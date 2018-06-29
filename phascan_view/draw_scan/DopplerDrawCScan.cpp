#include "DopplerDrawCScan.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <gHeader.h>

extern int lastgroup,currentgroup;
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

    float _fGScale =  (float)(255.0 / 100.0);
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


U8 src[2048][2048];
void DopplerDrawCScanH::DrawGateAmplitude(QImage* pImage_ , GATE_TYPE eGate_)
{
	U32 _aGateValue[256] ;
    memset(_aGateValue, 0x00, sizeof(_aGateValue));
	int _nHeight   = pImage_->height();
	int _nWidth	   = pImage_->width() ;

    //U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp;// , *_pColorTmp;
    //int _nWidthStep   = pImage_->bytesPerLine() ;
    SCANNER& _scanner = m_pConfig->common.scanner;

    ParameterProcess* _process = ParameterProcess::Instance();
    int _nLawQty	  = m_CScanInfo.nLawQty   ;
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    //UpdateDisplayRange(2, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _scanner.fScanPos;
        m_PosStop  = _scanner.fScanPos + _nWidth;

    }
    if(_nWidth <_nScanend)
    {
        _nScanend = _nWidth;
        int _nScanPos	 = _process->GetScanIndexPos() ;
        UpdateDisplayRange(2, _nWidth , _nScanPos) ;
    }
    else
    {
        m_PosStart = _nStart;
        m_PosStop  = _nStart+_nScanend;
        emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
    }
    if(0 == lawstop && _nLawQty > 0)
    {
        lawstop = _nLawQty;
        _scanner.fLawStop = _nLawQty;
        _scanner.fLawQty = _nLawQty;
    }

    if(currentgroup == -1)
    {
        lawstart = 0;
        lawstop = _nLawQty;
    }
    QSize csize = QSize(_nScanend>0?_nScanend:1,(lawstop - lawstart)>0?(lawstop - lawstart):1);
    QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    unsigned char* _pData = TImage->bits() ;
    memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    U8* _pImageBits = TImage->bits() ;
    int _nWidthStep   = TImage->bytesPerLine() ;
	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	U32 _nTmpValue ;
	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart , j = 0 ; i <= m_PosStop && j < (_nScanend); i++ , j++) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			GetPixValueInfo(i, eGate_, _aGateValue);
            for(k = lawstart ; k < lawstop ; k++) {
                _pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
                _nTmpValue = (0xFF & _aGateValue[k ])  * _fScale ;
                if(_nTmpValue > 255)	_nTmpValue = 255 ;
                src[j][k-lawstart]=_nTmpValue;
                //memcpy(_pImageTmp, &m_pColor[_nTmpValue], 3);
			}
		} else {
			_pImageTmp = _pImageBits + j * 3 ;
			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
                for(k = lawstart ; k < lawstop ; k++) {
                    _pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
                    memset(_pImageTmp, 0, 3);
				}
			}
		}
	}
    _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
        TransformImage(m_PosStop - m_PosStart,lawstop-lawstart,src,_nWidth,_nHeight,pImage_);

    delete TImage;
}

void DopplerDrawCScanH::DrawGatePos(QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_)
{
	U32 _aGateValue1[256] ;
	U32 _aGateValue2[256] ;
	memset(_aGateValue1, 0x00, sizeof(_aGateValue1));
	memset(_aGateValue2, 0x00, sizeof(_aGateValue2));
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;

    //U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp , *_pColorTmp;
    //int _nWidthStep   = pImage_->bytesPerLine() ;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
    SCANNER& _scanner = m_pConfig->common.scanner;

	ParameterProcess* _process = ParameterProcess::Instance();
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _scanner.fScanPos;
        m_PosStop  = _scanner.fScanPos + _nWidth;

    }
    if(_nWidth < _nScanend)
    {
        _nScanend = _nWidth;
        int _nScanPos	 = _process->GetScanIndexPos() ;
        UpdateDisplayRange(2, _nWidth , _nScanPos) ;
    }
    else
    {
        m_PosStart = _nStart;
        m_PosStop  = _nStart+_nScanend;
        emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
    }
    //int _nScanPos	 = _process->GetScanIndexPos()  ;
    //UpdateDisplayRange(2, _nScanend>0?_nScanend:1 , _nScanPos);

    if(0 == lawstop && _nLawQty > 0)
    {
        lawstop = _nLawQty;
        _scanner.fLawStop = _nLawQty;
        _scanner.fLawQty = _nLawQty;
    }
    if(currentgroup == -1)
    {
        lawstart = 0;
        lawstop = _nLawQty;
    }
    QSize csize = QSize(_nScanend>0?_nScanend:1,(lawstop - lawstart)>0?(lawstop - lawstart):1);
    QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    unsigned char* _pData = TImage->bits() ;
    memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    U8* _pImageBits = TImage->bits() ;
    int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;
	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetScanMax();
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart , j = 0 ; i <= m_PosStop && j < (_nScanend); i++ , j++) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			if(eGate2_)	{
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
				GetPixValueDistance(_aGateValue1, _aGateValue2);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValuePos(_aGateValue1);
			}

            for(k = lawstart ; k < lawstop ; k++) {
                _pImageTmp	   = _pImageBits + (k -lawstart) * _nWidthStep + j * 3 ;
                _pColorTmp	   = m_pColor[_aGateValue1[k ]] ;
                 src[j][k-lawstart]=_aGateValue1[k ];
                //memcpy(_pImageTmp, _pColorTmp, 3);
			}
		} else {
			_pImageTmp = _pImageBits + j * 3 ;
			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
                for(k = lawstart ; k < lawstop ; k++)
				{
                    _pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
					memset(_pImageTmp, 0x00, 3);
				}
			}
		}
	}
    _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
        TransformImage(m_PosStop - m_PosStart,lawstop-lawstart,src,_nWidth,_nHeight,pImage_);
    delete TImage;
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

    //U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp1 , *_pImageTmp2;
    //int _nWidthStep   = pImage_->bytesPerLine() ;

	ParameterProcess* _process = ParameterProcess::Instance();
    SCANNER& _scanner = m_pConfig->common.scanner;
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    //UpdateDisplayRange(3, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _scanner.fScanPos;
        m_PosStop  = _scanner.fScanPos + _nWidth;

    }
    if(_nHeight < _nScanend)
    {
        _nScanend = _nHeight;
        int _nScanPos	 = _process->GetScanIndexPos() ;
        UpdateDisplayRange(3, _nHeight , _nScanPos) ;
    }
    else
    {
        m_PosStart = _nStart;
        m_PosStop  = _nStart+_nScanend;
        emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
    }

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
    if(0 == lawstop && _nLawQty > 0)
    {
        lawstop = _nLawQty;
        _scanner.fLawStop = _nLawQty;
        _scanner.fLawQty = _nLawQty;
    }
    if(currentgroup == -1)
    {
        lawstart = 0;
        lawstop = _nLawQty;
    }
    QSize csize = QSize((lawstop - lawstart)>0?(lawstop - lawstart):1,_nScanend>0?_nScanend:1);
    QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    unsigned char* _pData = TImage->bits() ;
    memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    U8* _pImageBits = TImage->bits() ;
    int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	U32 _nTmpValue ;
	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart , j = _nScanend - 1 ; i <= m_PosStop && j >= 0; i++ , j--) {
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			GetPixValueInfo(i, eGate_, _aGateValue);
			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;

            for(k = lawstart ; k < lawstop ; k++) {
                _pImageTmp2 = _pImageTmp1 + (k - lawstart) * 3 ;
                _nTmpValue = (0xFF & _aGateValue[k ])  * _fScale ;
				if(_nTmpValue > 255) _nTmpValue = 255 ;
                src[k-lawstart][j]=_nTmpValue;
                //memcpy(_pImageTmp2, &m_pColor[_nTmpValue], 3);
			}
		} else {
			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
			if( *_pImageTmp1 || *(_pImageTmp1 + 1) || *(_pImageTmp1+2)) {
				memset(_pImageTmp1 , 0 , _nWidthStep);
			}
		}
	}
    _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
    TransformImage(lawstop-lawstart,m_PosStop - m_PosStart,src,_nWidth,_nHeight,pImage_);
    delete TImage;
}

void DopplerDrawCScanV::DrawGatePos(QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_)
{
	U32 _aGateValue1[256] ;
	U32 _aGateValue2[256] ;
	memset(_aGateValue1, 0x00, sizeof(_aGateValue1));
	memset(_aGateValue2, 0x00, sizeof(_aGateValue2));
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;

    //U8* _pImageBits = pImage_->bits() ;
	U8* _pImageTmp1 , *_pImageTmp2 , *_pColorTmp;
    //int _nWidthStep   = pImage_->bytesPerLine() ;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
	ParameterProcess* _process = ParameterProcess::Instance();
    SCANNER& _scanner = m_pConfig->common.scanner;
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    //UpdateDisplayRange(3, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _scanner.fScanPos;
        m_PosStop  = _scanner.fScanPos + _nWidth;

    }
    if(_nHeight < _nScanend)
    {
        _nScanend = _nHeight;
        int _nScanPos	 = _process->GetScanIndexPos() ;
        UpdateDisplayRange(3, _nHeight , _nScanPos) ;
    }
    else
    {
        m_PosStart = _nStart;
        m_PosStop  = _nStart+_nScanend;
        emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
    }

    if(0 == lawstop && _nLawQty > 0)
    {
        lawstop = _nLawQty;
        _scanner.fLawStop = _nLawQty;
        _scanner.fLawQty = _nLawQty;
    }
    if(currentgroup == -1)
    {
        lawstart = 0;
        lawstop = _nLawQty;
    }
    QSize csize = QSize((lawstop - lawstart)>0?(lawstop - lawstart):1,_nScanend>0?_nScanend:1);
    QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    unsigned char* _pData = TImage->bits() ;
    memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    U8* _pImageBits = TImage->bits() ;
    int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetScanMax();
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart , j = _nScanend - 1 ; i <= m_PosStop && j >= 0; i++ , j--) {
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

            for(k = lawstart ; k < lawstop ; k++) {
                _pImageTmp2 = _pImageTmp1 + (k - lawstart) * 3 ;
                _pColorTmp = m_pColor[_aGateValue1[k ]] ;
                src[k-lawstart][j]=_aGateValue1[k ];
                //memcpy(_pImageTmp2, _pColorTmp, 3);
			}
		} else {
			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
			if( *_pImageTmp1 || *(_pImageTmp1 + 1) || *(_pImageTmp1+2)) {
				memset(_pImageTmp1 , 0 , _nWidthStep);
			}
		}
	}
    _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
    TransformImage(lawstop-lawstart,m_PosStop - m_PosStart,src,_nWidth,_nHeight,pImage_);
    delete TImage;
}
