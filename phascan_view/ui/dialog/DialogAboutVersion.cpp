#include "DialogAbouVersion.h"
#include "ui_DialogAboutVersion.h"
#include "version.h"

DialogAboutVersion::DialogAboutVersion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutVersion)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("About"));
    ui->label_Version->setText(VERSION);
}

DialogAboutVersion::~DialogAboutVersion()
{
    delete ui;
}
