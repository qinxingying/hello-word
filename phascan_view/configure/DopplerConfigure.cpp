﻿#include "DopplerConfigure.h"
#include "DopplerXMLReader.h"
#include "DopplerColorIndex.h"
#include <string.h>
#include <QFile>
#include <QFileinfo.h>
#include <QDataStream>
#include <math.h>
#include <QDebug>
#include "gHeader.h"

#include <report/DopplerHtmlReport.h>
#include <process/ParameterProcess.h>
#include "config_phascan_ii/config.h"

extern int Cscan_range,Csrc_start,Bscan_range,Bsrc_start;
extern double RL_EL_SL[5];
int Phascan_Version;
static const PROBE_CONFIG DEFAULT_PROBE_PA  = {
	"Default PA" ,
	"Doppler Serial" ,
	64 ,			//主轴阵元数
	1,				//副轴阵元数
	0,				//location
	5,				//Frequency
	0.75,			//主轴间距
	0,
	1,
	5,
	5,
};


static const PROBE_CONFIG DEFAULT_PROBE_UT  = {
	"Default UT" ,
	"Doppler Serial" ,
	1,					//主轴阵元数
	1,					//副轴阵元数
	0,					//location
	5,					//Frequency
	0,					//主轴间距
	0,
	5,
	5,
	5,
};

static const WEDGE_CONFIG  DEFAULT_WEDGE_PA  =
{
	"Default PA" ,
	"Doppler Serial" ,
	setup_WEDGE_TYPE_PA ,
	setup_WEDGE_ORIENTATION_NORMAL ,
    (float)36.1,
	0 ,
	2330 ,
	2330 ,
    (float)7.12, (float)-20.11 , 0 , 0 , 0 ,
	60 , 30 , 40 ,
	0 , 0 ,
};

static const WEDGE_CONFIG  DEFAULT_WEDGE_UT  =
{
	"default UT" ,
	"Doppler Serial" ,
	setup_WEDGE_TYPE_UT ,
	setup_WEDGE_ORIENTATION_NORMAL ,
	0 ,
	0 ,
	2330 ,
	2330 ,
	0 , 0 , 0 , 0 , 0 ,
	60 , 30 , 40 ,
	0 , 0 ,
};


DopplerConfigure* DopplerConfigure::m_pConfig = NULL ;

DopplerConfigure* DopplerConfigure::Instance()
{
	if(!m_pConfig)
	{
		m_pConfig = new DopplerConfigure() ;
	}
	return m_pConfig ;
}

DopplerConfigure::DopplerConfigure(QObject *parent) :
	QObject(parent)
{
    memset(group, 0x00, sizeof(group)*(setup_MAX_GROUP_QTY+1));

	m_pData = NULL;
	m_pDataShadow = NULL;   

	for(int i = 0; i < setup_MAX_GROUP_QTY; i++)
	{
		ClearDefectInfo(i);
		m_dfParam[i].index = 0;
		m_dfParam[i].pDFHead = NULL;
		m_dfParam[i].pDFEnd = NULL;
		m_nCutBmpNo[i] = 0;
	}

    m_listMaterial = new QList<MATERIAL*>;
	m_listMaterial->clear();

    QString _str = QCoreApplication::applicationDirPath() + "/init/Material.init";
    DopplerXMLReader::LoadMaterial(&_str, m_listMaterial);

    g_strColorAmp = QCoreApplication::applicationDirPath() + "/init/palette/ONDT_Amplitude.pal";
    g_strColorThickness	= QCoreApplication::applicationDirPath() + "/init/palette/ONDT_Corrosion.pal";
    g_strColorRectifier	= QCoreApplication::applicationDirPath() + "/init/palette/ONDT_RFTOFD.pal";

    InitCommonConfig();
	m_szFileInUse.clear();

    coupleCScanGroupInfo buff;
    buff.calculateState = false;
    buff.oldPartThickness = 0;
    buff.data.clear();
    coupleCScanData.clear();
    for(int i = 0; i < setup_MAX_GROUP_QTY; i++)
    {
        coupleCScanData.append(buff);
    }

	header.eType = FILE_TYPE_CONFIG ;
	const char* _strVersion = "DOPPLER CONFIGURE FILE VERSION 1.0"  ;
	memcpy(header.strVersion  ,  _strVersion , strlen(_strVersion)) ;
	m_pDataFile = new DopplerDataFileOperateor(0);

    m_pReport = new DopplerHtmlReport();
	m_pReport->InitReportInfo();

    OpenEvn();
}


DopplerConfigure::~DopplerConfigure()
{
	ReleaseShadowData();	
    delete m_pDataFile;
    delete m_pReport;

	SaveEvn();
	ReleaseAllDefect();
}

void DopplerConfigure::OpenEvn()
{
    QString g_strDataFilePath = QCoreApplication::applicationDirPath() + "/data";
    QString g_strPartDir = QCoreApplication::applicationDirPath() + "/init/part/ncc/";
    QString _strPathName = QCoreApplication::applicationDirPath() + "/init/EVN.DPL";

    QFile file(_strPathName);
	file.open (QIODevice::ReadOnly);
	QDataStream reader(&file);

    int ret = reader.readRawData((char*)&AppEvn, sizeof(SYSTEM_ENVIRMENT));

    if(ret != sizeof(SYSTEM_ENVIRMENT))
	{
        GetExePathName1(g_strDataFilePath.toLatin1().data(), _strPathName.toLatin1().data());
        strcpy(AppEvn.strDataFilePath, _strPathName.toLatin1().data());

        GetExePathName1(g_strPartDir.toLatin1().data(), _strPathName.toLatin1().data());
        strcpy(AppEvn.strNccFilePath, _strPathName.toLatin1().data());

        AppEvn.eLanguage = setup_LANG_ENGLISH;
		AppEvn.eUnit	 = setup_SOUND_AXIX_UNIT_MM;
		AppEvn.iTofdDataProMode = 0;
        AppEvn.bSAxisCursorSync	   = true;
        AppEvn.bTrueDepth_A_S_Sync = true;
        AppEvn.bShowRL = false;
        AppEvn.bShowSL = false;
        AppEvn.bShowEL = false;

		AppEvn.anMeasureSelection[0][0] = 1  ;
		AppEvn.anMeasureSelection[0][1] = 32 ;
		AppEvn.anMeasureSelection[0][2] = 34 ;
		AppEvn.anMeasureSelection[0][3] = 0  ;
		AppEvn.anMeasureSelection[0][4] = 0  ;
        AppEvn.anMeasureSelection[0][5] = 0  ;
        AppEvn.anMeasureSelection[0][6] = 0  ;
        AppEvn.anMeasureSelection[0][7] = 0  ;
        AppEvn.anMeasureSelection[0][8] = 0  ;
        AppEvn.anMeasureSelection[0][9] = 0  ;
		AppEvn.anMeasureSelection[1][0] = 42 ;
		AppEvn.anMeasureSelection[1][1] = 43 ;
		AppEvn.anMeasureSelection[1][2] = 44 ;
		AppEvn.anMeasureSelection[1][3] = 45 ;
		AppEvn.anMeasureSelection[1][4] = 0  ;
        AppEvn.anMeasureSelection[1][5] = 0  ;
        AppEvn.anMeasureSelection[1][6] = 0  ;
        AppEvn.anMeasureSelection[1][7] = 0  ;
        AppEvn.anMeasureSelection[1][8] = 0  ;
        AppEvn.anMeasureSelection[1][9] = 0  ;

        for(int i = 0 ; i < ENV_MAX_GROUP_QTY; i++)
		{
            AppEvn.bShowCursor[i]	= true ;
            AppEvn.bShowMeasure[i]  = true ;
            AppEvn.bShowWeld[i]	    = false;
            AppEvn.bShowThickness[i]= false;
            AppEvn.bShowLwBw[i]	    = true;
			AppEvn.bShowDefect[i]	= true;
            AppEvn.bShowGateA[i]    = 1;
            AppEvn.bShowGateB[i]    = 0;
            AppEvn.bShowGateI[i]    = 0;
            AppEvn.CScanSource[i][0]= 0;
            AppEvn.CScanSource[i][1]= 3;
            AppEvn.DisplayMode[i]   = 12;
            AppEvn.bShowCurve[i]    = true;
            AppEvn.CurSS[i]         = 0;
            AppEvn.Standard[i]      = 0;
            AppEvn.Thickness[i]     = 0;
            AppEvn.bShowAScanMeasure[i] = true;
            AppEvn.bShowBScanMeasure[i] = true;
            AppEvn.bShowCScanMeasure[i] = true;
            AppEvn.bShowSScanMeasure[i] = true;
            AppEvn.bCursor[i][setup_CURSOR_LAW] = 0;

            AppEvn.bCursor[i][setup_CURSOR_A_REF] =
                AppEvn.bCursor[i][setup_CURSOR_U_REF] =
                AppEvn.bCursor[i][setup_CURSOR_S_REF] =
                AppEvn.bCursor[i][setup_CURSOR_I_REF] =
                AppEvn.bCursor[i][setup_CURSOR_VPA_REF] =
                AppEvn.bCursor[i][setup_CURSOR_TFOD_LW] = 10 ;

            AppEvn.bCursor[i][setup_CURSOR_A_MES] =
                AppEvn.bCursor[i][setup_CURSOR_U_MES] =
                AppEvn.bCursor[i][setup_CURSOR_S_MES] =
                AppEvn.bCursor[i][setup_CURSOR_I_MES] =
                AppEvn.bCursor[i][setup_CURSOR_VPA_MES] =
                AppEvn.bCursor[i][setup_CURSOR_TFOD_BW]= 20 ;
		}
		SetLastDate();
	}

    CUR_RES.bShowRL = AppEvn.bShowRL;
    CUR_RES.bShowEL = AppEvn.bShowEL;
    CUR_RES.bShowSL = AppEvn.bShowSL;
    for(int i = 0 ; i < ENV_MAX_GROUP_QTY; i++)
	{
        for( int j = 0; j < setup_MAX_MEASURE_QTY; j++){
            group[i].aeMeasureType[j] = AppEvn.anMeasureSelection[0][j];
        }

		group[i].bShowCursor	= AppEvn.bShowCursor[i] ;
        group[i].bShowThickness = AppEvn.bShowThickness[i];
        group[i].bShowWeldPart  = AppEvn.bShowWeld[i];
		group[i].bShowMeasure   = AppEvn.bShowMeasure[i] ;
		group[i].bShowLwBw	    = AppEvn.bShowLwBw[i] ;
        group[i].bShowDefect	= true;
        group[i].bShowGateA     = AppEvn.bShowGateA[i];
        group[i].bShowGateB     = AppEvn.bShowGateB[i];
        group[i].bShowGateI     = AppEvn.bShowGateI[i];
        group[i].DisplayMode    = AppEvn.DisplayMode[i];
        group[i].bShowCurve     = AppEvn.bShowCurve[i];
        CUR_RES.CurSS[i]        = AppEvn.CurSS[i];
        CUR_RES.Standard[i]     = AppEvn.Standard[i];
        CUR_RES.Thickness[i]    = AppEvn.Thickness[i];
        group[i].bShowAScanMeasure = AppEvn.bShowAScanMeasure[i];
        group[i].bShowBScanMeasure = AppEvn.bShowBScanMeasure[i];
        group[i].bShowCScanMeasure = AppEvn.bShowCScanMeasure[i];
        group[i].bShowSScanMeasure = AppEvn.bShowSScanMeasure[i];
        for(int j = 1; j < setup_CURSOR_MAX; j++){
            group[i].afCursor[j] = AppEvn.bCursor[i][j];
        }
	}
	AppEvn.bSAxisCursorSync		= false;
	AppEvn.bRegStatus = false;

	file.close();
}

void DopplerConfigure::SaveEvn()
{
	for(int i = 0 ; i < common.nGroupQty ; i++)
	{
		if(group[i].eGroupMode == setup_GROUP_MODE_PA )
		{
            for( int j = 0; j < setup_MAX_MEASURE_QTY; j++){
                AppEvn.anMeasureSelection[0][j] = group[i].aeMeasureType[j];
            }
        }else{
            for( int j = 0; j < setup_MAX_MEASURE_QTY; j++){
                AppEvn.anMeasureSelection[1][j] = group[i].aeMeasureType[j];
            }
		}

        AppEvn.bShowCursor[i]		= group[i].bShowCursor;
        AppEvn.bShowThickness[i]	= group[i].bShowThickness;
        AppEvn.bShowWeld[i]			= group[i].bShowWeldPart;
        AppEvn.bShowMeasure[i]		= group[i].bShowMeasure;
        AppEvn.bShowLwBw[i]			= group[i].bShowLwBw;
        AppEvn.bShowDefect[i]		= group[i].bShowDefect;
        AppEvn.bShowGateA[i]        = group[i].bShowGateA;
        AppEvn.bShowGateB[i]        = group[i].bShowGateB;
        AppEvn.bShowGateI[i]        = group[i].bShowGateI;
        AppEvn.CScanSource[i][0]    = (int)group[i].eCScanSource[0];
        AppEvn.CScanSource[i][1]    = (int)group[i].eCScanSource[1];
        AppEvn.DisplayMode[i]       = group[i].DisplayMode;
        AppEvn.bShowCurve[i]        = group[i].bShowCurve;
        AppEvn.CurSS[i]             = CUR_RES.CurSS[i];
        AppEvn.Standard[i]          = CUR_RES.Standard[i];
        AppEvn.Thickness[i]         = CUR_RES.Thickness[i];
        AppEvn.bShowAScanMeasure[i] = group[i].bShowAScanMeasure;
        AppEvn.bShowBScanMeasure[i] = group[i].bShowBScanMeasure;
        AppEvn.bShowCScanMeasure[i] = group[i].bShowCScanMeasure;
        AppEvn.bShowSScanMeasure[i] = group[i].bShowSScanMeasure;

        for(int j = 1; j < setup_CURSOR_MAX; j++){
            AppEvn.bCursor[i][j] = group[i].afCursor[j];
        }

	}
    AppEvn.bShowRL = CUR_RES.bShowRL;
    AppEvn.bShowEL = CUR_RES.bShowEL;
    AppEvn.bShowSL = CUR_RES.bShowSL;

	if(AppEvn.bRegStatus) {
		SetLastDate();
	}

    QString _strPathName = QCoreApplication::applicationDirPath() + "/init/EVN.DPL";
	QFile file(_strPathName);
	file.open (QIODevice::WriteOnly);
	QDataStream write(&file);
    write.writeRawData((char*)&AppEvn, sizeof(SYSTEM_ENVIRMENT));
    file.close();
}

