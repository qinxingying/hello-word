#include "DopplerGroupTab.h"
#include "ui_DopplerGroupTab.h"
#include <QPushButton>
#include <configure/DopplerConfigure.h>
#include <process/ParameterProcess.h>
#include <configure/const.h>
#include <gHeader.h>
#include <QtGui>



const int MAX_ITEM_QTY = 50 ;
/****************************************************************************
  Description: 所有显示窗口类型
*****************************************************************************/
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
	"S-A-C-C SCAN"  , "S-A-C-C SCAN"
}  ;




DopplerGroupTab::DopplerGroupTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DopplerGroupTab)
{
	ui->setupUi(this);

	m_nGroupId = 0 ;
	m_pConfig = DopplerConfigure::Instance()  ;
	m_pGroup  = &m_pConfig->group[m_nGroupId]  ;
	ui->toolBox->setMinimumHeight(400);
	m_pSizingCurveName[0]  = ui->LabelSizingCure1;
	m_pSizingCurveName[1]  = ui->LabelSizingCure2;
	m_pSizingCurveName[2]  = ui->LabelSizingCure3;
	m_pSizingCurveName[3]  = ui->LabelSizingCure4;
	m_pSizingCurveName[4]  = ui->LabelSizingCure5;
	m_pSizingCurveName[5]  = ui->LabelSizingCure6;
	m_pSizingCurveName[6]  = ui->LabelSizingCure7;
	m_pSizingCurveName[7]  = ui->LabelSizingCure8;
	m_pSizingCurveName[8]  = ui->LabelSizingCure9;
	m_pSizingCurveName[9]  = ui->LabelSizingCure10;
	m_pSizingCurveName[10] = ui->LabelSizingCure11;
	m_pSizingCurveName[11] = ui->LabelSizingCure12;
	m_pSizingCurveName[12] = ui->LabelSizingCure13;
	m_pSizingCurveName[13] = ui->LabelSizingCure14;
	m_pSizingCurveName[14] = ui->LabelSizingCure15;
	m_pSizingCurveName[15] = ui->LabelSizingCure16;

	m_pSizingCurveValue[0]  = ui->ValueSizingCurve1;
	m_pSizingCurveValue[1]  = ui->ValueSizingCurve2;
	m_pSizingCurveValue[2]  = ui->ValueSizingCurve3;
	m_pSizingCurveValue[3]  = ui->ValueSizingCurve4;
	m_pSizingCurveValue[4]  = ui->ValueSizingCurve5;
	m_pSizingCurveValue[5]  = ui->ValueSizingCurve6;
	m_pSizingCurveValue[6]  = ui->ValueSizingCurve7;
	m_pSizingCurveValue[7]  = ui->ValueSizingCurve8;
	m_pSizingCurveValue[8]  = ui->ValueSizingCurve9;
	m_pSizingCurveValue[9]  = ui->ValueSizingCurve10;
	m_pSizingCurveValue[10] = ui->ValueSizingCurve11;
	m_pSizingCurveValue[11] = ui->ValueSizingCurve12;
	m_pSizingCurveValue[12] = ui->ValueSizingCurve13;
	m_pSizingCurveValue[13] = ui->ValueSizingCurve14;
	m_pSizingCurveValue[14] = ui->ValueSizingCurve15;
	m_pSizingCurveValue[15] = ui->ValueSizingCurve16;

	m_pSizingCurveUnit[0]  = ui->LabelSizingCureUnit1;
	m_pSizingCurveUnit[1]  = ui->LabelSizingCureUnit2;
	m_pSizingCurveUnit[2]  = ui->LabelSizingCureUnit3;
	m_pSizingCurveUnit[3]  = ui->LabelSizingCureUnit4;
	m_pSizingCurveUnit[4]  = ui->LabelSizingCureUnit5;
	m_pSizingCurveUnit[5]  = ui->LabelSizingCureUnit6;
	m_pSizingCurveUnit[6]  = ui->LabelSizingCureUnit7;
	m_pSizingCurveUnit[7]  = ui->LabelSizingCureUnit8;
	m_pSizingCurveUnit[8]  = ui->LabelSizingCureUnit9;
	m_pSizingCurveUnit[9]  = ui->LabelSizingCureUnit10;
	m_pSizingCurveUnit[10] = ui->LabelSizingCureUnit11;
	m_pSizingCurveUnit[11] = ui->LabelSizingCureUnit12;
	m_pSizingCurveUnit[12] = ui->LabelSizingCureUnit13;
	m_pSizingCurveUnit[13] = ui->LabelSizingCureUnit14;
	m_pSizingCurveUnit[14] = ui->LabelSizingCureUnit15;
	m_pSizingCurveUnit[15] = ui->LabelSizingCureUnit16;

	int _iLang = m_pConfig->AppEvn.eLanguage;
	ui->ComLanguage->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComLanguage->addItem(g_strLanguageName[i]);
	}
	ui->LabelLanguage->hide();
	ui->ComLanguage->hide();;
	//--------------------------------------------
	ui->ComLanguage->setCurrentIndex(_iLang);

	SetWndName(m_pConfig->AppEvn.eLanguage); // whuan language 2015-05-13

	UpdateGroupConfig ();
	ui->toolBox->setCurrentIndex(0);
	CreateSettingView ();
	// 使窗口不使能  只作数据显示用
	SetWidgetInvalide() ;
}

DopplerGroupTab::~DopplerGroupTab ()
{
	delete ui;
}

void DopplerGroupTab::SetGroupId(int nGroupId_)
{
	m_nGroupId = nGroupId_ ;
	m_pGroup  = &m_pConfig->group[m_nGroupId]  ;
	UpdateGroupConfig ();
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
	MATERIAL& _material = m_pGroup->part.material ;
	ui->ComVelocitySelection->clear();

	QString _strTmp[3];
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
	int _iLang = _pConfig->AppEvn.eLanguage;
	_strTmp[0] = _material.strName[_iLang] ;

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
		_str.sprintf("[%s][L:%.0f][T:%.0f]" , QString(tr(_pMaterial->strName[_iLang])).toUtf8().data(), _pMaterial->fVelocityLon , _pMaterial->fVelocityTran ) ;
		_strList.append(_str);
		if(!strcmp( _pMaterial->strName[0] , m_pGroup->part.material.strName[0]) )
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
	PROBE_CONFIG& _probe = m_pGroup->probe[bIsRx_ ? 1 : 0] ;

	QString _str[4] ;

	if (m_pConfig->AppEvn.eLanguage == setup_LANG_ENGLISH)
	{
		_str[0].sprintf("Element Qty  : Pri[%3d]   Sec[%3d] ", _probe.nElementPri ,	_probe.nElementSec ) ;
		_str[1].sprintf("Element Size : Pri[%2.1f] Sec[%2.1f]  mm", _probe.fSizePri ,  _probe.fSizeSec)	;
		_str[2].sprintf("Element Pitch: Pri[%2.1f] Sec[%2.1f]  mm" , _probe.fPitchPri, _probe.fPitchSec) ;
		_str[3].sprintf("Element Frequency: %.1f MHz" , _probe.fFrequency);
	}
	else
	{
        _str[0].sprintf("阵元数  : 主轴[%3d]   次轴[%3d] ", _probe.nElementPri ,	_probe.nElementSec ) ;
		_str[1].sprintf("阵元尺寸 : 主轴[%2.1f] 次轴[%2.1f]  mm", _probe.fSizePri ,  _probe.fSizeSec)	;
		_str[2].sprintf("阵元间距 : 主轴[%2.1f] 次轴[%2.1f]  mm" , _probe.fPitchPri, _probe.fPitchSec) ;
        _str[3].sprintf("频率	: %.1f MHz" , _probe.fFrequency);
	}

	if(bIsRx_)
	{
		ui->BtnProbeSelection_2->setText(_probe.strName);
		ui->LabelProbeT_Line1_2->setText(_str[0]);
		ui->LabelProbeT_Line2_2->setText(_str[1]);
		ui->LabelProbeT_Line3_2->setText(_str[2]);
		ui->LabelProbeT_Line4_2->setText(_str[3]);
	}
	else
	{
		ui->BtnProbeSelection->setText(_probe.strName);
		ui->LabelProbeT_Line1->setText(_str[0]);
		ui->LabelProbeT_Line2->setText(_str[1]);
		ui->LabelProbeT_Line3->setText(_str[2]);
		ui->LabelProbeT_Line4->setText(_str[3]);
	}
}

