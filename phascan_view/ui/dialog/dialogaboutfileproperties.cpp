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
    ui->labelFpgaPaVersion->setText(pConfig->fileInfo.fpgaPaVersion);
    ui->labelFpgaCpuVersion->setText(pConfig->fileInfo.fpgaCpuVersion);
    ui->labelPhascanVersion->setText(pConfig->fileInfo.deviceVersion);
    ui->labelSN->setText(pConfig->fileInfo.deviceSN);
    ui->labelDateTime->setText(pConfig->fileInfo.date);

    if (pConfig->fileInfo.fpgaPaVersion.isEmpty()) {
        ui->labelFpgaCpuVersion->hide();
        ui->label_3->hide();
        ui->label->setText(tr("FPGA"));
    }
}

DialogAboutFileProperties::~DialogAboutFileProperties()
{
    delete ui;
}
