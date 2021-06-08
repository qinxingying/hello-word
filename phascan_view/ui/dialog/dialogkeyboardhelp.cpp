﻿#include "dialogkeyboardhelp.h"
#include "ui_dialogkeyboardhelp.h"

DialogKeyboardHelp::DialogKeyboardHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogKeyboardHelp)
{
    ui->setupUi(this);
    ui->labelLogo->setPixmap(QPixmap(":/file/resource/report_logo/logo.png"));
    ui->labelKeyboard->setPixmap(QPixmap(":/file/resource/Main/M.jpg"));
    ui->labelWimage->setPixmap(QPixmap(":/file/resource/Main/w.png"));
    ui->labelWtext->setText(tr("Height start"));
    ui->labelSimage->setPixmap(QPixmap(":/file/resource/Main/s.png"));
    ui->labelStext->setText(tr("Height stop"));
    ui->labelAimage->setPixmap(QPixmap(":/file/resource/Main/a.png"));
    ui->labelAtext->setText(tr("Position start"));
    ui->labelDimage->setPixmap(QPixmap(":/file/resource/Main/d.png"));
    ui->labelDtext->setText(tr("Position stop"));
    ui->labelZimage->setPixmap(QPixmap(":/file/resource/Main/z.png"));
    ui->labelZtext->setText(tr("Save maximum amplitude position"));
    ui->labelCimage->setPixmap(QPixmap(":/file/resource/Main/c.png"));
    ui->labelCtext->setText(tr("Call maximum amplitude position"));
    ui->label0image->setPixmap(QPixmap(":/file/resource/Main/0.png"));
    ui->label0text->setText(tr("On(Off) C/B scan showall"));
    ui->labelUpimage->setPixmap(QPixmap(":/file/resource/Main/up.png"));
    ui->labelUptext->setText(tr("Up(down) ajust law angle cursor"));
    ui->labelLeftimage->setPixmap(QPixmap(":/file/resource/Main/left.png"));
    ui->labelLefttext->setText(tr("left(right) ajust scanpos cursor"));
    ui->labelShift->setPixmap(QPixmap(":/file/resource/Main/shift.png"));
    ui->labelShiftimage->setPixmap(QPixmap(":/file/resource/Main/left.png"));
    ui->labelShifttext->setText(tr("left(right) fast ajust scanpos cursor"));

    ui->labelWimage->hide();
    ui->labelWtext->hide();
    ui->labelSimage->hide();
    ui->labelStext->hide();
    ui->labelAimage->hide();
    ui->labelAtext->hide();
    ui->labelDimage->hide();
    ui->labelDtext->hide();
    ui->labelZimage->hide();
    ui->labelZtext->hide();
    ui->labelCimage->hide();
    ui->labelCtext->hide();
    ui->label0image->hide();
    ui->label0text->hide();
    ui->labelUpimage->hide();
    ui->labelUptext->hide();
    ui->labelLeftimage->hide();
    ui->labelLefttext->hide();
    ui->labelShift->hide();
    ui->labelShiftimage->hide();
    ui->labelShifttext->hide();
    ui->label_2->hide();

    ui->labelLogo_analysis->setPixmap(QPixmap(":/file/resource/report_logo/logo.png"));
    ui->labelKeyboard_analysis->setPixmap(QPixmap(":/file/resource/Main/A.jpg"));
}

DialogKeyboardHelp::~DialogKeyboardHelp()
{
    delete ui;
}

void DialogKeyboardHelp::setLanguage(setup_LANG lang)
{
    if (lang == setup_LANG_CHINESE) {

    } else {

    }
}
