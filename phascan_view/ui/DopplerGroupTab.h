/***************************
  Name:  DopplerGroupTab
  Date : 2013-08-26
  Description:   ���������ô���
************************************/

#ifndef DOPPLERGROUPTAB_H
#define DOPPLERGROUPTAB_H

#include <QWidget>
#include <QModelIndex>
#include <configure/const.h>
#include <process/ParameterProcess.h>
#include <QtGui>
#include <QLabel>
#include <QDoubleSpinBox>

class QToolBox ;
class DopplerConfigure ;
class QStandardItemModel;
namespace Ui {
    class DopplerGroupTab;
}



class DopplerGroupTab : public QWidget
{
    Q_OBJECT

public:
    explicit DopplerGroupTab(QWidget *parent = 0);
    ~DopplerGroupTab();
    void SetGroupId(int nGroupId_) ;
    QToolBox* GetToolBox() const ;
    void UpdateCursorValue();
    void UpdateDefectBox();
    void UpdateDefectValue();
    void SetWndName(setup_LANG eLang);
    void UpdateGroupConfig () ;

	void UpdateCurrentAngleCom();
	void UpdateTofdParam();
	void UpdateSizeingCurves();
protected:
    //##### ֻ��������ʾʱ ���ڲ�ʹ��
    void SetWidgetInvalide();
    //###############################
    void CreateSettingView();
    void UpdateColorSetting();
    void UpdateSampleRange();
    void UpdateVelocitySelection() ;
    void InitComBoxMaterialSelection() ;
    void UpdateProbeConfig(int bIsRx_) ;
    void UpdateWedgeConfig(int bIsRx_) ;
    void UpdateLawConfig();
    void UpdateProbeWedge() ;

    void UpdateMeasureBox();
    void UpdateParameterLimit();
    void UpdateFocallawState();
    void UpdateGeometryState();
    void ElementAlign() ;
    void FocusPositionAlign();
    void AngleAlign();
    int  m_nGroupId;
    DopplerConfigure*  m_pConfig ;
    GROUP_CONFIG*      m_pGroup  ;
    QStandardItemModel *model    ;

	QLabel*			m_pSizingCurveName[setup_DAC_POINT_QTY];
	QDoubleSpinBox* m_pSizingCurveValue[setup_DAC_POINT_QTY];
	QLabel*			m_pSizingCurveUnit[setup_DAC_POINT_QTY];

private slots:
    void StartDrags(QModelIndex a) ;
    void slotMeasureBoxTipInfo(int nIndex_);
    void on_ValueGain_editingFinished();
    void on_ValueRefGain_valueChanged(double arg1);
    void on_ValueStart_editingFinished();
    void on_ValueRange_editingFinished();
    void on_ComCurrentAngle_currentIndexChanged(int index);
    void on_ComTravelMode_currentIndexChanged(int index);
    void on_ValueVelocity_editingFinished();
    void on_ValueWedgeDelay_editingFinished();
    void on_ComVelocitySelection_currentIndexChanged(int index);
    void on_ValuePulser_editingFinished();
    void on_ValueReceiver_editingFinished();
    void on_ComFilter_currentIndexChanged(int index);
    void on_ComRectifier_currentIndexChanged(int );
    void on_CheckVideoFilter_clicked(bool checked);
    void on_ValuePointQty_editingFinished();
    void on_ValueSumGain_editingFinished();
    void on_CheckPointQtyAuto_toggled(bool checked);
    void on_CheckSumGainAuto_toggled(bool checked);
    void on_ComAverage_currentIndexChanged(int index);
    void on_ComGroupMode_currentIndexChanged(int index);
    void on_BtnProbeSelection_clicked();
    void on_BtnWedgeSelection_clicked();
    void on_BtnProbeSelection_2_clicked();
    void on_BtnWedgeSelection_2_clicked();
    void on_BtnProcessLaw_clicked();
    void on_ComLawType_currentIndexChanged(int index);
    void on_ComAngleType_currentIndexChanged(int index);
    void on_ValuePriSteerStart_editingFinished();
    void on_ValuePriSteerStop_editingFinished();
    void on_ValuePriSteerStep_editingFinished();
    void on_ValueSecSteerStart_editingFinished();
    void on_ValueSecSteerStop_editingFinished();
    void on_ValueSecSteerStep_editingFinished();
    void on_ValueRefractStart_editingFinished();
    void on_ValueRefractStop_editingFinished();
    void on_ValueRefractStep_editingFinished();
    void on_ValueSkewStart_editingFinished();
    void on_ValueSkewStop_editingFinished();
    void on_ValueSkewStep_editingFinished();
    void on_ComFocalType_currentIndexChanged(int index);
    void on_ValueFocusPositionStart_editingFinished();
    void on_ValueFocusPositionStop_editingFinished();
    void on_ValueFocusPositionStep_editingFinished();
    void on_ValueFocusOffsetStart_editingFinished();
    void on_ValueFocusOffsetStop_editingFinished();
    void on_ValueFocusDepthStart_editingFinished();
    void on_ValueFocusDepthStop_editingFinished();
    void on_ValueElementQtyPri_editingFinished();
    void on_ValueElementQtySec_editingFinished();
    void on_ValueElementStartPri_editingFinished();
    void on_ValueElementStartSec_editingFinished();
    void on_ValueElementStopPri_editingFinished();
    void on_ValueElementStopSec_editingFinished();
    void on_ValueElementStepPri_editingFinished();
    void on_ValueElementStepSec_editingFinished();

