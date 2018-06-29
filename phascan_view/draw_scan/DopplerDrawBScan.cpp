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
extern U8 src[2048][2048];
extern int zoomflag,srcrangestart,srcrangestop;
extern int currangestart,currangestop;

void DopplerDrawBScanH::Draw (QImage* pImage_)
{
	m_hMutex.lock();
	if(!pImage_) {
		m_hMutex.unlock();
		return ;
	}
    SCANNER& _scanner = m_pConfig->common.scanner;
	S32 _nPointQty = m_BScanInfo.nPointQty ;
	S32   _nHeight = pImage_->height();
	S32	   _nWidth = pImage_->width() ;



//    U8* _pImageBits = pImage_->bits() ;//获取图像首地址
//    S32 _nWidthStep = pImage_->bytesPerLine() ;//Image每行字节数

	ParameterProcess* _process = ParameterProcess::Instance();
	volatile WDATA*	    _pData = _process->GetShadowDataPointer();
	if(!_pData) {
		m_hMutex.unlock();
		return ;
	}

	S32 _nScanPos	 = _process->GetScanIndexPos();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());

    if(_scanner.fScanPos == _scanner.fScanStart2)
    {
        m_PosStart = _scanner.fScanPos;
        m_PosStop = _scanner.fScanPos + _nHeight;
    }
    if(_nHeight <_nScanend)
    {
        _nScanend = _nHeight;
        UpdateDisplayRange(0, _nHeight , _nScanPos) ;
    }
    else
    {
        m_PosStart = _nStart;
        m_PosStop  = _nStart+_nScanend;
        emit signalScanRangeMove(0, _nStart, _nStart+_nScanend) ;
    }

    QSize csize = QSize(_nWidth,_nScanend>0?_nScanend:1);
    if(zoomflag == 1)
    {
        csize = QSize(currangestop - currangestart,_nScanend>0?_nScanend:1);
    }
    QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    U8* _pImageBits = TImage->bits() ;
    memset(_pImageBits, 0 , TImage->bytesPerLine() * TImage->height() );
    int _nWidthStep   = TImage->bytesPerLine() ;
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
    memset(src,0x00,sizeof(src));
    if(zoomflag == 0)
    {
    for(i = m_PosStart , k =_nScanend  ; i <= m_PosStop && k >= 0; i++ , k--)	{
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			_index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
            _pImg1  = _pImageBits + _nWidthStep * k ;//第K行
			_pData1 = _pData + _nOffset + _index * _nFrameOffset;

            for(j = 0 ; j <= _nWidth ; j++) {
                _pImg2  = _pImg1 + j * 3; //第j个像素
				_pData2 = _pData1 + j * _nPointQty / _nWidth;
				_iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                src[j+1][k+1] = _iData;
                //memcpy(_pImg2, &m_pColor[_iData], 3);
			}
		} else {
			_pImg1 = _pImageBits + _nWidthStep * k ;
			if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
				memset(_pImg1 , 0 , _nWidthStep) ;
			}
		}
	}
     TransformImage(_nWidth,m_PosStop-m_PosStart,src,_nWidth,_nHeight,pImage_);
    }
    else if (zoomflag == 1)
    {
        for(i = m_PosStart - 1 , k =_nScanend+1   ; i <= m_PosStop + 1 && k >= -1; i++ , k--)	{
            if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
                _index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
                _pImg1  = _pImageBits + _nWidthStep * k ;//第K行
                _pData1 = _pData + _nOffset + _index * _nFrameOffset;

                for(j = currangestart - 1; j <= currangestop+1 ; j++) {
                    if(j<0)
                        continue;
                    _pImg2  = _pImg1 + j * 3; //第j个像素
                    _pData2 = _pData1 + j * _nPointQty / _nWidth;
                    _iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                    src[j-currangestart+1][k+1] = _iData;
                    //memcpy(_pImg2, &m_pColor[_iData], 3);
                }
            } else {
                _pImg1 = _pImageBits + _nWidthStep * k ;
                if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
                    memset(_pImg1 , 0 , _nWidthStep) ;
                }
            }
        }
         TransformImage(currangestop-currangestart,m_PosStop-m_PosStart,src,_nWidth,_nHeight,pImage_);
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
    SCANNER& _scanner = m_pConfig->common.scanner;
	S32 _nPointQty = m_BScanInfo.nPointQty ;
	S32   _nHeight = pImage_->height();
	S32    _nWidth = pImage_->width() ;

//	U8* _pImageBits = pImage_->bits() ;
//	S32 _nWidthStep = pImage_->bytesPerLine() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	volatile WDATA*	    _pData = _process->GetShadowDataPointer();

	if(!_pData) {
		m_hMutex.unlock();
		return ;
	}

	S32 _nScanPos	 = _process->GetScanIndexPos();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {
        m_PosStart = _scanner.fScanPos;
        m_PosStop = _scanner.fScanPos + _nWidth;
    }
    if(_nWidth <_nScanend)
    {
        _nScanend = _nWidth;
        UpdateDisplayRange(1, _nWidth , _nScanPos) ;
    }
    else
    {
        m_PosStart = _nStart;
        m_PosStop  = _nStart+_nScanend;
        emit signalScanRangeMove(1, _nStart, _nStart+_nScanend) ;
    }

    QSize csize = QSize(_nScanend>0?_nScanend:1,_nHeight);
    if(zoomflag == 1)
    {
        csize = QSize(_nScanend>0?_nScanend:1,currangestop - currangestart);
    }
    QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    U8* _pImageBits = TImage->bits() ;
    memset(_pImageBits, 0 , TImage->bytesPerLine() * TImage->height() );
    int _nWidthStep   = TImage->bytesPerLine() ;
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
    memset(src,0x00,sizeof(src));
    if(zoomflag == 0)
    {
    for(i = m_PosStart , k = 0 ; i <= m_PosStop && k <= _nScanend; i++ , k++) {
		_index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			_pData1 = _index * _nFrameOffset + _pData + _nOffset ;
            for(j = 0 ; j <= _nHeight ; j++)	{
				_pImg1  = _pImageBits + _nWidthStep * j ;
				_pImg2  = _pImg1 + k * 3 ;
				_pData2 = _pData1 + j * _nPointQty / _nHeight  ;
				_iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                src[k+1][j+1] = _iData;
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
    TransformImage(m_PosStop-m_PosStart,_nHeight,src,_nWidth,_nHeight,pImage_);
    }
    else if(zoomflag == 1)
    { 
        for(i = m_PosStart-1 , k = -1 ; i <= m_PosStop+1 && k <= _nScanend+1; i++ , k++) {
            _index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
            if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
                _pData1 = _index * _nFrameOffset + _pData + _nOffset ;
                for(j = currangestart-1 ; j <= currangestop+1 ; j++)	{
                    if(j < 0)
                        continue;
                    _pImg1  = _pImageBits + _nWidthStep * j ;
                    _pImg2  = _pImg1 + k * 3 ;
                    _pData2 = _pData1 + j * _nPointQty / _nHeight  ;
                    _iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                    src[k+1][j-currangestart+1] = _iData;
                }
            } else {
                _pImg1 = _pImageBits + 3 * k ;
                if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
                    for(j = currangestart; j < currangestop ; j++) {
                        _pImg2 = _pImg1 +  _nWidthStep * j ;
                        memset(_pImg2, 0, 3);
                    }
                }
            }
        }
        TransformImage(m_PosStop-m_PosStart,currangestop-currangestart,src,_nWidth,_nHeight,pImage_);
    }
	m_hMutex.unlock();
}
