#include "DopplerDrawBScan.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <QColor>

int Bscan_range = 0;
int Bsrc_start = 0;
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

bool DopplerDrawBScanH::getShowAllStatus()
{
    return m_pConfig->group[m_cInfo.nGroupId].CScanShowAll;
}

extern U8 src[2048][2048];
//extern int srcrangestart,srcrangestop;

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

    static int flag = 0;

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
    if(zoomflag == 1)
    {
        if((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop))
            flag = 1;
        if(flag == 1)
        {
            if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                curscanstart = _scanner.fScanPos-1;
            if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                curscanstop = _scanner.fScanPos+1;
        }
        _nStart     = _process->SAxisDistToIndex(curscanstart);
        _nScanend    = _process->SAxisDistToIndex(curscanstop) - _nStart;
    }
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {
        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop = _process->SAxisDistToIndex(_scanner.fScanPos) + _nHeight;
    }
    float step = 1.0;
    int VRange;
    if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
        if(zoomflag == 2){
            zoomflag = 0;
            flag = 0;
            m_PosStart = _process->SAxisDistToIndex(srcBstart);
            m_PosStop = _process->SAxisDistToIndex(srcBend);
            _nScanend = m_PosStop - m_PosStart;
            emit signalScanRangeMove(0, m_PosStart, m_PosStop) ;
        }else{
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(0, _nStart, _nStart+_nScanend) ;
        }
        if(_nHeight < _nScanend){
            if(_nHeight > 2048){
                _nHeight = 2048;
            }
            step = (float)_nHeight/_nScanend;
            VRange = _nHeight;
        }else{
            if(m_PosStop - m_PosStart > 2048){
                step = (float)2048/(m_PosStop - m_PosStart);
                VRange = 2048;
            }else{
              VRange = m_PosStop - m_PosStart;
            }
        }
    }else{
        if(_nHeight <_nScanend){
            _nScanend = _nHeight;
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcBstart);
                m_PosStop = _process->SAxisDistToIndex(srcBend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync)
            {
                if(Bscan_range == _nScanend){
                    m_PosStart = Bsrc_start;
                    m_PosStop = Bsrc_start + _nScanend;
                }else{
                    Bscan_range = _nScanend;
                }
            }
            UpdateDisplayRange(0, _nHeight , _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Bsrc_start = m_PosStart;
            }
        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcBstart);
                m_PosStop = _process->SAxisDistToIndex(srcBend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(0, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(0, _nStart, _nStart+_nScanend) ;
            }
        }
        VRange = m_PosStop - m_PosStart;
    }

    QSize csize = QSize(_nPointQty,_nScanend>0?_nScanend:1);
    if(zoomflag == 1)
    {
        csize = QSize((currangestop - currangestart)*_nPointQty/_nWidth,_nScanend>0?_nScanend:1);
    }
    //QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    //U8* _pImageBits = TImage->bits() ;
    //memset(_pImageBits, 0 , TImage->bytesPerLine() * TImage->height() );
    //int _nWidthStep   = TImage->bytesPerLine() ;
	S32 _nFrameOffset = m_BScanInfo.nFrameSize  ;
	S32      _nOffset = m_BScanInfo.nLawOffset  ;
	U8*      _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;

	F32	   _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	S32 i , j , k, _iData;
	volatile WDATA*  _pData1, *_pData2 ;
    //U8* _pImg1, *_pImg2 ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
	int    _index = 0;
    memset(src,0x00,sizeof(src));
    int fixDis;
    if( _scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        fixDis = 0;
    }else{
        int index = _process->TransforIndexPosToIndex(_scanner.fIndexPos);
        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        fixDis = scanQty*index;

    }
    if(zoomflag == 0)
    {
    for(i = m_PosStart , k =_nScanend  ; i <= m_PosStop && k >= 0; i++ , k--)	{
        int buff = fixDis + i;
        if(_pMarker[buff] && buff >= _nScanOff && buff < _nScanMax) {
            _index = _process->GetRealScanIndex(m_cInfo.nGroupId, buff);
            //_pImg1  = _pImageBits + _nWidthStep * k ;//第K行
			_pData1 = _pData + _nOffset + _index * _nFrameOffset;
            int index_ = k*step;
            for(j = 0 ; j <= _nPointQty ; j++) {
                //_pImg2  = _pImg1 + j * 3; //第j个像素
                _pData2 = _pData1 + j ;
				_iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                src[j+1][index_+1] = _iData;
                //memcpy(_pImg2, &m_pColor[_iData], 3);
			}
		} else {
//			_pImg1 = _pImageBits + _nWidthStep * k ;
//			if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
//				memset(_pImg1 , 0 , _nWidthStep) ;
//			}
		}
	}
     TransformImage(_nPointQty,VRange,src,_nWidth,_nHeight,pImage_);
    }
    else if (zoomflag == 1)
    {
        for(i = m_PosStart - 1 , k =_nScanend+1   ; i <= m_PosStop + 1 && k >= -1; i++ , k--)	{
            int buff = fixDis + i;
            if(_pMarker[buff] && buff >= _nScanOff && buff < _nScanMax) {
                _index = _process->GetRealScanIndex(m_cInfo.nGroupId, buff);
                //_pImg1  = _pImageBits + _nWidthStep * k ;//第K行
                _pData1 = _pData + _nOffset + _index * _nFrameOffset;
                int index_ = (k + 1)*step;
                for(j = currangestart*_nPointQty/_nWidth - 1; j <= currangestop*_nPointQty/_nWidth+1 ; j++) {
                    if(j<0)
                        continue;
                    //_pImg2  = _pImg1 + j * 3; //第j个像素
                    _pData2 = _pData1 + j ;
                    _iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                    src[j-currangestart*_nPointQty/_nWidth+1][index_] = _iData;
                    //memcpy(_pImg2, &m_pColor[_iData], 3);
                }
            } else {
//                _pImg1 = _pImageBits + _nWidthStep * k ;
//                if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
//                    memset(_pImg1 , 0 , _nWidthStep) ;
//                }
            }
        }
         TransformImage((currangestop-currangestart)*_nPointQty/_nWidth,VRange,src,_nWidth,_nHeight,pImage_);
    }
    //delete TImage;
	m_hMutex.unlock();
}

