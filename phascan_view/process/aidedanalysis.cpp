#include "aidedanalysis.h"
#include "DopplerConfigure.h"
#include "ParameterProcess.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <qmath.h>
#include <QRect>

AidedAnalysis::AidedAnalysis(QObject *parent) :
    QObject(parent)
{
    m_dataMaxStatus = false;
    m_dataMax       = 0;
}

void AidedAnalysis::setGroupId( int groupId)
{
    m_groupId = groupId;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    m_pColor  = (unsigned char (*)[3])_pConfig->group[m_groupId].color.Amp;
}

void AidedAnalysis::setRange( double scanStart, double scanStop, double widthStart, double widthStop)
{
    m_scanStart = scanStart;
    m_scanStop  = scanStop;
    m_TopcWidthStart = widthStart;
    m_TopcWidthStop  = widthStop;
}

int AidedAnalysis::analysisDefect()
{
    calculateSrcData();
    int max = getDataMax();
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int threshold = _pConfig->group[m_groupId].gate[0].nThreshold * 255.0 / 100;
    if( max < threshold){
        return 0;
    }
    max--;
    int rows, cols;
    if( m_orient == ORIENT_HORIZONTAL){
        rows = topcWidthPixel;
        cols = scanPixel;
    }else{
        rows = scanPixel;
        cols = topcWidthPixel;
    }
    cv::Mat paintBuff( rows, cols, CV_8U, srcData.data());
    cv::Mat result;
    cv::threshold( paintBuff, result, max, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point> >contours;
    contours.clear();
    cv::findContours( result, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//    cv::namedWindow("Original Image", 1);
//    cv::imshow("Original Image", result);
//    cv::waitKey();
    defectCentre.clear();
    defectRect.clear();
    int defectNum = contours.size();
    if(defectNum != 0){
        std::vector<cv::Rect> boundRect( defectNum);
        for( int i = 0; i < defectNum; i++){
            boundRect[i] = cv::boundingRect( cv::Mat( contours[i]));
            int x = boundRect[i].x + (boundRect[i].width / 2);
            int y = boundRect[i].y + (boundRect[i].height / 2);
            QPoint buff(x, y);
            QRect _buff(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height);
            defectCentre.append(buff);
            defectRect.append(_buff);
            qDebug()<<"x"<<boundRect[i].x<<"y"<<boundRect[i].y<<"width"<<boundRect[i].width
                   <<"height"<<boundRect[i].height;
        }
    }
    qDebug()<<"defectCentre"<<defectCentre;
    return defectNum;
}

void AidedAnalysis::paintDefectImage(QImage* pImage)
{
    int srcDx, srcDy;
    if( m_orient == ORIENT_HORIZONTAL){
        srcDx = scanPixel;
        srcDy = topcWidthPixel;
    }else{
        srcDx = topcWidthPixel;
        srcDy = scanPixel;
    }
    int _nWidth	 = pImage->width();
    int _nHeight = pImage->height();
    double widthscale = (double)srcDx/_nWidth;
    double hightscale = (double)srcDy/_nHeight;
    int srcx = 0;
    int srcy = 0;
    float transx = 0.0;
    float transy = 0.0;
    float diffx = 0.0;
    float diffy = 0.0;

    int midy3;
    int i;
    int j;
    U8* _pImageTmp;
    U8* _pImageBits = pImage->bits();
    int _nWidthStep = pImage->bytesPerLine();
    for(i = 0; i < _nWidth; i++){
        transx = (i+0.5)*widthscale - 0.5;
        srcx = qFloor(transx);
        diffx = transx - srcx;
        srcx += 1;
        if(srcx >= srcDx - 2){
            srcx = srcDx - 2;
        }

        for( j = 0; j < _nHeight; j++){
            _pImageTmp = _pImageBits + j * _nWidthStep + i * 3;
            transy = (j+0.5)*hightscale-0.5;
            srcy = qFloor(transy);
            diffy = transy -srcy;
            srcy += 1;
            if( srcy >= srcDy - 2){
                srcy = srcDy - 2;
            }
            int Index = srcy*srcDx;
            midy3 = (1-diffx)*(1-diffy)*srcData[srcx+Index] + (1-diffx)*(diffy)*srcData[srcx+Index+srcDx]
                    +diffx*(1-diffy)*srcData[srcx+1+Index]+diffx*diffy*srcData[srcx+1+Index+srcDx];
            memcpy(_pImageTmp,&m_pColor[midy3],3);
        }
    }

    defectInImage.clear();
    QVector<QPoint>::const_iterator ip;
    for( ip = defectCentre.begin(); ip != defectCentre.end(); ip++){
        int x = ip->x() * (_nWidth -1) / (srcDx -1);
        int y = ip->y() * (_nHeight -1) / (srcDy -1);
        QPoint buff(x, y);
        defectInImage.append(buff);
    }
    RectInImage.clear();
    QVector<QRect>::const_iterator ir;
    for( ir = defectRect.begin(); ir != defectRect.end(); ir++){
        int x = ir->x() * (_nWidth -1) / (srcDx -1);
        int y = ir->y() * (_nHeight -1) / (srcDy -1);
        int width  = ir->width() * (_nWidth -1) / (srcDx -1);
        int height = ir->height() * (_nHeight -1) / (srcDy -1);
        QRect buff( x, y, width, height);
        RectInImage.append(buff);
    }
}

bool AidedAnalysis::setSelectDefectIndex(int index)
{
    int max = getDataMax();
    //max = max / 2;
    //max = (max - 1)/2;
    max--;
    QPoint buff = defectCentre[index];
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    TOPC_INFO& _TOPCInfo = _pConfig->group[m_groupId].TopCInfo;
    int scanIndex;
    float  indexOffset = _pConfig->group[m_groupId].fIndexOffset;
    if( m_orient == ORIENT_HORIZONTAL){
        scanIndex = _process->SAxisDistToIndex(m_scanStart);
        qDebug()<<"scanIndex"<<scanIndex;
        scanIndex = scanIndex + buff.x();
    }else{
        scanIndex = _process->SAxisDistToIndex(m_scanStop);
        scanIndex = scanIndex - buff.y();
    }
    qDebug()<<"buff.x"<<buff.x()<<"scanIndex"<<scanIndex;
    int _pixelWidth = _TOPCInfo.pixelWidth;
    int _pixelHeigh = _TOPCInfo.pixelHeigh;
    int direction;
    QVector<quint8> src( _pixelWidth*_pixelHeigh, 0);
    setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_groupId);
    switch (_eAngle) {
    case setup_PROBE_PART_SKEW_0:
        direction = 0;
        indexOffset = 0;
        break;
    case setup_PROBE_PART_SKEW_90:
        direction = 0;        
        break;
    case setup_PROBE_PART_SKEW_180:
        direction = 1;
        indexOffset = 0;
        break;
    case setup_PROBE_PART_SKEW_270:
        direction = 1;
        indexOffset = 0 - indexOffset;
        break;
    default:
        direction = 0;
        break;
    }
    WDATA* pData;
    float _fScale = _process->GetRefGainScale(m_groupId);
    int i, j;
    int TmpValue;
    pData = _process->GetScanPosPointer( m_groupId, scanIndex);
    qDebug()<<"m_groupId"<<m_groupId;

    for( i = 0; i < _pixelWidth; i++){
        WDATA buff = 0;
        for( j = 0; j < _pixelHeigh; j++){
            int index = j * _TOPCInfo.pixelWidth + i;
            index = _TOPCInfo.pDataIndex[index];
            if(index){
                buff = pData[index];
            }else{
                buff = 0;
            }
            TmpValue =  _process->correctionPdata(buff) * _fScale;
            if( TmpValue > 255) TmpValue = 255;
            src[ j * _pixelWidth + i] = TmpValue;
        }
    }
//    int srcMax = 0;
//    for(int k = 0; k < src.size(); k++){
//        if(src[k] > srcMax){
//            srcMax = src[k];
//        }
//    }
//    qDebug()<<"srcMax"<<srcMax;
    cv::Mat paintBuff( _pixelHeigh, _pixelWidth, CV_8U, src.data());
    //cv::imshow("origin Image", paintBuff);
    cv::Mat result;
    cv::threshold( paintBuff, result, max, 255, cv::THRESH_BINARY);
    qDebug()<<"max"<<max;
    //cv::imshow("result Image", result);

    std::vector<std::vector<cv::Point> >contours;
    contours.clear();
    cv::findContours( result, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    int defectNum = contours.size();
    if(defectNum == 0){
        qDebug()<<"return1";
        return false;
    }
    cv::Rect boundRect;
    QVector<QPoint> _centre;
    QVector<QRect>  _centreRect;
    _centre.clear();
    _centreRect.clear();
    int _selectX;
    if( m_orient == ORIENT_HORIZONTAL){
        if(direction == 0){
           _selectX = slectRectInfo.pixelWidthStart + buff.y();
        }else{
           _selectX = slectRectInfo.pixelWidthStop - buff.y();
        }
    }else{
        if(direction == 0){
           _selectX = slectRectInfo.pixelWidthStart + buff.x();
        }else{
           _selectX = slectRectInfo.pixelWidthStop - buff.x();
        }
    }


    for( int i = 0; i < defectNum; i++){
        boundRect = cv::boundingRect( cv::Mat( contours[i]));
        int x1 = boundRect.x;
        int x2 = boundRect.x + boundRect.width;
        int y1 = boundRect.y;
        int y2 = boundRect.y + boundRect.height;
        if(x1 <= _selectX && _selectX <= x2){
            if(y1 < slectRectInfo.pixelHeightStart){
                if(y2 > slectRectInfo.pixelHeightStart){
                    int x = boundRect.x + ((boundRect.width) / 2) + 1;
                    int y = boundRect.y + ((boundRect.height) / 2) + 1;
                    QPoint buff(x, y);
                    QRect _buff(x1, y1, boundRect.width, boundRect.height);
                    _centre.append(buff);
                    _centreRect.append(_buff);
                }
            }else{
                if(y1 < slectRectInfo.pixelHeightStop){
                    int x = boundRect.x + (boundRect.width / 2) + 1;
                    int y = boundRect.y + (boundRect.height / 2) + 1;
                    QPoint buff(x, y);
                    QRect _buff(x1, y1, boundRect.width, boundRect.height);
                    _centre.append(buff);
                    _centreRect.append(_buff);
                }
            }
        }
    }
    if(_centre.size() == 0){
        qDebug()<<"return2";
        return false;
    }
    int _index = 0;
    int maxRect = 0;
    for(int i = 0; i < _centre.size(); i++){
        int curArea = _centreRect[i].width() * _centreRect[i].height();
        if(curArea > maxRect){
            maxRect = curArea;
            _index  = i;
        }
    }
    QPoint _defectC = _centre[_index];
    max = (max - 1)/2;
    cv::threshold( paintBuff, result, max, 255, cv::THRESH_BINARY);
    contours.clear();
    cv::findContours( result, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    defectNum = contours.size();
    if(defectNum == 0){
        qDebug()<<"return3";
        return false;
    }
    QRect _defect;
    bool status = false;
    for( int i = 0; i < defectNum; i++){
        boundRect = cv::boundingRect( cv::Mat( contours[i]));
        QRect buff( boundRect.x, boundRect.y, boundRect.width, boundRect.height);
            if(buff.contains(_defectC)){
                _defect = buff;
                status = true;
                break;
            }
    }

    if(status == false){
        return false;
    }
    int _index_ = _defectC.y() * _TOPCInfo.pixelWidth + _defectC.x();
    _index_ = _TOPCInfo.pDataIndex[_index_];
    int pointQty = _pConfig->group[m_groupId].nPointQty + setup_DATA_PENDIX_LENGTH;
    int curLaw = _index_ / pointQty;
     _pConfig->common.aidedAnalysis.aidedBeamId = curLaw;
    qDebug()<<pData[_index_]<<"pointQty"<<pointQty<<"_index_"<<_index_<<"curLaw"<<curLaw;
    float defectTop    = (_TOPCInfo.stopY - _TOPCInfo.startY) * _defect.y()/( _pixelHeigh -1) + _TOPCInfo.startY;
    float defectBottom = (_TOPCInfo.stopY - _TOPCInfo.startY) * _defect.bottom()/( _pixelHeigh -1) + _TOPCInfo.startY;
    float _defectLeft  = (_TOPCInfo.stopX - _TOPCInfo.startX) * _defect.x()/( _pixelWidth -1) + _TOPCInfo.startX;
    float _defectRight = (_TOPCInfo.stopX - _TOPCInfo.startX) * _defect.right()/( _pixelWidth -1) + _TOPCInfo.startX;
    if(direction == 0){
        _defectLeft  += indexOffset;
        _defectRight += indexOffset;
    }else{
        _defectLeft  = -(_defectLeft + indexOffset);
        _defectRight = -(_defectRight + indexOffset);
    }
    _pConfig->group[m_groupId].afCursor[setup_CURSOR_U_REF] = defectTop;
    _pConfig->group[m_groupId].afCursor[setup_CURSOR_U_MES] = defectBottom;
    _pConfig->group[m_groupId].afCursor[setup_CURSOR_I_REF] = _defectLeft;
    _pConfig->group[m_groupId].afCursor[setup_CURSOR_I_MES] = _defectRight;

    int left, right;
    int methodId = _pConfig->common.aidedAnalysis.aidedMethodId;    
    if(methodId){
        float methodThreshold = _process->GetDetermineThreshold(m_groupId, setup_EL);
        max = methodThreshold * 255 / 100 - 1;
        if(max < 0){
            max = 0;
        }
        int rows, cols;
        if( m_orient == ORIENT_HORIZONTAL){
            rows = topcWidthPixel;
            cols = scanPixel;
        }else{
            rows = scanPixel;
            cols = topcWidthPixel;
        }
        cv::Mat _paintBuff( rows, cols, CV_8U, srcData.data());
        cv::threshold( _paintBuff, result, max, 255, cv::THRESH_BINARY);
        contours.clear();
        cv::findContours( result, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        defectNum = contours.size();
        left  = scanPixel -1;
        right = 0;
        for( int i = 0; i < defectNum; i++){
            boundRect = cv::boundingRect( cv::Mat( contours[i]));
            if( m_orient == ORIENT_HORIZONTAL){
                if(boundRect.x < left){
                    left = boundRect.x;
                }
                if(boundRect.x + boundRect.width > right){
                    right = boundRect.x + boundRect.width;
                }
            }else{
                if(boundRect.y < left){
                    left = boundRect.y;
                }
                if(boundRect.y + boundRect.height > right){
                    right = boundRect.y + boundRect.height;
                }
            }
        }
    }else{
        getAmpDataWatershed(left, right);
    }


//    cv::namedWindow("Original Image", 1);
//    cv::imshow("Original Image", result);
//    cv::waitKey();
    float defectCLeft, defectCRight;
    if( m_orient == ORIENT_HORIZONTAL){
        defectCLeft  = (m_scanStop - m_scanStart) * left / (scanPixel -1) + m_scanStart;
        defectCRight = (m_scanStop - m_scanStart) * right / (scanPixel -1) + m_scanStart;
    }else{
        defectCLeft  = m_scanStop - ((m_scanStop - m_scanStart) * left / (scanPixel -1));
        defectCRight = m_scanStop - ((m_scanStop - m_scanStart) * right / (scanPixel -1));
    }

    _pConfig->group[m_groupId].afCursor[setup_CURSOR_S_REF] = defectCLeft;
    _pConfig->group[m_groupId].afCursor[setup_CURSOR_S_MES] = defectCRight;

    float scanPos = _process->SAxisIndexToDist(scanIndex);
    _process->SetupScanPos(scanPos);
    return true;
}

void AidedAnalysis::calculateSrcData()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    TOPC_INFO& _TOPCInfo  = _pConfig->group[m_groupId].TopCInfo;
    bool   Calculation = true;
    float  gateStart = _pConfig->group[m_groupId].gate[0].fStart;
    float  gateWidth = _pConfig->group[m_groupId].gate[0].fWidth;
    float  gateStop  = gateStart + gateWidth;
    float  indexOffset = _pConfig->group[m_groupId].fIndexOffset;
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
    realWidthStart = m_TopcWidthStart;
    realWidthStop  = m_TopcWidthStop;

    setup_PROBE_ANGLE _eAngle = _process->GetProbeAngle(m_groupId);
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
    slectRectInfo.pixelHeightStart = pixelHeightStart;
    slectRectInfo.pixelHeightStop  = pixelHeightStop;
    slectRectInfo.pixelWidthStart  = pixelWidthStart;
    slectRectInfo.pixelWidthStop   = pixelWidthStop;

    int scanPixelStart = _process->SAxisDistToIndex(m_scanStart);
    int scanPixelStop  = _process->SAxisDistToIndex(m_scanStop);

    topcWidthPixel = pixelWidthStop - pixelWidthStart + 1;
    scanPixel      = scanPixelStop - scanPixelStart + 1;
    srcData.clear();
    srcData.resize(topcWidthPixel*scanPixel);

    WDATA* pData;
    U8* _pMarker = _process->GetScanMarker(m_groupId);
    int i, j, k, m, n;
    float _fScale = _process->GetRefGainScale(m_groupId);
    int TmpValue;
    int _nScanOff = _process->GetScanOff(m_groupId);
    int _nScanMax = _process->GetRealScanMax() + _nScanOff;
    if(Calculation){
        if( m_orient == ORIENT_HORIZONTAL){
            for(i = scanPixelStart, j = 0; i <= scanPixelStop; i++ , j++){
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    pData = _process->GetScanPosPointer( m_groupId, i);
                    if(direction == 0){
                        for( k = pixelWidthStart, n = 0; k <= pixelWidthStop; k++,n++){
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
                            srcData[n*scanPixel + j] = TmpValue;
                        }
                    }else{
                        for( k = pixelWidthStop, n = 0; k >= pixelWidthStart; k--,n++){
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
                            srcData[n*scanPixel + j] = TmpValue;
                        }
                    }
                }
            }
        }else{
            for(i = scanPixelStop, j = 0; i >= scanPixelStart; i--, j++){
                if(_pMarker[i] && i >= _nScanOff && i < _nScanMax){
                    pData = _process->GetScanPosPointer( m_groupId, i);
                    int offset = j * topcWidthPixel;
                    if(direction == 0){
                        for( k = pixelWidthStart, n = 0; k <= pixelWidthStop; k++,n++){
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
                            srcData[ offset + n] = TmpValue;
                        }
                    }else{
                        for( k = pixelWidthStop, n = 0; k >= pixelWidthStart; k--,n++){
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
                            srcData[ offset + n] = TmpValue;
                        }
                    }
                }
            }
        }

    }
}

quint8 AidedAnalysis::getDataMax()
{
    if(m_dataMaxStatus){
        return m_dataMax;
    }
    quint8 max = 0;
    QVector<quint8>::const_iterator i;
    for( i = srcData.begin(); i != srcData.end(); i++){
        if(*i > max){
            max = *i;
        }
    }
    m_dataMaxStatus = true;
    m_dataMax = max;
    return max;
}

void AidedAnalysis::getAmpData(int &leftAmp, int &rightAmp)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    float methodThreshold = _process->GetDetermineThreshold(m_groupId, setup_EL);
    int max = methodThreshold * 255 / 100;
    QVector<int> Points_;
    Points_.clear();

    for(int i = 0; i < topcWidthPixel; i++){
        int offset = i*scanPixel;
        int buff = 0;
        int position = 0;
        for(int j = 0; j < scanPixel; j++){
            int temp = srcData[offset + j];
            if(temp >= buff){
                buff =  temp;
                position = j;
            }else{
                if(buff > max){
                    break;
                }else{
                    buff = temp;
                    position = j;
                }
            }
        }
        Points_.append(position);
    }
    int tempP = scanPixel - 1;
    int index = 0;
    for(int i = 0; i < Points_.size(); i++){
        if(Points_[i] < tempP){
            tempP = Points_[i];
            index = i;
        }
    }
    int offset = index * scanPixel + Points_[index];
    leftAmp = srcData[offset];

    Points_.clear();
    for(int i = 0; i < topcWidthPixel; i++){
        int offset = i*scanPixel;
        int buff = 0;
        int position = 0;
        for(int j = scanPixel - 1; j >= 0; j--){
            int temp = srcData[offset + j];
            if(temp >= buff){
                buff =  temp;
                position = j;
            }else{
                if(buff > max){
                    break;
                }else{
                    buff = temp;
                    position = j;
                }
            }
        }
        Points_.append(position);
    }
    tempP = 0;
    index = 0;
    for(int i = 0; i < Points_.size(); i++){
        if(Points_[i] > tempP){
            tempP = Points_[i];
            index = i;
        }
    }
    offset = index * scanPixel + Points_[index];
    rightAmp = srcData[offset];
}

void AidedAnalysis::getAmpDataWatershed(int &leftAmp, int &rightAmp)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    float methodThreshold = _process->GetDetermineThreshold(m_groupId, setup_EL);
    int max = methodThreshold * 255 / 100;
    int rows, cols;
    if( m_orient == ORIENT_HORIZONTAL){
        rows = topcWidthPixel;
        cols = scanPixel;
    }else{
        rows = scanPixel;
        cols = topcWidthPixel;
    }
    cv::Mat ima3( rows, cols, CV_8UC3, cv::Scalar(0,0,0));
    for(int i = 0; i < rows; i++){
        int offset = i*cols;
        uchar* data = ima3.ptr<uchar> (i);
        for(int j = 0; j < cols; j++){
            int xoff = 3 * j;
            uchar buff = srcData[offset + j];
            data[xoff] = buff;
            data[xoff + 1] = buff;
            data[xoff + 2] = buff;
        }
    }
    cv::Mat afterCanny;
    cv::Canny( ima3, afterCanny, max, 150);

    std::vector<std::vector<cv::Point>> contours;
//    std::vector<cv::Vec4i> hierarchy;
    cv::findContours( afterCanny, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //cv::findContours( afterCanny, contours, hierarchy, cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE,cv::Point());
    //cv::Mat imageContours = cv::Mat::zeros(ima3.size(),CV_8UC1);
//    cv::Mat marks(ima3.size(),CV_32S);
//    marks = cv::Scalar::all(0);
    //qDebug()<<"contours"<<contours.size();
    int defectNum = contours.size();
    cv::Rect boundRect;
    int left = scanPixel - 1;
    int right = 0;
    for(int index = 0; index < defectNum; index++){
        //cv::drawContours( marks, contours, index, cv::Scalar::all(255), 1, 8);
        boundRect = cv::boundingRect( cv::Mat( contours[index]));
        int x1, x2;
        if( m_orient == ORIENT_HORIZONTAL){
            x1 = boundRect.x;
            x2 = boundRect.x + boundRect.width;
        }else{
            x1 = boundRect.y;
            x2 = boundRect.y + boundRect.height;
        }

        if(x1 < left){
            left = x1;
        }
        if(x2 > right){
            right = x2;
        }
        //cv::drawContours( imageContours, contours, index, cv::Scalar(255), 1, 8, hierarchy);
    }
//    cv::Mat marksShows;
//    cv::convertScaleAbs( marks, marksShows);
//    cv::imshow("after Image", marksShows);
//    cv::watershed( ima3, marks);
//    cv::Mat afterWatershed;
//    cv::convertScaleAbs( marks, afterWatershed);

//    cv::imshow("origin Image", _paintBuff);
    //qDebug()<<"left"<<left<<"right"<<right;
    leftAmp  = left;
    rightAmp = right;
}
