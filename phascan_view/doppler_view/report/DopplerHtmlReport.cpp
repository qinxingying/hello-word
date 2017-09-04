#include "DopplerHtmlReport.h"
#include "ParameterProcess.h"

#include <QFile>
#include <QDir>
#include <QProcess>
#include <QStringList>

#define TABLE_WIDTH	 800
char tableWidth[256];
const char* tableThStyle	= "class=\"general_cell\"  align=left";
const char* tableTdStyle	= "class=\"general_cell\"";
const char* sonTableStyle   = "width=100% style=\"table-layout:fixed\"";
const char* tdSpace		    = "&nbsp;";

const char* string_groupMode[] = {"UT", "PA", "UT1", "UT2"};
const char* string_filter[]    = {
		"None  0.5-20.0 MHz",
		"Auto",
		"1 MHz",
		"1.5-2.5MHz",
		"3-5MHz",
		"7.5MHz",
		">=10MHz",
		"5MHz",
		"7.5MHz",
		"10MHz",
		"12MHz",
		"15MHz",
		"20MHz",
		"HR" ,
		"HR 10 MHz",
		"None"
};

DopplerHtmlReport::DopplerHtmlReport()
{
	m_pFile = NULL ;

    QString g_strReportLogo = "data/logo/logo.png";

#ifdef QT_NO_DEBUG
    GetExePathName1(g_strReportLogo.toLatin1().data(), m_strReportLogo);
#else
    strcpy(m_strReportLogo, g_strReportLogo.toLatin1().data());
#endif
}

void DopplerHtmlReport::InitReportInfo()
{
    QString g_strReportDir;
    if(!m_dataFilePath.isEmpty()) {
        if(QFileInfo(m_dataFilePath).isRoot()) {
            g_strReportDir = m_dataFilePath + "Report/";
        } else {
            g_strReportDir = m_dataFilePath + "/Report/";
        }
#ifdef QT_NO_DEBUG
        std::string _str1 = g_strReportDir.toStdString();
        const char* _str2 = _str1.c_str();
        strcpy(m_strReportDir, _str2);
#else
        strcpy(m_strReportDir, g_strReportDir.toLatin1().data());
#endif
    }

    sprintf(tableWidth, "width=%d style=\"table-layout:fixed\"", TABLE_WIDTH);
	{
        strcpy(m_cInfo.strPartName, "Part");
        strcpy(m_cInfo.strPartNo, "No. 1");
        strcpy(m_cInfo.strPartPos, "Part Position");
        strcpy(m_cInfo.strReportName, "Report");
	}

	QDate _date= QDate::currentDate();
    m_cInfo.nYear  = _date.year();
    m_cInfo.nMonth = _date.month();
    m_cInfo.nDate  = _date.day();
	m_cValueList.clear();
    m_cInfo.eMode  = 0;
}

void DopplerHtmlReport::SetReportInfo(ReportInfo* pInfo_)
{
	if(pInfo_)
        memcpy((void*)&m_cInfo, (void*)pInfo_, sizeof(ReportInfo));
}

ReportInfo* DopplerHtmlReport::GetReportInfo()
{
	return &m_cInfo ;
}

void DopplerHtmlReport::CreateTofdHeader(int nGroupId_)
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	GROUP_CONFIG* _pGroup = &_pConfig->group[nGroupId_] ;
	TOFD_PARA* _pTofd = &_pConfig->TOFD[nGroupId_];
	SCANNER& _scaner = _pConfig->common.scanner ;
	ParameterProcess* _process = ParameterProcess::Instance();

	fprintf(m_pFile , "<br />\n");
    fprintf(m_pFile , "<th align=left>%s</th>\n", "TOFD");

	fprintf(m_pFile,"<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);
	fprintf(m_pFile,"<tr>\n");

    QString g_strTofdReportHead[] = {
        QString(QObject::tr("Channel")),
        QString(QObject::tr("Frequency")),
        QString(QObject::tr("Chip Size")),
        QString(QObject::tr("Wedge Angle")),
        QString(QObject::tr("Probe Dealy")),
        QString(QObject::tr("The Probe Center Distance")),
        QString(QObject::tr("The Time Window Set")),
        QString(QObject::tr("DB Set")),
        QString(QObject::tr("Scan Incremental")),
        QString(QObject::tr("Scan Mode"))
    };

	for(int i = 0 ;i < 10 ;++i)
	{
        fprintf(m_pFile,"<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strTofdReportHead[i]));
	}
	fprintf(m_pFile,"</tr>\n\n");

	int iScanMode = _scaner.eScanType;
    QString g_strScanMode[] = {
        QString(QObject::tr("Normal")),
        QString(QObject::tr("Parallel"))
    };

	fprintf(m_pFile,"<tr>\n");
	fprintf(m_pFile,"<td %s>%s</td>\n" ,tableTdStyle , string_groupMode[_pGroup->eGroupMode]);
	fprintf(m_pFile,"<td %s>%.1fMHz</td>\n" ,tableTdStyle , _pGroup->probe[0].fFrequency);
	fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _pGroup->probe[0].fSizePri);
	fprintf(m_pFile,"<td %s>%2.1f°</td>\n" ,tableTdStyle , _pGroup->law.nAngleStartRefract / 10.0f);
	fprintf(m_pFile,"<td %s>%.2fus</td>\n" ,tableTdStyle , _pTofd->fZero);
	fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _pTofd->fPCS);
	fprintf(m_pFile,"<td %s>%.2fus</td>\n" ,tableTdStyle , _process->DistMmToUs(nGroupId_ , _pGroup->fSampleRange));
	fprintf(m_pFile,"<td %s>%.1fdB</td>\n" ,tableTdStyle , _pGroup->fGain);
	fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _scaner.fScanStep);
    fprintf(m_pFile,"<td %s>%s</td>\n" ,tableTdStyle , TOCHAR(g_strScanMode[iScanMode]));
	fprintf(m_pFile,"</tr>\n\n");

	fprintf(m_pFile,"</table>\n</table>\n\n");
}

