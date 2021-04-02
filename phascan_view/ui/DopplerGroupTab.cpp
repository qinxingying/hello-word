#include "DopplerGroupTab.h"
#include "ui_DopplerGroupTab.h"

#include "const.h"
#include "gHeader.h"
#include "ProcessDisplay.h"
#include "dialog/DialogColorSelect.h"
//#include "dialog/DialogWeldPartLoad.h"
#include "dialog/DialogDxfFileLoad.h"
#include "dialog/dialogweldfixdataii.h"
#include <QPushButton>
#include "defectidentify.h"

const int MAX_ITEM_QTY = 50;
extern int bHideCursor;
//  Description: 所有显示窗口类型
static const char* g_strDisplayMode[] =
{
	//**************************	HEADER
	"3D Display" ,
	"2D Display" ,
	//**************************	DISPLAY GROUP
	"All" , "Part" , "Probe and Wedge" , "Weld" , "Sonic Beams" ,
	"A SCAN" , "A-B SCAN" , "A-B SCAN" ,
	"S SCAN" , "S-A SCAN" , "S-A SCAN" , "S-A-A-A SCAN" , "S-A-A-A-C SCAN" ,
	"S-A-B SCAN" , "S-A-B SCAN" ,"S-A-B SCAN" ,
	"S-A-B-C SCAN" , "S-A-B-C SCAN" , "S-A-B-C SCAN" ,
	"S-A-C SCAN"  , "S-A-C SCAN"  ,
    "S-A-C-C SCAN"  , "S-A-C-C SCAN","S-A-B-C SCAN","S-A-C SCAN",
    "S-A-B-C SCAN"
};

DopplerGroupTab::DopplerGroupTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DopplerGroupTab)
{
	ui->setupUi(this);

	m_nGroupId = 0 ;
    m_pConfig = DopplerConfigure::Instance();
    m_pGroup  = &m_pConfig->group[m_nGroupId];
	ui->toolBox->setMinimumHeight(400);
    ui->ValueCScanThicknessMax->setMinimum(0.1);
    ui->ValueCScanThicknessMin->setMinimum(0);

    for(int i = 0; i < setup_DAC_POINT_QTY; i++){
        m_pSizingCurveName[i] = findChild<QLabel*>("LabelSizingCure" + QString::number(i + 1));
    }

    for(int i = 0; i < setup_DAC_POINT_QTY; i++){
        m_pSizingCurveValue[i] = findChild<QDoubleSpinBox*>("ValueSizingCurve" + QString::number(i + 1));
    }

    for(int i = 0; i < setup_DAC_POINT_QTY; i++){
        m_pSizingCurveUnit[i] = findChild<QLabel*>("LabelSizingCureUnit" + QString::number(i + 1));
    }

    SetWndName();

    UpdateMeasureBox();
    UpdateGroupConfig();
	ui->toolBox->setCurrentIndex(0);
    CreateSettingView();

    SetWidgetInvalide(); // 使窗口不使能  只作数据显示用
}

DopplerGroupTab::~DopplerGroupTab()
{
	delete ui;
    delete model;
}

void DopplerGroupTab::SetGroupId(int nGroupId_)
{
    m_nGroupId = nGroupId_;
    m_pGroup  = &m_pConfig->group[m_nGroupId];
    UpdateGroupConfig();
}

QToolBox* DopplerGroupTab::GetToolBox() const
{
	if(ui->toolBox)
	  return ui->toolBox ;
	else return NULL;
}

/****************************************************************************
  Description: 声速类型选择
*****************************************************************************/
void DopplerGroupTab::UpdateVelocitySelection()
{
    MATERIAL& _material = m_pGroup->part.material;
	ui->ComVelocitySelection->clear();

	QString _strTmp[3];
    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    int _iLang = _pConfig->AppEvn.eLanguage;
    _strTmp[0] = QString(_material.strName[_iLang]) ;

	_strTmp[1].sprintf("[L]%.0f" , _material.fVelocityLon) ;
	_strTmp[2].sprintf("[T]%.0f" , _material.fVelocityTran) ;

	ui->ComVelocitySelection->addItem(_strTmp[0]);
	ui->ComVelocitySelection->addItem(_strTmp[1]);
	ui->ComVelocitySelection->addItem(_strTmp[2]);
}

void DopplerGroupTab::InitComBoxMaterialSelection()
{
	QList<MATERIAL*>* _list = m_pConfig->m_listMaterial ;
	ui->ComMaterial->clear();
	QStringList _strList;

    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    int _iLang = _pConfig->AppEvn.eLanguage;

	int _nIndex = 0;
	for(int i = 0 ; i< _list->count() ; i++)
	{
		MATERIAL* _pMaterial = _list->at(i) ;
        QString _str ;
        _str.sprintf("[%s][L:%.0f][T:%.0f]" , QString(tr(_pMaterial->strName[_iLang])).toUtf8().data(),
                     _pMaterial->fVelocityLon, _pMaterial->fVelocityTran);
        _strList.append(_str);
        if(!strcmp( _pMaterial->strName[0], m_pGroup->part.material.strName[0]) )
			_nIndex= i ;
		//-------------------------------------------------------------
    }
	ui->ComMaterial->addItems(_strList);
	ui->ComMaterial->setCurrentIndex(_nIndex);
}
/****************************************************************************
  Description: 探头参数
*****************************************************************************/
void DopplerGroupTab::UpdateProbeConfig(int bIsRx_)
{
    PROBE_CONFIG& _probe = m_pGroup->probe[bIsRx_ ? 1 : 0];

	if(bIsRx_)
	{
		ui->BtnProbeSelection_2->setText(_probe.strName);
        ui->lineEdit_probeR_1->setText(QString::number((double)_probe.nElementPri, 'f', 0));
        ui->lineEdit_probeR_2->setText(QString::number((double)_probe.nElementSec, 'f', 0));
        ui->lineEdit_probeR_3->setText(QString::number((double)_probe.fSizePri, 'f', 1));
        ui->lineEdit_probeR_4->setText(QString::number((double)_probe.fSizeSec, 'f', 1));
        ui->lineEdit_probeR_5->setText(QString::number((double)_probe.fPitchPri, 'f', 1));
        ui->lineEdit_probeR_6->setText(QString::number((double)_probe.fPitchSec, 'f', 1));
        ui->lineEdit_probeR_7->setText(QString::number((double)_probe.fFrequency, 'f', 1));
	}
	else
	{
		ui->BtnProbeSelection->setText(_probe.strName);
        ui->lineEdit_probeT_1->setText(QString::number((double)_probe.nElementPri, 'f', 0));
        ui->lineEdit_probeT_2->setText(QString::number((double)_probe.nElementSec, 'f', 0));
        ui->lineEdit_probeT_3->setText(QString::number((double)_probe.fSizePri, 'f', 1));
        ui->lineEdit_probeT_4->setText(QString::number((double)_probe.fSizeSec, 'f', 1));
        ui->lineEdit_probeT_5->setText(QString::number((double)_probe.fPitchPri, 'f', 1));
        ui->lineEdit_probeT_6->setText(QString::number((double)_probe.fPitchSec, 'f', 1));
        ui->lineEdit_probeT_7->setText(QString::number((double)_probe.fFrequency, 'f', 1));
	}
}

/****************************************************************************
  Description: 楔块参数
*****************************************************************************/
void DopplerGroupTab::UpdateWedgeConfig(int bIsRx_)
{
    WEDGE_CONFIG& _wedge = m_pGroup->wedge[bIsRx_ ? 1 : 0];

	if(bIsRx_)
	{
        ui->BtnWedgeSelection_2->setText(_wedge.strName);

        ui->lineEdit_wedgeR_1->setText(QString::number((double)_wedge.fWedgeAngle, 'f', 1));
        ui->lineEdit_wedgeR_2->setText(QString::number((double)_wedge.fRoofAngle, 'f', 1));

        if(_wedge.eType){
            ui->lineEdit_wedgeR_3->setText("UT");

            ui->label_wedgeR_7->setText(tr("Reference Point:"));
            ui->label_wedgeR_8->setText(tr("Wedge Delay:"));
            ui->label_wedgeR_9->hide();

            ui->lineEdit_wedgeR_7->setText(QString::number((double)_wedge.fRefPoint, 'f', 1) + " mm");
            ui->lineEdit_wedgeR_8->setText(QString::number((double)_wedge.nWedgeDelay/1000.0, 'f', 1) + " us");
            ui->lineEdit_wedgeR_9->hide();
        }else{
            ui->lineEdit_wedgeR_3->setText(tr("PA"));
            ui->lineEdit_wedgeR_7->setText(QString::number((double)_wedge.fHeigtFirst, 'f', 1));
            ui->lineEdit_wedgeR_8->setText(QString::number((double)_wedge.fOffsetFir, 'f', 1));
            ui->lineEdit_wedgeR_9->setText(QString::number((double)_wedge.fOffsetSec, 'f', 1));
        }

        if(_wedge.eDirection){
            ui->lineEdit_wedgeR_4->setText(tr("NORMAL"));
        }else{
            ui->lineEdit_wedgeR_4->setText(tr("INVERSE"));
        }

        ui->lineEdit_wedgeR_5->setText(QString::number((double)_wedge.fVelocityLon, 'f', 0));
        ui->lineEdit_wedgeR_6->setText(QString::number((double)_wedge.fVelocityTra, 'f', 0));
	}
	else
	{
		ui->BtnWedgeSelection->setText(_wedge.strName);
        ui->lineEdit_wedgeT_1->setText(QString::number((double)_wedge.fWedgeAngle, 'f', 1));
        ui->lineEdit_wedgeT_2->setText(QString::number((double)_wedge.fRoofAngle, 'f', 1));

        if(_wedge.eType){
            ui->lineEdit_wedgeT_3->setText(tr("UT"));

            ui->label_wedgeT_7->setText(tr("Reference Point:"));
            ui->label_wedgeT_8->setText(tr("Wedge Delay:"));
            ui->label_wedgeT_9->hide();

            ui->lineEdit_wedgeT_7->setText(QString::number((double)_wedge.fRefPoint, 'f', 1) + " mm");
            ui->lineEdit_wedgeT_8->setText(QString::number((double)_wedge.nWedgeDelay/1000.0, 'f', 1) + " us");
            ui->lineEdit_wedgeT_9->hide();
        }else{
            ui->lineEdit_wedgeT_3->setText(tr("PA"));
            ui->lineEdit_wedgeT_7->setText(QString::number((double)_wedge.fHeigtFirst, 'f', 1));
            ui->lineEdit_wedgeT_8->setText(QString::number((double)_wedge.fOffsetFir, 'f', 1));
            ui->lineEdit_wedgeT_9->setText(QString::number((double)_wedge.fOffsetSec, 'f', 1));
        }

        if(_wedge.eDirection){
            ui->lineEdit_wedgeT_4->setText(tr("NORMAL"));
        }else{
            ui->lineEdit_wedgeT_4->setText(tr("INVERSE"));
        }

        ui->lineEdit_wedgeT_5->setText(QString::number((double)_wedge.fVelocityLon, 'f', 0));
        ui->lineEdit_wedgeT_6->setText(QString::number((double)_wedge.fVelocityTra, 'f', 0));

	}

}
/****************************************************************************
  Description: 聚焦法则参数
*****************************************************************************/
void DopplerGroupTab::UpdateLawConfig()
{
	LAW_CONFIG& _law = m_pGroup->law ;
	ui->ComLawType->setCurrentIndex(_law.eLawType);
	//************  angle  setting ***************
	ui->ValueRefractStart->setValue(_law.nAngleStartRefract / 10.0);
	ui->ValueRefractStep->setValue(_law.nAngleStepRefract / 10.0);
	ui->ValueRefractStop->setValue(_law.nAngleStopRefract / 10.0);
	//************************************************
	//************ focal point
	ui->ComFocalType->setCurrentIndex(_law.eFocalType);
	ui->ValueFocusPositionStart->setValue(_law.fPositionStart);
	ui->ValueFocusPositionStop->setValue(_law.fPositionStop);
	ui->ValueFocusPositionStep->setValue(_law.fPositionStep);
	ui->ValueFocusOffsetStart->setValue(_law.fOffsetStart);
	ui->ValueFocusOffsetStop->setValue(_law.fOffsetStop);
	ui->ValueFocusDepthStart->setValue(_law.fDepthStart);
	ui->ValueFocusDepthStop->setValue(_law.fDepthStop);
    ui->ValueFocalDepth->setValue(_law.fPositionStart);
	//***********************************************
	//************ element selection
	ui->ValueElementQtyPri->setValue(_law.nElemQtyFir);
	ui->ValueElementStartPri->setValue(_law.nFirstElemFir);
	ui->ValueElementStopPri->setValue(_law.nLastElemFir);
	ui->ValueElementStepPri->setValue(_law.nElemStepFir);
	ui->ValueElementQtySec->setValue(_law.nElemQtySec);
	ui->ValueElementStartSec->setValue(_law.nFirstElemSec);
	ui->ValueElementStopSec->setValue(_law.nLastElemSec);
	ui->ValueElementStepSec->setValue(_law.nElemStepSec);

	UpdateFocallawState();
}

