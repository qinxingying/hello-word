#include "dialogaboutfileproperties.h"
#include "ui_dialogaboutfileproperties.h"
#include "config_phascan_ii/config.h"
#include "DopplerConfigure.h"

DialogAboutFileProperties::DialogAboutFileProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutFileProperties)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("File Properties"));
    DopplerConfigure *pConfig = DopplerConfigure::Instance();
    ui->labelFpgaPaVersion->setText(Config::instance()->getFpgaPaVersion());
    ui->labelFpgaCpuVersion->setText(Config::instance()->getFpgaCpuVersion());
    ui->labelPhascanVersion->setText(Config::instance()->getVersion());
    ui->labelSN->setText(Config::instance()->getDeviceSN());
    ui->labelDateTime->setText(pConfig->GetDataFileDateTime().toString("yyyy-MM-dd HH:mm:ss"));
}

DialogAboutFileProperties::~DialogAboutFileProperties()
{
    delete ui;
}
