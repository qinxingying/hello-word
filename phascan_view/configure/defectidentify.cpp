#include "defectidentify.h"

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
            QVector<beamAmp> beamAmps;
            for(int j = 0; j < lawQty; j++){
                int _fStart = Scale[j] * ( start - SampleStart[j]);
                int _fWidth = Scale[j] * width;

                captureBeamAmps(_pData, j, _fStart, _fWidth, threshold, _beamdis, beamAmps);
                _pData += _nLawSize;
            }
        }
    }
}

void DefectIdentify::captureBeamAmps( WDATA* Data, int lawId, int start, int width, int height, int beamdis, QVector<beamAmp> &beamAmps)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    bool inset = false;
    int maxData = 0;
    QVector<beamData> buff;
    QVector<beamData> setbeam;
    for(int i = start; i < start + width; i++){
        if(i >= 0){
            if(Data[i] >= height){
                if(inset){
                    beamData data;
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

    int size = setbeam.size();
    if(size){
        beamData data;
        data.dataIndex = -100;
        QVector<beamData>::Iterator i = setbeam.begin();
        while(i != setbeam.end()){
            if(i->dataIndex < beamdis){
                if(data.value > i->value){
                    i = setbeam.erase(i);
                }else{
                    data = *i;
                    --i;
                    i = setbeam.erase(i);
                }
            }else{
                data = *i;
                ++i;
            }
        }
    }
    size = setbeam.size();

}

DefectIdentify::beamData DefectIdentify::filterValue(QVector<beamData> &beamDatas, int maxValue)
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
