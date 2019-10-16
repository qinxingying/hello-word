/***************************
  Description:   参数设置处理类
*****************************/


#ifndef PARAMETERPROCESS_H
#define PARAMETERPROCESS_H

#include "DopplerConfigure.h"

#include <QObject>
#include <QString>
#include <QPoint>

class Focallaw ;
enum GATE_POS_VALUE_TYPE
{
   NS_WITH_DELAY     ,
   MM_WITH_DELAY     ,

   NS_WITHOUT_DELAY  ,
   MM_WITHOUT_DELAY  ,

   MM_TRUE_DEPTH     ,
   MM_HORIZENTAL_DIST
} ;


class ParameterProcess : public QObject
{
    Q_OBJECT
public:
    static   ParameterProcess* Instance() ;

    QString AddOneGroup(int nGroupId_) ;
    QString DeleteOneGroup(int nGroupId_);
    //******************************
    //     set value  : group
    //******************************
    int  SetupGain(int nGroupId_ , double fValue_);
    int  SetupRefGain(int nGroupId_ , double fValue_) ;
    //int  SetupSampleStart(int nGroupId_ , double fValue_) ;
    //int  SetupSampleRange(int nGroupId_ , double fValue_) ;
    int  SetupTravelMode(int nGroupId_ , int eMode_);
    int  SetupVelocity(int nGroupId_ , double fValue_)    ;
    int  SetupWedgeDelay(int nGroupId_ , double fValue_)  ;
    int  SetupTxElementStart(int nGroupId_ , int nValue_) ;
    int  SetupRxElementStart(int nGroupId_ , int nValue_) ;
    int  SetupFilter(int nGroupId_ , int nValue_)      ;
    int  SetupRectifier(int nGroupId_ , int nValue_)   ;
    int  SetupVedioOnOff(int nGroupId_ , int nValue_)  ;
    int  SetupPointQty(int nGroupId_ , int nValue_)    ;
    int  SetupSumGain(int nGroupId_ , double fValue_)  ;
    int  SetupPointQtyAutoMode(int nGroupId_ , int bValue_);
    int  SetupSumGainAutoMode(int nGroupId_ , int bValue_) ;
    int  SetupAverage(int nGroupId_ , int nValue_)     ;
    int  SetupGroupMode(int nGroupId_ , int nValue_);
    int  SetupProbeLoad(int nGroupId_ , PROBE_CONFIG* probe_ , int TxRx_) ;
    int  SetupWedgeLoad(int nGroupId_ , WEDGE_CONFIG* wedge_ , int TxRx_) ;
    int  SetupFocalLaw(int nGroupId_ , LAW_CONFIG* law_)  ;
    int  SetupGateInfo(int nGroupId_ , setup_GATE_NAME name_ ,GATE_CONFIG* gate_ ) ;
    int  SetupSizingCurve(int nGroupId_ , CURVES curve_);
	int  SetupPart(int nGroupId_ , PART_CONFIG* part_) ;
	int  SetupPartGeometry(int nGroupId_ , PART_CONFIG* part_) ;
	int  SetupPartMaterial(int nGroupId_ , int nIndex_) ;

	//int  SetupPartWeld(int nGroupId_ , PART_CONFIG* part_) ;
    int  SetupWedgePosition(int nGroupId_ , float fValue1_ , float fValue2_) ;
    int  SetupWedgeSkewAngle(int nGroupId_ , setup_PROBE_ANGLE eAngle_) ;
    int  GetShowWeldPart(int nGroupId_);
    int  SetupShowWeldPart(int nGroupId_ , int bShow_) ;
    int  SetupMeasureData(int nGroupId_ , int nField_ , int index_ ) ;
    int  SetupShowMeasure(int nGroupId_ , int bShow_) ;

	int  GetShowMeasureNumber(int nGroupId_);
	int  SetupCursor(int nGroupId_ , setup_CURSOR_TYPE eType_ , float fValue_) ;
    int  SetupShowCursor(int nGroupId_ , int bShow_) ;
    int  SetupCurrentLawCursor(int nGroupId_ , int nValue_) ;
    int  SetupPalette(int nGroupId_, PALETTE_NAME ePalette_ , void* pColor_);
    int  SetupAScanColor(int nGroupId_ , int nLineId_ , int eColor_);
    //***************************************************************
    //     set value  :  instrument
    //***************************************************************
	int  SetupScanPos(float fScanPos_) ;
	int  SetupScanType(setup_SCAN_TYPE eType_);
    int  SetupScanMode(setup_SCAN_MODE eMode_);
    int  SetupEncoderType(setup_ENCODER_TYPE eType_) ;
    int  SetupPrf(float fValue_);
    int  SetupScanArea(float afValue_[6]);
    int  SetupEncoderConfigure(int eEncoder_ , ENCODER_CONFIG* pEncoder_) ;
    int  SetupPAVoltage(setup_VOLTAGE_MODE eVoltage_) ;
    int  SetupUTVoltage(setup_VOLTAGE_MODE eVoltage_) ;
    //int  SetupPATxRxMode(setup_TX_RX_MODE eMode_);
    //int  SetupUTTxRxMode(setup_TX_RX_MODE eMode_);
    //***************************************************************
    //     get value
    //***************************************************************
    int  GetGroupQty() const ;
    int  GetGroupDataSize(int nGroupId_) const;
    int  GetTotalDataSize() const;
    int  GetGroupLawQty(int nGroupId_) const ;
    int  GetGroupLawQtyForPosition(int nGroupId_) const ;
    int  GetTotalLawQty() const ;

