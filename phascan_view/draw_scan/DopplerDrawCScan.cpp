﻿#include "DopplerDrawCScan.h"
#include <process/ParameterProcess.h>
#include <QImage>
#include <gHeader.h>

extern int lastgroup,currentgroup;
extern int Phascan_Version;
int Cscan_range = 0;
int Csrc_start = 0;
int Cindex_range = 0;
int Csrc_indexStart = 0;

U32 getGateDataAmplitude( U32 value)
{
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4)
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
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4)
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
    if( Phascan_Version == 1 || Phascan_Version == 3 || Phascan_Version == 4)
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
                emit signalIndexRangeMove(0, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove(0, m_indexStartIndex, m_indexStopIndex);
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
        PEAK_CONFIG _info[setup_GATE_MAX];
        setup_GATE_NAME _eGate;

        switch(eGate_)
        {
        case GATE_A: _eGate = setup_GATE_A; break;
        case GATE_B: _eGate = setup_GATE_B; break;
        case GATE_I: _eGate = setup_GATE_I; break;
        default:  return;
        }
        memset(src,0x00,sizeof(src));
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
//            int indexStepBuff = indexStepDrawBeam;
//            if(i == m_indexStopIndex){
//                indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
//            }
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                int markerPos = markerBuff + k;

                if( _pMarker[markerPos]){
                    for(int w = 0; w < indexStepBuff; w++){
                        _process->GetGatePeakInfos(m_cInfo.nGroupId, markerPos, w, _info);
                        _nTmpValue = getGateDataAmplitude(_info[_eGate].iY) * _fScale;
                        if(_nTmpValue > 255)	_nTmpValue = 255;

                        src[p][srcBuffIndex + w] = _nTmpValue;
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        int srcHeight = j*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        TransformImage( p, srcHeight, src, pImage_->width(), pImage_->height(), pImage_);
        return;
    }

    TOPC_INFO& _TOPCInfo  = m_pConfig->group[m_cInfo.nGroupId].TopCInfo;
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
        realWidthStart = 0 - topcWidth/2;
        realWidthStop  = topcWidth/2;
        setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_cInfo.nGroupId) ;
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
            break;
        case setup_PROBE_PART_SKEW_270:
            direction = 1;
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
        unsigned char* _pData;
        WDATA* pData;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, m, n;
        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
        int TmpValue;
        int _nScanOff = _process->GetScanOff(m_cInfo.nGroupId);
        int _nScanMax = _process->GetRealScanMax() + _nScanOff;
        memset( src, 0x00, sizeof(src));
        if(Calculation){
            for(i = m_PosStart - 1, j = -1; i <= m_PosStop + 1 && j < (_nScanend)+1; i++ , j++){
                if(i<0)
                    continue;
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    pData = _process->GetScanPosPointer(m_cInfo.nGroupId, i);
                    if(direction == 0){
                        for( k = pixelWidthStart, n = 0; k < pixelWidthStop; k++,n++){
                            WDATA buff = 0;
                            WDATA _nTmpValue = 0;
                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
                                int index = m * _TOPCInfo.pixelWidth + k;
                                index = _TOPCInfo.pDataIndex[index];
                                if(index){
                                    buff = pData[index];
                                }else{
                                    buff = 0;
                                }
                                if(buff > _nTmpValue){
                                    _nTmpValue = buff;
                                }
                            }

                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
                            if( TmpValue > 255) TmpValue = 255;
                            src[j+1][n] = TmpValue;
                        }
                    }else{
                        for( k = pixelWidthStop - 1, n = 0; k >= pixelWidthStart; k--,n++){
                            WDATA buff = 0;
                            WDATA _nTmpValue = 0;
                            for( m = pixelHeightStart; m < pixelHeightStop; m++){
                                int index = m * _TOPCInfo.pixelWidth + k;
                                index = _TOPCInfo.pDataIndex[index];
                                if(index){
                                    buff = pData[index];
                                }else{
                                    buff = 0;
                                }
                                if(buff > _nTmpValue){
                                    _nTmpValue = buff;
                                }
                            }

                            TmpValue =  _process->correctionPdata(_nTmpValue) * _fScale;
                            if( TmpValue > 255) TmpValue = 255;
                            src[j+1][n] = TmpValue;
                        }
                    }

                }
            }
        }
        _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        TransformImage( m_PosStop - m_PosStart, pixelWidthStop- pixelWidthStart, src,
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
        lawstop     =_process->GetLawStop();
        _scanner.fLawStart = lawstart2;
        _scanner.fLawStop = lawstop2;
    }
    //UpdateDisplayRange(2, _nScanend>0?_nScanend:1 , _nScanPos) ;
    if(_scanner.fScanPos == _scanner.fScanStart2)
    {

        m_PosStart = _process->SAxisDistToIndex(_scanner.fScanPos);
        m_PosStop  = _process->SAxisDistToIndex(_scanner.fScanPos) + _nWidth;

    }
    if(_nWidth <_nScanend)
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
            m_PosStop = _process->SAxisDistToIndex(srcCend) ;

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
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = -1 ; i <= m_PosStop + 1&& j < (_nScanend)+1; i++ , j++) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			GetPixValueInfo(i, eGate_, _aGateValue);
            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
                _nTmpValue = getGateDataAmplitude(_aGateValue[k ])  * _fScale;

                if(_nTmpValue > 255)	_nTmpValue = 255 ;
                src[j+1][k-lawstart+1]=_nTmpValue;
                //memcpy(_pImageTmp, &m_pColor[_nTmpValue], 3);
			}
		} else {
//			_pImageTmp = _pImageBits + j * 3 ;
//			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
//                for(k = lawstart ; k < lawstop ; k++) {
//                    _pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
//                    memset(_pImageTmp, 0, 3);
//				}
//			}
		}
	}
    _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
        TransformImage(m_PosStop - m_PosStart,lawstop-lawstart,src,pImage_->width(),pImage_->height(),pImage_);
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
                emit signalIndexRangeMove(0, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove(0, m_indexStartIndex, m_indexStopIndex);
            }
        }
        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, p;
