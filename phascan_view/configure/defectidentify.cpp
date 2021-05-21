#include "defectidentify.h"
#include "gHeader.h"
#include <cmath>
#include "process/CalcMeasurement.h"

DefectIdentify::DefectIdentify(int groupId, QObject *parent) :
    QObject(parent), m_groupId(groupId), m_identifyDone(false)
{

}

DefectIdentify::~DefectIdentify()
{

}

//分析数据，得到每一帧的缺陷
bool DefectIdentify::analysisData(int scanStart, int scanStop, int beamStart, int beamStop)
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
    int _nLawSize = group.nPointQty + setup_DATA_PENDIX_LENGTH;//data文件的组成是a扫数据+PENDIX_LENGTH要定位下一条beam的数据就要加上这个偏移量
    m_pointQty = group.nPointQty;
    m_lawQty = lawQty;
    m_frameDefects.clear();
    float start = group.gate[setup_GATE_A].fStart;
    float width = group.gate[setup_GATE_A].fWidth;
    unsigned int threshold = group.gate[setup_GATE_A].nThreshold;
    if(_process->is200Data()){
        threshold = ceil(threshold*255.0/200);
    }else{
        threshold = ceil(threshold*255.0/100);
    }

    QVector<float> SampleStart(lawQty);
    QVector<float> SampleRange(lawQty);
    QVector<float> Scale(lawQty);

    for(int i = beamStart; i < beamStop; i++){
        SampleStart[i] = _process->GetSampleStart( m_groupId, i);
        SampleRange[i] = _process->GetSampleRange( m_groupId, i);
        Scale[i] = group.nPointQty / SampleRange[i];
    }
    int _beamdis = group.nPointQty / group.fSampleRange * BEAMDIS;//在beamdis范围内两个点就要合并成一个点，不在范围之内就是两个独立的点.每mm内有多少点
    for(int i = scanStart; i < scanStop; i++){
        if(_pConfig->common.nRecMark[i]){
            WDATA* _pData = _process->GetShadowDataPointer();
            int _index = _process->GetRealScanIndex(m_groupId, i);
            int _nFrameOffset = _nFrameSize * _index;
            _pData += _nFrameOffset + _nGroupOffset;

            WDATA* lawData = _pData;
            QMap<int, QVector<beamData> > beamAss; // key:帧索引，value:帧上所有beam上的峰值集合
            _pData += beamStart * _nLawSize;
            for(int j = beamStart; j < beamStop; j++){
                int _fStart, _fWidth;
//                if(start < SampleStart[j]){
//                    _fStart = 0;
//                }else{
                    _fStart = Scale[j] * ( start - SampleStart[j]); // 该beam在闸门内的第一个采样点
//                }

//                if(start + width > SampleStart[i] + SampleRange[i]){
//                    _fWidth = Scale[j] * (SampleStart[i] + SampleRange[i] - start) - 1;
//                }else{
                    _fWidth = Scale[j] * width; // 将闸门的mm转换为点数值，闸门范围内有多少个点。该beam在闸门内的最后一个采样点
//                }

                captureBeamAmps(_pData, j, _fStart, _fWidth, threshold, _beamdis, beamAss);
                _pData += _nLawSize;
            }

            captrueFrameAmps( i, _beamdis, beamAss, lawData);
        }
    }
//    qDebug()<<"m_frameDefects"<<m_frameDefects.size();

    return true;
}

bool DefectIdentify::analysisDefect()
{
    ParameterProcess* _process = ParameterProcess::Instance();
    if (m_scanStart == 0 && m_scanStop == 0 && m_beamStart == 0 && m_beamStop == 0) {
        m_scanStop  = _process->GetScanMax();
        m_beamStop  = _process->GetGroupLawQty(m_groupId);
    }
    bool ret;
    ret = analysisData(m_scanStart, m_scanStop, m_beamStart, m_beamStop);

    if (ret) {
        m_defectsRectL.clear();
        m_defectsRectH.clear();
        m_scanIds.clear();
        m_lawIds.clear();
        m_defectsBetweenFrames.clear();
        QMap<int, QVector<QRectF>> _Rects;  // key: 帧， value：帧上所有缺陷矩形
        QMap<int, QVector<defectRect>> _DefectRects;
        QList<int> keys = m_frameDefects.keys();
        for (int i = 0; i < keys.count(); ++i) {
            QVector<QPointF> MaxPoint;
            QVector<QRectF> rect;
            QVector<defectRect> defectRects;
            getDefectInfo(keys[i], MaxPoint, rect, defectRects);
            _Rects.insert(keys[i], rect);
            _DefectRects.insert(keys[i], defectRects);
        }

        for (int i = 0; i < keys.count() - 1; ++i) { // 遍历所有帧, i 帧索引
            QVector<QRectF> rectsCurrentFrame = _Rects.value(keys[i]);
            for (int j = 0; j < rectsCurrentFrame.count(); ++j) { // 遍历当前帧所有的缺陷， j 缺陷索引
                if (_DefectRects[keys[i]][j].bMergeStatus) {
                    continue;// 若已经合并，无需继续比较
                }
                defectRect maxDefectRect = _DefectRects[keys[i]][j];
                float maxArea            = getRectFArea(rectsCurrentFrame[j]);
                QRectF maxRect           = rectsCurrentFrame[j];
                int scanIdEnd            = keys[i];
                int scanIdStart          = keys[i];
                int scanId               = keys[i];
                int maxValue             = maxDefectRect.valueMax;
                defectRect specialRect   = _DefectRects[keys[i]][j];
                QRectF rect              = rectsCurrentFrame[j];
                QVector<specialDefect> specials;
                _DefectRects[keys[i]][j].bMergeStatus = true;
                specialDefect tmp;
                tmp.valueMax    = maxValue;
                tmp.specialRect = specialRect;
                tmp.scanId      = scanId;
                tmp.rect        = rect;
                specials.append(tmp);

                for (int k = i + 1; k < keys.count(); ++k) { // 每一个缺陷与后面所有连续帧的所有缺陷比较, k 帧索引
                    QVector<QRectF> rectsNextFrame = _Rects.value(keys[k]);

                    if (keys[k-1] != keys[k] - 1) { // 帧不连续，跳出循环，先记下这个特征点，后边再根据情况合并
                        break;
                    }

                    for (int index = 0; index < rectsNextFrame.count(); ++index) {
                        if (_DefectRects[keys[k]][index].bMergeStatus) {
                            continue;// 若已经合并，无需继续比较
                        }
                        QRectF intersectedRect = maxRect.intersected(rectsNextFrame[index]);
                        float areaNext = getRectFArea(rectsNextFrame[index]);
                        float minArea  = qMin(maxArea, areaNext);

                        if (getRectFArea(intersectedRect) >= minArea * m_scale) {
                            _DefectRects[keys[k]][index].bMergeStatus = true;
                            maxRect = rectsNextFrame[index];
                            maxArea = areaNext;
                            if (maxValue < _DefectRects[keys[k]][index].valueMax) {
                                maxValue    = _DefectRects[keys[k]][index].valueMax;
                            }
                            specialDefect tmp;
                            tmp.valueMax    = _DefectRects[keys[k]][index].valueMax;
                            tmp.specialRect = _DefectRects[keys[k]][index];
                            tmp.scanId      = keys[k];
                            tmp.rect        = rectsNextFrame[index];
                            specials.append(tmp);
                            scanIdEnd = keys[k];
                        }
                    }
                }

                if (specials.count()) {
                    specialDefect _out;
                    findMaxSpecialDefect(maxValue, specials, _out);
                    defectsBetweenFrames defects;
                    defects.scanIdStart   = scanIdStart;
                    defects.scanIdEnd     = scanIdEnd;
                    defects.length        = scanIdEnd - scanIdStart;
                    defects.special       = _out;
                    defects.allSpecial    = specials;
                    defects.bMergedStatus = false;
                    m_defectsBetweenFrames.append(defects);
                }
            }
        }
    }

    mergeDefects();
    measureLength();
    if (m_bAutoMerge) {
        mergeDefects();// 测长之后再次合并缺陷，长度方向
    }
    if (m_heightMeasureMethod == TipDiffraction) {
        // 高度方向做合并
        mergeDefectsTipDiffraction();
    }
    calDefectRect();
//    forceMerge();
    return ret;
}

