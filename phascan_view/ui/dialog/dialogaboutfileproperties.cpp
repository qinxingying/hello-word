#include "dialogaboutfileproperties.h"
#include "ui_dialogaboutfileproperties.h"
#include "config_phascan_ii/config.h"

DialogAboutFileProperties::DialogAboutFileProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutFileProperties)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("File Properties"));
    ui->labelFpgaPaVersion->setText(Config::instance()->getFpgaPaVersion());
    ui->labelFpgaCpuVersion->setText(Config::instance()->getFpgaCpuVersion());
    ui->labelPhascanVersion->setText(Config::instance()->getVersion());
    ui->labelSN->setText(Config::instance()->getDeviceSN());
}

DialogAboutFileProperties::~DialogAboutFileProperties()
{
    delete ui;
}
