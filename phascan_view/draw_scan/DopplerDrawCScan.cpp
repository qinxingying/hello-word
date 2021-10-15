#include "DopplerDrawCScan.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <gHeader.h>
#include "ProcessDisplay.h"

extern int lastgroup,currentgroup;
extern int Phascan_Version;
int Cscan_range = 0;
int Csrc_start = 0;
int Cindex_range = 0;
int Csrc_indexStart = 0;

U32 getGateDataAmplitude( U32 value)
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        return value & 0xFF;
    }
    else
    {
        return value & 0x1FF;
    }
}

U32 getGateDataDepth( U32 value)
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        return value >> 8;
    }
    else
    {
        return value >> 9;
    }
}

U32 combinedGateDate( U32 depth, int amp)
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4 || Phascan_Version == 6 || Phascan_Version == 8)
    {
        return ( (depth << 8) | (U8)amp);
    }
    else
    {
        return ( (depth << 9) | amp);
    }
}

DopplerDrawCScanH::DopplerDrawCScanH(QObject *parent) : DopplerDrawScan(parent)
{
	m_PosStart = 0  ;
	m_PosStop  = 0  ;
    topcShow   = false;
    topcMergShow = false;
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

bool DopplerDrawCScanH::getShowAllStatus()
{
    return m_pConfig->group[m_cInfo.nGroupId].CScanShowAll;
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
U8 srcMerge[2048][2048];
void DopplerDrawCScanH::DrawGateAmplitude(QImage* pImage_ , GATE_TYPE eGate_)
{
    //qDebug()<<"cscan_group"<<m_cInfo.nGroupId;
	U32 _aGateValue[256] ;
    memset(_aGateValue, 0x00, sizeof(_aGateValue));
    //int _nHeight   = pImage_->height();
	int _nWidth	   = pImage_->width() ;
    int _nHeight = pImage_->height();
    static int flag = 0;
    //U8* _pImageBits = pImage_->bits() ;
    //U8* _pImageTmp;// , *_pColorTmp;
    //int _nWidthStep   = pImage_->bytesPerLine() ;
    SCANNER& _scanner = m_pConfig->common.scanner;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nLawQty  = m_CScanInfo.nLawQty;
    int lawstart  = _process->GetLawStart();
    int lawstop   = _process->GetLawStop();
    int lawstart2 = lawstart;
    int lawstop2  = lawstop;
    int _nStart   = _process->GetScanIndexStart2();
    int _nScanend = _process->SAxisstoptoIndex(_process->GetScanend());    

    //二维扫查显示
    if( _scanner.eScanType == setup_SCAN_TYPE_RASTER){
        int indexStepBeam = _process->GetRasterIndexStepBeam(m_cInfo.nGroupId);

        //命名规范，对新增的变量做如下规定：_abc a为Index或Scan表示步进轴或者扫查轴 b为Start或End等限定位置
        //c为Pos或Index或pixel表示是坐标位置还是数据索引或像素
        int _IndexStartIndex = _process->TransforIndexPosToIndex( _process->GetIndexStartPos());
        int _IndexRangeIndex = _process->TransforIndexPosToIndex( _process->GetIndexEndPos());
        int _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        //float Indexlength = _process->GetRasterCoveredLength(m_cInfo.nGroupId);
        int heightToIndex = (_nHeight- _process->GetGroupLawQty(m_cInfo.nGroupId))/indexStepBeam;
        if( heightToIndex < 0){
            heightToIndex = 0;
        }
        if(zoomflag == 1){
            if(((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop)) ||
                   ((_scanner.fIndexPos > curIndexStartPos)&&(_scanner.fIndexPos < curIndexStopPos))){
                flag = 1;
            }
            if( flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
                if((_scanner.fIndexPos < curIndexStartPos+1)&&(_scanner.fIndexPos-1 >= _scanner.fIndexStart))
                    curIndexStartPos = _scanner.fIndexPos-1;
                if((_scanner.fIndexPos > curIndexStopPos-1)&&(_scanner.fIndexPos+1 <= _scanner.fIndexStop))
                    curIndexStopPos = _scanner.fIndexPos+1;
            }
            _nStart     = _process->SAxisDistToIndex(curscanstart);
            _nScanend   = _process->SAxisDistToIndex(curscanstop) - _nStart;
            _IndexStartIndex = _process->TransforIndexPosToIndex(curIndexStartPos);
            _IndexRangeIndex = _process->TransforIndexPosToIndex(curIndexStopPos) - _IndexStartIndex;
            _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        }
        if(_scanner.fScanPos == _scanner.fScanStart2){

            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
        }
        if(_scanner.fIndexPos == _scanner.fIndexStart){
            m_indexStartIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
            m_indexStopIndex = m_indexStartIndex + heightToIndex;
        }
        float Hstep = 1.0;
        int HRange;
        float Vstep = 1.0;
        int VRange;
        if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
            if(zoomflag == 2){
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend) ;
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
                zoomflag = 0;
                flag = 0;
                m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
                emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
            }
            if(_nWidth < _nScanend){
                if(_nWidth > 2048){
                    _nWidth = 2048;
                }
                Hstep = (float)_nWidth/_nScanend;
                HRange = _nWidth;
            }else{
                if(m_PosStop - m_PosStart > 2048){
                    Hstep = (float)2048/(m_PosStop - m_PosStart);
                    HRange = 2048;
                }else{
                    HRange = m_PosStop - m_PosStart;
                }
            }

            if(_nHeight < _IndexRangePixel){
                if(_nHeight > 2048){
                    _nHeight = 2048;
                }
                Vstep = (float)_nHeight/_IndexRangePixel;
                VRange = _nHeight;
            }else{
                if(_IndexRangePixel > 2048){
                    Vstep = (float)2048/_IndexRangePixel;
                    VRange = 2048;
                }else{
                    VRange = _IndexRangePixel;
                }
            }
        }else{
            if(_nWidth <_nScanend){
                _nScanend = _nWidth;
                if(zoomflag == 2){
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cscan_range == _nScanend){
                        m_PosStart = Csrc_start;
                        m_PosStop = Csrc_start + _nScanend;
                    }else{
                        Cscan_range = _nScanend;
                    }
                }
                int _nScanPos	 = _process->GetScanIndexPos();
                UpdateDisplayRange(2, _nWidth , _nScanPos) ;
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_start = m_PosStart;
                }
            }else{
                if(zoomflag == 2){
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend) ;
                    _nScanend = m_PosStop - m_PosStart;
                    emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
                }else{
                    m_PosStart = _nStart;
                    m_PosStop  = _nStart+_nScanend;
                    emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
                }
            }
            if(_nHeight < _IndexRangePixel){
                _IndexRangePixel = heightToIndex*indexStepBeam + _process->GetGroupLawQty(currentgroup);
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                    m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cindex_range == _IndexRangePixel){
                        m_indexStartIndex = Csrc_indexStart;
                        m_indexStopIndex = Csrc_indexStart + heightToIndex;
                    }else{
                        Cindex_range = _IndexRangePixel;
                    }
                }
                int _nIndexCurIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
                UpdateIndexRange(0, heightToIndex, _nIndexCurIndex);
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_indexStart = m_indexStartIndex;
                }
            }else{
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                    m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
                    emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
                }else{
                    m_indexStartIndex = _IndexStartIndex;
                    m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                    emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
                }
            }
            HRange = m_PosStop - m_PosStart;
            VRange = _IndexRangePixel;
        }

        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, p;
        int Vindex_;
//        int indexStepDrawBeam = indexStepBeam;
//        if(indexStepDrawBeam > _process->GetGroupLawQty(m_cInfo.nGroupId)){
//            indexStepDrawBeam = _process->GetGroupLawQty(m_cInfo.nGroupId);
//        }
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        U32 _nTmpValue;
//        PEAK_CONFIG _info[setup_GATE_MAX];
//        setup_GATE_NAME _eGate;

