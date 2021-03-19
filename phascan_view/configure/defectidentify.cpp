#include "defectidentify.h"
#include "gHeader.h"

DefectIdentify::DefectIdentify(int groupId, QObject *parent) :
    QObject(parent), m_groupId(groupId), m_identifyDone(false)
{

}

DefectIdentify::~DefectIdentify()
{

}

//分析数据
bool DefectIdentify::analysisData()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    GROUP_CONFIG& group = _pConfig->group[m_groupId];
    if(group.eGroupMode != setup_GROUP_MODE_PA ||  _pConfig->common.scanner.eScanEncoderType == setup_ENCODER_TYPE_TIMER
            || _pConfig->common.scanner.eScanType != setup_SCAN_TYPE_ONE_LINE){
        m_identifyDone = false;
        return false;
    }

    int scanQty = _process->GetScanMax();
    int lawQty = _process->GetGroupLawQty(m_groupId);
    int _nFrameSize = _process->GetTotalDataSize();
    int _nGroupOffset = _process->GetGroupDataOffset(m_groupId);
    int _nLawSize = group.nPointQty + setup_DATA_PENDIX_LENGTH;
    m_pointQty = group.nPointQty;
    m_lawQty = lawQty;
    m_frameDefects.clear();
    float start = group.gate[setup_GATE_A].fStart;
    float width = group.gate[setup_GATE_A].fWidth;
    unsigned int threshold = group.gate[setup_GATE_A].nThreshold;
    if(_process->is200Data()){
        threshold = threshold*255.0/200;
    }else{
        threshold = threshold*255.0/100;
    }


    QVector<float> SampleStart(lawQty);
    QVector<float> SampleRange(lawQty);
    QVector<float> Scale(lawQty);

    for(int i = 0; i < lawQty; i++){
        SampleStart[i] = _process->GetSampleStart( m_groupId, i);
        SampleRange[i] = _process->GetSampleRange( m_groupId, i);
        Scale[i] = group.nPointQty / SampleRange[i];
    }
    int _beamdis = group.nPointQty / group.fSampleRange * BEAMDIS;
    for(int i = 0; i < scanQty; i++){
        if(_pConfig->common.nRecMark[i]){
            WDATA* _pData = _process->GetShadowDataPointer();
            int _nFrameOffset = _nFrameSize * i;
            _pData += _nFrameOffset + _nGroupOffset;
            WDATA* lawData = _pData;
            QMap<int, QVector<beamData> > beamAss;
            for(int j = 0; j < lawQty; j++){
                int _fStart, _fWidth;
//                if(start < SampleStart[j]){
//                    _fStart = 0;
//                }else{
                    _fStart = Scale[j] * ( start - SampleStart[j]);
//                }

//                if(start + width > SampleStart[i] + SampleRange[i]){
//                    _fWidth = Scale[j] * (SampleStart[i] + SampleRange[i] - start) - 1;
//                }else{
                    _fWidth = Scale[j] * width;
//                }

                captureBeamAmps(_pData, j, _fStart, _fWidth, threshold, _beamdis, beamAss);
                _pData += _nLawSize;
            }

            captrueFrameAmps( i, _beamdis, beamAss, lawData);
        }
    }
    qDebug()<<"m_frameDefects"<<m_frameDefects.size();
    return true;
}

//通过scanPos取得缺陷的特征点集合，为单帧的集合，用于显示在S扫中，包含合计的外框和集合的极值点
void DefectIdentify::getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect)
{
    const QVector<defectRect> &buff = m_frameDefects.value(scanPos);
    if(!buff.size()){
        return;
    }
    QVector<defectRect>::const_iterator i;
    for(i = buff.begin(); i != buff.end(); ++i){
        QPointF points[3];
        for(int j = 0; j < 3; j++){
            int lawId = i->_rect[j].lawId;
            int dataIndex = i->_rect[j].dataIndex;
            transformPolarToCartesian(lawId, dataIndex, points[j]);
        }
        MaxPoint.append(points[0]);
        qreal left, right, top, bottom;
        if(points[1].x() > points[2].x()){
            left = points[2].x();
            right = points[1].x();
        }else{
            left = points[1].x();
            right = points[2].x();
        }

        if(points[1].y() > points[2].y()){
            top = points[2].y();
            bottom = points[1].y();
        }else{
            top = points[1].y();
            bottom = points[2].y();
        }

        QPointF topLeft( left, top);
        QPointF bottomRight( right, bottom);
        QRectF _rect(topLeft, bottomRight);
        rect.append(_rect);
    }
}

