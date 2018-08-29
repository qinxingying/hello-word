#include "InstrumentSettingWidget.h"
#include "ui_InstrumentSettingWidget.h"

#include "DopplerConfigure.h"
#include "ParameterProcess.h"

#include <QSlider>

#include "ProcessDisplay.h"
#include "MainWindow.h"

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
    if(_scanner.eEncoderType)
        ui->ValueScanEnd->setValue(_scanner.fScanStop);
    else
        ui->ValueScanEnd->setValue(_scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart);
	ui->ValueScanResolution->setValue(_scanner.fScanStep);
	ui->ValueIndexStart->setValue(_scanner.fIndexStart);
	ui->ValueIndexStop->setValue(_scanner.fIndexStop);
	ui->ValueIndexResolution->setValue(_scanner.fIndexStep);
}
#include "qdebug.h"
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
        ui->LabelScanStartUnit_2->setText("sec");
        ui->LabelScanStopUnit->setText("sec");
        ui->LabelIndexStartUnit->setText("   ");
        ui->LabelIndexStopUnit->setText("   ");
	} else {
		ui->LabelScanPosUnit->setText("mm");
        ui->LabelScanStartUnit_2->setText("mm");
        ui->LabelScanStopUnit->setText("mm");
        ui->LabelIndexStartUnit->setText("  ");
        ui->LabelIndexStopUnit->setText("  ");
	}
	ui->LabelIndexPosUnit->setText("mm");
    ParameterProcess* _process = ParameterProcess::Instance();
    double fstart,fstop,fstart2,fstop2,fstep;
    _process->ChangeCscanIndexRange(&fstart,&fstop,&fstart2,&fstop2,&fstep);


    ui->SpinBoxCurrentScanPos->setMinimum(_scanner.fScanStart);

    ui->SpinBoxCurrentScanend->setMinimum(_scanner.fScanStart2+1);
    if(_scanner.eEncoderType)
    {
        ui->SpinBoxCurrentScanPos->setMaximum(_scanner.fScanStop);
        ui->SpinBoxCurrentScanstart->setMaximum(_scanner.fScanStop - _scanner.fScanStep);
        ui->SpinBoxCurrentScanend->setMaximum(_scanner.fScanStop);
        ui->SpinBoxCurrentScanPos->setSingleStep(_scanner.fScanStep);
        ui->SpinBoxCurrentScanstart->setSingleStep(_scanner.fScanStep);
        ui->SpinBoxCurrentScanend->setSingleStep(_scanner.fScanStep);
    }
    else
    {
        ui->SpinBoxCurrentScanPos->setMaximum(_scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart);
        ui->SpinBoxCurrentScanstart->setMaximum(_scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart - 1/_scanner.fPrf);
        ui->SpinBoxCurrentScanend->setMaximum(_scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart);
        ui->SpinBoxCurrentScanPos->setSingleStep(1/_scanner.fPrf);
        ui->SpinBoxCurrentScanstart->setSingleStep(1/_scanner.fPrf);
        ui->SpinBoxCurrentScanend->setSingleStep(1/_scanner.fPrf);
        _scanner.fScanend = _scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart;
    }
    ui->SpinBoxCurrentScanstart->setMinimum(_scanner.fScanStart);