//        switch(eGate_)
//        {
//        case GATE_A: _eGate = setup_GATE_A; break;
//        case GATE_B: _eGate = setup_GATE_B; break;
//        case GATE_I: _eGate = setup_GATE_I; break;
//        default:  return;
//        }
        memset(src,0x00,sizeof(src));
        WDATA* pData;
        pData = _process->GetRasterData(m_cInfo.nGroupId, setup_CSCAN_SOURCE_MODE (m_CScanInfo.eType));
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){

            double _offsetbuff = _pConfig->rasterOffset[j];
            int _offset = scanQty * _offsetbuff /(_scanner.fScanStop - _scanner.fScanStart);
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){

                if( p - _offset < 0 || p - _offset >= scanQty){
                    continue;
                }
                int markerPos = markerBuff + k - _offset;
                if( _pMarker[markerPos]){
                    int Hindex_ = p*Hstep;
                    int markOffset = markerPos * indexStepBuff;
                    for(int w = 0; w < indexStepBuff; w++){
                        Vindex_ = (srcBuffIndex + w)*Vstep;
                        //_process->GetGatePeakInfos(m_cInfo.nGroupId, markerPos, w, _info);
                        //_nTmpValue = getGateDataAmplitude(_info[_eGate].iY) * _fScale;
                        _nTmpValue = _process->correctionPdata(pData[markOffset + w]) * _fScale;
                        if(_nTmpValue > WAVE_MAX)	_nTmpValue = WAVE_MAX;

                        src[Hindex_][Vindex_] = _nTmpValue;
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        //int srcHeight = (j-1)*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        //TransformImage( p, srcHeight, src, pImage_->width(), pImage_->height(), pImage_);
        TransformImage( HRange, Vindex_, src, pImage_->width(), pImage_->height(), pImage_);
        return;
    }

    //TOPC融合
    TOPC_INFO& _TOPCInfo  = m_pConfig->group[m_cInfo.nGroupId].TopCInfo;
    if( m_pConfig->common.TOPCMergeValid && _TOPCInfo.TOPCMergeStatus || topcMergShow){
        int mergeGroupId = _TOPCInfo.TOPCMergeRefer;
        TOPC_INFO& _mergeTOPCInfo = m_pConfig->group[mergeGroupId].TopCInfo;
        double topcWidth = (_TOPCInfo.TOPCWidth > _mergeTOPCInfo.TOPCWidth) ? _TOPCInfo.TOPCWidth : _mergeTOPCInfo.TOPCWidth;
        bool   Calculation = true;   //false 表示闸门在图像外面，绘制空白即可
        float  gateStart = m_pConfig->group[m_cInfo.nGroupId].gate[0].fStart;
        float  gateWidth = m_pConfig->group[m_cInfo.nGroupId].gate[0].fWidth;
        float  gateStop  = gateStart + gateWidth;
        float  indexOffset = m_pConfig->group[m_cInfo.nGroupId].fIndexOffset;
        int    direction;

        float realHeightStart, realHeightStop;
        float realWidthStart, realWidthStop;
        if( gateStart >= _TOPCInfo.stopY || gateStop <= _TOPCInfo.startY){
            Calculation = false;
        }else{
            realHeightStart = ( gateStart > _TOPCInfo.startY) ? gateStart : _TOPCInfo.startY;
            realHeightStop  = ( gateStop < _TOPCInfo.stopY) ? gateStop : _TOPCInfo.stopY;
            if(fabs(realHeightStop - realHeightStart) < 1.0){
                Calculation = false;
            }
        }
        if(zoomflag == 1){
            realWidthStart = curlawstart;
            realWidthStop  = curlawstop;
        }else{
            realWidthStart = 0 - topcWidth/2;
            realWidthStop  = topcWidth/2;
        }

        setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_cInfo.nGroupId) ;
        float temp;
        switch ( _eAngle) {
        case setup_PROBE_PART_SKEW_0:
            direction = 0;
            break;
        case setup_PROBE_PART_SKEW_90:
            direction = 0;
            realWidthStart -= indexOffset;
            realWidthStop  -= indexOffset;
            break;
        case setup_PROBE_PART_SKEW_180:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            break;
        case setup_PROBE_PART_SKEW_270:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            realWidthStart += indexOffset;
            realWidthStop  += indexOffset;
            break;
        default:
            Calculation = false;
            break;
        }

        if( realWidthStart >= _TOPCInfo.stopX || _TOPCInfo.startX >= realWidthStop){
            Calculation = false;
        }else{
            realWidthStart = (realWidthStart > _TOPCInfo.startX) ? realWidthStart : _TOPCInfo.startX;
            realWidthStop  = (realWidthStop < _TOPCInfo.stopX) ? realWidthStop : _TOPCInfo.stopX;
            if(fabs(realWidthStop - realWidthStart) < 1.0){
                Calculation = false;
            }
        }

        int pixelWidthStart, pixelWidthStop, pixelHeightStart, pixelHeightStop;
        if(Calculation){
            pixelWidthStart = (realWidthStart - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelWidthStop = (realWidthStop - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelHeightStart = (realHeightStart - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            pixelHeightStop = (realHeightStop - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            if(pixelWidthStop - pixelWidthStart > 2048){
                pixelHeightStop = pixelHeightStart + 2048;
            }
        }else{
            pixelWidthStart = 0;
            pixelWidthStop  = 10;
            realWidthStart  = _TOPCInfo.stopX + 1.0;
            realWidthStop   = _TOPCInfo.stopX + 11.0;
        }

        if(zoomflag == 1){
            if((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop))
                flag = 1;
            if(flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
            }
            _nStart   = _process->SAxisDistToIndex(curscanstart);
            _nScanend = _process->SAxisDistToIndex(curscanstop) - _nStart;

        }
        if(_scanner.fScanPos == _scanner.fScanStart2){
            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
        }

        if(zoomflag == 2 || zoomflag == 0){
            float rulerStart, rulerStop;
            switch ( _eAngle) {
            case setup_PROBE_PART_SKEW_0:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_90:
                rulerStart = realWidthStart + indexOffset;
                rulerStop  = realWidthStop + indexOffset;
                break;
            case setup_PROBE_PART_SKEW_180:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_270:
                rulerStart = realWidthStart - indexOffset;
                rulerStop  = realWidthStop - indexOffset;
                break;
            default:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            }
            emit signalIndexRangeMove( 0, 1, rulerStart, rulerStop);
        }else{

        }
        float step = 1.0;
        int HRange;
        if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(2, m_PosStart, m_PosStop);
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart + _nScanend;
                emit signalScanRangeMove(2, _nStart, _nStart + _nScanend);
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
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cscan_range == _nScanend){
                        m_PosStart = Csrc_start;
                        m_PosStop = Csrc_start + _nScanend;
                    }else{
                        Cscan_range = _nScanend;
                    }
                }
                int _nScanPos = _process->GetScanIndexPos();
                UpdateDisplayRange(2, _nWidth, _nScanPos);
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_start = m_PosStart;
                }
            }else{
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                    _nScanend = m_PosStop - m_PosStart;
                    emit signalScanRangeMove(2, m_PosStart, m_PosStop);
                }else{
                    m_PosStart = _nStart;
                    m_PosStop  = _nStart + _nScanend;
                    emit signalScanRangeMove(2, _nStart, _nStart + _nScanend);
                }
            }
            if(m_PosStop - m_PosStart > 2048){
                step = (float)2048/(m_PosStop - m_PosStart);
                HRange = 2048;
            }else{
                HRange = m_PosStop - m_PosStart;
            }
        }

        unsigned char* _pData;
        WDATA* pData;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, n;
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        int TmpValue;
        int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
        int _nScanMax = _process->GetRealScanMax() + _nScanOff;
        memset( src, 0x00, sizeof(src));
//        if(Calculation){
//            for(i = m_PosStart - 1, j = -1; i <= m_PosStop + 1 && j < (_nScanend)+1; i++ , j++){
//                if(i<0)
//                    continue;
//                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
//                    pData = _process->GetScanPosPointer(m_cInfo.nGroupId, i);
//                    int index_ = (j+1)*step;
//                    if(direction == 0){
//                        for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[index_][n] = TmpValue;
//                        }
//                    }else{
//                        for( k = pixelWidthStop - 1, n = 0; k >= pixelWidthStart; k--,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[index_][n] = TmpValue;
//                        }
//                    }

//                }
//            }
//        }

        if(Calculation){
            pData = _process->GetTOPCData(m_cInfo.nGroupId, pixelWidthStart, pixelWidthStop, pixelHeightStart,
                                          pixelHeightStop, direction);
            int recMax = m_pConfig->comTmp.nRecMax;
            for(i = m_PosStart - 1, j = -1; i <= m_PosStop + 1 && j < (_nScanend)+1; i++ , j++){
                if(i<0)
                    continue;
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    int _index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
                    int index_ = (j+1)*step;
                    for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
                        WDATA _nTmpValue = pData[n*recMax + _index];
                        TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
                        if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
                        src[index_][n] = TmpValue;
                    }
                }
            }
        }

        bool mergeCalculation  = true;
        float mergeGateStart   = m_pConfig->group[mergeGroupId].gate[0].fStart;
        float mergeGateWidth   = m_pConfig->group[mergeGroupId].gate[0].fWidth;
        float mergeGateStop    = mergeGateStart + mergeGateWidth;
        float mergeIndexOffset = m_pConfig->group[mergeGroupId].fIndexOffset;
        int mergeDirection;

        float mergeRealHeightStart, mergeRealHeightStop;
        float mergeRealWidthStart, mergeRealWidthStop;
        if( mergeGateStart >= _mergeTOPCInfo.stopY || mergeGateStop <= _mergeTOPCInfo.startY){
            mergeCalculation = false;
        }else{
            mergeRealHeightStart = ( mergeGateStart > _mergeTOPCInfo.startY) ? mergeGateStart : _mergeTOPCInfo.startY;
            mergeRealHeightStop  = ( mergeGateStop < _mergeTOPCInfo.stopY) ? mergeGateStop : _mergeTOPCInfo.stopY;
            if(fabs( mergeRealHeightStop - mergeRealHeightStart) < 1.0){
                mergeCalculation = false;
            }
        }
        if(zoomflag == 1){
            mergeRealWidthStart = curlawstart;
            mergeRealWidthStop  = curlawstop;
        }else{
            mergeRealWidthStart = 0 - topcWidth/2;
            mergeRealWidthStop  = topcWidth/2;
        }

        setup_PROBE_ANGLE _mergeAngle = _process->GetProbeAngle(mergeGroupId);
        switch ( _mergeAngle) {
        case setup_PROBE_PART_SKEW_0:
            mergeDirection = 0;
            break;
        case setup_PROBE_PART_SKEW_90:
            mergeDirection = 0;
            mergeRealWidthStart -= mergeIndexOffset;
            mergeRealWidthStop  -= mergeIndexOffset;
            break;
        case setup_PROBE_PART_SKEW_180:
            mergeDirection = 1;
            temp = - mergeRealWidthStart;
            mergeRealWidthStart = - mergeRealWidthStop;
            mergeRealWidthStop = temp;
            break;
        case setup_PROBE_PART_SKEW_270:
            mergeDirection = 1;
            temp = - mergeRealWidthStart;
            mergeRealWidthStart = - mergeRealWidthStop;
            mergeRealWidthStop = temp;
            mergeRealWidthStart += mergeIndexOffset;
            mergeRealWidthStop  += mergeIndexOffset;
            break;
        default:
            mergeCalculation = false;
            break;
        }

        if( mergeRealWidthStart >= _mergeTOPCInfo.stopX || _mergeTOPCInfo.startX >= mergeRealWidthStop){
            mergeCalculation = false;
        }else{
            mergeRealWidthStart = (mergeRealWidthStart > _mergeTOPCInfo.startX) ? mergeRealWidthStart : _mergeTOPCInfo.startX;
            mergeRealWidthStop  = (mergeRealWidthStop < _mergeTOPCInfo.stopX) ? mergeRealWidthStop : _mergeTOPCInfo.stopX;
            if(fabs(mergeRealWidthStop - mergeRealWidthStart) < 1.0){
                mergeCalculation = false;
            }
        }

        int mergePixelWidthStart, mergePixelWidthStop, mergePixelHeightStart, mergePixelHeightStop;
        if(mergeCalculation){
            mergePixelWidthStart = (mergeRealWidthStart - _mergeTOPCInfo.startX)/(_mergeTOPCInfo.stopX - _mergeTOPCInfo.startX)
                                * _mergeTOPCInfo.pixelWidth;
            mergePixelWidthStop = (mergeRealWidthStop - _mergeTOPCInfo.startX)/(_mergeTOPCInfo.stopX - _mergeTOPCInfo.startX)
                                * _mergeTOPCInfo.pixelWidth;
            mergePixelHeightStart = (mergeRealHeightStart - _mergeTOPCInfo.startY)/(_mergeTOPCInfo.stopY - _mergeTOPCInfo.startY)
                                * _mergeTOPCInfo.pixelHeigh;
            mergePixelHeightStop = (mergeRealHeightStop - _mergeTOPCInfo.startY)/(_mergeTOPCInfo.stopY - _mergeTOPCInfo.startY)
                                * _mergeTOPCInfo.pixelHeigh;
            if(mergePixelWidthStop - mergePixelWidthStart > 2048){
                mergePixelHeightStop = mergePixelHeightStart + 2048;
            }
        }else{
            mergePixelWidthStart = 0;
            mergePixelWidthStop  = 10;
            mergeRealWidthStart  = _mergeTOPCInfo.stopX + 1.0;
            mergeRealWidthStop   = _mergeTOPCInfo.stopX + 11.0;
        }

        WDATA* pMergeData;
        U8* _pMergeMarker = _process->GetScanMarker(mergeGroupId);
        int mi, mj, mk, mn;
        float _mergeScale = _process->GetRefGainScale(mergeGroupId);
        int mergeTmpValue;
        int mergeScanOff = _process->GetScanOff(mergeGroupId);
        int mergeScanMax = _process->GetRealScanMax() + mergeScanOff;
        memset( srcMerge, 0x00, sizeof(srcMerge));