DopplerDrawBScanV::DopplerDrawBScanV(QObject *parent) : DopplerDrawBScanH(parent)
{

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
    static int flag = 0;
//	U8* _pImageBits = pImage_->bits() ;
//	S32 _nWidthStep = pImage_->bytesPerLine() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	volatile WDATA*	    _pData = _process->GetShadowDataPointer();

	if(!_pData) {
		m_hMutex.unlock();
		return ;
	}
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	S32 _nScanPos	 = _process->GetScanIndexPos();
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    if(zoomflag == 1)
    {
        if((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop))
            flag = 1;
        if(flag == 1)
        {
            if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                curscanstart = _scanner.fScanPos-1;
            if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                curscanstop = _scanner.fScanPos+1;
        }
        _nStart     = _process->SAxisDistToIndex(curscanstart);
        _nScanend    = _process->SAxisDistToIndex(curscanstop)-_nStart;
    }
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {
        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
    }

    float step = 1.0;
    int HRange;
    if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
        if(zoomflag == 2){
            zoomflag = 0;
            flag = 0;
            m_PosStart = _process->SAxisDistToIndex(srcBstart);
            m_PosStop = _process->SAxisDistToIndex(srcBend);
            _nScanend = m_PosStop - m_PosStart;
            emit signalScanRangeMove(1, m_PosStart, m_PosStop) ;
        }else{
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(1, _nStart, _nStart+_nScanend) ;
        }
        if(_nWidth < _nScanend){
            if(_nWidth > 2048){
                _nWidth = 2048;
            }
            step = (float)_nWidth/_nScanend;
            HRange = _nWidth;
        }else{
            if(m_PosStop - m_PosStart > 2048){
                step = (float)2048/(m_PosStop - m_PosStart);
                HRange = 2048;
            }else{
                HRange = m_PosStop - m_PosStart;
            }

        }
    }else{
        if(_nWidth <_nScanend){
            _nScanend = _nWidth;
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcBstart);
                m_PosStop = _process->SAxisDistToIndex(srcBend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Bscan_range == _nScanend){
                    m_PosStart = Bsrc_start;
                    m_PosStop = Bsrc_start + _nScanend;
                }else{
                    Bscan_range = _nScanend;
                }
            }
            UpdateDisplayRange(1, _nWidth , _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Bsrc_start = m_PosStart;
            }
        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcBstart);
                m_PosStop = _process->SAxisDistToIndex(srcBend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(1, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(1, _nStart, _nStart+_nScanend) ;
            }
        }
        HRange = m_PosStop - m_PosStart;
    }


    QSize csize = QSize(_nScanend>0?_nScanend:1,_nPointQty);
    if(zoomflag == 1)
    {
        csize = QSize(_nScanend>0?_nScanend:1,(currangestop - currangestart)* _nPointQty / _nHeight);
    }
    //QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    //U8* _pImageBits = TImage->bits() ;
    //memset(_pImageBits, 0 , TImage->bytesPerLine() * TImage->height() );
    //int _nWidthStep   = TImage->bytesPerLine() ;
	S32 _nFrameOffset = m_BScanInfo.nFrameSize  ;
	S32      _nOffset = m_BScanInfo.nLawOffset  ;
	U8*      _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;

	F32	   _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	bool _bRectify = (_process->GetRectifierMode(m_cInfo.nGroupId) == setup_RECTIFIER_RF ) ;

	S32 i , j , k , _iData;
	volatile WDATA* _pData1, *_pData2 ;
    //U8* _pImg1, *_pImg2 ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
	int    _index = 0;
    memset(src,0x00,sizeof(src));
    int fixDis;
    if( _scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        fixDis = 0;
    }else{
        int index = _process->TransforIndexPosToIndex(_scanner.fIndexPos);
        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        fixDis = scanQty*index;

    }
    if(zoomflag == 0)
    {
    for(i = m_PosStart , k = 0 ; i <= m_PosStop && k <= _nScanend; i++ , k++) {
        int buff = fixDis + i;
        if(_pMarker[buff] && buff >= _nScanOff && buff < _nScanMax) {
            _index = _process->GetRealScanIndex(m_cInfo.nGroupId, buff);
			_pData1 = _index * _nFrameOffset + _pData + _nOffset ;
            int index_ = k*step;
            for(j = 0 ; j <= _nPointQty ; j++)	{
                //_pImg1  = _pImageBits + _nWidthStep * j ;
                //_pImg2  = _pImg1 + k * 3 ;
                _pData2 = _pData1 + j   ;
				_iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                src[index_+1][j+1] = _iData;
			}
		} else {
//			_pImg1 = _pImageBits + 3 * k ;
//			if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
//                for(j = 0 ; j < _nHeight ; j++) {
//					_pImg2 = _pImg1 +  _nWidthStep * j ;
//					memset(_pImg2, 0, 3);
//				}
//			}
		}
	}
    TransformImage(HRange,_nPointQty,src,_nWidth,_nHeight,pImage_);
    }
    else if(zoomflag == 1)
    { 
        for(i = m_PosStart-1 , k = -1 ; i <= m_PosStop+1 && k <= _nScanend+1; i++ , k++) {
            int buff = fixDis + i;

            if(_pMarker[buff] && buff >= _nScanOff && buff < _nScanMax) {
                _index = _process->GetRealScanIndex(m_cInfo.nGroupId, buff);
                _pData1 = _index * _nFrameOffset + _pData + _nOffset ;
                int index_ = (k + 1)*step;
                for(j = currangestart* _nPointQty / _nHeight-1 ; j <= currangestop* _nPointQty / _nHeight+1 ; j++)	{
                    if(j < 0)
                        continue;
                    //_pImg1  = _pImageBits + _nWidthStep * j ;
                    //_pImg2  = _pImg1 + k * 3 ;
                    _pData2 = _pData1 + j   ;
                    _iData  = _process->GetRefGainScaleData(*_pData2, _fScale, _bRectify);
                    src[index_][j-currangestart* _nPointQty / _nHeight+1] = _iData;
                }
            } else {
//                _pImg1 = _pImageBits + 3 * k ;
//                if(*_pImg1  || *(_pImg1+1) || *(_pImg1+2)) {
//                    for(j = currangestart; j < currangestop ; j++) {
//                        _pImg2 = _pImg1 +  _nWidthStep * j ;
//                        memset(_pImg2, 0, 3);
//                    }
//                }
            }
        }
        TransformImage(HRange,(currangestop-currangestart)* _nPointQty / _nHeight,src,_nWidth,_nHeight,pImage_);
    }
    //delete TImage;
	m_hMutex.unlock();
}