void DopplerHtmlReport::CreateDefect(int nGroupId_)
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    GROUP_CONFIG&  _group = _pConfig->group[nGroupId_];

	fprintf(m_pFile , "<br />\n");

    QString strDefect = QString(QObject::tr("Defect"));
    QString defect[] =
    {
        QString(QObject::tr("Defect")),
        QString(QObject::tr("Remark")),
        QString(QObject::tr("Index")),
        QString(QObject::tr("Position start")),
        QString(QObject::tr("Length")),
        QString(QObject::tr("Depth start")),
        QString(QObject::tr("Height")),
        QString(QObject::tr("Index pos")),
        QString(QObject::tr("Width"))
    };

    fprintf(m_pFile , "<th align=left>%s(Gr%d)</th>\n", TOCHAR(strDefect), nGroupId_+1);
	fprintf(m_pFile,"<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);
	fprintf(m_pFile,"<tr>\n");
	int iMax = 6;

	if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD)
		iMax = 8;

    for(int i = 1; i < iMax ;++i)
	{
        fprintf(m_pFile,"<th %s>%s</th>\n" ,tableThStyle, TOCHAR(defect[i+1]));
	}
	fprintf(m_pFile,"</tr>\n\n");
	fprintf(m_pFile,"<tr>\n");

	float _fStart = 0;
	float  _fData = 0;
	float _fDepth = 0;

	for(int i = 0; i < _pConfig->GetDefectCnt(nGroupId_); i++)
	{
		fprintf(m_pFile,"<td %s>%d</td>\n" ,tableTdStyle , i+1);

		_fData = _pConfig->DefectLengthValue(nGroupId_, &_fStart, i);
		fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _fStart);
		fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _fData);

		_fData = _pConfig->DefectHeightValue(nGroupId_, &_fStart, i);
		_fDepth = _pConfig->DefectDepthValue(nGroupId_, i);
		if(_fDepth >= 0) {
			_fStart = _fDepth;
		}
		fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _fStart);
		fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _fData);

		if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD)
		{
			_fData = _pConfig->DefectWidthValue(nGroupId_, &_fStart, i);
			fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _fStart);
			fprintf(m_pFile,"<td %s>%.1fmm</td>\n" ,tableTdStyle , _fData);
		}
		fprintf(m_pFile,"</tr>\n\n");
	}

	fprintf(m_pFile,"</table>\n</table>\n\n");
}

void DopplerHtmlReport::CreateDefectCell(int nGroupId_, int index_)
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	DEFECT_INFO*      _pDfInfo = _pConfig->GetDefectPointer(nGroupId_, index_);

    fprintf(m_pFile, "<br />\n");
    fprintf(m_pFile, "<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);
    fprintf(m_pFile, "<tr>\n");

    QString strIndex = QString(QObject::tr("Index"));
    QString strGroup = QString(QObject::tr("Group"));
    QString strLaw = QString(QObject::tr("Law ID"));
    fprintf(m_pFile,"<th %s>%s</th>\n", tableThStyle, TOCHAR(strIndex));
    fprintf(m_pFile ,"\t\t\t<th>%s</th>\n", TOCHAR(strGroup));
    fprintf(m_pFile ,"\t\t\t<th>%s</th>\n", TOCHAR(strLaw));

    for(int i = 0 ; i < 5 ; i++){
        fprintf(m_pFile ,"\t\t\t<th>%s<br>(%s)</th>\n" , _pDfInfo->m_strSzField[i] ,_pDfInfo->m_strSzFieldUnit[i]);
    }

	fprintf(m_pFile,"</tr>\n\n");
	fprintf(m_pFile,"<tr>\n");

	//int i = index_+1;
	if(strlen(_pDfInfo->srtInfo) > 0) {
		fprintf(m_pFile,"<td %s>%d: %s</td>\n" ,tableTdStyle , index_+1, _pDfInfo->srtInfo);
	} else {
		fprintf(m_pFile,"<td %s>%d</td>\n" ,tableTdStyle , index_+1);
	}
	fprintf(m_pFile ,"\t\t\t<th>%d</th>\n" , nGroupId_+1);
	fprintf(m_pFile ,"\t\t\t<th>%d</th>\n" , _pDfInfo->nLawNo+1);

	for(int i = 0; i < 5; i++) {
		fprintf(m_pFile ,"\t\t\t<th>%s</th>\n" , _pDfInfo->m_strMeasure[i]);
	}

	fprintf(m_pFile ,"\t\t\t<tr>\n");
	fprintf(m_pFile,"</tr>\n\n");
	fprintf(m_pFile,"</table>\n</table>\n\n");

	QString _strImgPathName = _pConfig->m_szDefectPathName +
							QString(QObject::tr("/")) +
							QString(QObject::tr(_pDfInfo->srtImageName)) +
							QString(QObject::tr(".png"));
	QString _sourceImgName = m_strFolder + QString("/") +
							QString(QObject::tr(_pDfInfo->srtImageName)) +
							QString(QObject::tr(".png"));
	QString _strDir = m_strReportDir + _sourceImgName ;
	fprintf(m_pFile ,"\t\t<img src=\"%s\" width=%d>\n" ,  TOCHAR(_sourceImgName), TABLE_WIDTH);
	fprintf(m_pFile ,"\t\t</br>\n");
	CopyFileToPath(_strDir , _strImgPathName) ;
}