    static int getWaveHalfValue();
    static int correctionPdata( WDATA value);

    unsigned int* GetGroupBeamDelay(int nGroupId_) const;
    float         GetRefGainScale(int nGroupId_) ;
    WDATA	  GetRefGainScaleData(WDATA wData_, float fScale_, bool bRectify_);

	float*        GetBeamInsertPos(int nGroupId_);
    float         GetBeamInsertPos(int nGroupId_ , int nLawId_);
    int           GetGroupPointQty(int nGroupId_);
    unsigned int  GetGroupWedgeDelay(int nGroupId_) const ;
    unsigned int  GetGroupPulserWidth(int nGroupId_) const ;
    void  GetCScanThicknessRangeTime(int nGroupId_ , int* nStart_ , int* nStop_);
    float GetCScanThicknessStart(int nGroupId_) ;
    float GetCScanThicknessStop(int nGroupId_)  ;


    int  GetGroupDataOffset(int nGroupId_) const ;
    int  GetScanIndexPos() const ;
    int  transforRasterPosToMarker() const;
    int  GetScanIndexStart2() const;
    int SAxisDistToIndex(float fDist_) const;
    float GetIndexStartPos() const;
    float GetIndexEndPos() const;
    int TransforIndexPosToIndex(float fPos) const;
    float TransforIndexIndexToPos(int fIndex) const;
    int SAxisstoptoIndex(float fStop) const;
	float SAxisIndexToDist(int index_) const;
    int  GetGroupLawDataOffset(int nGroupId_ , int nLawId_) const ;
	int GetRealScanIndex(int nGroupId_, int nScanPos_);
	WDATA* GetDataPointer() ;
    WDATA* GetShadowDataPointer();
    WDATA* GetDataAbsolutePosPointer(int nGroupId_, int nScanPos_, int nLawId_, WDATA* pSource_);
	float GetSizingCurveRefAmp(int nGroupId_, int nBeamNo_, int nPoint);
    void PutRecDataToShadow(int nGroupId_);
	void GroupDataMove(int nGroupId_, WDATA* pSource_, WDATA* pDest_, int nSourceOff, int nDestOff_);
    float GetPeakTraceHeight(int nGroupId_, int nScanPos_, int nLawId_, float fUDist_);
	bool GetGatePeakInfos(int nGroupId_, int nScanPos_, int nLawId_, PEAK_CONFIG* pInfo_);
	bool GetGatePeakInfos(int nGroupId_, WDATA* pData_, int nLawId_, PEAK_CONFIG* pInfo_);
    int  GetCoupleMonitoringData(int nGroupId_, float* pResult_);
    WDATA* GetScanPosPointer(int nGroupId_, int nScanPos_);
    WDATA* GetGroupDataPointer(int nGroupId_);
    WDATA* GetGroupDataPointerRaster(int nGroupId_);
    WDATA* GetLawDataPointer(int nGroupId_ , int nLawId_)  ;
    WDATA* GetCoupleDataPointer( int nGroupId_);

    unsigned int   GetLawGateDWORD(int nGroupId_ , int nLawId_ , setup_GATE_NAME eGate_);
	U8* GetScanMarker(int nGroupId_) const;
    float GetScanStart() const;
    float GetScanStop() const;
    float GetScanStart2() const;
    float GetScanend() const;
    int GetLawStart() const;
    int GetLawStop() const;
    void ChangeLawStart(int lawstart) const;
    void ChangeLawStop(int lawstop) const;
    float GetScanPos() const;
	int GetScanOff(int nGroupId_) const;
	int GetScanMax() const;
	int GetRealScanMax() const;
    int  TofdDepthCalibration(int nGroupId_);
    void TofdCursorCalibration(int nGroupId_);
    void UpdateTofdParam(int nGroupId_);
    float CalculateTofdProbeDelay(int nGroupId_);
    float CalculateTofdPcs(int nGroupId_);
    float GetTofdDepth(int nGroupId_ , float fCursorPos);
    int  GetTofdDepth(int nGroupId_ , int ID_ , float* fValue_) ;
    void FittedCurveGetPoints(int nGroupId_, float fPrecX_, float fPrecY_, float fTX0_, int iDots_, QPointF* pPoints_);