//        if(mergeCalculation){
//            for(mi = m_PosStart - 1, mj = -1; mi <= m_PosStop + 1 && mj < (_nScanend)+1; mi++ , mj++){
//                if(mi<0)
//                    continue;
//                if(_pMergeMarker[mi] && mi >= mergeScanOff && mi < mergeScanMax){
//                    pMergeData = _process->GetScanPosPointer( mergeGroupId, mi);
//                    int index_ = (mj+1)*step;
//                    if(mergeDirection == 0){
//                        for( mk = mergePixelWidthStart, mn = 0; mk < mergePixelWidthStop; mk++,mn++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( mm = mergePixelHeightStart; mm < mergePixelHeightStop; mm++){
//                                int index = mm * _mergeTOPCInfo.pixelWidth + mk;
//                                index = _mergeTOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pMergeData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            mergeTmpValue =  _process->correctionPdata(_nTmpValue) * _mergeScale;
//                            if( mergeTmpValue > WAVE_MAX) mergeTmpValue = WAVE_MAX;
//                            srcMerge[index_][mn] = mergeTmpValue;
//                        }
//                    }else{
//                        for( mk = mergePixelWidthStop - 1, mn = 0; mk >= mergePixelWidthStart; mk--, mn++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( mm = mergePixelHeightStart; mm < mergePixelHeightStop; mm++){
//                                int index = mm * _mergeTOPCInfo.pixelWidth + mk;
//                                index = _mergeTOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pMergeData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }
//                            mergeTmpValue =  _process->correctionPdata(_nTmpValue) * _mergeScale;
//                            if( mergeTmpValue > WAVE_MAX) mergeTmpValue = WAVE_MAX;
//                            srcMerge[index_][mn] = mergeTmpValue;
//                        }
//                    }
//                }
//            }
//        }
        if(mergeCalculation){
            pMergeData = _process->GetTOPCData( mergeGroupId, mergePixelWidthStart, mergePixelWidthStop, mergePixelHeightStart,
                                          mergePixelHeightStop, mergeDirection);
            int recMax = m_pConfig->comTmp.nRecMax;
            for(mi = m_PosStart - 1, mj = -1; mi <= m_PosStop + 1 && mj < (_nScanend)+1; mi++ , mj++){
                if(mi<0)
                    continue;
                if(_pMergeMarker[mi] && mi >= mergeScanOff && mi < mergeScanMax){
                    int _index = _process->GetRealScanIndex(mergeGroupId, mi);
                    int index_ = (mj+1)*step;
                    for( mk = mergePixelWidthStart, mn = 0; mk < mergePixelWidthStop; mk++,mn++){
                        WDATA _nTmpValue = pMergeData[mn*recMax + _index];
                        mergeTmpValue =  _process->correctionPdata(_nTmpValue) * _mergeScale;
                        if( mergeTmpValue > WAVE_MAX) mergeTmpValue = WAVE_MAX;
                        srcMerge[index_][mn] = mergeTmpValue;
                    }
                }
            }
        }

        //处理像素不同的融合问题
        if( pixelWidthStop - pixelWidthStart > mergePixelWidthStop - mergePixelWidthStart){
            int y = pixelWidthStop - pixelWidthStart;
            int x = HRange;
            float fixStep = (float)(mergePixelWidthStop - mergePixelWidthStart) / y;
            for( int i = 0; i <= y; i++){
                int mergeIndex = i * fixStep;
                for( int j = 0; j <= x; j++){
                    if( srcMerge[j][mergeIndex] > src[j][i]){
                        src[j][i] = srcMerge[j][mergeIndex];
                    }
                }
            }
            _pData = pImage_->bits();
            memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
            TransformImage( x, y, src, pImage_->width(), pImage_->height(), pImage_);
        }else{
            int y = mergePixelWidthStop - mergePixelWidthStart;
            int x = HRange;
            float fixStep = (float)(pixelWidthStop - pixelWidthStart) / y;
            for( int i = 0; i <= y; i++){
                int mergeIndex = i * fixStep;
                for( int j = 0; j <= x; j++){
                    if( src[j][mergeIndex] > srcMerge[j][i]){
                        srcMerge[j][i] = src[j][mergeIndex];
                    }
                }
            }
            _pData = pImage_->bits();
            memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
            TransformImage( x, y, srcMerge, pImage_->width(), pImage_->height(), pImage_);
        }
        return;
    }

    //TOPC
    if( _TOPCInfo.TOPCStatus  || topcShow){
        //确定闸门位置和方向
        bool   Calculation = true;   //false 表示闸门在图像外面，绘制空白即可
        float  gateStart = m_pConfig->group[m_cInfo.nGroupId].gate[0].fStart;
        float  gateWidth = m_pConfig->group[m_cInfo.nGroupId].gate[0].fWidth;
        float  gateStop  = gateStart + gateWidth;
        float  indexOffset = m_pConfig->group[m_cInfo.nGroupId].fIndexOffset;
        double topcWidth = _TOPCInfo.TOPCWidth;
        int    direction;

        float realHeightStart, realHeightStop;
        float realWidthStart, realWidthStop;
        if( gateStart >= _TOPCInfo.stopY || gateStop <= _TOPCInfo.startY){
            Calculation = false;
        }else{
            realHeightStart = ( gateStart > _TOPCInfo.startY) ? gateStart : _TOPCInfo.startY;
            realHeightStop  = ( gateStop < _TOPCInfo.stopY) ? gateStop : _TOPCInfo.stopY;
            if(fabs(realHeightStop - realHeightStart) < 1.0){
                Calculation = false;
            }
        }
        if(zoomflag == 1){
            realWidthStart = curlawstart;
            realWidthStop  = curlawstop;
        }else{
            realWidthStart = 0 - topcWidth/2;
            realWidthStop  = topcWidth/2;
        }
        setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_cInfo.nGroupId) ;
        float temp;
        switch ( _eAngle) {
        case setup_PROBE_PART_SKEW_0:
            direction = 0;
            break;
        case setup_PROBE_PART_SKEW_90:
            direction = 0;
            realWidthStart -= indexOffset;
            realWidthStop  -= indexOffset;
            break;
        case setup_PROBE_PART_SKEW_180:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            break;
        case setup_PROBE_PART_SKEW_270:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            realWidthStart += indexOffset;
            realWidthStop  += indexOffset;
            break;
        default:
            Calculation = false;
            break;
        }

        if( realWidthStart >= _TOPCInfo.stopX || _TOPCInfo.startX >= realWidthStop){
            Calculation = false;
        }else{
            realWidthStart = (realWidthStart > _TOPCInfo.startX) ? realWidthStart : _TOPCInfo.startX;
            realWidthStop  = (realWidthStop < _TOPCInfo.stopX) ? realWidthStop : _TOPCInfo.stopX;
            if(fabs(realWidthStop - realWidthStart) < 1.0){
                Calculation = false;
            }
        }

        int pixelWidthStart, pixelWidthStop, pixelHeightStart, pixelHeightStop;
        if(Calculation){
            pixelWidthStart = (realWidthStart - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelWidthStop = (realWidthStop - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelHeightStart = (realHeightStart - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            pixelHeightStop = (realHeightStop - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            if(pixelWidthStop - pixelWidthStart > 2048){
                pixelHeightStop = pixelHeightStart + 2048;
            }
        }else{
            pixelWidthStart = 0;
            pixelWidthStop  = 10;
            realWidthStart  = _TOPCInfo.stopX + 1.0;
            realWidthStop   = _TOPCInfo.stopX + 11.0;
        }

        if(zoomflag == 1){
            if((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop))
                flag = 1;
            if(flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
            }
            _nStart   = _process->SAxisDistToIndex(curscanstart);
            _nScanend = _process->SAxisDistToIndex(curscanstop) - _nStart;

        }
        if(_scanner.fScanPos == _scanner.fScanStart2){
            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
        }
        //qDebug()<<"zoomflag"<<zoomflag;
        if(zoomflag == 2 || zoomflag == 0){
            float rulerStart, rulerStop;
            switch ( _eAngle) {
            case setup_PROBE_PART_SKEW_0:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_90:
                rulerStart = realWidthStart + indexOffset;
                rulerStop  = realWidthStop + indexOffset;
                break;
            case setup_PROBE_PART_SKEW_180:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_270:
                rulerStart = realWidthStart - indexOffset;
                rulerStop  = realWidthStop - indexOffset;
                break;
            default:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            }
            emit signalIndexRangeMove( 0, 1, rulerStart, rulerStop);
        }else{

        }
        float step = 1.0;
        int HRange;
        if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(2, m_PosStart, m_PosStop);
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart + _nScanend;
                emit signalScanRangeMove(2, _nStart, _nStart + _nScanend);
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
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cscan_range == _nScanend){
                        m_PosStart = Csrc_start;
                        m_PosStop = Csrc_start + _nScanend;
                    }else{
                        Cscan_range = _nScanend;
                    }
                }
                int _nScanPos = _process->GetScanIndexPos();
                UpdateDisplayRange(2, _nWidth, _nScanPos);
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_start = m_PosStart;
                }
            }else{
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                    _nScanend = m_PosStop - m_PosStart;
                    emit signalScanRangeMove(2, m_PosStart, m_PosStop);
                }else{
                    m_PosStart = _nStart;
                    m_PosStop  = _nStart + _nScanend;
                    emit signalScanRangeMove(2, _nStart, _nStart + _nScanend);
                }
            }
            HRange = m_PosStop - m_PosStart;
        }

        unsigned char* _pData;
        WDATA* pData;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, n;
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        int TmpValue;
        int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
        int _nScanMax = _process->GetRealScanMax() + _nScanOff;
        memset( src, 0x00, sizeof(src));
//        if(Calculation){
//            for(i = m_PosStart - 1, j = -1; i <= m_PosStop + 1 && j < (_nScanend)+1; i++ , j++){
//                if(i<0)
//                    continue;
//                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
//                    pData = _process->GetScanPosPointer(m_cInfo.nGroupId, i);
//                    int index_ = (j+1)*step;
//                    if(direction == 0){
//                        for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[index_][n] = TmpValue;
//                        }
//                    }else{
//                        for( k = pixelWidthStop - 1, n = 0; k >= pixelWidthStart; k--,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[index_][n] = TmpValue;
//                        }
//                    }

//                }
//            }
//        }

        if(Calculation){
            pData = _process->GetTOPCData(m_cInfo.nGroupId, pixelWidthStart, pixelWidthStop, pixelHeightStart,
                                          pixelHeightStop, direction);
            int recMax = m_pConfig->comTmp.nRecMax;
            for(i = m_PosStart - 1, j = -1; i <= m_PosStop + 1 && j < (_nScanend)+1; i++ , j++){
                if(i<0)
                    continue;
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    int _index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
                    int index_ = (j+1)*step;

                    for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
                        WDATA _nTmpValue = pData[n*recMax + _index];
                        TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
                        if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
                        src[index_][n] = TmpValue;
                    }
                }
            }
        }
        _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        TransformImage( HRange, pixelWidthStop- pixelWidthStart, src,
                        pImage_->width(), pImage_->height(), pImage_);
        return;
    }

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
        _nScanend   = _process->SAxisDistToIndex(curscanstop) - _nStart;
        _process->ChangeCscanIndexstart(&curlawstart);
        _process->ChangeCscanIndexstop(&curlawstop);
        lawstart = _process->GetLawStart();
        lawstop  = _process->GetLawStop();
        _scanner.fLawStart = lawstart2;
        _scanner.fLawStop = lawstop2;
    }
    //UpdateDisplayRange(2, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;

    }

    if(zoomflag == 2 || zoomflag == 0){
        LAW_CONFIG* _law = _process->GetLawConfig(m_cInfo.nGroupId);
        double startAngle,stopAngle;
        if( _law->eLawType == setup_LAW_TYPE_AZIMUTHAL){
            startAngle = _law->nAngleStartRefract / 10.0;
            stopAngle  = _law->nAngleStopRefract / 10.0;

        }else{
            int _nLawQty = _process->GetGroupLawQty(m_cInfo.nGroupId);
            startAngle = 0;
            stopAngle  = _nLawQty - 1;
            //qDebug()<<"nFirstElemFir"<<_law->nFirstElemFir<<_law->nLastElemFir<<_law->nElemStepFir;
        }
        emit signalIndexRangeMove( 0, 1, startAngle, stopAngle);
    }
    float step = 1.0;
    int HRange;
    if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
        if(zoomflag == 2){
            zoomflag = 0;
            flag = 0;
            m_PosStart = _process->SAxisDistToIndex(srcCstart);
            m_PosStop = _process->SAxisDistToIndex(srcCend) ;

            _nScanend = m_PosStop - m_PosStart;
            emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
        }else{
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
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
        if(_nWidth < _nScanend){
            _nScanend = _nWidth;
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cscan_range == _nScanend){
                    m_PosStart = Csrc_start;
                    m_PosStop = Csrc_start + _nScanend;
                }else{
                    Cscan_range = _nScanend;
                }
            }

            int _nScanPos	 = _process->GetScanIndexPos();
            UpdateDisplayRange(2, _nWidth , _nScanPos);
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_start = m_PosStart;
            }

        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend) ;

                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
            }
        }
