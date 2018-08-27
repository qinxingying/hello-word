#include "DialogAbouVersion.h"
#include "ui_DialogAboutVersion.h"

DialogAboutVersion::DialogAboutVersion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutVersion)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("About"));
    ui->label_Version->setText("1.1.6");
    ui->label_InstructmenVersion->setText("3.5.9-200");
}

DialogAboutVersion::~DialogAboutVersion()
{
    delete ui;
}