    float GetVelocity(int nGroupId_);
    float GetPrf()  ;
    float GetScanSpeed();
    double GetRealScanRange();

	void  GetScanScanAxisRange(int nGroupId_ ,  int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_);
	void  GetBScanScanAxisRange(int nGroupId_ ,  int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_);
    void  GetBScanIndexAxisRange(int nGroupId_ ,  int nDist_ , double* fStart_ , double* fStop_);
	void  GetCScanScanAxisRange(int nGroupId_ , int nDist_ , double* fStart_ , double* fStop_, double* fSliderStart_ , double* fSliderStop_);
    void  GetCScanIndexAxisRange(int nGroupId_ , double* fStart_ , double* fStop_);
    void ChangeCscanIndexRange( double* fStart_ , double* fStop_,double* fStart2_,double* fStop2_,double* fstep);
    void ChangeCscanIndexstart( double* fStart_ );
    void ChangeCscanIndexstop( double* fStop_ );
    void ChangeCscanruler( int fscanstart, int fscanend);
    float GetRasterCoveredLength( int nGroupId_);
    float GetRasterCurrentIndexPos( int nGroupId_);
    int   GetRasterIndexStepBeam( int nGroupId_);
    void  GetSImageHorizentalRange(int nGroupId_ , float* fStart_ , float* fStop_);
    int  GetSImageVerticalRange(int nGroupId_ , float* fStart_ , float* fStop_);
    void  GetSScanHorizentalRange(int nGroupId_ , float* fStart_ , float* fStop_);
    int  GetSScanVerticalRange(int nGroupId_ , float* fStart_ , float* fStop_);
	int DistMmToDotPos(int nGroupId_, int nLawId_, float fDist_);
    float DistDotPosToMm(int nGroupId_ , int nPos_);
    float DistUsToMm(int nGroupId_ , float fTime_);
    float DistMmToUs(int nGroupId_ , float fDist_);
    float DistNsToMm(int nGroupId_ , int nTime_);
    int   DistMmToNs(int nGroupId_ , float fDist_);
    int SCanAngleToCScanLineAngle(int nGroupId_, float _fCursor);
    float CScanLineAngleToScanLineAngle(int nGroupId_, int _nPos);

    QString GetSonicAxisUnit(int nGroupId_) ;
    QString GetScanAxisUnit()  ;
    QString GetIndexAxisUnit() ;
    QString GetCscanIndexUnit(int nGroupId_) ;
    setup_CSCAN_SOURCE_MODE GetCScanSource(int nGroupId_ , int eCScan_) ;


    float GetLawAngle(int nGroupId_ , int nLawId_) ;
    float GetSampleStart(int nGroupId_ , int nLawId_) ;
    float GetSampleRange(int nGroupId_ , int nLawId_) ;
    float GetSampleStartSoundpath(int nGroupId_) ;
    float GetSampleRangeSoundpath(int nGroupId_) ;
    float GetMaterialVelocity(int nGroupId_ , int bTran_)  ;
    float GetPartThickness(int nGroupId_) const;
    void  GetWedgePosition(int nGroupId_ , float* fScanOffset_  , float* fIndexOffset_ ) ;
    setup_PROBE_ANGLE GetProbeAngle(int nGroupId_) const;
    setup_RECTIFIER_MODE GetRectifierMode(int nGroupId_)  const ;
    setup_PROBE_ANGLE   GetGroupSkewType(int nGroupId_) const;
    setup_TX_RX_MODE  GetGroupTxRxMode(int nGroupId_) const;

	PART_CONFIG*  GetPart(int nGroupId_);
	GATE_CONFIG*  GetGateInfo(int nGroupId_ , setup_GATE_NAME eGATE_) ;
    PROBE_CONFIG* GetProbeConfig(int nGroupId_ , int TxRx_) ;
    WEDGE_CONFIG* GetWedgeConfig(int nGroupId_ , int TxRx_) ;
    LAW_CONFIG*   GetLawConfig(int nGroupId_);
    GROUP_CONFIG* GetGroupConfig(int nGroupId_);
    WELD* GetWeld(int nGroupId_) ;
    void  SetWeld(int nGroupId_ , WELD* pWeld_ );
    void* GetPalete(int nGroupId_ , PALETTE_NAME eName_);
    float GetGateValueAmp(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_)  ;
    float GetGateValuePos(int nGroupId_ , int nLaw_ , setup_GATE_NAME eGate_ , GATE_POS_VALUE_TYPE eType_ = NS_WITH_DELAY)  ;

    void InitScanOff(int nGroupId_);

    QVector<WDATA> GetCoupleCScanData( int nGroupId_);
protected:
    explicit ParameterProcess(QObject *parent = 0);
    DopplerConfigure* m_pConfig;
	float m_fBScanOff[8];
	float m_fCScanOff[8];
signals:

public slots:


};


#endif // PARAMETERPROCESS_H