/****************************************************************************
  Description:  探头相关设置
*****************************************************************************/
void DopplerGroupTab::UpdateProbeWedge()
{
	ui->ComGroupMode->setCurrentIndex(m_pGroup->eGroupMode);
	UpdateProbeConfig(0);
	UpdateProbeConfig(1);
	UpdateWedgeConfig(0);
	UpdateWedgeConfig(1);
}
#include <QToolTip>
#include <process/CalcMeasurement.h>
void DopplerGroupTab::slotMeasureBoxTipInfo(int nIndex_)
{
	QToolTip::hideText();
	QToolTip::showText(QCursor::pos() , QString(CalcMeasurement::GetMeasureContentString(m_nGroupId , (FEILD_VALUE_INDEX)nIndex_ ))) ;
}


/****************************************************************************
  Description: 测量类型选择
*****************************************************************************/
void DopplerGroupTab::UpdateMeasureBox()
{
    QComboBox* _field[setup_MAX_MEASURE_QTY] ;
    _field[0]  = ui->ComField1 ;
    _field[1]  = ui->ComField2 ;
    _field[2]  = ui->ComField3 ;
    _field[3]  = ui->ComField4 ;
    _field[4]  = ui->ComField5 ;
    _field[5]  = ui->ComField6 ;
    _field[6]  = ui->ComField7 ;
    _field[7]  = ui->ComField8 ;
    _field[8]  = ui->ComField9 ;
    _field[9]  = ui->ComField10;
    _field[10] = ui->ComField11;
    _field[11] = ui->ComField12;
    _field[12] = ui->ComField13;
    _field[13] = ui->ComField14;

    for(int i = 0 ; i < setup_MAX_MEASURE_QTY; i ++)
	{
		_field[i]->clear();

		for(int j = 0 ; j < FEILD_VALUE_INDEX_MAX ; j++)
		{
			_field[i]->addItem( CalcMeasurement::GetMeasureNameString(m_nGroupId , (FEILD_VALUE_INDEX)j ));
		}
		_field[i]->setCurrentIndex(m_pGroup->aeMeasureType[i]);

		connect(_field[i] , SIGNAL(highlighted(int)) , SLOT(slotMeasureBoxTipInfo(int))) ;
	}
}

void DopplerGroupTab::UpdateStandard(int selectID,int ifadd)
{
    QComboBox* _field = ui->ComThickness;
    //int i;
    if(ifadd)
    {
    if(selectID == 0)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[0]);
        _field->addItem(g_strThicknessStandard[1]);
        _field->addItem(g_strThicknessStandard[2]);
    }
    else if(selectID == 1)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[3]);
        _field->addItem(g_strThicknessStandard[4]);
        _field->addItem(g_strThicknessStandard[5]);
    }
    else if(selectID == 2)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[6]);
        _field->addItem(g_strThicknessStandard[7]);
        _field->addItem(g_strThicknessStandard[8]);
        _field->addItem(g_strThicknessStandard[9]);
        _field->addItem(g_strThicknessStandard[10]);
    }
    else if(selectID == 3)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[11]);
        _field->addItem(g_strThicknessStandard[12]);
    }
    else if(selectID == 4)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[13]);
    }
    else if(selectID == 5)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[14]);
        _field->addItem(g_strThicknessStandard[15]);
    }
    else if(selectID == 6)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[16]);
    }
    }
    _field->setCurrentIndex(m_pGroup->ThicknessType[m_nGroupId]);
    int index = _field->currentIndex();
    CUR_RES.CurRL[m_nGroupId] = g_ValuedbStandard[selectID][_field->currentIndex()][0];
    CUR_RES.CurEL[m_nGroupId] = g_ValuedbStandard[selectID][_field->currentIndex()][2];
    CUR_RES.CurSL[m_nGroupId] = g_ValuedbStandard[selectID][_field->currentIndex()][1];
    CUR_RES.Standard[m_nGroupId] = selectID;
    CUR_RES.Thickness[m_nGroupId] = _field->currentIndex();
    ui->ValueRL->setValue(CUR_RES.CurRL[m_nGroupId]);
    ui->ValueSL->setValue(CUR_RES.CurSL[m_nGroupId]);
    ui->ValueEL->setValue(CUR_RES.CurEL[m_nGroupId]);
    if(selectID == 2 && (index == 3 || index == 4)){

        ui->labelRLaperture->setText(QString::fromLocal8Bit("φ6"));
        ui->labelSLaperture->setText(QString::fromLocal8Bit("φ6"));
        ui->labelELaperture->setText(QString::fromLocal8Bit("φ6"));
    }else{
        ui->labelRLaperture->setText(QString::fromLocal8Bit("φ2"));
        ui->labelSLaperture->setText(QString::fromLocal8Bit("φ2"));
        ui->labelELaperture->setText(QString::fromLocal8Bit("φ2"));
    }
}

void DopplerGroupTab::LoadStandardFormConifg()
{
    QComboBox* _field = ui->ComThickness;
    int selectID = CUR_RES.Standard[m_nGroupId];
    ui->ComStandard->blockSignals(true);
    ui->ComStandard->setCurrentIndex(selectID);
    ui->ComStandard->blockSignals(false);
    if(selectID == 0)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[0]);
        _field->addItem(g_strThicknessStandard[1]);
        _field->addItem(g_strThicknessStandard[2]);
    }
    else if(selectID == 1)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[3]);
        _field->addItem(g_strThicknessStandard[4]);
        _field->addItem(g_strThicknessStandard[5]);
    }
    else if(selectID == 2)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[6]);
        _field->addItem(g_strThicknessStandard[7]);
        _field->addItem(g_strThicknessStandard[8]);
        _field->addItem(g_strThicknessStandard[9]);
        _field->addItem(g_strThicknessStandard[10]);
    }
    else if(selectID == 3)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[11]);
        _field->addItem(g_strThicknessStandard[12]);
    }
    else if(selectID == 4)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[13]);
    }
    else if(selectID == 5)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[14]);
        _field->addItem(g_strThicknessStandard[15]);
    }
    else if(selectID == 6)
    {
        _field->clear();
        _field->addItem(g_strThicknessStandard[16]);
    }
    int thinkness = CUR_RES.Thickness[m_nGroupId];
    _field->setCurrentIndex(thinkness);
    int index = _field->currentIndex();
    if(!m_pGroup->loadCurveData){
        CUR_RES.CurRL[m_nGroupId] = g_ValuedbStandard[selectID][_field->currentIndex()][0];
        CUR_RES.CurEL[m_nGroupId] = g_ValuedbStandard[selectID][_field->currentIndex()][2];
        CUR_RES.CurSL[m_nGroupId] = g_ValuedbStandard[selectID][_field->currentIndex()][1];
    }
    ui->ValueRL->setValue(CUR_RES.CurRL[m_nGroupId]);
    ui->ValueSL->setValue(CUR_RES.CurSL[m_nGroupId]);
    ui->ValueEL->setValue(CUR_RES.CurEL[m_nGroupId]);
    if(selectID == 2 && (index == 3 || index == 4)){

        ui->labelRLaperture->setText(QString::fromLocal8Bit("φ6"));
        ui->labelSLaperture->setText(QString::fromLocal8Bit("φ6"));
        ui->labelELaperture->setText(QString::fromLocal8Bit("φ6"));
    }else{
        ui->labelRLaperture->setText(QString::fromLocal8Bit("φ2"));
        ui->labelSLaperture->setText(QString::fromLocal8Bit("φ2"));
        ui->labelELaperture->setText(QString::fromLocal8Bit("φ2"));
    }
}

void DopplerGroupTab::setTopcWidthValue(double value)
{
    ui->ValueTopcWidth->setValue(value);
}

void DopplerGroupTab::setThicknessValue(double value)
{
    ui->ValuePartSize1->blockSignals(true);
    ui->ValuePartSize1->setValue(value);
    ui->ValuePartSize1->blockSignals(false);
}

void DopplerGroupTab::setShowCursorStatus(bool status)
{
    ui->CheckCursorShow->setChecked(status);
    on_CheckCursorShow_clicked(status);
}

void DopplerGroupTab::setShowDefectStatus(bool status)
{
    ui->CheckDefectShow->setChecked(status);
    on_CheckDefectShow_clicked(status);
}

void DopplerGroupTab::setCscanShowallChange()
{
    int index = ui->ComCScanShowAll->currentIndex();
    if(index){
        ui->ComCScanShowAll->setCurrentIndex(0);
    }else{
        ui->ComCScanShowAll->setCurrentIndex(1);
    }
}

void DopplerGroupTab::setMeasureEnable(bool status)
{
    ui->ComField1->setEnabled(status);
    ui->ComField2->setEnabled(status);
    ui->ComField3->setEnabled(status);
}

//true 显示B闸门 false显示A闸门，B闸门隐藏
void DopplerGroupTab::setShowGateB(bool status)
{
    if(status){
        m_pGroup->bShowGateB = true;
        ui->ComGateSelect->setCurrentIndex(1);
        ui->ValueGateStart->setValue(m_pGroup->gate[1].fStart);
        ui->ValueGateWidth->setValue(m_pGroup->gate[1].fWidth);
        ui->ValueGateHeight->setValue(m_pGroup->gate[1].nThreshold);
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateB ? Qt::Checked : Qt::Unchecked);
    }else{
        m_pGroup->bShowGateB = false;
        ui->ComGateSelect->setCurrentIndex(0);
        ui->ValueGateStart->setValue(m_pGroup->gate[0].fStart);
        ui->ValueGateWidth->setValue(m_pGroup->gate[0].fWidth);
        ui->ValueGateHeight->setValue(m_pGroup->gate[0].nThreshold);
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateA ? Qt::Checked : Qt::Unchecked);
    }
    ProcessDisplay _display;
    _display.UpdateAllViewOverlay();
}

/****************************************************************************
  Description: 当前角度选择控件更新
*****************************************************************************/
void DopplerGroupTab::UpdateCurrentAngleCom()
{
	ui->ComCurrentAngle->clear();
	QString _str ;
	int _nCurrentAngle = m_pGroup->law.nAngleStartRefract;
	if(m_pGroup->eGroupMode == setup_GROUP_MODE_PA && m_pGroup->law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
	{

		while(_nCurrentAngle <= m_pGroup->law.nAngleStopRefract)
		{
			_str.clear();
			_str.sprintf("%2.1f" , _nCurrentAngle / 10.0) ;
			_nCurrentAngle += m_pGroup->law.nAngleStepRefract  ;
			ui->ComCurrentAngle->addItem(_str);
		}
	}
	else
	{
		_str.sprintf("%2.1f" , _nCurrentAngle / 10.0) ;
		ui->ComCurrentAngle->addItem(_str);
	}
	int _nCurrentId  = (int)m_pGroup->afCursor[setup_CURSOR_LAW]  ;
    if(m_pGroup->law.eLawType == setup_LAW_TYPE_AZIMUTHAL)
    {
        if(_nCurrentId > ui->ComCurrentAngle->count() - 1)
        {
            _nCurrentId  = 0  ;
            m_pGroup->afCursor[setup_CURSOR_LAW] = 0;
        }
        ui->ComCurrentAngle->setCurrentIndex(_nCurrentId);
    }
}
/****************************************************************************
  Description: 采样范围
*****************************************************************************/
void DopplerGroupTab::UpdateSampleRange()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nLawId = ui->ComCurrentAngle->currentIndex() ;
	ui->ValueStart->setValue(_process->GetSampleStart(m_nGroupId , _nLawId));
	ui->ValueRange->setValue(_process->GetSampleRange(m_nGroupId , _nLawId));

    QString _Unit =  _process->GetSonicAxisUnit(m_nGroupId);
    ui->LabelStartUnit->setText(_Unit);
    ui->LabelRangeUnit->setText(_Unit);
}