void DopplerConfigure::setSetting(int group, const QString &valueName, int value)
{
    QString strPathName = QCoreApplication::applicationDirPath() + "/init/setting.ini";
    QSettings s(strPathName,QSettings::IniFormat);
    if (s.status() != QSettings::NoError) {
        qDebug("setting test error");
        return ;
    }
    s.beginWriteArray("setings");
    s.setArrayIndex(group);
    s.setValue(valueName,value);
    s.endArray();
}

int DopplerConfigure::getSetting(int group, const QString &valueName)
{
    QString strPathName = QCoreApplication::applicationDirPath() + "/init/setting.ini";
    QSettings s(strPathName,QSettings::IniFormat);
    if (s.status() != QSettings::NoError) {
        qDebug("setting test error");
        return -1;
    }
    s.beginReadArray("setings");
    s.setArrayIndex(group);
    if(! s.contains(valueName)){
        return -1;
    }
    int value = s.value(valueName).toInt();
    s.endArray();
    return value;
}

int DopplerConfigure::OpenConfig(QString& path_)
{
	FilePathPro(path_);

	QFile file(path_);
	file.open (QIODevice::ReadOnly);
	QDataStream reader(&file);
	int ret ;

	ret = reader.readRawData((char*)&header , sizeof(FILE_HEADER)) ;
	if(ret < 0) return ret ;
	ret = reader.readRawData((char*)&common , sizeof(COMMON_CONFIG))  ;
	if(ret < 0) return ret ;
	int _nGroupQty = common.nGroupQty;
	for(int i = 0 ; i< _nGroupQty ; i++)
	{
		ret = reader.readRawData((char*)(&(group[i])) , sizeof(GROUP_CONFIG))  ;
		if(ret < 0) return ret ;
	}

	file.close();
	int _iMax = RectifyScanLength();
	CreateShadowData(_iMax);
	return 0 ;
}

void DopplerConfigure::SaveConfig(QString& path_)
{
	QFile file(path_);
	file.open (QIODevice::WriteOnly);
	QDataStream write(&file);

	write.writeRawData((char*)&header , sizeof(FILE_HEADER)) ;
	write.writeRawData((char*)&common , sizeof(COMMON_CONFIG)) ;
	int _nGroupQty = common.nGroupQty;
	for(int i = 0 ; i< _nGroupQty ; i++)
	{
		write.writeRawData((char*)(&(group[i])) , sizeof(GROUP_CONFIG))  ;
	}
	file.close();
}

/*!
  \brief 解析后缀为.data的文件

  \param path_ 文件的完整路径

  \return 成功返回0；失败返回 -1

*/
int DopplerConfigure::OpenData(QString& path_)
{
	FilePathPro(path_);

    if(!Config::instance()->load(path_, m_pDataFile)) {
        qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"
                 << " not Phascan II data format!!!!";
        int ret = m_pDataFile->LoadDataFile(m_szFileInUse) ;
        Config::instance()->set_is_phascan_ii(false);
        if(ret)  return -1;
    }
    ReleaseShadowData();

	OldConfigureToConfigure(m_pDataFile);
	OldGroupToGroup(m_pDataFile) ;
    ReorderDefect();
	m_pData = m_pDataFile->GetData();
    m_pDataSize = m_pDataFile->GetDataSize();
//    GROUP_INFO *targetGroup;
//    if(Config::instance()->is_phascan_ii()) {
//        targetGroup = m_pDataFile->GetGroupInfo(0);
//    } else {
//        targetGroup = m_pDataFile->GetGroupInfo(0);
//    }
    InitTOPCMerge();
    //SIZING_CURVES &targetCurves = targetGroup->SizingCurves;

	int _iMax = RectifyScanLength();
	CreateShadowData(_iMax);
	memcpy(&comTmp, &common, sizeof(COMMON_CONFIG));

    InitTOPCInfo();
    for(int i = 0; i < setup_MAX_GROUP_QTY + 1; i++){
        if(group[i].TopCData.topcData){
            free(group[i].TopCData.topcData);
        }
        memset( &group[i].TopCData, 0x00, sizeof(TOPC_DATA));
    }

    m_pReport->set_data_path(QFileInfo(path_).absolutePath());
	m_pReport->InitReportInfo();
	return 0;
}

int DopplerConfigure::RectifyScanLength()
{
    for(int i = 0; i < setup_MAX_DISPLAY_QTY; i++) {
		m_nComDisplay[i] = i;
	}

    if(common.scanner.eScanType == setup_SCAN_TYPE_RASTER){
        int index = Config::instance()->data_mark_length() - 1;
        int iMax  = index;
        for(int i = index; i >= 0; i--){
            if(common.nRecMark[i]){
                iMax = i;
                break;
            }
        }

        int scanQty = (common.scanner.fScanStop - common.scanner.fScanStart) / common.scanner.fScanStep + 0.5;
        int buff = iMax / scanQty;
        if( iMax % scanQty == 0){
            buff--;
        }
        int offsetNum = buff + 1;
        rasterOffset.resize(offsetNum);
        for(int i = 0; i < rasterOffset.size(); i++){
            rasterOffset[i] = 0;
        }
        //如果只有1条，就按线扫处理
        if( buff < 1){
            common.scanner.eScanType = setup_SCAN_TYPE_ONE_LINE;
            common.scanner.fScanStop = iMax * common.scanner.fScanStep + common.scanner.fScanStart;
            common.nRecMax = iMax+1;
            if(common.scanner.eScanEncoderType){
                common.scanner.fScanend     =   common.scanner.fScanStop;
            }else{
                common.scanner.fScanend     =   common.scanner.fScanStop/common.scanner.fPrf;
            }
            return iMax + 1;
        }
        common.scanner.fIndexStop = common.scanner.fIndexStart + buff * common.scanner.fIndexStep;
        common.nRecMax = iMax + 1;
        return iMax + 1;
    }

	int _index = (common.scanner.fScanStop - common.scanner.fScanStart) / common.scanner.fScanStep + 0.5 ;
	int _iMax = _index;
	for(int i = _index; i >= 0; i--)
	{
		if(common.nRecMark[i])
		{
			_iMax = i;
			break;
		}
	}
	common.scanner.fScanStop = _iMax * common.scanner.fScanStep + common.scanner.fScanStart;
	common.nRecMax = _iMax+1;
    if(common.scanner.eScanEncoderType)
        common.scanner.fScanend     =   common.scanner.fScanStop;
    else
        //common.scanner.fScanend     =   common.scanner.fScanStop/common.scanner.fPrf + common.scanner.fScanStart;
        common.scanner.fScanend     =   common.scanner.fScanStop/common.scanner.fPrf;

	return _iMax+1;
}

void DopplerConfigure::CreateShadowData(int iLen_)
{
    //ReleaseShadowData();
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nFrameSize = _process->GetTotalDataSize() ;
	int _iTotalSize = iLen_ * _nFrameSize;

    if(common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        m_pDataShadow = new WDATA[_iTotalSize+10];
        memset(m_pDataShadow, 0x00, _iTotalSize);
        if(m_pData) {
            if(_iTotalSize > m_pDataSize){
                memcpy(m_pDataShadow, m_pData, m_pDataSize);
            }else{
                memcpy(m_pDataShadow, m_pData, _iTotalSize);
            }
        }
    }else{
        m_pDataShadow = m_pData;
    }
	common.nDataSize  = _iTotalSize;
	common.nScanOffMax = 0;
	memset(common.nScanOff, 0x00, setup_MAX_GROUP_QTY);
}

void DopplerConfigure::ReleaseShadowData()
{
    if(common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        if(m_pDataShadow){
            delete m_pDataShadow;
            m_pDataShadow = NULL;
        }
    }else{
        m_pDataShadow = NULL;
    }
}

/*!
  \brief 组的扫查偏置改变后，重新计算

*/
void DopplerConfigure::ResetShadowData()
{
	int _nQty = comTmp.nGroupQty;

	float _fScanOff[setup_MAX_GROUP_QTY];
    {
		float _fMinOff = 200000;
        float _fMaxOff = -200000;
		for(int i = 0; i < _nQty; i++) {
			_fScanOff[i] = group[i].fScanOffset;
			if(_fScanOff[i] < _fMinOff) {
				_fMinOff = _fScanOff[i];
			}

			if(_fScanOff[i] > _fMaxOff) {
				_fMaxOff = _fScanOff[i];
			}
		}
		common.scanner.fScanStart = comTmp.scanner.fScanStart + _fMinOff;	/**/        
        common.scanner.fScanStop  = comTmp.scanner.fScanStop  + _fMaxOff;	/**/
        if(common.scanner.eScanEncoderType){
            common.scanner.fScanStart2  = common.scanner.fScanStart;
            common.scanner.fScanend     =   common.scanner.fScanStop;
        }
        else{
            common.scanner.fScanStart2  = common.scanner.fScanStart/common.scanner.fPrf;
            common.scanner.fScanend     =   common.scanner.fScanStop/common.scanner.fPrf;
        }
    }

//    int _nChanOffTmp[setup_MAX_GROUP_QTY];
//	for(int i = 0; i < _nQty; i++) {
//        _nChanOffTmp[i] = common.nScanOff[i];
//	}

	int _nOffTab[setup_MAX_GROUP_QTY];
	int _nMin = 2000000000;
	for(int i = 0; i < _nQty; i++) {
		_nOffTab[i] = _fScanOff[i] / comTmp.scanner.fScanStep;
		if(_nOffTab[i] < _nMin) {
			_nMin = _nOffTab[i];
		}
	}

	int _nMax = 0;
	for(int i = 0; i < _nQty; i++) {
		common.nScanOff[i] = _nOffTab[i] - _nMin;
		if(common.nScanOff[i] > _nMax) {
			_nMax = common.nScanOff[i];
		}
	}

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nFrameSize = _process->GetTotalDataSize() ;

	common.nScanOffMax = _nMax;
	common.nRecMax   = comTmp.nRecMax + _nMax;
	common.nDataSize = _nFrameSize * common.nRecMax;

	memset(common.nRecMark, 0x00, setup_MAX_REC_LEN);
	memcpy(&common.nRecMark[common.nScanOffMax], &comTmp.nRecMark[comTmp.nScanOffMax], comTmp.nRecMax);
}

/*!
  \brief 初始化位置,读取新的文件后将pos置为开始位置

*/
void DopplerConfigure::initScanPos()
{
    common.scanner.fScanPos = common.scanner.fScanStart;
}

U8* DopplerConfigure::GetComDisplayPoint()
{
	return m_nComDisplay;
}

WDATA* DopplerConfigure::GetShadowDataPoint()
{
	return m_pDataShadow ;
}

WDATA* DopplerConfigure::GetFileDataPoint() const
{
	return m_pData ;
}

void DopplerConfigure::InitCommonConfig()
{
	memset(&common, 0x00, sizeof(common));

	header.eType = FILE_TYPE_CONFIG  ;
	memcpy (header.strVersion , CONFIG_FILE_VERSION , strlen(CONFIG_FILE_VERSION)) ;
	common.nGroupQty = 1 ;
	common.bUnifiedPart = 1 ;
    common.aidedAnalysis.aidedStatus = false;
    common.aidedAnalysis.aidedMethodId = 0;
	//common.instrument.eTxRxModePA  = setup_TX_RX_MODE_PE ;
	//common.instrument.eTxRxModeUT  = setup_TX_RX_MODE_PE ;
	common.instrument.eVoltagePA   = setup_VOLTAGE_50	;
	common.instrument.eVoltageUT   = setup_VOLTAGE_50	;

	memset((char*)(&common.alarm) , 0 , sizeof(ALARM_CONFIG) * 3) ;

    common.scanner.eScanEncoderType = setup_ENCODER_TYPE_TIMER  ;
	common.scanner.eScanType	= setup_SCAN_TYPE_ONE_LINE  ;
	common.scanner.eScanMode	= setup_SCAN_NORMAL;
	common.scanner.fScanPos	 = 5.0  ;
	common.scanner.fPrf		 = 20.0 ;

	common.scanner.fScanStart   =  0  ;
	common.scanner.fIndexStart  =  0  ;
	common.scanner.fScanStop	=  800;
	common.scanner.fIndexStop   =  800;
	common.scanner.fScanStep	=  1.0;
    common.scanner.fIndexStep   =  1.0;
    common.scanner.fScanStart2  =   0;
    common.scanner.fLawStart    =   0;
    common.scanner.fLawStop     =   0;
    common.scanner.fScanend     =   800;
    common.scanner.fLawQty      =   0;

	ENCODER_CONFIG _encoder = {
		 setup_ENC_MODE_QUADRATURE  ,
		 setup_ENC_POLARITY_NORNAL,
		 48.0  ,
		 0
    };

    for( int i = 0; i < setup_MAX_ENCODER_QTY; i++){
        memcpy((char*)(&common.scanner.encoder[i]) , (void*)&_encoder , sizeof(ENCODER_CONFIG)) ;
    }
	InitGroupConfig(0);
}