/****************************************************************************
  Description: 楔块参数
*****************************************************************************/
void DopplerGroupTab::UpdateWedgeConfig(int bIsRx_)
{
	WEDGE_CONFIG& _wedge = m_pGroup->wedge[bIsRx_ ? 1 : 0] ;

	QString _str[4] ;
	if (m_pConfig->AppEvn.eLanguage == setup_LANG_ENGLISH)
	{
		_str[0].sprintf("Wedge Angle: %2.1f Roof Angle: %2.1f" , _wedge.fWedgeAngle , _wedge.fRoofAngle ) ;
		_str[1].sprintf("Velocity Longtitude: %.0f Transmmit: %.0f" , _wedge.fVelocityLon , _wedge.fVelocityTra ) ;
		_str[2].sprintf("Wedge Type: %s Wedge Direction: %s",
						_wedge.eType ? "UT" : "PA" , _wedge.eDirection ? "NORMAL" : "INVERSE");
		if(_wedge.eType)
		{
			_str[3].sprintf("Reference Point: %.1f mm Wedge Delay: %.2f us" ,
							_wedge.fRefPoint , _wedge.nWedgeDelay /1000.0) ;
		}
		else
		{
			_str[3].sprintf("First Height: %.1f  Offset Fir: %.1f  Sec: %.1f" ,
						   _wedge.fHeigtFirst , _wedge.fOffsetFir , _wedge.fOffsetSec) ;
		}
	}
	else if(m_pConfig->AppEvn.eLanguage == setup_LANG_CHINESS)
	{
		_str[0].sprintf("楔块角度: %2.1f 楔块顶角: %2.1f" , _wedge.fWedgeAngle , _wedge.fRoofAngle ) ;
		_str[1].sprintf("声速 纵波: %.0f 横波: %.0f" , _wedge.fVelocityLon , _wedge.fVelocityTra ) ;
		_str[2].sprintf("楔块类型: %s 楔块方向: %s",
                        _wedge.eType ? "UT" : "PA" , _wedge.eDirection ? QString(QString::fromLocal8Bit("正向")).toUtf8().data() : QString(QString::fromLocal8Bit("反向")).toUtf8().data());

		if(_wedge.eType)
		{
			_str[3].sprintf("参考点: %.1f mm 楔块延迟: %.2f us" ,
							_wedge.fRefPoint , _wedge.nWedgeDelay /1000.0) ;
		}
		else
		{
			_str[3].sprintf("第一阵元高度: %.1f  偏置 主轴: %.1f  次轴: %.1f" ,
						   _wedge.fHeigtFirst , _wedge.fOffsetFir , _wedge.fOffsetSec) ;
		}
	}

	if(bIsRx_)
	{
        ui->BtnWedgeSelection_2->setText(_wedge.strName);
		ui->LabelWedgeT_Line1_2->setText(_str[0]);
		ui->LabelWedgeT_Line2_2->setText(_str[1]);
		ui->LabelWedgeT_Line3_2->setText(_str[2]);
		ui->LabelWedgeT_Line4_2->setText(_str[3]);
	}
	else
	{
		ui->BtnWedgeSelection->setText(_wedge.strName);
		ui->LabelWedgeT_Line1->setText(_str[0]);
		ui->LabelWedgeT_Line2->setText(_str[1]);
		ui->LabelWedgeT_Line3->setText(_str[2]);
		ui->LabelWedgeT_Line4->setText(_str[3]);
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
	QComboBox* _field[5] ;
	_field[0] = ui->ComField1 ;
	_field[1] = ui->ComField2 ;
	_field[2] = ui->ComField3 ;
	_field[3] = ui->ComField4 ;
	_field[4] = ui->ComField5 ;

	for(int i = 0 ; i < 5 ; i ++)
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
	if(_nCurrentId > ui->ComCurrentAngle->count() - 1)
	{
		_nCurrentId  = 0  ;
		m_pGroup->afCursor[setup_CURSOR_LAW] = 0;
	}
	ui->ComCurrentAngle->setCurrentIndex(_nCurrentId);
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
}

void DopplerGroupTab::SetWndName(setup_LANG eLang)
{
	switch(eLang)
	{
	case setup_LANG_ENGLISH:
		ui->toolBox->setItemText(0, QString(tr("Ut Setting")));
		ui->toolBox->setItemText(1, QString(tr("Probe/Wedge")));
		ui->toolBox->setItemText(2, QString(tr("Focallaw")));
		ui->toolBox->setItemText(3, QString(tr("Gate and Sizing Curves")));
		ui->toolBox->setItemText(4, QString(tr("Geometry")));
		ui->toolBox->setItemText(5, QString(tr("Measurement")));
		ui->toolBox->setItemText(6, QString(tr("Display")));

		// Ut Setting
		ui->BoxGeneral->setTitle(QString(tr("General")));
		ui->LabelGain->setText(QString(tr("Gain:")));
		ui->LabelStart->setText(QString(tr("Start:")));
		ui->LabelCurrentAngle->setText(QString(tr("Current Angle:")));
		ui->LabelRange->setText(QString(tr("Range:")));
		ui->LabelVelocity->setText(QString(tr("Velocity:")));
		ui->LabelWedgeDelay->setText(QString(tr("WedgeDelay:")));
		ui->LabelTravelMode->setText(QString(tr("Travel Mode:")));

		ui->BoxPulserReceiver->setTitle(QString(tr("Pulser/Receiver")));
		ui->LabelPulser->setText(QString(tr("Pulser:")));
		ui->LabelReceiver->setText(QString(tr("Receiver:")));
		ui->LabelFilter->setText(QString(tr("Filter:")));
		ui->LabelTxRxMode->setText(QString(tr("TX RX mode:")));
		ui->LabelRectifier->setText(QString(tr("Rectifier:")));
		ui->LabelViedoFilter->setText(QString(tr("Video Filter:")));
		ui->CheckVideoFilter->setText(QString(tr("on/off")));

		ui->LabelPointQty->setText(QString(tr("Point Qty:")));
		ui->CheckPointQtyAuto->setText(QString(tr("Auto")));
		ui->LabelSumGain->setText(QString(tr("Sum Gain:")));
		ui->CheckSumGainAuto->setText(QString(tr("Auto")));
		ui->LabelAverage->setText(QString(tr("Average:")));
		ui->LabelGroupMode->setText(QString(tr("Group Mode:")));
		ui->BoxProbeTrigger->setTitle(QString(tr("Tx Probe")));
		ui->BoxWedgeTrigger->setTitle(QString(tr("Tx Wedge")));
		ui->BoxProbeTrigger_2->setTitle(QString(tr("Rx Probe")));
		ui->BoxWedgeTrigger_2->setTitle(QString(tr("Rx Wedge")));
		ui->LabelLawType->setText(QString(tr("Law Type:")));
		ui->BtnProcessLaw->setText(QString(tr("Process")));
		ui->BoxAngle->setTitle(QString(tr("Angle")));
		ui->LabelAngleType->setText(QString(tr("Angle Type:")));
		ui->LabelAngStart->setText(QString(tr("Start")));
		ui->LabelAngStop->setText(QString(tr("Stop")));
		ui->LabelAngStep->setText(QString(tr("Step")));
		ui->LabelPriSteering->setText(QString(tr("Pri Steering:")));
		ui->LabelSecSteering->setText(QString(tr("Sec Steering:")));
		ui->LlabelRefract->setText(QString(tr("Refract:")));
		ui->LlabelBeamSkew->setText(QString(tr("Beam Skew:")));

		ui->BoxFocalPoint->setTitle(QString(tr("Focal Point")));
		ui->LabelFocalType->setText(QString(tr("Focal Type:")));
		ui->LabelFocalStart->setText(QString(tr("Start")));
		ui->LabelFocalStop->setText(QString(tr("Stop")));
		ui->LabelFocalStep->setText(QString(tr("Step")));
		ui->LabelFocalPosition->setText(QString(tr("Position:")));
		ui->LabelFocalOffset->setText(QString(tr("Offset:")));
		ui->LabelFocalDepth->setText(QString(tr("Depth:")));

		ui->BoxAperture->setTitle(QString(tr("Aperture")));
		ui->LlabelPriAxis->setText(QString(tr("PriAxis")));
		ui->LlabelSecAxis->setText(QString(tr("SecAxis")));
		ui->LabelElementSelect->setText(QString(tr("Element Selected:")));
		ui->LabelElementStart->setText(QString(tr("Start Element:")));
		ui->LabelElementStop->setText(QString(tr("Stop Element:")));
		ui->LabelElementStep->setText(QString(tr("Step Element:")));
		ui->LabelGate->setText(QString(tr("Gate")));
		ui->CheckGateShow->setText(QString(tr("Show")));
		ui->LabelGateSelect->setText(QString(tr("Select:")));
		ui->LabelGateStart->setText(QString(tr("Start:")));
		ui->LabelGateWidth->setText(QString(tr("Width:")));
		ui->LabelGateHeight->setText(QString(tr("Height:")));
		ui->LabelGateSync->setText(QString(tr("Synchro.:")));
		ui->LabelGateMeasure->setText(QString(tr("Measure:")));

		ui->LabelSizingCurves->setText(QString(tr("Sizing Curves")));
		ui->LabelCurveSel->setText(QString(tr("Select:")));
		ui->DacPointPos->setText(QString(tr("Point No.:")));
		ui->BtnAddPoint->setText(QString(tr("ADD")));
		ui->BtnDelPoint->setText(QString(tr("DEL")));
		for(int i = 0; i < setup_DAC_POINT_QTY; i++) {
			m_pSizingCurveName[i]->setText(QString(tr("RefAmplitude:")));
		}
		ui->BoxPart->setTitle(QString(tr("Part")));
		ui->LabelGeometry->setText(QString(tr("Geometry:")));
		ui->LabelMaterial->setText(QString(tr("Material:")));
		ui->LabelPartSize1->setText(QString(tr("Thickness:")));
		ui->CheckShowThickness->setText(QString(tr("Show")));
		ui->LabelPartSize2->setText(QString(tr("Length:")));
		ui->LabelPartSize3->setText(QString(tr("Width:")));
		ui->CheckUnifiedPartSetting->setText(QString(tr("Unified Part setting")));

		ui->BoxPartPosition->setTitle(QString(tr("Position")));
		ui->LabelScanOffset->setText(QString(tr("Scan Offset:")));
		ui->LabelIndexOffset->setText(QString(tr("Index Offset:")));
		ui->LabelSkewAngle->setText(QString(tr("Skew Angle:")));

		ui->LabelPartFile->setText(QString(tr("Weld & Part File")));
		ui->LabelPartFileLoad->setText(QString(tr("Load:")));
		ui->BtnLoadPartFile->setText(QString(tr("Weld")));
		ui->CheckPartFileShow->setText(QString(tr("Show")));
		ui->CheckLwBwShow->setText(QString(tr("Show")));
		ui->LabelTofdScanMode->setText(QString(tr("Scan Mode:")));
		ui->LabelTofdProMode->setText(QString(tr("Process Mode:")));
		ui->LabelTofdWedgeSep->setText(QString(tr("Wedge Seperation:")));
		ui->LabelTofdPcs->setText(QString(tr("PCS:")));
		ui->LabelTofdPcsCal->setText(QString(tr("Cal PCS:")));
		ui->BoxDepthCal->setTitle(QString(tr("Depth Calibration")));
		ui->LabelDepthCal->setText(QString(tr("Depth:")));
		ui->BtnDepthCal->setText(QString(tr("Calibration")));
		ui->LabelMeasureValue->setText(QString(tr("Measure Value")));
		ui->CheckMeasureShow->setText(QString(tr("Show")));
		ui->CheckBackShow->setText(QString(tr("Background")));
		ui->LabelField1->setText(QString(tr("Field 1:")));
		ui->LabelField2->setText(QString(tr("Field 2:")));
		ui->LabelField3->setText(QString(tr("Field 3:")));
		ui->LabelField4->setText(QString(tr("Field 4:")));
		ui->LabelField5->setText(QString(tr("Field 5:")));
		ui->LabelCursor->setText(QString(tr("Cursor")));
		ui->CheckCursorShow->setText(QString(tr("Show")));
		ui->CheckCursorSync->setText(QString(tr("Cursor sync")));
		ui->LabelZeroOff->setText(QString(tr("Wedge delay correction:")));
		ui->LabelDepthStart->setText(QString(tr("Depth start:")));
		ui->LabelDepthEnd->setText(QString(tr("Depth end:")));
		ui->CheckDefectShow->setText(QString(tr("Show")));
		ui->groupBox->setTitle(QString(tr("ColorSetting")));
		ui->LabelAmpColor->setText(QString(tr("Amplitude:")));
		ui->LabelColorRF->setText(QString(tr("RF:")));
		ui->label_5->setText(QString(tr("Thickness:")));
		ui->LabelCScanSource1->setText(QString(tr("C Scan 1 Source:")));
		ui->LabelCScanSource2->setText(QString(tr("C Scan 2 Source:")));
		ui->LabelCScanThickness->setText(QString(tr("C Scan Thickness")));
		ui->LabelCScanThicknessMin->setText(QString(tr("Min:")));
		ui->LabelCScanThicknessMax->setText(QString(tr("Max:")));
		ui->LabelLanguage->setText(QString(tr("Language:")));
		ui->groupBoxComDisp->setTitle(QString(tr("Combination Display")));
		ui->BtnRefurbishComDisp->setText(QString(tr("Refresh")));
		break;
	case setup_LANG_CHINESS:
        ui->toolBox->setItemText(0, QString::fromLocal8Bit("超声设置"));
        ui->toolBox->setItemText(1, QString::fromLocal8Bit("探头/楔块"));
        ui->toolBox->setItemText(2, QString::fromLocal8Bit("聚焦法则"));
        ui->toolBox->setItemText(3, QString::fromLocal8Bit("闸门和曲线"));
        ui->toolBox->setItemText(4, QString::fromLocal8Bit("几何结构"));
        ui->toolBox->setItemText(5, QString::fromLocal8Bit("测量"));
        ui->toolBox->setItemText(6, QString::fromLocal8Bit("显示"));
        ui->BoxGeneral->setTitle(QString::fromLocal8Bit("常规"));
        ui->LabelGain->setText(QString::fromLocal8Bit("增益:"));
        ui->LabelStart->setText(QString::fromLocal8Bit("起点:"));
        ui->LabelCurrentAngle->setText(QString::fromLocal8Bit("当前角度:"));
        ui->LabelRange->setText(QString::fromLocal8Bit("范围:"));
        ui->LabelVelocity->setText(QString::fromLocal8Bit("声速:"));
        ui->LabelWedgeDelay->setText(QString::fromLocal8Bit("楔块延迟:"));
        ui->LabelTravelMode->setText(QString::fromLocal8Bit("声轴单位:"));//"跟踪模式:";
        ui->BoxPulserReceiver->setTitle(QString::fromLocal8Bit("发射/接收"));
        ui->LabelPulser->setText(QString::fromLocal8Bit("脉冲:"));
        ui->LabelReceiver->setText(QString::fromLocal8Bit("接收:"));
        ui->LabelFilter->setText(QString::fromLocal8Bit("滤波:"));
        ui->LabelTxRxMode->setText(QString::fromLocal8Bit("TX RX 模式:"));
        ui->LabelRectifier->setText(QString::fromLocal8Bit("检波方式:"));//(QString("整流器:")));
        ui->LabelViedoFilter->setText(QString::fromLocal8Bit("视频滤波:"));
        ui->CheckVideoFilter->setText(QString::fromLocal8Bit("开/关"));
        ui->LabelPointQty->setText(QString::fromLocal8Bit("采样点:"));//"点数:";
        ui->CheckPointQtyAuto->setText(QString::fromLocal8Bit("自动"));
        ui->LabelSumGain->setText(QString::fromLocal8Bit("总增益:"));
        ui->CheckSumGainAuto->setText(QString::fromLocal8Bit("自动"));
        ui->LabelAverage->setText(QString::fromLocal8Bit("平均:"));//(QString("平均值:")));
        ui->LabelGroupMode->setText(QString::fromLocal8Bit("组模式:"));
        ui->BoxProbeTrigger->setTitle(QString::fromLocal8Bit("Tx 探头"));
        ui->BoxWedgeTrigger->setTitle(QString::fromLocal8Bit("Tx 楔块"));
        ui->BoxProbeTrigger_2->setTitle(QString::fromLocal8Bit("Rx 探头"));
        ui->BoxWedgeTrigger_2->setTitle(QString::fromLocal8Bit("Rx 楔块"));
        ui->LabelLawType->setText(QString::fromLocal8Bit("聚焦法则类型:"));
        ui->BtnProcessLaw->setText(QString::fromLocal8Bit("进行"));
        ui->BoxAngle->setTitle(QString::fromLocal8Bit("角度"));
        ui->LabelAngleType->setText(QString::fromLocal8Bit("角度类型:"));
        ui->LabelAngStart->setText(QString::fromLocal8Bit("起始角"));
        ui->LabelAngStop->setText(QString::fromLocal8Bit("终止角"));
        ui->LabelAngStep->setText(QString::fromLocal8Bit("步进"));
        ui->LabelPriSteering->setText(QString::fromLocal8Bit("主轴偏转角:"));
        ui->LabelSecSteering->setText(QString::fromLocal8Bit("次轴偏转角:"));
        ui->LlabelRefract->setText(QString::fromLocal8Bit("折射角:"));
        ui->LlabelBeamSkew->setText(QString::fromLocal8Bit("声束转向角:"));
        ui->BoxFocalPoint->setTitle(QString::fromLocal8Bit("焦点"));
        ui->LabelFocalType->setText(QString::fromLocal8Bit("聚焦类型:"));
        ui->LabelFocalStart->setText(QString::fromLocal8Bit("起点"));
        ui->LabelFocalStop->setText(QString::fromLocal8Bit("终点"));
        ui->LabelFocalStep->setText(QString::fromLocal8Bit("步距"));
        ui->LabelFocalPosition->setText(QString::fromLocal8Bit("位置:"));
        ui->LabelFocalOffset->setText(QString::fromLocal8Bit("偏移:"));
        ui->LabelFocalDepth->setText(QString::fromLocal8Bit("深度:"));
        ui->BoxAperture->setTitle(QString::fromLocal8Bit("孔径"));
        ui->LlabelPriAxis->setText(QString::fromLocal8Bit("主轴"));
        ui->LlabelSecAxis->setText(QString::fromLocal8Bit("次轴"));
        ui->LabelElementSelect->setText(QString::fromLocal8Bit("阵元数:"));
        ui->LabelElementStart->setText(QString::fromLocal8Bit("起始阵元:"));
        ui->LabelElementStop->setText(QString::fromLocal8Bit("末阵元:"));
        ui->LabelElementStep->setText(QString::fromLocal8Bit("阵元步进:"));
        ui->LabelGate->setText(QString::fromLocal8Bit("闸门"));
        ui->CheckGateShow->setText(QString::fromLocal8Bit("显示"));
        ui->LabelGateSelect->setText(QString::fromLocal8Bit("选择:"));
        ui->LabelGateStart->setText(QString::fromLocal8Bit("起点:"));
        ui->LabelGateWidth->setText(QString::fromLocal8Bit("宽度:"));
        ui->LabelGateHeight->setText(QString::fromLocal8Bit("阈值"));//"高度:";
        ui->LabelGateSync->setText(QString::fromLocal8Bit("同步.:"));
        ui->LabelGateMeasure->setText(QString::fromLocal8Bit("测量:"));

        ui->LabelSizingCurves->setText(QString::fromLocal8Bit("曲线"));
        ui->LabelCurveSel->setText(QString::fromLocal8Bit("类型:"));
        ui->DacPointPos->setText(QString::fromLocal8Bit("序号:"));
        ui->BtnAddPoint->setText(QString::fromLocal8Bit("增加"));
        ui->BtnDelPoint->setText(QString::fromLocal8Bit("删除"));
		for(int i = 0; i < setup_DAC_POINT_QTY; i++) {
            m_pSizingCurveName[i]->setText(QString::fromLocal8Bit("参考幅度:"));
		}
        ui->BoxPart->setTitle(QString::fromLocal8Bit("模块"));
        ui->LabelGeometry->setText(QString::fromLocal8Bit("结构:"));
        ui->LabelMaterial->setText(QString::fromLocal8Bit("材料:"));
        ui->LabelPartSize1->setText(QString::fromLocal8Bit("厚度:"));
        ui->CheckShowThickness->setText(QString::fromLocal8Bit("显示"));
        ui->LabelPartSize2->setText(QString::fromLocal8Bit("长度:"));
        ui->LabelPartSize3->setText(QString::fromLocal8Bit("宽度:"));
        ui->CheckUnifiedPartSetting->setText(QString::fromLocal8Bit("统一模块设置"));
        ui->BoxPartPosition->setTitle(QString::fromLocal8Bit("位置"));
        ui->LabelScanOffset->setText(QString::fromLocal8Bit("扫查偏置:"));
        ui->LabelIndexOffset->setText(QString::fromLocal8Bit("步进偏置:"));
        ui->LabelSkewAngle->setText(QString::fromLocal8Bit("转向角:"));

        ui->LabelPartFile->setText(QString::fromLocal8Bit("焊缝 & 模块文件"));
        ui->LabelPartFileLoad->setText(QString::fromLocal8Bit("加载:"));
        ui->BtnLoadPartFile->setText(QString::fromLocal8Bit("焊缝"));
        ui->CheckPartFileShow->setText(QString::fromLocal8Bit("显示"));
        ui->CheckLwBwShow->setText(QString::fromLocal8Bit("显示"));
        ui->LabelTofdScanMode->setText(QString::fromLocal8Bit("扫描模式:"));
        ui->LabelTofdProMode->setText(QString::fromLocal8Bit("数据处理模式:"));
        ui->LabelTofdWedgeSep->setText(QString::fromLocal8Bit("楔块间距:"));
        ui->LabelTofdPcs->setText(QString::fromLocal8Bit("探头中心间距:"));
        ui->LabelTofdPcsCal->setText(QString::fromLocal8Bit("计算中心间距:"));
        ui->BoxDepthCal->setTitle(QString::fromLocal8Bit("深度校准"));
        ui->LabelDepthCal->setText(QString::fromLocal8Bit("深度:"));
        ui->BtnDepthCal->setText(QString::fromLocal8Bit("校准"));
        ui->LabelMeasureValue->setText(QString::fromLocal8Bit("测量值"));
        ui->CheckMeasureShow->setText(QString::fromLocal8Bit("显示"));
        ui->CheckBackShow->setText(QString::fromLocal8Bit("背景"));
        ui->LabelField1->setText(QString::fromLocal8Bit("区域 1:"));
        ui->LabelField2->setText(QString::fromLocal8Bit("区域 2:"));
        ui->LabelField3->setText(QString::fromLocal8Bit("区域 3:"));
        ui->LabelField4->setText(QString::fromLocal8Bit("区域 4:"));
        ui->LabelField5->setText(QString::fromLocal8Bit("区域 5:"));
        ui->LabelCursor->setText(QString::fromLocal8Bit("光标"));
        ui->CheckCursorShow->setText(QString::fromLocal8Bit("显示"));
        ui->CheckCursorSync->setText(QString::fromLocal8Bit("光标同步"));
        ui->LabelZeroOff->setText(QString::fromLocal8Bit("楔块延时修正值:"));
        ui->LabelDepthStart->setText(QString::fromLocal8Bit("分层起点:"));
        ui->LabelDepthEnd->setText(QString::fromLocal8Bit("分层终点:"));
        ui->CheckDefectShow->setText(QString::fromLocal8Bit("显示"));
        ui->BtnDefectDelete->setText(QString::fromLocal8Bit("删 除"));
        ui->groupBox->setTitle(QString::fromLocal8Bit("颜色设置"));
        ui->LabelAmpColor->setText(QString::fromLocal8Bit("波幅:"));
        ui->LabelColorRF->setText(QString::fromLocal8Bit("射频:"));
        ui->label_5->setText(QString::fromLocal8Bit("厚度:"));
        ui->LabelCScanSource1->setText(QString::fromLocal8Bit("C扫查1数据源:"));
        ui->LabelCScanSource2->setText(QString::fromLocal8Bit("C扫查2数据源:"));
        ui->LabelCScanThickness->setText(QString::fromLocal8Bit("C扫查厚度"));
        ui->LabelCScanThicknessMin->setText(QString::fromLocal8Bit("最小值:"));
        ui->LabelCScanThicknessMax->setText(QString::fromLocal8Bit("最大值:"));
        ui->LabelLanguage->setText(QString::fromLocal8Bit("语言:"));
        ui->groupBoxComDisp->setTitle(QString::fromLocal8Bit("组合显示"));
        ui->BtnRefurbishComDisp->setText(QString::fromLocal8Bit("刷 新"));
		break;
	case setup_LANG_JAPEN:
		break;
	case setup_LANG_KOREA:
		break;
	}
	int iLang = eLang;

	ui->LabelDefect->setText(g_strDefect[0][eLang]);
	ui->LabelReMark->setText(g_strDefect[1][eLang]);
	ui->LabelDefectIndex->setText(g_strDefect[2][eLang]);
	ui->labelDefectStart->setText(g_strDefect[3][eLang]);
	ui->labelDefectLength->setText(g_strDefect[4][eLang]);
	ui->labelDefectDepth->setText(g_strDefect[5][eLang]);
	ui->labelDefectHeight->setText(g_strDefect[6][eLang]);
	ui->labelDefectOffset->setText(g_strDefect[7][eLang]);
	ui->labelDefectWidth->setText(g_strDefect[8][eLang]);
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

	ui->ComGateSelect->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComGateSelect->addItem(g_strGateSelect[i][iLang]);
	}

	ui->ComGateSync->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComGateSync->addItem(g_strGateSync[i][iLang]);
	}

	ui->ComGateMeasure->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComGateMeasure->addItem(g_strGateMeasure[i][iLang]);
	}

	ui->ComSizingCurve->clear();
	for(int i = 0; i < (int)setup_CURVE_TYPE_MAX; i++) {
		ui->ComSizingCurve->addItem(g_strSizingCurve[i][iLang]);
	}

	ui->ComTravelMode->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComTravelMode->addItem(g_strTravelMode[i][iLang]);
	}

	ui->ComTxRxMode->clear();
	for(int i = 0; i < 4; i++) {
		ui->ComTxRxMode->addItem(g_strTxRxMode[i][iLang]);
	}

	ui->ComRectifier->clear();
	for(int i = 0; i < 4; i++) {
		ui->ComRectifier->addItem(g_strRectifier[i][iLang]);
	}

	ui->ComLawType->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComLawType->addItem(g_strLawType[i][iLang]);
	}

	ui->ComAngleType->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComAngleType->addItem(g_strAngleType[i][iLang]);
	}

	ui->ComFocalType->clear();
	for(int i = 0; i < 5; i++) {
		ui->ComFocalType->addItem(g_strFocalType[i][iLang]);
	}

	ui->ComSkewAngle->clear();
	for(int i = 0; i < 4; i++) {
		ui->ComSkewAngle->addItem(g_strSkewAngle[i][iLang]);
	}

	ui->ComColorLineColor->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComColorLineColor->addItem(g_strColorLineColor[i][iLang]);
	}

	ui->ComCScanSource1->clear();
	for(int i = 0; i < 8; i++) {
		ui->ComCScanSource1->addItem(g_strCScanSource[i][iLang]);
	}

	ui->ComCScanSource2->clear();
	for(int i = 0; i < 8; i++) {
		ui->ComCScanSource2->addItem(g_strCScanSource[i][iLang]);
	}

	ui->ComBoxScanMode->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComBoxScanMode->addItem(g_strTofdScanMode[i][iLang]);
	}

	ui->ComBoxProMode->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComBoxProMode->addItem(g_strTofdProMode[i][iLang]);
	}
	//--------------------------------------------------
	//ui->ComLanguage->clear();
	//for(int i = 0; i < 2; i++) {
	//	ui->ComLanguage->addItem(g_strLanguageName[i]);
	//}
	//ui->ComLanguage->setCurrentIndex(iLang);
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
			_str.sprintf("Group%d", i+1) ;
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
	ui->ValueGain->setEnabled(false);
	ui->ValueStart->setEnabled(false);
	ui->ValueRange->setEnabled(false);
	ui->ComCurrentAngle->setEnabled(false);
	ui->ComVelocitySelection->setEnabled(false);
	ui->ValueVelocity->setEnabled(false);
	ui->ValueWedgeDelay->setEnabled(false);
	ui->ComTravelMode->setEnabled(false);

	ui->BoxPulserReceiver->setEnabled(false);
	ui->ValuePointQty->setEnabled(false);
	ui->ComAverage->setEnabled(false);

	ui->CheckPointQtyAuto->setEnabled(false);
	ui->ValueSumGain->setEnabled(false);
	ui->CheckSumGainAuto->setEnabled(false);
	ui->BoxProbeTrigger->setEnabled(false);
	ui->BoxWedgeTrigger->setEnabled(false);
	ui->BoxProbeTrigger_2->setEnabled(false);
	ui->BoxWedgeTrigger_2->setEnabled(false);

	ui->ComLawType->setEnabled(false);
	ui->BtnProcessLaw->setEnabled(false);
	ui->BoxAngle->setEnabled(false);
	ui->BoxFocalPoint->setEnabled(false);
	ui->BoxFocalPoint->setEnabled(false);
	ui->BoxAperture->setEnabled(false);
	ui->ValueGateHeight->setEnabled(false);