void DopplerHtmlReport::SaveReport()
{
    BuildReport();
#ifdef LINUX
	QString _strExec("/usr/bin/firefox") ;
#else
    QString _strExec("\"C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE\"");
#endif
    QStringList _strlist;
	_strlist.append(m_strFile);

	QProcess *myProcess = new QProcess(0);
	myProcess->start(_strExec, _strlist);
}

void DopplerHtmlReport::AddOneValueItem(ReportValueItem* value)
{
	m_cValueList.append(*value);
}

void DopplerHtmlReport::DelOneValueItem()
{
	if(m_cValueList.count())
		m_cValueList.removeLast();
}


void DopplerHtmlReport::BuildReport()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();

    char _strName[1024];
    strcpy(_strName , m_strReportDir);
    strcat(_strName , m_cInfo.strReportName);
    strcat(_strName , ".html");

#ifdef QT_NO_DEBUG
    m_strFile = QString(_strName);
#else
    m_strFile  = QDir::currentPath() + "/" + QString(_strName);
#endif

    m_strFolder.clear();
    m_strFolderDir.clear();
    m_szDataFile = _pConfig->m_szFileInUse;
    memset(_strName, 0, 1024);
    strcpy(_strName, m_cInfo.strReportName);
    strcat(_strName, "_files");
    m_strFolder	= QString(_strName);
    m_strFolderDir.sprintf("%s%s" , m_strReportDir, _strName);

    // folder ready
    CreateFolder();
    m_pFile = fopen(TOCHAR(m_strFile), "w+");
    if(m_pFile == NULL)  return;

    // report start...........
    BuildStarter();
    //## logo and header
    CreateHeader();
    // group info
    //枚举group，每一个group，都是一个独立的信息
    int _nGroupQty = _pConfig->common.nGroupQty;
    for (int i = 0; i < _nGroupQty; ++i)
    {
        UpdateGroupConfig(i);
        if(m_cInfo.eMode) SprintfGroupProbeConfig(i);

        GROUP_CONFIG&   _group = _pConfig->group[i];
        if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD && m_cInfo.eMode)
            CreateTofdHeader(i);

        int _nDfNO = _pConfig->GetDefectCnt(i);
        if(_nDfNO > 0) {
            CreateDefect(i);
            for(int k = 0; k < _nDfNO; k++) {
                CreateDefectCell(i, k);
            }
        }
    }
    //# table
    if(m_cInfo.eMode)  SprintfReportTable();

    SprintfGroupMeasure();
    SfprintfReportSignature();
    // report end...........
    BuildEnder();
    fclose(m_pFile);
}

