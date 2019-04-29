#include "dialogweldfixdataii.h"
#include "ui_dialogweldfixdataii.h"

#include "ParameterProcess.h"

DialogWeldFixDataII::DialogWeldFixDataII(QWidget *parent, int nGroupId) :
    QDialog(parent),
    ui(new Ui::DialogWeldFixDataII), m_nGroupId(nGroupId)
{
    ui->setupUi(this);
    ParameterProcess* _process = ParameterProcess::Instance();
    PART_CONFIG* _pPart = _process->GetPart(m_nGroupId);
    memcpy((void*)&m_cPart, (void*)_pPart, sizeof(PART_CONFIG));
    ui->showWidget->SerPart( &m_cPart);

    int weldType = (int)m_cPart.weld_ii.eType;
    ui->weldTypeComboBox->setCurrentIndex(weldType);
    weldTypeChanged(weldType);

    connect( ui->weldTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(weldTypeChanged(int)));

}

DialogWeldFixDataII::~DialogWeldFixDataII()
{
    delete ui;
}


void DialogWeldFixDataII::weldTypeChanged(int index)
{
    m_cPart.weld_ii.eType = (setup_WELD_TYPE_II)index;
    blockSignals(true);
    switch (m_cPart.weld_ii.eType) {
    case NONE_TYPE:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/none.jpg"));
        ui->w1Label->hide();
        ui->w1DoubleSpinBox->hide();
        ui->w1UnitLabel->hide();
        ui->h1Label->hide();
        ui->h1DoubleSpinBox->hide();
        ui->h1UnitLabel->hide();
        ui->r1Label->hide();
        ui->r1DoubleSpinBox->hide();
        ui->r1UnitLabel->hide();
        ui->w2Label->hide();
        ui->w2DoubleSpinBox->hide();
        ui->w2UnitLabel->hide();
        ui->h2Label->hide();
        ui->h2DoubleSpinBox->hide();
        ui->h2UnitLabel->hide();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->hide();
        ui->w3DoubleSpinBox->hide();
        ui->w3UnitLabel->hide();
        break;
    case I:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/i.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->hide();
        ui->h1DoubleSpinBox->hide();
        ui->h1UnitLabel->hide();
        ui->r1Label->hide();
        ui->r1DoubleSpinBox->hide();
        ui->r1UnitLabel->hide();
        ui->w2Label->hide();
        ui->w2DoubleSpinBox->hide();
        ui->w2UnitLabel->hide();
        ui->h2Label->hide();
        ui->h2DoubleSpinBox->hide();
        ui->h2UnitLabel->hide();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->hide();
        ui->w3DoubleSpinBox->hide();
        ui->w3UnitLabel->hide();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.I.w);
        break;
    case V:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/v.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->show();
        ui->h1DoubleSpinBox->show();
        ui->h1UnitLabel->show();
        ui->r1Label->hide();
        ui->r1DoubleSpinBox->hide();
        ui->r1UnitLabel->hide();
        ui->w2Label->show();
        ui->w2DoubleSpinBox->show();
        ui->w2UnitLabel->show();
        ui->h2Label->hide();
        ui->h2DoubleSpinBox->hide();
        ui->h2UnitLabel->hide();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->hide();
        ui->w3DoubleSpinBox->hide();
        ui->w3UnitLabel->hide();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.V.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.V.h);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.V.w2);
        break;
    case U:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/u.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->show();
        ui->h1DoubleSpinBox->show();
        ui->h1UnitLabel->show();
        ui->r1Label->show();
        ui->r1DoubleSpinBox->show();
        ui->r1UnitLabel->show();
        ui->w2Label->show();
        ui->w2DoubleSpinBox->show();
        ui->w2UnitLabel->show();
        ui->h2Label->hide();
        ui->h2DoubleSpinBox->hide();
        ui->h2UnitLabel->hide();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->hide();
        ui->w3DoubleSpinBox->hide();
        ui->w3UnitLabel->hide();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.U.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.U.h);
        ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.U.r);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.U.w2);
        break;
    case VY:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/vy.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->show();
        ui->h1DoubleSpinBox->show();
        ui->h1UnitLabel->show();
        ui->r1Label->hide();
        ui->r1DoubleSpinBox->hide();
        ui->r1UnitLabel->hide();
        ui->w2Label->show();
        ui->w2DoubleSpinBox->show();
        ui->w2UnitLabel->show();
        ui->h2Label->show();
        ui->h2DoubleSpinBox->show();
        ui->h2UnitLabel->show();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->show();
        ui->w3DoubleSpinBox->show();
        ui->w3UnitLabel->show();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.VY.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.VY.h1);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.VY.w2);
        ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.VY.h2);
        ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.VY.w3);
        break;
    case VV:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/vv.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->show();
        ui->h1DoubleSpinBox->show();
        ui->h1UnitLabel->show();
        ui->r1Label->hide();
        ui->r1DoubleSpinBox->hide();
        ui->r1UnitLabel->hide();
        ui->w2Label->show();
        ui->w2DoubleSpinBox->show();
        ui->w2UnitLabel->show();
        ui->h2Label->show();
        ui->h2DoubleSpinBox->show();
        ui->h2UnitLabel->show();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->show();
        ui->w3DoubleSpinBox->show();
        ui->w3UnitLabel->show();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.VV.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.VV.h1);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.VV.w2);
        ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.VV.h2);
        ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.VV.w3);
        break;
    case UU:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/uu.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->show();
        ui->h1DoubleSpinBox->show();
        ui->h1UnitLabel->show();
        ui->r1Label->show();
        ui->r1DoubleSpinBox->show();
        ui->r1UnitLabel->show();
        ui->w2Label->show();
        ui->w2DoubleSpinBox->show();
        ui->w2UnitLabel->show();
        ui->h2Label->show();
        ui->h2DoubleSpinBox->show();
        ui->h2UnitLabel->show();
        ui->r2Label->show();
        ui->r2DoubleSpinBox->show();
        ui->r2UnitLabel->show();
        ui->w3Label->show();
        ui->w3DoubleSpinBox->show();
        ui->w3UnitLabel->show();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.UU.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.UU.h1);
        ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.UU.r1);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.UU.w2);
        ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.UU.h2);
        ui->r2DoubleSpinBox->setValue(m_cPart.weld_ii.UU.r2);
        ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.UU.w3);
        break;
    case UV:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/uv.jpg"));
        ui->w1Label->show();
        ui->w1DoubleSpinBox->show();
        ui->w1UnitLabel->show();
        ui->h1Label->show();
        ui->h1DoubleSpinBox->show();
        ui->h1UnitLabel->show();
        ui->r1Label->show();
        ui->r1DoubleSpinBox->show();
        ui->r1UnitLabel->show();
        ui->w2Label->show();
        ui->w2DoubleSpinBox->show();
        ui->w2UnitLabel->show();
        ui->h2Label->show();
        ui->h2DoubleSpinBox->show();
        ui->h2UnitLabel->show();
        ui->r2Label->hide();
        ui->r2DoubleSpinBox->hide();
        ui->r2UnitLabel->hide();
        ui->w3Label->show();
        ui->w3DoubleSpinBox->show();
        ui->w3UnitLabel->show();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.UV.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.UV.h1);
        ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.UV.r);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.UV.w2);
        ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.UV.h2);
        ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.UV.w3);
        break;
    default:
        break;
    }
    blockSignals(false);
    ui->showWidget->update();
}