void DopplerGroupTab::SetWndName()
{
	if(m_pGroup->eTxRxMode == setup_TX_RX_MODE_TOFD ) {
		ui->labelDefectOffset->hide();
		ui->labelDefectWidth->hide();
		ui->ValueDefectWStart->hide();
		ui->ValueDefectWidth->hide();
		ui->LabelCursorUnit3_11->hide();
		ui->LabelCursorUnit3_12->hide();
	} else {
		ui->labelDefectOffset->show();
		ui->labelDefectWidth->show();
		ui->ValueDefectWStart->show();
		ui->ValueDefectWidth->show();
		ui->LabelCursorUnit3_11->show();
		ui->LabelCursorUnit3_12->show();
	}

	QComboBox* _comboxTab[4];
	_comboxTab[0] = ui->ComComDisp1;
	_comboxTab[1] = ui->ComComDisp2;
	_comboxTab[2] = ui->ComComDisp3;
	_comboxTab[3] = ui->ComComDisp4;

	QString _str;
	int _nQty = m_pConfig->common.nGroupQty;
	U8* _pComDisp = m_pConfig->GetComDisplayPoint();
	for(int k = 0; k < 4; k++) {
		_comboxTab[k]->clear();
		for(int i = 0; i < _nQty; i++) {
            _str.sprintf("Group%d", i+1);
			_comboxTab[k]->addItem(_str);
		}
		_comboxTab[k]->setCurrentIndex(_pComDisp[k]);
	}

	if(_nQty < 5 && _nQty > 1) {
		ui->groupBoxComDisp->show();
		ui->BtnRefurbishComDisp->setEnabled(false);
		for(int i = 0; i < 4; i++)	{
			_comboxTab[i]->hide();
			_comboxTab[i]->setEnabled(false);
		}

		for(int i = 0; i < _nQty; i++)	{
			_comboxTab[i]->show();
		}
	} else if(_nQty == 1) {
		ui->groupBoxComDisp->hide();
	} else {
		ui->groupBoxComDisp->show();
		ui->BtnRefurbishComDisp->setEnabled(true);
		for(int i = 0; i < 4; i++)	{
			_comboxTab[i]->show();
			_comboxTab[i]->setEnabled(true);
		}
	}
}

/****************************************************************************
  Description: 窗口不可编辑
*****************************************************************************/
void DopplerGroupTab::SetWidgetInvalide()
{
    ui->ValueGain->setDisabled(true);
    ui->ValueRefGain->setDisabled(true);
    ui->ValueCoupleGain->setDisabled(true);
    ui->ValueStart->setDisabled(true);
    ui->ValueRange->setDisabled(true);
    ui->ValueWedgeDelay->setDisabled(true);
    ui->ValueVelocity->setDisabled(true);
    ui->ComCurrentAngle->setDisabled(true);
    ui->ComVelocitySelection->setDisabled(true);
    //ui->ComTravelMode->setDisabled(true);
    ui->BoxPulserReceiver->setDisabled(true);
    ui->groupBox_2->setDisabled(true);

    ui->ComGroupMode->setDisabled(true);
    ui->BoxProbeTrigger->setDisabled(true);
    ui->BoxWedgeTrigger->setDisabled(true);
    ui->BoxProbeTrigger_2->setDisabled(true);
    ui->BoxWedgeTrigger_2->setDisabled(true);

    ui->FocalLaw->setDisabled(true);

    ui->ComGateSync->setDisabled(false);
    ui->ComGateMeasure->setDisabled(false);

    ui->ValueSizingCurve1->setDisabled(true);
    ui->ValueSizingCurve2->setDisabled(true);
    ui->ValueSizingCurve3->setDisabled(true);
    ui->ValueSizingCurve4->setDisabled(true);
    ui->ValueSizingCurve5->setDisabled(true);
    ui->ValueSizingCurve6->setDisabled(true);
    ui->ValueSizingCurve7->setDisabled(true);
    ui->ValueSizingCurve8->setDisabled(true);
    ui->ValueSizingCurve9->setDisabled(true);
    ui->ValueSizingCurve10->setDisabled(true);
    ui->ValueSizingCurve11->setDisabled(true);
    ui->ValueSizingCurve12->setDisabled(true);
    ui->ValueSizingCurve13->setDisabled(true);
    ui->ValueSizingCurve14->setDisabled(true);
    ui->ValueSizingCurve15->setDisabled(true);
    ui->ValueSizingCurve16->setDisabled(true);

    ui->ComGeometry->setDisabled(true);
    ui->ComMaterial->setDisabled(true);
    ui->ValuePartSize2->setDisabled(true);
    ui->ValuePartSize3->setDisabled(true);
    ui->ValuePartSize4->setDisabled(true);
    ui->CheckUnifiedPartSetting->setDisabled(true);

    ui->ValueARef->setDisabled(true);
    ui->ValueAMes->setDisabled(true);
    ui->lineEditReMark->setDisabled(true);
    ui->ValueDefectLStart->setDisabled(true);
    ui->ValueDefectLength->setDisabled(true);
    ui->ValueDefectHStart->setDisabled(true);
    ui->ValueDefectHeight->setDisabled(true);
    ui->ValueDefectWStart->setDisabled(true);
    ui->ValueDefectWidth->setDisabled(true);

    ui->ComColorLineColor->setDisabled(true);
    ui->ComColorLineSelection->setDisabled(true);
}

#include <QStandardItemModel>
#include <QMimeData>
#include <QDrag>

/****************************************************************************
  Description: 显示类型窗口创建
*****************************************************************************/
void DopplerGroupTab::CreateSettingView()
{
	model = new QStandardItemModel(2,1);
	model->setHeaderData(0, Qt::Horizontal, tr("Display Mode"));
	QStandardItem* _pItems[MAX_ITEM_QTY]  ;
	int i;
	int _nQty = sizeof(g_strDisplayMode) / sizeof(int) ;
    for( i = 0 ; i < _nQty-2; i++)
	{        
        int t = i;
        if(i >= 13)
            t=i+2;
        _pItems[i] = new QStandardItem(tr(g_strDisplayMode[t]));
        QString str = QString(":/file/resource/display/0-");
        QString tmp; tmp.sprintf("%02d.png", t+1) ;
		str += tmp ;
		QByteArray array = str.toLatin1() ;
		_pItems[i]->setIcon(QIcon(array.data()));
		_pItems[i]->setData(i , Qt::UserRole);
	}

	model->setItem(0, 0, _pItems[0]);
	model->setItem(1, 0, _pItems[1]);

	for(i = 2 ; i< 3 ; i++)
	{
		_pItems[0]->appendRow(_pItems[i]);
	}
	//----------------------------------------
    for(i = 7 ; i< _nQty-2 ; i++)
	{
		_pItems[1]->appendRow(_pItems[i]);
	}


	QTreeView *tree = ui->treeView;
	tree->setModel (model);
	tree->expandAll();
	tree->viewport()->setAttribute(Qt::WA_StaticContents);
	connect(tree , SIGNAL(pressed(QModelIndex)) , SLOT(StartDrags(QModelIndex)))  ;
}
/****************************************************************************
  Description: 显示类型窗口  拖拽响应函数
*****************************************************************************/
void DopplerGroupTab::StartDrags(QModelIndex index)
{
	// Get item string and id
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	const QAbstractItemModel* model = index.model() ;
	QString _str1  = model->data(index , Qt::DisplayRole).toString()  ;
    int _nId = model->data(index , Qt::UserRole).toInt();
	QVariant icon = model->data(index , Qt::DecorationRole);
	QPixmap pixmap =  (icon.value<QIcon>()).pixmap(48 , 48);

	// setup MimeData
	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	dataStream << _str1 << _nId << m_nGroupId;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("DOPPLER_DISPLAY_ITEM", itemData);

    //DopplerConfigure::setSetting(m_nGroupId,"DISP_MODE",_nId);
    _pConfig->group[m_nGroupId].DisplayMode = _nId;

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);

	drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
	drag->setPixmap(pixmap);
	drag->exec() ; //(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
}

void DopplerGroupTab::UpdateColorSetting()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	void* _pColor = _process->GetPalete(m_nGroupId , PALETTE_AMP) ;
	ui->BtnColorAmp->SetColorIndex(_pColor);
	_pColor = _process->GetPalete(m_nGroupId , PALETTE_RECTIFY) ;
	ui->BtnColorRf->SetColorIndex(_pColor);
	_pColor = _process->GetPalete(m_nGroupId , PALETTE_THICKNESS) ;
	ui->BtnColorThickness->SetColorIndex(_pColor);
}

/****************************************************************************
  Description: 光标参数同步
*****************************************************************************/
void DopplerGroupTab::UpdateCursorValue()
{
	ui->ValueARef->setValue(m_pGroup->afCursor[setup_CURSOR_A_REF]);
	ui->ValueAMes->setValue(m_pGroup->afCursor[setup_CURSOR_A_MES]);
	ui->ValueURef->setValue(m_pGroup->afCursor[setup_CURSOR_U_REF]);
    ui->ValueUMes->setValue(m_pGroup->afCursor[setup_CURSOR_U_MES]);
	ui->ValueSRef->setValue(m_pGroup->afCursor[setup_CURSOR_S_REF]);
	ui->ValueSMes->setValue(m_pGroup->afCursor[setup_CURSOR_S_MES]);
	ui->ValueIRef->setValue(m_pGroup->afCursor[setup_CURSOR_I_REF]);
	ui->ValueIMes->setValue(m_pGroup->afCursor[setup_CURSOR_I_MES]);

    SCANNER& _scanner = m_pConfig->common.scanner;
    if(_scanner.eScanEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelCursorUnit5->setText("sec");
		ui->LabelCursorUnit6->setText("sec");
	} else {
		ui->LabelCursorUnit5->setText("mm");
		ui->LabelCursorUnit6->setText("mm");
	}

    ParameterProcess* _process = ParameterProcess::Instance();
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
    _process->GetTofdDepth(m_nGroupId, 1, &_tofd->fDepthCal);
	ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);
}

void DopplerGroupTab::UpdateDefectBox()
{
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _iCnt = _pConfig->GetDefectCnt(m_nGroupId);

	QComboBox* _pBox = ui->ComDefectIndex;
	_pBox->clear();
	if(_iCnt == 0)
	{
		_pBox->addItem(QString("NULL"));
		_pBox->setEnabled(false);
    }else{
		QString _str;
		int _index = _pConfig->m_dfParam[m_nGroupId].index;

		for(int i = 0 ; i < _iCnt ; i ++)
		{
            int index = _pConfig->GetDefectIndex(m_nGroupId, i);
            _str.sprintf("%d", index);
			_pBox->addItem(_str);
		}
		_pBox->setCurrentIndex(_index);
		_pBox->setEnabled(true);
	}

	ui->CheckDefectShow->setChecked(m_pGroup->bShowDefect ? Qt::Checked : Qt::Unchecked);
}

void DopplerGroupTab::UpdateDefectValue()
{
    DopplerConfigure* pConfig = DopplerConfigure::Instance();
    int _iCnt = pConfig->GetDefectCnt(m_nGroupId);

    if(_iCnt > 0){
        int _index = pConfig->m_dfParam[m_nGroupId].index;

		if(_index < 0)		_index = 0;
		if(_index >= _iCnt) _index = _iCnt - 1;

        char *_pInfo = pConfig->GetDefectInfo(m_nGroupId, _index);
		ui->lineEditReMark->setText(QString(tr(_pInfo)));
		ui->lineEditReMark->setEnabled(true);

		float _fStart = 0;
		float  _fData = 0;
        _fData = pConfig->DefectLengthValue(m_nGroupId, &_fStart, _index);

        if(_fData >= 0){
            ui->ValueDefectLStart->setValue(_fStart);
			ui->ValueDefectLength->setValue(_fData);
		}

        _fData = pConfig->DefectHeightValue(m_nGroupId, &_fStart, _index);

        if(_fData >= 0){
            float _fDepth = pConfig->DefectDepthValue(m_nGroupId, _index);

            if(_fDepth >= 0){
				_fStart = _fDepth;
			}

			ui->ValueDefectHStart->setValue(_fStart);
			ui->ValueDefectHeight->setValue(_fData);
		}

        _fData = pConfig->DefectWidthValue(m_nGroupId, &_fStart, _index);

        if(_fData >= 0){
			ui->ValueDefectWStart->setValue(_fStart);
			ui->ValueDefectWidth->setValue(_fData);
		}
    }else{
		ui->ValueDefectLStart->setValue(0);
		ui->ValueDefectLength->setValue(0);
		ui->ValueDefectHStart->setValue(0);
		ui->ValueDefectHeight->setValue(0);
		ui->ValueDefectWStart->setValue(0);
		ui->ValueDefectWidth->setValue(0);
	}
}

