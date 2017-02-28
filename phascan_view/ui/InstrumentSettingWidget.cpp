#include "InstrumentSettingWidget.h"
#include "ui_InstrumentSettingWidget.h"

#include "DopplerConfigure.h"
#include "ParameterProcess.h"

#include <QSlider>

InstrumentSettingWidget::InstrumentSettingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::InstrumentSettingWidget)
{
	ui->setupUi(this);
    m_pConfig = DopplerConfigure::Instance();
	InitCommonConfig();
}

InstrumentSettingWidget::~InstrumentSettingWidget()
{
	delete ui;
}


void InstrumentSettingWidget::showEvent (QShowEvent *event)
{
	InitCommonConfig();
	QWidget::showEvent(event) ;
}

void InstrumentSettingWidget::UpdateEncoderInfo()
{
	SCANNER& _scanner = m_pConfig->common.scanner ;
	int _nEncoder = ui->ComEncoderTypeSetting->currentIndex() + 1;
	ENCODER_CONFIG& _encoder = _scanner.encoder[_nEncoder] ;
	ui->ValueEncoderResolution->setValue(_encoder.fResulotion);
	ui->ComEncoderPolarity->setCurrentIndex(_encoder.ePolarity);
	ui->ComEncoderDirection->setCurrentIndex(_encoder.eEncoderMode);
	ui->ValueEncoderOrg->setValue(_encoder.fOrigin);
}

void InstrumentSettingWidget::UpdateScanRange()
{
	SCANNER& _scanner = m_pConfig->common.scanner ;
	ui->ValueScanStart->setValue(_scanner.fScanStart);
	ui->ValueScanEnd->setValue(_scanner.fScanStop);
	ui->ValueScanResolution->setValue(_scanner.fScanStep);
	ui->ValueIndexStart->setValue(_scanner.fIndexStart);
	ui->ValueIndexStop->setValue(_scanner.fIndexStop);
	ui->ValueIndexResolution->setValue(_scanner.fIndexStep);
}

