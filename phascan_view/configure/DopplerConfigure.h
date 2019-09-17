/***************************
  Name:  DopplerConfigure
  Date : 2013-08-26
  Description:   用于操作配置文件，负责配置文件的加载
				 初始化，和保存
************************************/


#ifndef DOPPLERCONFIGURE_H
#define DOPPLERCONFIGURE_H

#include "const.h"
#include "Struct.h"
#include "DopplerDataFileOperateor.h"
#include "FileStruct.h"
#include "Instrument.h"
//#include <report/DopplerHtmlReport.h>

#include <QObject>
#include <QList>
#include <QVector>

class DopplerHtmlReport ;
enum PALETTE_NAME
{
    PALETTE_AMP = 0 ,
	PALETTE_THICKNESS ,
	PALETTE_RECTIFY ,
	PALETTE_NAME_MAX
};

struct FOCALLAW_RESULT
{
	unsigned int anBeamDelay[setup_MAX_GROUP_LAW_QTY] ;
	float afPos[setup_MAX_GROUP_LAW_QTY];
	int anElementDelay[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT_ACTIVE];


	float   afBeamExitPointX[setup_MAX_GROUP_LAW_QTY];  /*入射点的坐标*/
	float   afBeamExitPointY[setup_MAX_GROUP_LAW_QTY];
	float   afBeamExitPointZ[setup_MAX_GROUP_LAW_QTY];

	//发射探头
	float afFocusPosX[setup_MAX_GROUP_LAW_QTY];/*聚焦点坐标*/
	float afFocusPosY[setup_MAX_GROUP_LAW_QTY];/*聚焦点坐标*/
	float afFocusPosZ[setup_MAX_GROUP_LAW_QTY];/*聚焦点坐标*/
	float afElementPosX[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT];/*阵元坐标*/
	float afElementPosY[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT];/*阵元坐标*/
	float afElementPosZ[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT];/*阵元坐标*/
	float afRefractPosX[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT];/*入射点坐标 */
	float afRefractPosY[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT];/*入射点坐标 */
	float afRefractPosZ[setup_MAX_GROUP_LAW_QTY][setup_MAX_PROBE_ELEMENT];/*入射点坐标 */
};

enum DEFECT_SIGN_TYPE
{
	DEFECT_SIGN_LENGTH = 0 ,
	DEFECT_SIGN_HEIGHT,
	DEFECT_SIGN_DEPTH,
	DEFECT_SIGN_SAVE
//	DEFECT_SIGN_DELETE
};

struct DEFECT_INFO
{
	DEFECT_INFO *pPrev;
	DEFECT_INFO *pNext;

	char  srtInfo[256];
    char  srtInfo2[256];
	char  srtImageName[256];

	bool  bValid;

	float fUDepth;

	float fUStart;
	float fUStop;

	float fSStart;
	float fSStop;

	float fIStart;
	float fIStop;

    float fVPAStart;
    float fVPAStop;

	int   nLawNo;
    char  m_strMeasure[setup_MAX_MEASURE_QTY][50]  ;
    char  m_strSzField[setup_MAX_MEASURE_QTY][20];
    char  m_strSzFieldUnit[setup_MAX_MEASURE_QTY][20];
    char SL[20];
    char Index_pos[20];
};

struct DEFECT_PARAM
{
	int		  index;
	DEFECT_INFO  dfInfo;
	DEFECT_INFO* pDFHead;
	DEFECT_INFO* pDFEnd;
};

struct coupleCScanGroupInfo{
    bool calculateState;      //本组C扫状态，false为还未计算，true为已经计算
    float oldPartThickness;   //旧的工件厚度值，用于判断工件厚度改变重新计算耦合闸门内的值
    QVector<WDATA> data;      //储存耦合C扫数据
};

class DopplerConfigure : public QObject
{
	Q_OBJECT

public:
	~DopplerConfigure () ;
	static   DopplerConfigure* Instance() ;

	int   OpenConfig(QString& path_) ;
	void  SaveConfig(QString& path_) ;
	int   OpenData(QString& path_);