//    ui->SpinBoxCurrentIndexend->setMinimum(fstart2 + 1);
//    if(_scanner.fLawQty > 0)
//    ui->SpinBoxCurrentIndexend->setMaximum(fstop2);
//    ui->SpinBoxCurrentIndexend->setSingleStep(fstep);
    ui->SliderCurrentScanPos->setMinimum(0);
    ui->SliderCurrentScanPos->setSingleStep(_scanner.fScanStep);
    ui->SliderCurrentScanPos->setMaximum( (_scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep );
    ui->SpinBoxCurrentIndexstart->setMaximum(fstop2 - fstep);
    ui->SpinBoxCurrentIndexstart->setMinimum(fstart2);
    ui->SpinBoxCurrentIndexstart->setSingleStep(fstep);
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
    ui->SpinBoxCurrentScanstart->setValue(_scanner.fScanStart2) ;
    ui->SpinBoxCurrentScanend->setValue(_scanner.fScanend) ;
    double fstart,fstop,fstart2,fstop2,fstep;
    _process->ChangeCscanIndexRange(&fstart,&fstop,&fstart2,&fstop2,&fstep);
    if(_scanner.eEncoderType == setup_ENCODER_TYPE_TIMER) {
        ui->LabelScanPosUnit->setText("sec");
        ui->LabelScanStartUnit_2->setText("sec");
        ui->LabelScanStopUnit->setText("sec");
        ui->LabelIndexStartUnit->setText("   ");
        ui->LabelIndexStopUnit->setText("   ");
    } else {
        ui->LabelScanPosUnit->setText("mm");
        ui->LabelScanStartUnit_2->setText("mm");
        ui->LabelScanStopUnit->setText("mm");
        ui->LabelIndexStartUnit->setText("  ");
        ui->LabelIndexStopUnit->setText("  ");
    }
    ui->SpinBoxCurrentIndexend->setMinimum(fstart2 + fstep);
    ui->SpinBoxCurrentIndexend->setMaximum(fstop2);
    ui->SpinBoxCurrentIndexend->setSingleStep(fstep);
    ui->SpinBoxCurrentIndexstart->setMaximum(fstop2 - fstep);
    ui->SpinBoxCurrentIndexstart->setMinimum(fstart2);
    ui->SpinBoxCurrentIndexstart->setSingleStep(fstep);
    ui->SpinBoxCurrentIndexstart->setValue(fstart);
    ui->SpinBoxCurrentIndexend->setValue(fstop) ;
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

void InstrumentSettingWidget::on_SpinBoxCurrentScanPos_valueChanged(double arg1)
{
	if(!ui->SpinBoxCurrentScanPos->hasFocus())  return ;
	 SCANNER& _scanner = m_pConfig->common.scanner ;

	 _scanner.fScanPos = arg1 ;
     if(_scanner.eEncoderType) {
        ui->SliderCurrentScanPos->setValue((arg1 - _scanner.fScanStart)/_scanner.fScanStep);
     }
     else
     {
         ui->SliderCurrentScanPos->setValue((arg1 - _scanner.fScanStart)*_scanner.fPrf);
     }

     ProcessDisplay _proDisplay ;
     for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
          _proDisplay.UpdateAllViewCursorOfGroup(i);
     }
	 g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::on_SliderCurrentScanPos_valueChanged(int value)
{
	if(!ui->SliderCurrentScanPos->hasFocus()) return ;
	SCANNER& _scanner = m_pConfig->common.scanner	;

	if(_scanner.eEncoderType) {
		_scanner.fScanPos = _scanner.fScanStep * value + _scanner.fScanStart ;
	} else {
		_scanner.fScanPos =  value / _scanner.fPrf  + _scanner.fScanStart ;
	}
	ui->SpinBoxCurrentScanPos->setValue(_scanner.fScanPos);

     ProcessDisplay _proDisplay ;
     for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
          _proDisplay.UpdateAllViewCursorOfGroup(i);
     }
     g_pMainWnd->UpdateSlider();
	g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::retranslateUi()
{
    ui->retranslateUi(this);
}


void InstrumentSettingWidget::on_SpinBoxCurrentScanend_valueChanged(double arg1)
{
    if(!ui->SpinBoxCurrentScanend->hasFocus())  return ;
    if(arg1 <= ui->SpinBoxCurrentScanstart->value())
        return;
    SCANNER& _scanner = m_pConfig->common.scanner ;
    if(_scanner.eEncoderType)
    {
        ui->SpinBoxCurrentScanstart->setMaximum(arg1-_scanner.fScanStep);
    }
    else
    {
        ui->SpinBoxCurrentScanstart->setMaximum(arg1-1/_scanner.fPrf);
    }

        _scanner.fScanend =  arg1 ;


    ProcessDisplay _proDisplay ;

    for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
         _proDisplay.UpdateAllViewCursorOfGroup(i);
    }
    g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::on_SpinBoxCurrentIndexend_valueChanged(double arg1)
{
    if(!ui->SpinBoxCurrentIndexend->hasFocus())  return ;
    ParameterProcess* _process = ParameterProcess::Instance();
    double fstart,fstop,fstart2,fstop2,fstep;
    _process->ChangeCscanIndexRange(&fstart,&fstop,&fstart2,&fstop2,&fstep);
    ui->SpinBoxCurrentIndexstart->setMaximum(arg1 - fstep);


    _process->ChangeCscanIndexstop(&arg1);

    ProcessDisplay _proDisplay ;

    for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
        _proDisplay.UpdateAllViewOfGroup(i);
         _proDisplay.UpdateAllViewCursorOfGroup(i);
    }
    g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::on_SpinBoxCurrentScanstart_valueChanged(double arg1)
{

    if(!ui->SpinBoxCurrentScanstart->hasFocus())  return ;

     SCANNER& _scanner = m_pConfig->common.scanner ;
     if(arg1 >= ui->SpinBoxCurrentScanend->value())
         return;
     if(_scanner.eEncoderType)
     {
         ui->SpinBoxCurrentScanend->setMinimum(arg1+_scanner.fScanStep);
     }
     else
     {
         ui->SpinBoxCurrentScanend->setMinimum(arg1+1/_scanner.fPrf);
     }
         _scanner.fScanStart2 =  arg1 ;


     ProcessDisplay _proDisplay ;
     for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
          _proDisplay.UpdateAllViewCursorOfGroup(i);
     }
     g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::on_SpinBoxCurrentIndexstart_valueChanged(double arg1)
{
    if(!ui->SpinBoxCurrentIndexstart->hasFocus())  return ;
     ParameterProcess* _process = ParameterProcess::Instance();
     double fstart,fstop,fstart2,fstop2,fstep;
     _process->ChangeCscanIndexRange(&fstart,&fstop,&fstart2,&fstop2,&fstep);
     ui->SpinBoxCurrentIndexend->setMinimum(arg1 + fstep);


     _process->ChangeCscanIndexstart(&arg1);

     ProcessDisplay _proDisplay ;
     for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
         _proDisplay.UpdateAllViewOfGroup(i);
          _proDisplay.UpdateAllViewCursorOfGroup(i);
     }
     g_pMainWnd->RunDrawThreadOnce(true);
}