void DefectIdentify::getDefectInfo(int scanPos, QVector<QPointF> &MaxPoint, QVector<QRectF> &rect, QVector<defectRect> &defectRects)
{
    const QVector<defectRect> &buff = m_frameDefects.value(scanPos);
    defectRects = buff;
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

void DefectIdentify::getDefectInfo(QVector<QRectF> &rectL, QVector<QRectF> &rectH, QVector<int> &scanId, QVector<int> &lawId)
{
    rectL  = m_defectsRectL;
    rectH  = m_defectsRectH;
    scanId = m_scanIds;
    lawId  = m_lawIds;
}

void DefectIdentify::setRange(int scanStart, int scanStop, int beamStart, int beamStop)
{
    m_scanStart = scanStart;
    m_scanStop  = scanStop;
    m_beamStart = beamStart;
    m_beamStop  = beamStop;
}

/**
 * @brief DefectIdentify::setSscanRange 设置S扫检测区域
 * @param _recet
 */
void DefectIdentify::setSscanRange(QRectF _recet)
{
    m_rectSscan = _recet;
    m_bSscanRangeIsSet = true;
}

void DefectIdentify::setSscanRangeValid(bool _isValid)
{
    m_bSscanRangeIsSet = _isValid;
}

void DefectIdentify::setIdentifyStatus(bool status)
{
    m_identifyDone = status;
    if (m_identifyDone) {
        m_scanStart = 0;
        m_scanStop  = 0;
        m_beamStart = 0;
        m_beamStop  = 0;
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
                    maxData = 0;
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
                        if(listValue.lawId == lastLaw && abs(data.dataIndex - listValue.dataIndex) < beamdis){// 每条beam与邻近beam上的特征点距离小于beamdis，合并
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

        size = temp.size();
        if(size){
            QVector<defectRect> defectrect;
            for(int i = 0; i < size; ++i){
                int maxValue = findMaxValue(temp.at(i));
                int maxValueCnt = 0;
                beamData _data = filterValue( temp.at(i), maxValue, &maxValueCnt);
                QPointF point;
                if (m_bSscanRangeIsSet) {
                    transformPolarToCartesian(_data.lawId, _data.dataIndex, point);
                    if (!m_rectSscan.contains(point)) {
                        continue;
                    }
                }
                defectRect defect;
                defect.valueMax = maxValue;
                defect._rect[0].dataIndex = _data.dataIndex;
                defect._rect[0].lawId = _data.lawId;
                defect._rect[0].value = _data.value;
                defect.valueMaxCount = maxValueCnt;
                defect.bMergeStatus = false;

                QVector<beamData> peakDatas;
                if (m_heightMeasureMethod == HalfWave || m_heightMeasureMethod == TipDiffraction) { // 6db 法 。端点衍射法默认用6db测每一帧缺陷的大小
                    peakDatas.append(_data);
                } else if (m_heightMeasureMethod == EndPointHalfWave){ // 端点6db 法
                    findAllPeakDatas(temp.at(i), peakDatas);
                } else {
                    // 绝对灵敏度法
                    peakDatas = temp[i];
                }
                findRectBorder(Data, maxValue, beamdis, &defect._rect[1], peakDatas);
                defectrect.append(defect);
//                calViA(scanId, defectrect[i]._rect[1].lawId, &defectrect[i]._ViARange[0]);
//                calDA(scanId, defectrect[i]._rect[1].lawId, &defectrect[i]._DARange[0]);
//                calViA(scanId, defectrect[i]._rect[2].lawId, &defectrect[i]._ViARange[1]);
//                calDA(scanId, defectrect[i]._rect[2].lawId, &defectrect[i]._DARange[1]);

//                // 重新排列DA
//                if (defectrect[i]._DARange[0] > defectrect[i]._DARange[1]) {
//                    float tmp = defectrect[i]._DARange[0];
//                    defectrect[i]._DARange[0] = defectrect[i]._DARange[1];
//                    defectrect[i]._DARange[1] = tmp;
//                }
            }
//            QVector<defectRect> _rect;
//            filterSameDefect(defectrect, _rect);
            m_frameDefects.insert(scanId, defectrect);
        }
    }
}

//找出集合里面的极值点
DefectIdentify::beamData DefectIdentify::filterValue(const QVector<beamData> &beamDatas, int maxValue, int *maxValueCount)
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
    if (maxValueCount != nullptr) {
        *maxValueCount = size;
    }
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

// 找出所有的波峰
void DefectIdentify::findAllPeakDatas(const QVector<beamData> &beamDatas, QVector<beamData> &peakDatas)
{
    if (beamDatas.isEmpty()) return;

    int cnt = beamDatas.count();
    if (cnt < 3) {
        int index = 0;
        int max = beamDatas.at(0).value;
        for (int i = 1; i < cnt; ++i) {
            if (beamDatas.at(i).value > max) {
                index = i;
                max = beamDatas.at(i).value;
            }
        }
        peakDatas.append(beamDatas.at(index));
        return;
    }
    if (beamDatas.at(0).value > beamDatas.at(1).value) {
         peakDatas.append(beamDatas.at(0));
    }
    for (int i = 1; i <= cnt - 2; ++i) {
        if (beamDatas.at(i).value >= beamDatas.at(i-1).value && beamDatas.at(i).value > beamDatas.at(i+1).value) {
            peakDatas.append(beamDatas.at(i));
        } else if (i == cnt - 2) {
            if (beamDatas.at(i).value >= beamDatas.at(i-1).value && beamDatas.at(i).value < beamDatas.at(i+1).value) {
                peakDatas.append(beamDatas.at(i + 1));
            }
        }
    }
}

//找出特种点群的外边沿，方法是此区域峰值一半的点为外边沿，查找方法是在两端寻找sa在1mm范围内点的最大值是否等于-6dB,
void DefectIdentify::findRectBorder( WDATA* Data, int maxValue, int beamdis, beamAmp *borders, const QVector<beamData> &data)
{
    float borderValue = maxValue / 2.0;
    int _nLawSize = m_pointQty + setup_DATA_PENDIX_LENGTH;
    if (data.isEmpty()) return;

    const beamData &leftData  = data.first();
    const beamData &rightData = data.last();
    if (m_heightMeasureMethod == AbsoluteSensitivity) {
        borders[0].dataIndex = leftData.dataIndex;
        borders[0].lawId     = leftData.lawId;
        borders[0].value     = leftData.value;

        borders[1].dataIndex = rightData.dataIndex;
        borders[1].lawId     = rightData.lawId;
        borders[1].value     = rightData.value;
        return;
    }
    //查找左边界
    borderValue = leftData.value / 2.0;
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
                float diff1 = log10((curValue * 1.0) / borderValue);//abs(borderValue - curValue); 取对数
                float diff2 = log10((borderValue * 1.0) / value);//abs(borderValue - value);
                if(diff1 > diff2){ // 取与borderValue接近的点
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
    borderValue = rightData.value / 2;
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
                float diff1 = log10((curValue * 1.0) / borderValue);//abs(borderValue - curValue);
                float diff2 = log10((borderValue * 1.0) / value);//abs(borderValue - value);
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

float DefectIdentify::transformCartesianToPolar(int lawId, float _xPos)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    GROUP_CONFIG& _group = _pConfig->group[m_groupId];
    float indexOffset = _group.fIndexOffset;

    switch (_group.eSkew) {
    case setup_PROBE_PART_SKEW_0:
        _xPos = _xPos;
        break;
    case setup_PROBE_PART_SKEW_90:
        _xPos -= indexOffset;
        break;
    case setup_PROBE_PART_SKEW_180:
        _xPos = -_xPos;
        break;
    case setup_PROBE_PART_SKEW_270:
        _xPos = -_xPos + indexOffset;
        break;
    default:
        _xPos = _xPos;
        break;
    }

    float _fAngle  = DEGREE_TO_ARCH(_process->GetLawAngle( m_groupId, lawId));
    float s        = qFuzzyIsNull(sin(_fAngle)) ? 1 : sin(_fAngle);
    float _fDist = (_xPos - _process->GetBeamInsertPos( m_groupId, lawId)) / s;

    return _fDist;
}

void DefectIdentify::calViA( int scanId, int lawId, float *pResult)
{
    PEAK_CONFIG peakInfo[setup_GATE_MAX];
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG* config = &(m_pConfig->group[m_groupId]);

    ParameterProcess* _process = ParameterProcess::Instance() ;
    _process->GetGatePeakInfos(m_groupId, scanId, lawId, peakInfo);
//    GATE_CONFIG* A_pGate = _process->GetGateInfo(m_groupId , setup_GATE_A ) ;
//    ret = CalViDist(nGroupId_ , nLaw_ , setup_GATE_A , pResult_) ;
    int ret = 0;
//	ret = CalPDist(m_groupId ,lawId ,  setup_GATE_A , _fViA1 ) ;
    float _nHeight = peakInfo[setup_GATE_A].fGh ;
    float _fAmp    = peakInfo[setup_GATE_A].fAmp;

    _fAmp = fabs(_fAmp);
    if(_nHeight < 1) _nHeight = 1  ;

    if(_nHeight > _fAmp)
        ret  =  -1 ;

    if(_process->GetGateInfo(m_groupId , setup_GATE_A)->eMeasure){
        *pResult = peakInfo[setup_GATE_A].fLEdge + _process->GetBeamInsertPos(m_groupId  , lawId);
    }else{
        *pResult = peakInfo[setup_GATE_A].fL + _process->GetBeamInsertPos(m_groupId  , lawId);
    }

    setup_PROBE_ANGLE _eSkew = _process->GetGroupSkewType(m_groupId)  ;
    float  _fIndexOffset ;
    _process->GetWedgePosition( m_groupId , NULL , &_fIndexOffset );
    if(setup_PROBE_PART_SKEW_90 == _eSkew)
    {
        *pResult +=_fIndexOffset ;
    }
    else if(setup_PROBE_PART_SKEW_270  == _eSkew )
    {
        *pResult =_fIndexOffset - *pResult ;
    }
}

void DefectIdentify::calDA(int scanId, int lawId, float *pResult)
{
    PEAK_CONFIG peakInfo[setup_GATE_MAX];
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG* config = &(m_pConfig->group[m_groupId]);

    ParameterProcess* _process = ParameterProcess::Instance() ;
    _process->GetGatePeakInfos(m_groupId, scanId, lawId, peakInfo);
    GATE_CONFIG* A_pGate = _process->GetGateInfo(m_groupId , setup_GATE_A ) ;

    if(A_pGate->eMeasure){
        *pResult = peakInfo[setup_GATE_A].fDEdge;
    }else{
        *pResult = peakInfo[setup_GATE_A].fD;
    }
}

// 找出最特殊的那个缺陷作为该集群的特征点
void DefectIdentify::findMaxSpecialDefect(int maxValue, const QVector<DefectIdentify::specialDefect> &specils, specialDefect &_out)
{
    QVector<DefectIdentify::specialDefect> _buff;
    for (int i = 0; i < specils.count(); ++i) {
        if (maxValue == specils.at(i).valueMax) {
            _buff.append(specils.at(i));
        }
    }

    int valueCntMax = 0;
    for (auto &i : _buff){
        if(i.specialRect.valueMaxCount > valueCntMax){
            valueCntMax = i.specialRect.valueMaxCount;
        }
    }

    QVector<DefectIdentify::specialDefect> buff;
    for (auto &i : _buff) {
        if (i.specialRect.valueMaxCount == valueCntMax) {
            buff.append(i);
        }
    }
    _buff.clear();

    int count = buff.count();
    if (count == 0) {
        return;
    }
    if (count % 2 == 1) {
        int index = (count - 1) / 2;
        _out = buff.at(index);
    } else {
        int indexLeft = count / 2 - 1;
        int indexRight = count / 2;
        int leftDataIndex = buff.at(indexLeft).specialRect._rect[0].dataIndex;
        int rightDataIndex = buff.at(indexRight).specialRect._rect[0].dataIndex;
        int leftScanId = buff.at(indexLeft).scanId;
        int rightScanId = buff.at(indexRight).scanId;
        int leftLawId = buff.at(indexLeft).specialRect._rect[0].lawId;
        int rightLawId = buff.at(indexRight).specialRect._rect[0].lawId;

        ParameterProcess* _process = ParameterProcess::Instance();
        WDATA* _pData = _process->GetShadowDataPointer();
        WDATA* lawData = _process->GetDataAbsolutePosPointer(m_groupId, leftScanId - 1, leftLawId, _pData);
        int leftData1 = lawData[leftDataIndex];
        lawData = _process->GetDataAbsolutePosPointer(m_groupId, leftScanId + 1, leftLawId, _pData);
        int leftData2 = lawData[leftDataIndex];

        lawData = _process->GetDataAbsolutePosPointer(m_groupId, rightScanId - 1, rightLawId, _pData);
        int rightData1 = lawData[rightDataIndex];
        lawData = _process->GetDataAbsolutePosPointer(m_groupId, rightScanId + 1, rightLawId, _pData);
        int rightData2 = lawData[rightDataIndex];

        int sumLeft = leftData1 + leftData2;
        int sumRight = rightData1 + rightData2;

        if(sumLeft >= sumRight){
            _out = buff[indexLeft];
        }else{
            _out = buff[indexRight];
        }
    }
}

/**
 * @brief DefectIdentify::measureLength 对每个特征点进行测长
 */
void DefectIdentify::measureLength()
{
    if (m_defectsBetweenFrames.count() == 0) return;

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    GROUP_CONFIG& group = _pConfig->group[m_groupId];

    auto pHead = m_defectsBetweenFrames.begin();
    auto end = m_defectsBetweenFrames.end();
    while(pHead != end) {
        if (!pHead->bMergedStatus) {
            defectsBetweenFrames &_defect = *pHead;
            if (m_lengthMeasureMethod == AbsoluteSensitivity) {
               // 绝对灵敏度法不需要再做处理
                continue;
           }

           PEAK_CONFIG peakInfo[setup_GATE_MAX];
           QVector<int> borders;
           borders.clear();
           if (m_lengthMeasureMethod == HalfWave) { // 6db 法
               int scanId           = _defect.special.scanId;
               _process->GetGatePeakInfos(m_groupId, scanId, _defect.special.specialRect._rect[0].lawId, peakInfo);
               float borderValue    = pow(10.0, group.fRefGain / 20.0) * peakInfo[setup_GATE_A].fAmp / 2.0;
               float curValue       = borderValue;
               for (int i = _defect.special.specialRect._rect[1].lawId; i <= _defect.special.specialRect._rect[2].lawId; ++i) {
                   // 查找左边界
                   if (scanId == m_scanStart) {
                       borders.append(scanId);
                   }
                   for (int j = scanId - 1; j >= m_scanStart; --j) {
                       _process->GetGatePeakInfos(m_groupId, j, i, peakInfo);
                       float value = pow(10.0, group.fRefGain / 20.0) * peakInfo[setup_GATE_A].fAmp;

                       if (value <= borderValue) {
                           float diff1 = log10((curValue * 1.0) / borderValue);
                           float diff2 = log10((borderValue * 1.0) / value);
                           if((diff1 > diff2) || qFuzzyIsNull(diff1)){ // 取与borderValue接近的点
                               borders.append(j);
                           } else {
                               borders.append(j + 1);
                           }
                           break;
                       } else if (j == m_scanStart) {
                           borders.append(j);
                       } else {
                           curValue = value;
                       }
                   }

                   // 查找右边界
                   if (scanId == m_scanStop) {
                       borders.append(scanId);
                   }
                   for (int j = scanId + 1; j <= m_scanStop; ++j) {
                       _process->GetGatePeakInfos(m_groupId, j, i, peakInfo);
                       float value = pow(10.0, group.fRefGain / 20.0) * peakInfo[setup_GATE_A].fAmp;
                       if (value <= borderValue) {
                           float diff1 = log10((curValue * 1.0) / borderValue);
                           float diff2 = log10((borderValue * 1.0) / value);
                           if((diff1 > diff2) || qFuzzyIsNull(diff1)){ // 取与borderValue接近的点
                               borders.append(j);
                           } else {
                               borders.append(j - 1);
                           }
                           break;
                       } else if (j == m_scanStop) {
                           borders.append(j);
                       } else {
                           curValue = value;
                       }
                   }
               }
           } else if (m_lengthMeasureMethod == EndPointHalfWave){ // 端点6db 法
               QMap<int, QVector<_Amp>> beamIdValues;// 该缺陷范围内所有的beamId上对应的所有特征点
               for (int i = _defect.special.specialRect._rect[1].lawId; i <= _defect.special.specialRect._rect[2].lawId; ++i) {
                   for (int j = _defect.scanIdStart; j <= _defect.scanIdEnd; ++j) {
                       _process->GetGatePeakInfos(m_groupId, j, i, peakInfo);
                       float _amp = pow(10.0, group.fRefGain / 20.0) * peakInfo[setup_GATE_A].fAmp;

                       float methodThreshold = 0.0;// _process->GetDetermineThreshold(m_groupId, setup_SL);
                       //float max = methodThreshold * 255 / 100 - 1;
                       float height = qFuzzyIsNull(methodThreshold) ? peakInfo[setup_GATE_A].fGh : methodThreshold;
                       if (_amp >= height) {
                           _Amp tmp;
                           tmp.lawId  = i;
                           tmp.scanId = j;
                           tmp.value  = _amp;
                           beamIdValues[i].append(tmp);
                       }
                   }
               }

               for (int b : beamIdValues.keys()) {

                   QVector<_Amp> beamAmps = beamIdValues.value(b);
                   int cnt = beamAmps.count();
                   QVector<_Amp> peakAmps;
                   QVector<QVector<_Amp>> peakValues;
                   if (cnt == 0) {
                       continue;
                   }

                   QVector<_Amp> continuousPeaks;
                   continuousPeaks.append(beamAmps[0]);
                   for (int n = 1; n < cnt; ++n) {
                       if (beamAmps[n].scanId - 1 != beamAmps[n-1].scanId) {
                           peakValues.append(continuousPeaks);
                           continuousPeaks.clear();
                       }
                       continuousPeaks.append(beamAmps[n]);
                   }
                   peakValues.append(continuousPeaks);

                   for (int p = 0; p < peakValues.count(); ++p) {
                       QVector<_Amp> tmp = peakValues[p];
                       int count = tmp.count();
                       if (count == 1) {
                           peakAmps.append(tmp[0]);
                       } else if (count == 2) {
                           if (tmp[0].value > tmp[1].value) {
                               peakAmps.append(tmp[0]);
                           } else {
                               peakAmps.append(tmp[1]);
                           }
                       } else {
                           if (tmp[0].value > tmp[1].value) {
                               peakAmps.append(tmp.at(0));
                           }

                           for (int k = 1; k < count - 1; ++k) {
                               if (tmp.at(k).value >= tmp.at(k-1).value && tmp.at(k).value > tmp.at(k+1).value) {
                                   peakAmps.append(tmp.at(k));
                               } else if (k == count - 2) {
                                   if (tmp.at(k).value <= tmp.at(k+1).value) {
                                       peakAmps.append(tmp.at(k + 1));
                                   }
                               }
                           }
                       }
                       if (peakAmps.count() == 0) continue;
                       _Amp defectLeft  = peakAmps.first();
                       _Amp defectRight = peakAmps.last();
                       // 查找左边界
                       int scanId         = defectLeft.scanId;
                       int lawId          = defectLeft.lawId;
                       float borderValue    = defectLeft.value / 2;
                       float curValue       = borderValue;
                       if (scanId == m_scanStart) {
                           borders.append(scanId);
                       }
                       for (int j = scanId - 1; j >= m_scanStart; --j) {
                           _process->GetGatePeakInfos(m_groupId, j, lawId, peakInfo);
                           float value = pow(10.0, group.fRefGain / 20.0) * peakInfo[setup_GATE_A].fAmp;
                           if (value <= borderValue) {
                               float diff1 = log10((curValue * 1.0) / borderValue);
                               float diff2 = log10((borderValue * 1.0) / value);
                               if((diff1 > diff2) || qFuzzyIsNull(diff1)){ // 取与borderValue接近的点
                                   borders.append(j);
                               } else {
                                   borders.append(j + 1);
                               }
                               break;
                           } else if (j == m_scanStart) {
                               borders.append(j);
                           } else {
                               curValue = value;
                           }
                       }

                       // 查找右边界
                       scanId         = defectRight.scanId;
                       lawId          = defectRight.lawId;
                       borderValue    = defectRight.value / 2;
                       curValue       = borderValue;
                       if (scanId == m_scanStop) {
                           borders.append(scanId);
                       }
                       for (int j = scanId + 1; j <= m_scanStop; ++j) {
                           _process->GetGatePeakInfos(m_groupId, j, lawId, peakInfo);
                           float value = peakInfo[setup_GATE_A].fAmp;

                           if (value <= borderValue) {
                               float diff1 = log10((curValue * 1.0) / borderValue);
                               float diff2 = log10((borderValue * 1.0) / value);
                               if((diff1 > diff2) || qFuzzyIsNull(diff1)){ // 取与borderValue接近的点
                                   borders.append(j);
                               } else {
                                   borders.append(j - 1);
                               }
                               break;
                           } else if (j == m_scanStop) {
                               borders.append(j);
                           } else {
                               curValue = value;
                           }
                       }
                   }
               }
           }

           if (borders.count()) {
               qSort(borders.begin(), borders.end());

               _defect.scanIdStart = borders.first();
               _defect.scanIdEnd   = borders.last();
               _defect.length      = _defect.scanIdEnd - _defect.scanIdStart;
           }
        }
        ++pHead;
    }
}

void DefectIdentify::mergeDefects()
{
    if (m_defectsBetweenFrames.count() <= 0) return;

    auto pHead = m_defectsBetweenFrames.begin();
    auto end = m_defectsBetweenFrames.end();
    while (pHead < end) {
        if ((*pHead).bMergedStatus) {
            ++pHead;
            continue;
        }
        auto pNext                = pHead + 1;
        while (pNext != end) {
            if ((*pNext).bMergedStatus) {
                ++pNext;
                continue;
            }
            QRectF headRect        = (*pHead).special.rect;
            QRectF nextRect        = (*pNext).special.rect;
            QRectF intersectedRect = headRect.intersected(nextRect);
            float areaInter        = getRectFArea(intersectedRect);
            float areaHead         = getRectFArea(headRect);
            float areaNext         = getRectFArea(nextRect);
            // 面积有重叠且间距少于两个缺陷中最小的，进行合并处理
            if (areaInter >= qMin(areaHead, areaNext) * m_scale) {
                int headLength     = (*pHead).scanIdEnd   - (*pHead).scanIdStart;
                int nextLength     = (*pNext).scanIdEnd   - (*pNext).scanIdStart;
                int distLength     = 0;
                if ((*pHead).scanIdStart < (*pNext).scanIdStart) {
                    distLength     = (*pNext).scanIdStart - (*pHead).scanIdEnd;
                } else {
                    distLength     = (*pHead).scanIdStart - (*pNext).scanIdEnd;
                }
                if ((distLength <= qMin(nextLength,headLength)) || qFuzzyIsNull(m_scale)) { // 合并,取特征值较大的作为合并之后的特征值
                    int maxValueHead = (*pHead).special.valueMax;
                    int maxValueNext = (*pNext).special.valueMax;
                    if ((maxValueHead > maxValueNext) || ((maxValueHead == maxValueNext) && (areaHead >= areaNext))) {
                        (*pHead).scanIdStart   = qMin((*pHead).scanIdStart, (*pNext).scanIdStart);
                        (*pHead).scanIdEnd     = qMax((*pHead).scanIdEnd, (*pNext).scanIdEnd);
                        (*pHead).length       += (*pNext).length;
                        (*pHead).allSpecial.append((*pNext).allSpecial);
                        (*pNext).bMergedStatus = true;
                    } else if ((maxValueHead < maxValueNext) || ((maxValueHead == maxValueNext) && (areaHead < areaNext))) {
                        (*pNext).scanIdStart   = qMin((*pHead).scanIdStart, (*pNext).scanIdStart);
                        (*pNext).scanIdEnd     = qMax((*pHead).scanIdEnd, (*pNext).scanIdEnd);
                        (*pNext).length       += (*pHead).length;
                        QVector<specialDefect> tmp = (*pHead).allSpecial;
                        tmp.append((*pNext).allSpecial);
                        (*pNext).allSpecial    = tmp;
                        (*pHead).bMergedStatus = true;
                    }
                }
            }
            ++pNext;
        }
        ++pHead;
    }
}

void DefectIdentify::calDefectRect()
{
    if (m_defectsBetweenFrames.count() == 0) return;

    ParameterProcess* _process = ParameterProcess::Instance();
    auto pHead = m_defectsBetweenFrames.begin();
    auto end = m_defectsBetweenFrames.end();
    while(pHead != end) {
        if (!pHead->bMergedStatus) {
            pHead->_rect.setLeft(_process->SAxisIndexToDist(pHead->scanIdStart));
            pHead->_rect.setRight(_process->SAxisIndexToDist(pHead->scanIdEnd));
            auto defect = pHead->special;
            if (m_heightMeasureMethod == TipDiffraction) {
                tipDiffractionMeasureHeight(defect);
            }
            int id = defect.specialRect._rect[1].lawId;
            float tmp = _process->CScanLineAngleToScanLineAngle(m_groupId, id);
            pHead->_rect.setTop(tmp);
            id = defect.specialRect._rect[2].lawId;
            tmp = _process->CScanLineAngleToScanLineAngle(m_groupId, id);
            pHead->_rect.setBottom(tmp);
            m_defectsRectL.append(pHead->_rect);
            m_defectsRectH.append(defect.rect);
            m_scanIds.append(defect.scanId);
            m_lawIds.append(defect.specialRect._rect[0].lawId);
        }
        ++pHead;
    }
}

/**
 * @brief DefectIdentify::forceMerge 对培训班来说，选中的区域内所有缺陷都合并为一个缺陷
 */
void DefectIdentify::forceMerge()
{
    if (m_defectsBetweenFrames.count() <= 1 || m_defectsRectL.count() == 0)
        return;

    int maxValue    = 0;
    float scanStart   = m_defectsRectL.first().left();
    float scanEnd     = m_defectsRectL.last().right();
    int angleStart  = m_defectsRectL.last().top();
    int angleEnd    = m_defectsRectL.first().bottom();

    m_defectsRectL.clear();
    m_defectsRectH.clear();
    m_scanIds.clear();
    m_lawIds.clear();

    auto pHead = m_defectsBetweenFrames.begin();
    auto end = m_defectsBetweenFrames.end();
    defectsBetweenFrames maxDefect;
    while(pHead != end) {
        if (!pHead->bMergedStatus) {
            if (pHead->special.valueMax > maxValue) {
                maxValue   = pHead->special.valueMax;
            }
            if (pHead->_rect.left() < scanStart ) {
                scanStart = pHead->_rect.left();
            }
            if (pHead->_rect.right() - 1 > scanEnd) {
                scanEnd = pHead->_rect.right() - 1;
            }
            if (pHead->_rect.top() < angleStart) {
                angleStart = pHead->_rect.top();
            }
            if (pHead->_rect.bottom() - 1 > angleEnd) {
                angleEnd = pHead->_rect.bottom() - 1;
            }
        }
        ++pHead;
    }

    QRectF rectL;
    rectL.setLeft(scanStart);
    rectL.setRight(scanEnd);
    rectL.setTop(angleStart);
    rectL.setBottom(angleEnd);
    m_defectsRectL.append(rectL);

    // 取特征点最大的为新的特征点，若存在多个最大值，取长度较长的
    pHead = m_defectsBetweenFrames.begin();
    QVector<defectsBetweenFrames> tmp;
    while(pHead != end) {
        if (!pHead->bMergedStatus) {
            if (pHead->special.valueMax == maxValue) {
                tmp.append(*pHead);
            }
        }
        ++pHead;
    }

    if (tmp.count() == 0) return;
    m_defectsRectH.append(tmp.at(0).special.rect);
    m_scanIds.append(tmp.at(0).special.scanId);
    m_lawIds.append(tmp.at(0).special.specialRect._rect[0].lawId);
    float len = tmp.at(0).scanIdEnd - tmp.at(0).scanIdStart;
    for (int i = 1; i < tmp.count(); ++i) {
        float lenTmp = tmp.at(i).scanIdEnd - tmp.at(i).scanIdStart;
        if (lenTmp > len) {
            m_defectsRectH.clear();
            m_scanIds.clear();
            m_lawIds.clear();

            m_defectsRectH.append(tmp.at(i).special.rect);
            m_scanIds.append(tmp.at(i).special.scanId);
            m_lawIds.append(tmp.at(i).special.specialRect._rect[0].lawId);
        }
    }
}

/**
 * @brief DefectIdentify::tipDiffractionMeasureHeight 端点衍射法对特征缺陷重新测量高度，特别版本
 * @param _defect
 */
void DefectIdentify::tipDiffractionMeasureHeight(specialDefect &_defect)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    WDATA* _pData = _process->GetShadowDataPointer();

    int borderValue = _defect.valueMax / 7;// 经验值，暂定为最大值的七分之一
    int scanId      = _defect.scanId;

    QPointF point;
    transformPolarToCartesian(_defect.specialRect._rect[0].lawId, _defect.specialRect._rect[0].dataIndex, point);
    float _via = point.x();
    // 在via +-2 mm范围内寻找
    float _distStart = _via - 2;
    float _distEnd   = _via + 2;

    QVector<beamData> beamDatas;
    int startBeamId = qMax(_defect.specialRect._rect[2].lawId, m_beamStart);
    for (int i = startBeamId + 1; i < m_lawQty; ++i) {
        int	  _indexStart = transformDistMmToDotPos(transformCartesianToPolar(i, _distStart));
        int	  _indexEnd   = transformDistMmToDotPos(transformCartesianToPolar(i, _distEnd));

        if(_indexStart < 0 || _indexStart >= m_pointQty || _indexEnd < 0 || _indexEnd >= m_pointQty) {
            continue ;
        }

        WDATA* lawData  = _process->GetDataAbsolutePosPointer(m_groupId, scanId, i, _pData);
        int value, postion;
        findMaxValueAndPos(lawData, _indexStart, _indexEnd, value, postion);
        if (value >= borderValue) {
            beamData _data;
            _data.dataIndex = postion;
            _data.lawId     = i;
            _data.value     = value;

            QPointF point;
            if (m_bSscanRangeIsSet) {
                transformPolarToCartesian(_data.lawId, _data.dataIndex, point);
                if (!m_rectSscan.contains(point)) {
                    continue;
                }
            }
            if (beamDatas.count()) {
                if (beamDatas.last().lawId + 1 != i) { // 不连续，清除之前的
                    beamDatas.clear();
                }
            }
            beamDatas.append(_data);
        }
    }
    QVector<beamData> peakDatas;
    findAllPeakDatas(beamDatas, peakDatas);
    float top = _defect.rect.top();
    for (int i = 0; i < peakDatas.count(); ++i) {
        QPointF point;
        transformPolarToCartesian(peakDatas[i].lawId, peakDatas[i].dataIndex, point);
        if (point.y() < top) {
            top = point.y();
            _defect.specialRect._rect[2].lawId = peakDatas[i].lawId;
        }
    }
    _defect.rect.setTop(top);
}

int DefectIdentify::transformDistMmToDotPos(float fDist_)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& group = _pConfig->group[m_groupId];
    float _fSampleStart = group.fSampleStart;
    float _fSampleRange = group.fSampleRange;

    int _iDot = m_pointQty * (fDist_ - _fSampleStart) / _fSampleRange;

    return _iDot;
}

void DefectIdentify::mergeDefectsTipDiffraction()
{
    if (m_defectsBetweenFrames.count() <= 1) return;

    auto pHead = m_defectsBetweenFrames.begin();
    auto end = m_defectsBetweenFrames.end();
    while (pHead < end) {
        if (pHead->bMergedStatus) {
            ++pHead;
            continue;
        }
        auto pNext                = pHead + 1;
        while (pNext != end) {
            if (pNext->bMergedStatus) {
                ++pNext;
                continue;
            }

            if (((pHead->scanIdStart <= pNext->scanIdStart) && (pHead->scanIdEnd >= pNext->scanIdStart)) ||
                  ((pHead->scanIdStart <= pNext->scanIdEnd) && (pHead->scanIdEnd >= pNext->scanIdEnd)) ||
                    ((pHead->scanIdStart >= pNext->scanIdStart) && (pHead->scanIdEnd <= pNext->scanIdEnd))) {
                if (pHead->special.valueMax > pNext->special.valueMax) {
                    pNext->bMergedStatus = true;
                } else if (pHead->special.valueMax < pNext->special.valueMax) {
                    pHead->bMergedStatus = true;
                } else {
                    if (pHead->length >= pNext->length) {
                        pNext->bMergedStatus = true;
                    } else {
                        pHead->bMergedStatus = true;
                    }
                }
            }

            ++pNext;
        }
        ++pHead;
    }
}


/**
 * @brief DefectIdentify::filterSameDefect 一个圆形缺陷，一次波和二次波可能测出来两个缺陷，此时两个缺陷的ViA和DA范围是非常接近的，据此过滤掉一个缺陷
 *          留下特征点较大的那个缺陷，若两个特征点一样大，留下面积较大的
 */
//void DefectIdentify::filterSameDefect(QVector<defectRect> &defectRects,QVector<defectRect> &_Rects )
//{
//    float scale = 0.5;  // 重叠区域要大于等于 50%
//    QVector<defectRect> needRemoveRects; // 保存需要剔除的
//    needRemoveRects.clear();
//    for (int i = 0; i < defectRects.count() - 1; ++i) {
//        for (int k = 0; k < needRemoveRects.count(); k++) { // 已经找出需要剔除的特征点不再参与下面的比较
//            if (defectRects[i]._rect[0].dataIndex == needRemoveRects[k]._rect[0].dataIndex &&
//                    defectRects[i]._rect[0].lawId == needRemoveRects[k]._rect[0].lawId) {
//                continue;
//            }
//        }
//        for (int j = i + 1; j < defectRects.count(); j++) {
//            for (int k = 0; k < needRemoveRects.count(); k++) { // 已经找出需要剔除的特征点不再参与下面的比较
//                if (defectRects[j]._rect[0].dataIndex == needRemoveRects[k]._rect[0].dataIndex &&
//                        defectRects[j]._rect[0].lawId == needRemoveRects[k]._rect[0].lawId) {
//                    continue;
//                }
//            }

//            float disViA1 = abs(defectRects[i]._ViARange[1] - defectRects[i]._ViARange[0]);
//            float disDA1 = abs(defectRects[i]._DARange[1] - defectRects[i]._DARange[0]);
//            float disViA2 = abs(defectRects[j]._ViARange[1] - defectRects[j]._ViARange[0]);
//            float disDA2 = abs(defectRects[j]._DARange[1] - defectRects[j]._DARange[0]);

//            float disViAMin = qMin(disViA1, disViA2);
//            float disDAMin = qMin(disDA1, disDA2);
//            float disViATmp = 0.0;
//            float disDATmp = 0.0;
//            if (defectRects[i]._ViARange[0] <= defectRects[j]._ViARange[0]) {
//                if (defectRects[i]._ViARange[1] <= defectRects[j]._ViARange[0]){ // ViA 无交集
//                    continue;
//                } else {
//                    disViATmp = defectRects[i]._ViARange[1] - defectRects[j]._ViARange[0];
//                    if (disViATmp < disViAMin * scale) {
//                        continue;
//                    }
//                }
//            } else {
//                if (defectRects[i]._ViARange[0] > defectRects[j]._ViARange[1]) {
//                    continue;
//                } else {
//                    disViATmp = defectRects[j]._ViARange[1] - defectRects[i]._ViARange[0];
//                    if (disViATmp < disViAMin * scale) {
//                        continue;
//                    }
//                }
//            }
//            // Via 和 DA 需要同时重叠 50% 以上
//            if(defectRects[i]._DARange[0] <=  defectRects[j]._DARange[0]) {
//                if (defectRects[i]._DARange[1] <=  defectRects[j]._DARange[0]) {
//                    continue;
//                } else {
//                    disDATmp = defectRects[i]._DARange[1] - defectRects[j]._DARange[0];
//                    if (disDATmp < disDAMin * scale) {
//                        continue;
//                    }
//                }
//            } else {
//                if (defectRects[i]._DARange[0] >  defectRects[j]._DARange[1]) {
//                    continue;
//                } else {
//                    disDATmp = defectRects[i]._DARange[0] - defectRects[j]._DARange[1];
//                    if (disDATmp < disDAMin * scale) {
//                        continue;
//                    }
//                }
//            }

//            // 此时 ViA 和 DA 同时满足重叠 50% 以上，应将这个两个缺陷合并为一个
//            if (defectRects[i].valueMax > defectRects[j].valueMax) {
//                needRemoveRects.append(defectRects[j]);
//            } else if (defectRects[i].valueMax < defectRects[j].valueMax) {
//                needRemoveRects.append(defectRects[i]);
//            } else {
//                float area1 = (defectRects[i]._ViARange[1] - defectRects[i]._ViARange[0]) * (defectRects[i]._DARange[1] - defectRects[i]._DARange[0]);
//                float area2 = (defectRects[j]._ViARange[1] - defectRects[j]._ViARange[0]) * (defectRects[j]._DARange[1] - defectRects[j]._DARange[0]);
//                if (area1 < area2) {
//                    needRemoveRects.append(defectRects[i]);
//                } else {
//                    needRemoveRects.append(defectRects[j]);
//                }
//            }
//        }
//    }

//    for (int i = 0; i < defectRects.count(); i++) {
//        bool insert = true;
//        for (int k = 0; k < needRemoveRects.count(); k++) {
//            if (defectRects[i]._rect[0].dataIndex == needRemoveRects[k]._rect[0].dataIndex &&
//                    defectRects[i]._rect[0].lawId == needRemoveRects[k]._rect[0].lawId) {
//                insert = false;
//                break;
//            }
//        }
//        if (insert) {
//            _Rects.append(defectRects[i]);
//        }
//    }

//}