//找出每条beam的特征点
void DefectIdentify::captureBeamAmps( WDATA* Data, int lawId, int start, int width, int height, int beamdis, QMap<int, QVector<beamData> > &beamAmps)
{
    //DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    bool inset = false;
    int maxData = 0;
    QVector<beamData> buff;
    QVector<beamData> setbeam;
    //找出超过闸门阈值的特征点
    int end = start + width;
    if(end > m_pointQty){
        end = m_pointQty;
    }
    for(int i = start; i < end; i++){
        if(i >= 0){
            if(Data[i] >= height){
                if(inset){
                    beamData data;
                    data.lawId = lawId;
                    data.dataIndex = i;
                    data.value = Data[i];
                    data.leftValue = Data[i-1];
                    data.rightValue = Data[i+1];
                    if(maxData < data.value){
                        maxData = data.value;
                    }
                    buff.append(data);
                }else{
                    buff.clear();
                    beamData data;
                    data.lawId = lawId;
                    data.dataIndex = i;
                    data.value = Data[i];
                    data.leftValue = Data[i-1];
                    data.rightValue = Data[i+1];
                    if(maxData < data.value){
                        maxData = data.value;
                    }
                    buff.append(data);
                    inset = true;
                }
            }else{
                if(inset){
                    beamData _data = filterValue( buff, maxData);
                    if(_data.dataIndex >= 0){
                        setbeam.append(_data);
                    }
                    inset = false;
                }
            }
        }
    }

    //合并距离太近的特征点
    int size = setbeam.size();
    QVector<beamData> mergebeam;
    if(size){

        beamData data;
        data.dataIndex = -100;
        QVector<beamData>::Iterator i = setbeam.begin();
        while(i != setbeam.end()){
            if(abs(i->dataIndex - data.dataIndex) < beamdis){
                if(data.value > i->value){
                    //i = setbeam.erase(i);
                    ++i;
                }else{
                    data = *i;
                    //--i;
                    //i = setbeam.erase(i);
                    mergebeam.removeLast();
                    mergebeam.append(*i);
                    ++i;
                }
            }else{
                data = *i;
                mergebeam.append(*i);
                ++i;
            }
        }
        //qDebug()<<"siez"<<size<<mergebeam.size();
    }
    if(mergebeam.size()){
        beamAmps.insert(lawId, mergebeam);
    }

}