	int RectifyScanLength();
	void CreateShadowData(int iLen_);
	void ReleaseShadowData();
	void ResetShadowData();
    void initScanPos();
	WDATA* GetShadowDataPoint();
	U8* GetComDisplayPoint();

	WDATA* GetFileDataPoint() const ;
	void  InitCommonConfig()  ;
	void  InitGroupConfig (int nGroupId_)  ;
	void  GroupModeChanged(int nGroupId_ , setup_GROUP_MODE eMode_) ;
	void  InitLawComfing  (int nGroupId_)  ;
	void  OldConfigureToConfigure(DopplerDataFileOperateor* pConf_);
	void  OldGroupToGroup(DopplerDataFileOperateor* pConf_) ;
    void  InitTOPCInfo();

	void  UpdateTofdConfig(int nGroupId) ;
	TOFD_PARA* GetTofdConfig(int nGroupId) ;
	DopplerHtmlReport* GetReportOpp() ;
	void OpenDefectFile(QString& path_);
	void SaveDefectFile(QString& path_);
	void FilePathPro(QString& path_);
	// 
	int DefectSign(int iGroupId_, DEFECT_SIGN_TYPE signType_);
	int AddDefectInfo(int iGroupId_, DEFECT_INFO dfInfo_);
	int ClearDefectInfo(int iGroupId_);
	int DeleteDefect(int iGroupId_, int index_);
	int GetDefectCnt(int iGroupId_);
	void ReleaseAllDefect();
	void ReleaseDefect(int iGroupId_);
	float DefectLengthValue(int iGroupId_, float* pStart_, int index_ = -1);
	float DefectLengthPos(int iGroupId_, float* pStart_, int index_ = -1);
    float DefectVPAPos(int iGroupId_, float* pStart_, int index_ = -1);
	float DefectHeightValue(int iGroupId_, float* pStart_, int index_ = -1);
	float DefectHeightPos(int iGroupId_, float* pStart_, int index_ = -1);

	float DefectWidthValue(int iGroupId_, float* pStart_, int index_ = -1);
	float DefectWidthPos(int iGroupId_, float* pStart_, int index_ = -1);

	float DefectDepthValue(int iGroupId_, int index_ = -1);
	float DefectDepthPos(int iGroupId_, int index_ = -1);
	DEFECT_INFO* GetDefectPointer(int iGroupId_, int index_);
    DEFECT_INFO* SetDefectInfo(int iGroupId_, int index_, char* strInfo_,char* strInfo2);
	char* GetDefectInfo(int iGroupId_, int index_);
	void SetLastDate();
	QDate GetLastDate();
	//--------------------------------------------------

	void SaveEvn() ;

    static void setSetting(int group,const QString &valueName,int value);
    static int getSetting(int group,const QString &valueName);

protected:
	explicit DopplerConfigure(QObject *parent = 0);
	void OpenEvn() ;

	static   DopplerConfigure* m_pConfig   ;
	DopplerDataFileOperateor* m_pDataFile  ;
	DopplerHtmlReport* m_pReport  ;

public:
	FILE_HEADER			header ;   //
	COMMON_CONFIG		common ;   //
	COMMON_CONFIG		comTmp ;   //
	GROUP_CONFIG		group[setup_MAX_GROUP_QTY+1] ;
	FOCALLAW_RESULT		focallaw[setup_MAX_GROUP_QTY] ;

    QList<coupleCScanGroupInfo> coupleCScanData;
    QVector<double> rasterOffset; //保存二维扫查每个步进分辨率上的偏置,单位mm

private:
	WDATA*				m_pData ;
	WDATA*				m_pDataShadow ;
	U8					m_nComDisplay[4];

    QString g_strColorAmp;
    QString g_strColorThickness;
    QString g_strColorRectifier;

public:
    QList<MATERIAL*>*	m_listMaterial;
	TOFD_PARA			TOFD[setup_MAX_GROUP_QTY] ;
	QString				m_szFileInUse;
	QString				m_szDefectPathName;

    SYSTEM_ENVIRMENT	AppEvn;
	DEFECT_PARAM		m_dfParam[setup_MAX_GROUP_QTY];
	int					m_nCutBmpNo[setup_MAX_GROUP_QTY];

};

#endif // DOPPLERCONFIGURE_H