void DopplerConfigure::InitGroupConfig(int nGroupId_)
{
	GROUP_CONFIG* _pConfig = &group[nGroupId_]  ;

	_pConfig->eGroupMode  = setup_GROUP_MODE_PA  ;
	_pConfig->eTravelMode = setup_TRAVEL_MODE_TRUE_DEPTH  ;
    _pConfig->nWedgeDelay  =  0;
    _pConfig->fSampleStart =  0;
    _pConfig->fSampleRange =  48;
    _pConfig->nPointQty	   =  600;
    _pConfig->fVelocity	   =  5920 ;

    _pConfig->nTimeStart   = 2 * (1000000 * _pConfig->fSampleStart / _pConfig->fVelocity);
    _pConfig->nTimeRange   = 2 * (1000000 * _pConfig->fSampleRange / _pConfig->fVelocity);

    _pConfig->fGain		   =  20	;
	_pConfig->fRefGain	   =  0	 ;
    _pConfig->fSumGain	   =  (float)24.8  ;
	_pConfig->bPointQtyAuto  = -1;
	_pConfig->bSumGainAuto   = -1;
	/* 发射接收 */
    _pConfig->nTrigeStart	 = 1;
	_pConfig->nReceiveStart  = 1;

    _pConfig->eFileter	     = setup_FILTER_AUTO  ;
	_pConfig->eRectifier	 = setup_RECTIFIER_FW ;
	_pConfig->eAveraging	 = setup_AVERAGE_1	;
	_pConfig->bVedioFilter   = 1 ;

	// 设置的探头频率，和对应的脉宽
	_pConfig->fTriFrequency  = 5; 		/* Mhz*/
	_pConfig->nPulserWidth   = 100;			/* ns */

	_pConfig->afCursor[setup_CURSOR_LAW] = 0;
	/* 参考光标 */

//	_pConfig->afCursor[setup_CURSOR_A_REF] =
//		_pConfig->afCursor[setup_CURSOR_U_REF] =
//		_pConfig->afCursor[setup_CURSOR_S_REF] =
//		_pConfig->afCursor[setup_CURSOR_I_REF] =
//		_pConfig->afCursor[setup_CURSOR_VPA_REF] =
//		_pConfig->afCursor[setup_CURSOR_TFOD_LW] = 10 ;

//	_pConfig->afCursor[setup_CURSOR_A_MES] =
//		_pConfig->afCursor[setup_CURSOR_U_MES] =
//		_pConfig->afCursor[setup_CURSOR_S_MES] =
//		_pConfig->afCursor[setup_CURSOR_I_MES] =
//		_pConfig->afCursor[setup_CURSOR_VPA_MES] =
//		_pConfig->afCursor[setup_CURSOR_TFOD_BW]= 20 ;
	//-----------------------------------------------------------------
	// thickness range for c scan display
	_pConfig->eCScanSource[0]	= setup_CSCAN_AMP_A ;
	_pConfig->eCScanSource[1]	= setup_CSCAN_POS_A ;
	_pConfig->fMinThickness		= 0;
	_pConfig->fMaxThickness		= 50;
    _pConfig->CScanShowAll      = false;

	_pConfig->fScanOffset		= 0.0;	/*mm*/
	_pConfig->fIndexOffset		= 0.0;	  /*mm*/
	_pConfig->eSkew				= setup_PROBE_PART_SKEW_90 ;

	/*  校准状态  */
	_pConfig->bVelocityCalib	= 0 ;
	_pConfig->bWedgeDelayCalib	= 0 ;
	_pConfig->bSensationCalib	= 0 ;

	memset((void*)_pConfig->afGainOffset , 0 , sizeof(float) * setup_MAX_GROUP_LAW_QTY)  ;
	memset((void*)_pConfig->anBeamDelay ,  0 , sizeof(int) * setup_MAX_GROUP_LAW_QTY)  ;
	memset((void*)_pConfig->afBeamPos ,    0 , sizeof(float) * setup_MAX_GROUP_LAW_QTY)  ;

	GATE_CONFIG	 gate[3] = {	{ 10  , 7 ,  5 , setup_GATE_AYNC_PUL , 0} ,
								{ 10  , 8 , 10 , setup_GATE_AYNC_PUL , 0} ,
								{ 10  , 9 , 20 , setup_GATE_AYNC_PUL , 0} };
	memcpy((void*)&_pConfig->gate[0] , (void*)&gate , 3 * sizeof(GATE_CONFIG) )  ;

	PART_CONFIG&  _part = _pConfig->part ;
	memset(&_part, 0x00, sizeof(PART_CONFIG));
	_part.eGeometry	 = setup_PART_GEOMETRY_FLAT ;
	_part.afSize[0] = 20  ;
	_part.afSize[1] = _part.afSize[2] = 100 ;

    MATERIAL& _material  = _part.material ;
    QString _name = QString::fromLocal8Bit("普通钢");
    strcpy(_material.strName[0] , "Steel common") ;
    strcpy(_material.strName[1] , _name.toUtf8().data()) ;
    strcpy(_material.strName[2] , " ") ;
    strcpy(_material.strName[3] , " ") ;

	_material.fVelocityLon = 5920 ;
	_material.fVelocityTran= 3230 ;
    _material.fDensity	 = (float)7.9  ;

	WELD& _weld		  = _part.weld   ;
	_weld.eType	 = setup_WELD_V  ;
	_weld.eSymmetry = setup_WELD_SYMMETRY  ;
	_weld.weland_height  = 5.0 ;
	_weld.weland_offset  = 5.0 ;
    _weld.fizone_height  = 15  ;
	_weld.fizone_angle   = 30  ;
	_weld.fizone_radius  = 10  ;
    _weld.fizone_down_height = 10;
    _weld.fizone_down_angle = 60;

	memcpy((void*)&_pConfig->wedge[0] , (void*)&DEFAULT_WEDGE_PA , sizeof(WEDGE_CONFIG)) ;
	memcpy((void*)&_pConfig->wedge[1] , (void*)&DEFAULT_WEDGE_PA , sizeof(WEDGE_CONFIG))  ;

	memcpy((void*)&_pConfig->probe[0] , (void*)&DEFAULT_PROBE_PA , sizeof(PROBE_CONFIG))  ;
	memcpy((void*)&_pConfig->probe[1] , (void*)&DEFAULT_PROBE_PA , sizeof(PROBE_CONFIG))  ;

	InitLawComfing(nGroupId_) ;

	CURVES& _curve  = _pConfig->curve  ;

	_curve.bTcgCalibrated  =  0;
	_curve.bApplyToAllLaws =  0;

	_curve.eType			= setup_CURVE_TYPE_NULL;
	_curve.nPointQty		= 1;
	_curve.fCurStep			= 0.5;
    _curve.fMatAtten		= (float)0.1;
	_curve.fAmpOffsetAmp	= 80;
	_curve.fAmpOffsetLinear	= 80;
	_curve.nLinearDelay		= 10 ;

	memset((void*)&_curve.faAmpLinear ,   0 , sizeof(float) * setup_DAC_POINT_QTY)  ;
	memset((void*)&_curve.faAmpPosition , 0 , sizeof(float) * setup_DAC_POINT_QTY)  ;
	memset((void*)&_curve.faAmpRef ,      0 , sizeof(float) * setup_MAX_GROUP_LAW_QTY)  ;
	memset((void*)&_curve.faAmp ,         0 , sizeof(float) * setup_MAX_GROUP_LAW_QTY * setup_DAC_POINT_QTY)  ;
	memset((void*)&_curve.faPosition ,    0 , sizeof(float) * setup_MAX_GROUP_LAW_QTY * setup_DAC_POINT_QTY)  ;

    DopplerColorIndex _color;
    _color.LoadPallete(g_strColorAmp);
	memcpy((void*)_pConfig->color.Amp , _color.GetColorIndex() , 256 * 3);

    _color.LoadPallete(g_strColorThickness);
	memcpy((void*)_pConfig->color.Thickness , _color.GetColorIndex() , 256 * 3);

    _color.LoadPallete(g_strColorRectifier);
	memcpy((void*)_pConfig->color.Rf ,_color.GetColorIndex() , 256 * 3);

}

void DopplerConfigure::GroupModeChanged(int nGroupId_ , setup_GROUP_MODE eMode_)
{
	GROUP_CONFIG& _group = group[nGroupId_]  ;
	_group.eGroupMode = eMode_ ;
	if(eMode_ == setup_GROUP_MODE_PAUT)
	{
		memcpy((void*)&_group.wedge[0] , (void*)&DEFAULT_WEDGE_PA , sizeof(WEDGE_CONFIG))  ;
		memcpy((void*)&_group.wedge[1] , (void*)&DEFAULT_WEDGE_PA , sizeof(WEDGE_CONFIG))  ;
		memcpy((void*)&_group.probe[0] , (void*)&DEFAULT_PROBE_PA , sizeof(PROBE_CONFIG))  ;
		memcpy((void*)&_group.probe[1] , (void*)&DEFAULT_PROBE_PA , sizeof(PROBE_CONFIG))  ;
		InitLawComfing(nGroupId_) ;
		LAW_CONFIG& _law = _group.law  ;
		_law.nElemQtyFir		= 1  ;
		_law.nLastElemFir	   = 1  ;
	}
	else if(eMode_ == setup_GROUP_MODE_PA)
	{
		memcpy((void*)&_group.wedge[0] , (void*)&DEFAULT_WEDGE_PA , sizeof(WEDGE_CONFIG))  ;
		memcpy((void*)&_group.wedge[1] , (void*)&DEFAULT_WEDGE_PA , sizeof(WEDGE_CONFIG))  ;
		memcpy((void*)&_group.probe[0] , (void*)&DEFAULT_PROBE_PA , sizeof(PROBE_CONFIG))  ;
		memcpy((void*)&_group.probe[1] , (void*)&DEFAULT_PROBE_PA , sizeof(PROBE_CONFIG))  ;
		InitLawComfing(nGroupId_) ;
	}
	else
	{
		memcpy((void*)&_group.wedge[0] , (void*)&DEFAULT_WEDGE_UT , sizeof(WEDGE_CONFIG))  ;
		memcpy((void*)&_group.wedge[1] , (void*)&DEFAULT_WEDGE_UT , sizeof(WEDGE_CONFIG))  ;
		memcpy((void*)&_group.probe[0] , (void*)&DEFAULT_PROBE_UT , sizeof(PROBE_CONFIG))  ;
		memcpy((void*)&_group.probe[1] , (void*)&DEFAULT_PROBE_UT , sizeof(PROBE_CONFIG))  ;
		InitLawComfing(nGroupId_) ;

        LAW_CONFIG& _law = _group.law;
        _law.nElemQtyFir = 1;
        _law.nLastElemFir = 1;
	}
}

void DopplerConfigure::InitLawComfing(int nGroupId_)
{
    GROUP_CONFIG& config = group[nGroupId_];
    LAW_CONFIG& _law = config.law;
    memset((void*)&_law, 0, sizeof(LAW_CONFIG));
    _law.eLawType		 = setup_LAW_TYPE_AZIMUTHAL;
    _law.eAngleType		 = setup_ANGLE_TYPE_REFRACT;
    _law.eFocalType		 = setup_FOCAL_TYPE_TRUE_DEPTH;
    _law.nAngleStartRefract = 300; // 30 DEG
    _law.nAngleStopRefract  = 500;
    _law.nAngleStepRefract  = 100;

    _law.fPositionStart	 = 30;
    _law.fPositionStep	 = 1;
    _law.fPositionStop	 = 60;
    _law.fOffsetStart	 = 20;
    _law.fOffsetStop	 = 100;
    _law.fDepthStart	 = 100;
    _law.fDepthStop		 = 20;

    _law.nElemQtyFir	 = 8;
    _law.nElemQtySec	 = 1;
    _law.nFirstElemFir	 = 1;
    _law.nFirstElemSec	 = 1;
    _law.nLastElemFir	 = 8;
    _law.nElemStepFir	 = 1;
    _law.nElemStepSec	 = 1;
}