void DopplerHtmlReport::BuildStarter ()
{
	fprintf(m_pFile,"<html>\n");
	fprintf(m_pFile,"<head>\n");
	fprintf(m_pFile,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\n");
	fprintf(m_pFile,"<style>\n");
	fprintf(m_pFile,"h3 { page-break-before: always; }\n");
	fprintf(m_pFile,".general_cell { width : 16%%; valign:\"bottom\"; }\n");
	fprintf(m_pFile,"</style>\n");
	fprintf(m_pFile,"</head>\n");
	fprintf(m_pFile,"<body>\n");
	fprintf(m_pFile,"<br>\n");
}

void DopplerHtmlReport::BuildEnder()
{
	fprintf(m_pFile,"</body>\n");
	fprintf(m_pFile,"</html>\n");
}

void DopplerHtmlReport::CreateHeader()
{
    QString strReportName = QString(QObject::tr("Phascan Report"));
    QString strReportPath = QString(QObject::tr("Path"));
    QString g_strReportHead[] = {
        QString(QObject::tr("Part Name")),
        QString(QObject::tr("Part No.")),
        QString(QObject::tr("Position")),
        QString(QObject::tr("Date"))
    };

    fprintf(m_pFile,"<table %s>\n", tableWidth);
	fprintf(m_pFile,"<tr>\n");
    fprintf(m_pFile,"<td align=left><img src = \"%s/logo.png\"></td>\n", TOCHAR(m_strFolder));
    fprintf(m_pFile,"<td align=right><h1>%s</h1></td>\n", TOCHAR(strReportName));
	fprintf(m_pFile,"</tr>\n");
	fprintf(m_pFile,"<tr>\n");
    fprintf(m_pFile,"<td align=left style=\"word-break:break-all; word-wrap:break-word;\" colspan=2>%s</td>\n", TOCHAR(strReportName));

	fprintf(m_pFile,"</tr>\n");
	fprintf(m_pFile,"</table>\n");

	fprintf(m_pFile,"<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);//table

	fprintf(m_pFile,"<tr>\n");

    for(int i = 0 ;i < 4 ;++i){
        fprintf(m_pFile,"<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strReportHead[i]));
	}
	fprintf(m_pFile,"</tr>\n\n");

    QString _date;
    _date.sprintf("%d - %d - %d" , m_cInfo.nYear , m_cInfo.nMonth,  m_cInfo.nDate );
	fprintf(m_pFile,"<tr>\n");
	fprintf(m_pFile,"<td %s>%s</td>\n" ,tableTdStyle , m_cInfo.strPartName );
	fprintf(m_pFile,"<td %s>%s</td>\n" ,tableTdStyle , m_cInfo.strPartNo   );
	fprintf(m_pFile,"<td %s>%s</td>\n" ,tableTdStyle , m_cInfo.strPartPos);
	fprintf(m_pFile,"<td %s>%s</td>\n" ,tableTdStyle , TOCHAR(_date));
	fprintf(m_pFile,"</tr>\n\n");

	fprintf(m_pFile,"<tr>\n");
    fprintf(m_pFile,"<th %s>%s</th>\n" ,tableThStyle, TOCHAR(strReportPath));
	fprintf(m_pFile,"<td colspan=\"6\" %s>%s</td>\n" ,tableTdStyle , TOCHAR(m_szDataFile));
	fprintf(m_pFile,"</tr>\n\n");
	fprintf(m_pFile,"</table></td></tr>\n</table>\n\n");//table
	fprintf(m_pFile,"<br>\n");
}

void DopplerHtmlReport::UpdateGroupConfig(int nGroupId_)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG* _pGroup = &_pConfig->group[nGroupId_];
    int _iLang = _pConfig->AppEvn.eLanguage;

    m_probeModel.sprintf("%s" , _pGroup->probe[0].strName);
    m_probeSerial.sprintf("%s" , _pGroup->probe[0].strSerial);
    m_probeFrequency.sprintf("%.1f MHz" , _pGroup->probe[0].fFrequency);
    m_wedgeModel.sprintf("%s" , _pGroup->wedge[0].strSerial);
    m_wedgeAngle.sprintf("%.1f deg" , _pGroup->wedge[0].fWedgeAngle );


	m_beamDelay.sprintf("%.2f us" , _pGroup->anBeamDelay[0] * 0.001) ;
    m_start.sprintf( "%.2f mm"	, _pGroup->fSampleStart);
    m_range.sprintf( "%.2f mm"	, _pGroup->fSampleRange);
	m_prf.sprintf  ( "%d"		, (int)_pConfig->common.scanner.fPrf) ;
    m_type.sprintf ("%s" , string_groupMode[_pGroup->eGroupMode]);
	m_averagingFactor.sprintf("%d" , _pGroup->eAveraging << 1 ) ;

    m_scaleFactor.sprintf("1");
    QString g_strOnOff[] = {
        QString(QObject::tr("Off")),
        QString(QObject::tr("ON")),
        QString(QObject::tr("Defect")),
    };
    QString g_strRectifier[] = {//UpdateGroupConfig()
        QString(QObject::tr("RF")),
        QString(QObject::tr("HW+")),
        QString(QObject::tr("HW-")),
        QString(QObject::tr("FW")),
    };
    QString g_strTxRxMode[] = {
         QString(QObject::tr("Pitch Catch")),
         QString(QObject::tr("Pitch Echo")),
         QString(QObject::tr("Through Trans")),
         QString(QObject::tr("TOFD")),
     };

    if(_pGroup->bVedioFilter > 0) {
        m_videoFilter = g_strOnOff[1];
    } else {
        m_videoFilter = g_strOnOff[0];
    }

    m_rectification = g_strRectifier[_pGroup->eRectifier];
    m_bandPassFilter.sprintf("%s" , string_filter[_pGroup->eFileter]);
	m_gain.sprintf( "%.1f dB" ,  _pGroup->fGain );

    m_mode = g_strTxRxMode[_pGroup->eTxRxMode];

    m_soundVelocity.sprintf("%.1f m/s" , _pGroup->fVelocity);
    m_pulseWidth.sprintf("%d ns" , _pGroup->nPulserWidth );
    m_scanOffset.sprintf("%.1f mm" , _pGroup->fScanOffset);
    m_indexOffset.sprintf("%.1f mm" ,_pGroup->fIndexOffset);
	m_skew.sprintf("%d" , _pGroup->eSkew * 90) ;

    m_gateIstart.sprintf("%.2f mm" ,_pGroup->gate[setup_GATE_I].fStart);
    m_gateIwidth.sprintf("%.2f mm" ,_pGroup->gate[setup_GATE_I].fWidth);
    m_gateAstart.sprintf("%.2f mm" ,_pGroup->gate[setup_GATE_A].fStart);
    m_gateAwidth.sprintf("%.2f mm" ,_pGroup->gate[setup_GATE_A].fWidth);
    m_gateBstart.sprintf("%.2f mm" ,_pGroup->gate[setup_GATE_B].fStart);
    m_gateBwidth.sprintf("%.2f mm" ,_pGroup->gate[setup_GATE_B].fWidth);

    m_gateIthreshold.sprintf("%d %%" , _pGroup->gate[setup_GATE_I].nThreshold );
    m_gateAthreshold.sprintf("%d %%" , _pGroup->gate[setup_GATE_A].nThreshold );
    m_gateBthreshold.sprintf("%d %%" , _pGroup->gate[setup_GATE_B].nThreshold );

    QString g_strGateSync[] = {
        QString(QObject::tr("Pulse")),
        QString(QObject::tr("I/")),
        QString(QObject::tr("A/"))
    };
    m_gateIsynchro = g_strGateSync[_pGroup->gate[setup_GATE_I].eSynChro];
    m_gateAsynchro = g_strGateSync[_pGroup->gate[setup_GATE_A].eSynChro];
    m_gateBsynchro = g_strGateSync[_pGroup->gate[setup_GATE_B].eSynChro];

    m_probeAperture.sprintf ("%d", _pGroup->law.nElemQtyFir);
    m_usedElementQty.sprintf("%d", _pGroup->law.nElemQtyFir);
    m_firstTXelement.sprintf("%d", _pGroup->law.nFirstElemFir);
    m_lastTXelement.sprintf ("%d", _pGroup->law.nLastElemFir);

	m_firstRXelement = QString("-");
	m_lastRXelement = QString("-");

    m_startAngle.sprintf("%.1f deg" ,_pGroup->law.nAngleStartRefract * 0.1);
	if(setup_LAW_TYPE_LINEAR == _pGroup->law.eLawType )//线扫
	{
		m_resolution.sprintf("%d" , _pGroup->law.nElemStepFir ) ;
		m_stopAngle = QString("-");
		m_angleResolution = QString("-");
	}
	else
	{
		m_resolution = QString("-");
        m_stopAngle.sprintf("%.1f deg" ,_pGroup->law.nAngleStopRefract * 0.1);
		m_angleResolution.sprintf("%.1f deg" ,_pGroup->law.nAngleStepRefract * 0.1);

	}

    QString g_strLawConfig[] = {
        QString(QObject::tr("Azimuthal")),
        QString(QObject::tr("Linear")),
        QString(QObject::tr("Depth")),
        QString(QObject::tr("Static"))
    };
    QString g_strFocalType[] = {// (report)
        QString(QObject::tr("Half Path")),
        QString(QObject::tr("True Depth")),
        QString(QObject::tr("Projection")),
        QString(QObject::tr("Focal Plane")),
        QString(QObject::tr("Automatic"))
    };
    m_lawConfiguration = g_strLawConfig[_pGroup->law.eLawType];
	m_focalPointType = _pGroup->law.eFocalType ;
    m_focalType = g_strFocalType[_pGroup->law.eFocalType];

	switch(m_focalPointType)
	{
	case 0:
	case 1:
		m_positionStart.sprintf("%.2f mm" ,_pGroup->law.fPositionStart ) ;
		m_positionEnd = QString("-");
		m_positionStep = QString("-");
		break;
	case 2:
        m_offsetStart.sprintf("%.2f mm" ,_pGroup->law.fOffsetStart );
		m_positionStep = QString("-");
		m_positionEnd  = QString("-");
		m_depthEnd	 = QString("-");
		break;
	case 3:
		m_offsetStart.sprintf("%.2f mm" ,_pGroup->law.fOffsetStart ) ;
		m_offsetEnd.sprintf  ("%.2f mm" ,_pGroup->law.fOffsetStop  ) ;
		m_depthStart.sprintf ("%.2f mm" ,_pGroup->law.fDepthStart  ) ;
		m_depthEnd.sprintf   ("%.2f mm" ,_pGroup->law.fDepthStop   ) ;
		break;
	default:
		break;
	}
    m_material = _pGroup->part.material.strName[_iLang];
    QString g_strGeometry[]={
        QString(QObject::tr("Plate")),
        QString(QObject::tr("OD")),
        QString(QObject::tr("ID"))
    };
    m_geometry = g_strGeometry[_pGroup->part.eGeometry];
    m_thickness.sprintf("%.2f mm", _pGroup->part.afSize[0]);

    int* _pMeasure = _pConfig->group[nGroupId_].aeMeasureType;
    int _nQty = 0;

    for(int i = 0; i < 5; i++)
	{
		if(_pMeasure[i])
		{
			m_szField[nGroupId_][_nQty] = CalcMeasurement::GetMeasureString(nGroupId_ , (FEILD_VALUE_INDEX)_pMeasure[i]);
			m_szFieldUnit[nGroupId_][_nQty] = CalcMeasurement::GetMeasureUnit((FEILD_VALUE_INDEX)_pMeasure[i]) ;
            _nQty++;
		}
	}

	for(int i = _nQty ; i< 5 ; i++)
	{
		m_szField[nGroupId_][i] = m_szFieldUnit[nGroupId_][i] = QString("-");
	}
}


void DopplerHtmlReport::SprintfGroupProbeConfig(int nGroupId_)
{
	fprintfReportGroupStart(nGroupId_);
	fprintfReportGroupProbe();
	fprintfReportGroupSetup();
	fprintfReportGroupCalculator();
	fprintfReportGroupPart();
}


void DopplerHtmlReport::fprintfReportGroupStart(int group)
{
	fprintf(m_pFile , "<br />\n");
	fprintf(m_pFile ,"<h3></h3>");
	fprintf(m_pFile , "<table %s>\n" ,tableWidth);
	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td><hr /></td>\n" );
	fprintf(m_pFile , "</tr>\n");
	fprintf(m_pFile , "<tr>\n");

    QString _str;
    _str.append(QObject::tr("GROUP "));
    _str.append(QString::number((group + 1), 'f', 0));
    _str.append(QObject::tr(":"));
//    _str.sprintf("GROUP %d", group + 1);

	fprintf(m_pFile , "<th align=left>%s</th>\n" , TOCHAR(_str));
	fprintf(m_pFile , "</tr>\n");
	fprintf(m_pFile , "</table>\n\n");
}

void DopplerHtmlReport::fprintfReportGroupProbe()
{
    QString g_strProbe[] = {
        QString(QObject::tr("Probe Characterization")),
        QString(QObject::tr("Probe Model")),
        QString(QObject::tr("Probe Serial")),
        QString(QObject::tr("Probe Frequency")),
        QString(QObject::tr("Wedge Model")),
        QString(QObject::tr("Wedge Angle")),
        QString(QObject::tr("Wedge Aperture"))
    };
	int i;
	fprintf(m_pFile , "<br />\n");
    fprintf(m_pFile , "%s\n", TOCHAR(g_strProbe[0]));
	fprintf(m_pFile , "<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);//table

	fprintf(m_pFile , "<tr>\n");
	for(i = 1 ;i < 4 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strProbe[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<Tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_probeModel));//"Probe Model"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_probeSerial));//"Probe Serial #"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_probeFrequency));//"Probe Frequency"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	for(i = 4 ;i < 7 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strProbe[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_wedgeModel));//"Wedge Model"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_wedgeAngle));//"Wedge Angle"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_probeAperture));//"Probe Aperture"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");
	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空1行
	fprintf(m_pFile , "</tr>\n\n");
	fprintf(m_pFile , "</table></td></tr>\n</table>\n\n");//table
}

void DopplerHtmlReport::fprintfReportGroupSetup()
{
    QString g_strGroupSetup[] = {
        QString(QObject::tr("Setup")),
        //1
        QString(QObject::tr("Beam Delay")),
        QString(QObject::tr("Sample Start")),
        QString(QObject::tr("Sample Range")),
        QString(QObject::tr("PRF")),
        QString(QObject::tr("Type")),
        QString(QObject::tr("Averaging Factor")),
        //7
        QString(QObject::tr("Scale Factor")),
        QString(QObject::tr("Video Filter")),
        QString(QObject::tr("Rectification")),
        QString(QObject::tr("Band-Pass Filter")),
        //11
        QString(QObject::tr("Gain")),
        QString(QObject::tr("Mode")),
        QString(QObject::tr("Sound Velocity")),
        QString(QObject::tr("Pulse Width")),
        //15
        QString(QObject::tr("Scan Offset")),
        QString(QObject::tr("Index Offset")),
        QString(QObject::tr("Skew")),
        QString(QObject::tr("Gate")),
        QString(QObject::tr("Start")),
        QString(QObject::tr("Width")),
        QString(QObject::tr("Threshold")),
        QString(QObject::tr("Synchro"))
        //23
    };
	int i;
	fprintf(m_pFile , "<br />\n");
    fprintf(m_pFile , "%s\n", TOCHAR(g_strGroupSetup[0]));
	fprintf(m_pFile , "<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);//table

	fprintf(m_pFile , "<tr>\n");
	for(i = 1 ;i < 7 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strGroupSetup[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_beamDelay));//Beam Delay
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_start));//Start (Half Path)
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_range));//Range (Half Path)
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_prf));//PRF
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_type));//Type
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_averagingFactor));//Averaging Factor
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	for(i = 7 ;i < 11 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strGroupSetup[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_scaleFactor));//Scale Factor
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_videoFilter));//"Video Filter"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_rectification));//"Rectification"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_bandPassFilter));//"Band-Pass Filter"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	for(i = 11 ;i < 15;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strGroupSetup[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	//fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_voltage));//"Voltage"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gain));//Gain
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_mode));//"Mode"
	//fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_waveType));//Wave Type
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_soundVelocity));//Sound Velocity
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_pulseWidth));//Pulse Width
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	for(i = 15 ;i <18 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strGroupSetup[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_scanOffset));//Scan Offset
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_indexOffset));//Index Offset
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_skew));//Skew
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr><td colspan=6><hr /></td></tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	for(i = 18 ;i < 23 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strGroupSetup[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>I</td>\n" ,tableTdStyle);//Gate
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateIstart));//Start
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateIwidth));//Width
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateIthreshold));//Threshold
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateIsynchro));//"Synchro"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>A</td>\n" ,tableTdStyle);//Gate
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateAstart));//Start
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateAwidth));//Width
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateAthreshold));//Threshold
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateAsynchro));//"Synchro"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>B</td>\n" ,tableTdStyle);//Gate
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateBstart));//Start
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateBwidth));//Width
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateBthreshold));//Threshold
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_gateBsynchro));//"Synchro"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "</table></td></tr>\n</table>\n\n");//table
}

