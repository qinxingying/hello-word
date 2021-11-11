#include "AExportData.h"
#include "DopplerConfigure.h"
#include "config_phascan_ii/config.h"
#include "DopplerDataView.h"
#include "DopplerExcelBase.h"
#include "DopplerWordBase.h"
#include "report/DopplerHtmlReport.h"
#include <QApplication>

extern U32 getGateDataAmplitude( U32 value);
extern U32 getGateDataDepth( U32 value);
extern U32 combinedGateDate( U32 depth, int amp);

AExportData::AExportData(QObject *parent) : QObject(parent)
{

}

void AExportData::saveBScanData(QString filePath)
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

void AExportData::saveCScanData(QString filePath)
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

void AExportData::saveReport(QString filePath)
{
    DopplerConfigure* pConfig  = DopplerConfigure::Instance();
    QString reportForm = "/data/Report/report.doc";
    if(pConfig->group[m_iCurGroup].eTxRxMode == setup_TX_RX_MODE_TOFD) {
        reportForm = "/data/Report/tofdReport.doc";
        QString reportPath = QCoreApplication::applicationDirPath() + reportForm;
        saveTofdReport(filePath, reportPath);
    } else {
        QString reportPath = QCoreApplication::applicationDirPath() + reportForm;
        savePhaseReport(filePath, reportPath);
    }

    emit done();
}

