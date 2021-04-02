#include "dialogdefectmethodselect.h"
#include "ui_dialogdefectmethodselect.h"

DialogDefectMethodSelect::DialogDefectMethodSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDefectMethodSelect)
{
    ui->setupUi(this);
    if (m_lengthMeasureMethod == 0) {
        ui->halfWaveRadioL->setChecked(true);
    }
    if (m_heightMeasureMethod == 0) {
        ui->halfWaveRadioH->setChecked(true);
    }
}

DialogDefectMethodSelect::~DialogDefectMethodSelect()
{
    delete ui;
}

void DialogDefectMethodSelect::on_halfWaveRadioL_clicked()
{
    m_lengthMeasureMethod = 0;
}

void DialogDefectMethodSelect::on_endHalfWaveRadioL_clicked()
{
    m_lengthMeasureMethod = 1;
}

void DialogDefectMethodSelect::on_sensitivityRadioL_clicked()
{
    m_lengthMeasureMethod = 2;
}

void DialogDefectMethodSelect::on_halfWaveRadioH_clicked()
{
    m_heightMeasureMethod = 0;
}

void DialogDefectMethodSelect::on_endHalfWaveRadioH_clicked()
{
    m_heightMeasureMethod = 1;
}

void DialogDefectMethodSelect::on_sensitivityRadioH_clicked()
{
    m_heightMeasureMethod = 2;
}

void DialogDefectMethodSelect::on_pushButton_clicked()
{
    accept();
}