    void on_CheckGateShow_clicked(bool checked);
    void on_ComGateSelect_currentIndexChanged(int index);
    void GatePro();
    void on_ValueGateStart_valueChanged(double arg);
    void on_ValueGateWidth_valueChanged(double arg);
    void on_ValueGateHeight_valueChanged(double arg);
    void on_ComGateSync_currentIndexChanged(int index);
    void on_ComGateMeasure_currentIndexChanged(int index);

    void on_CheckShowThickness_clicked(bool checked);
    void on_ComGeometry_currentIndexChanged(int index);
    void on_ComMaterial_currentIndexChanged(int index);

    void PartPro();
    void on_ValuePartSize1_valueChanged(double arg);
    void on_ValuePartSize2_valueChanged(double arg);
    void on_ValuePartSize3_valueChanged(double arg);
    void on_CheckUnifiedPartSetting_clicked(bool checked);
	void on_ValueScanOffset_editingFinished();
	void on_ValueIndexOffset_editingFinished();
    void on_ComSkewAngle_currentIndexChanged(int index);
    void on_BtnLoadPartFile_clicked();
	void on_CheckLwBwShow_clicked(bool checked);
	void on_ComBoxProMode_currentIndexChanged(int index_);
    void on_SpinBoxWedgeSeperation_valueChanged(double arg1);
    void on_SpinBoxZeroOff_valueChanged(double);
    void on_SpinBoxDepthStart_valueChanged(double);
    void on_SpinBoxDepthEnd_valueChanged(double);
    void on_SpinBoxDepthCal_valueChanged(double);
    void on_BtnDepthCal_clicked();
    void on_CheckPartFileShow_clicked(bool checked);
    void on_CheckMeasureShow_clicked(bool checked);
	void on_CheckBackShow_clicked(bool checked);
	void on_ComField1_currentIndexChanged(int index);
    void on_ComField2_currentIndexChanged(int index);
    void on_ComField3_currentIndexChanged(int index);
    void on_ComField4_currentIndexChanged(int index);
    void on_ComField5_currentIndexChanged(int index);

    void on_ValueARef_valueChanged(double);
    void on_ValueAMes_valueChanged(double);
    void on_ValueURef_valueChanged(double);
    void on_ValueUMes_valueChanged(double);
    void on_ValueSRef_valueChanged(double);
    void on_ValueSMes_valueChanged(double);
    void on_ValueIRef_valueChanged(double);
    void on_ValueIMes_valueChanged(double);
    void on_BtnColorAmp_clicked();
    void on_BtnColorRf_clicked();
    void on_BtnColorThickness_clicked();
    void on_ComColorLineSelection_currentIndexChanged(int index);
    void on_ComColorLineColor_currentIndexChanged(int index);
    void on_CheckCursorShow_clicked(bool checked);
	void on_CheckCursorSync_clicked(bool checked);
    void on_ValueCScanThicknessMin_valueChanged(double);
    void on_ValueCScanThicknessMax_valueChanged(double);
    //void on_ValueCScanThicknessMin_editingFinished();
    //void on_ValueCScanThicknessMax_editingFinished();
    void on_ComCScanSource1_currentIndexChanged(int index);
    void on_ComCScanSource2_currentIndexChanged(int index);

	void ComDispPro(int index, int iGroup);
	void on_ComComDisp1_currentIndexChanged(int index);
	void on_ComComDisp2_currentIndexChanged(int index);
	void on_ComComDisp3_currentIndexChanged(int index);
	void on_ComComDisp4_currentIndexChanged(int index);
	void on_BtnRefurbishComDisp_clicked();
    void on_CheckDefectShow_clicked(bool checked);
    void on_ComDefectIndex_currentIndexChanged(int index);
	void on_lineEditReMark_textChanged(QString str);
	void on_BtnDefectDelete_clicked();
    void on_ComLanguage_currentIndexChanged(int index);

private:
    Ui::DopplerGroupTab *ui;
};

#endif // DOPPLERGROUPTAB_H
