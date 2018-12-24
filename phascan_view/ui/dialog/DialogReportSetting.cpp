#include "DialogReportSetting.h"
#include "ui_DialogReportSetting.h"

#include <QFileDialog>

DialogReportSetting::DialogReportSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReportSetting)
{
    ui->setupUi(this);
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
    QString t1 = ui->StrReportName->text();
    std::string t2 = t1.toStdString();
    const char * t3 = t2.c_str();
    strcpy(m_cInfo.strPartName, ui->StrPartName->text().toLocal8Bit().data()) ;
    strcpy(m_cInfo.strPartNo  , ui->StrPartNo->text().toLocal8Bit().data()) ;
    strcpy(m_cInfo.strPartPos , ui->StrPartPostion->text().toLocal8Bit().data()) ;
    strcpy(m_cInfo.strReportName, t3) ;
    strcpy(m_cInfo.logoName, ui->logoLineEdit->text().toUtf8().data());
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

    ui->StrPartName->setText(QString::fromLocal8Bit(m_cInfo.strPartName));
    ui->StrPartNo->setText(QString::fromLocal8Bit(m_cInfo.strPartNo));
    ui->StrPartPostion->setText(QString::fromLocal8Bit(m_cInfo.strPartPos));
    ui->StrReportName->setText(QString(m_cInfo.strReportName));
    ui->logoLineEdit->setText(m_cInfo.logoName);
    ui->ComModeSelection->setCurrentIndex(m_cInfo.eMode ? 1 : 0);
}

void DialogReportSetting::on_logoToolButton_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Logo Image"),
                                                "~", tr("Image Files (*.png *.jpg *.bmp)"));
    ui->logoLineEdit->setText(name);
}