void InstrumentSettingWidget::InitCommonConfig()
{
	COMMON_CONFIG& config = m_pConfig->common ;
	ui->ComScanType->setCurrentIndex(config.scanner.eScanType);
	ui->ComEncoderType->setCurrentIndex(config.scanner.eEncoderType);
	ui->ComEncoderTypeSetting->setCurrentIndex(0);
	ui->ValuePrf->setValue(config.scanner.fPrf);

	ui->ComVoltagePa->setCurrentIndex(config.instrument.eVoltagePA);
	ui->ComVoltageUt->setCurrentIndex(config.instrument.eVoltageUT);

    UpdateScanRange();
    UpdateEncoderInfo();

	SCANNER& _scanner = m_pConfig->common.scanner ;
	if(_scanner.eEncoderType == setup_ENCODER_TYPE_TIMER) {
		ui->LabelScanPosUnit->setText("sec");
	} else {
		ui->LabelScanPosUnit->setText("mm");
	}
	ui->LabelIndexPosUnit->setText("mm");

	ui->SpinBoxCurrentScanPos->setMaximum(_scanner.fScanStop);
	ui->SpinBoxCurrentScanPos->setMinimum(_scanner.fScanStart);
	ui->SpinBoxCurrentScanPos->setSingleStep(_scanner.fScanStep);
	ui->SliderCurrentScanPos->setMinimum(0);
	ui->SliderCurrentScanPos->setSingleStep(1);
	ui->SliderCurrentScanPos->setMaximum( (_scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep + 0.5);

    UpdateScanPos();
    SetItemInvalide();
}

void InstrumentSettingWidget::SetItemInvalide()
{
    ui->groupBox->setDisabled(true);
    ui->BoxScanArea->setDisabled(true);
    ui->BoxEncoderMode->setDisabled(true);
    ui->groupBoxVoltage->setDisabled(true);
    ui->SpinBoxCurrentIndexPos->setDisabled(true);
}

void InstrumentSettingWidget::UpdateScanPos()
{
	SCANNER& _scanner = m_pConfig->common.scanner ;
	double _fScanPos = _scanner.fScanPos ;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nPos = _process->SAxisDistToIndex(_scanner.fScanPos);

	ui->SpinBoxCurrentScanPos->setValue(_fScanPos) ;
	ui->SliderCurrentScanPos->setValue(_nPos);
}

void InstrumentSettingWidget::ResetEncoderSetting()
{
	ENCODER_CONFIG _encoder ;
	_encoder.ePolarity	= (setup_ENCODER_POLARITY)ui->ComEncoderPolarity->currentIndex() ;
	_encoder.eEncoderMode = (setup_ENCODER_MODE) ui->ComEncoderDirection->currentIndex();
	_encoder.fOrigin	  = ui->ValueEncoderOrg->value() ;
	_encoder.fResulotion  = ui->ValueEncoderResolution->value() ;
	ParameterProcess* _process = ParameterProcess::Instance();
	int nEncoder = ui->ComEncoderTypeSetting->currentIndex() + 1 ;
	_process->SetupEncoderConfigure((setup_ENCODER_TYPE)nEncoder , &_encoder);
}

void InstrumentSettingWidget::on_ComScanType_currentIndexChanged(int index)
{
	if(!ui->ComScanType->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupScanType((setup_SCAN_TYPE)index) ;
}

void InstrumentSettingWidget::on_ComEncoderType_currentIndexChanged(int index)
{
	if(!ui->ComEncoderType->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupEncoderType((setup_ENCODER_TYPE)index) ;
}

void InstrumentSettingWidget::on_ComEncoderTypeSetting_currentIndexChanged(int)
{
	if(!ui->ComEncoderTypeSetting->hasFocus())  return ;
	UpdateEncoderInfo()  ;
}


void InstrumentSettingWidget::on_ComEncoderPolarity_currentIndexChanged(int)
{
	if(!ui->ComEncoderPolarity->hasFocus())  return ;
	ResetEncoderSetting();
}

void InstrumentSettingWidget::on_ComEncoderDirection_currentIndexChanged(int)
{
	if(!ui->ComEncoderDirection->hasFocus())  return ;
	ResetEncoderSetting();
}


void InstrumentSettingWidget::on_ComVoltagePa_currentIndexChanged(int index)
{
	if(!ui->ComVoltagePa->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupPAVoltage((setup_VOLTAGE_MODE)index) ;
}

void InstrumentSettingWidget::on_ComVoltageUt_currentIndexChanged(int index)
{
	if(!ui->ComVoltageUt->hasFocus())  return ;
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupUTVoltage((setup_VOLTAGE_MODE)index) ;
}

//void InstrumentSettingWidget::on_ComTRPA_currentIndexChanged(int index)
//{
//	if(!ui->ComTRPA->hasFocus())  return ;
//	ParameterProcess* _process = ParameterProcess::Instance();
//	_process->SetupPATxRxMode((setup_TX_RX_MODE)index) ;
//}

//void InstrumentSettingWidget::on_ComTRUT_currentIndexChanged(int index)
//{
//	if(!ui->ComTRUT->hasFocus())  return ;
//	ParameterProcess* _process = ParameterProcess::Instance();
//	_process->SetupUTTxRxMode((setup_TX_RX_MODE)index) ;
//}

void InstrumentSettingWidget::on_ValuePrf_editingFinished()
{
	ParameterProcess* _process = ParameterProcess::Instance();
	float _fPrf = ui->ValuePrf->value() ;
	_process->SetupPrf(_fPrf)  ;
}

void InstrumentSettingWidget::on_ValueScanStart_editingFinished()
{
	float _afValue[6] ;
	_afValue[0] =  ui->ValueScanStart->value() ;
	_afValue[1] =  ui->ValueIndexStart->value();
	_afValue[2] =  ui->ValueScanEnd->value()   ;
	_afValue[3] =  ui->ValueIndexStop->value() ;
	_afValue[4] =  ui->ValueScanResolution->value() ;
	_afValue[5] =  ui->ValueIndexResolution->value();
	ParameterProcess* _process = ParameterProcess::Instance();
	_process->SetupScanArea(_afValue);
}

void InstrumentSettingWidget::on_ValueScanEnd_editingFinished()
{
	on_ValueScanStart_editingFinished();
}

void InstrumentSettingWidget::on_ValueScanResolution_editingFinished()
{
	on_ValueScanStart_editingFinished();
}

void InstrumentSettingWidget::on_ValueIndexStart_editingFinished()
{
	on_ValueScanStart_editingFinished();
}

void InstrumentSettingWidget::on_ValueIndexStop_editingFinished()
{
	on_ValueScanStart_editingFinished();
}

void InstrumentSettingWidget::on_ValueIndexResolution_editingFinished()
{
	on_ValueScanStart_editingFinished();
}

void InstrumentSettingWidget::on_ValueEncoderResolution_editingFinished()
{
	ResetEncoderSetting();
}

void InstrumentSettingWidget::on_ValueEncoderOrg_editingFinished()
{
	ResetEncoderSetting();
}

#include "ProcessDisplay.h"
#include "MainWindow.h"
void InstrumentSettingWidget::on_SpinBoxCurrentScanPos_valueChanged(double arg1)
{
	if(!ui->SpinBoxCurrentScanPos->hasFocus())  return ;
	 SCANNER& _scanner = m_pConfig->common.scanner ;

	 ParameterProcess* _process = ParameterProcess::Instance();

	 int _nPos1 = arg1  + 0.5;
	 int _nPos2 = _process->SAxisDistToIndex(_scanner.fScanPos);
	 if(_nPos1 == _nPos2)  return ;

	 _scanner.fScanPos = arg1 ;
	 ui->SliderCurrentScanPos->setValue(_nPos1);

	 ProcessDisplay _proDisplay ;
	 _proDisplay.UpdateAllView();
	 g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::on_SliderCurrentScanPos_valueChanged(int value)
{
	if(!ui->SliderCurrentScanPos->hasFocus()) return ;
	SCANNER& _scanner = m_pConfig->common.scanner	;

	ParameterProcess* _process = ParameterProcess::Instance();
	int _nPos = _process->SAxisDistToIndex(_scanner.fScanPos);
	if(_nPos == value)  return ;

	if(_scanner.eEncoderType) {
		_scanner.fScanPos = _scanner.fScanStep * value + _scanner.fScanStart ;
	} else {
		_scanner.fScanPos =  value / _scanner.fPrf  + _scanner.fScanStart ;
	}
	ui->SpinBoxCurrentScanPos->setValue(_scanner.fScanPos);

	 ProcessDisplay _proDisplay ;
	_proDisplay.UpdateAllView();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::retranslateUi()
{
    ui->retranslateUi(this);
}