//	ui->ValueGateStart->setEnabled(false);
//	ui->ValueGateWidth->setEnabled(false);
	ui->ComGateMeasure->setEnabled(false);
	ui->ComGateSync->setEnabled(false);
	ui->ComGroupMode->setEnabled(false);

	ui->ComGeometry->setEnabled(false);
	ui->ComMaterial->setEnabled(false);
	ui->ValuePartSize2->setEnabled(false);
	ui->ValuePartSize3->setEnabled(false);
	ui->CheckUnifiedPartSetting->setEnabled(false);
	ui->ValueDefectLStart->setEnabled(false);
	ui->ValueDefectLength->setEnabled(false);

	ui->ValueDefectHStart->setEnabled(false);
	ui->ValueDefectHeight->setEnabled(false);

	ui->ValueDefectWStart->setEnabled(false);
	ui->ValueDefectWidth->setEnabled(false);
	//---------------------------------------------------------
	//ui->ComSkewAngle->setEnabled(false);
	ui->ComColorLineColor->setEnabled(false);
	ui->ComColorLineSelection->setEnabled(false);

	ui->BoxProbeTrigger_2->setVisible(false);
	ui->BoxWedgeTrigger_2->setVisible(false);

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
	for( i = 0 ; i < _nQty; i++)
	{
		_pItems[i] = new QStandardItem(tr(g_strDisplayMode[i]));
		QString str = QString(":/icon/display/resource/Display/0-");
		QString tmp; tmp.sprintf("%02d.png", i+1) ;
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
	for(i = 7 ; i< _nQty ; i++)
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
	const QAbstractItemModel* model = index.model() ;
	QString _str1  = model->data(index , Qt::DisplayRole).toString()  ;
	int _nId = model->data(index , Qt::UserRole).toInt() ;
	QVariant icon = model->data(index , Qt::DecorationRole);
	QPixmap pixmap =  (icon.value<QIcon>()).pixmap(48 , 48);

	// setup MimeData
	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	dataStream << _str1 << _nId << m_nGroupId;

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("DOPPLER_DISPLAY_ITEM", itemData);

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

	SCANNER& _scanner = m_pConfig->common.scanner ;
	if(_scanner.eEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelCursorUnit5->setText("sec");
		ui->LabelCursorUnit6->setText("sec");
	} else {
		ui->LabelCursorUnit5->setText("mm");
		ui->LabelCursorUnit6->setText("mm");
	}

	ui->ValueARef->setEnabled(false);
	ui->ValueAMes->setEnabled(false);

	ParameterProcess* _process = ParameterProcess::Instance() ;
	TOFD_PARA* _tofd = m_pConfig->GetTofdConfig(m_nGroupId);
	_process->GetTofdDepth(m_nGroupId , 1 , &_tofd->fDepthCal);
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
	}
	else
	{
		QString _str;
		int _index = _pConfig->m_dfParam[m_nGroupId].index;
		for(int i = 0 ; i < _iCnt ; i ++)
		{
			_str.sprintf("%d", i+1);
			_pBox->addItem(_str);
		}
		_pBox->setCurrentIndex(_index);
		_pBox->setEnabled(true);
	}

	ui->CheckDefectShow->setChecked(m_pGroup->bShowDefect ? Qt::Checked : Qt::Unchecked);
}