//        if(m_PosStop - m_PosStart > 2048){
//            step = (float)2048/(m_PosStop - m_PosStart);
//            HRange = 2048;
//        }else{
            HRange = m_PosStop - m_PosStart;
        //}
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
    //QSize csize = QSize(_nScanend>0?_nScanend:1,(lawstop - lawstart)>0?(lawstop - lawstart):1);
    //QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    //unsigned char* _pData = TImage->bits() ;
    unsigned char* _pData;
    //memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    //U8* _pImageBits = TImage->bits() ;
    //int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	U32 _nTmpValue ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
    int _oldIndex = -1;
    int _newIndex = 0;
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = -1 ; i <= m_PosStop + 1&& j < (_nScanend)+1; i++ , j++) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
            _newIndex = (j+1)*step;
            if( _newIndex == _oldIndex){
                continue;
            }else{
                _oldIndex = _newIndex;
            }
			GetPixValueInfo(i, eGate_, _aGateValue);
            //int index_ = (j+1)*step;
            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
                _nTmpValue = getGateDataAmplitude(_aGateValue[k ])  * _fScale;

                if(_nTmpValue > WAVE_MAX)	_nTmpValue = WAVE_MAX;

                src[_newIndex][k-lawstart+1]=_nTmpValue;
                //memcpy(_pImageTmp, &m_pColor[_nTmpValue], 3);
			}
        }
	}
    _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );

        TransformImage( HRange,lawstop-lawstart,src,pImage_->width(),pImage_->height(),pImage_);
    //delete TImage;
}

void DopplerDrawCScanH::DrawGatePos(QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_)
{
	U32 _aGateValue1[256] ;
	U32 _aGateValue2[256] ;
	memset(_aGateValue1, 0x00, sizeof(_aGateValue1));
	memset(_aGateValue2, 0x00, sizeof(_aGateValue2));
    int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;
    static int flag = 0;
    //U8* _pImageBits = pImage_->bits() ;
    //U8* _pImageTmp , *_pColorTmp;
    //int _nWidthStep   = pImage_->bytesPerLine() ;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
    SCANNER& _scanner = m_pConfig->common.scanner;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	ParameterProcess* _process = ParameterProcess::Instance();
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int lawstart2 = lawstart;
    int lawstop2 = lawstop;
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    //二维扫查显示
    if( _scanner.eScanType == setup_SCAN_TYPE_RASTER){
        int indexStepBeam = _process->GetRasterIndexStepBeam(m_cInfo.nGroupId);
        int _IndexStartIndex = _process->TransforIndexPosToIndex( _process->GetIndexStartPos());
        int _IndexRangeIndex = _process->TransforIndexPosToIndex( _process->GetIndexEndPos());
        int _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        //float Indexlength = _process->GetRasterCoveredLength(m_cInfo.nGroupId);
        int heightToIndex = (_nHeight- _process->GetGroupLawQty(m_cInfo.nGroupId))/indexStepBeam;
        if( heightToIndex < 0){
            heightToIndex = 0;
        }
        if(zoomflag == 1){
            if(((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop)) ||
                   ((_scanner.fIndexPos > curIndexStartPos)&&(_scanner.fIndexPos < curIndexStopPos))){
                flag = 1;
            }
            if( flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
                if((_scanner.fIndexPos < curIndexStartPos+1)&&(_scanner.fIndexPos-1 >= _scanner.fIndexStart))
                    curIndexStartPos = _scanner.fIndexPos-1;
                if((_scanner.fIndexPos > curIndexStopPos-1)&&(_scanner.fIndexPos+1 <= _scanner.fIndexStop))
                    curIndexStopPos = _scanner.fIndexPos+1;
            }
            _nStart     = _process->SAxisDistToIndex(curscanstart);
            _nScanend   = _process->SAxisDistToIndex(curscanstop) - _nStart;
            _IndexStartIndex = _process->TransforIndexPosToIndex(curIndexStartPos);
            _IndexRangeIndex = _process->TransforIndexPosToIndex(curIndexStopPos) - _IndexStartIndex;
            _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        }
        if(_scanner.fScanPos == _scanner.fScanStart2){

            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
        }
        if(_scanner.fIndexPos == _scanner.fIndexStart){
            m_indexStartIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
            m_indexStopIndex = m_indexStartIndex + heightToIndex;
        }
        float Hstep = 1.0;
        int HRange;
        float Vstep = 1.0;
        int VRange;
        if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
            if(zoomflag == 2){
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend) ;
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
                zoomflag = 0;
                flag = 0;
                m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
                emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
            }
            if(_nWidth < _nScanend){
                if(_nWidth > 2048){
                    _nWidth = 2048;
                }
                Hstep = (float)_nWidth/_nScanend;
                HRange = _nWidth;
            }else{
                if(m_PosStop - m_PosStart > 2048){
                    Hstep = (float)2048/(m_PosStop - m_PosStart);
                    HRange = 2048;
                }else{
                    HRange = m_PosStop - m_PosStart;
                }
            }

            if(_nHeight < _IndexRangePixel){
                if(_nHeight > 2048){
                    _nHeight = 2048;
                }
                Vstep = (float)_nHeight/_IndexRangePixel;
                VRange = _nHeight;
            }else{
                if(_IndexRangePixel > 2048){
                    Vstep = (float)2048/_IndexRangePixel;
                    VRange = 2048;
                }else{
                    VRange = _IndexRangePixel;
                }
            }
        }else{
            if(_nWidth <_nScanend){
                _nScanend = _nWidth;
                if(zoomflag == 2){
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cscan_range == _nScanend){
                        m_PosStart = Csrc_start;
                        m_PosStop = Csrc_start + _nScanend;
                    }else{
                        Cscan_range = _nScanend;
                    }
                }
                int _nScanPos	 = _process->GetScanIndexPos();
                UpdateDisplayRange(2, _nWidth , _nScanPos) ;
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_start = m_PosStart;
                }
            }else{
                if(zoomflag == 2){
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend) ;
                    _nScanend = m_PosStop - m_PosStart;
                    emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
                }else{
                    m_PosStart = _nStart;
                    m_PosStop  = _nStart+_nScanend;
                    emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
                }
            }
            if(_nHeight < _IndexRangePixel){
                _IndexRangePixel = heightToIndex*indexStepBeam + _process->GetGroupLawQty(currentgroup);
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                    m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cindex_range == _IndexRangePixel){
                        m_indexStartIndex = Csrc_indexStart;
                        m_indexStopIndex = Csrc_indexStart + heightToIndex;
                    }else{
                        Cindex_range = _IndexRangePixel;
                    }
                }
                int _nIndexCurIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
                UpdateIndexRange(0, heightToIndex, _nIndexCurIndex);
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_indexStart = m_indexStartIndex;
                }
            }else{
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                    m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
    //                _IndexRangePixel = (m_indexStopIndex - m_indexStartIndex)*indexStepBeam +
    //                                    _process->GetGroupLawQty(m_cInfo.nGroupId);
                    emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
                }else{
                    m_indexStartIndex = _IndexStartIndex;
                    m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                    emit signalIndexRangeMove( 0, 0, m_indexStartIndex, m_indexStopIndex);
                }
            }
            HRange = m_PosStop - m_PosStart;
            VRange = _IndexRangePixel;
        }

        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, p;
        int Vindex_;
        memset(src,0x00,sizeof(src));
        WDATA* pData;
        pData = _process->GetRasterData(m_cInfo.nGroupId, setup_CSCAN_SOURCE_MODE (m_CScanInfo.eType));
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
            double _offsetbuff = _pConfig->rasterOffset[j];
            int _offset = scanQty * _offsetbuff /(_scanner.fScanStop - _scanner.fScanStart);
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                if( p - _offset < 0 || p - _offset >= scanQty){
                    continue;
                }
                int markerPos = markerBuff + k - _offset;

                if( _pMarker[markerPos]){
//                    if(eGate2_){
//                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
//                        GetPixValueInfo(markerPos, eGate2_, _aGateValue2);
//                        GetPixValueDistance(_aGateValue1, _aGateValue2);
//                    }else{
//                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
//                        GetPixValuePos(_aGateValue1);
//                    }
                    int Hindex_ = p*Hstep;
                    int markOffset = markerPos * indexStepBuff;
                    for(int w = 0; w < indexStepBuff; w++){
                        Vindex_ = (srcBuffIndex + w)*Vstep;
                        //src[p][srcBuffIndex + w] = _aGateValue1[w];
                        src[Hindex_][Vindex_] = pData[markOffset + w];
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        //int srcHeight = (j - 1)*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        TransformImage( HRange, Vindex_, src, pImage_->width(), pImage_->height(), pImage_);
        return;
    }
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
        _process->ChangeCscanIndexstart(&curlawstart);
        _process->ChangeCscanIndexstop(&curlawstop);
        lawstart = _process->GetLawStart();
        lawstop     =_process->GetLawStop();
        _scanner.fLawStart = lawstart2;
        _scanner.fLawStop = lawstop2;
    }
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;

    }
    float step = 1.0;
    int HRange;
    if( m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
        if(zoomflag == 2)
        {
            zoomflag = 0;
            flag = 0;
            m_PosStart = _process->SAxisDistToIndex(srcCstart);
            m_PosStop = _process->SAxisDistToIndex(srcCend);
            _nScanend = m_PosStop - m_PosStart;
            emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
        }
        else
        {
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
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
        if(_nWidth < _nScanend)
        {
            _nScanend = _nWidth;
            if(zoomflag == 2)
            {
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync)
            {
                if(Cscan_range == _nScanend)
                {
                    m_PosStart = Csrc_start;
                    m_PosStop = Csrc_start + _nScanend;
                }
                else
                {
                    Cscan_range = _nScanend;
                }
            }
            int _nScanPos	 = _process->GetScanIndexPos() ;
            UpdateDisplayRange(2, _nWidth , _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync)
            {
                Csrc_start = m_PosStart;
            }
        }
        else
        {
            if(zoomflag == 2)
            {
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(2, m_PosStart, m_PosStop) ;
            }
            else
            {
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(2, _nStart, _nStart+_nScanend) ;
            }
        }
        HRange = m_PosStop - m_PosStart;
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
    //QSize csize = QSize(_nScanend>0?_nScanend:1,(lawstop - lawstart)>0?(lawstop - lawstart):1);
    //QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    //unsigned char* _pData = TImage->bits() ;
    //memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    //U8* _pImageBits = TImage->bits() ;
    //int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;
	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetScanMax();
    int old_index = -1;
    int new_index = 0;
    float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = -1 ; i <= m_PosStop+1 && j < (_nScanend)+1; i++ , j++) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
            new_index = (j+1)*step;
            if( new_index == old_index){
                continue;
            }else{
                old_index = new_index;
            }
			if(eGate2_)	{
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
                GetPixValueDistance(_aGateValue1, _aGateValue2, _fScale);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
                GetPixValuePos(_aGateValue1, _aGateValue2, _fScale);
			}
            //int index_ = (j+1)*step;
            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp	   = _pImageBits + (k -lawstart) * _nWidthStep + j * 3 ;
                //_pColorTmp	   = m_pColor[_aGateValue1[k ]] ;
                 src[new_index][k-lawstart+1]=_aGateValue1[k ];
                //memcpy(_pImageTmp, _pColorTmp, 3);
			}
        }