void DopplerHtmlReport::fprintfReportGroupCalculator()
{
    QString g_strCalculator[]= {
        QString(QObject::tr("Calculator")),

        QString(QObject::tr("Element Qty")),
        QString(QObject::tr("First TX Element")),
        QString(QObject::tr("Last TX Element")),
        QString(QObject::tr("First RX Element")),
        QString(QObject::tr("Last RX Element")),
        QString(QObject::tr("Resolution")),
        //
        QString(QObject::tr("Start Angle")),
        QString(QObject::tr("Stop Angle")),
        QString(QObject::tr("Angle Resolution")),
        QString(QObject::tr("Law Configuration")),
        //
        QString(QObject::tr("Focal Type")),
        QString(QObject::tr("Position Start")),
        QString(QObject::tr("Position End")),
        QString(QObject::tr("Position Step")),
        QString(QObject::tr("Offset Start")),
        QString(QObject::tr("Offset Stop")),
        QString(QObject::tr("Depth Start")),
        QString(QObject::tr("Depth Stop"))
    };

	int i;
	fprintf(m_pFile , "<br />\n");
    fprintf(m_pFile , "%s\n", TOCHAR(g_strCalculator[0]));
	fprintf(m_pFile , "<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);//table

	fprintf(m_pFile , "<tr>\n");
	for(i = 1 ; i < 7 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_usedElementQty));//Used Element Qty.
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_firstTXelement));//First TX Element
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_lastTXelement));//Last TX Element
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_firstRXelement));//First RX Element
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_lastRXelement));//Last RX Element
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_resolution));//Resolution
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	for(i = 7 ;i < 11 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_startAngle));//Start Angle
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_stopAngle));//Stop Angle
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_angleResolution));//Angle Resolution
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_lawConfiguration));//"Law Configuration"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
    fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[11]));
	switch(m_focalPointType)
	{
	case 0:
	case 1:
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[12]));
		break;
	case 2:
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[15]));
		break;
	case 3:
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[15]));
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[16]));
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[17]));
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strCalculator[18]));
		break;
	default:
		break;
    };

	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_focalType));//"Focal Type"
	switch(m_focalPointType)
	{
	case 0:
	case 1:
	 fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_positionStart));//Position Start
	 break;
	case 2:
	 fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_offsetStart));//Offset Start
	 break;
	case 3:
	 fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_offsetStart));//Offset Start
	 fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_offsetEnd));//Offset End
	 fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_depthStart));//Depth Start
	 fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_depthEnd));//Depth End
	 break;
	default:
	 break;
	}
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);
	fprintf(m_pFile , "</tr>\n\n");


	fprintf(m_pFile , "</table></td></tr>\n</table>\n\n");//table
}