/****************************************************************************
  Description: 组参数同步
*****************************************************************************/
void DopplerGroupTab::UpdateGroupConfig()
{
    //blockSignals(true);
	ParameterProcess* _process = ParameterProcess::Instance();
    if(m_pGroup->eTxRxMode == setup_TX_RX_MODE_TOFD)
    {
        ui->ValueComGain->setDisabled(true);
    }
	ui->ValueGain->setValue(m_pGroup->fGain) ;
    ui->ValueRefGain->setValue(m_pGroup->RefGain);
    ui->ValueCoupleGain->setValue(m_pGroup->CoupleGain);
    ui->ValueREFGain->setMinimum(0-m_pGroup->fGain-m_pGroup->RefGain-CUR_RES.Com_Gain[m_nGroupId]);
    ui->ValueComGain->setMinimum(0-m_pGroup->fGain-m_pGroup->RefGain-CUR_RES.REF_Gain[m_nGroupId]);
    ui->ValueREFGain->setValue(CUR_RES.REF_Gain[m_nGroupId]);
    ui->ValueComGain->setValue(CUR_RES.Com_Gain[m_nGroupId]);    
    ui->ValueRL->setValue(CUR_RES.CurRL[m_nGroupId]);
    ui->ValueSL->setValue(CUR_RES.CurSL[m_nGroupId]);
    ui->ValueEL->setValue(CUR_RES.CurEL[m_nGroupId]);
    //qDebug()<<"885"<<CUR_RES.CurSS[m_nGroupId];
    ui->ValueScannerSensitivity->setValue(CUR_RES.CurSS[m_nGroupId]);
	UpdateCurrentAngleCom();
	UpdateSampleRange();
	ui->ValueWedgeDelay->setValue(m_pGroup->nWedgeDelay / 1000.0);
    ui->ValueVelocity->setValue(m_pGroup->fVelocity);
	ui->ComTravelMode->setCurrentIndex(m_pGroup->eTravelMode);
	ui->ComTxRxMode->setCurrentIndex(m_pGroup->eTxRxMode);
//    if( m_pGroup->eGroupMode == setup_GROUP_MODE_UT1 || m_pGroup->eGroupMode == setup_GROUP_MODE_UT2){
//        ui->ComTravelMode->setEnabled(true);
//    }else{
//        ui->ComTravelMode->setEnabled(false);
//    }

    UpdateVelocitySelection();
	ui->ValuePulser->setValue(m_pGroup->nTrigeStart);
	ui->ValueReceiver->setValue(m_pGroup->nReceiveStart);
	ui->ComFilter->setCurrentIndex(m_pGroup->eFileter);
	ui->ComRectifier->setCurrentIndex(m_pGroup->eRectifier);
	ui->CheckVideoFilter->setCheckState(m_pGroup->bVedioFilter?Qt::Checked :Qt::Unchecked);
	ui->ValuePointQty->setValue(m_pGroup->nPointQty);
	//ui->ValuePointQty->setEnabled(!m_pGroup->bPointQtyAuto);
	ui->CheckPointQtyAuto->setCheckState(m_pGroup->bPointQtyAuto ? Qt::Checked : Qt::Unchecked);
	ui->ValueSumGain->setValue(m_pGroup->fSumGain);
	//ui->ValueSumGain->setEnabled(!m_pGroup->bSumGainAuto);
	ui->CheckSumGainAuto->setCheckState(m_pGroup->bSumGainAuto ?Qt::Checked :Qt::Unchecked );
	ui->ComAverage->setCurrentIndex(m_pGroup->eAveraging);

	//********** Probe and Wedge **********//
	UpdateProbeWedge() ;

	//**********	Focallaw	***************//
	UpdateLawConfig();

	//**********   Gate and Sizeing curves
	int _nGate = ui->ComGateSelect->currentIndex() ;
	GATE_CONFIG& gate = m_pGroup->gate[_nGate] ;
    if(_nGate == 0)
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateA ? Qt::Checked : Qt::Unchecked);
    else if(_nGate == 1)
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateB ? Qt::Checked : Qt::Unchecked);
    else if(_nGate == 2)
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateI ? Qt::Checked : Qt::Unchecked);
    //ui->CheckGateShow->setCheckState(m_pGroup->bShowGate ? Qt::Checked : Qt::Unchecked);
	ui->ValueGateStart->setValue(gate.fStart);
	ui->ValueGateWidth->setValue(gate.fWidth);
	ui->ValueGateHeight->setValue(gate.nThreshold);
    ui->ComGateMode->setCurrentIndex(gate.gTravelMode);
    if(m_pGroup->part.eGeometry == setup_PART_GEOMETRY_FLAT){
        ui->ComGateMode->setEnabled(true);
    }else{
        ui->ComGateMode->setEnabled(false);
    }
	ui->ComGateSync->setCurrentIndex(gate.eSynChro);
	ui->ComGateMeasure->setCurrentIndex(gate.eMeasure);
	UpdateSizeingCurves();

    if( m_pGroup->TopCInfo.TOPCValid){
        ui->ComCscanType->setEnabled(true);
        ui->ValueTopcWidth->setEnabled(true);
        if(m_pGroup->TopCInfo.TOPCStatus){
            ui->ComCscanType->setCurrentIndex(1);
        }else{
            ui->ComCscanType->setCurrentIndex(0);
        }
        ui->ValueTopcWidth->setValue(m_pGroup->TopCInfo.TOPCWidth);
    }else{
        ui->ComCscanType->setEnabled(false);
        ui->ValueTopcWidth->setEnabled(false);
        ui->ComCscanType->setCurrentIndex(0);
    }

    if( m_pConfig->common.TOPCMergeValid){
        ui->ComTopCMergeRefer->setEnabled(true);
        ui->ComTopCMergeRefer->clear();
        int buff = 0;
        for(int i = 0, j = 0; i < m_pConfig->common.TOPCMergeQty; i++){
            if(m_pConfig->common.TOPCMergeGroupId[i] != m_nGroupId){
                ui->ComTopCMergeRefer->addItem(QString("%1").arg(m_pConfig->common.TOPCMergeGroupId[i]+ 1));
                if( m_pConfig->common.TOPCMergeGroupId[i] == m_pGroup->TopCInfo.TOPCMergeRefer){
                    buff = j;
                }
                j++;
            }
        }
        ui->ComTopCMergeRefer->setCurrentIndex(buff);

        ui->ComTopcMergeStatus->setEnabled(true);
        ui->ComTopcMergeStatus->setCurrentIndex(m_pGroup->TopCInfo.TOPCMergeStatus);
    }else{
        ui->ComTopCMergeRefer->setEnabled(false);
        ui->ComTopCMergeRefer->clear();
        ui->ComTopCMergeRefer->addItem("NULL");

        ui->ComTopcMergeStatus->setEnabled(false);
        ui->ComTopcMergeStatus->setCurrentIndex(0);
    }

    if(m_pGroup->loadCurveData) {
        ui->ValueScannerSensitivity->setEnabled(false);
    }else{
        ui->ValueScannerSensitivity->setEnabled(true);
    }

    //  ********** geometry  ***************//
	InitComBoxMaterialSelection() ;
	ui->ComGeometry->setCurrentIndex(m_pGroup->part.eGeometry);
	UpdateGeometryState();
	ui->CheckShowThickness->setCheckState(m_pGroup->bShowThickness ? Qt::Checked : Qt::Unchecked );
	ui->CheckUnifiedPartSetting->setCheckState(m_pConfig->common.bUnifiedPart ? Qt::Checked : Qt::Unchecked);
	//if(m_nGroupId && m_pConfig->common.bUnifiedPart)   ui->BoxPart->setEnabled(false);
    SCANNER& _scan = m_pConfig->common.scanner;
    if(_scan.eScanEncoderType == setup_ENCODER_TYPE_TIMER)
    {
        //ui->ValueScanOffset->setEnabled(false);
        double buff = m_pGroup->fScanOffset/_scan.fPrf;
        ui->ValueScanOffset->setValue(buff);
    }
    else
    {
        //ui->ValueScanOffset->setEnabled(true);
        ui->ValueScanOffset->setValue(m_pGroup->fScanOffset);
    }

    ui->ValueIndexOffset->setValue(m_pGroup->fIndexOffset);
	ui->ComSkewAngle->setCurrentIndex(m_pGroup->eSkew);
//	ui->CheckPartFileShow->setChecked(_process->GetShowWeldPart(m_nGroupId));
    ui->CheckDxfFileShow->setChecked(_process->GetShowWeldPart(m_nGroupId));

	SCANNER& _scanner = m_pConfig->common.scanner ;
    if(_scanner.eScanEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelScanOffsetUnit->setText("sec");
	} else {
		ui->LabelScanOffsetUnit->setText("mm");
	}

	UpdateTofdParam();

	//*********** measure
	ui->CheckMeasureShow->setCheckState(m_pGroup->bShowMeasure ? Qt::Checked : Qt::Unchecked );
    ui->checkAScanShow->setCheckState(m_pGroup->bShowAScanMeasure ? Qt::Checked : Qt::Unchecked);
    ui->checkBScanShow->setCheckState(m_pGroup->bShowBScanMeasure ? Qt::Checked : Qt::Unchecked);
    ui->checkCScanShow->setCheckState(m_pGroup->bShowCScanMeasure ? Qt::Checked : Qt::Unchecked);
    ui->checkSScanShow->setCheckState(m_pGroup->bShowSScanMeasure ? Qt::Checked : Qt::Unchecked);

	//ui->CheckBackShow->setCheckState(g_pMainWnd->ParamBackMode() ? Qt::Checked : Qt::Unchecked );
	//ui->CheckBackShow->setChecked(g_pMainWnd->ParamBackMode()); //放开程序崩溃
	ui->ComField1->setCurrentIndex(m_pGroup->aeMeasureType[0]);
	ui->ComField2->setCurrentIndex(m_pGroup->aeMeasureType[1]);
	ui->ComField3->setCurrentIndex(m_pGroup->aeMeasureType[2]);
	ui->ComField4->setCurrentIndex(m_pGroup->aeMeasureType[3]);
	ui->ComField5->setCurrentIndex(m_pGroup->aeMeasureType[4]);
    ui->ComField6->setCurrentIndex(m_pGroup->aeMeasureType[5]);
    ui->ComField7->setCurrentIndex(m_pGroup->aeMeasureType[6]);
    ui->ComField8->setCurrentIndex(m_pGroup->aeMeasureType[7]);
    ui->ComField9->setCurrentIndex(m_pGroup->aeMeasureType[8]);
    ui->ComField10->setCurrentIndex(m_pGroup->aeMeasureType[9]);
    ui->ComField11->setCurrentIndex(m_pGroup->aeMeasureType[10]);
    ui->ComField12->setCurrentIndex(m_pGroup->aeMeasureType[11]);
    ui->ComField13->setCurrentIndex(m_pGroup->aeMeasureType[12]);
    ui->ComField14->setCurrentIndex(m_pGroup->aeMeasureType[13]);

	//*********** measure
	ui->CheckCursorShow->setCheckState(m_pGroup->bShowCursor ? Qt::Checked : Qt::Unchecked );
	ui->CheckCursorSync->setCheckState(m_pConfig->AppEvn.bSAxisCursorSync ? Qt::Checked : Qt::Unchecked );
    UpdateCursorValue();
    UpdateDefectValue();

	ui->ComColorLineSelection->setCurrentIndex(0);
	ui->ComColorLineColor->setCurrentIndex(m_pGroup->color.anColor[0]);
	ui->ComCScanSource1->setCurrentIndex(m_pGroup->eCScanSource[0]);
	ui->ComCScanSource2->setCurrentIndex(m_pGroup->eCScanSource[1]);
	ui->ValueCScanThicknessMin->setValue(m_pGroup->fMinThickness);
	ui->ValueCScanThicknessMax->setValue(m_pGroup->fMaxThickness);
    if(m_pGroup->CScanShowAll == true){
        ui->ComCScanShowAll->setCurrentIndex(1);
    }else{
        ui->ComCScanShowAll->setCurrentIndex(0);
    }

	UpdateColorSetting();
	UpdateMeasureBox();
	UpdateDefectBox();
	UpdateParameterLimit();
    //blockSignals(false);
}
void DopplerGroupTab::UpdateTofdParam()
{
	ui->LabelTofdPcsCal->hide();
	ui->SpinBoxCalPCS->hide();
	ui->LabelCalPCSUnit->hide();

	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
	{
		ui->BoxPartTofd->hide();
        ui->scrollGeometry->setMinimumHeight(450);
        ui->scrollGeometry->resize(ui->scrollGeometry->width(), 450);
    }else{
		ui->BoxPartTofd->show();
        ui->scrollGeometry->setMinimumHeight(760);
        ui->scrollGeometry->resize(ui->scrollGeometry->width(), 760);
		ui->CheckLwBwShow->setChecked(m_pGroup->bShowLwBw);

		SCANNER& _scaner = m_pConfig->common.scanner ;
		ui->ComBoxScanMode->setCurrentIndex(_scaner.eScanMode);
		ui->ComBoxProMode->setCurrentIndex(m_pConfig->AppEvn.iTofdDataProMode);

		TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
		ui->SpinBoxWedgeSeperation->setValue(_tofd->fWedgeSep);
		ui->SpinBoxPCS->setValue(_tofd->fPCS);
		ui->SpinBoxCalPCS->setValue(_tofd->fPcs);
		ui->SpinBoxZeroOff->setValue(_tofd->fZeroOff);
		ui->SpinBoxDepthStart->setValue(_tofd->fLayerStart);
		ui->SpinBoxDepthEnd->setValue(_tofd->fLayerEnd);
	}
}