//        else {
//			_pImageTmp = _pImageBits + j * 3 ;
//			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
//                for(k = lawstart ; k < lawstop ; k++)
//				{
//                    _pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
//					memset(_pImageTmp, 0x00, 3);
//				}
//			}
//		}
	}
    unsigned char* _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
        TransformImage( HRange,lawstop-lawstart,src,pImage_->width(),pImage_->height(),pImage_);
    //delete TImage;
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

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    if(_pConfig->group[m_cInfo.nGroupId].m_mode==D_MODE)
    {
    _pConfig->group[m_cInfo.nGroupId].DrawCviewflage=true;
    }

	for(int i = 0 ; i < _nBeamQty ; i++)
	{
		_process->GetGatePeakInfos(m_cInfo.nGroupId, nScanPos_, i, _info);
        pBuff_[i] = (_info[_eGate].fH * 1000);
        pBuff_[i] = combinedGateDate( pBuff_[i], _info[_eGate].iY);
	}   
    _pConfig->group[m_cInfo.nGroupId].DrawCviewflage=false;

}

void DopplerDrawCScanH::GetPixValuePos(U32* pBuff_, U32* pBuff2_, float GainScale_)
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
        _nPeak = getGateDataAmplitude(_nData) * GainScale_;

		if(_nPeak < _nGateHeight)
		{
			//pBuff_[i] = 255 ;
			pBuff_[i] = 0 ;
            pBuff2_[i] = 0;
		}
		else
		{
            _nDepth = getGateDataDepth(_nData);
            pBuff2_[i] = _nDepth / 1000;
			if(_nDepth < _nMin)
				pBuff_[i] = 0 ;
			else if(_nDepth > _nMax)
                pBuff_[i] = WAVE_MAX;
			else
			{
                pBuff_[i] = WAVE_MAX * (_nDepth - _nMin) / _nRange ;
                if(pBuff_[i] > WAVE_MAX)
                    pBuff_[i] = WAVE_MAX;
			}
		}
	}
}

void DopplerDrawCScanH::GetPixValueDistance(U32* pBuff1_ , U32* pBuff2_, float GainScale_)
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
        _nPeak1 = getGateDataAmplitude(_nData1) * GainScale_;
        _nPeak2 = getGateDataAmplitude(_nData2) * GainScale_;

		if(_nPeak1 >= _nGateHeight1 && _nPeak2 >= _nGateHeight2)
		{
            _nDepth1 = getGateDataDepth(_nData1);
            _nDepth2 = getGateDataDepth(_nData2);

			_nDepth1 = abs((int)(_nDepth2 - _nDepth1));
            pBuff2_[i] = _nDepth1 / 100;
			if(_nDepth1 < _nMin)
				pBuff1_[i] = 0 ;
			else if(_nDepth1 > _nMax)
                pBuff1_[i] = WAVE_MAX;
			else
			{
                pBuff1_[i] = WAVE_MAX * (_nDepth1 - _nMin) / _nRange ;
                if(pBuff1_[i] > WAVE_MAX)
                    pBuff1_[i] = WAVE_MAX;
			}
		}
		else
		{
            pBuff1_[i] = 0;
            pBuff2_[i] = 0;
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
    static int flag = 0;
    //U8* _pImageBits = pImage_->bits() ;
    //U8* _pImageTmp1 , *_pImageTmp2;
    //int _nWidthStep   = pImage_->bytesPerLine() ;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	ParameterProcess* _process = ParameterProcess::Instance();
    SCANNER& _scanner = m_pConfig->common.scanner;
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int lawstart2 = lawstart;
    int lawstop2 = lawstop;
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    //二维扫查显示
    if( _scanner.eScanType == setup_SCAN_TYPE_RASTER){
        int indexStepBeam = _process->GetRasterIndexStepBeam(m_cInfo.nGroupId);
        int _IndexStartIndex = _process->TransforIndexPosToIndex( _process->GetIndexStartPos());
        int _IndexRangeIndex = _process->TransforIndexPosToIndex( _process->GetIndexEndPos());
        int _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        //float Indexlength = _process->GetRasterCoveredLength(m_cInfo.nGroupId);
        int heightToIndex = (_nWidth - _process->GetGroupLawQty(m_cInfo.nGroupId))/indexStepBeam;
        if( heightToIndex < 0){
            heightToIndex = 0;
        }
        if(zoomflag == 1){
            if(((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop)) ||
                   ((_scanner.fIndexPos > curIndexStartPos)&&(_scanner.fIndexPos < curIndexStopPos))){
                flag = 1;
            }
            if( flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
                if((_scanner.fIndexPos < curIndexStartPos+1)&&(_scanner.fIndexPos-1 >= _scanner.fIndexStart))
                    curIndexStartPos = _scanner.fIndexPos-1;
                if((_scanner.fIndexPos > curIndexStopPos-1)&&(_scanner.fIndexPos+1 <= _scanner.fIndexStop))
                    curIndexStopPos = _scanner.fIndexPos+1;
            }
            _nStart     = _process->SAxisDistToIndex(curscanstart);
            _nScanend   = _process->SAxisDistToIndex(curscanstop) - _nStart;
            _IndexStartIndex = _process->TransforIndexPosToIndex(curIndexStartPos);
            _IndexRangeIndex = _process->TransforIndexPosToIndex(curIndexStopPos) - _IndexStartIndex;
            _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        }
        if(_scanner.fScanPos == _scanner.fScanStart2){

            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nHeight;
        }
        if(_scanner.fIndexPos == _scanner.fIndexStart){
            m_indexStartIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
            m_indexStopIndex = m_indexStartIndex + heightToIndex;
        }
        if(_nHeight <_nScanend){
            _nScanend = _nHeight;
            if(zoomflag == 2){
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cscan_range == _nScanend){
                    m_PosStart = Csrc_start;
                    m_PosStop = Csrc_start + _nScanend;
                }else{
                    Cscan_range = _nScanend;
                }
            }
            int _nScanPos	 = _process->GetScanIndexPos();
            UpdateDisplayRange(3, _nHeight, _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_start = m_PosStart;
            }
        }else{
            if(zoomflag == 2){
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend) ;
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
            }
        }
        if(_nWidth < _IndexRangePixel){
            _IndexRangePixel = heightToIndex*indexStepBeam + _process->GetGroupLawQty(currentgroup);
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cindex_range == _IndexRangePixel){
                    m_indexStartIndex = Csrc_indexStart;
                    m_indexStopIndex = Csrc_indexStart + heightToIndex;
                }else{
                    Cindex_range = _IndexRangePixel;
                }
            }
            int _nIndexCurIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
            UpdateIndexRange(2, heightToIndex, _nIndexCurIndex);
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_indexStart = m_indexStartIndex;
            }
        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
//                _IndexRangePixel = (m_indexStopIndex - m_indexStartIndex)*indexStepBeam +
//                                    _process->GetGroupLawQty(m_cInfo.nGroupId);
                emit signalIndexRangeMove( 2, 0, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove( 2, 0, m_indexStartIndex, m_indexStopIndex);
            }
        }
        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, p;
//        int indexStepDrawBeam = indexStepBeam;
//        if(indexStepDrawBeam > _process->GetGroupLawQty(m_cInfo.nGroupId)){
//            indexStepDrawBeam = _process->GetGroupLawQty(m_cInfo.nGroupId);
//        }
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        U32 _nTmpValue;
//        PEAK_CONFIG _info[setup_GATE_MAX];
//        setup_GATE_NAME _eGate;

//        switch(eGate_)
//        {
//        case GATE_A: _eGate = setup_GATE_A; break;
//        case GATE_B: _eGate = setup_GATE_B; break;
//        case GATE_I: _eGate = setup_GATE_I; break;
//        default:  return;
//        }
        memset(src,0x00,sizeof(src));
        WDATA* pData;
        pData = _process->GetRasterData(m_cInfo.nGroupId, setup_CSCAN_SOURCE_MODE (m_CScanInfo.eType));
        int transf = m_PosStop - m_PosStart;
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
            double _offsetbuff = _pConfig->rasterOffset[j];
            int _offset = scanQty * _offsetbuff /(_scanner.fScanStop - _scanner.fScanStart);
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                if( p - _offset < 0 || p - _offset >= scanQty){
                    continue;
                }
                int markerPos = markerBuff + k - _offset;

                if( _pMarker[markerPos]){
                    for(int w = 0; w < indexStepBuff; w++){
                        int markOffset = markerPos * indexStepBuff;
                        //_process->GetGatePeakInfos(m_cInfo.nGroupId, markerPos, w, _info);
                        //_nTmpValue = getGateDataAmplitude(_info[_eGate].iY) * _fScale;
                        _nTmpValue =  _process->correctionPdata(pData[markOffset + w]) * _fScale;
                        if(_nTmpValue > WAVE_MAX)	_nTmpValue = WAVE_MAX;

                        src[srcBuffIndex + w][transf - p] = _nTmpValue;
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        int srcHeight = (j-1)*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        TransformImage( srcHeight, p, src, pImage_->width(), pImage_->height(), pImage_);
        return;
    }

    //TOPC融合
    TOPC_INFO& _TOPCInfo  = m_pConfig->group[m_cInfo.nGroupId].TopCInfo;
    if( m_pConfig->common.TOPCMergeValid && _TOPCInfo.TOPCMergeStatus){
        int mergeGroupId = _TOPCInfo.TOPCMergeRefer;
        TOPC_INFO& _mergeTOPCInfo = m_pConfig->group[mergeGroupId].TopCInfo;
        double topcWidth = (_TOPCInfo.TOPCWidth > _mergeTOPCInfo.TOPCWidth) ? _TOPCInfo.TOPCWidth : _mergeTOPCInfo.TOPCWidth;
        bool   Calculation = true;   //false 表示闸门在图像外面，绘制空白即可
        float  gateStart = m_pConfig->group[m_cInfo.nGroupId].gate[0].fStart;
        float  gateWidth = m_pConfig->group[m_cInfo.nGroupId].gate[0].fWidth;
        float  gateStop  = gateStart + gateWidth;
        float  indexOffset = m_pConfig->group[m_cInfo.nGroupId].fIndexOffset;
        int    direction;

        float realHeightStart, realHeightStop;
        float realWidthStart, realWidthStop;
        if( gateStart >= _TOPCInfo.stopY || gateStop <= _TOPCInfo.startY){
            Calculation = false;
        }else{
            realHeightStart = ( gateStart > _TOPCInfo.startY) ? gateStart : _TOPCInfo.startY;
            realHeightStop  = ( gateStop < _TOPCInfo.stopY) ? gateStop : _TOPCInfo.stopY;
            if(fabs(realHeightStop - realHeightStart) < 1.0){
                Calculation = false;
            }
        }
        if(zoomflag == 1){
            realWidthStart = curlawstart;
            realWidthStop  = curlawstop;
        }else{
            realWidthStart = 0 - topcWidth/2;
            realWidthStop  = topcWidth/2;
        }

        setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_cInfo.nGroupId) ;
        float temp;
        switch ( _eAngle) {
        case setup_PROBE_PART_SKEW_0:
            direction = 0;
            break;
        case setup_PROBE_PART_SKEW_90:
            direction = 0;
            realWidthStart -= indexOffset;
            realWidthStop  -= indexOffset;
            break;
        case setup_PROBE_PART_SKEW_180:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            break;
        case setup_PROBE_PART_SKEW_270:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            realWidthStart += indexOffset;
            realWidthStop  += indexOffset;
            break;
        default:
            Calculation = false;
            break;
        }

        if( realWidthStart >= _TOPCInfo.stopX || _TOPCInfo.startX >= realWidthStop){
            Calculation = false;
        }else{
            realWidthStart = (realWidthStart > _TOPCInfo.startX) ? realWidthStart : _TOPCInfo.startX;
            realWidthStop  = (realWidthStop < _TOPCInfo.stopX) ? realWidthStop : _TOPCInfo.stopX;
            if(fabs(realWidthStop - realWidthStart) < 1.0){
                Calculation = false;
            }
        }

        int pixelWidthStart, pixelWidthStop, pixelHeightStart, pixelHeightStop;
        if(Calculation){
            pixelWidthStart = (realWidthStart - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelWidthStop = (realWidthStop - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelHeightStart = (realHeightStart - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            pixelHeightStop = (realHeightStop - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            if(pixelWidthStop - pixelWidthStart > 2048){
                pixelHeightStop = pixelHeightStart + 2048;
            }
        }else{
            pixelWidthStart = 0;
            pixelWidthStop  = 10;
            realWidthStart  = _TOPCInfo.stopX + 1.0;
            realWidthStop   = _TOPCInfo.stopX + 11.0;
        }

        if(zoomflag == 1){
            if((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop))
                flag = 1;
            if(flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
            }
            _nStart   = _process->SAxisDistToIndex(curscanstart);
            _nScanend =  _process->SAxisDistToIndex(curscanstop) - _nStart;
        }
        if(_scanner.fScanPos == _scanner.fScanStart2){
            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
        }
        if(zoomflag == 2 || zoomflag == 0){
            float rulerStart, rulerStop;
            switch ( _eAngle) {
            case setup_PROBE_PART_SKEW_0:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_90:
                rulerStart = realWidthStart + indexOffset;
                rulerStop  = realWidthStop + indexOffset;
                break;
            case setup_PROBE_PART_SKEW_180:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_270:
                rulerStart = realWidthStart - indexOffset;
                rulerStop  = realWidthStop - indexOffset;
                break;
            default:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            }
            emit signalIndexRangeMove( 2, 1, rulerStart, rulerStop);
        }else{

        }
        float step = 1.0;
        int VRange;
        if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
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
            if(_nHeight < _nScanend){
                _nScanend = _nHeight;
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cscan_range == _nScanend){
                        m_PosStart = Csrc_start;
                        m_PosStop = Csrc_start + _nScanend;
                    }else{
                        Cscan_range = _nScanend;
                    }
                }
                int _nScanPos	 = _process->GetScanIndexPos() ;
                UpdateDisplayRange(3, _nHeight , _nScanPos) ;
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_start = m_PosStart;
                }
            }else{
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                    _nScanend = m_PosStop - m_PosStart;
                    emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
                }else{
                    m_PosStart = _nStart;
                    m_PosStop  = _nStart+_nScanend;
                    emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
                }
            }
            if(m_PosStop - m_PosStart > 2048){
                step = (float)2048/(m_PosStop - m_PosStart);
                VRange = 2048;
            }else{
                VRange = m_PosStop - m_PosStart;
            }
        }

        unsigned char* _pData;
        WDATA* pData;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, n;
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        int TmpValue;
        int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
        int _nScanMax = _process->GetRealScanMax() + _nScanOff;
        memset( src, 0x00, sizeof(src));
