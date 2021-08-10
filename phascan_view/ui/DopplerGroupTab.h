/***************************
  Name:  DopplerGroupTab
  Date : 2013-08-26
************************************/

#ifndef DOPPLERGROUPTAB_H
#define DOPPLERGROUPTAB_H

#include "const.h"
#include "ParameterProcess.h"
#include "Instrument.h"
#include "DopplerConfigure.h"

#include <QWidget>
#include <QModelIndex>
#include <QtGui>
#include <QLabel>
#include <QDoubleSpinBox>

class QToolBox;
class DopplerConfigure;
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
    void SetWndName();
    void UpdateGroupConfig();

	void UpdateCurrentAngleCom();
	void UpdateTofdParam();
	void UpdateSizeingCurves();
    void retranslateGroupTabUi();
    void LoadStandardFormConifg();
    void setTopcWidthValue(double value);
    void setThicknessValue(double value);
    void setShowCursorStatus(bool status);
    void setShowDefectStatus(bool status);
    void setCscanShowallChange();
    void setMeasureEnable(bool status);
    void setShowGateB(bool status);
protected:
    void SetWidgetInvalide();
    void CreateSettingView();
    void UpdateColorSetting();
    void UpdateSampleRange();
    void UpdateVelocitySelection();
    void InitComBoxMaterialSelection();
    void UpdateProbeConfig(int bIsRx_);
    void UpdateWedgeConfig(int bIsRx_);
    void UpdateLawConfig();
    void UpdateProbeWedge();
    void UpdateMeasureBox();
    void UpdateStandard(int selectID,int ifadd);    
    void UpdateParameterLimit();
    void UpdateFocallawState();
    void UpdateGeometryState();
    void ElementAlign();
    void FocusPositionAlign();
    void AngleAlign();
    int  m_nGroupId;
    DopplerConfigure* m_pConfig;
    GROUP_CONFIG* m_pGroup;
    QStandardItemModel *model;

    QLabel*	m_pSizingCurveName[setup_DAC_POINT_QTY];
	QDoubleSpinBox* m_pSizingCurveValue[setup_DAC_POINT_QTY];
    QLabel*	m_pSizingCurveUnit[setup_DAC_POINT_QTY];

signals:
    void thicknessChange(double thickness);

private slots:
    void StartDrags(QModelIndex a) ;
    void slotMeasureBoxTipInfo(int nIndex_);
    void on_ValueGain_editingFinished();
    //void on_ValueStart_editingFinished();
    //void on_ValueRange_editingFinished();
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
    void on_BtnProcessLaw_clicked();
    void on_ComLawType_currentIndexChanged(int index);
    void on_ComAngleType_currentIndexChanged(int index);
    void on_ValueRefractStart_editingFinished();
    void on_ValueRefractStop_editingFinished();
    void on_ValueRefractStep_editingFinished();
    void on_ComFocalType_currentIndexChanged(int index);
    void on_ValueFocusPositionStart_editingFinished();
    void on_ValueFocusPositionStop_editingFinished();
    void on_ValueFocusPositionStep_editingFinished();
    void on_ValueElementQtyPri_editingFinished();
    void on_ValueElementStartPri_editingFinished();
    void on_ValueElementStopPri_editingFinished();
    void on_ValueElementStepPri_editingFinished();
    void on_CheckGateShow_clicked(bool checked);
    void on_ComGateSelect_currentIndexChanged(int index);
    void GatePro();
    void on_ValueGateStart_valueChanged(double);
    void on_ValueGateWidth_valueChanged(double);
    void on_ValueGateHeight_valueChanged(double);
    void on_ValueTopcWidth_valueChanged(double);
    void on_ComCscanType_currentIndexChanged(int index);
    void on_ComTopCMergeRefer_currentIndexChanged(int index);
    void on_ComTopcMergeStatus_currentIndexChanged(int index);
    void on_ComGateMode_currentIndexChanged(int index);
    void on_ComGateSync_currentIndexChanged(int index);
    void on_ComGateMeasure_currentIndexChanged(int index);
    void on_CheckShowThickness_clicked(bool checked);
    void on_ComGeometry_currentIndexChanged(int index);
    void on_ComMaterial_currentIndexChanged(int index);
    void PartPro();
    void on_ValuePartSize1_valueChanged(double arg);
    void on_ValuePartSize2_valueChanged(double arg);
    void on_ValuePartSize3_valueChanged(double arg);
//    void on_ValueScanOffset_editingFinished();
//    void on_ValueIndexOffset_editingFinished();
    void on_ComSkewAngle_currentIndexChanged(int index);