/*!
  \brief 根据数据文件DrawInfo信息更新common的参数，需要在数据文件读取成功后进行

  \param pConf_ 读取数据文件的入口
*/
void DopplerConfigure::OldConfigureToConfigure(DopplerDataFileOperateor* pConf_)
{
	DRAW_INFO_PACK* _pack = pConf_->GetDrawInfo();
	common.nGroupQty = _pack->nGroupNum ;
    common.dataModeStatus = true;
    common.scanner.fPrf  = pConf_->GetGroupInfo(0)->prf1 / 10.0;
    common.aidedAnalysis.aidedGroupId = 0;
    common.aidedAnalysis.aidedStatus  = false;
    Cscan_range = 0;
    Csrc_start = 0;
    Bscan_range = 0;
    Bsrc_start = 0;
	if(_pack->nEncodeType)
	{
        common.scanner.eScanType	= setup_SCAN_TYPE_ONE_LINE;
        common.scanner.eScanEncoderType = static_cast<setup_ENCODER_TYPE> (_pack->nEncodeType);
		common.scanner.eScanMode	= setup_SCAN_NORMAL;
        common.scanner.fScanPos		=  _pack->nScanStart		/ 1000.0;
        common.scanner.fIndexPos	=  _pack->nInspecStart	    / 1000.0;
        common.scanner.fScanStart   =  _pack->nScanStart		/ 1000.0;
        common.scanner.fScanStop	=  _pack->nScanEnd		    / 1000.0;
        common.scanner.fScanStep	=  _pack->nScanResolution   / 1000.0;
        common.scanner.fIndexStart  =  _pack->nInspecStart	    / 1000.0;
        common.scanner.fIndexStop   =  _pack->nInspecEnd		/ 1000.0;
        common.scanner.fIndexStep   =  _pack->nInspecResolution / 1000.0;
        common.scanner.fScanStart2  =   common.scanner.fScanStart;
        common.scanner.fLawStart    =   0;
        common.scanner.fLawStop     =   0;
        common.scanner.fLawQty      =   0;

        common.scanner.fScanend     =   common.scanner.fScanStop;
	}
	else
	{
        common.scanner.eScanType	= setup_SCAN_TYPE_ONE_LINE;
        common.scanner.eScanEncoderType = setup_ENCODER_TYPE_TIMER;
		common.scanner.eScanMode	= setup_SCAN_NORMAL;
		common.scanner.fScanPos		=  0 ;
		common.scanner.fIndexPos	=  0 ;
		common.scanner.fScanStart   =  0 ;
		common.scanner.fScanStop	=  _pack->nScanEnd / 1000   ;
		common.scanner.fScanStep	=  1 ;
		common.scanner.fIndexStart  =  0 ;
		common.scanner.fIndexStop   =  _pack->nInspecEnd / 1000;
		common.scanner.fIndexStep   =  1 ;
        common.scanner.fScanStart2  =   common.scanner.fScanStart;
        common.scanner.fLawStart    =   0;
        common.scanner.fLawStop     =   0;
        common.scanner.fLawQty      =   0;
        common.scanner.fScanend     =   common.scanner.fScanStop/common.scanner.fPrf + common.scanner.fScanStart;
	}
	//common.scanner.eEncoderType = setup_ENCODER_TYPE_ENCODER_1 ;
	int _nScanIndex = (common.scanner.fScanStop - common.scanner.fScanStart) / common.scanner.fScanStep + 1.5 ;
    memset(common.nRecMark , 0 , setup_MAX_REC_LEN );
    if(Config::instance()->is_phascan_ii()) {
        Config::instance()->getScannerData( common.scanner);
        memcpy(common.nRecMark , Config::instance()->data_mark(), Config::instance()->data_mark_length()) ;
    } else {
        memcpy(common.nRecMark , _pack->bScanMark , _nScanIndex) ;
    }

    //清除旧的耦合监控c扫数据，每个文件载入只计算一次
    for( int i = 0; i < setup_MAX_GROUP_QTY; i++)
    {
        coupleCScanData[i].calculateState = false;
        coupleCScanData[i].oldPartThickness = 0;
        coupleCScanData[i].data.clear();
    }
}

