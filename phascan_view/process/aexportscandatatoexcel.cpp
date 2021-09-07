#include "aexportscandatatoexcel.h"
#include "DopplerConfigure.h"
#include "DopplerDataView.h"
#include "DopplerExcelBase.h"

extern U32 getGateDataAmplitude( U32 value);
extern U32 getGateDataDepth( U32 value);
extern U32 combinedGateDate( U32 depth, int amp);

AExportScanDataToExcel::AExportScanDataToExcel(QObject *parent) : QObject(parent)
{

}

void AExportScanDataToExcel::saveBScanData(QString filePath)
{
    //qDebug() << QThread::currentThread() << "sub thread";
    DopplerConfigure* pConfig = DopplerConfigure::Instance();
    ParameterProcess* process = ParameterProcess::Instance();
    int scanMax    = process->SAxisstoptoIndex(process->GetScanend());
    int pointQty  = process->GetGroupPointQty(m_iCurGroup);
    int dispMode = pConfig->group[m_iCurGroup].DisplayMode;
    if(dispMode < 0){
        dispMode = (int)ProcessDisplay::DISP_S_AV;
    }
    int nLawId = pConfig->group[m_iCurGroup].afCursor[setup_CURSOR_LAW];

    if (!filePath.isEmpty())
    {
        volatile WDATA*	    pData = process->GetShadowDataPointer();

        if(!pData) {
            return ;
        }
        SCANNER& scanner = pConfig->common.scanner;
        int fixDis;
        int nScanOff = process->GetScanOff(m_iCurGroup);
        S32 j , k , iData;
        S32 nFrameOffset = process->GetTotalDataSize()  ;
        int nGroupOffset = process->GetGroupDataOffset(m_iCurGroup);
        int nLawOffset   = process->GetGroupLawDataOffset(m_iCurGroup, nLawId) ;
        int nOffset	  = nGroupOffset + nLawOffset  ;

        U8*      pMarker = process->GetScanMarker(m_iCurGroup)  ;

        F32	   fScale = process->GetRefGainScale(m_iCurGroup) ;
        bool bRectify = (process->GetRectifierMode(m_iCurGroup) == setup_RECTIFIER_RF ) ;

        volatile WDATA* pData1, *pData2 ;
        if( scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
            fixDis = 0;
        }else{
            int index = process->TransforIndexPosToIndex(scanner.fIndexPos);
            int scanQty = ( scanner.fScanStop - scanner.fScanStart) / scanner.fScanStep + 0.5;
            fixDis = scanQty*index;

        }
        int  index = 0;
        int step = 1.0;
        U8 (*src)[1024] = new WDATA[scanMax+1][1024];
        memset(src, 0, (scanMax+1) * 1024);
        for( k = 0 ; k <= scanMax; k++) {
            int buff = fixDis + k;
            if(pMarker[buff] && buff >= nScanOff && buff <= scanMax) {
                index = process->GetRealScanIndex(m_iCurGroup, buff);
                pData1 = index * nFrameOffset + pData + nOffset ;
                int index_ = k*step;
                for(j = 0 ; j <= pointQty ; j++)	{
                    pData2 = pData1 + j   ;
                    iData  = process->GetRefGainScaleData(*pData2, fScale, bRectify);
                    src[index_][j] = iData;
                }
            }
        }

        QList< QList<QVariant> > m_datas;
        for (int j = -1; j <= scanMax; ++j) {
            QList<QVariant> rows;
            if (j == -1) {
                rows.append("");
                for (int i = 1; i <= pointQty; ++i) {
                    rows.append(QString("Point%1").arg(i));
                }
                m_datas.append(rows);
                continue;
            }
            rows.append(QString("Pos%1").arg(j));
            for (int i = 0; i < pointQty; ++i) {
                  rows.append(src[j][i]);
            }

            m_datas.append(rows);
        }
        ExcelBase xls;
        xls.create(filePath);
        xls.setCurrentSheet(1);
        QElapsedTimer timer;
        timer.start();
        xls.writeCurrentSheet(m_datas);
        qDebug() << "write cost:"<< timer.elapsed()<< "ms";
        xls.save();
        xls.close();
        free(src);
    }
    emit done();
}

