#include "DopplerDrawBScan.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <QColor>

DopplerDrawBScanH::DopplerDrawBScanH(QObject *parent) :
	DopplerDrawScan(parent)
{
	m_PosStart = m_PosStop = 0 ;
}

void DopplerDrawBScanH::UpdateDrawInfo()
{
	m_hMutex.lock();
	ParameterProcess* _process = ParameterProcess::Instance();

	int _nFrameOffset = _process->GetTotalDataSize() ;
	int _nGroupOffset = _process->GetGroupDataOffset(m_cInfo.nGroupId);
	int _nLawOffset   = _process->GetGroupLawDataOffset(m_cInfo.nGroupId , m_cInfo.nBeamId) ;
	int _nOffset	  = _nGroupOffset + _nLawOffset  ;
	m_BScanInfo.nFrameSize  = _nFrameOffset  ;
	m_BScanInfo.nLawOffset  = _nOffset  ;
	m_BScanInfo.nPointQty   = _process->GetGroupPointQty(m_cInfo.nGroupId);
	m_hMutex.unlock();
}

void DopplerDrawBScanH::Draw (QImage* pImage_)
{
	m_hMutex.lock();
	if(!pImage_) {
		m_hMutex.unlock();
		return ;
	}

	S32 _nPointQty = m_BScanInfo.nPointQty ;
	S32   _nHeight = pImage_->height();
	S32	   _nWidth = pImage_->width() ;

    U8* _pImageBits = pImage_->bits() ;//获取图像首地址
    S32 _nWidthStep = pImage_->bytesPerLine() ;//Image每行字节数

	ParameterProcess* _process = ParameterProcess::Instance();
	volatile WDATA*	    _pData = _process->GetShadowDataPointer();
	if(!_pData) {
		m_hMutex.unlock();
		return ;
	}

	S32 _nScanPos	 = _process->GetScanIndexPos();
	UpdateDisplayRange(0, _nHeight , _nScanPos);

	S32 _nFrameOffset = m_BScanInfo.nFrameSize  ;
	S32      _nOffset = m_BScanInfo.nLawOffset  ;
	U8*      _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;

	F32	   _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	S32 i , j , k, _iData;
	volatile WDATA*  _pData1, *_pData2 ;
	U8* _pImg1, *_pImg2 ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
	int    _index = 0;
	for(i = m_PosStart , k = _nHeight - 1 ; i <= m_PosStop && k >= 0; i++ , k--)	{
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			_index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
            _pImg1  = _pImageBits + _nWidthStep * k ;//第K行
			_pData1 = _pData + _nOffset + _index * _nFrameOffset;

			for(j = 0 ; j < _nWidth ; j++) {
                _pImg2  = _pImg1 + j * 3; //第j个像素
				_pData2 = _pData1 + j * _nPointQty / _nWidth;
				_iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
				memcpy(_pImg2, &m_pColor[_iData], 3);
			}
		} else {
			_pImg1 = _pImageBits + _nWidthStep * k ;
			if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
				memset(_pImg1 , 0 , _nWidthStep) ;
			}
		}
	}
	m_hMutex.unlock();
}

void DopplerDrawBScanV::Draw (QImage* pImage_)
{
	m_hMutex.lock();
	if(!pImage_) {
		m_hMutex.unlock();
		return ;
	}

	S32 _nPointQty = m_BScanInfo.nPointQty ;
	S32   _nHeight = pImage_->height();
	S32    _nWidth = pImage_->width() ;

	U8* _pImageBits = pImage_->bits() ;
	S32 _nWidthStep = pImage_->bytesPerLine() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	volatile WDATA*	    _pData = _process->GetShadowDataPointer();

	if(!_pData) {
		m_hMutex.unlock();
		return ;
	}

	S32 _nScanPos	 = _process->GetScanIndexPos();
	UpdateDisplayRange(1, _nWidth , _nScanPos);

	S32 _nFrameOffset = m_BScanInfo.nFrameSize  ;
	S32      _nOffset = m_BScanInfo.nLawOffset  ;
	U8*      _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;

	F32	   _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	S32 i , j , k , _iData;
	volatile WDATA* _pData1, *_pData2 ;
	U8* _pImg1, *_pImg2 ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
	int    _index = 0;

	for(i = m_PosStart , k = 0 ; i <= m_PosStop && k < _nWidth; i++ , k++) {
		_index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			_pData1 = _index * _nFrameOffset + _pData + _nOffset ;
			for(j = 0 ; j < _nHeight ; j++)	{
				_pImg1  = _pImageBits + _nWidthStep * j ;
				_pImg2  = _pImg1 + k * 3 ;
				_pData2 = _pData1 + j * _nPointQty / _nHeight  ;
				_iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
				memcpy(_pImg2, &m_pColor[_iData], 3);
			}
		} else {
			_pImg1 = _pImageBits + 3 * k ;
			if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
				for(j = 0 ; j < _nHeight ; j++) {
					_pImg2 = _pImg1 +  _nWidthStep * j ;
					memset(_pImg2, 0, 3);
				}
			}
		}
	}
	m_hMutex.unlock();
}