void DopplerHtmlReport::fprintfReportGroupPart()
{
    QString g_strGroupPart[] = {
        QString(QObject::tr("Part")),
        QString(QObject::tr("Material")),
        QString(QObject::tr("Geometry")),
        QString(QObject::tr("Thickness"))
    };
	int i;
	fprintf(m_pFile , "<br />\n");
    fprintf(m_pFile , "%s\n", TOCHAR(g_strGroupPart[0]));
	fprintf(m_pFile , "<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);//table

	fprintf(m_pFile , "<tr>\n");
	for(i = 1 ;i < 4 ;++i)
	{
        fprintf(m_pFile , "<th %s>%s</th>\n" ,tableThStyle, TOCHAR(g_strGroupPart[i]));
	}
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_material));//"Material"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_geometry));//"Geometry"
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,TOCHAR(m_thickness));//Thickness
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "<td %s>%s</td>\n" ,tableTdStyle ,tdSpace);//空
	fprintf(m_pFile , "</tr>\n\n");

	fprintf(m_pFile , "</table></td></tr>\n</table>\n\n");//table
}

void DopplerHtmlReport::SprintfReportTable()
{
	fprintf(m_pFile , "<br />\n");
	fprintf(m_pFile ,"<h3></h3>");
	fprintf(m_pFile , "<table %s>\n" ,tableWidth);
	fprintf(m_pFile , "<tr>\n");
	fprintf(m_pFile , "<td><hr /></td>\n" );
	fprintf(m_pFile , "</tr>\n");
	fprintf(m_pFile , "<tr>\n");

    QString tableName = QString(QObject::tr("Table"));
    fprintf(m_pFile , "<th align=left>%s</th>\n" , TOCHAR(tableName));

	fprintf(m_pFile , "</tr>\n");
	fprintf(m_pFile , "</table>\n\n");
	fprintf(m_pFile , "<br />\n");
}