void AExportScanDataToExcel::saveCScanData(QString filePath)
{
    ParameterProcess* process = ParameterProcess::Instance();

    //
    U32 aGateValue[256] ;
    memset(aGateValue, 0x00, sizeof(aGateValue));
    U32 aGateValue2[256] ;
    memset(aGateValue2, 0x00, sizeof(aGateValue2));
    setup_CSCAN_SOURCE_MODE eSource = process->GetCScanSource(m_iCurGroup , 0) ;
    setup_GATE_NAME eGate1 = setup_GATE_A;
    setup_GATE_NAME eGate2 = setup_GATE_A;
    int lawstart  = process->GetLawStart();
    int lawstop   = process->GetLawStop();
    bool twoGate = false;
    switch (eSource) {
        case setup_CSCAN_AMP_A:
        case setup_CSCAN_POS_A:
            eGate1 = setup_GATE_A;
            break;
        case setup_CSCAN_POS_AI:
            eGate1 = setup_GATE_A;
            eGate2 = setup_GATE_I;
            twoGate = true;
            break;
        case setup_CSCAN_AMP_B:
        case setup_CSCAN_POS_B:
            eGate1 = setup_GATE_B;
            break;
        case setup_CSCAN_POS_BI:
            eGate1 = setup_GATE_B;
            eGate2 = setup_GATE_I;
            twoGate = true;
            break;
        case setup_CSCAN_POS_BA:
            eGate1 = setup_GATE_B;
            eGate2 = setup_GATE_A;
            twoGate = true;
            break;
        case setup_CSCAN_POS_I:
            eGate1 = setup_GATE_I; break;
        default:  return;
    }
    float fGScale =  (float)(255.0 / 100.0);
    GROUP_CONFIG* group   = process->GetGroupConfig(m_iCurGroup);
    U32 nGateHeight1 = group->gate[eGate1].nThreshold * fGScale;
    U32 nGateHeight2 = group->gate[eGate2].nThreshold * fGScale;//

    int scanMax    = process->SAxisstoptoIndex(process->GetScanend());
    volatile WDATA*	    pData = process->GetShadowDataPointer();

    if(!pData) {
        return ;
    }
    int nScanOff = process->GetScanOff(m_iCurGroup);
    S32 k ;
    float step = 1.0;

    U8*      pMarker = process->GetScanMarker(m_iCurGroup)  ;
    int oldIndex = -1;
    int newIndex = 0;
    U32 nTmpValue ;
    float fScale = process->GetRefGainScale(m_iCurGroup) ;
    U8 (*src)[128] = new WDATA[scanMax+1][128];
    memset(src,0,128 * (scanMax+1));
    for(int i = 0, j = -1 ; i <= scanMax + 1&& j < (scanMax)+1; i++ , j++) {
        if(pMarker[i] && i >= nScanOff) {
            newIndex = (j+1)*step;
            if( newIndex == oldIndex){
                continue;
            }else{
                oldIndex = newIndex;
            }
            getPixValueInfo(i, eGate1, aGateValue);
            if (eSource != setup_CSCAN_AMP_A && eSource != setup_CSCAN_AMP_B) {
                if (eGate2) {
                    getPixValueInfo(i, eGate2, aGateValue2);
                    getPixValueDistance(aGateValue, aGateValue2, fScale, nGateHeight1, nGateHeight2);
                } else {
                    getPixValuePos(aGateValue, aGateValue2, fScale, nGateHeight1);
                }
                memcpy(aGateValue, aGateValue2, sizeof(aGateValue));
            }
            for(k = lawstart ; k < lawstop+1 ; k++) {
                if (eSource == setup_CSCAN_AMP_A || eSource == setup_CSCAN_AMP_B) {
                    nTmpValue = getGateDataAmplitude(aGateValue[k ])  * fScale;
                } else {
                    nTmpValue = aGateValue[k];
                }

                if(nTmpValue > WAVE_MAX)	nTmpValue = WAVE_MAX;

                src[newIndex][k] = nTmpValue;
            }
        }
    }

    if (!filePath.isEmpty())
    {
        QList< QList<QVariant> > m_datas;
        for (int j = -1; j <= scanMax; ++j) {
            QList<QVariant> rows;
            if (j == -1) {
                rows.append("");
                for (int i = 1; i <= lawstop; ++i) {
                    rows.append(QString("Beam%1").arg(i));
                }
                m_datas.append(rows);
                continue;
            }
            rows.append(QString("Pos%1").arg(j));
            int index = j * step;
            for (int i = lawstart; i <= lawstop; ++i) {
                if (twoGate) {
                    rows.append(src[index][i] / 10.0);
                } else {
                    rows.append(src[index][i]);
                }
            }
            m_datas.append(rows);
        }
        ExcelBase xls;
        xls.create(filePath);
        xls.setCurrentSheet(1);
        QElapsedTimer timer;
        timer.start();
        xls.writeCurrentSheet(m_datas);
        qDebug() << "write cost:"<< timer.elapsed()<< "ms";
        xls.save();
        xls.close();
        free(src);
    }
    emit done();
}