/*!
  \brief 根据数据文件GroupInfo信息更新group的参数，需要在数据文件读取成功后进行

  \param pConf_ 读取数据文件的入口
*/
void DopplerConfigure::OldGroupToGroup(DopplerDataFileOperateor* pConf_)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    if(Config::instance()->is_phascan_ii()) {
//        if(Config::instance()->is_200wave()){
//            Phascan_Version = 5;
//        }else{
//            Phascan_Version = 4;
//        }
        Phascan_Version = Config::instance()->getPhascanVersion();
    } else {
        Phascan_Version = m_pDataFile->GetFileHeader()->version - m_pDataFile->GetFileHeader()->size -
                m_pDataFile->GetFileHeader()->reserved;
    }
    //qDebug()<<"Phascan_Version"<<Phascan_Version;

	for(int i = 0 ; i < common.nGroupQty ; i++)
	{
		GROUP_INFO* _pGroupInfo = pConf_->GetGroupInfo(i) ;
        GROUP_CONFIG& _group  = group[i] ;
        _group.ThicknessType[i] = 0;
        //_group.bShowGateA     = 1;
        //_group.bShowGateB     = _group.bShowGateI = 0;
		_group.eGroupMode	  = (setup_GROUP_MODE)_pGroupInfo->group_mode  ;
        switch (_pGroupInfo->ut_unit) {
        case 0:
            _group.eTravelMode = setup_TRAVEL_MODE_HALF_PATH;
            break;
        case 1:
            _group.eTravelMode = setup_TRAVEL_MODE_TIME;
            break;
        case 2:
            _group.eTravelMode = setup_TRAVEL_MODE_TRUE_DEPTH;
            break;
        default:
            _group.eTravelMode = setup_TRAVEL_MODE_TRUE_DEPTH;
            break;
        }
        if( _group.eGroupMode != setup_GROUP_MODE_PA && _group.eTravelMode == setup_TRAVEL_MODE_HALF_PATH){
            _group.eTravelMode = setup_TRAVEL_MODE_TRUE_DEPTH;
        }
        //_group.eTravelMode	  = _pGroupInfo->ut_unit ? setup_TRAVEL_MODE_TRUE_DEPTH : setup_TRAVEL_MODE_HALF_PATH;
		_group.eTxRxMode	  = (setup_TX_RX_MODE)_pGroupInfo->tx_rxmode1 ;
		_group.nWedgeDelay	  = _pGroupInfo->wedge_delay ;
        _group.fVelocity	  = _pGroupInfo->velocity   / 100.0 ;
		_group.nTimeStart     = _pGroupInfo->start;									/* 时间起点 单位 ns */
		_group.nTimeRange     = _pGroupInfo->range;									/* 时间范围 单位 ns */
		_group.fSampleStart   = _process->DistNsToMm(i , _pGroupInfo->start) ;		/* 显示范围 单位 mm		*/
		_group.fSampleRange   = _process->DistNsToMm(i , _pGroupInfo->range) ;		/* 扫描延时 单位 mm		*/
		_group.nPointQty	  = _pGroupInfo->point_qty ;		/* 点个数 */
        _group.on_off_status  = _pGroupInfo->on_off_status;
        //on_off_status第一个比特位是0
        //if(!((_group.on_off_status & (0x01 << 0)) != 0))
        if((_group.on_off_status & 0x01) == 0)
        {
            _group.fGain		  = _pGroupInfo->gain / 100.0;			/* 增益 0 - 80 db  _STEP 0.01dB */
            _group.fRefGain	      = 0;
            _group.RefGain        = 0;
        }
        //else if((_group.on_off_status & (0x01 << 0)) != 0)
        else
        {
            _group.fGain		  = _pGroupInfo->gainr / 100.0;			/* 增益 0 - 80 db  _STEP 0.01dB */
            _group.fRefGain	      = 0;
            _group.RefGain        = _pGroupInfo->gain / 100.0 - _pGroupInfo->gainr / 100.0;
        }
        _group.CoupleGain = 0;

        CUR_RES.REF_Gain[i]      = 0;
        CUR_RES.Com_Gain[i]      = 0;
        CUR_RES.CurRL[i]         = -4;
        CUR_RES.CurEL[i]         = -18;
        CUR_RES.CurSL[i]         = -12;
        CUR_RES.Ref_Amp[i]       = 80;
//        CUR_RES.CurSS[i]         = AppEvn.CurSS[i];
//        CUR_RES.Standard[i]      = AppEvn.Standard[i];
//        CUR_RES.Thickness[i]     = AppEvn.Thickness[i];
        _group.fSumGain	      = 20 * log10(_pGroupInfo->sum_gain / 16.0);
		_group.bPointQtyAuto  = 0;
		_group.bSumGainAuto   = 0;
        /* 耦合监控 版本4和5才有此功能，on_off_status 第2位表示开启关闭，0关闭；1开启 3位到21表示声速的10倍值*/
        if(Phascan_Version == 4 || Phascan_Version == 5 || Phascan_Version == 6 || Phascan_Version == 7)
        {
            _group.coupleMonitoringState = (( _group.on_off_status>>2) & 0x01);
            _group.coupleMonitoringVelocity = ((_group.on_off_status>>3) & 0x3FFFF)/10;
        }
        else
        {
            _group.coupleMonitoringState = false;
            _group.coupleMonitoringVelocity = _pGroupInfo->velocity /100;
        }
        //qDebug()<<"coupleMonitoringState"<<_group.coupleMonitoringState;

		/* 发射接收 */
        _group.nTrigeStart	  = _pGroupInfo->pulser1;	/* 1~128 - elem_qty(聚焦阵元数最大为32) + 1
                                                        指定发射阵元与机器配置相关我们是128阵元最大,值与connect P 一样 */
		_group.nReceiveStart  = _pGroupInfo->receiver1;		/* 接收阵元 必须是 PR 模式才能调节 */

		_group.eFileter	      = (setup_FILTER_MODE)_pGroupInfo->filter_pos1 ;		/* 滤波 */
		_group.eRectifier	  = (setup_RECTIFIER_MODE)_pGroupInfo->rectifier1;		/* 检波 */
		_group.eAveraging	  = (setup_AVERAGE_MODE)_pGroupInfo->averaging1;		/* 平均 */
		_group.bVedioFilter   = _pGroupInfo->on_off_status  & 0x02;

		// 设置的探头频率，和对应的脉宽
		_group.fTriFrequency  = _pGroupInfo->frequency1 / 1000.0;	/* Mhz*/
		_group.nPulserWidth   = _pGroupInfo->pulser_width1 / 100;			/* ns */

		/* 参考光标 */
		//_group.afCursor[setup_CURSOR_MAX]  ;
		// thickness range for c scan display
        //int CScanSource1 = getSetting(i,"CScansource1");
        int CScanSource1 = AppEvn.CScanSource[i][0];
        if(CScanSource1 < 0){
            CScanSource1 = (int)setup_CSCAN_AMP_A;
        }
        //int CScanSource2 = getSetting(i,"CScansource2");
        int CScanSource2 = AppEvn.CScanSource[i][1];
        if(CScanSource2 < 0){
            CScanSource2 = (int)setup_CSCAN_POS_A;
        }
        if(!Config::instance()->is_phascan_ii()) {
            if(common.scanner.eScanEncoderType && Phascan_Version >= 2) {
                common.scanner.encoder[common.scanner.eScanEncoderType - 1].fResulotion = _pGroupInfo->cursors_info[0].resolution/100.0;
            }
        }

        _group.eCScanSource[0]= (setup_CSCAN_SOURCE_MODE)CScanSource1 ;
        _group.eCScanSource[1]= (setup_CSCAN_SOURCE_MODE)CScanSource2 ;
		_group.fMinThickness  = _pGroupInfo->min_thickness/1000.0 ;		/* Measurements->Thickness->min */
		_group.fMaxThickness  = _pGroupInfo->max_thickness/1000.0 ;		/* Measurements->Thickness->max */
        _group.CScanShowAll   = false;

		/*  校准状态  */
		_group.bVelocityCalib	 = _pGroupInfo->VelocityCalibrated  ;
		_group.bWedgeDelayCalib  = _pGroupInfo->WedgeDelayCalibrated;
		_group.bSensationCalib   = _pGroupInfo->SensationCalibrated ;

		for(int k = 0 ; k < setup_MAX_GROUP_LAW_QTY ; k++)
		{
			_group.afGainOffset[k] = _pGroupInfo->gain_offset[k] / 100.0;
			_group.anBeamDelay[k]  = _pGroupInfo->beam_delay[k];
			_group.afBeamPos[k]    = _pGroupInfo->field_distance[k];
		}

        for(int k = 0 ; k < setup_GATE_MAX; k++)
		{
			GATE_CONFIG& _gate = _group.gate[k] ;
			GATE_INFO&   _Gate = _pGroupInfo->gate[k] ;
			_gate.fStart	   = _process->DistNsToMm(i , _Gate.start) ;
			_gate.fWidth	   = _process->DistNsToMm(i , _Gate.width) ;
			_gate.nThreshold   = _Gate.height ;
			_gate.eMeasure	   = _Gate.measure;
			_gate.eSynChro	   = (setup_GATE_AYNC_TYPE)_Gate.synchro;
            _gate.gTravelMode  = (setup_GATE_TRAVEL_MODE)_Gate.travel_mode;
		}

		SIZING_CURVES& _Curve = _pGroupInfo->SizingCurves;
		CURVES&        _curve = _group.curve;

		_curve.bTcgCalibrated	=  _Curve.bTcgCalibrated;
		_curve.bApplyToAllLaws	=  _Curve.bApplyToAllLaws;

		_curve.eType			= (setup_CURVE_TYPE)_Curve.curve_pos;
		_curve.nPointPos		= _Curve.point_pos;
		_curve.nPointQty        = _Curve.dac_point_qty;
		_curve.fCurStep         = _Curve.curve_step / 1000.0f;
		_curve.fMatAtten        = _Curve.mat_atten / 1000.0f;			// 暂不知道
		_curve.fAmpOffsetAmp    = _Curve.ref_ampl_offset / 1000.0f;
		_curve.fAmpOffsetLinear = _Curve.linear_ref_ampl / 1000.0f ;
		_curve.nLinearDelay     = _Curve.delay ;			// 暂不知道
        //qDebug()<<"_curve.fAmpOffsetLinear"<<_curve.fAmpOffsetLinear;
		for(int k = 0; k < setup_DAC_POINT_QTY; k++)
		{
			_curve.faAmpLinear[k]   = _Curve.linearamplitude[k] / 1000.0f;
			_curve.faAmpPosition[k] = _Curve.linearposition[k] / 1000.0f;
		}

		for(int k = 0; k < setup_MAX_GROUP_LAW_QTY; k++)
		{
			_curve.faAmpRef[k]     = _Curve.dac_ref_ampl[k] / 1000.0f;
			for(int j = 0; j < setup_DAC_POINT_QTY; j++)
			{
				_curve.faAmp[k][j]      = _Curve.amplitude[k][j] / 1000.0f;
				_curve.faPosition[k][j] = _Curve.position[k][j] / 1000.0f;
			}
		}
//		_group.bShowCurve = 0;
//		if(_curve.nPointQty > 0 && _curve.eType > setup_CURVE_TYPE_NULL && _curve.eType < setup_CURVE_TYPE_MAX)
//			_group.bShowCurve = 1;
        //CUR_RES.bShowRL = 0;
        //CUR_RES.bShowEL = 0;
        //CUR_RES.bShowSL = 0;
        memset(RL_EL_SL,0,sizeof(RL_EL_SL));
		//-----------------------------------------
		LAW_CONFIG& _LawConfig = _group.law ;
		LAW_INFO&     _LawInfo = _pGroupInfo->law_info ;
		_LawConfig.eLawType	      = (setup_LAW_TYPE)_LawInfo.Focal_type  ;
        if(_LawConfig.eLawType == setup_LAW_TYPE_TFM){
            Config::instance()->getTMFRange(i, &_group.fSampleStart, &_group.fSampleRange, &_group.nPointQty);
            _group.nTimeStart = _process->DistMmToNs(i, _group.fSampleStart);
            _group.nTimeRange = _process->DistMmToNs(i, _group.fSampleRange);
        }
		_LawConfig.eFocalType     = (setup_FOCAL_TYPE)_LawInfo.Focal_point_type  ;
		_LawConfig.nElemQtyFir	  = _LawInfo.Elem_qty   ;
		_LawConfig.nElemQtySec	  = 1 ;
		_LawConfig.nElemStepFir   = _LawInfo.Elem_step  ;
		_LawConfig.nElemStepSec   = 1 ;
		_LawConfig.nFirstElemFir  = _LawInfo.First_tx_elem  ;
		_LawConfig.nFirstElemSec  = 1 ;
		_LawConfig.nLastElemFir   = _LawInfo.Last_tx_elem   ;
		_LawConfig.nLastElemSec   = 1 ;

		_LawConfig.fPositionStart = _LawInfo.Position_start / 1000.0;					// focal depth
		_LawConfig.fPositionStop  = _LawInfo.Position_end   / 1000.0 ;					// not available currently
		_LawConfig.fPositionStep  = _LawInfo.Position_step  / 1000.0;					// not available currently
		//###################################################
		_LawConfig.fOffsetStart   = _LawInfo.Offset_start   / 1000.0;					// focal plane
		_LawConfig.fDepthStart	  = _LawInfo.Depth_start    / 1000.0;					//
		_LawConfig.fOffsetStop	  = _LawInfo.Offset_end     / 1000.0;				//
		_LawConfig.fDepthStop	  = _LawInfo.Depth_end	    / 1000.0;
		// refract angle
		_LawConfig.nAngleStartRefract   = _LawInfo.Angle_min / 10;						  // 0.1 degree
		_LawConfig.nAngleStopRefract	= _LawInfo.Angle_max / 10;					 // focal law  angle setting
		_LawConfig.nAngleStepRefract	= _LawInfo.Angle_step / 10;  		 					 //
        //qDebug()<<"ElemQtyFir"<<_LawConfig.nElemQtyFir<<""<<
		// beam skew angle
		_LawConfig.nAngleStartBeamSkew  = 1;
		_LawConfig.nAngleStopBeamSkew   = 1;
		_LawConfig.nAngleStepBeamSkew   = 1;
		// primary axis steering angle
		_LawConfig.nAngleStartPriSteer  = 1;
		_LawConfig.nAngleStopPriSteer   = 1;
		_LawConfig.nAngleStepPriSteer   = 1;
		// primary axis steering angle
		_LawConfig.nAngleStartSecSteer  = 1;
		_LawConfig.nAngleStopSecSteer   = 1;
		_LawConfig.nAngleStepSecSteer   = 1;

        if(Config::instance()->is_phascan_ii()){
            Config::instance()->getApertureSec( i, &_LawConfig.nElemQtySec);
        }

		if(_group.eGroupMode <= setup_GROUP_MODE_PA)
		{
			PROBE_CONFIG& _probe = _group.probe[0] ;
			PROBE& _Probe = _pGroupInfo->probe ;
			memcpy(_probe.strName , _Probe.Model , 20) ;
			memcpy(_probe.strSerial , _Probe.Serial , 20) ;

			_probe.nElementPri     =  _Probe.Elem_qty;			//主轴阵元数
			_probe.nElementSec     =  1;						//副轴阵元数
			_probe.nLocationPolicy =  0;						// 二维探头，排列顺序

			_probe.fFrequency =  _Probe.Frequency/1000.0;		//MHz
			_probe.fPitchPri  =  _Probe.Pitch    /1000.0;		//主轴间距
			_probe.fPitchSec  =  _Probe.Pitch    /1000.0;
			_probe.fSizePri   =  1 ;
			_probe.fSizeSec   =  1 ;
			_probe.fReferencePoint  = _Probe.Reference_Point / 1000.0 ;
            if(Config::instance()->is_phascan_ii()){
                _probe.nElementSec = _Probe.A4;
                _probe.fPitchSec   = _Probe.A3 /1000.0;
            }
		}
		else
		{
			PROBE_CONFIG& _probe = _group.probe[0] ;
			PROBE& _Probe = _pGroupInfo->probe ;
			memcpy(_probe.strName , _Probe.Model , 20) ;
			memcpy(_probe.strSerial , _Probe.Serial , 20) ;

			_probe.nElementPri     =  1 ;		 //主轴阵元数
			_probe.nElementSec     =  1 ;		 //副轴阵元数
			_probe.nLocationPolicy =  0;		 //二维探头，排列顺序

			_probe.fFrequency =  _Probe.Frequency/1000.0;			 //MHz
			float _fSize	  =  _Probe.Pitch    /1000.0 ;
			_probe.fPitchPri  =  _fSize	 ;			 //主轴间距
			_probe.fPitchSec  =  _fSize	 ;
			_probe.fSizePri   =  _fSize	 ;
			_probe.fSizeSec   =  _fSize	 ;
			_probe.fReferencePoint  = _Probe.Reference_Point / 1000.0 ;
		}


		WEDGE_CONFIG& _wedge = _group.wedge[0] ;
		WEDGE& _Wedge = _pGroupInfo->wedge ;

		memcpy(_wedge.strName , _Wedge.Model , 20) ;
		memcpy(_wedge.strSerial , _Wedge.Serial , 20) ;

		_wedge.eType		 = ( _group.eGroupMode <= setup_GROUP_MODE_PA ) ? setup_WEDGE_TYPE_PA : setup_WEDGE_TYPE_UT ;
		_wedge.eDirection	 = ( setup_WEDGE_ORIENTATION ) _Wedge.Orientation ;

		_wedge.fWedgeAngle   = _Wedge.Angle / 10.0; /* 楔块角 */
		_wedge.fRoofAngle	 = 0 ;  /* 顶角 */

		_wedge.fVelocityLon  = _Wedge.Velocity_PA / 1000.0 ;/*纵波声速*/
		_wedge.fVelocityTra  = _Wedge.Velocity_UT / 1000.0 ;/*横波声速*/

		_wedge.fHeigtFirst   = _Wedge.Height            / 1000.0 ;  /*第一阵元高度*/
		_wedge.fOffsetFir	 = _Wedge.Primary_offset    / 1000.0 ;	/*主轴阵元偏移*/
		_wedge.fOffsetSec	 = _Wedge.Secondary_offset  / 1000.0 ;	/*次轴阵元偏移*/
		_wedge.fPriAxisRef   = 0;   /*主轴楔块参考位置*/
		_wedge.fSecAxisRef   = 0;   /*次轴楔块参考位置*/

		_wedge.fLength	= 50; /*楔块长度*/
		_wedge.fWidth	= 40; /*楔块宽度*/
        _wedge.fHeight	= 30; /*楔块高度*/

		//ut 探头参数
		_wedge.fRefPoint   = _Wedge.Ref_point / 1000.0;
		_wedge.nWedgeDelay = _Wedge.Probe_delay  ;

        _group.part.eGeometry  = (setup_PART_GEOMETRY)_pGroupInfo->part.Geometry;
		_group.part.afSize[0]  = _pGroupInfo->part.Thickness / 1000.0 ;
        _group.part.afSize[1]  = 100;
        _group.part.afSize[2]  = 100;
        _group.part.afSize[3]  = _pGroupInfo->part.Diameter / 1000.0;
        if(common.scanner.eScanEncoderType)
        {
            if(Phascan_Version == 1)
            {
                _group.fScanOffset	  = _pGroupInfo->scan_offset  / 10.0 ;		/*mm*/
                _group.fIndexOffset   = _pGroupInfo->index_offset  / 10.0;			/*mm*/
            }
            else
            {
                _group.fScanOffset	  = _pGroupInfo->scan_offset  / 1000.0 ;		/*mm*/
                _group.fIndexOffset   = _pGroupInfo->index_offset  / 1000.0;			/*mm*/
            }
        }
        else
        {
            if(Phascan_Version == 1)
            {
                _group.fScanOffset	  = 0;
                _group.fIndexOffset   = _pGroupInfo->index_offset  / 10.0;			/*mm*/
            }
            else
            {
                _group.fScanOffset	  = 0;
                _group.fIndexOffset   = _pGroupInfo->index_offset  / 1000.0;			/*mm*/
            }
        }

        _group.eSkew		   = (setup_PROBE_ANGLE)_pGroupInfo->skew_pos;

		QList<MATERIAL*>* _list = m_pConfig->m_listMaterial ;

		if ( _list->size() > _pGroupInfo->part.Material_pos ) {
			MATERIAL* _material = _list->at(_pGroupInfo->part.Material_pos) ;
			memcpy((void*)&_group.part.material , (void*)_material , sizeof(MATERIAL)) ;
		}
        _group.part.CADFresh = false;
        bool hasCADData = false;
        if(Phascan_Version >= 6){
            if(m_pDataFile->GetCADExist(i)){
                QString g_filePath = QCoreApplication::applicationDirPath() + QString("/temp/%1.dxf").arg(i);
                std::string str = g_filePath.toStdString();
                const char* p = str.c_str();
                sprintf(_group.part.strPartFile, "%s", p);
                hasCADData = true;
            }
        }

	//	MATERIAL* _material = _list->at(_pGroupInfo->part.Material_pos) ;
    //	memcpy((void*)&_group.part.material , (void*)_material , sizeof(MATERIAL)) ;

        _group.part.weld.eSymmetry = (setup_WELD_SYMMETRY_TYPE) _pGroupInfo->part.symmetry ;
        _group.part.weld.eType	   = (setup_WELD_TYPE) ((_pGroupInfo->part.Weld == 4)?_pGroupInfo->part.Weld+2:_pGroupInfo->part.Weld);
        if(hasCADData){
            _group.part.weld.eType = setup_WELD_DXF;
        }
		_group.part.weld.weland_height   = _pGroupInfo->part.weland_height / 1000.0 ;
		_group.part.weld.weland_offset   = _pGroupInfo->part.weland_offset / 1000.0 ;
		_group.part.weld.fizone_angle	 = _pGroupInfo->part.fizone_angle  / 1000.0 ;
		_group.part.weld.fizone_height   = _pGroupInfo->part.fizone_height / 1000.0 ;
		_group.part.weld.fizone_radius   = _pGroupInfo->part.fizone_radius / 1000.0 ;
        _group.part.weld.Diameter        = _pGroupInfo->part.Diameter      / 1000.0 ;
        if(2 == _group.part.weld.eType)
        {
           if(((_group.part.afSize[0] - _group.part.weld.weland_height - _group.part.weld.fizone_height) !=
               _group.part.weld.fizone_height)||(_group.part.weld.fizone_radius !=_group.part.weld.fizone_angle))
           {
               _group.part.weld.eType = (setup_WELD_TYPE)4;
               _group.part.weld.fizone_down_height = _group.part.weld.fizone_height;
               _group.part.weld.fizone_height = _group.part.afSize[0] - _group.part.weld.weland_height - _group.part.weld.fizone_height;
               _group.part.weld.fizone_down_angle = _group.part.weld.fizone_radius;
           }
        }

        else if(5 == _group.part.weld.eType)
        {
            _group.part.weld.fizone_down_height = _group.part.weld.weland_height;
            _group.part.weld.weland_height = _group.part.afSize[0] - _group.part.weld.weland_height - _group.part.weld.fizone_height;
            _group.part.weld.fizone_down_angle = _group.part.weld.weland_offset;
            unsigned short b=*(unsigned short *)_pGroupInfo->gate[0].tt;
            _group.part.weld.weland_offset = b/1000;
        }
        else if(6 == _group.part.weld.eType)
        {
            _group.part.weld.fizone_down_height = _group.part.weld.fizone_height - _group.part.weld.weland_height;
            _group.part.weld.fizone_height = _group.part.afSize[0] - _group.part.weld.weland_height - _group.part.weld.fizone_down_height;
            _group.part.weld.fizone_down_angle = _group.part.weld.fizone_radius;
        }

        if( Config::instance()->is_phascan_ii())
        {
            _group.part.weldFormat = PHASCAN_II_FORMAT;
            Config::instance()->getWeldData(i, _group.part.weld_ii);
            Config::instance()->getTOPCWidth(i, _group.TopCInfo.TOPCWidth);
            _group.loadCurveData = Config::instance()->getCurve_RL_EL_SL(i, _group.CoupleGain);
            //qDebug()<<"loadCurveData"<<_group.loadCurveData<<CUR_RES.CurSS[i];
        }
        else
        {
            _group.loadCurveData = false;
            _group.part.weldFormat = PHASCAN_I_FORMAT;
            _group.TopCInfo.TOPCWidth = 10;
            WELD& _weld = _group.part.weld;
            switch ( _group.part.weld.eType) {
            case setup_WELD_I:
                _group.TopCInfo.TOPCWidth = _weld.weland_offset * 2 + 2;
                break;
            case setup_WELD_V:
            case setup_WELD_DV:
                _group.TopCInfo.TOPCWidth = ( _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))
                                              * _weld.fizone_height) *2 + 2;
                break;
            case setup_WELD_U:
                _group.TopCInfo.TOPCWidth = ( _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))*
                                              _weld.fizone_height + _weld.fizone_radius) *2 + 2;
                break;
            case setup_WELD_DIFF_DV:
                _group.TopCInfo.TOPCWidth = ( _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))
                                              * _weld.fizone_height) *2 + 2;
                break;
            case setup_WELD_J:
                _group.TopCInfo.TOPCWidth = ( _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))*
                                              _weld.fizone_height + _weld.fizone_radius) *2 + 2;
                break;
            case setup_WELD_VY:
                _group.TopCInfo.TOPCWidth = ( _weld.weland_offset + tan(DEGREE_TO_ARCH(_weld.fizone_angle))
                                              * _weld.fizone_height) *2 + 2;
                break;
            default:
                break;
            }
        }

        _group.part.weld_border = _process->GetWeldBorder(i);

		DopplerColorIndex _color ;

        _color.LoadPallete(g_strColorAmp);
        memcpy((void*)_group.color.Amp, _color.GetColorIndex() , 256 * 3);

        _color.LoadPallete(g_strColorThickness);
		memcpy((void*)_group.color.Thickness , _color.GetColorIndex() , 256 * 3);

        _color.LoadPallete(g_strColorRectifier);
		memcpy((void*)_group.color.Rf ,_color.GetColorIndex() , 256 * 3);
		//##################################
		UpdateTofdConfig(i) ;
		//##################################

		if(_group.eGroupMode == setup_GROUP_MODE_PA )
		{
            for( int i = 0; i < setup_MAX_MEASURE_QTY; i++){
                _group.aeMeasureType[i]  = AppEvn.anMeasureSelection[0][i];
            }
		}
		else
		{
            for( int i = 0; i < setup_MAX_MEASURE_QTY; i++){
                _group.aeMeasureType[i]  = AppEvn.anMeasureSelection[1][i];
            }
		}
        for(int i = 0; i < setup_MAX_MEASURE_QTY; i++){
            if((_group.aeMeasureType[i] < FEILD_NONE) || (_group.aeMeasureType[i] >= FEILD_VALUE_INDEX_MAX)){
                _group.aeMeasureType[i] = FEILD_NONE;
            }
            _group.measuregateType[i] = _group.aeMeasureType[i];
        }

        _group.measureGateStatus = false;
        _group.measuregateType[0] = FEILD_B100;
        _group.measuregateType[1] = FEILD_DB;
        _group.measuregateType[2] = FEILD_ViB;


		_group.afCursor[setup_CURSOR_TFOD_LW] = _group.fSampleStart + _group.fSampleRange  / 10;
		_group.afCursor[setup_CURSOR_TFOD_BW] = _group.fSampleStart + 9 * _group.fSampleRange / 10;

        LAW_CONFIG _law = _group.law ;
        float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
        float _fAngleStep = _law.nAngleStepRefract/10.0;
        int tmpCScanLinePos =  _fAngleStart + 0*_fAngleStep;
        _group.afCursor[setup_CURSOR_C_ANGLE]  = tmpCScanLinePos ;