void DopplerHtmlReport::SprintfGroupMeasure()
{
    int _nGroupId;
	const char* bodyFormat = "i";
	const char* newLineFormat = " align=\"center\" style=\"word-break:break-all; word-wrap:break-word;\"";

    for(int i=0; i < m_cValueList.count(); i++)
	{
        fprintf(m_pFile, "\t\t</br>\n");

        ReportValueItem _value = m_cValueList.at(i);
        _nGroupId = _value.nGroupId;
        fprintf(m_pFile, "<table %s frame=box>\n<tr><td><table %s>\n", tableWidth, sonTableStyle);//table

        QString str_1 = QString(QObject::tr("Scan Pos"));
        QString str_2 = QString(QObject::tr("Group"));
        QString str_3 = QString(QObject::tr("Law ID"));

        fprintf(m_pFile ,"\t\t\t<th>%s</th>\n" , TOCHAR(str_1));
        fprintf(m_pFile ,"\t\t\t<th>%s</th>\n" , TOCHAR(str_2));
        fprintf(m_pFile ,"\t\t\t<th>%s</th>\n" , TOCHAR(str_3));

        for(int i = 0 ; i < 5 ; i++){
            fprintf(m_pFile ,"\t\t\t<th>%s<br>(%s)</th>\n" , TOCHAR(_value.szField[i]) ,TOCHAR(_value.szFieldUnit[i]));
        }

		fprintf(m_pFile ,"\t\t\t<tr>\n");
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%.2f</%s></td>\n", newLineFormat ,bodyFormat , _value.fPos, bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%d</%s></td>\n", newLineFormat ,bodyFormat , _value.nGroupId + 1, bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%d</%s></td>\n", newLineFormat ,bodyFormat , _value.nLawId  + 1, bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%s</%s></td>\n", newLineFormat ,bodyFormat ,TOCHAR(_value.szValue[0]) ,bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%s</%s></td>\n", newLineFormat ,bodyFormat ,TOCHAR(_value.szValue[1]) ,bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%s</%s></td>\n", newLineFormat ,bodyFormat ,TOCHAR(_value.szValue[2]) ,bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%s</%s></td>\n", newLineFormat ,bodyFormat ,TOCHAR(_value.szValue[3]) ,bodyFormat);
        fprintf(m_pFile ,"\t\t\t<td%s><%s>%s</%s></td>\n", newLineFormat ,bodyFormat ,TOCHAR(_value.szValue[4]) ,bodyFormat);
		fprintf(m_pFile ,"\t\t\t</tr>\n");
		fprintf(m_pFile , "</table></td></tr>\n</table>\n\n");//table

        QString sourceImageName = m_strFolder + QString("\\") + _value.szPixmap;
        QString _strDir = m_strReportDir + sourceImageName;
        fprintf(m_pFile, "\t\t<img src=\"%s\" width=%d>\n",  TOCHAR(sourceImageName), TABLE_WIDTH);
//		fprintf(m_pFile ,"\t\t</br>\n");
        CopyFileToPath(_strDir , _value.szPixmap);
	}
    fprintf(m_pFile, "\t\t</br>\n");
    fprintf(m_pFile, "\t\t</br>\n");
}

