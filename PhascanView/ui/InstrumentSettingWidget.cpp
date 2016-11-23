#include "InstrumentSettingWidget.h"
#include "ui_InstrumentSettingWidget.h"
#include <configure/DopplerConfigure.h>
#include <process/ParameterProcess.h>
#include <QSlider>

InstrumentSettingWidget::InstrumentSettingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::InstrumentSettingWidget)
{
	ui->setupUi(this);
	m_pConfig = DopplerConfigure::Instance()  ;
	SetWndName(m_pConfig->AppEvn.eLanguage); // whuan language 2015-05-19
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
	//ui->ComTRPA->setCurrentIndex(config.instrument.eTxRxModePA);
	//ui->ComTRUT->setCurrentIndex(config.instrument.eTxRxModeUT);

	UpdateScanRange()   ;
	UpdateEncoderInfo() ;

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

	UpdateScanPos()  ;
	SetItemInvalide() ;
}

void InstrumentSettingWidget::SetItemInvalide()
{
	ui->ComEncoderType->setEnabled(false);
	ui->ComScanType->setEnabled(false);
	ui->ValueScanEnd->setEnabled(false);
	ui->ValueScanStart->setEnabled(false);
	ui->ValueScanResolution->setEnabled(false);
	ui->ValueIndexResolution->setEnabled(false);
	ui->ValueIndexStart->setEnabled(false);
	ui->ValueIndexStop->setEnabled(false);
	ui->BoxEncoderMode->setEnabled(false);
	ui->SpinBoxCurrentIndexPos->setEnabled(false);
	ui->SliderCurrentIndexPos->setEnabled(false);
	ui->ValuePrf->setEnabled(false);
	ui->ComVoltagePa->setEnabled(false);
	ui->ComVoltageUt->setEnabled(false);
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

void InstrumentSettingWidget::SetWndName(setup_LANG eLang)
{
	switch(eLang)
	{
	case setup_LANG_ENGLISH:
		ui->LabelScanType->setText(QString(tr("Scan Type:")));
		ui->LabelEncoderType->setText(QString(tr("Encoder Type:")));
		ui->LabelPrf->setText(QString(tr("PRF:")));

		ui->BoxScanArea->setTitle(QString(tr("Area")));
		ui->LabelPaValtage_2->setText(QString(tr("Scan Axis")));
		ui->LabelPaValtage_3->setText(QString(tr("Index Axis")));
		ui->LabelScanStart->setText(QString(tr("Start:")));
		ui->LabelScanEnd->setText(QString(tr("End:")));
		ui->LabelScanResolution->setText(QString(tr("Resolution:")));

		ui->BoxEncoderMode->setTitle(QString(tr("Encoder Mode")));
		ui->LabelEncoderType_2->setText(QString(tr("Encoder Type:")));
		ui->LabelResolution->setText(QString(tr("Resolution:")));
		ui->LabelEncoderPolarity->setText(QString(tr("Polarity:")));
		ui->LabelEncoderDirection->setText(QString(tr("Direction:")));
		ui->LabelEncoderOrg->setText(QString(tr("Origin:")));

		ui->LabelPaValtage->setText(QString(tr("PA Voltage:")));
		ui->LabelUtVolatage->setText(QString(tr("UT Voltage:")));

		ui->LabelScanPos->setText(QString(tr("Current Scan Pos:")));
		ui->LabelIndexPos->setText(QString(tr("Current Index Pos:")));

		break;
	case setup_LANG_CHINESS:
		ui->LabelScanType->setText(QString(tr("扫查方式:")));
		ui->LabelEncoderType->setText(QString(tr("编码器:")));
		ui->LabelPrf->setText(QString(tr("重复频率:")));

		ui->BoxScanArea->setTitle(QString(tr("扫查区域")));
		ui->LabelPaValtage_2->setText(QString(tr("扫查轴")));
		ui->LabelPaValtage_3->setText(QString(tr("步进轴")));
		ui->LabelScanStart->setText(QString(tr("起点:")));
		ui->LabelScanEnd->setText(QString(tr("终点:")));
		ui->LabelScanResolution->setText(QString(tr("分辨率:")));

		ui->BoxEncoderMode->setTitle(QString(tr("编码器类型")));
		ui->LabelEncoderType_2->setText(QString(tr("编码器:")));
		ui->LabelResolution->setText(QString(tr("精度:")));
		ui->LabelEncoderPolarity->setText(QString(tr("极性:")));
		ui->LabelEncoderDirection->setText(QString(tr("类型:")));
		ui->LabelEncoderOrg->setText(QString(tr("编码器起点:")));

		ui->LabelPaValtage->setText(QString(tr("PA 发射电压:")));
		ui->LabelUtVolatage->setText(QString(tr("UT 发射电压:")));

		ui->LabelScanPos->setText(QString(tr("扫描轴当前位置:")));
		ui->LabelIndexPos->setText(QString(tr("步进轴当前位置:")));

		break;

	case setup_LANG_JAPEN:
		break;
	case setup_LANG_KOREA:
		break;
	}
		int iLang = eLang;

	ui->ComScanType->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComScanType->addItem(g_strScanType[i][iLang]);
	}

	ui->ComEncoderType->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComEncoderType->addItem(g_strEncoderType[i][iLang]);
	}

	ui->ComEncoderTypeSetting->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComEncoderTypeSetting->addItem(g_strEncoderType[i+1][iLang]);
	}

	ui->ComEncoderPolarity->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComEncoderPolarity->addItem(g_strPolarity[i][iLang]);
	}

	ui->ComEncoderDirection->clear();
	for(int i = 0; i < 3; i++) {
		ui->ComEncoderDirection->addItem(g_strDirection[i][iLang]);
	}
}