void DopplerGroupTab::UpdateSizeingCurves()
{
	ParameterProcess* _process = ParameterProcess::Instance();

    ui->CheckCurveShow->setCheckState(m_pGroup->bShowCurve ? Qt::Checked : Qt::Unchecked);
    ui->CheckRLShow->setCheckState(CUR_RES.bShowRL ? Qt::Checked : Qt::Unchecked);
    ui->CheckELShow->setCheckState(CUR_RES.bShowEL ? Qt::Checked : Qt::Unchecked);
    ui->CheckSLShow->setCheckState(CUR_RES.bShowSL ? Qt::Checked : Qt::Unchecked);

    ui->ComSizingCurve->setEnabled(false);
	ui->ComCurvePointId->setEnabled(false);

	ui->BtnAddPoint->setEnabled(false);
	ui->BtnDelPoint->setEnabled(false);

	for(int i = 0; i < setup_DAC_POINT_QTY; i++) {
		m_pSizingCurveValue[i]->setEnabled(false);

		m_pSizingCurveName[i]->hide();
		m_pSizingCurveValue[i]->hide();
		m_pSizingCurveUnit[i]->hide();
	}

	CURVES& _curve = m_pGroup->curve;

    if(_curve.eType == setup_CURVE_TYPE_LINEAR_DAC) {
        m_pSizingCurveName[0]->setText(QString(tr("Mat. Atten:")));
        m_pSizingCurveName[1]->setText(QString(tr("Delay:")));
    } else {
        m_pSizingCurveName[0]->setText(QString(tr("Ref Amplitude:")));
        m_pSizingCurveName[1]->setText(QString(tr("Ref Amplitude:")));
    }

	int _nLawId  = (int)m_pGroup->afCursor[setup_CURSOR_LAW]  ;
	switch(_curve.eType)
	{
	case setup_CURVE_TYPE_DAC:
		for(int i = 0; i < _curve.nPointQty; i++)
		{
			m_pSizingCurveName[i]->show();
			m_pSizingCurveValue[i]->show();
			m_pSizingCurveUnit[i]->show();

			m_pSizingCurveValue[i]->setDecimals(1);
			m_pSizingCurveValue[i]->setValue(_process->GetSizingCurveRefAmp(m_nGroupId, _nLawId,  i+1));
			m_pSizingCurveUnit[i]->setText(QString(tr("%")));
		}
		break;
	case setup_CURVE_TYPE_LINEAR_DAC:
		for(int i = 0; i < 2; i++)
		{
			m_pSizingCurveName[i]->show();
			m_pSizingCurveValue[i]->show();
			m_pSizingCurveUnit[i]->show();

			m_pSizingCurveValue[i]->setDecimals(2);
			m_pSizingCurveValue[i]->setValue(_process->GetSizingCurveRefAmp(m_nGroupId, _nLawId,  i));
		}

		m_pSizingCurveUnit[0]->setText(QString(tr("dB/mm")));
		m_pSizingCurveUnit[1]->setText(QString(tr("mm")));
		break;
	case setup_CURVE_TYPE_TCG:
		for(int i = 0; i < _curve.nPointQty; i++)
		{
			m_pSizingCurveName[i]->show();
			m_pSizingCurveValue[i]->show();
			m_pSizingCurveUnit[i]->show();

			m_pSizingCurveValue[i]->setDecimals(1);
			m_pSizingCurveValue[i]->setValue(_process->GetSizingCurveRefAmp(m_nGroupId, _nLawId,  i+1));
			m_pSizingCurveUnit[i]->setText(QString(tr("dB")));
		}
		break;
	default:
		break;
	}

    if(m_pSizingCurveValue[0]->isHidden()) {
        ui->scrollAreaGateAndCurve->setMinimumHeight(450);
    } else {
        ui->scrollAreaGateAndCurve->setMinimumHeight(800);
    }

	ui->ComSizingCurve->setCurrentIndex((int)_curve.eType);
	ui->ComCurvePointId->clear();
	char strBuf[256];
	for(int i = 0; i < _curve.nPointQty; i++) {
		sprintf(strBuf, "%d", i+1);
		ui->ComCurvePointId->addItem(QString(QObject::tr(strBuf)));
	}
    ui->ComCurvePointId->setCurrentIndex(_curve.nPointPos);
}

/****************************************************************************
  Description: 参数极限更新
*****************************************************************************/
#include <process/Limitation.h>
void DopplerGroupTab::UpdateParameterLimit()
{
    Limitation _limit;

    //ui->ValueGain->setMaximum(_limit.GetGroupGainMax(m_nGroupId));
    //ui->ValueGain->setMinimum(_limit.GetGroupGainMin(m_nGroupId));
	// Start & Range
	ui->ValueStart->setMaximum(_limit.GetGroupSampleRangeMax(m_nGroupId));
	ui->ValueRange->setMaximum(_limit.GetGroupSampleRangeMax(m_nGroupId) - ui->ValueStart->value());
}


/****************************************************************************
  Description: 聚焦法则类型
*****************************************************************************/
void DopplerGroupTab::UpdateFocallawState()
{
    ui->ComAngleType->setCurrentIndex(0);

	if(ui->ComLawType->currentIndex() == 0) // angle
	{ // angle
		ui->ValueElementStopPri->setValue(ui->ValueElementQtyPri->value() + ui->ValueElementStartPri->value() - 1 );
    }
}

/****************************************************************************
  Description: 工件类型 参数
*****************************************************************************/
void DopplerGroupTab::UpdateGeometryState()
{
	setup_PART_GEOMETRY _eGeometry =  (setup_PART_GEOMETRY)ui->ComGeometry->currentIndex();
	if(_eGeometry == setup_PART_GEOMETRY_FLAT)
	{
        ui->LabelPartSize1->setText(QString(tr("Thickness:")));
        ui->LabelPartSize2->setText(QString(tr("Length:")));
        ui->LabelPartSize3->setText(QString(tr("Width:")));
    }else{
        ui->LabelPartSize1->setText(QString(tr("Inner Diameter:")));
        ui->LabelPartSize2->setText(QString(tr("Outer Diameter:")));
        ui->LabelPartSize3->setText(QString(tr("Length:")));
	}

	ui->ValuePartSize1->setValue(m_pGroup->part.afSize[0]);
	ui->ValuePartSize2->setValue(m_pGroup->part.afSize[1]);
	ui->ValuePartSize3->setValue(m_pGroup->part.afSize[2]);
    ui->ValuePartSize4->setValue(m_pGroup->part.afSize[3]);
}

void DopplerGroupTab::on_ValueGain_editingFinished()
{
	double _fValue = ui->ValueGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGain(m_nGroupId , _fValue) ;
}


//void DopplerGroupTab::on_ValueStart_editingFinished()
//{
//	double _fValue = ui->ValueStart->value() ;
//	ParameterProcess* _process = ParameterProcess::Instance();

//	if(ui->ComTravelMode->currentIndex() == 0)
//	{
//		int _nLawId = ui->ComCurrentAngle->currentIndex() ;
//		float _fAngle = _process->GetLawAngle(m_nGroupId , _nLawId) ;
//		_fValue = _fValue / cos(DEGREE_TO_ARCH(_fAngle))  ;
//	}

//	_process->SetupSampleStart(m_nGroupId , _fValue) ;
//	ProcessDisplay _display ;
//	_display.UpdateAllViewOfGroup(m_nGroupId);
//}

//void DopplerGroupTab::on_ValueRange_editingFinished()
//{
//	double _fValue = ui->ValueRange->value() ;
//	ParameterProcess* _process = ParameterProcess::Instance();

//	if(ui->ComTravelMode->currentIndex() == 0)
//	{
//		int _nLawId = ui->ComCurrentAngle->currentIndex() ;
//		float _fAngle = _process->GetLawAngle(m_nGroupId , _nLawId) ;
//		_fValue = _fValue / cos(DEGREE_TO_ARCH(_fAngle))  ;
//	}
//	_process->SetupSampleRange(m_nGroupId , _fValue ) ;

//	ProcessDisplay _display ;
//	_display.UpdateAllViewOfGroup(m_nGroupId);
//}