//        if(Calculation){
//            for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--){
//                if(i<0)
//                    continue;
//                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
//                    pData = _process->GetScanPosPointer(m_cInfo.nGroupId, i);
//                    int index_ = (j+1)*step;
//                    if(direction == 0){
//                        for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }
//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[n][index_] = TmpValue;
//                        }
//                    }else{
//                        for( k = pixelWidthStop - 1, n = 0; k >= pixelWidthStart; k--,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[n][index_] = TmpValue;
//                        }
//                    }
//                }
//            }
//        }
        if(Calculation){
            pData = _process->GetTOPCData(m_cInfo.nGroupId, pixelWidthStart, pixelWidthStop, pixelHeightStart,
                                          pixelHeightStop, direction);
            int recMax = m_pConfig->comTmp.nRecMax;
            for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--){
                if(i<0)
                    continue;
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    int _index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
                    int index_ = (j+1)*step;
                    for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
                        WDATA _nTmpValue = pData[n*recMax + _index];
                        TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
                        if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
                        src[n][index_] = TmpValue;
                    }
                }
            }
        }

        bool mergeCalculation  = true;
        float mergeGateStart   = m_pConfig->group[mergeGroupId].gate[0].fStart;
        float mergeGateWidth   = m_pConfig->group[mergeGroupId].gate[0].fWidth;
        float mergeGateStop    = mergeGateStart + mergeGateWidth;
        float mergeIndexOffset = m_pConfig->group[mergeGroupId].fIndexOffset;
        int mergeDirection;

        float mergeRealHeightStart, mergeRealHeightStop;
        float mergeRealWidthStart, mergeRealWidthStop;
        if( mergeGateStart >= _mergeTOPCInfo.stopY || mergeGateStop <= _mergeTOPCInfo.startY){
            mergeCalculation = false;
        }else{
            mergeRealHeightStart = ( mergeGateStart > _mergeTOPCInfo.startY) ? mergeGateStart : _mergeTOPCInfo.startY;
            mergeRealHeightStop  = ( mergeGateStop < _mergeTOPCInfo.stopY) ? mergeGateStop : _mergeTOPCInfo.stopY;
            if(fabs( mergeRealHeightStop - mergeRealHeightStart) < 1.0){
                mergeCalculation = false;
            }
        }
        if(zoomflag == 1){
            mergeRealWidthStart = curlawstart;
            mergeRealWidthStop  = curlawstop;
        }else{
            mergeRealWidthStart = 0 - topcWidth/2;
            mergeRealWidthStop  = topcWidth/2;
        }

        setup_PROBE_ANGLE _mergeAngle = _process->GetProbeAngle(mergeGroupId);
        switch ( _mergeAngle) {
        case setup_PROBE_PART_SKEW_0:
            mergeDirection = 0;
            break;
        case setup_PROBE_PART_SKEW_90:
            mergeDirection = 0;
            mergeRealWidthStart -= mergeIndexOffset;
            mergeRealWidthStop  -= mergeIndexOffset;
            break;
        case setup_PROBE_PART_SKEW_180:
            mergeDirection = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            break;
        case setup_PROBE_PART_SKEW_270:
            mergeDirection = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            mergeRealWidthStart += mergeIndexOffset;
            mergeRealWidthStop  += mergeIndexOffset;
            break;
        default:
            mergeCalculation = false;
            break;
        }

        if( mergeRealWidthStart >= _mergeTOPCInfo.stopX || _mergeTOPCInfo.startX >= mergeRealWidthStop){
            mergeCalculation = false;
        }else{
            mergeRealWidthStart = (mergeRealWidthStart > _mergeTOPCInfo.startX) ? mergeRealWidthStart : _mergeTOPCInfo.startX;
            mergeRealWidthStop  = (mergeRealWidthStop < _mergeTOPCInfo.stopX) ? mergeRealWidthStop : _mergeTOPCInfo.stopX;
            if(fabs(mergeRealWidthStop - mergeRealWidthStart) < 1.0){
                mergeCalculation = false;
            }
        }

        int mergePixelWidthStart, mergePixelWidthStop, mergePixelHeightStart, mergePixelHeightStop;
        if(mergeCalculation){
            mergePixelWidthStart = (mergeRealWidthStart - _mergeTOPCInfo.startX)/(_mergeTOPCInfo.stopX - _mergeTOPCInfo.startX)
                                * _mergeTOPCInfo.pixelWidth;
            mergePixelWidthStop = (mergeRealWidthStop - _mergeTOPCInfo.startX)/(_mergeTOPCInfo.stopX - _mergeTOPCInfo.startX)
                                * _mergeTOPCInfo.pixelWidth;
            mergePixelHeightStart = (mergeRealHeightStart - _mergeTOPCInfo.startY)/(_mergeTOPCInfo.stopY - _mergeTOPCInfo.startY)
                                * _mergeTOPCInfo.pixelHeigh;
            mergePixelHeightStop = (mergeRealHeightStop - _mergeTOPCInfo.startY)/(_mergeTOPCInfo.stopY - _mergeTOPCInfo.startY)
                                * _mergeTOPCInfo.pixelHeigh;
            if(mergePixelWidthStop - mergePixelWidthStart > 2048){
                mergePixelHeightStop = mergePixelHeightStart + 2048;
            }
        }else{
            mergePixelWidthStart = 0;
            mergePixelWidthStop  = 10;
            mergeRealWidthStart  = _mergeTOPCInfo.stopX + 1.0;
            mergeRealWidthStop   = _mergeTOPCInfo.stopX + 11.0;
        }

        WDATA* pMergeData;
        U8* _pMergeMarker = _process->GetScanMarker(mergeGroupId);
        int mi, mj, mk, mn;
        float _mergeScale = _process->GetRefGainScale(mergeGroupId);
        int mergeTmpValue;
        int mergeScanOff = _process->GetScanOff(mergeGroupId);
        int mergeScanMax = _process->GetRealScanMax() + mergeScanOff;
        memset( srcMerge, 0x00, sizeof(srcMerge));