void InstrumentSettingWidget::on_BtnReset_clicked()
{
    SCANNER& _scanner = m_pConfig->common.scanner ;


    ParameterProcess* _process = ParameterProcess::Instance();
    double fstart,fstop,fstart2,fstop2,fstep;
    _process->ChangeCscanIndexRange(&fstart,&fstop,&fstart2,&fstop2,&fstep);
    ui->SpinBoxCurrentIndexstart->setValue(fstart2);
    ui->SpinBoxCurrentIndexend->setValue(fstop2) ;
    if(_scanner.eEncoderType)
    {
        ui->SpinBoxCurrentScanstart->setValue(_scanner.fScanStart);
        ui->SpinBoxCurrentScanend->setValue(_scanner.fScanStop) ;
        _scanner.fScanStart2 = _scanner.fScanStart;
        _scanner.fScanend = _scanner.fScanStop;
        _scanner.fScanPos = _scanner.fScanStart2;
    }
    else
    {
        ui->SpinBoxCurrentScanstart->setValue(_scanner.fScanStart);
        ui->SpinBoxCurrentScanend->setValue(_scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart) ;
        _scanner.fScanStart2 = _scanner.fScanStart;
        _scanner.fScanend = _scanner.fScanStop/_scanner.fPrf + _scanner.fScanStart;
        _scanner.fScanPos = _scanner.fScanStart2;
    }
    ui->SpinBoxCurrentScanPos->setValue(_scanner.fScanPos);
    ui->SliderCurrentScanPos->setValue(0);
    _process->ChangeCscanIndexstart(&fstart2);
    _process->ChangeCscanIndexstop(&fstop2);
    InitCommonConfig();
    ProcessDisplay _proDisplay ;
    for(int i = 0; i < m_pConfig->common.nGroupQty; i ++) {
        _proDisplay.UpdateAllViewOfGroup(i);
         _proDisplay.UpdateAllViewCursorOfGroup(i);
    }
    g_pMainWnd->RunDrawThreadOnce(true);
}