void DopplerGroupTab::UpdateDefectValue()
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance();

	ui->lineEditReMark->setText(QString(tr("")));
	ui->lineEditReMark->setEnabled(false);
	ui->ValueDefectLStart->setValue(0);
	ui->ValueDefectLength->setValue(0);
	ui->ValueDefectHStart->setValue(0);
	ui->ValueDefectHeight->setValue(0);
	ui->ValueDefectWStart->setValue(0);
	ui->ValueDefectWidth->setValue(0);

	int _iCnt = _pConfig->GetDefectCnt(m_nGroupId);
	if(_iCnt > 0)
	{
		int   _index = _pConfig->m_dfParam[m_nGroupId].index;
		if(_index < 0)		_index = 0;
		if(_index >= _iCnt) _index = _iCnt - 1;

		char *_pInfo = _pConfig->GetDefectInfo(m_nGroupId, _index);
		ui->lineEditReMark->setText(QString(tr(_pInfo)));
		ui->lineEditReMark->setEnabled(true);

		float _fStart = 0;
		float  _fData = 0;

		_fData = _pConfig->DefectLengthValue(m_nGroupId, &_fStart, _index);
		if(_fData >= 0)
		{
			ui->ValueDefectLStart->setValue(_fStart);
			ui->ValueDefectLength->setValue(_fData);
		}

		_fData = _pConfig->DefectHeightValue(m_nGroupId, &_fStart, _index);
		if(_fData >= 0)
		{
			float _fDepth = _pConfig->DefectDepthValue(m_nGroupId, _index);
			if(_fDepth >= 0) {
				_fStart = _fDepth;
			}
			ui->ValueDefectHStart->setValue(_fStart);
			ui->ValueDefectHeight->setValue(_fData);
		}

		_fData = _pConfig->DefectWidthValue(m_nGroupId, &_fStart, _index);
		if(_fData >= 0)
		{
			ui->ValueDefectWStart->setValue(_fStart);
			ui->ValueDefectWidth->setValue(_fData);
		}
	}
	else
	{
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
void DopplerGroupTab::UpdateGroupConfig ()
{
	ParameterProcess* _process = ParameterProcess::Instance();

	ui->ValueGain->setValue(m_pGroup->fGain) ;
	ui->ValueRefGain->setValue(m_pGroup->fRefGain);
	UpdateCurrentAngleCom();
	UpdateSampleRange();
	ui->ValueWedgeDelay->setValue(m_pGroup->nWedgeDelay / 1000.0);
	ui->ValueVelocity->setValue(m_pGroup->fVelocity);
	ui->ComTravelMode->setCurrentIndex(m_pGroup->eTravelMode);
	ui->ComTxRxMode->setCurrentIndex(m_pGroup->eTxRxMode);
	//QAction* action = ui->ComTxRxMode->actions().at(3) ;
	//if(m_pGroup->eGroupMode == setup_GROUP_MODE_PA )
	//	action->setEnabled(false);
	//else
	//	action->setEnabled( true);

	UpdateVelocitySelection() ;
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

	//************************************************
	//********** Probe and Wedge **********//
	UpdateProbeWedge() ;
	//***********************************************
	//**********	Focallaw	***************//
	UpdateLawConfig();
	//***********************************************
	//**********   Gate and Sizeing curves
	int _nGate = ui->ComGateSelect->currentIndex() ;
	GATE_CONFIG& gate = m_pGroup->gate[_nGate] ;
	ui->CheckGateShow->setCheckState(m_pGroup->bShowGate ? Qt::Checked : Qt::Unchecked);
	ui->ValueGateStart->setValue(gate.fStart);
	ui->ValueGateWidth->setValue(gate.fWidth);
	ui->ValueGateHeight->setValue(gate.nThreshold);
	ui->ComGateSync->setCurrentIndex(gate.eSynChro);
	ui->ComGateMeasure->setCurrentIndex(gate.eMeasure);
	UpdateSizeingCurves();
	//***********************************************
	//  ********** geometry
	InitComBoxMaterialSelection() ;
	ui->ComGeometry->setCurrentIndex(m_pGroup->part.eGeometry);
	UpdateGeometryState();
	ui->CheckShowThickness->setCheckState(m_pGroup->bShowThickness ? Qt::Checked : Qt::Unchecked );
	ui->CheckUnifiedPartSetting->setCheckState(m_pConfig->common.bUnifiedPart ? Qt::Checked : Qt::Unchecked);
	//if(m_nGroupId && m_pConfig->common.bUnifiedPart)   ui->BoxPart->setEnabled(false);

	ui->ValueScanOffset->setValue(m_pGroup->fScanOffset);
	ui->ValueIndexOffset->setValue(m_pGroup->fIndexOffset);
	ui->ComSkewAngle->setCurrentIndex(m_pGroup->eSkew);
	ui->CheckPartFileShow->setChecked(_process->GetShowWeldPart(m_nGroupId));

	SCANNER& _scanner = m_pConfig->common.scanner ;
	if(_scanner.eEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelScanOffsetUnit->setText("sec");
	} else {
		ui->LabelScanOffsetUnit->setText("mm");
	}

	UpdateTofdParam();
	//--------------------------------------------------
	//************************************************
	//*********** measure
	ui->CheckMeasureShow->setCheckState(m_pGroup->bShowMeasure ? Qt::Checked : Qt::Unchecked );
	//ui->CheckBackShow->setCheckState(g_pMainWnd->ParamBackMode() ? Qt::Checked : Qt::Unchecked );
	//ui->CheckBackShow->setChecked(g_pMainWnd->ParamBackMode()); //放开程序崩溃
	ui->ComField1->setCurrentIndex(m_pGroup->aeMeasureType[0]);
	ui->ComField2->setCurrentIndex(m_pGroup->aeMeasureType[1]);
	ui->ComField3->setCurrentIndex(m_pGroup->aeMeasureType[2]);
	ui->ComField4->setCurrentIndex(m_pGroup->aeMeasureType[3]);
	ui->ComField5->setCurrentIndex(m_pGroup->aeMeasureType[4]);
	//************************************************
	//*********** measure
	ui->CheckCursorShow->setCheckState(m_pGroup->bShowCursor ? Qt::Checked : Qt::Unchecked );
	ui->CheckCursorSync->setCheckState(m_pConfig->AppEvn.bSAxisCursorSync ? Qt::Checked : Qt::Unchecked );
	UpdateCursorValue() ;
	UpdateDefectValue() ;

	ui->ComColorLineSelection->setCurrentIndex(0);
	ui->ComColorLineColor->setCurrentIndex(m_pGroup->color.anColor[0]);
	ui->ComCScanSource1->setCurrentIndex(m_pGroup->eCScanSource[0]);
	ui->ComCScanSource2->setCurrentIndex(m_pGroup->eCScanSource[1]);
	ui->ValueCScanThicknessMin->setValue(m_pGroup->fMinThickness);
	ui->ValueCScanThicknessMax->setValue(m_pGroup->fMaxThickness);

	UpdateColorSetting();
	UpdateMeasureBox();
	UpdateDefectBox();
	UpdateParameterLimit();

}
void DopplerGroupTab::UpdateTofdParam()
{
	ui->LabelTofdPcsCal->hide();
	ui->SpinBoxCalPCS->hide();
	ui->LabelCalPCSUnit->hide();
	if(m_pGroup->eTxRxMode != setup_TX_RX_MODE_TOFD )
	{
		ui->BoxPartTofd->hide();
	}
	else
	{
		ui->BoxPartTofd->show();
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

		//ui->SpinBoxDepthCal->setValue(_tofd->fDepthCal);

	}
}

void DopplerGroupTab::UpdateSizeingCurves()
{
	ParameterProcess* _process = ParameterProcess::Instance();

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
	//***************************

	CURVES& _curve = m_pGroup->curve;
	switch(m_pConfig->AppEvn.eLanguage)
	{
	case setup_LANG_ENGLISH:
		if(_curve.eType == setup_CURVE_TYPE_LINEAR_DAC) {
			m_pSizingCurveName[0]->setText(QString(tr("Mat. Atten:")));
			m_pSizingCurveName[1]->setText(QString(tr("Delay:")));
		} else {
			m_pSizingCurveName[0]->setText(QString(tr("RefAmplitude:")));
			m_pSizingCurveName[1]->setText(QString(tr("RefAmplitude:")));
		}
		break;
	case setup_LANG_CHINESS:
		if(_curve.eType == setup_CURVE_TYPE_LINEAR_DAC) {
            m_pSizingCurveName[0]->setText(QString::fromLocal8Bit("衰减系数:"));
            m_pSizingCurveName[1]->setText(QString::fromLocal8Bit("延迟时间:"));
		} else {
            m_pSizingCurveName[0]->setText(QString::fromLocal8Bit("参考幅度:"));
            m_pSizingCurveName[1]->setText(QString::fromLocal8Bit("参考幅度:"));
		}
		break;
	default:
		break;
	}

	//***************************

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
	Limitation _limit ;
	//GROUP_CONFIG& group = m_pConfig->group[nGroupId_] ;
	// Gain
	ui->ValueGain->setMaximum(_limit.GetGroupGainMax(m_nGroupId));
	ui->ValueGain->setMinimum(_limit.GetGroupGainMin(m_nGroupId));
	// Start & Range
	ui->ValueStart->setMaximum(_limit.GetGroupSampleRangeMax(m_nGroupId));
	ui->ValueRange->setMaximum(_limit.GetGroupSampleRangeMax(m_nGroupId) - ui->ValueStart->value());
	//
}


/****************************************************************************
  Description: 聚焦法则类型
*****************************************************************************/
void DopplerGroupTab::UpdateFocallawState()
{
	ui->ComAngleType->setCurrentIndex(0);
	ui->ComAngleType->setEnabled(false);

	ui->ValuePriSteerStart->setEnabled(false);
	ui->ValuePriSteerStep->setEnabled(false);
	ui->ValuePriSteerStop->setEnabled(false);

	ui->ValueSecSteerStart->setEnabled(false);
	ui->ValueSecSteerStep->setEnabled(false);
	ui->ValueSecSteerStop->setEnabled(false);

	ui->ValueSkewStart->setEnabled(false);
	ui->ValueSkewStep->setEnabled(false);
	ui->ValueSkewStop->setEnabled(false);

	ui->ValueElementQtySec->setEnabled(false);
	ui->ValueElementStartSec->setEnabled(false);
	ui->ValueElementStopSec->setEnabled(false);
	ui->ValueElementStepSec->setEnabled(false);

	if(ui->ComLawType->currentIndex() == 0) // angle
	{ // angle
		ui->ValueRefractStart->setEnabled(true);
		ui->ValueRefractStop->setEnabled(true);
		ui->ValueRefractStep->setEnabled(true);

		ui->ValueElementQtyPri->setEnabled(true);
		ui->ValueElementStartPri->setEnabled(true);
		ui->ValueElementStopPri->setEnabled(false);
		ui->ValueElementStepPri->setEnabled(false);
		ui->ValueElementStopPri->setValue(ui->ValueElementQtyPri->value() + ui->ValueElementStartPri->value() - 1 );
	}
	else // linear
	{
		ui->ValueRefractStart->setEnabled(true);
		ui->ValueRefractStop->setEnabled(false);
		ui->ValueRefractStep->setEnabled(false);

		ui->ValueElementQtyPri->setEnabled(true);
		ui->ValueElementStartPri->setEnabled(true);
		ui->ValueElementStopPri->setEnabled(true);
		ui->ValueElementStepPri->setEnabled(true);
		//ui->ValueElementStopPri->setValue(ui->ValueElementQtyPri->value() + ui->ValueElementStartPri->value() - 1 );
	}

	if(ui->ComFocalType->currentIndex() == 0)
	{ // depth
		ui->ValueFocusDepthStart->setEnabled(false);
		ui->ValueFocusDepthStop->setEnabled(false);
		ui->ValueFocusOffsetStart->setEnabled(false);
		ui->ValueFocusOffsetStop->setEnabled(false);
		ui->ValueFocusPositionStart->setEnabled(true);
		ui->ValueFocusPositionStop->setEnabled(false);
		ui->ValueFocusPositionStep->setEnabled(false);

	}
	else if(ui->ComFocalType->currentIndex() == 1)
	{// half path
		ui->ValueFocusDepthStart->setEnabled(false);
		ui->ValueFocusDepthStop->setEnabled(false);
		ui->ValueFocusOffsetStart->setEnabled(false);
		ui->ValueFocusOffsetStop->setEnabled(false);
		ui->ValueFocusPositionStart->setEnabled(true);
		ui->ValueFocusPositionStop->setEnabled(false);
		ui->ValueFocusPositionStep->setEnabled(false);
	}
	else if (ui->ComFocalType->currentIndex() == 2)
	{// projection
		ui->ValueFocusDepthStart->setEnabled(false);
		ui->ValueFocusDepthStop->setEnabled(false);
		ui->ValueFocusOffsetStart->setEnabled(true);
		ui->ValueFocusOffsetStop->setEnabled(false);
		ui->ValueFocusPositionStart->setEnabled(false);
		ui->ValueFocusPositionStop->setEnabled(false);
		ui->ValueFocusPositionStep->setEnabled(false);
	}
	else
	{// focal plane
		ui->ValueFocusDepthStart->setEnabled(true);
		ui->ValueFocusDepthStop->setEnabled(true);
		ui->ValueFocusOffsetStart->setEnabled(true);
		ui->ValueFocusOffsetStop->setEnabled(true);
		ui->ValueFocusPositionStart->setEnabled(false);
		ui->ValueFocusPositionStop->setEnabled(false);
		ui->ValueFocusPositionStep->setEnabled(false);
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
	if (m_pConfig->AppEvn.eLanguage == setup_LANG_ENGLISH)
	{
		ui->LabelPartSize1->setText(QString(tr("Thickness:")));
		ui->LabelPartSize2->setText(QString(tr("Length:")));
		ui->LabelPartSize3->setText(QString(tr("Width:")));
	}
	else if (m_pConfig->AppEvn.eLanguage == setup_LANG_CHINESS)
	{
        ui->LabelPartSize1->setText(QString::fromLocal8Bit("厚度:"));
        ui->LabelPartSize2->setText(QString::fromLocal8Bit("长度:"));
        ui->LabelPartSize3->setText(QString::fromLocal8Bit("宽度:"));
	}
	}
	else
	{
	if (m_pConfig->AppEvn.eLanguage == setup_LANG_ENGLISH)
	{
		ui->LabelPartSize1->setText(QString(tr("Inner Diameter:")));
		ui->LabelPartSize2->setText(QString(tr("Outer Diameter:")));
		ui->LabelPartSize3->setText(QString(tr("Length:")));
	}
	else if (m_pConfig->AppEvn.eLanguage == setup_LANG_CHINESS)
	{
        ui->LabelPartSize1->setText(QString::fromLocal8Bit("内部直径:"));
        ui->LabelPartSize2->setText(QString::fromLocal8Bit("外部直径:"));
        ui->LabelPartSize3->setText(QString::fromLocal8Bit("长度:"));
	}
	}

	ui->ValuePartSize1->setValue(m_pGroup->part.afSize[0]);
	ui->ValuePartSize2->setValue(m_pGroup->part.afSize[1]);
	ui->ValuePartSize3->setValue(m_pGroup->part.afSize[2]);
}

void DopplerGroupTab::on_ValueGain_editingFinished()
{
	double _fValue = ui->ValueGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGain(m_nGroupId , _fValue) ;
}

#include "ProcessDisplay.h"
void DopplerGroupTab::on_ValueRefGain_valueChanged(double)
{
	if(!ui->ValueRefGain->hasFocus())  return ;
	double _fValue = ui->ValueRefGain->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupRefGain(m_nGroupId , _fValue) ;
	ProcessDisplay _display ;
	_display.UpdateAllViewCursorOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueStart_editingFinished()
{
	double _fValue = ui->ValueStart->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();

	if(ui->ComTravelMode->currentIndex() == 0)
	{
		int _nLawId = ui->ComCurrentAngle->currentIndex() ;
		float _fAngle = _process->GetLawAngle(m_nGroupId , _nLawId) ;
		_fValue = _fValue / cos(DEGREE_TO_ARCH(_fAngle))  ;
	}

	_process->SetupSampleStart(m_nGroupId , _fValue) ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}

void DopplerGroupTab::on_ValueRange_editingFinished()
{
	double _fValue = ui->ValueRange->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();

	if(ui->ComTravelMode->currentIndex() == 0)
	{
		int _nLawId = ui->ComCurrentAngle->currentIndex() ;
		float _fAngle = _process->GetLawAngle(m_nGroupId , _nLawId) ;
		_fValue = _fValue / cos(DEGREE_TO_ARCH(_fAngle))  ;
	}
	_process->SetupSampleRange(m_nGroupId , _fValue ) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}

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
	_process->SetupTravelMode(m_nGroupId , index) ;
	UpdateSampleRange();
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

void DopplerGroupTab::on_BtnProbeSelection_clicked()
{
}

void DopplerGroupTab::on_BtnWedgeSelection_clicked()
{
}

void DopplerGroupTab::on_BtnProbeSelection_2_clicked()
{
}

void DopplerGroupTab::on_BtnWedgeSelection_2_clicked()
{
}

void DopplerGroupTab::on_ComLawType_currentIndexChanged(int)
{
	if(!ui->ComLawType->hasFocus())  return ;
	UpdateFocallawState() ;
}


void DopplerGroupTab::on_BtnProcessLaw_clicked()
{
	//qDebug("on_BtnProcessLaw_clicked");

	LAW_CONFIG _law ;
	_law.eLawType = (setup_LAW_TYPE)ui->ComLawType->currentIndex();
	//************  angle  setting ***************
	_law.nAngleStartRefract = ui->ValueRefractStart->value() * 10 ;
	_law.nAngleStepRefract = ui->ValueRefractStep->value() * 10 ;
	_law.nAngleStopRefract = ui->ValueRefractStop->value() * 10 ;
	//************************************************
	//************ focal point
	_law.eFocalType	 = (setup_FOCAL_TYPE)ui->ComFocalType->currentIndex() ;
	_law.fPositionStart = ui->ValueFocusPositionStart->value() ;
	_law.fPositionStop  = ui->ValueFocusPositionStop->value() ;
	_law.fPositionStep  = ui->ValueFocusPositionStep->value() ;
	_law.fOffsetStart   = ui->ValueFocusOffsetStart->value() ;
	_law.fOffsetStop	= ui->ValueFocusOffsetStop->value() ;
	_law.fDepthStart	= ui->ValueFocusDepthStart->value() ;
	_law.fDepthStop	 = ui->ValueFocusDepthStop->value() ;
	//***********************************************
	//************ element selection
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

void DopplerGroupTab::on_ValuePriSteerStart_editingFinished()
{

}

void DopplerGroupTab::on_ValuePriSteerStop_editingFinished()
{

}

void DopplerGroupTab::on_ValuePriSteerStep_editingFinished()
{

}

void DopplerGroupTab::on_ValueSecSteerStart_editingFinished()
{

}

void DopplerGroupTab::on_ValueSecSteerStop_editingFinished()
{

}

void DopplerGroupTab::on_ValueSecSteerStep_editingFinished()
{

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

//&&&&&&&&&&&&&
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

void DopplerGroupTab::on_ValueSkewStart_editingFinished()
{

}

void DopplerGroupTab::on_ValueSkewStop_editingFinished()
{

}

void DopplerGroupTab::on_ValueSkewStep_editingFinished()
{

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

void DopplerGroupTab::on_ValueFocusOffsetStart_editingFinished()
{

}

void DopplerGroupTab::on_ValueFocusOffsetStop_editingFinished()
{

}

void DopplerGroupTab::on_ValueFocusDepthStart_editingFinished()
{

}

void DopplerGroupTab::on_ValueFocusDepthStop_editingFinished()
{

}

void DopplerGroupTab::on_ValueElementQtyPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementQtySec_editingFinished()
{

}

void DopplerGroupTab::on_ValueElementStartPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStartSec_editingFinished()
{

}

void DopplerGroupTab::on_ValueElementStopPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStopSec_editingFinished()
{

}

void DopplerGroupTab::on_ValueElementStepPri_editingFinished()
{
	ElementAlign() ;
}

void DopplerGroupTab::on_ValueElementStepSec_editingFinished()
{

}

//*****************************************
// gate
void DopplerGroupTab::on_ComGateSelect_currentIndexChanged(int index)
{
	if(!ui->ComGateSelect->hasFocus())  return ;
	GROUP_CONFIG& group = m_pConfig->group[m_nGroupId] ;
	GATE_CONFIG& _gate = group.gate[index] ;
	ui->ValueGateStart->setValue(_gate.fStart);
	ui->ValueGateWidth->setValue(_gate.fWidth);
	ui->ValueGateHeight->setValue(_gate.nThreshold);

	if(index == 2) //gate i
	{
		ui->ComGateSync->setCurrentIndex(0);
		ui->ComGateMeasure->setCurrentIndex(0);
		ui->ComGateMeasure->setEnabled(false);
		ui->ComGateSync->setEnabled(false);
	}
	else
	{
		ui->ComGateMeasure->setEnabled(true);
		ui->ComGateSync->setEnabled(true);
		ui->ComGateSync->setCurrentIndex(_gate.eSynChro);
		ui->ComGateMeasure->setCurrentIndex(_gate.eMeasure);
	}
}

#include "ProcessDisplay.h"
void DopplerGroupTab::on_CheckGateShow_clicked(bool checked)
{
	m_pGroup->bShowGate = checked ;
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
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGateInfo(m_nGroupId , (setup_GATE_NAME)ui->ComGateSelect->currentIndex() , &_gate) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueGateStart_valueChanged(double arg)
{
	if(!ui->ValueGateStart->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueGateWidth_valueChanged(double arg)
{
	if(!ui->ValueGateWidth->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ValueGateHeight_valueChanged(double arg)
{
	if(!ui->ValueGateHeight->hasFocus())  return ;
	GatePro();
}
void DopplerGroupTab::on_ComGateSync_currentIndexChanged(int /*index*/)
{
	if(!ui->ComGateSync->hasFocus())  return ;
	GatePro();
}

void DopplerGroupTab::on_ComGateMeasure_currentIndexChanged(int /*index*/)
{
	if(!ui->ComGateMeasure->hasFocus())  return ;
	GatePro();
	UpdateMeasureBox();
}
/*
void DopplerGroupTab::on_ValueGateStart_editingFinished()
{
	GATE_CONFIG _gate ;
	_gate.fStart = ui->ValueGateStart->value() ;
	_gate.fWidth = ui->ValueGateWidth->value() ;
	_gate.nThreshold = ui->ValueGateHeight->value();
	_gate.eMeasure   = ui->ComGateMeasure->currentIndex() ;
	_gate.eSynChro   = ui->ComGateSync->currentIndex() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupGateInfo(m_nGroupId , (setup_GATE_NAME)ui->ComGateSelect->currentIndex() , &_gate) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ValueGateWidth_editingFinished()
{
	on_ValueGateStart_editingFinished() ;
}

void DopplerGroupTab::on_ValueGateHeight_editingFinished()
{
	on_ValueGateWidth_editingFinished();
}

void DopplerGroupTab::on_ComGateSync_currentIndexChanged(int)
{
	if(!ui->ComGateSync->hasFocus())  return ;
	on_ValueGateWidth_editingFinished();
}

void DopplerGroupTab::on_ComGateMeasure_currentIndexChanged(int)
{
	if(!ui->ComGateMeasure->hasFocus())  return ;
	on_ValueGateStart_editingFinished();

	UpdateMeasureBox();
}
*/
void DopplerGroupTab::on_CheckShowThickness_clicked(bool checked)
{
	m_pGroup->bShowThickness = checked  ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComGeometry_currentIndexChanged(int)
{
	if(!ui->ComGeometry->hasFocus())  return ;
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
	_process->SetupPartGeometry (m_nGroupId , &_part) ;
	ProcessDisplay _display ;
	_display.UpdateAllView();
	g_pMainWnd->RunDrawThreadOnce(true);
	UpdateDefectValue();
}

void DopplerGroupTab::on_ValuePartSize1_valueChanged(double)
{
	if(!ui->ValuePartSize1->hasFocus())  return ;
	PartPro();
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

/*
void DopplerGroupTab::on_ValuePartSize1_editingFinished()
{
	PART_CONFIG _part ;
	_part.eGeometry = (setup_PART_GEOMETRY)ui->ComGeometry->currentIndex() ;
	_part.afSize[0] = ui->ValuePartSize1->value() ;
	_part.afSize[1] = ui->ValuePartSize2->value() ;
	_part.afSize[2] = ui->ValuePartSize3->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPartInfoGeometry (m_nGroupId , &_part) ;
	ProcessDisplay _display ;
	_display.UpdateAllView();
}

void DopplerGroupTab::on_ValuePartSize2_editingFinished()
{
	on_ValuePartSize1_editingFinished() ;
}

void DopplerGroupTab::on_ValuePartSize3_editingFinished()
{
	on_ValuePartSize1_editingFinished() ;
}
*/

void DopplerGroupTab::on_ComMaterial_currentIndexChanged(int index)
{
	if(!ui->ComMaterial->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPartMaterial(m_nGroupId ,  index) ;
	ui->ValueVelocity->setValue(m_pGroup->fVelocity);
	UpdateVelocitySelection() ;
}

void DopplerGroupTab::on_CheckUnifiedPartSetting_clicked(bool)
{
}

//void DopplerGroupTab::on_ValueScanOffset_valueChanged()
void DopplerGroupTab::on_ValueScanOffset_editingFinished()
{
	if(!ui->ValueScanOffset->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue1 = ui->ValueScanOffset->value()  ;
	double _fValue2 = ui->ValueIndexOffset->value() ;
	_process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	_pConfig->ResetShadowData();

	g_pMainWnd->RunDrawThreadOnce(true);
	ProcessDisplay _display ;
	//_display.UpdateAllViewOfGroup(m_nGroupId);
	_display.UpdateAllView();
	sleep(20);
	_display.UpdateAllView();
	g_pMainWnd->RunDrawThreadOnce(true);
	sleep(20);
}

void DopplerGroupTab::on_ValueIndexOffset_editingFinished()
{
	if(!ui->ValueIndexOffset->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue1 = ui->ValueScanOffset->value()  ;
	double _fValue2 = ui->ValueIndexOffset->value() ;
	_process->SetupWedgePosition(m_nGroupId ,  _fValue1 , _fValue2) ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
	g_pMainWnd->RunDrawThreadOnce(true);
}

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

#include "dialog/DialogWeldPartLoad.h"
void DopplerGroupTab::on_BtnLoadPartFile_clicked()
{
	DialogWeldPartLoad _dialog(this);
	int _nRet = _dialog.exec();

	if(_nRet)
	{
		ParameterProcess* _process = ParameterProcess::Instance();
		_process->SetupPart(m_nGroupId,  _dialog.GetPart());
	}

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}
void DopplerGroupTab::on_CheckLwBwShow_clicked(bool checked)
{
	m_pGroup->bShowLwBw = checked;
	ProcessDisplay _display ;
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

void DopplerGroupTab::on_CheckPartFileShow_clicked(bool checked)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupShowWeldPart(m_nGroupId , checked)  ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOfGroup(m_nGroupId);
}

void DopplerGroupTab::on_CheckMeasureShow_clicked(bool checked)
{
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupShowMeasure(m_nGroupId , checked)  ;
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

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField2_currentIndexChanged(int index)
{
	if(!ui->ComField2->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 1 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField3_currentIndexChanged(int index)
{
	if(!ui->ComField3->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 2 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField4_currentIndexChanged(int index)
{
	if(!ui->ComField4->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 3 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

void DopplerGroupTab::on_ComField5_currentIndexChanged(int index)
{
	if(!ui->ComField5->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupMeasureData(m_nGroupId , 4 , index)  ;

	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
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

void DopplerGroupTab::on_ValueARef_valueChanged(double)
{
	if(!ui->ValueARef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueARef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_A_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueAMes_valueChanged(double)
{
	if(!ui->ValueAMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueAMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_A_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueURef_valueChanged(double)
{
	if(!ui->ValueURef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueURef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_U_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
	ui->ValueARef->setValue(m_pGroup->afCursor[setup_CURSOR_A_REF]);
}
void DopplerGroupTab::on_ValueUMes_valueChanged(double)
{
	if(!ui->ValueUMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueUMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_U_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
	ui->ValueAMes->setValue(m_pGroup->afCursor[setup_CURSOR_A_MES]);
}
void DopplerGroupTab::on_ValueSRef_valueChanged(double)
{
	if(!ui->ValueSRef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueSRef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_S_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueSMes_valueChanged(double)
{
	if(!ui->ValueSMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueSMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_S_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueIRef_valueChanged(double)
{
	if(!ui->ValueIRef->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueIRef->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_I_REF , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}
void DopplerGroupTab::on_ValueIMes_valueChanged(double)
{
	if(!ui->ValueIMes->hasFocus()) return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _fValue = ui->ValueIMes->value() ;
	_process->SetupCursor(m_nGroupId , setup_CURSOR_I_MES , _fValue)  ;

	if(ui->CheckCursorShow->checkState())
	{
		ProcessDisplay _display ;
		_display.UpdateAllViewOverlay();
	}
	if(ui->CheckMeasureShow->checkState())
	{
		 g_pMainWnd->RunDrawThreadOnce(true);
	}
}

#include "dialog/DialogColorSelect.h"
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
	m_pGroup->fMinThickness = ui->ValueCScanThicknessMin->value() ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void DopplerGroupTab::on_ValueCScanThicknessMax_valueChanged(double)
{
	if(!ui->ValueCScanThicknessMax->hasFocus()) return ;
	m_pGroup->fMaxThickness = ui->ValueCScanThicknessMax->value() ;

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
	g_pMainWnd->RunDrawThreadOnce(true);
}
/*
void DopplerGroupTab::on_ValueCScanThicknessMin_editingFinished()
{
	m_pGroup->fMinThickness = ui->ValueCScanThicknessMin->value() ;
}

void DopplerGroupTab::on_ValueCScanThicknessMax_editingFinished()
{
	m_pGroup->fMaxThickness = ui->ValueCScanThicknessMax->value() ;
}
*/
void DopplerGroupTab::on_ComCScanSource1_currentIndexChanged(int index)
{
	if(!ui->ComCScanSource1->hasFocus()) return ;
	m_pGroup->eCScanSource[0] = (setup_CSCAN_SOURCE_MODE)index ;
	g_pMainWnd->UpdateAllDisplay();
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_ComCScanSource2_currentIndexChanged(int index)
{
	if(!ui->ComCScanSource2->hasFocus()) return ;
	m_pGroup->eCScanSource[1] = (setup_CSCAN_SOURCE_MODE)index ;
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
	m_pGroup->bShowDefect = checked ;
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComDefectIndex_currentIndexChanged(int index)
{
	if(!ui->ComDefectIndex->hasFocus()) return ;
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	_pConfig->m_dfParam[m_nGroupId].index = index;
	UpdateDefectValue() ;
	g_pMainWnd->RunDrawThreadOnce();
}

void DopplerGroupTab::on_lineEditReMark_textChanged(QString str)
{
	if(!ui->lineEditReMark->hasFocus()) return ;
	//QString str = ui->lineEditReMark->text();
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _index = _pConfig->m_dfParam[m_nGroupId].index;
	_pConfig->SetDefectInfo(m_nGroupId, _index, (char*)(qPrintable(str)));

	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}
void DopplerGroupTab::on_BtnDefectDelete_clicked()
{
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	int _index = _pConfig->m_dfParam[m_nGroupId].index;

	_pConfig->DeleteDefect(m_nGroupId, _index);

	UpdateDefectBox();
	UpdateDefectValue() ;
//  g_pMainWnd->RunDrawThreadOnce();
	ProcessDisplay _display ;
	_display.UpdateAllViewOverlay();
}

void DopplerGroupTab::on_ComLanguage_currentIndexChanged(int index_)
{
	if(!ui->ComLanguage->hasFocus()) return ;

	setup_LANG _eLang;
	switch(index_)
	{
	case 0:  _eLang = setup_LANG_ENGLISH;  break;
	case 1:  _eLang = setup_LANG_CHINESS;  break;
	case 2:  _eLang = setup_LANG_JAPEN;  break;
	case 3:  _eLang = setup_LANG_KOREA;  break;
	default: return;
	}
	m_pConfig->AppEvn.eLanguage = _eLang;
	g_pMainWnd->SetWndName(_eLang);

/*	SetWndName(m_pConfig->AppEvn.eLanguage);
	UpdateGroupConfig ();*/
}