//        _group.bShowAScanMeasure = _group.bShowMeasure;
//        _group.bShowBScanMeasure = _group.bShowMeasure;
//        _group.bShowCScanMeasure = _group.bShowMeasure;
//        _group.bShowSScanMeasure = _group.bShowMeasure;
        _group.storeScanLawId.status = false;
        _group.storeScanLawId.scanPos = 0.0;
        _group.storeScanLawId.lawId = 0;

		ParameterProcess* _process = ParameterProcess::Instance() ;
		unsigned char*	  _pData = _process->GetLawDataPointer(i , 0) ;
		if(_pData)
		{
			bool _bRectify = (_process->GetRectifierMode(i) == setup_RECTIFIER_RF ) ;
			if(!_bRectify)
				_group.bShowLwBw = false;
		}

        if( _group.RasterData.rasterData){
            free(_group.RasterData.rasterData);
        }
        memset( &_group.RasterData, 0x00, sizeof(RASTER_DATA));

		_process->TofdCursorCalibration(i);

	}
}

void  DopplerConfigure::InitTOPCMerge()
{
//    if( !Config::instance()->is_phascan_ii()){
//        common.TOPCMergeValid = false;
//        for(int i = 0; i < common.nGroupQty; i++){
//            TOPC_INFO& _TOPCInfo  = group[i].TopCInfo;
//            _TOPCInfo.TOPCMergeStatus = 0;
//        }
//        return;
//    }

    int buff = 0;
    for(int i = 0; i < common.nGroupQty; i++){
        GROUP_CONFIG& _group  = group[i];
        if( _group.eGroupMode == setup_GROUP_MODE_PA){
            common.TOPCMergeGroupId[buff] = i;
            buff++;
        }
    }
    if( buff < 2){
        common.TOPCMergeValid = false;
        for(int i = 0; i < common.nGroupQty; i++){
            TOPC_INFO& _TOPCInfo  = group[i].TopCInfo;
            _TOPCInfo.TOPCMergeStatus = 0;
        }
        return;
    }

    common.TOPCMergeValid = true;
    common.TOPCMergeQty = buff;
    for(int i = 0; i < common.nGroupQty; i++){
        TOPC_INFO& _TOPCInfo  = group[i].TopCInfo;
        _TOPCInfo.TOPCMergeStatus = 0;
        for(int j = 0; j < buff; j++){
            if(common.TOPCMergeGroupId[j] != i){
                _TOPCInfo.TOPCMergeRefer = common.TOPCMergeGroupId[j];
                break;
            }
        }
    }

}

void  DopplerConfigure::InitTOPCInfo()
{
    //if( !Config::instance()->is_phascan_ii() || common.scanner.eScanType != setup_SCAN_TYPE_ONE_LINE){
    if( common.scanner.eScanType != setup_SCAN_TYPE_ONE_LINE){
        for( int i = 0; i < common.nGroupQty; i++){
            TOPC_INFO& _TOPCInfo  = group[i].TopCInfo;
            _TOPCInfo.TOPCValid  = false;
            _TOPCInfo.TOPCStatus = false;
        }
        return;
    }

    ParameterProcess* _process = ParameterProcess::Instance();
    for( int i = 0; i < common.nGroupQty; i++){
        GROUP_CONFIG& _group  = group[i];
        TOPC_INFO& _TOPCInfo  = group[i].TopCInfo;

        if( _group.eGroupMode != setup_GROUP_MODE_PA){
            _TOPCInfo.TOPCValid  = false;
            _TOPCInfo.TOPCStatus = false;
            continue;
        }
        _TOPCInfo.TOPCValid  = true;
        _TOPCInfo.TOPCStatus = false;
        float _nStartX, _nStopX, _nStartY, _nStopY;
        _process->GetSImageHorizentalRange( i, &_nStartX, &_nStopX);
        _process->GetSImageVerticalRange( i, &_nStartY, &_nStopY);
        float realWidth = fabs( _nStopX - _nStartX);
        float realHeigh = fabs( _nStopY - _nStartY);
        LAW_CONFIG _law = _group.law;
        int _nPointQty = _group.nPointQty;
        float _nSampleRange = _group.fSampleRange;
        int _width = realWidth / _nSampleRange * _nPointQty * 1.5;
        int _height = realHeigh / _nSampleRange * _nPointQty * 1.5;
        int dataSize = _width * _height;
        //qDebug()<<"topcDataSize"<<i<<_width<<_height;

        if( _TOPCInfo.pDataIndex){
            free( _TOPCInfo.pDataIndex);
        }
        _TOPCInfo.pDataIndex = (int*)malloc( dataSize * sizeof(int));
        memset((void*)(_TOPCInfo.pDataIndex), 0, dataSize * sizeof(int));
        _TOPCInfo.startX = _nStartX;
        _TOPCInfo.stopX  = _nStopX;
        _TOPCInfo.startY = _nStartY;
        _TOPCInfo.stopY  = _nStopY;
        _TOPCInfo.pixelWidth = _width;
        _TOPCInfo.pixelHeigh = _height;
        //qDebug()<<"topcwidtha"<<i<<_width;
        int beamLength;
//        if(_group.law.eLawType == setup_LAW_TYPE_TFM){
//            beamLength = _nPointQty;
//        }else{
            beamLength = setup_DATA_PENDIX_LENGTH + _nPointQty;
        //}

        float *_pExitPoint = _group.afBeamPos;
        float _nAngleStart = DEGREE_TO_ARCH( _law.nAngleStartRefract / 10.0);

        if( _group.law.eLawType == setup_LAW_TYPE_AZIMUTHAL){            
            float _nAngleStop  = DEGREE_TO_ARCH( _law.nAngleStopRefract / 10.0);
            float _nAngleStep  = DEGREE_TO_ARCH( _law.nAngleStepRefract / 10.0);
            int	  _nBeamQty    = (int)(( _nAngleStop - _nAngleStart) / _nAngleStep + 1.1);
            float _nSampleStart= _group.fSampleStart;
            float _nSampleStop = _nSampleStart + _nSampleRange;
            float _nStepX, _nStepY;
            _nStepX  = (_nStopX - _nStartX) / (_width - 1);
            _nStepY  = (_nStopY - _nStartY) / (_height - 1);

            float _nTopLocation[256];
            for(int i = 0 ; i < _nBeamQty - 1; i++){
                _nTopLocation[i] = (_pExitPoint[i] + _pExitPoint[i+1]) / 2;
            }

            float _nAngles[256];
            for(int i = 0 ; i < _nBeamQty ; i++){
                _nAngles[i] = _nAngleStart + i * _nAngleStep;
            }

            float _nPosJunction[256];
            int i, j, k, t, _index;
            float _fX, _fY, _nTmp;
            for( j = 0; j < _height; j++){
                _fY = _nStartY + j * _nStepY;
                for( k = 0; k < _nBeamQty; k++){
                    _nPosJunction[k] = _pExitPoint[k] + tan(_nAngles[k]) * _fY;
                }
                t = 0;
                for( i = 0; i < _width; i++){
                    _fX = _nStartX + _nStepX * i;
                    for( ; t < _nBeamQty - 1; t++){
                        if(_fX > _nPosJunction[_nBeamQty - 1] || _fX < _nPosJunction[0]){
                            break;
                        }
                        if(_fX >= _nPosJunction[t] && _fX <= _nPosJunction[t+1] ){
                            _index = i + j * _width;
                            _nTmp = _fX - _nTopLocation[t];
                            _nTmp = sqrt(_fY * _fY + _nTmp * _nTmp);

                            if(_nTmp > _nSampleStop || _nTmp < _nSampleStart){
                                break;
                            }
                            _TOPCInfo.pDataIndex[_index] =
                            t * beamLength + (_nPointQty * (_nTmp - _nSampleStart) / _nSampleRange);
                            break;
                        }
                    }
                }
            }
        }else{
            int _nStartElement = _law.nFirstElemFir;
            int  _nStopElement = _law.nLastElemFir;
            int  _nStepElement = _law.nElemStepFir;
            int   _nElementQty = _law.nElemQtyFir;
            float _fAngle = _nAngleStart;
            float _fRange = _nSampleRange;

            int  _nBeamMaxId = (_nStopElement  - _nStartElement - _nElementQty + 1 ) / _nStepElement;
            float _fStartPos = _pExitPoint[0];
            float _fStopPos  = _pExitPoint[_nBeamMaxId];
            float _angle = fabs(_fAngle);

            float _real_height = _fRange * cos(_angle);
            float _real_width  = fabs(_fStopPos - _fStartPos) + _fRange * sin(_angle);
            float _xScale = _width / _real_width;
            float _xVacc  = tan(_angle) * _real_height * _xScale;
            float _fScale = _xVacc / _height;
            float _beam_width = _width - _xVacc;
            bool _bWedgeRev = (_fStopPos - _fStartPos) > 0 ? false : true;
            float tmpX, xxx;
            float tmpDrawRate;
            float tmpDataNo;
            int i, j, index;
            for( i = 0; i < _height; i++){
                tmpX = i * _fScale;
                tmpDataNo = ((double)i) / _height;
                for( j = 0 ; j < _width ; j++ ){
                    index  = j + i * _width;
                    if( _fAngle >=0 ){
                        xxx = j - tmpX;
                    }else{
                        xxx = j - _xVacc + tmpX;
                    }
                    if( xxx < 0 || xxx >= _beam_width){
                        continue;
                    }
                    tmpDrawRate = ( xxx / _beam_width) * _nBeamMaxId;
                    int buffBeamId;
                    if(_bWedgeRev){
                        buffBeamId = _nBeamMaxId - (U8)tmpDrawRate;
                    }else{
                        buffBeamId = (U8)tmpDrawRate;
                    }
                    _TOPCInfo.pDataIndex[index] = buffBeamId * beamLength + _nPointQty * tmpDataNo;
                }
            }
        }
    }
}