void DopplerHtmlReport::SfprintfReportSignature()
{
    QString g_strSignature[] = {
        QString(QObject::tr("Technician Name:")),
        QString(QObject::tr("Technician Signature:")),
        QString(QObject::tr("Contractor:")),
        QString(QObject::tr("Date:"))
    };

	fprintf(m_pFile , "<table %s frame=box>\n<tr><td><table %s>\n" ,tableWidth ,sonTableStyle);//table
	for(int i = 0 ;i < 4 ;++i)
	{
		fprintf(m_pFile , "<tr>\n");
         fprintf(m_pFile , "<td width=25%% align=\"right\">%s</td>\n", TOCHAR(g_strSignature[i]));
		fprintf(m_pFile , "<td >%s</td>\n" , tdSpace);
		fprintf(m_pFile , "</tr>\n");
		fprintf(m_pFile , "<tr>\n");
		fprintf(m_pFile , "<td width=100%%>%s</td>\n"  ,tdSpace);
		fprintf(m_pFile , "<td><hr /></td>\n");
		fprintf(m_pFile , "</tr>\n\n");
	}
	fprintf(m_pFile , "</table></td></tr>\n</table>\n\n");//table
}

bool DopplerHtmlReport::CopyFileToPath(QString toDir ,QString sourceDir)
{
    toDir.replace("\\", "/");
	if (sourceDir == toDir){
		return true;
	}

	if (!QFile::exists(sourceDir)){
		return false;
	}

    QDir *createfile = new QDir;
	bool exist = createfile->exists(toDir);

	if (exist)
	{
		 createfile->remove(toDir);
	}

	if(!QFile::copy(sourceDir, toDir))
	{
		return false;
	}
	return true;
}

void DopplerHtmlReport::CreateFolder()
{
    QString _str;
	QDir foder;
    _str.sprintf("%s", m_strReportDir);
	if(!foder.exists(_str))
        foder.mkdir(_str);

	_str.clear();
    _str.sprintf("%s%s" , m_strReportDir, TOCHAR(m_strFolder));
    if(!foder.exists(_str))  foder.mkdir(_str);

    _str.sprintf("%s%s%s", m_strReportDir, TOCHAR(m_strFolder), "/logo.png");
    CopyFileToPath(_str, QString(m_strReportLogo));
}

void DopplerHtmlReport::set_data_path(QString &str)
{
    m_dataFilePath = str;
}