void AExportScanDataToExcel::getPixValueInfo(int nScanPos, setup_GATE_NAME eGate, U32 *pBuff)
{
    ParameterProcess* process = ParameterProcess::Instance();
    int lawstop   = process->GetLawStop();
    PEAK_CONFIG info[setup_GATE_MAX];
    for(int i = 0 ; i < lawstop ; i++)
    {
        process->GetGatePeakInfos(m_iCurGroup, nScanPos, i, info);
        pBuff[i] = (info[eGate].fH * 1000);
        pBuff[i] = combinedGateDate( pBuff[i], info[eGate].iY);
    }
}

void AExportScanDataToExcel::getPixValueDistance(U32 *pBuff1, U32 *pBuff2, float GainScale, U32 gateHeight1, U32 gateHeight2)
{
    ParameterProcess* process = ParameterProcess::Instance();
    int lawstop   = process->GetLawStop();
    U32	 nBeamQty = lawstop;
    U32		 nMin =  (int)(process->GetCScanThicknessStart(m_iCurGroup) * 1000);
    U32		 nMax = (int)(process->GetCScanThicknessStop(m_iCurGroup) * 1000);
    U32	   nRange = nMax - nMin;
    U32 nGateHeight1 = gateHeight1;
    U32 nGateHeight2 = gateHeight2;

    U32 nData1, nData2;
    U32 nPeak1, nPeak2;
    U32 nDepth1, nDepth2;
    for(U32 i = 0; i < nBeamQty; i++)
    {
        nData1  = pBuff1[i];	  nData2  = pBuff2[i];
        nPeak1 = getGateDataAmplitude(nData1) * GainScale;
        nPeak2 = getGateDataAmplitude(nData2) * GainScale;

        if(nPeak1 >= nGateHeight1 && nPeak2 >= nGateHeight2)
        {
            nDepth1 = getGateDataDepth(nData1);
            nDepth2 = getGateDataDepth(nData2);

            nDepth1 = abs((int)(nDepth2 - nDepth1));
            pBuff2[i] = nDepth1 / 100;
            if(nDepth1 < nMin)
                pBuff1[i] = 0 ;
            else if(nDepth1 > nMax)
                pBuff1[i] = WAVE_MAX;
            else
            {
                pBuff1[i] = WAVE_MAX * (nDepth1 - nMin) / nRange ;
                if(pBuff1[i] > WAVE_MAX)
                    pBuff1[i] = WAVE_MAX;
            }
        }
        else
        {
            pBuff1[i] = 0;
            pBuff2[i] = 0;
        }
    }
}

void AExportScanDataToExcel::getPixValuePos(U32* pBuff, U32* pBuff2, float gainScale, U32 gateHeight1)
{
    ParameterProcess* process = ParameterProcess::Instance();
    int lawstop   = process->GetLawStop();
    U32	 nBeamQty = lawstop;
    U32		 nMin =  (int)(process->GetCScanThicknessStart(m_iCurGroup) * 1000);
    U32		 nMax = (int)(process->GetCScanThicknessStop(m_iCurGroup) * 1000);
    U32	   nRange = nMax - nMin;
    U32 nGateHeight = gateHeight1;

    U32 nData  = 0;
    U32 nPeak  = 0;
    U32 nDepth = 0;
    for(U32 i = 0; i < nBeamQty; i++)
    {
        nData  = pBuff[i];
        nPeak = getGateDataAmplitude(nData) * gainScale;

        if(nPeak < nGateHeight)
        {
            //pBuff_[i] = 255 ;
            pBuff[i] = 0 ;
            pBuff2[i] = 0;
        }
        else
        {
            nDepth = getGateDataDepth(nData);
            pBuff2[i] = nDepth / 1000;
            if(nDepth < nMin)
                pBuff[i] = 0 ;
            else if(nDepth > nMax)
                pBuff[i] = WAVE_MAX;
            else
            {
                pBuff[i] = WAVE_MAX * (nDepth - nMin) / nRange ;
                if(pBuff[i] > WAVE_MAX)
                    pBuff[i] = WAVE_MAX;
            }
        }
    }
}