void AExportData::savePhaseReport(QString filePath, QString reportFormPath)
{
    DopplerConfigure* pConfig  = DopplerConfigure::Instance();
    DopplerHtmlReport* pReport = pConfig->GetReportOpp();
    pReport->BuildReport();
    if (!filePath.isEmpty()) {
        WordBase word;
        bool ret = word.open(reportFormPath, false);
        int nGroupQty = pConfig->common.nGroupQty;
        //focallaw
        for(int i = 0; i < 1; i++){
            GROUP_CONFIG& group = pConfig->group[i];
            COMMON_CONFIG& config = pConfig->common ;
            LAW_CONFIG& law = group.law;

            // customer info
            ReportInfo2 info = pReport->GetReportInfo2();
            word.setBookmarkText("ProjectName", info.projectName);
            word.setBookmarkText("Client", info.client);
            word.setBookmarkText("SpecimenName", info.specimenName);
            word.setBookmarkText("ReportNum", info.reportNum);
            word.setBookmarkText("SpecimenNum", info.specimenNum);
            word.setBookmarkText("InspectionQuantity", info.inspectionQuantity);
            word.setBookmarkText("InspectionScale", info.inspectionScale);
            word.setBookmarkText("ConstructionOrganization", info.constructionOrganization);
            word.setBookmarkText("Specifications", info.specifications);
            word.setBookmarkText("WeldingMethod", info.weldingMethod);
            word.setBookmarkText("SlopeType", info.slopeType);
            word.setBookmarkText("HotDealingCondition", info.hotDealingCondition);
            word.setBookmarkText("TestSurface", info.testSurface);
            word.setBookmarkText("DetectionTime", info.detectionTime);
            word.setBookmarkText("OperationInstructionNum", info.operationInstructionNum);
            word.setBookmarkText("TestStandard", info.testStandard);
            word.setBookmarkText("AcceptanceStandard", info.acceptanceStandard);
            word.setBookmarkText("DetectionLevel", info.detectionLevel);
            word.setBookmarkText("AcceptanceLevel", info.acceptanceLevel);
            word.setBookmarkText("SurfaceCondition", info.surfaceCondition);
            word.setBookmarkText("CalibrationBlock", info.calibrationBlock);
            word.setBookmarkText("Couplant", info.couplant);

            //
            MATERIAL& material = group.part.material;
            QString strTmp[3];
            int iLang = pConfig->AppEvn.eLanguage;
            strTmp[0] = QString(material.strName[iLang]);
            strTmp[1].sprintf("[L]%.0f" , material.fVelocityLon) ;
            strTmp[2].sprintf("[T]%.0f" , material.fVelocityTran) ;
            word.setBookmarkText("Material", strTmp[0] + strTmp[1] + strTmp[2]);

            WEDGE_CONFIG& wedge = group.wedge[0];
            word.setBookmarkText("WedgeType", wedge.strName);
            PROBE_CONFIG& probe = group.probe[0];
            word.setBookmarkText("ProbeType", probe.strName);

            if (Config::instance()->is_phascan_ii()) {
                word.setBookmarkText("DeviceType", "Phascan II");
            } else {
                word.setBookmarkText("DeviceType", "Phascan I");
            }

            word.setBookmarkText("ElemQtyFir", QString::number(probe.fPitchPri * probe.nElementPri) + " mm");
            if (config.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE) {
                word.setBookmarkText("ScanType", QString::fromLocal8Bit("单线扫查"));
            } else {
                word.setBookmarkText("ScanType", QString::fromLocal8Bit("双线扫查"));
            }
            word.setBookmarkText("Resolution", QString::number(pConfig->common.scanner.fScanStep, 'f', 0) + " mm");

            QString angeleRange = QString::number(law.nAngleStartRefract / 10) + "~" + QString::number(law.nAngleStopRefract / 10);
            word.setBookmarkText("AngleRange", angeleRange);
            word.setBookmarkText("AngleStep", QString::number(law.nAngleStepRefract / 10));

            if (law.eLawType == setup_LAW_TYPE_AZIMUTHAL) {
                word.setBookmarkText("LawType", QString::fromLocal8Bit("扇形扫查"));
            } else if (law.eLawType == setup_LAW_TYPE_LINEAR) {
                word.setBookmarkText("LawType", QString::fromLocal8Bit("线形扫查"));
            } else if (law.eLawType == setup_LAW_TYPE_TFM) {
                word.setBookmarkText("LawType", QString::fromLocal8Bit("全聚焦"));
            }

            if (law.eFocalType == setup_FOCAL_TYPE_HALF_PATH) {
                word.setBookmarkText("FocallawType", QString::fromLocal8Bit("半声程"));
            } else if (law.eFocalType == setup_FOCAL_TYPE_TRUE_DEPTH) {
                word.setBookmarkText("FocallawType", QString::fromLocal8Bit("真实深度"));
            } else if (law.eFocalType == setup_FOCAL_TYPE_PROJECTION) {
                word.setBookmarkText("FocallawType", QString::fromLocal8Bit("投影"));
            } else if (law.eFocalType == setup_FOCAL_TYPE_FOCAL_PLANE) {
                word.setBookmarkText("FocallawType", QString::fromLocal8Bit("任意面"));
            }

            word.setBookmarkText("FocallawPosition", QString::number(law.fPositionStart, 'f', 0) + "mm");

            word.setBookmarkText("CoupleGain", QString::number(group.CoupleGain + CUR_RES.Com_Gain[i], 'f', 0) + " db");
            word.setBookmarkText("RL", QString::number(CUR_RES.CurRL[i], 'f', 0) + " db");
            word.setBookmarkText("SL", QString::number(CUR_RES.CurSL[i], 'f', 0) + " db");
            word.setBookmarkText("EL", QString::number(CUR_RES.CurEL[i], 'f', 0) + " db");
            word.setBookmarkText("SS", QString::number(CUR_RES.CurSS[i], 'f', 0) + " db");
        }

        //qDebug() << "table count : " << word.getTableCount();
        // defect
        int defectNum = 0;
        for(int i = 0; i < nGroupQty; i++){
            defectNum += pConfig->GetDefectCnt(i);
        }

        //for (int i = 0; i < defectNum*2; i += 2) {
        //    word.MergeCells(3,4 + i,1,4 + i,7);
        //}
        if (defectNum > 16) {
            word.addTableRow(2,4,19);
        }
        if (defectNum > 34) {
            for (int i = 0 ; i < defectNum % 34; i++) {
                word.addTableRow(2,4,19*(i+1));
            }
        }

        if(defectNum){
            DEFECT_INFO **sortBuff = (DEFECT_INFO **)malloc(sizeof(DEFECT_INFO *)* defectNum);
            int index_ = 0;
            for(int i = 0; i < nGroupQty; i++){
                GROUP_CONFIG&   group = pConfig->group[i];
                if(group.eTxRxMode == setup_TX_RX_MODE_TOFD){
                    continue;
                }
                DEFECT_INFO* pDfInfo = pConfig->m_dfParam[i].pDFHead;
                while (pDfInfo != NULL) {
                    sortBuff[index_] = pDfInfo;
                    pDfInfo = pDfInfo->pNext;
                    index_++;
                }
            }
            if (index_ > 1) {
                word.addTableRow(3,4,index_ - 1);
            }

            for(int i = 0; i < index_; i++){
                DEFECT_INFO* pDfInfo = sortBuff[i];
                int groupId = pDfInfo->dGroupId - 1;
                if(groupId < 0) groupId = 0;

                QString index = QString::number(pDfInfo->dIndex);
                QString X     = QString::number(pDfInfo->fSStart + pDfInfo->dScanOffset,'f',1);
                QString L     = QString::number(pDfInfo->fSStop - pDfInfo->fSStart,'f',1);
                QString Y     = QString::number(pDfInfo->dDepth,'f',1);

                float fStart;
                float fData = pConfig->DefectHeightValue(groupId, &fStart, pDfInfo->dIndex);
                QString H     = QString::number(fData,'f',1);

                QStringList strMeasure;
                QStringList strSzField;
                for(int i = 0; i < setup_MAX_MEASURE_QTY_V1; i++) {
                    if(pDfInfo->m_strSzField[i][0] == 45 && pDfInfo->m_strSzField[i][1] == 0){

                    }else{
                        strMeasure << pDfInfo->m_strMeasure[i];
                        strSzField << pDfInfo->m_strSzField[i];
                    }

                }
                int max = setup_MAX_MEASURE_QTY - setup_MAX_MEASURE_QTY_V1;
                if(pConfig->loadDefectVersion == 2){
                    for(int i = 0; i < max; i++){
                        if(pDfInfo->m_strSzField_V2[i][0] == 45 && pDfInfo->m_strSzField_V2[i][1] == 0){

                        }else{
                            strMeasure << pDfInfo->m_strMeasure_V2[i];
                            strSzField << pDfInfo->m_strSzField_V2[i];
                        }

                    }
                }

                int indexViA = strSzField.indexOf("ViA^  ");
                int indexZA = strSzField.indexOf("ZA    ");

                QString ViA = "NA";
                QString ZA = "NA";
                if (indexViA >= 0) ViA = strMeasure[indexViA];
                if (indexZA >= 0) ZA = strMeasure[indexZA];

                // table2
                word.setCellString(2,5 + i,2,index);
                word.setCellString(2,5 + i,3,X);
                word.setCellString(2,5 + i,4,L);
                word.setCellString(2,5 + i,5,Y);
                word.setCellString(2,5 + i,6,H);
                word.setCellString(2,5 + i,7,ViA);
                word.setCellString(2,5 + i,8,ZA);

                // table 3
                QString strImgPathName = pConfig->m_szDefectPathName +
                                        QString(QObject::tr("/")) +
                                        QString(QObject::tr(pDfInfo->srtImageName)) +
                                        QString(QObject::tr(".png"));
                QString sourceImgName = pReport->getReportFolder() + QString("/") +
                                        QString(QObject::tr(pDfInfo->srtImageName)) +
                                        QString(QObject::tr(".png"));
                QString strDir = pReport->getReportDir() + sourceImgName ;
                pReport->CopyFileToPath(strDir , strImgPathName);

                word.insertBookMark(3,4+i,1,QString("defect%1").arg(i+1));
                word.createHyperLink(2,5 + i,10,QString(pDfInfo->srtImageName) + ".png", QString("defect%1").arg(i+1));

                word.insertCellPic(3,4 + i,1,strDir);
            }
        }

        word.setSaveName(filePath);
        word.moveForEnd();
        word.setVisible(true);
        word.close();
    }
}