//计算出一帧数据的特征点集合，合并每条beam与邻近beam距离很近的点，并找出这些点的集合的边界
void DefectIdentify::captrueFrameAmps( int scanId, int beamdis, QMap<int, QVector<beamData> > &beamAmps, WDATA* Data)
{
    int size = beamAmps.size();
    if(size){
        //qDebug()<<"captrueFrameAmps"<<size;
        QMap<int, QVector<beamData> >::const_iterator i = beamAmps.constBegin();
        int lastLaw = -2;
        QList<QVector<beamData> > temp;
        //QVector<QVector<beamData> > frameAmps;
        while (i != beamAmps.constEnd()){
            if(lastLaw != i.key() - 1){
                lastLaw = i.key();
                QVector<beamData> value = i.value();
                QVector<beamData>::Iterator j;
                for(j = value.begin(); j != value.end(); ++j){
                    QVector<beamData> buff;
                    buff.append(*j);
                    temp.append(buff);
                }
                ++i;
            }else{
                QVector<beamData> value = i.value();
                QVector<beamData>::Iterator j;
                for(j = value.begin(); j != value.end(); ++j){
                    beamData data = *j;
                    bool insert = false;
                    QList<QVector<beamData> >::iterator index;
                    for(index = temp.begin(); index != temp.end(); ++index){
                        beamData listValue = (*index).last();
                        if(listValue.lawId == lastLaw && abs(data.dataIndex - listValue.dataIndex) < beamdis){
                            (*index).append(data);
                            insert = true;
                            break;
                        }
                    }
                    if(!insert){
                        QVector<beamData> buff;
                        buff.append(data);
                        temp.append(buff);
                    }
                }
                lastLaw = i.key();
                ++i;
            }
        }
//        int lastLaw = -2;
//        for(int i = 0; i < m_lawQty; i++){
//            const QVector<beamData> value = beamAmps.value(i);
//            if( value.size()){
//                if(lastLaw != i - 1){
//                    lastLaw = i;
//                    QVector<beamData>::Iterator j;
//                    for(j = value.begin(); j != value.end(); ++j){
//                        QVector<beamData> buff;
//                        buff.append(*j);
//                        temp.append(buff);
//                    }
//                }else{
//                    QVector<beamData>::Iterator j;
//                    for(j = value.begin(); j != value.end(); ++j){
//                        beamData data = *j;
//                        bool insert = false;
//                        QList<QVector<beamData> >::iterator index;
//                        for(index = temp.begin(); index != temp.end(); ++index){
//                            beamData listValue = (*index).last();
//                            if(listValue.lawId == lastLaw && abs(data.dataIndex - listValue.dataIndex) < beamdis){
//                                (*index).append(data);
//                                insert = true;
//                                break;
//                            }
//                        }
//                        if(!insert){
//                            QVector<beamData> buff;
//                            buff.append(data);
//                            temp.append(buff);
//                        }
//                    }
//                    lastLaw = i;
//                }
//            }
//        }
        size = temp.size();
        if(size){
            QVector<defectRect> defectrect(size);
            for(int i = 0; i < size; ++i){
                int maxValue = findMaxValue(temp.at(i));
                beamData _data = filterValue( temp.at(i), maxValue);
                //defectRect &defect = defectrect.at(i);
                defectrect[i].valueMax = maxValue;
                defectrect[i]._rect[0].dataIndex = _data.dataIndex;
                defectrect[i]._rect[0].lawId = _data.lawId;
                defectrect[i]._rect[0].value = _data.value;
                findRectBorder(Data, maxValue, beamdis, &defectrect[i]._rect[1], temp.at(i));
            }
            m_frameDefects.insert(scanId, defectrect);
        }
    }
}

//找出集合里面的极值点
DefectIdentify::beamData DefectIdentify::filterValue(const QVector<beamData> &beamDatas, int maxValue)
{
    int size = beamDatas.size();
    beamData data;
    QVector<beamData> buff;
    buff.clear();
    for(int i = 0; i < size; i++){
        if(beamDatas[i].value == maxValue){
            buff.append(beamDatas[i]);
        }
    }
    size = buff.size();
    if(size == 0){
        data.dataIndex = -1;
    }else if(size%2 == 1){
        int index = (size - 1)/2;
        data = buff[index];
    }else{
        int indexLeft = size/2 - 1;
        int indexRight = size/2;
        int sumLeft = buff[indexLeft].value + buff[indexLeft].leftValue + buff[indexLeft].rightValue;
        int sumRight = buff[indexRight].value + buff[indexRight].leftValue + buff[indexRight].rightValue;
        if(sumLeft >= sumRight){
            data = buff[indexLeft];
        }else{
            data = buff[indexRight];
        }
    }
    return data;
}

//查找集合里面的最大值，以此为此集合的极值点
int DefectIdentify::findMaxValue(const QVector<beamData> &beamDatas)
{
    int maxValue = 0;
    QVector<beamData>::const_iterator i;
    for (i = beamDatas.begin(); i != beamDatas.end(); ++i){
        if(i->value > maxValue){
            maxValue = i->value;
        }
    }
    return maxValue;
}

