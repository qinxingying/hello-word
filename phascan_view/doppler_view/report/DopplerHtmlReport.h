#ifndef DOPPLERHTMLREPORT_H
#define DOPPLERHTMLREPORT_H

#include <QString>
#include <QDate>
#include <stdio.h>
#include <QList>
#include <configure/DopplerConfigure.h>
#include <process/CalcMeasurement.h>

#define STRING QString
#define TOCHAR(x) ((x).toLocal8Bit().data())
#define TOSTRING(x ,y) (x) = QString(y)

struct ReportInfo
{
    char  strReportName[1024]  ;
    char  strPartName[1024]    ;
    char  strPartNo  [1024]    ;
    char  strPartPos [1024]    ;
    char  logoName   [1024];
    int   nYear  ;
    int   nMonth ;
    int   nDate  ;
    int   eMode  ;
}  ;

struct ReportValueItem
{
    float fPos ;
    int   nGroupId ;
    int   nLawId   ;
    QString szValue[setup_MAX_MEASURE_QTY];
    QString szPixmap;
    QString szField[setup_MAX_MEASURE_QTY];
    QString szFieldUnit[setup_MAX_MEASURE_QTY];
} ;


class DopplerHtmlReport
{
public:
    DopplerHtmlReport();
    void InitReportInfo();
    void SetReportInfo(ReportInfo*) ;
    ReportInfo* GetReportInfo() ;
    void SaveReport()    ;
    void BuildReport()   ;
    void AddOneValueItem(ReportValueItem* value)  ;
    int DelOneValueItem()  ;

    void CreateTofdHeader(int nGroupId_);
    void CreateDefect(int nGroupId_);
	void CreateDefectCell(int nGroupId_, int index_);
    void set_data_path(QString &str);

protected:
    void BuildStarter () ;
    void BuildEnder()    ;
    void CreateHeader()  ;
    void UpdateGroupConfig(int nGroupId_) ;
    void SprintfGroupProbeConfig(int nGroupId_);

    void fprintfReportGroupStart(int group) ;
    void fprintfReportGroupProbe();
    void fprintfReportGroupSetup();
    void fprintfReportGroupCalculator();
    void fprintfReportGroupPart();
    void SprintfReportTable();
    void SprintfGroupMeasure() ;
    void SfprintfReportSignature() ;

    void CreateFolder()  ;
    bool CopyFileToPath(QString toDir ,QString sourceDir);

    ReportInfo m_cInfo ;
    FILE*      m_pFile ;
    QString    m_strFile      ;
    QString    m_szDataFile   ;
    QString    m_strFolder    ;
    QString    m_strFolderDir ;
    QList<ReportValueItem>  m_cValueList ;

    QString m_probeModel;
    QString m_probeSerial;
    QString m_probeFrequency;
    QString m_peakFrequency;
    QString m_wedgeModel;
    QString m_wedgeAngle;
    QString m_probeAperture;

    QString m_db6lowerFrequency;
    QString m_db6higherFrequency;
    QString m_db6centerFrequency;
    QString m_db6bandWidthMHz;
    QString m_db6bandWidth;
    QString m_db20lowerFrequency;
    QString m_db20higherFrequency;
    QString m_db20centerFrequency;
    QString m_db20bandWidthMHz;
    QString m_db20bandWidth;

    QString m_beamDelay;
    QString m_start;
    QString m_range;
    QString m_prf;
    QString m_type;
    QString m_averagingFactor;

    QString m_scaleFactor;
    QString m_videoFilter;
    QString m_rectification;
    QString m_bandPassFilter;

    QString m_voltage;
    QString m_gain;
    QString m_mode;
    bool m_waveTypeSW;
    QString m_waveType;
    QString m_soundVelocity;
    QString m_pulseWidth;

    QString m_scanOffset;
    QString m_indexOffset;
    QString m_skew;

    QString m_gateIstart;
    QString m_gateIwidth;
    QString m_gateIthreshold;
    QString m_gateIsynchro;

    QString m_gateAstart;
    QString m_gateAwidth;
    QString m_gateAthreshold;
    QString m_gateAsynchro;

    QString m_gateBstart;
    QString m_gateBwidth;
    QString m_gateBthreshold;
    QString m_gateBsynchro;

    QString m_usedElementQty;
    QString m_firstTXelement;
    QString m_lastTXelement;
    QString m_firstRXelement;
    QString m_lastRXelement;
    QString m_resolution;

    QString m_waveTypeVelocity;
    QString m_startAngle;
    QString m_stopAngle;
    QString m_angleResolution;
    QString m_lawConfiguration;

    int m_focalPointType;
    QString m_focalType;
    QString m_positionStart;
    QString m_positionEnd;
    QString m_positionStep;
    QString m_offsetStart;
    QString m_offsetEnd;
    QString m_depthStart;
    QString m_depthEnd;

    QString m_material;
    QString m_geometry;
    QString m_thickness;

    QString m_scanStart;
    QString m_scanLength;
    QString m_scanResolution;
    QString m_indexStart;
    QString m_indexLength;
    QString m_indexResolution;

    QString m_scanSynchro;
    QString m_scanSpeed;
    QString m_axis;
	QString m_encoder;
    QString m_encoderType;
    QString m_encoderResolution;
    QString m_polarity;
    QString m_axis2;

    QString  m_szField[setup_MAX_GROUP_QTY][setup_MAX_MEASURE_QTY];
    QString  m_szFieldUnit[setup_MAX_GROUP_QTY][setup_MAX_MEASURE_QTY];
    QString m_dataFilePath;

	char m_strReportDir[1024];
};

#endif // DOPPLERHTMLREPORT_H
