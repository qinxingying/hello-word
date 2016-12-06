#include "DialogReportSetting.h"
#include "ui_DialogReportSetting.h"


DialogReportSetting::DialogReportSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReportSetting)
{
    ui->setupUi(this);

    //********************************************************
    // whuan language 2015-05-15
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance() ;
    SetWndName(m_pConfig->AppEvn.eLanguage);
	//********************************************************
}

DialogReportSetting::~DialogReportSetting()
{
    delete ui;
}

void DialogReportSetting::on_pushButton_clicked()
{
    QDate _date = ui->dateEdit->date();
    m_cInfo.nYear  = _date.year()  ;
    m_cInfo.nMonth = _date.month() ;
    m_cInfo.nDate  = _date.day()   ;

    strcpy(m_cInfo.strPartName, ui->StrPartName->text().toLocal8Bit().data()) ;
    strcpy(m_cInfo.strPartNo  , ui->StrPartNo->text().toLocal8Bit().data()) ;
    strcpy(m_cInfo.strPartPos , ui->StrPartPostion->text().toLocal8Bit().data()) ;
    strcpy(m_cInfo.strReportName, ui->StrReportName->text().toLocal8Bit().data()) ;
    m_cInfo.eMode = ui->ComModeSelection->currentIndex() ;
    accept ();
}


void DialogReportSetting::SetReportInfo(ReportInfo* pInfo_)
{
    if(pInfo_)
        memcpy((void*)&m_cInfo , (void*)pInfo_ , sizeof(ReportInfo)) ;

    UpdateItems() ;
}

ReportInfo* DialogReportSetting::GetRePortInfo()
{
    return &m_cInfo ;
}


void DialogReportSetting::UpdateItems()
{
    QDate _date ;
    _date.setDate(m_cInfo.nYear , m_cInfo.nMonth , m_cInfo.nDate ) ;
    ui->dateEdit->setDate(_date);

    ui->StrPartName->setText(QString(m_cInfo.strPartName));
    ui->StrPartNo->setText(QString(m_cInfo.strPartNo));
    ui->StrPartPostion->setText(QString(m_cInfo.strPartPos));
    ui->StrReportName->setText(QString(m_cInfo.strReportName));
    ui->ComModeSelection->setCurrentIndex(m_cInfo.eMode ? 1 : 0);
}

void DialogReportSetting::SetWndName(setup_LANG eLang)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	switch(eLang)
	{
	case setup_LANG_ENGLISH:
		setWindowTitle(QString(tr("Report Setting"))) ;

		ui->label_5->setText(QString(tr("Part Name:")));
		ui->label->setText(QString(tr("Part N0.:")));
		ui->label_2->setText(QString(tr("Part Position")));
		ui->label_6->setText(QString(tr("Report Name:")));
		ui->label_4->setText(QString(tr("Date & Time:")));

		ui->pushButton->setText(QString(tr("Ok")));
		break;
	case setup_LANG_CHINESS:
		setWindowTitle(QString(tr("报表设置"))) ;

		ui->label_5->setText(QString(tr("部件名称:")));
		ui->label->setText(QString(tr("部件序号:")));
		ui->label_2->setText(QString(tr("部件位置")));
		ui->label_6->setText(QString(tr("报表名称:")));
		ui->label_4->setText(QString(tr("日期 & 时间:")));

		ui->pushButton->setText(QString(tr("确认")));
		break;
	case setup_LANG_JAPEN:
		break;
	case setup_LANG_KOREA:
		break;
	}

	int iLang = eLang;
	ui->ComModeSelection->clear();
	for(int i = 0; i < 2; i++) {
		ui->ComModeSelection->addItem(g_strReportSetGroupParamMode[i][iLang]);
	}
	ui->ComModeSelection->setCurrentIndex(m_cInfo.eMode ? 1 : 0);
}