void AExportData::saveTofdReport(QString filePath, QString reportFormPath)
{
    DopplerConfigure* pConfig  = DopplerConfigure::Instance();
    DopplerHtmlReport* pReport = pConfig->GetReportOpp();
    pReport->BuildReport();
    if (!filePath.isEmpty()) {
        WordBase word;
        bool ret = word.open(reportFormPath, false);
        //int nGroupQty = pConfig->common.nGroupQty;

        if (Config::instance()->is_phascan_ii()) {
            word.setBookmarkText("DeviceType", "Phascan II");
        } else {
            word.setBookmarkText("DeviceType", "Phascan I");
        }

        int defectNum = 0;
        defectNum += pConfig->GetDefectCnt(m_iCurGroup);

        if (defectNum > 17) {
            word.addTableRow(2,4,defectNum - 17);
        }

        if(defectNum){
            DEFECT_INFO **sortBuff = (DEFECT_INFO **)malloc(sizeof(DEFECT_INFO *)* defectNum);
            int index_ = 0;
            DEFECT_INFO* pDfInfo = pConfig->m_dfParam[m_iCurGroup].pDFHead;
            while (pDfInfo != NULL) {
                sortBuff[index_] = pDfInfo;
                pDfInfo = pDfInfo->pNext;
                index_++;
            }

            word.addTableRow(3,2,index_ - 1);

            for(int i = 0; i < index_; i++){
                DEFECT_INFO* pDfInfo = sortBuff[i];
                int groupId = pDfInfo->dGroupId - 1;
                if(groupId < 0) groupId = 0;

                //QString index = QString::number(pDfInfo->dIndex);
                QString X     = QString::number(pDfInfo->fSStart + pDfInfo->dScanOffset,'f',1);
                QString L     = QString::number(pDfInfo->fSStop - pDfInfo->fSStart,'f',1);
                QString Y     = QString::number(pDfInfo->dDepth,'f',1);

                float fStart;
                float fData = pConfig->DefectHeightValue(groupId, &fStart, pDfInfo->dIndex);
                QString H     = QString::number(fData,'f',1);

                //word.setCellString(1,4 + i,1,index);
                word.setCellString(2,4 + i,2,X);
                word.setCellString(2,4 + i,3,L);
                word.setCellString(2,4 + i,4,Y);
                word.setCellString(2,4 + i,5,H);

                // table 3
                QString strImgPathName = pConfig->m_szDefectPathName +
                                        QString(QObject::tr("/")) +
                                        QString(QObject::tr(pDfInfo->srtImageName)) +
                                        QString(QObject::tr(".png"));
                QString sourceImgName = pReport->getReportFolder() + QString("/") +
                                        QString(QObject::tr(pDfInfo->srtImageName)) +
                                        QString(QObject::tr(".png"));
                QString strDir = pReport->getReportDir() + sourceImgName ;
                pReport->CopyFileToPath(strDir , strImgPathName);

                //word.insertBookMark(1,4+i,1,QString("defect%1").arg(i+1));
                //word.createHyperLink(1,5 + i,10,QString(pDfInfo->srtImageName) + ".png", QString("defect%1").arg(i+1));

                word.setCellString(3,2 + i,1, QString("%1").arg(i+1));
                word.insertCellPic(3,2 + i,1,strDir);
            }
        }

        word.setSaveName(filePath);
        word.moveForEnd();
        word.setVisible(true);
        word.close();
    }
}

void AExportData::getPixValueInfo(int nScanPos, setup_GATE_NAME eGate, U32 *pBuff)
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

void AExportData::getPixValueDistance(U32 *pBuff1, U32 *pBuff2, float GainScale, U32 gateHeight1, U32 gateHeight2)
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

void AExportData::getPixValuePos(U32* pBuff, U32* pBuff2, float gainScale, U32 gateHeight1)
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