void  DopplerConfigure::UpdateTofdConfig(int nGroupId_)
{
	GROUP_CONFIG& _group = group[nGroupId_] ;
	if(_group.eGroupMode == setup_GROUP_MODE_PA )  return ;
	if(_group.eTxRxMode  != setup_TX_RX_MODE_TOFD )  return  ;

	TOFD_PARA& _tofd = TOFD[nGroupId_]  ;
	_tofd.fLayerStart	= 0;
	_tofd.fLayerEnd		= _group.part.afSize[0];
	_tofd.fArcH			= 0;
	_tofd.fPCS			= _group.afBeamPos[254] ;
	_tofd.fZeroOff		= 0;
	_tofd.fRefPoint		=  (_tofd.fPCS - _group.afBeamPos[255]) / 2;
	_tofd.fWedgeSep		=  _group.afBeamPos[255] ;

    if( Config::instance()->is_phascan_ii()){
        Config::instance()->getTofdData( nGroupId_, &_tofd.fPCS, &_tofd.fRefPoint);
        _tofd.fWedgeSep = _tofd.fPCS - 2 *_tofd.fRefPoint;
    }else{
        _tofd.fPCS			= _group.afBeamPos[254];
        _tofd.fRefPoint		=  (_tofd.fPCS - _group.afBeamPos[255]) / 2;
        _tofd.fWedgeSep		=  _group.afBeamPos[255];
    }

	memset(_tofd.proInfo, 0x00,  sizeof(_tofd.proInfo));
	_tofd.eProingST = TOFD_PRO_NONE;
	_tofd.iProCnt   = 0;
}

TOFD_PARA* DopplerConfigure::GetTofdConfig(int nGroupId_)
{
	return &TOFD[nGroupId_]  ;
}

DopplerHtmlReport* DopplerConfigure::GetReportOpp()
{
	return m_pReport ;
}

void DopplerConfigure::OpenDefectFile(QString& path_)
{
    loadDefectVersion = 2;
    ReleaseAllDefect();
	QString _strName = path_ + QString(tr("/defect"));
	QFile file(_strName);
    if(!file.open (QIODevice::ReadOnly)){
        return;
    }
	QDataStream reader(&file);

	int _sign;
	reader.readRawData((char*)&_sign , sizeof(int)) ;

    if(_sign == 0x15263748)	{
        loadDefectVersion = 1;
		int _nGroupQty;
		reader.readRawData((char*)&_nGroupQty , sizeof(int));

		for(int iGroup = 0; iGroup < _nGroupQty; iGroup++) {
			int _iDefectN;
			reader.readRawData((char*)&_iDefectN , sizeof(int));

			for(int i = 0; i < _iDefectN; i++) {
                DEFECT_INFO_V1 _dfInfo;
                reader.readRawData((char*)&_dfInfo , sizeof(DEFECT_INFO_V1));
				AddDefectInfo(iGroup, _dfInfo);
			}
		}
    }else if(_sign == 0x15263749){
        loadDefectVersion = 2;
        int _nGroupQty;
        reader.readRawData((char*)&_nGroupQty , sizeof(int));

        for(int iGroup = 0; iGroup < _nGroupQty; iGroup++) {
            int _iDefectN;
            reader.readRawData((char*)&_iDefectN , sizeof(int));

            for(int i = 0; i < _iDefectN; i++) {
                DEFECT_INFO _dfInfo;
                reader.readRawData((char*)&_dfInfo , sizeof(DEFECT_INFO));
                AddDefectInfo(iGroup, _dfInfo);
            }
        }
    }else{
        loadDefectVersion = 2;
    }
	file.close();
}

void DopplerConfigure::SaveDefectFile(QString& path_)
{
	QDir *_tmp = new QDir;
	if(!_tmp->exists(path_)) {
		_tmp->mkdir(path_);
	}

	QString _strName = path_ + QString(tr("/defect"));
	QFile file(_strName);
	file.open (QIODevice::WriteOnly);
	QDataStream write(&file);
    if(loadDefectVersion == 1){
        int _sign = 0x15263748;
        write.writeRawData((char*)&_sign , sizeof(int));

        int _nGroupQty = common.nGroupQty;
        write.writeRawData((char*)&_nGroupQty , sizeof(int));

        for(int iGroup = 0; iGroup < _nGroupQty; iGroup++) {
            int _iDefectN = GetDefectCnt(iGroup);
            write.writeRawData((char*)&_iDefectN , sizeof(int));

            for(int i = 0; i < _iDefectN; i++) {
                DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroup, i);
                write.writeRawData((char*)_pDfInfo, sizeof(DEFECT_INFO_V1));
            }
        }
    }else{
        int _sign = 0x15263749;
        write.writeRawData((char*)&_sign , sizeof(int));

        int _nGroupQty = common.nGroupQty;
        write.writeRawData((char*)&_nGroupQty , sizeof(int));

        for(int iGroup = 0; iGroup < _nGroupQty; iGroup++) {
            int _iDefectN = GetDefectCnt(iGroup);
            write.writeRawData((char*)&_iDefectN , sizeof(int));

            for(int i = 0; i < _iDefectN; i++) {
                DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroup, i);
                write.writeRawData((char*)_pDfInfo, sizeof(DEFECT_INFO));
            }
        }
    }
	file.close();
}

#include <QDir.h>
void DopplerConfigure::FilePathPro(QString& path_)
{
	m_szFileInUse = path_ ;
	QFileInfo _fi = QFileInfo(m_szFileInUse);
	QString _name = _fi.fileName();
	QString _path = _fi.absolutePath() + "/";
	QString _strDefectPath = _path + tr("DPL DEFECTS/");

	strcpy(AppEvn.strDataFilePath, qPrintable(_path));

	int _index;
	_index = _name.lastIndexOf(".");
	_name.truncate(_index);

	QDir *_tmp = new QDir;
	if(!_tmp->exists(_strDefectPath))
	{
		_tmp->mkdir(_strDefectPath);
	}

	m_szDefectPathName = _strDefectPath + _name;
	OpenDefectFile(m_szDefectPathName);
}

int DopplerConfigure::DefectSign(int iGroupId_, DEFECT_SIGN_TYPE signType_)
{
	GROUP_CONFIG& _group = group[iGroupId_] ;

	float _fScanOff = _group.fScanOffset;

	float _fRef;
	float _fMes;

	int _ret = -1;
	switch(signType_)
	{
	case DEFECT_SIGN_LENGTH:
		if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD) {
			_fRef = _group.afCursor[setup_CURSOR_S_REF];
			_fMes = _group.afCursor[setup_CURSOR_S_MES];
			m_dfParam[iGroupId_].dfInfo.fSStart = _fRef < _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fSStop  = _fRef > _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fSStart -= _fScanOff;
			m_dfParam[iGroupId_].dfInfo.fSStop  -= _fScanOff;
			if(m_dfParam[iGroupId_].dfInfo.fUStart < -10000) {
				_fMes = _group.afCursor[setup_CURSOR_U_MES];
				m_dfParam[iGroupId_].dfInfo.fUStart = _fMes;
				m_dfParam[iGroupId_].dfInfo.fUStop  = _fMes;
			}
			m_dfParam[iGroupId_].dfInfo.bValid = true;
			_ret = 0;
		}
		break;
	case DEFECT_SIGN_HEIGHT:
		if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD) {
			_fRef = _group.afCursor[setup_CURSOR_U_REF];
			_fMes = _group.afCursor[setup_CURSOR_U_MES];
			m_dfParam[iGroupId_].dfInfo.fUStart = _fRef < _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fUStop  = _fRef > _fMes ? _fRef : _fMes;
			if(m_dfParam[iGroupId_].dfInfo.fSStart < -10000) {
				_fMes = _group.afCursor[setup_CURSOR_S_MES];
				m_dfParam[iGroupId_].dfInfo.fSStart = _fMes;
				m_dfParam[iGroupId_].dfInfo.fSStop  = _fMes;
			}
			m_dfParam[iGroupId_].dfInfo.bValid = true;
			_ret = 1;
		}
		break;
	case DEFECT_SIGN_DEPTH:
		if(_group.eTxRxMode == setup_TX_RX_MODE_TOFD) {
			_fMes = _group.afCursor[setup_CURSOR_U_MES];
			m_dfParam[iGroupId_].dfInfo.fUDepth = _fMes;
			m_dfParam[iGroupId_].dfInfo.bValid = true;
			_ret = 2;
		}
		break;
	case DEFECT_SIGN_SAVE:
		if(_group.eTxRxMode != setup_TX_RX_MODE_TOFD )
		{
			_fRef = _group.afCursor[setup_CURSOR_S_REF];
			_fMes = _group.afCursor[setup_CURSOR_S_MES];
			m_dfParam[iGroupId_].dfInfo.fSStart = _fRef < _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fSStop  = _fRef > _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fSStart -= _fScanOff;
			m_dfParam[iGroupId_].dfInfo.fSStop  -= _fScanOff;

			_fRef = _group.afCursor[setup_CURSOR_U_REF];
			_fMes = _group.afCursor[setup_CURSOR_U_MES];
			m_dfParam[iGroupId_].dfInfo.fUStart = _fRef < _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fUStop  = _fRef > _fMes ? _fRef : _fMes;

			_fRef = _group.afCursor[setup_CURSOR_I_REF];
			_fMes = _group.afCursor[setup_CURSOR_I_MES];
			m_dfParam[iGroupId_].dfInfo.fIStart = _fRef < _fMes ? _fRef : _fMes;
			m_dfParam[iGroupId_].dfInfo.fIStop  = _fRef > _fMes ? _fRef : _fMes;

            _fRef = _group.afCursor[setup_CURSOR_VPA_REF];
            _fMes = _group.afCursor[setup_CURSOR_VPA_MES];
            m_dfParam[iGroupId_].dfInfo.fVPAStart = _fRef < _fMes ? _fRef : _fMes;
            m_dfParam[iGroupId_].dfInfo.fVPAStop  = _fRef > _fMes ? _fRef : _fMes;

			m_dfParam[iGroupId_].dfInfo.fUDepth = m_dfParam[iGroupId_].dfInfo.fUStart;
			m_dfParam[iGroupId_].dfInfo.bValid = true;

            m_dfParam[iGroupId_].dfInfo.dGroupId = iGroupId_ + 1;

            if(loadDefectVersion == 1){
                m_dfParam[iGroupId_].dfInfo.dVersion = 1;
            }else{
                m_dfParam[iGroupId_].dfInfo.dVersion = 2;
            }
		} else {
			if(m_dfParam[iGroupId_].dfInfo.fSStart < -10000)
			break;
		}
		_ret = AddDefectInfo(iGroupId_, m_dfParam[iGroupId_].dfInfo);
		ClearDefectInfo(iGroupId_);

		if(_ret >= 0) {

			int _index = GetDefectCnt(iGroupId_)-1;
			DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, _index);
			//---------------------------------------
            int _nLawNo;
            if(loadDefectVersion == 1){
                _nLawNo = _group.afCursor[setup_CURSOR_LAW];
                _pDfInfo->nLawNo = _nLawNo;
            }else{
                _pDfInfo->nLawNo       = _group.storeScanLawId.lawId;
                _pDfInfo->dZA          = _group.storeScanLawId.ZA;
                _pDfInfo->dScanPos     = _group.storeScanLawId.scanPos;
                _pDfInfo->dDepth       = _group.storeScanLawId.depth;
                _pDfInfo->dScanOffset  = _group.fScanOffset;
                _pDfInfo->dIndexOffset = _group.fIndexOffset;
                _nLawNo = _group.storeScanLawId.lawId;
            }
            ReorderDefect();
			//---------------------------------------
            int* _pMeasure;
            if(group[iGroupId_].measureGateStatus){
                _pMeasure = group[iGroupId_].measuregateType;
            }else{
                _pMeasure = group[iGroupId_].aeMeasureType;
            }
            //int* _pMeasure = group[iGroupId_].aeMeasureType;
			int _nQty = 0 ;
            for(int i = 0 ; i < setup_MAX_MEASURE_QTY; i++) {
				strcpy(_pDfInfo->m_strMeasure[i], "-");
                strcpy(_pDfInfo->m_strSzField[i],"-");
                strcpy(_pDfInfo->m_strSzFieldUnit[i],"-");
                strcpy(_pDfInfo->SL,"NA");
                QString SLstr = CalcMeasurement::GetMeasureValueSimpleString(iGroupId_ , _nLawNo, FEILD_SL );
                strcpy(_pDfInfo->SL,(char*)(qPrintable(SLstr)));
                strcpy(_pDfInfo->Index_pos,"NA");
                QString Pa_Value = CalcMeasurement::GetMeasureValueSimpleString(iGroupId_ , _nLawNo, FEILD_PA );
                if(QString::compare(Pa_Value,"NA"))
                {
                    double Index_pos = Pa_Value.toDouble()-fabs(group[iGroupId_].fIndexOffset);
                    Pa_Value = QString::number(Index_pos,10,2);
                }
                strcpy(_pDfInfo->Index_pos,(char*)(qPrintable(Pa_Value)));
				if(_pMeasure[i]) {
                    QString _str = CalcMeasurement::GetMeasureValueSimpleString(iGroupId_ , _nLawNo, (FEILD_VALUE_INDEX)_pMeasure[i]);
					strcpy(_pDfInfo->m_strMeasure[_nQty], (char*)(qPrintable(_str)));
                    _str = CalcMeasurement::GetMeasureString(iGroupId_ , (FEILD_VALUE_INDEX)_pMeasure[i]);
                    strcpy(_pDfInfo->m_strSzField[_nQty], (char*)(qPrintable(_str)));
                    _str = CalcMeasurement::GetMeasureUnit((FEILD_VALUE_INDEX)_pMeasure[i]) ;
                    strcpy(_pDfInfo->m_strSzFieldUnit[_nQty], (char*)(qPrintable(_str)));
					_nQty++  ;
				}
			}
			//---------------------------------------
			m_dfParam[iGroupId_].index = _index;

			QDateTime time = QDateTime::currentDateTime();
			memset(_pDfInfo->srtInfo, 0x00, 256);

			QString str1, str2;
			str1.sprintf("GR%d ", iGroupId_+1);
			str2 = time.toString("yyyy-MM-dd hh mm ss");

			QString str3 = str1 + str2;
			strcpy(_pDfInfo->srtImageName, (char*)(qPrintable(str3)));
			//---------------------------------------
			SaveDefectFile(m_szDefectPathName);
			_ret = 3;
		}
		break;
	default:
		_ret = -1;
	}
	return _ret;
}