//        int indexStepDrawBeam = indexStepBeam;
//        if(indexStepDrawBeam > _process->GetGroupLawQty(m_cInfo.nGroupId)){
//            indexStepDrawBeam = _process->GetGroupLawQty(m_cInfo.nGroupId);
//        }
//        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
//        U32 _nTmpValue;
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
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                int markerPos = markerBuff + k;

                if( _pMarker[markerPos]){
                    if(eGate2_){
                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
                        GetPixValueInfo(markerPos, eGate2_, _aGateValue2);
                        GetPixValueDistance(_aGateValue1, _aGateValue2);
                    }else{
                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
                        GetPixValuePos(_aGateValue1);
                    }
                    for(int w = 0; w < indexStepBuff; w++){
//                        _process->GetGatePeakInfos(m_cInfo.nGroupId, markerPos, w, _info);
//                        _nTmpValue = getGateDataAmplitude(_info[_eGate].iY) * _fScale;
//                        if(_nTmpValue > 255)	_nTmpValue = 255;

                        src[p][srcBuffIndex + w] = _aGateValue1[w];
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        int srcHeight = j*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
        TransformImage( p, srcHeight, src, pImage_->width(), pImage_->height(), pImage_);
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
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = -1 ; i <= m_PosStop+1 && j < (_nScanend)+1; i++ , j++) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			if(eGate2_)	{
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
				GetPixValueDistance(_aGateValue1, _aGateValue2);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValuePos(_aGateValue1);
			}

            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp	   = _pImageBits + (k -lawstart) * _nWidthStep + j * 3 ;
                //_pColorTmp	   = m_pColor[_aGateValue1[k ]] ;
                 src[j+1][k-lawstart+1]=_aGateValue1[k ];
                //memcpy(_pImageTmp, _pColorTmp, 3);
			}
		} else {
//			_pImageTmp = _pImageBits + j * 3 ;
//			if( *_pImageTmp || *(_pImageTmp + 1) || *(_pImageTmp+2)) {
//                for(k = lawstart ; k < lawstop ; k++)
//				{
//                    _pImageTmp = _pImageBits + (k - lawstart) * _nWidthStep + j * 3 ;
//					memset(_pImageTmp, 0x00, 3);
//				}
//			}
		}
	}
    unsigned char* _pData = pImage_->bits() ;
        memset(_pData, 0 , pImage_->bytesPerLine() * pImage_->height() );
        TransformImage(m_PosStop - m_PosStart,lawstop-lawstart,src,pImage_->width(),pImage_->height(),pImage_);
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
	for(int i = 0 ; i < _nBeamQty ; i++)
	{
		_process->GetGatePeakInfos(m_cInfo.nGroupId, nScanPos_, i, _info);
		pBuff_[i] = (_info[_eGate].fD * 1000);
        pBuff_[i] = combinedGateDate( pBuff_[i], _info[_eGate].iY);
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
        _nPeak = getGateDataAmplitude(_nData);

		if(_nPeak < _nGateHeight)
		{
			//pBuff_[i] = 255 ;
			pBuff_[i] = 0 ;
		}
		else
		{
            _nDepth = getGateDataDepth(_nData);

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
        _nPeak1 = getGateDataAmplitude(_nData1);
        _nPeak2 = getGateDataAmplitude(_nData2);

		if(_nPeak1 >= _nGateHeight1 && _nPeak2 >= _nGateHeight2)
		{
            _nDepth1 = getGateDataDepth(_nData1);
            _nDepth2 = getGateDataDepth(_nData2);

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
            pBuff1_[i] = 0;
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
                emit signalIndexRangeMove(2, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove(2, m_indexStartIndex, m_indexStopIndex);
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
        PEAK_CONFIG _info[setup_GATE_MAX];
        setup_GATE_NAME _eGate;

        switch(eGate_)
        {
        case GATE_A: _eGate = setup_GATE_A; break;
        case GATE_B: _eGate = setup_GATE_B; break;
        case GATE_I: _eGate = setup_GATE_I; break;
        default:  return;
        }
        memset(src,0x00,sizeof(src));
        int transf = m_PosStop - m_PosStart;
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                int markerPos = markerBuff + k;

                if( _pMarker[markerPos]){
                    for(int w = 0; w < indexStepBuff; w++){
                        _process->GetGatePeakInfos(m_cInfo.nGroupId, markerPos, w, _info);
                        _nTmpValue = getGateDataAmplitude(_info[_eGate].iY) * _fScale;
                        if(_nTmpValue > 255)	_nTmpValue = 255;

                        src[srcBuffIndex + w][transf - p] = _nTmpValue;
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        int srcHeight = j*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
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
    if(_nHeight < _nScanend)
    {
        _nScanend = _nHeight;
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
        UpdateDisplayRange(3, _nHeight , _nScanPos) ;
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
            emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
        }
        else
        {
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
        }
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
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			GetPixValueInfo(i, eGate_, _aGateValue);
            //_pImageTmp1 = _pImageBits + j * _nWidthStep  ;

            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp2 = _pImageTmp1 + (k - lawstart) * 3 ;

                _nTmpValue = getGateDataAmplitude(_aGateValue[ k]) * _fScale;
				if(_nTmpValue > 255) _nTmpValue = 255 ;
                src[k-lawstart+1][j+1]=_nTmpValue;
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
    TransformImage(lawstop-lawstart,m_PosStop - m_PosStart,src,pImage_->width(),pImage_->height(),pImage_);
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
    //U8* _pImageBits = pImage_->bits() ;
    //U8* _pImageTmp1 , *_pImageTmp2 , *_pColorTmp;
    //int _nWidthStep   = pImage_->bytesPerLine() ;

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
                emit signalIndexRangeMove(2, m_indexStartIndex, m_indexStopIndex);
            }else{
                m_indexStartIndex = _IndexStartIndex;
                m_indexStopIndex  = _IndexStartIndex + _IndexRangeIndex;
                emit signalIndexRangeMove(2, m_indexStartIndex, m_indexStopIndex);
            }
        }
        int scanQty = ( _scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5;
        U8* _pMarker = _process->GetScanMarker(m_cInfo.nGroupId);
        int i, j, k, p;
//        int indexStepDrawBeam = indexStepBeam;
//        if(indexStepDrawBeam > _process->GetGroupLawQty(m_cInfo.nGroupId)){
//            indexStepDrawBeam = _process->GetGroupLawQty(m_cInfo.nGroupId);
//        }
//        float _fScale = _process->GetRefGainScale(m_cInfo.nGroupId);
//        U32 _nTmpValue;
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
        int transf = m_PosStop - m_PosStart;
        for(i = m_indexStartIndex, j = 0; i <= m_indexStopIndex; i++, j++){
            int indexStepBuff = _process->GetGroupLawQty(m_cInfo.nGroupId);
            int srcBuffIndex = j*indexStepBeam;
            int markerBuff = scanQty*i;
            for( k = m_PosStart, p = 0; k <= m_PosStop&& p < _nScanend; k++, p++){
                int markerPos = markerBuff + k;

                if( _pMarker[markerPos]){
                    if(eGate2_){
                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
                        GetPixValueInfo(markerPos, eGate2_, _aGateValue2);
                        GetPixValueDistance(_aGateValue1, _aGateValue2);
                    }else{
                        GetPixValueInfo(markerPos, eGate1_, _aGateValue1);
                        GetPixValuePos(_aGateValue1);
                    }
                    for(int w = 0; w < indexStepBuff; w++){
//                        _process->GetGatePeakInfos(m_cInfo.nGroupId, markerPos, w, _info);
//                        _nTmpValue = getGateDataAmplitude(_info[_eGate].iY) * _fScale;
//                        if(_nTmpValue > 255)	_nTmpValue = 255;

                        src[srcBuffIndex + w][transf - p] = _aGateValue1[w];
                    }
                }
            }
        }
        unsigned char* _pData = pImage_->bits();
        memset( _pData, 0, pImage_->bytesPerLine() * pImage_->height());
        int srcHeight = j*indexStepBeam + _process->GetGroupLawQty(m_cInfo.nGroupId);
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
    if(_nHeight < _nScanend)
    {
        _nScanend = _nHeight;
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
        UpdateDisplayRange(3, _nHeight , _nScanPos) ;
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
            emit signalScanRangeMove(3, m_PosStart, m_PosStop) ;
        }
        else
        {
            m_PosStart = _nStart;
            m_PosStop  = _nStart+_nScanend;
            emit signalScanRangeMove(3, _nStart, _nStart+_nScanend) ;
        }
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
    memset(src,0x00,sizeof(src));
    for(i = m_PosStart-1 , j = _nScanend  ; i <= m_PosStop+1 && j >= -1; i++ , j--) {
        if(i<0)
            continue;
		if(_pMarker[i] && i >= _nScanOff && i < _nScanMax) {
			if(eGate2_) {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValueInfo(i, eGate2_, _aGateValue2);
				GetPixValueDistance(_aGateValue1, _aGateValue2);
			} else {
				GetPixValueInfo(i, eGate1_, _aGateValue1);
				GetPixValuePos(_aGateValue1);
			}

            //_pImageTmp1 = _pImageBits + j * _nWidthStep  ;

            for(k = lawstart-1 ; k < lawstop+1 ; k++) {
                if(k<0||k>_nLawQty)
                    continue;
                //_pImageTmp2 = _pImageTmp1 + (k - lawstart) * 3 ;
                //_pColorTmp = m_pColor[_aGateValue1[k ]] ;
                src[k-lawstart+1][j+1]=_aGateValue1[k ];
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
    TransformImage(lawstop-lawstart,m_PosStop - m_PosStart,src,pImage_->width(),pImage_->height(),pImage_);
    //delete TImage;
}