//找出特种点群的外边沿，方法是此区域峰值一半的点为外边沿，查找方法是在两端寻找sa在1mm范围内点的最大值是否等于-6dB,
void DefectIdentify::findRectBorder( WDATA* Data, int maxValue, int beamdis, beamAmp *borders, const QVector<beamData> &data)
{
    int borderValue = maxValue / 2;
    int _nLawSize = m_pointQty + setup_DATA_PENDIX_LENGTH;
    const beamData &leftData = data.first();
    const beamData &rightData = data.last();
    //查找左边界
    if(leftData.value < borderValue || leftData.lawId == 0){
        borders[0].dataIndex = leftData.dataIndex;
        borders[0].lawId = leftData.lawId;
        borders[0].value = leftData.value;
    }else{
        int curLawId = leftData.lawId;
        int curDataIndex = leftData.dataIndex;
        int curValue = leftData.value;
        for(int i = leftData.lawId - 1; i >= 0; --i){
            int rangeLeft = curDataIndex - (beamdis/2);
            int rangeRight = curDataIndex + (beamdis/2);
            if(rangeLeft < 0){
                rangeLeft = 0;
            }
            if(rangeRight >= m_pointQty){
                rangeRight = m_pointQty - 1;
            }
            WDATA* lawData = Data + i*_nLawSize;
            int value, postion;
            findMaxValueAndPos(lawData, rangeLeft, rangeRight, value, postion);
            if(value <= borderValue){
                int diff1 = abs(borderValue - curValue);
                int diff2 = abs(borderValue - value);
                if(diff1 > diff2){
                    curLawId = i;
                    curDataIndex = postion;
                    curValue = value;
                }
                break;
            }else{
                curLawId = i;
                curDataIndex = postion;
                curValue = value;
            }
        }
        borders[0].dataIndex = curDataIndex;
        borders[0].lawId = curLawId;
        borders[0].value = curValue;
    }

    //查找右边界
    if(rightData.value < borderValue || rightData.lawId == m_lawQty - 1){
        borders[1].dataIndex = rightData.dataIndex;
        borders[1].lawId = rightData.lawId;
        borders[1].value = rightData.value;
    }else{
        int curLawId = rightData.lawId;
        int curDataIndex = rightData.dataIndex;
        int curValue = rightData.value;
        for(int i = rightData.lawId; i < m_lawQty; ++i){
            int rangeLeft = curDataIndex - (beamdis/2);
            int rangeRight = curDataIndex + (beamdis/2);
            if(rangeLeft < 0){
                rangeLeft = 0;
            }
            if(rangeRight >= m_pointQty){
                rangeRight = m_pointQty - 1;
            }
            WDATA* lawData = Data + i*_nLawSize;
            int value, postion;
            findMaxValueAndPos(lawData, rangeLeft, rangeRight, value, postion);
            if(value <= borderValue){
                int diff1 = abs(borderValue - curValue);
                int diff2 = abs(borderValue - value);
                if(diff1 > diff2){
                    curLawId = i;
                    curDataIndex = postion;
                    curValue = value;
                }
                break;
            }else{
                curLawId = i;
                curDataIndex = postion;
                curValue = value;
            }
        }
        borders[1].dataIndex = curDataIndex;
        borders[1].lawId = curLawId;
        borders[1].value = curValue;
    }
}

//找出给定范围的同一beam下的幅值最大值的值和点位置
void DefectIdentify::findMaxValueAndPos( WDATA* Data, int start, int end, int &value, int &postion)
{
    value = 0;
    postion = start;
    for(int i = start; i <= end; i++){
        if(Data[i] > value){
            value = Data[i];
            postion = i;
        }
    }
}

//将极坐标转换为直角坐标，lawId:beam编号， dataIndex：数据位于beam上的点位置
void DefectIdentify::transformPolarToCartesian(int lawId, int dataIndex, QPointF &postion)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    GROUP_CONFIG& _group = _pConfig->group[m_groupId];
    float indexOffset = _group.fIndexOffset;
    float _fDist = _process->DistDotPosToMm( m_groupId, dataIndex);
    float _fAngle  = DEGREE_TO_ARCH(_process->GetLawAngle( m_groupId, lawId));
    float Posy = _fDist * cos(_fAngle);
    float posx = _fDist * sin(_fAngle) + _process->GetBeamInsertPos( m_groupId, lawId);
    switch (_group.eSkew) {
    case setup_PROBE_PART_SKEW_0:
        posx = posx;
        break;
    case setup_PROBE_PART_SKEW_90:
        posx += indexOffset;
        break;
    case setup_PROBE_PART_SKEW_180:
        posx = -posx;
        break;
    case setup_PROBE_PART_SKEW_270:
        posx = -posx + indexOffset;
        break;
    default:
        posx = posx;
        break;
    }
    postion.setX(posx);
    postion.setY(Posy);
}