int DopplerConfigure::ClearDefectInfo(int iGroupId_)
{
	memset(&m_dfParam[iGroupId_].dfInfo, 0x00, sizeof(DEFECT_INFO));
	m_dfParam[iGroupId_].dfInfo.fIStart = -20000;
	m_dfParam[iGroupId_].dfInfo.fUStart = -20000;
	m_dfParam[iGroupId_].dfInfo.fSStart = -20000;
	m_dfParam[iGroupId_].dfInfo.fUDepth = -20000;
	return 0;
}

int DopplerConfigure::AddDefectInfo(int iGroupId_, DEFECT_INFO &dfInfo_)
{
	if(GetDefectCnt(iGroupId_) >= DEFECT_SIGN_MAX)
	return -1;

	DEFECT_INFO* _pDfInfo = new DEFECT_INFO;

	memcpy(_pDfInfo, &dfInfo_, sizeof(DEFECT_INFO));

	_pDfInfo->pPrev = NULL;
	_pDfInfo->pNext = NULL;

	if(m_dfParam[iGroupId_].pDFHead == NULL) {
		m_dfParam[iGroupId_].pDFHead = _pDfInfo;
	}

	if(m_dfParam[iGroupId_].pDFEnd) {
		_pDfInfo->pPrev = m_dfParam[iGroupId_].pDFEnd;
		m_dfParam[iGroupId_].pDFEnd->pNext = _pDfInfo;
	}

	m_dfParam[iGroupId_].pDFEnd = _pDfInfo;
	return 0;
}

int DopplerConfigure::AddDefectInfo(int iGroupId_, DEFECT_INFO_V1 &dfInfo_)
{
    if(GetDefectCnt(iGroupId_) >= DEFECT_SIGN_MAX)
    return -1;

    DEFECT_INFO* _pDfInfo = new DEFECT_INFO;
    memcpy(_pDfInfo, &dfInfo_, sizeof(DEFECT_INFO));

    _pDfInfo->pPrev = NULL;
    _pDfInfo->pNext = NULL;
    _pDfInfo->dVersion = 1;

    if(m_dfParam[iGroupId_].pDFHead == NULL) {
        m_dfParam[iGroupId_].pDFHead = _pDfInfo;
    }

    if(m_dfParam[iGroupId_].pDFEnd) {
        _pDfInfo->pPrev = m_dfParam[iGroupId_].pDFEnd;
        m_dfParam[iGroupId_].pDFEnd->pNext = _pDfInfo;
    }

    m_dfParam[iGroupId_].pDFEnd = _pDfInfo;
    return 0;
}

int DopplerConfigure::DeleteDefect(int iGroupId_, int index_)
{
	int _iMax = GetDefectCnt(iGroupId_);
	if(_iMax == 0)
		return 0;
	//------------------------------------------------------------
	DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);
	QString _strImageName = m_szDefectPathName + QString(tr("/")) + QString(tr(_pDfInfo->srtImageName)) + QString(tr(".png"));
	QFile::remove(_strImageName);
	//------------------------------------------------------------
	_pDfInfo = m_dfParam[iGroupId_].pDFHead;

	for(int i = 0; i < _iMax; i++)
	{
		if(i == index_)
		{
			DEFECT_INFO* _pDf1 = _pDfInfo->pPrev;
			if(_pDf1)
			_pDf1->pNext = _pDfInfo->pNext;

			DEFECT_INFO* _pDf2 = _pDfInfo->pNext;
			if(_pDf2)
			_pDf2->pPrev = _pDfInfo->pPrev;

			if(i == 0)
			m_dfParam[iGroupId_].pDFHead = _pDf2;

			if(i == _iMax - 1)
			m_dfParam[iGroupId_].pDFEnd = _pDf1;

			delete _pDfInfo ;
		}
		_pDfInfo = _pDfInfo->pNext;
	}

	_iMax = GetDefectCnt(iGroupId_);
	if(m_dfParam[iGroupId_].index >= _iMax)
	{
		m_dfParam[iGroupId_].index = _iMax - 1;
	}
    ReorderDefect();
	SaveDefectFile(m_szDefectPathName);
	return 0;
}

int DopplerConfigure::GetDefectCnt(int iGroupId_)
{
	DEFECT_INFO* _pDfInfo = m_dfParam[iGroupId_].pDFHead;
	int _iCnt = 0;

	while(_pDfInfo != NULL)
	{
		_pDfInfo = _pDfInfo->pNext;
		_iCnt ++;
	}

	return _iCnt;
}

void DopplerConfigure::ReleaseAllDefect()
{
	for(int iGroup = 0; iGroup < common.nGroupQty; iGroup++)
	{
	ReleaseDefect(iGroup);
	}
}

void DopplerConfigure::ReleaseDefect(int iGroupId_)
{
	DEFECT_INFO* _pDfInfo = m_dfParam[iGroupId_].pDFEnd;

	DEFECT_INFO* _pPrev;

	while(_pDfInfo)
	{
		_pPrev = _pDfInfo->pPrev;
		if(_pDfInfo)
		{
			delete _pDfInfo;
			_pDfInfo = _pPrev;
		}
	}

	m_dfParam[iGroupId_].pDFHead = NULL;
	m_dfParam[iGroupId_].pDFEnd = NULL;
}

void DopplerConfigure::ReorderDefect()
{
    //版本1按照组数和存贮顺序排序，每组都从1开始
    if(loadDefectVersion == 1){
        for(int i = 0; i < common.nGroupQty; i++){
            int index = 1;
            DEFECT_INFO* _pDfInfo = m_dfParam[i].pDFHead;
            while(_pDfInfo != NULL){
                _pDfInfo->dIndex = index;
                _pDfInfo = _pDfInfo->pNext;
                index++;
            }
        }
    }else{//版本2按照所有组的扫查起始的大小来排序
        int defectNum = 0;
        for(int i = 0; i < common.nGroupQty; i++){
            defectNum += GetDefectCnt(i);
        }
        if(defectNum == 0){
            return;
        }
        DEFECT_INFO **sortBuff = (DEFECT_INFO **)malloc(sizeof(DEFECT_INFO *)* defectNum);
        int index_ = 0;
        for(int i = 0; i < common.nGroupQty; i++){
            DEFECT_INFO* _pDfInfo = m_dfParam[i].pDFHead;
            while (_pDfInfo != NULL) {
                sortBuff[index_] = _pDfInfo;
                _pDfInfo = _pDfInfo->pNext;
                index_++;
            }
        }
        DEFECT_INFO *temp;
        for(int i = 0; i < defectNum - 1; i++){
            for(int j = 0; j < defectNum - 1 - i; j++){
                if(sortBuff[j]->dScanPos > sortBuff[j+1]->dScanPos){
                    temp = sortBuff[j];
                    sortBuff[j] = sortBuff[j+1];
                    sortBuff[j+1] = temp;
                }
            }
        }
        for(int i = 0; i < defectNum; i++){
            sortBuff[i]->dIndex = i + 1;
        }
        free(sortBuff);
    }
}

float DopplerConfigure::DefectLengthValue(int iGroupId_, float* pStart_, int index_)
{
	return DefectLengthPos(iGroupId_, pStart_, index_);
}

float DopplerConfigure::DefectLengthPos(int iGroupId_, float* pStart_, int index_)
{
	DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);
	GROUP_CONFIG& _group  = group[iGroupId_] ;
	float       _fScanOff = _group.fScanOffset;


	float _fLength = -1;
	if(_pDfInfo->bValid) {
		if(_pDfInfo->fSStart > -10000) {
			_fLength = _pDfInfo->fSStop - _pDfInfo->fSStart;
            *pStart_ = _pDfInfo->fSStart;
		}
	}
	*pStart_ += _fScanOff;
	return _fLength;
 }

float DopplerConfigure::DefectVPAPos(int iGroupId_, float* pStart_, int index_)
{
    DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);
    //GROUP_CONFIG& _group  = group[iGroupId_] ;
    //float       _fScanOff = _group.fScanOffset;


    float _fLength = -1;
    if(_pDfInfo->bValid) {
        if(_pDfInfo->fVPAStart > -10000) {
            _fLength = _pDfInfo->fVPAStop - _pDfInfo->fVPAStart;
            *pStart_ = _pDfInfo->fVPAStart;
        }
    }
    return _fLength;
 }

float DopplerConfigure::DefectHeightValue(int iGroupId_, float* pStart_, int index_)
{
	GROUP_CONFIG& _group = group[iGroupId_];
	float _fHeight = DefectHeightPos(iGroupId_, pStart_, index_);
	if(_fHeight >= 0 && _group.eTxRxMode == setup_TX_RX_MODE_TOFD) {
		ParameterProcess* _process = ParameterProcess::Instance();
		float _fStart = _process->GetTofdDepth(iGroupId_, *pStart_);
		float  _fStop = _process->GetTofdDepth(iGroupId_, *pStart_ + _fHeight);

		*pStart_ = _fStart;
		_fHeight = fabs(_fStop - _fStart);
	} else {
		float _fThickness = _group.part.afSize[0];
		if(*pStart_ > _fThickness || (*pStart_+_fHeight) > _fThickness) {
			float _fD1 = GetDepth(*pStart_, _group.part.afSize[0]);
			float _fD2 = GetDepth(*pStart_ + _fHeight, _group.part.afSize[0]);

			*pStart_ = GYMIN(_fD1, _fD2);
			float _fDelta = _fThickness - *pStart_;
			_fHeight = GYMIN(_fHeight, _fDelta);
		}
	}
	return _fHeight;
}

float DopplerConfigure::DefectHeightPos(int iGroupId_, float* pStart_, int index_)
{
	DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);

	float _fHeight = -1;
	if(_pDfInfo->bValid) {
		if(_pDfInfo->fUStart > -10000) {
			_fHeight = _pDfInfo->fUStop - _pDfInfo->fUStart;
			*pStart_ =_pDfInfo->fUStart;
		}
	}
	return _fHeight;
}

float DopplerConfigure::DefectWidthValue(int iGroupId_, float* pStart_, int index_)
{
	return DefectWidthPos(iGroupId_, pStart_, index_);
}

float DopplerConfigure::DefectWidthPos(int iGroupId_, float* pStart_, int index_)
{
	DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);

	float _fWidth = -1;
	if(_pDfInfo->bValid) {
		if(_pDfInfo->fIStart > -10000) {
			_fWidth  = _pDfInfo->fIStop - _pDfInfo->fIStart;
			*pStart_ =_pDfInfo->fIStart;
		}
	}
	return _fWidth;
}


float DopplerConfigure::DefectDepthValue(int iGroupId_, int index_)
{
	GROUP_CONFIG& _group = group[iGroupId_];
	float _fDepth = DefectDepthPos(iGroupId_, index_);
	if(_fDepth >= 0 && _group.eTxRxMode == setup_TX_RX_MODE_TOFD)
	{
	ParameterProcess* _process = ParameterProcess::Instance();
	_fDepth = _process->GetTofdDepth(iGroupId_, _fDepth);
	}
	return _fDepth;
}

float DopplerConfigure::DefectDepthPos(int iGroupId_, int index_)
{
    Q_UNUSED(index_);
	DEFECT_INFO* _pDfInfo = &m_dfParam[iGroupId_].dfInfo;

	float _fDepth = -1;
	if(_pDfInfo->bValid) {
		if(_pDfInfo->fUDepth > -10000) {
			_fDepth = _pDfInfo->fUDepth;
		}
	}
	return _fDepth;
}

DEFECT_INFO* DopplerConfigure::GetDefectPointer(int iGroupId_, int index_)
{
    DEFECT_INFO* _pDfInfo = m_dfParam[iGroupId_].pDFHead;

	if(index_ < 0) {
		_pDfInfo = &m_dfParam[iGroupId_].dfInfo;
	} else {
		for(int i = 1; i <= index_; i++) {
			if(_pDfInfo->pNext == NULL)
			break;
			_pDfInfo = _pDfInfo->pNext;
		}
	}
	return _pDfInfo;
}

DEFECT_INFO* DopplerConfigure::SetDefectInfo(int iGroupId_, int index_, char* strInfo_,char* strInfo2)
{
    DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);
    strcpy(_pDfInfo->srtInfo, strInfo_);
    strcpy(_pDfInfo->srtInfo2,strInfo2);
	SaveDefectFile(m_szDefectPathName);
	return _pDfInfo;
}

char* DopplerConfigure::GetDefectInfo(int iGroupId_, int index_)
{
	DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);
	return _pDfInfo->srtInfo;
}

int DopplerConfigure::GetDefectIndex(int iGroupId_, int index_)
{
    DEFECT_INFO* _pDfInfo = GetDefectPointer(iGroupId_, index_);
    return _pDfInfo->dIndex;
}

void DopplerConfigure::SetLastDate()
{
    QDate _date  = QDate::currentDate();
	AppEvn.year  = _date.year();
	AppEvn.month = _date.month();
	AppEvn.day   = _date.day();
}

QDate DopplerConfigure::GetLastDate()
{
	int _year  = AppEvn.year;
	int _month = AppEvn.month;
	int _day   = AppEvn.day;

	QDate _date(_year, _month, _day);
	return _date;
}
