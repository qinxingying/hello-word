#include "dialogdefectmethodselect.h"
#include "ui_dialogdefectmethodselect.h"

DialogDefectMethodSelect::DialogDefectMethodSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDefectMethodSelect)
{
    ui->setupUi(this);
    ui->endHalfWaveRadioH->hide();
    init_ui();

    ui->scaleDoubleSpinBox->setValue(m_scale);

    ui->autoH->hide();
    ui->autoL->hide();
}

DialogDefectMethodSelect::~DialogDefectMethodSelect()
{
    delete ui;
}

void DialogDefectMethodSelect::retranslateUi()
{
    ui->retranslateUi(this);
}

void DialogDefectMethodSelect::init_ui()
{
    if (m_lengthMeasureMethod == 0) {
        ui->halfWaveRadioL->setChecked(true);
    } else if (m_lengthMeasureMethod == 1){
        ui->endHalfWaveRadioL->setChecked(true);
    } else {
        ui->sensitivityRadioL->setChecked(true);
    }

    if (m_heightMeasureMethod == 0) {
        ui->halfWaveRadioH->setChecked(true);
    } else if (m_heightMeasureMethod == 1){
        ui->endHalfWaveRadioH->setChecked(true);
    } else if (m_heightMeasureMethod == 2){
        ui->sensitivityRadioH->setChecked(true);
    } else {
        ui->tipDiffractionH->setCheckable(true);
    }
}

void DialogDefectMethodSelect::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_QuoteLeft:
        on_pushButton_clicked();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        accept();
        break;
    default:
        break;
    }
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

void DialogDefectMethodSelect::on_scaleDoubleSpinBox_valueChanged(double arg1)
{
    m_scale = arg1;
}

void DialogDefectMethodSelect::on_tipDiffractionH_clicked()
{
    m_heightMeasureMethod = 3;
}

void DialogDefectMethodSelect::on_autoMerge_clicked()
{
    m_autoMerge = ui->autoMerge->isChecked();
}

void DialogDefectMethodSelect::on_autoIdentify_clicked()
{
    m_autoIdentify =  ui->autoIdentify->isChecked();
    if (m_autoIdentify) {
        ui->autoL->setChecked(true);
        ui->autoH->setChecked(true);

        ui->halfWaveRadioL->setEnabled(false);
        ui->endHalfWaveRadioL->setEnabled(false);
        ui->sensitivityRadioL->setEnabled(false);

        ui->halfWaveRadioH->setEnabled(false);
        ui->endHalfWaveRadioH->setEnabled(false);
        ui->sensitivityRadioH->setEnabled(false);
        ui->tipDiffractionH->setEnabled(false);

    } else {
        ui->halfWaveRadioL->setEnabled(true);
        ui->endHalfWaveRadioL->setEnabled(true);
        ui->sensitivityRadioL->setEnabled(true);

        ui->halfWaveRadioH->setEnabled(true);
        ui->endHalfWaveRadioH->setEnabled(true);
        ui->sensitivityRadioH->setEnabled(true);
        ui->tipDiffractionH->setEnabled(true);

        init_ui();
    }
}