//    void on_BtnLoadPartFile_clicked();
    void on_BtnLoadDxfFile_clicked();
	void on_CheckLwBwShow_clicked(bool checked);
	void on_ComBoxProMode_currentIndexChanged(int index_);
    void on_SpinBoxWedgeSeperation_valueChanged(double arg1);
    void on_SpinBoxZeroOff_valueChanged(double);
    void on_SpinBoxDepthStart_valueChanged(double);
    void on_SpinBoxDepthEnd_valueChanged(double);
    void on_SpinBoxDepthCal_valueChanged(double);
    void on_BtnDepthCal_clicked();
//    void on_CheckPartFileShow_clicked(bool checked);
    void on_CheckDxfFileShow_clicked(bool checked);
    void on_CheckMeasureShow_clicked(bool checked);
    void on_checkAScanShow_clicked(bool checked);
    void on_checkBScanShow_clicked(bool checked);
    void on_checkCScanShow_clicked(bool checked);
    void on_checkSScanShow_clicked(bool checked);
	void on_CheckBackShow_clicked(bool checked);
	void on_ComField1_currentIndexChanged(int index);
    void on_ComField2_currentIndexChanged(int index);
    void on_ComField3_currentIndexChanged(int index);
    void on_ComField4_currentIndexChanged(int index);
    void on_ComField5_currentIndexChanged(int index);
    void on_ComField6_currentIndexChanged(int index);
    void on_ComField7_currentIndexChanged(int index);
    void on_ComField8_currentIndexChanged(int index);
    void on_ComField9_currentIndexChanged(int index);
    void on_ComField10_currentIndexChanged(int index);
    void on_ComField11_currentIndexChanged(int index);
    void on_ComField12_currentIndexChanged(int index);
    void on_ComField13_currentIndexChanged(int index);
    void on_ComField14_currentIndexChanged(int index);

    void update_valueChanged();
    void on_ValueARef_valueChanged(double value);
    void on_ValueAMes_valueChanged(double value);
    void on_ValueURef_valueChanged(double value);
    void on_ValueUMes_valueChanged(double value);
    void on_ValueSRef_valueChanged(double value);
    void on_ValueSMes_valueChanged(double value);
    void on_ValueIRef_valueChanged(double value);
    void on_ValueIMes_valueChanged(double value);
    void on_BtnColorAmp_clicked();
    void on_BtnColorRf_clicked();
    void on_BtnColorThickness_clicked();
    void on_ComColorLineSelection_currentIndexChanged(int index);
    void on_ComColorLineColor_currentIndexChanged(int index);
    void on_CheckCursorShow_clicked(bool checked);
	void on_CheckCursorSync_clicked(bool checked);
    void on_ValueCScanThicknessMin_valueChanged(double);
    void on_ValueCScanThicknessMax_valueChanged(double);

    void on_ComCScanSource1_currentIndexChanged(int index);
    void on_ComCScanSource2_currentIndexChanged(int index);
    void on_ComCScanShowAll_currentIndexChanged(int index);
    void on_ComSscanReflect_currentIndexChanged(int index);

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

    void on_ValueCScanThicknessMin_editingFinished();
    void on_ValueCScanThicknessMax_editingFinished();
    void on_ValueScanOffset_valueChanged(double);
    void on_ValueIndexOffset_valueChanged(double);
    void on_CheckCurveShow_clicked(bool checked);

    void on_CheckCursorHide_clicked(bool checked);

    void on_CheckRLShow_clicked(bool checked);

    void on_ValueRL_valueChanged(double arg1);

    void on_ValueScannerSensitivity_valueChanged(double arg1);

    void on_CheckELShow_clicked(bool checked);

    void on_ValueEL_valueChanged(double arg1);

    void on_CheckSLShow_clicked(bool checked);

    void on_ValueSL_valueChanged(double arg1);

    void on_ValueREFGain_valueChanged(double arg1);

    void on_ValueComGain_valueChanged(double arg1);

    void on_ComStandard_currentIndexChanged(int index);

    void on_ComThickness_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_checkDefectBg_clicked(bool checked);

    void on_ValueCouplingGainCom_valueChanged(double arg1);

    void on_ComWeldRemianingHeight_activated(int index);



    void on_ComOneToOneShows_currentIndexChanged(int index);

    void on_ComsScanfMode_currentIndexChanged(int index);

private:
    Ui::DopplerGroupTab *ui;
};

#endif // DOPPLERGROUPTAB_H