//        if(mergeCalculation){
//            for(mi = m_PosStart - 1, mj = _nScanend; mi <= m_PosStop + 1 && mj >= -1; mi++ , mj--){
//                if(mi<0)
//                    continue;
//                if(_pMergeMarker[mi] && mi >= mergeScanOff && mi < mergeScanMax){
//                    pMergeData = _process->GetScanPosPointer( mergeGroupId, mi);
//                    int index_ = (mj+1)*step;
//                    if(mergeDirection == 0){
//                        for( mk = mergePixelWidthStart, mn = 0; mk < mergePixelWidthStop; mk++,mn++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( mm = mergePixelHeightStart; mm < mergePixelHeightStop; mm++){
//                                int index = mm * _mergeTOPCInfo.pixelWidth + mk;
//                                index = _mergeTOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pMergeData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            mergeTmpValue =  _process->correctionPdata(_nTmpValue) * _mergeScale;
//                            if( mergeTmpValue > WAVE_MAX) mergeTmpValue = WAVE_MAX;
//                            srcMerge[mn][index_] = mergeTmpValue;
//                        }
//                    }else{
//                        for( mk = mergePixelWidthStop - 1, mn = 0; mk >= mergePixelWidthStart; mk--, mn++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( mm = mergePixelHeightStart; mm < mergePixelHeightStop; mm++){
//                                int index = mm * _mergeTOPCInfo.pixelWidth + mk;
//                                index = _mergeTOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pMergeData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }
//                            mergeTmpValue =  _process->correctionPdata(_nTmpValue) * _mergeScale;
//                            if( mergeTmpValue > WAVE_MAX) mergeTmpValue = WAVE_MAX;
//                            srcMerge[mn][index_] = mergeTmpValue;
//                        }
//                    }
//                }
//            }
//        }
        if(mergeCalculation){
            pMergeData = _process->GetTOPCData( mergeGroupId, mergePixelWidthStart, mergePixelWidthStop, mergePixelHeightStart,
                                          mergePixelHeightStop, mergeDirection);
            int recMax = m_pConfig->comTmp.nRecMax;
            for(mi = m_PosStart - 1, mj = _nScanend; mi <= m_PosStop + 1 && mj >= -1; mi++ , mj--){
                if(mi<0)
                    continue;
                if(_pMergeMarker[mi] && mi >= mergeScanOff && mi < mergeScanMax){
                    int _index = _process->GetRealScanIndex(mergeGroupId, mi);
                    int index_ = (mj+1)*step;
                    for( mk = mergePixelWidthStart, mn = 0; mk < mergePixelWidthStop; mk++,mn++){
                        WDATA _nTmpValue = pMergeData[mn*recMax + _index];
                        mergeTmpValue =  _process->correctionPdata(_nTmpValue) * _mergeScale;
                        if( mergeTmpValue > WAVE_MAX) mergeTmpValue = WAVE_MAX;
                        srcMerge[mn][index_] = mergeTmpValue;
                    }
                }
            }
        }

        //处理像素不同的融合问题
        if( pixelWidthStop - pixelWidthStart > mergePixelWidthStop - mergePixelWidthStart){
            int x = pixelWidthStop - pixelWidthStart;
            int y = VRange;
            float fixStep = (float)(mergePixelWidthStop - mergePixelWidthStart) / x;
            for( int i = 0; i <= x; i++){
                int mergeIndex = i * fixStep;
                for( int j = 0; j <= y; j++){
                    if(srcMerge[mergeIndex][j] > src[i][j]){
                        src[i][j] = srcMerge[mergeIndex][j];
                    }
                }
            }
            _pData = pImage_->bits();
            memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
            TransformImage( x, y, src, pImage_->width(), pImage_->height(), pImage_);
        }else{
            int x = mergePixelWidthStop - mergePixelWidthStart;
            int y = VRange;
            float fixStep = (float)(pixelWidthStop - pixelWidthStart) / x;
            for( int i = 0; i <= x; i++){
                int mergeIndex = i * fixStep;
                for( int j = 0; j <= y; j++){
                    if(src[mergeIndex][j] > srcMerge[i][j]){
                        srcMerge[i][j] = src[mergeIndex][j];
                    }
                }
            }
            _pData = pImage_->bits();
            memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
            TransformImage( x, y, srcMerge, pImage_->width(), pImage_->height(), pImage_);
        }
        return;
    }
    //TOPC
    if( _TOPCInfo.TOPCStatus){
        //确定闸门位置和方向
        bool   Calculation = true;   //false 表示闸门在图像外面，绘制空白即可
        float  gateStart = m_pConfig->group[m_cInfo.nGroupId].gate[0].fStart;
        float  gateWidth = m_pConfig->group[m_cInfo.nGroupId].gate[0].fWidth;
        float  gateStop  = gateStart + gateWidth;
        float  indexOffset = m_pConfig->group[m_cInfo.nGroupId].fIndexOffset;
        double topcWidth = _TOPCInfo.TOPCWidth;
        int    direction;

        float realHeightStart, realHeightStop;
        float realWidthStart, realWidthStop;
        if( gateStart >= _TOPCInfo.stopY || gateStop <= _TOPCInfo.startY){
            Calculation = false;
        }else{
            realHeightStart = ( gateStart > _TOPCInfo.startY) ? gateStart : _TOPCInfo.startY;
            realHeightStop  = ( gateStop < _TOPCInfo.stopY) ? gateStop : _TOPCInfo.stopY;
            if(fabs(realHeightStop - realHeightStart) < 1.0){
                Calculation = false;
            }
        }
        if(zoomflag == 1){
            realWidthStart = curlawstart;
            realWidthStop  = curlawstop;
        }else{
            realWidthStart = 0 - topcWidth/2;
            realWidthStop  = topcWidth/2;
        }

        setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_cInfo.nGroupId) ;
        float temp;
        switch ( _eAngle) {
        case setup_PROBE_PART_SKEW_0:
            direction = 0;
            break;
        case setup_PROBE_PART_SKEW_90:
            direction = 0;
            realWidthStart -= indexOffset;
            realWidthStop  -= indexOffset;
            break;
        case setup_PROBE_PART_SKEW_180:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            break;
        case setup_PROBE_PART_SKEW_270:
            direction = 1;
            temp = - realWidthStart;
            realWidthStart = - realWidthStop;
            realWidthStop = temp;
            realWidthStart += indexOffset;
            realWidthStop  += indexOffset;
            break;
        default:
            Calculation = false;
            break;
        }

        if( realWidthStart >= _TOPCInfo.stopX || _TOPCInfo.startX >= realWidthStop){
            Calculation = false;
        }else{
            realWidthStart = (realWidthStart > _TOPCInfo.startX) ? realWidthStart : _TOPCInfo.startX;
            realWidthStop  = (realWidthStop < _TOPCInfo.stopX) ? realWidthStop : _TOPCInfo.stopX;
            if(fabs(realWidthStop - realWidthStart) < 1.0){
                Calculation = false;
            }
        }

        int pixelWidthStart, pixelWidthStop, pixelHeightStart, pixelHeightStop;
        if(Calculation){
            pixelWidthStart = (realWidthStart - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelWidthStop = (realWidthStop - _TOPCInfo.startX)/(_TOPCInfo.stopX - _TOPCInfo.startX)
                                * _TOPCInfo.pixelWidth;
            pixelHeightStart = (realHeightStart - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            pixelHeightStop = (realHeightStop - _TOPCInfo.startY)/(_TOPCInfo.stopY - _TOPCInfo.startY)
                                * _TOPCInfo.pixelHeigh;
            if(pixelWidthStop - pixelWidthStart > 2048){
                pixelHeightStop = pixelHeightStart + 2048;
            }
        }else{
            pixelWidthStart = 0;
            pixelWidthStop  = 10;
            realWidthStart  = _TOPCInfo.stopX + 1.0;
            realWidthStop   = _TOPCInfo.stopX + 11.0;
        }

        if(zoomflag == 1){
            if((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop))
                flag = 1;
            if(flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
            }
            _nStart   = _process->SAxisDistToIndex(curscanstart);
            _nScanend =  _process->SAxisDistToIndex(curscanstop) - _nStart;
        }
        if(_scanner.fScanPos == _scanner.fScanStart2){
            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;
        }
        if(zoomflag == 2 || zoomflag == 0){
            float rulerStart, rulerStop;
            switch ( _eAngle) {
            case setup_PROBE_PART_SKEW_0:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_90:
                rulerStart = realWidthStart + indexOffset;
                rulerStop  = realWidthStop + indexOffset;
                break;
            case setup_PROBE_PART_SKEW_180:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            case setup_PROBE_PART_SKEW_270:
                rulerStart = realWidthStart - indexOffset;
                rulerStop  = realWidthStop - indexOffset;
                break;
            default:
                rulerStart = realWidthStart;
                rulerStop  = realWidthStop;
                break;
            }
            emit signalIndexRangeMove( 2, 1, rulerStart, rulerStop);
        }else{

        }
        float step = 1.0;
        int VRange;
        if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
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
            if(_nHeight < _nScanend){
                _nScanend = _nHeight;
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                }
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    if(Cscan_range == _nScanend){
                        m_PosStart = Csrc_start;
                        m_PosStop = Csrc_start + _nScanend;
                    }else{
                        Cscan_range = _nScanend;
                    }
                }
                int _nScanPos	 = _process->GetScanIndexPos() ;
                UpdateDisplayRange(3, _nHeight , _nScanPos) ;
                if(_pConfig->AppEvn.bSAxisCursorSync){
                    Csrc_start = m_PosStart;
                }
            }else{
                if(zoomflag == 2){
                    zoomflag = 0;
                    flag = 0;
                    m_PosStart = _process->SAxisDistToIndex(srcCstart);
                    m_PosStop = _process->SAxisDistToIndex(srcCend);
                    _nScanend = m_PosStop - m_PosStart;
                    emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
                }else{
                    m_PosStart = _nStart;
                    m_PosStop  = _nStart+_nScanend;
                    emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
                }
            }
            VRange = m_PosStop - m_PosStart;
        }

        unsigned char* _pData;
        WDATA* pData;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, n;
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        int TmpValue;
        int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
        int _nScanMax = _process->GetRealScanMax() + _nScanOff;
        memset( src, 0x00, sizeof(src));
//        if(Calculation){
//            for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--){
//                if(i<0)
//                    continue;
//                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
//                    pData = _process->GetScanPosPointer(m_cInfo.nGroupId, i);
//                    int index_ = (j+1)*step;
//                    if(direction == 0){
//                        for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }
//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[n][index_] = TmpValue;
//                        }
//                    }else{
//                        for( k = pixelWidthStop - 1, n = 0; k >= pixelWidthStart; k--,n++){
//                            WDATA buff = 0;
//                            WDATA _nTmpValue = 0;
//                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
//                                int index = m * _TOPCInfo.pixelWidth + k;
//                                index = _TOPCInfo.pDataIndex[index];
//                                if(index){
//                                    buff = pData[index];
//                                }else{
//                                    buff = 0;
//                                }
//                                if(buff > _nTmpValue){
//                                    _nTmpValue = buff;
//                                }
//                            }

//                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
//                            if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
//                            src[n][index_] = TmpValue;
//                        }
//                    }
//                }
//            }
//        }
        if(Calculation){
            pData = _process->GetTOPCData(m_cInfo.nGroupId, pixelWidthStart, pixelWidthStop, pixelHeightStart,
                                          pixelHeightStop, direction);
            int recMax = m_pConfig->comTmp.nRecMax;
            for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--){
                if(i<0)
                    continue;
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    int _index = _process->GetRealScanIndex(m_cInfo.nGroupId, i);
                    int index_ = (j+1)*step;
                    for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
                        WDATA _nTmpValue = pData[n*recMax + _index];
                        TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
                        if( TmpValue > WAVE_MAX) TmpValue = WAVE_MAX;
                        src[n][index_] = TmpValue;
                    }
                }
            }
        }
        _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        TransformImage( pixelWidthStop- pixelWidthStart, VRange, src,
                        pImage_->width(), pImage_->height(), pImage_);
        return;
    }
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
        _nScanend    =  _process->SAxisDistToIndex(curscanstop)-_nStart;
        _process->ChangeCscanIndexstart(&curlawstart);
        _process->ChangeCscanIndexstop(&curlawstop);
        lawstart = _process->GetLawStart();
        lawstop     =_process->GetLawStop();
        _scanner.fLawStart = lawstart2;
        _scanner.fLawStop = lawstop2;
    }
    //UpdateDisplayRange(3, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;

    }

    if(zoomflag == 2 || zoomflag == 0){
        LAW_CONFIG* _law = _process->GetLawConfig(m_cInfo.nGroupId);
        double startAngle,stopAngle;
        if( _law->eLawType == setup_LAW_TYPE_AZIMUTHAL){
            startAngle = _law->nAngleStartRefract / 10.0;
            stopAngle  = _law->nAngleStopRefract / 10.0;

        }else{
            int _nLawQty = _process->GetGroupLawQty(m_cInfo.nGroupId);
            startAngle = 0;
            stopAngle  = _nLawQty - 1;
        }
        emit signalIndexRangeMove( 2, 1, startAngle, stopAngle);
    }
    float step = 1.0;
    int VRange;
    if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
        if(zoomflag == 2){
            zoomflag = 0;
            flag = 0;
            m_PosStart = _process->SAxisDistToIndex(srcCstart);
            m_PosStop = _process->SAxisDistToIndex(srcCend);
            _nScanend = m_PosStop - m_PosStart;
            emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
        }else{
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
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
        if(_nHeight < _nScanend){
            _nScanend = _nHeight;
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cscan_range == _nScanend){
                    m_PosStart = Csrc_start;
                    m_PosStop = Csrc_start + _nScanend;
                }else{
                    Cscan_range = _nScanend;
                }
            }
            int _nScanPos	 = _process->GetScanIndexPos() ;
            UpdateDisplayRange(3, _nHeight , _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_start = m_PosStart;
            }
        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
            }
        }
        VRange = m_PosStop - m_PosStart;
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
    //QSize csize = QSize((lawstop - lawstart)>0?(lawstop - lawstart):1,_nScanend>0?_nScanend:1);
    //QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    //unsigned char* _pData = TImage->bits() ;
    //memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    //U8* _pImageBits = TImage->bits() ;
    //int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId) ;
	U32 _nTmpValue ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetRealScanMax() + _nScanOff;
    int old_index = -1;
    int new_index = 0;
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
            new_index = (j+1)*step;
            if( new_index == old_index){
                continue;
            }else{
                old_index = new_index;
            }
			GetPixValueInfo(i, eGate_, _aGateValue);
            //_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
            //int index_ = (j+1)*step;
            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp2 = _pImageTmp1 + (k - lawstart) * 3 ;

                _nTmpValue = getGateDataAmplitude(_aGateValue[ k]) * _fScale;
                if(_nTmpValue > WAVE_MAX) _nTmpValue = WAVE_MAX;
                src[k-lawstart+1][new_index]=_nTmpValue;
                //memcpy(_pImageTmp2, &m_pColor[_nTmpValue], 3);
			}
		} else {
//			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
//			if( *_pImageTmp1 || *(_pImageTmp1 + 1) || *(_pImageTmp1+2)) {
//				memset(_pImageTmp1 , 0 , _nWidthStep);
//			}
		}
	}
    unsigned char* _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
    TransformImage(lawstop-lawstart, VRange, src, pImage_->width(), pImage_->height(), pImage_);
    //delete TImage;
}