void DopplerGroupTab::on_ComCurrentAngle_currentIndexChanged(int index)
{
	if(!ui->ComCurrentAngle->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupCurrentLawCursor(m_nGroupId , index) ;
	UpdateSampleRange();
}

void DopplerGroupTab::on_ComTravelMode_currentIndexChanged(int index)
{
	if(!ui->ComTravelMode->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
    if( m_pGroup->eGroupMode == setup_GROUP_MODE_PA){
//        if(index == 2){
//            ui->ComTravelMode->setCurrentIndex(0);
//            return;
//        }
        _process->SetupTravelMode(m_nGroupId , index);
        UpdateSampleRange();
        ProcessDisplay _display;
        _display.UpdateAllViewOfGroupAndScanDraw(m_nGroupId, true);
    }else{//ut
        if(index == 1){
            ui->ComTravelMode->setCurrentIndex(0);
            return;
        }
        _process->SetupTravelMode(m_nGroupId , index);
        UpdateSampleRange();
        ProcessDisplay _display;
        _display.UpdateAllViewOfGroup(m_nGroupId);
    }    
}

void DopplerGroupTab::on_ValueVelocity_editingFinished()
{
	double _fValue = ui->ValueVelocity->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupVelocity(m_nGroupId , _fValue) ;
}

void DopplerGroupTab::on_ValueWedgeDelay_editingFinished()
{
	double _fValue = ui->ValueWedgeDelay->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupVelocity(m_nGroupId , _fValue) ;
}

void DopplerGroupTab::on_ComVelocitySelection_currentIndexChanged(int index)
{
	if(!ui->ComVelocitySelection->hasFocus())  return ;
	if(!index)  return  ;

	ParameterProcess* _process = ParameterProcess::Instance();
	float _fValue  = _process->GetMaterialVelocity(m_nGroupId , index - 1 ) ;
	ui->ValueVelocity->setValue(_fValue);
	_process->SetupVelocity(m_nGroupId , _fValue) ;
	ui->ComVelocitySelection->setCurrentIndex(0);
}

void DopplerGroupTab::on_ValuePulser_editingFinished()
{
	int _nValue = ui->ValuePulser->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupTxElementStart(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ValueReceiver_editingFinished()
{
	int _nValue = ui->ValuePulser->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupRxElementStart(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ComFilter_currentIndexChanged(int)
{
	if(!ui->ComFilter->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nValue = ui->ComFilter->currentIndex() ;
	_process->SetupFilter(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ComRectifier_currentIndexChanged(int)
{
	if(!ui->ComRectifier->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nValue = ui->ComRectifier->currentIndex() ;
	_process->SetupRectifier(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_CheckVideoFilter_clicked(bool checked)
{
	if(!ui->CheckVideoFilter->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupRectifier(m_nGroupId , checked) ;
}

void DopplerGroupTab::on_ValuePointQty_editingFinished()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	int _nValue = ui->ValuePointQty->value() ;
	_process->SetupPointQty(m_nGroupId , _nValue) ;
}

void DopplerGroupTab::on_ValueSumGain_editingFinished()
{
	double _fValue = ui->ValueSumGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupSumGain(m_nGroupId , _fValue) ;
}

void DopplerGroupTab::on_ComAverage_currentIndexChanged(int index)
{
	if(!ui->ComAverage->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupAverage(m_nGroupId , index) ;
}

void DopplerGroupTab::on_ComGroupMode_currentIndexChanged(int index)
{
	if(!ui->ComGroupMode->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGroupMode(m_nGroupId , index) ;
	UpdateGroupConfig();
}

void DopplerGroupTab::on_CheckPointQtyAuto_toggled(bool checked)
{
	if(!ui->CheckPointQtyAuto->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPointQtyAutoMode(m_nGroupId , checked) ;
	ui->ValuePointQty->setEnabled(!checked);
}

void DopplerGroupTab::on_CheckSumGainAuto_toggled(bool checked)
{
	if(!ui->CheckSumGainAuto->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupSumGainAutoMode(m_nGroupId , checked) ;
	ui->ValueSumGain->setEnabled(!checked);
}

void DopplerGroupTab::on_ComLawType_currentIndexChanged(int)
{
	if(!ui->ComLawType->hasFocus())  return ;
	UpdateFocallawState() ;
}

void DopplerGroupTab::on_BtnProcessLaw_clicked()
{
	LAW_CONFIG _law ;
	_law.eLawType = (setup_LAW_TYPE)ui->ComLawType->currentIndex();

	_law.nAngleStartRefract = ui->ValueRefractStart->value() * 10 ;
	_law.nAngleStepRefract = ui->ValueRefractStep->value() * 10 ;
	_law.nAngleStopRefract = ui->ValueRefractStop->value() * 10 ;

    //************ focal point***************//
	_law.eFocalType	 = (setup_FOCAL_TYPE)ui->ComFocalType->currentIndex() ;
	_law.fPositionStart = ui->ValueFocusPositionStart->value() ;
	_law.fPositionStop  = ui->ValueFocusPositionStop->value() ;
	_law.fPositionStep  = ui->ValueFocusPositionStep->value() ;
	_law.fOffsetStart   = ui->ValueFocusOffsetStart->value() ;
	_law.fOffsetStop	= ui->ValueFocusOffsetStop->value() ;
	_law.fDepthStart	= ui->ValueFocusDepthStart->value() ;
	_law.fDepthStop	 = ui->ValueFocusDepthStop->value() ;

    //************ element selection***************//
	_law.nElemQtyFir   = ui->ValueElementQtyPri->value() ;
	_law.nFirstElemFir = ui->ValueElementStartPri->value() ;
	_law.nLastElemFir  = ui->ValueElementStopPri->value() ;
	_law.nElemStepFir  = ui->ValueElementStepPri->value() ;

	_law.nElemQtySec   = ui->ValueElementQtySec->value() ;
	_law.nFirstElemSec = ui->ValueElementStartSec->value() ;
	_law.nLastElemSec  = ui->ValueElementStopSec->value() ;
	_law.nElemStepSec  = ui->ValueElementStepSec->value() ;

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupFocalLaw(m_nGroupId , &_law);

	UpdateCurrentAngleCom();
	UpdateSampleRange();

}

void DopplerGroupTab::on_ComAngleType_currentIndexChanged(int)
{
	if(!ui->ComAngleType->hasFocus())  return ;
	UpdateFocallawState();
}

void DopplerGroupTab::AngleAlign()
{
	int _nStart = ui->ValueRefractStart->value() * 10 ;
	int _nStop  = ui->ValueRefractStop->value()  * 10 ;
	int _nStep  = ui->ValueRefractStep->value()  * 10 ;
	int _nSteps = (_nStop - _nStart) / _nStep  ;
	_nStop = _nStart + _nStep * _nSteps ;
	ui->ValueRefractStop->setValue(_nStop / 10.0);
}

void DopplerGroupTab::FocusPositionAlign()
{
	int _nStart = ui->ValueFocusPositionStart->value() * 10 ;
	int _nStop  = ui->ValueFocusPositionStop->value()  * 10 ;
	int _nStep  = ui->ValueFocusPositionStep->value()  * 10 ;
	int _nSteps = (_nStop - _nStart) / _nStep  ;
	_nStop = _nStart + _nStep * _nSteps ;
	ui->ValueFocusPositionStop->setValue(_nStop / 10.0);
}

void DopplerGroupTab::ElementAlign()
{
	int _nQty   = ui->ValueElementQtyPri->value()  ;
	int _nStart = ui->ValueElementStartPri->value() ;
	int _nStop  = ui->ValueElementStopPri->value() ;
	int _nStep  = ui->ValueElementStepPri->value() ;
	int _nSteps = (_nStop - _nQty - _nStart + 1) / _nStep ;
	_nStop = _nStart + _nStep * _nSteps + _nQty - 1;
	ui->ValueElementStopPri->setValue(_nStop );
}

void DopplerGroupTab::on_ValueRefractStart_editingFinished()
{
	AngleAlign() ;
}

void DopplerGroupTab::on_ValueRefractStop_editingFinished()
{
	AngleAlign();
}

void DopplerGroupTab::on_ValueRefractStep_editingFinished()
{
	AngleAlign();
}

void DopplerGroupTab::on_ComFocalType_currentIndexChanged(int)
{
	if(!ui->ComFocalType->hasFocus())  return ;
	UpdateFocallawState() ;
}

void DopplerGroupTab::on_ValueFocusPositionStart_editingFinished()
{
	FocusPositionAlign() ;
}

void DopplerGroupTab::on_ValueFocusPositionStop_editingFinished()
{
	FocusPositionAlign() ;
}

void DopplerGroupTab::on_ValueFocusPositionStep_editingFinished()
{
	FocusPositionAlign() ;
}

void DopplerGroupTab::on_ValueElementQtyPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStartPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStopPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStepPri_editingFinished()
{
	ElementAlign() ;
}
//int _Gate = 0 ;
//int _GateA = 1;
//int _GateB = 0;
//int _GateI = 0;
// gate
void DopplerGroupTab::on_ComGateSelect_currentIndexChanged(int index)
{
	if(!ui->ComGateSelect->hasFocus())  return ;
	GROUP_CONFIG& group = m_pConfig->group[m_nGroupId] ;
	GATE_CONFIG& _gate = group.gate[index] ;
	ui->ValueGateStart->setValue(_gate.fStart);
	ui->ValueGateWidth->setValue(_gate.fWidth);
	ui->ValueGateHeight->setValue(_gate.nThreshold);
    //Gate = index;
    if(index == 0)
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateA ? Qt::Checked : Qt::Unchecked);
    else if(index == 1)
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateB ? Qt::Checked : Qt::Unchecked);
    else if(index == 2)
        ui->CheckGateShow->setCheckState(m_pGroup->bShowGateI ? Qt::Checked : Qt::Unchecked);
	if(index == 2) //gate i
	{
		ui->ComGateSync->setCurrentIndex(0);
		ui->ComGateMeasure->setCurrentIndex(0);
        ui->ComGateMeasure->setEnabled(true);
        ui->ComGateSync->setEnabled(true);
    }else{
		ui->ComGateMeasure->setEnabled(true);
		ui->ComGateSync->setEnabled(true);
		ui->ComGateSync->setCurrentIndex(_gate.eSynChro);
		ui->ComGateMeasure->setCurrentIndex(_gate.eMeasure);
	}
}

void DopplerGroupTab::on_CheckGateShow_clicked(bool checked)
{
    //m_pGroup->bShowGate = checked ;
    int Gate = ui->ComGateSelect->currentIndex() ;
    if(Gate == 0)
        m_pGroup->bShowGateA = checked;
    else if(Gate == 1)
        m_pGroup->bShowGateB = checked;
    else if(Gate == 2)
        m_pGroup->bShowGateI = checked;
//    _GateA = m_pGroup->bShowGateA;
//    _GateB = m_pGroup->bShowGateB;
//    _GateI = m_pGroup->bShowGateI;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::GatePro()
{
    GATE_CONFIG _gate ;
	_gate.fStart = ui->ValueGateStart->value() ;
	_gate.fWidth = ui->ValueGateWidth->value() ;
	_gate.nThreshold = ui->ValueGateHeight->value();
	_gate.eMeasure   = ui->ComGateMeasure->currentIndex() ;
	_gate.eSynChro   = (setup_GATE_AYNC_TYPE)ui->ComGateSync->currentIndex() ;
    _gate.gTravelMode = (setup_GATE_TRAVEL_MODE)ui->ComGateMode->currentIndex();
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGateInfo(m_nGroupId , (setup_GATE_NAME)ui->ComGateSelect->currentIndex() , &_gate) ;

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->m_defect[m_nGroupId]->analysisData();

	ProcessDisplay _display ;
    _display.UpdateAllViewOverlay();
//    _display.UpdateAllViewGateOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueGateStart_valueChanged(double)
{
	if(!ui->ValueGateStart->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueGateWidth_valueChanged(double)
{
	if(!ui->ValueGateWidth->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueGateHeight_valueChanged(double)
{
	if(!ui->ValueGateHeight->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueTopcWidth_valueChanged(double value)
{
    if(!ui->ValueTopcWidth->hasFocus()) return;
    //m_pGroup->TopCInfo.TOPCWidth = value;
    int groupQty = m_pConfig->common.nGroupQty;
    for(int i = 0; i < groupQty; i++){
        if(m_pConfig->group[i].eGroupMode <= setup_GROUP_MODE_PA){
            m_pConfig->group[i].TopCInfo.TOPCWidth = value;
        }
    }
    ProcessDisplay _display;
    _display.UpdateAllViewOverlay();
    g_pMainWnd->setAllTopcWidht(value);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComCscanType_currentIndexChanged(int index)
{
    if(!ui->ComCscanType->hasFocus()) return;
    m_pGroup->TopCInfo.TOPCStatus = index;
    ProcessDisplay _display;
    _display.UpdateAllViewFrame();
    _display.UpdateAllViewOverlay();
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComTopCMergeRefer_currentIndexChanged(int /*index*/)
{
    if(!ui->ComTopCMergeRefer->hasFocus()) return;
    QString buff = ui->ComTopCMergeRefer->currentText();
    if( buff == "NULL"){
        return;
    }
    int topcMergeRefer = buff.toInt() -1;
    m_pGroup->TopCInfo.TOPCMergeRefer = topcMergeRefer;
    ProcessDisplay _display;
    _display.UpdateAllViewFrame();
    _display.UpdateAllViewOverlay();
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComTopcMergeStatus_currentIndexChanged(int index)
{
    if(!ui->ComTopcMergeStatus->hasFocus()) return;
    m_pGroup->TopCInfo.TOPCMergeStatus = index;
    ProcessDisplay _display;
    _display.UpdateAllViewFrame();
    _display.UpdateAllViewOverlay();
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComGateMode_currentIndexChanged(int )
{
    if(!ui->ComGateMode->hasFocus()) return;
    GatePro();
}

void DopplerGroupTab::on_ComGateSync_currentIndexChanged(int )
{
	if(!ui->ComGateSync->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ComGateMeasure_currentIndexChanged(int)
{
	if(!ui->ComGateMeasure->hasFocus())  return ;
	GatePro();
	UpdateMeasureBox();
}

void DopplerGroupTab::on_CheckShowThickness_clicked(bool checked)
{
    m_pGroup->bShowThickness = checked;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComGeometry_currentIndexChanged(int)
{
    if(!ui->ComGeometry->hasFocus())  return;
	UpdateGeometryState() ;
	PartPro();
}

void DopplerGroupTab::PartPro()
{
	PART_CONFIG _part ;
	_part.eGeometry = (setup_PART_GEOMETRY)ui->ComGeometry->currentIndex() ;
	_part.afSize[0] = ui->ValuePartSize1->value() ;
	_part.afSize[1] = ui->ValuePartSize2->value() ;
	_part.afSize[2] = ui->ValuePartSize3->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupPartGeometry (m_nGroupId, &_part) ;
	ProcessDisplay _display ;
	_display.UpdateAllView();
	g_pMainWnd->RunDrawThreadOnce(true);
	UpdateDefectValue();
}

void DopplerGroupTab::on_ValuePartSize1_valueChanged(double value)
{
	if(!ui->ValuePartSize1->hasFocus())  return ;
    emit thicknessChange(value);
    //PartPro();
}

void DopplerGroupTab::on_ValuePartSize2_valueChanged(double)
{
	if(!ui->ValuePartSize2->hasFocus())  return ;
	PartPro();
}

void DopplerGroupTab::on_ValuePartSize3_valueChanged(double)
{
	if(!ui->ValuePartSize3->hasFocus())  return ;
	PartPro();
}

void DopplerGroupTab::on_ComMaterial_currentIndexChanged(int index)
{
	if(!ui->ComMaterial->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPartMaterial(m_nGroupId ,  index) ;
	ui->ValueVelocity->setValue(m_pGroup->fVelocity);
	UpdateVelocitySelection() ;
}

//void DopplerGroupTab::on_ValueScanOffset_editingFinished()
//{
//    if(!ui->ValueScanOffset->hasFocus())  return ;
//    ParameterProcess* _process = ParameterProcess::Instance();
//    double _fValue1 = ui->ValueScanOffset->value()  ;
//    double _fValue2 = ui->ValueIndexOffset->value() ;
//    _process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

//    DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
//    _pConfig->ResetShadowData();

//    g_pMainWnd->RunDrawThreadOnce(true);
//    ProcessDisplay _display ;
//    //_display.UpdateAllViewOfGroup(m_nGroupId);
//    _display.UpdateAllView();
//    sleep(20);
//    _display.UpdateAllView();
//    g_pMainWnd->RunDrawThreadOnce(true);
//    sleep(20);
//}

//void DopplerGroupTab::on_ValueIndexOffset_editingFinished()
//{
//    if(!ui->ValueIndexOffset->hasFocus())  return ;
//    ParameterProcess* _process = ParameterProcess::Instance();
//    double _fValue1 = ui->ValueScanOffset->value()  ;
//    double _fValue2 = ui->ValueIndexOffset->value() ;
//    _process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

//    ProcessDisplay _display ;
//    _display.UpdateAllViewOfGroup(m_nGroupId);
//    g_pMainWnd->RunDrawThreadOnce(true);
//}

void DopplerGroupTab::on_ComSkewAngle_currentIndexChanged(int index)
{
	if(!ui->ComSkewAngle->hasFocus())  return  ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupWedgeSkewAngle(m_nGroupId , (setup_PROBE_ANGLE)index)  ;

	ProcessDisplay _display ;
	_display.UpdateAllView();
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

//void DopplerGroupTab::on_BtnLoadPartFile_clicked()
//{
//	DialogWeldPartLoad _dialog(this);
//	int _nRet = _dialog.exec();

//	if(_nRet)
//	{
//		ParameterProcess* _process = ParameterProcess::Instance();
//		_process->SetupPart(m_nGroupId,  _dialog.GetPart());
//	}

//    ProcessDisplay _display;
//    _display.UpdateAllViewOfGroup(m_nGroupId);
//}

void DopplerGroupTab::on_BtnLoadDxfFile_clicked()
{
    DopplerConfigure* Configure = DopplerConfigure::Instance();
    ParameterProcess* _process = ParameterProcess::Instance();
    GROUP_CONFIG& group = Configure->group[m_nGroupId];
    if( group.part.weldFormat)
    {
        DialogWeldFixDataII dataIIDialog(this, m_nGroupId);
        if(dataIIDialog.exec())
        {
            //ParameterProcess* _process = ParameterProcess::Instance();
            _process->SetupPart(m_nGroupId, dataIIDialog.GetPart());
        }
    }
    else
    {
        DialogDxfFileLoad dialog(this);

        if(dialog.exec())
        {
            //ParameterProcess* _process = ParameterProcess::Instance();
            _process->SetupPart(m_nGroupId, dialog.GetPart());
        }
    }
    group.part.weld_border = _process->GetWeldBorder(m_nGroupId);

    ProcessDisplay _display;
    _display.UpdateAllViewOfGroup(m_nGroupId);
    _display.UpdateAllView();
    _display.UpdateAllViewOfGroup(m_nGroupId);
    g_pMainWnd->RunDrawThreadOnce(true);
    ui->ComSkewAngle->setCurrentIndex(m_pGroup->eSkew);
    ui->ValuePartSize1->setValue(m_pGroup->part.afSize[0]);

}

void DopplerGroupTab::on_CheckLwBwShow_clicked(bool checked)
{
	m_pGroup->bShowLwBw = checked;
    ProcessDisplay _display;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComBoxProMode_currentIndexChanged(int index_)
{
	if(!ui->ComBoxProMode->hasFocus())  return  ;

	if(m_pConfig->TOFD[m_nGroupId].eProingST == 0) {
		m_pConfig->AppEvn.iTofdDataProMode = index_;
	} else {
		ui->ComBoxProMode->setCurrentIndex(m_pConfig->AppEvn.iTofdDataProMode);
	}
}

void DopplerGroupTab::on_SpinBoxWedgeSeperation_valueChanged(double arg1)
{
	if(!ui->SpinBoxWedgeSeperation->hasFocus())  return  ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fWedgeSep = arg1  ;
	_tofd->fPCS	  = arg1 + 2 * _tofd->fRefPoint ;
	ui->SpinBoxPCS->setValue(_tofd->fPCS);

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_SpinBoxZeroOff_valueChanged(double)
{
	if(!ui->SpinBoxZeroOff->hasFocus()) return ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fZeroOff = ui->SpinBoxZeroOff->value() ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);

	_process->GetTofdDepth(m_nGroupId , 1 , &_tofd->fDepthCal);
	ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);
}

void DopplerGroupTab::on_SpinBoxDepthStart_valueChanged(double)
{
	if(!ui->SpinBoxDepthStart->hasFocus()) return ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fLayerStart = ui->SpinBoxDepthStart->value() ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_SpinBoxDepthEnd_valueChanged(double)
{
	if(!ui->SpinBoxDepthEnd->hasFocus()) return ;

	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fLayerEnd = ui->SpinBoxDepthEnd->value() ;

	ParameterProcess* _process = ParameterProcess::Instance() ;
	_process->TofdCursorCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_SpinBoxDepthCal_valueChanged(double)
{
	if(!ui->SpinBoxDepthCal->hasFocus()) return ;
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fDepthCal = ui->SpinBoxDepthCal->value();
}

void DopplerGroupTab::on_BtnDepthCal_clicked()
{
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_tofd->fDepthCal = ui->SpinBoxDepthCal->value();

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->TofdDepthCalibration(m_nGroupId);

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);

	_process->GetTofdDepth(m_nGroupId, 2, &_tofd->fDepthCal);
	ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);

	ui->SpinBoxZeroOff->setValue(_tofd->fZeroOff);
}

//void DopplerGroupTab::on_CheckPartFileShow_clicked(bool checked)
//{
//	ParameterProcess* _process = ParameterProcess::Instance();
//    _process->SetupShowWeldPart(m_nGroupId , checked);

//	ProcessDisplay _display ;
//    _display.UpdateAllViewOfGroup(m_nGroupId);
//}

void DopplerGroupTab::on_CheckDxfFileShow_clicked(bool checked)
{
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupShowWeldPart(m_nGroupId , checked);

    ProcessDisplay _display ;
    _display.UpdateAllViewOfGroup(m_nGroupId);
}

void DopplerGroupTab::on_CheckMeasureShow_clicked(bool checked)
{
	ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupShowMeasure(m_nGroupId , checked);
    m_pConfig->group[m_nGroupId].bShowAScanMeasure = checked;
    m_pConfig->group[m_nGroupId].bShowBScanMeasure = checked;
    m_pConfig->group[m_nGroupId].bShowCScanMeasure = checked;
    m_pConfig->group[m_nGroupId].bShowSScanMeasure = checked;
    ui->checkAScanShow->setCheckState( checked ? Qt::Checked : Qt::Unchecked);
    ui->checkBScanShow->setCheckState( checked ? Qt::Checked : Qt::Unchecked);
    ui->checkCScanShow->setCheckState( checked ? Qt::Checked : Qt::Unchecked);
    ui->checkSScanShow->setCheckState( checked ? Qt::Checked : Qt::Unchecked);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_checkAScanShow_clicked(bool checked)
{
    if(!ui->checkAScanShow->hasFocus()) return;
    m_pConfig->group[m_nGroupId].bShowAScanMeasure = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_checkBScanShow_clicked(bool checked)
{
    if(!ui->checkBScanShow->hasFocus()) return;
    m_pConfig->group[m_nGroupId].bShowBScanMeasure = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_checkCScanShow_clicked(bool checked)
{
    if(!ui->checkCScanShow->hasFocus()) return;
    m_pConfig->group[m_nGroupId].bShowCScanMeasure = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_checkSScanShow_clicked(bool checked)
{
    if(!ui->checkSScanShow->hasFocus()) return;
    m_pConfig->group[m_nGroupId].bShowSScanMeasure = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckBackShow_clicked(bool checked)
{
	if(!ui->CheckBackShow->hasFocus()) return ;
	g_pMainWnd->SetParamBackMode(checked) ;
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComField1_currentIndexChanged(int index)
{
	if(!ui->ComField1->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 0 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
		 g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField2_currentIndexChanged(int index)
{
	if(!ui->ComField2->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 1 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
		 g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField3_currentIndexChanged(int index)
{
	if(!ui->ComField3->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 2 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
		 g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField4_currentIndexChanged(int index)
{
	if(!ui->ComField4->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId , 3 , index);

    //if(ui->CheckMeasureShow->checkState())
    //{
		 g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField5_currentIndexChanged(int index)
{
	if(!ui->ComField5->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 4 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
		 g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField6_currentIndexChanged(int index)
{
    if(!ui->ComField6->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId , 5 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
         g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField7_currentIndexChanged(int index)
{
    if(!ui->ComField7->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId , 6 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
         g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField8_currentIndexChanged(int index)
{
    if(!ui->ComField8->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId , 7 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
         g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField9_currentIndexChanged(int index)
{
    if(!ui->ComField9->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId , 8 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
         g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField10_currentIndexChanged(int index)
{
    if(!ui->ComField10->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId , 9 , index)  ;

    //if(ui->CheckMeasureShow->checkState())
    //{
         g_pMainWnd->RunDrawThreadOnce(true);
    //}
}

void DopplerGroupTab::on_ComField11_currentIndexChanged(int index)
{
    if(!ui->ComField11->hasFocus()) return;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId, 10, index);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComField12_currentIndexChanged(int index)
{
    if(!ui->ComField12->hasFocus()) return;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId, 11, index);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComField13_currentIndexChanged(int index)
{
    if(!ui->ComField13->hasFocus()) return;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId, 12, index);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComField14_currentIndexChanged(int index)
{
    if(!ui->ComField14->hasFocus()) return;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupMeasureData(m_nGroupId, 13, index);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckCursorShow_clicked(bool checked)
{
	m_pGroup->bShowCursor = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_CheckCursorSync_clicked(bool checked)
{
	m_pConfig->AppEvn.bSAxisCursorSync = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::update_valueChanged()
{
    if(ui->CheckCursorShow->checkState())
    {
        ProcessDisplay _display;
        _display.UpdateAllViewOverlay();
    }

    if(ui->CheckMeasureShow->checkState())
    {
        g_pMainWnd->RunDrawThreadOnce(true);
    }
}

void DopplerGroupTab::on_ValueARef_valueChanged(double value)
{
	if(!ui->ValueARef->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_A_REF, value);

    update_valueChanged();
}

void DopplerGroupTab::on_ValueAMes_valueChanged(double value)
{
	if(!ui->ValueAMes->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_A_MES, value);

    update_valueChanged();
}

void DopplerGroupTab::on_ValueURef_valueChanged(double value)
{
	if(!ui->ValueURef->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_U_REF , value);

    update_valueChanged();

	ui->ValueARef->setValue(m_pGroup->afCursor[setup_CURSOR_A_REF]);
}

void DopplerGroupTab::on_ValueUMes_valueChanged(double value)
{
	if(!ui->ValueUMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_U_MES, value);

    update_valueChanged();

	ui->ValueAMes->setValue(m_pGroup->afCursor[setup_CURSOR_A_MES]);
}

void DopplerGroupTab::on_ValueSRef_valueChanged(double value)
{
	if(!ui->ValueSRef->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId, setup_CURSOR_S_REF, value);

    update_valueChanged();
}

void DopplerGroupTab::on_ValueSMes_valueChanged(double value)
{
	if(!ui->ValueSMes->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_S_MES, value);

    update_valueChanged();
}

void DopplerGroupTab::on_ValueIRef_valueChanged(double value)
{
	if(!ui->ValueIRef->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_I_REF, value);

    update_valueChanged();
}

void DopplerGroupTab::on_ValueIMes_valueChanged(double value)
{
	if(!ui->ValueIMes->hasFocus()) return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupCursor(m_nGroupId , setup_CURSOR_I_MES, value);

    update_valueChanged();
}

void DopplerGroupTab::on_BtnColorAmp_clicked()
{
	DialogColorSelect _dialog(this) ;
	int _nRet = _dialog.exec();
	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPalette(m_nGroupId , PALETTE_AMP , _dialog.GetColorIndex()) ;
	}
	UpdateColorSetting();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_BtnColorRf_clicked()
{
	DialogColorSelect _dialog(this) ;
	int _nRet = _dialog.exec();
	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPalette(m_nGroupId , PALETTE_RECTIFY , _dialog.GetColorIndex()) ;
	}
	UpdateColorSetting();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_BtnColorThickness_clicked()
{
	DialogColorSelect _dialog(this) ;
	int _nRet = _dialog.exec();
	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPalette(m_nGroupId , PALETTE_THICKNESS , _dialog.GetColorIndex()) ;
	}
	UpdateColorSetting();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_ComColorLineSelection_currentIndexChanged(int index)
{
	if(!ui->ComColorLineSelection->hasFocus()) return ;
	ui->ComColorLineColor->setCurrentIndex(m_pGroup->color.anColor[index]);
}

void DopplerGroupTab::on_ComColorLineColor_currentIndexChanged(int index)
{
	if(!ui->ComColorLineColor->hasFocus()) return ;
	int _nLine = ui->ComColorLineSelection->currentIndex()  ;

	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupAScanColor(m_nGroupId , _nLine  , index);
}

void DopplerGroupTab::on_ValueCScanThicknessMin_valueChanged(double)
{
    if(!ui->ValueCScanThicknessMin->hasFocus()) return ;
    if(ui->ValueCScanThicknessMin->value() > ui->ValueCScanThicknessMax->value()) {
        ui->ValueCScanThicknessMin->setValue(ui->ValueCScanThicknessMax->value()
                                             - ui->ValueCScanThicknessMin->singleStep());
    }
	m_pGroup->fMinThickness = ui->ValueCScanThicknessMin->value() ;

	ProcessDisplay _display ;
    _display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueCScanThicknessMax_valueChanged(double)
{
    if(!ui->ValueCScanThicknessMax->hasFocus()) return ;
    if(ui->ValueCScanThicknessMax->value() < ui->ValueCScanThicknessMin->value()) {
        ui->ValueCScanThicknessMax->setValue(ui->ValueCScanThicknessMin->value()
                                             + ui->ValueCScanThicknessMax->singleStep());
    }
	m_pGroup->fMaxThickness = ui->ValueCScanThicknessMax->value() ;

	ProcessDisplay _display ;
    _display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComCScanSource1_currentIndexChanged(int index)
{
    if(!ui->ComCScanSource1->hasFocus()) return ;
	m_pGroup->eCScanSource[0] = (setup_CSCAN_SOURCE_MODE)index ;
	g_pMainWnd->UpdateAllDisplay();
	g_pMainWnd->RunDrawThreadOnce();
    //DopplerConfigure::setSetting(m_nGroupId,"CScansource1",index);
}

void DopplerGroupTab::on_ComCScanSource2_currentIndexChanged(int index)
{
	if(!ui->ComCScanSource2->hasFocus()) return ;
	m_pGroup->eCScanSource[1] = (setup_CSCAN_SOURCE_MODE)index ;
	g_pMainWnd->UpdateAllDisplay();
	g_pMainWnd->RunDrawThreadOnce();
    //DopplerConfigure::setSetting(m_nGroupId,"CScansource2",index);
}

void DopplerGroupTab::on_ComCScanShowAll_currentIndexChanged(int index)
{
    if(!ui->ComCScanShowAll->hasFocus()) return;
    if( index == 0){
        m_pGroup->CScanShowAll = false;
    }else{
        m_pGroup->CScanShowAll = true;
    }
    g_pMainWnd->UpdateAllDisplay();
    g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::ComDispPro(int index, int iGroup)
{
	QComboBox* _comboxTab[4];
	_comboxTab[0] = ui->ComComDisp1;
	_comboxTab[1] = ui->ComComDisp2;
	_comboxTab[2] = ui->ComComDisp3;
	_comboxTab[3] = ui->ComComDisp4;

	if(index > 3)  return ;
	if(!_comboxTab[index]->hasFocus()) return ;

	U8* _pComDisp = m_pConfig->GetComDisplayPoint();
	bool _bExist = false;
	for(int i = 0; i < 4; i++) {
		if(i != index) {
			if(_pComDisp[i] == iGroup) {
				_bExist = true;
			}
		}
	}
	if(_bExist) {
		_comboxTab[index]->setCurrentIndex(_pComDisp[index]);
	} else {
		_pComDisp[index] = iGroup;
	}
}

void DopplerGroupTab::on_ComComDisp1_currentIndexChanged(int index)
{
	ComDispPro(0, index);
}

void DopplerGroupTab::on_ComComDisp2_currentIndexChanged(int index)
{
	ComDispPro(1, index);
}

void DopplerGroupTab::on_ComComDisp3_currentIndexChanged(int index)
{
	ComDispPro(2, index);
}

void DopplerGroupTab::on_ComComDisp4_currentIndexChanged(int index)
{
	ComDispPro(3, index);
}

void DopplerGroupTab::on_BtnRefurbishComDisp_clicked()
{
	g_pMainWnd->UpdateCombinationDisplay();
	sleep(600);
}

void DopplerGroupTab::on_CheckDefectShow_clicked(bool checked)
{
    m_pGroup->bShowDefect = checked;
    ProcessDisplay _display;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComDefectIndex_currentIndexChanged(int index)
{
	if(!ui->ComDefectIndex->hasFocus()) return ;
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	_pConfig->m_dfParam[m_nGroupId].index = index;
    UpdateDefectValue();
    ProcessDisplay _display ;
    _display.ShowDefectInfo(m_nGroupId,index);
    //g_pMainWnd->RunDrawThreadOnce(true);
    g_pMainWnd->loadDefectPosition(m_nGroupId,index);
}

void DopplerGroupTab::on_lineEditReMark_textChanged(QString str)
{
	if(!ui->lineEditReMark->hasFocus()) return ;
   // QString t1 = ui->lineEditReMark->text();
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _index = _pConfig->m_dfParam[m_nGroupId].index;
    QString t1 = QString::fromLocal8Bit(qPrintable(str));
    std::string t2 = t1.toStdString();
    const char * t3 = t2.c_str();
    _pConfig->SetDefectInfo(m_nGroupId, _index, (char *)t3,(char*)(qPrintable(str)));
    //_pConfig->SetDefectInfo(m_nGroupId, _index, (char*)(qPrintable(str)));

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_BtnDefectDelete_clicked()
{
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _index = _pConfig->m_dfParam[m_nGroupId].index;

	_pConfig->DeleteDefect(m_nGroupId, _index);

//	UpdateDefectBox();
//	UpdateDefectValue() ;
    g_pMainWnd->updateAllDefectBox();
//  g_pMainWnd->RunDrawThreadOnce();
	ProcessDisplay _display ;
    _display.ResetDefectInfo(m_nGroupId);
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::retranslateGroupTabUi()
{
    ui->retranslateUi(this);
    model->setHeaderData(0, Qt::Horizontal, tr("Display Mode"));
}

void DopplerGroupTab::on_ValueCScanThicknessMin_editingFinished()
{
    ProcessDisplay _display ;
    _display.UpdateAllViewOverlay();
    g_pMainWnd->UpdateAllDisplay();
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueCScanThicknessMax_editingFinished()
{
    ProcessDisplay _display ;
    _display.UpdateAllViewOverlay();
    g_pMainWnd->UpdateAllDisplay();
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueScanOffset_valueChanged(double)
{
    if(!ui->ValueScanOffset->hasFocus())  return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    double _fValue1 = ui->ValueScanOffset->value()  ;
    double _fValue2 = ui->ValueIndexOffset->value() ;
    SCANNER& _scan = m_pConfig->common.scanner;
    if(_scan.eScanEncoderType == setup_ENCODER_TYPE_TIMER)
    {
        _fValue1 = _fValue1 * _scan.fPrf;
    }
    _process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

    DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
    _pConfig->ResetShadowData();
    g_pMainWnd->initSlider();
    g_pMainWnd->RunDrawThreadOnce(true);
    ProcessDisplay _display ;
    //_display.UpdateAllViewOfGroup(m_nGroupId);
    _display.UpdateAllView();
    sleep(20);
    _display.UpdateAllView();
    g_pMainWnd->RunDrawThreadOnce(true);
    sleep(20);
}

void DopplerGroupTab::on_ValueIndexOffset_valueChanged(double)
{
    if(!ui->ValueIndexOffset->hasFocus())  return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    double _fValue1 = ui->ValueScanOffset->value()  ;
    double _fValue2 = ui->ValueIndexOffset->value() ;
    SCANNER& _scan = m_pConfig->common.scanner;
    if(_scan.eScanEncoderType == setup_ENCODER_TYPE_TIMER)
    {
        _fValue1 = _fValue1 * _scan.fPrf;
    }
    _process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

    ProcessDisplay _display ;
    _display.UpdateAllViewOfGroup(m_nGroupId);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckCurveShow_clicked(bool checked)
{
    m_pGroup->bShowCurve = checked ;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckCursorHide_clicked(bool checked)
{
    bHideCursor = checked;
    ProcessDisplay _display ;
    _display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_CheckRLShow_clicked(bool checked)
{
    CUR_RES.bShowRL = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueRL_valueChanged(double arg1)
{
    CUR_RES.CurRL[m_nGroupId] = arg1;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueScannerSensitivity_valueChanged(double arg1)
{
    if(!ui->ValueScannerSensitivity->hasFocus())  return ;
    CUR_RES.CurSS[m_nGroupId] = arg1;
    ProcessDisplay _display;
    _display.UpdateAllViewOverlay();
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckELShow_clicked(bool checked)
{
    CUR_RES.bShowEL = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueEL_valueChanged(double arg1)
{
    CUR_RES.CurEL[m_nGroupId] = arg1;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_CheckSLShow_clicked(bool checked)
{
    CUR_RES.bShowSL = checked;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueSL_valueChanged(double arg1)
{
    CUR_RES.CurSL[m_nGroupId] = arg1;
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueREFGain_valueChanged(double arg1)
{
    if(!ui->ValueREFGain->hasFocus())  return ;
    CUR_RES.REF_Gain[m_nGroupId] = arg1;
    ui->ValueComGain->setMinimum(0-m_pGroup->fGain-m_pGroup->RefGain-CUR_RES.REF_Gain[m_nGroupId]);
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupRefGain(m_nGroupId , arg1 + CUR_RES.Com_Gain[m_nGroupId]) ;
    ProcessDisplay _display ;
    _display.UpdateAllViewCursorOfGroup(m_nGroupId);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueComGain_valueChanged(double arg1)
{
    if(!ui->ValueComGain->hasFocus())  return ;
    CUR_RES.Com_Gain[m_nGroupId] = arg1;
    ui->ValueREFGain->setMinimum(0-m_pGroup->fGain-m_pGroup->RefGain-CUR_RES.Com_Gain[m_nGroupId]);
    ParameterProcess* _process = ParameterProcess::Instance();
    _process->SetupRefGain(m_nGroupId , arg1 + CUR_RES.REF_Gain[m_nGroupId]) ;
    ProcessDisplay _display ;
    _display.UpdateAllViewCursorOfGroup(m_nGroupId);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComStandard_currentIndexChanged(int index)
{
    if(!ui->ComStandard->hasFocus())  return ;
    m_pGroup->ThicknessType[m_nGroupId] = 0;

    UpdateStandard(index,1);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ComThickness_currentIndexChanged(int index)
{
    if(!ui->ComThickness->hasFocus())  return ;
    m_pGroup->ThicknessType[m_nGroupId] = index;
    UpdateStandard(ui->ComStandard->currentIndex(),0);
    g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_pushButton_clicked()
{
    ParameterProcess* _process = ParameterProcess::Instance();
    int buff[setup_MAX_MEASURE_QTY];
    _process->GetDefaultMeasure(m_nGroupId, buff);

    ui->ComField1->setCurrentIndex(buff[0]);
    ui->ComField2->setCurrentIndex(buff[1]);
    ui->ComField3->setCurrentIndex(buff[2]);
    ui->ComField4->setCurrentIndex(buff[3]);
    ui->ComField5->setCurrentIndex(buff[4]);
    ui->ComField6->setCurrentIndex(buff[5]);
    ui->ComField7->setCurrentIndex(buff[6]);
    ui->ComField8->setCurrentIndex(buff[7]);
    ui->ComField9->setCurrentIndex(buff[8]);
    ui->ComField10->setCurrentIndex(buff[9]);
    ui->ComField11->setCurrentIndex(buff[10]);
    ui->ComField12->setCurrentIndex(buff[11]);
    ui->ComField13->setCurrentIndex(buff[12]);
    ui->ComField14->setCurrentIndex(buff[13]);

    _process->SetupMeasureData(m_nGroupId , 0 , ui->ComField1->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 1 , ui->ComField2->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 2 , ui->ComField3->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 3 , ui->ComField4->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 4 , ui->ComField5->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 5 , ui->ComField6->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 6 , ui->ComField7->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 7 , ui->ComField8->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 8 , ui->ComField9->currentIndex())  ;
    _process->SetupMeasureData(m_nGroupId , 9 , ui->ComField10->currentIndex()) ;
    _process->SetupMeasureData(m_nGroupId , 10, ui->ComField11->currentIndex()) ;
    _process->SetupMeasureData(m_nGroupId , 11, ui->ComField12->currentIndex()) ;
    _process->SetupMeasureData(m_nGroupId , 12, ui->ComField13->currentIndex()) ;
    _process->SetupMeasureData(m_nGroupId , 13, ui->ComField14->currentIndex()) ;
    if(ui->CheckMeasureShow->checkState())
    {
         g_pMainWnd->RunDrawThreadOnce(true);
    }
}

void DopplerGroupTab::on_checkDefectBg_clicked(bool checked)
{
    if(!ui->checkDefectBg->hasFocus()) return ;
    g_pMainWnd->SetDefectBackMode(checked) ;
    g_pMainWnd->RunDrawThreadOnce(true);
}