void DopplerDrawCScanV::DrawGatePos(QImage* pImage_ , GATE_TYPE eGate1_ , GATE_TYPE eGate2_)
{
	U32 _aGateValue1[256] ;
	U32 _aGateValue2[256] ;
	memset(_aGateValue1, 0x00, sizeof(_aGateValue1));
	memset(_aGateValue2, 0x00, sizeof(_aGateValue2));
	int _nHeight	  = pImage_->height();
	int _nWidth	   = pImage_->width() ;
    static int flag = 0;

	int _nLawQty	  = m_CScanInfo.nLawQty   ;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	ParameterProcess* _process = ParameterProcess::Instance();
    SCANNER& _scanner = m_pConfig->common.scanner;
    int lawstart    =_process->GetLawStart();
    int lawstop     =_process->GetLawStop();
    int lawstart2 = lawstart;
    int lawstop2 = lawstop;
    int _nStart     = _process->GetScanIndexStart2();
    int _nScanend    = _process->SAxisstoptoIndex(_process->GetScanend());
    //二维扫查显示
    if( _scanner.eScanType == setup_SCAN_TYPE_RASTER){
        int indexStepBeam = _process->GetRasterIndexStepBeam(m_cInfo.nGroupId);
        int _IndexStartIndex = _process->TransforIndexPosToIndex( _process->GetIndexStartPos());
        int _IndexRangeIndex = _process->TransforIndexPosToIndex( _process->GetIndexEndPos());
        int _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        int heightToIndex = (_nWidth - _process->GetGroupLawQty(m_cInfo.nGroupId))/indexStepBeam;
        if( heightToIndex < 0){
            heightToIndex = 0;
        }
        if(zoomflag == 1){
            if(((_scanner.fScanPos > curscanstart)&&(_scanner.fScanPos < curscanstop)) ||
                   ((_scanner.fIndexPos > curIndexStartPos)&&(_scanner.fIndexPos < curIndexStopPos))){
                flag = 1;
            }
            if( flag == 1){
                if((_scanner.fScanPos < curscanstart+1)&&(_scanner.fScanPos-1 >= _scanner.fScanStart))
                    curscanstart = _scanner.fScanPos-1;
                if((_scanner.fScanPos > curscanstop-1)&&(_scanner.fScanPos+1 <= _scanner.fScanStop))
                    curscanstop = _scanner.fScanPos+1;
                if((_scanner.fIndexPos < curIndexStartPos+1)&&(_scanner.fIndexPos-1 >= _scanner.fIndexStart))
                    curIndexStartPos = _scanner.fIndexPos-1;
                if((_scanner.fIndexPos > curIndexStopPos-1)&&(_scanner.fIndexPos+1 <= _scanner.fIndexStop))
                    curIndexStopPos = _scanner.fIndexPos+1;
            }
            _nStart     = _process->SAxisDistToIndex(curscanstart);
            _nScanend   = _process->SAxisDistToIndex(curscanstop) - _nStart;
            _IndexStartIndex = _process->TransforIndexPosToIndex(curIndexStartPos);
            _IndexRangeIndex = _process->TransforIndexPosToIndex(curIndexStopPos) - _IndexStartIndex;
            _IndexRangePixel = _IndexRangeIndex*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        }
        if(_scanner.fScanPos == _scanner.fScanStart2){

            m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
            m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nHeight;
        }
        if(_scanner.fIndexPos == _scanner.fIndexStart){
            m_indexStartIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
            m_indexStopIndex = m_indexStartIndex + heightToIndex;
        }
        if(_nHeight <_nScanend){
            _nScanend = _nHeight;
            if(zoomflag == 2){
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cscan_range == _nScanend){
                    m_PosStart = Csrc_start;
                    m_PosStop = Csrc_start + _nScanend;
                }else{
                    Cscan_range = _nScanend;
                }
            }
            int _nScanPos	 = _process->GetScanIndexPos();
            UpdateDisplayRange(3, _nHeight, _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_start = m_PosStart;
            }
        }else{
            if(zoomflag == 2){
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend) ;
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
            }
        }
        if(_nWidth < _IndexRangePixel){
            _IndexRangePixel = heightToIndex*indexStepBeam + _process->GetGroupLawQty(currentgroup);
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cindex_range == _IndexRangePixel){
                    m_indexStartIndex = Csrc_indexStart;
                    m_indexStopIndex = Csrc_indexStart + heightToIndex;
                }else{
                    Cindex_range = _IndexRangePixel;
                }
            }
            int _nIndexCurIndex = _process->TransforIndexPosToIndex( _scanner.fIndexPos);
            UpdateIndexRange(2, heightToIndex, _nIndexCurIndex);
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_indexStart = m_indexStartIndex;
            }
        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_indexStartIndex = _process->TransforIndexPosToIndex(srcCIndexStartPos);
                m_indexStopIndex = _process->TransforIndexPosToIndex(srcCIndexEndPos);
                emit signalIndexRangeMove( 2, 0, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove( 2, 0, m_indexStartIndex, m_indexStopIndex);
            }
        }
        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, p;
        memset(src,0x00,sizeof(src));
        WDATA* pData;
        pData = _process->GetRasterData(m_cInfo.nGroupId, setup_CSCAN_SOURCE_MODE (m_CScanInfo.eType));
        int transf = m_PosStop - m_PosStart;
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
            double _offsetbuff = _pConfig->rasterOffset[j];
            int _offset = scanQty * _offsetbuff /(_scanner.fScanStop - _scanner.fScanStart);
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                if( p - _offset < 0 || p - _offset >= scanQty){
                    continue;
                }
                int markerPos = markerBuff + k - _offset;

                if( _pMarker[markerPos]){
//                    if(eGate2_){
//                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
//                        GetPixValueInfo(markerPos, eGate2_, _aGateValue2);
//                        GetPixValueDistance(_aGateValue1, _aGateValue2);
//                    }else{
//                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
//                        GetPixValuePos(_aGateValue1);
//                    }
                    int markOffset = markerPos * indexStepBuff;
                    for(int w = 0; w < indexStepBuff; w++){
                        //src[srcBuffIndex + w][transf - p] = _aGateValue1[w];
                        src[srcBuffIndex + w][transf - p] = pData[markOffset + w];
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        int srcHeight = (j -1)*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        TransformImage( srcHeight, p, src, pImage_->width(), pImage_->height(), pImage_);
        return;
    }
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
        _nScanend    =  _process->SAxisDistToIndex(curscanstop)-_nStart;
        _process->ChangeCscanIndexstart(&curlawstart);
        _process->ChangeCscanIndexstop(&curlawstop);
        lawstart = _process->GetLawStart();
        lawstop     =_process->GetLawStop();
        _scanner.fLawStart = lawstart2;
        _scanner.fLawStop = lawstop2;
    }
    //UpdateDisplayRange(3, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;

    }
    float step = 1.0;
    int VRange;
    if(m_pConfig->group[m_cInfo.nGroupId].CScanShowAll){
        if(zoomflag == 2){
            zoomflag = 0;
            flag = 0;
            m_PosStart = _process->SAxisDistToIndex(srcCstart);
            m_PosStop = _process->SAxisDistToIndex(srcCend);
            _nScanend = m_PosStop - m_PosStart;
            emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
        }else{
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
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
        if(_nHeight < _nScanend){
            _nScanend = _nHeight;
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
            }
            if(_pConfig->AppEvn.bSAxisCursorSync){
                if(Cscan_range == _nScanend){
                    m_PosStart = Csrc_start;
                    m_PosStop = Csrc_start + _nScanend;
                }else{
                    Cscan_range = _nScanend;
                }
            }
            int _nScanPos	 = _process->GetScanIndexPos() ;
            UpdateDisplayRange(3, _nHeight , _nScanPos) ;
            if(_pConfig->AppEvn.bSAxisCursorSync){
                Csrc_start = m_PosStart;
            }
        }else{
            if(zoomflag == 2){
                zoomflag = 0;
                flag = 0;
                m_PosStart = _process->SAxisDistToIndex(srcCstart);
                m_PosStop = _process->SAxisDistToIndex(srcCend);
                _nScanend = m_PosStop - m_PosStart;
                emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
            }else{
                m_PosStart = _nStart;
                m_PosStop  = _nStart+_nScanend;
                emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
            }
        }
        VRange = m_PosStop - m_PosStart;
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
    //QSize csize = QSize((lawstop - lawstart)>0?(lawstop - lawstart):1,_nScanend>0?_nScanend:1);
    //QImage *TImage = new QImage(csize , QImage::Format_RGB888);
    //unsigned char* _pData = TImage->bits() ;
    //memset(_pData, 0 , TImage->bytesPerLine() * TImage->height() );
    //U8* _pImageBits = TImage->bits() ;
    //int _nWidthStep   = TImage->bytesPerLine() ;

	U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId)  ;
	int i , j  , k ;

	int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
	int _nScanMax = _process->GetScanMax();
    float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
    memset(src,0x00,sizeof(src));
    int old_index = -1;
    int new_index = 0;
    for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
            new_index = (j+1)*step;
            if(new_index == old_index){
                continue;
            }else{
                old_index = new_index;
            }
			if(eGate2_) {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
                GetPixValueDistance(_aGateValue1, _aGateValue2, _fScale);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
                GetPixValuePos(_aGateValue1, _aGateValue2, _fScale);
			}

            //_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
            //int index_ = (j+1)*step;
            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp2 = _pImageTmp1 + (k - lawstart) * 3 ;
                //_pColorTmp = m_pColor[_aGateValue1[k ]] ;
                src[k-lawstart+1][new_index]=_aGateValue1[k ];
                //memcpy(_pImageTmp2, _pColorTmp, 3);
			}
		} else {
//			_pImageTmp1 = _pImageBits + j * _nWidthStep  ;
//			if( *_pImageTmp1 || *(_pImageTmp1 + 1) || *(_pImageTmp1+2)) {
//				memset(_pImageTmp1 , 0 , _nWidthStep);
//			}
		}
	}
    unsigned char* _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
    TransformImage(lawstop - lawstart, VRange, src, pImage_->width(), pImage_->height(), pImage_);
    //delete TImage;
}
