#include "dialogweldfixdataii.h"
#include "ui_dialogweldfixdataii.h"

#include "ParameterProcess.h"
#include<QDebug>
DialogWeldFixDataII::DialogWeldFixDataII(QWidget *parent, int nGroupId) :
    QDialog(parent),
    ui(new Ui::DialogWeldFixDataII), m_nGroupId(nGroupId)
{
    ui->setupUi(this);
    SetDisplayMode(DISPLAY_WELD);
    ParameterProcess* _process = ParameterProcess::Instance();
    PART_CONFIG* _pPart = _process->GetPart(m_nGroupId);
    memcpy((void*)&m_cPart, (void*)_pPart, sizeof(PART_CONFIG));
    ui->showWidget->SerPart( &m_cPart);
    ui->showWidget->setGroupId(nGroupId);
    ui->showWidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    ui->showWidget->setPalette(palette);

    int weldType = (int)m_cPart.weld_ii.eType;
    ui->weldTypeComboBox->setCurrentIndex(weldType);
    int _buff = (int)m_cPart.weld_ii.eSymmetry;
    ui->symmetryComboBox->setCurrentIndex(_buff);
    _buff = (int)m_cPart.weld_ii.eProbePos;
    ui->ProbePosComboBox->setCurrentIndex(_buff);
    double HAZ = m_cPart.weld_ii.eHAZ;
    ui->HAZDoubleSpinBox->setValue(HAZ);
    weldTypeChanged(weldType);

    m_path = QCoreApplication::applicationDirPath() + "/init/part/dxf/";
    SetWndName();
    ListPartFiles();

    connect( ui->weldTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(weldTypeChanged(int)));
    connect( ui->symmetryComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(symmetryChanged(int)));
    connect( ui->ProbePosComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(probePosChanged(int)));
    connect( ui->weldFormComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(weldFormChanged(int)));
    connect( ui->HAZDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(HAZValueChanged(double)));
    connect( ui->w1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(w1ValueChanged(double)));
    connect( ui->w2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(w2ValueChanged(double)));
    connect( ui->w3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(w3ValueChanged(double)));
    connect( ui->h1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(h1ValueChanged(double)));
    connect( ui->h2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(h2ValueChanged(double)));
    connect( ui->r1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(r1ValueChanged(double)));
    connect( ui->r2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(r2ValueChanged(double)));
    connect( ui->partFileListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(PartFileListClicked(QModelIndex)));
    connect( ui->showWidget, SIGNAL(zoom(double)), this, SLOT(zoomValueChanged(double)));
    connect( ui->zoomDoubleSpinBox, SIGNAL(valueChanged(double)), ui->showWidget, SLOT(do_zoom_change(double)));
}

DialogWeldFixDataII::~DialogWeldFixDataII()
{
    delete ui;
}

PART_CONFIG* DialogWeldFixDataII::GetPart()
{
    return &m_cPart;
}

void DialogWeldFixDataII::SetDisplayMode(DISPLAY_MODE eMode_)
{
    m_eDisplay = eMode_;
    if(eMode_ == DISPLAY_WELD){
        ui->weldImageLabel->show();
        ui->weldParameterGroupBox->show();
        ui->partFileGroupBox->hide();
        ui->pathLabel->hide();
    }else{
        ui->weldImageLabel->hide();
        ui->weldParameterGroupBox->hide();
        ui->partFileGroupBox->show();
        ui->pathLabel->show();
    }
}

void DialogWeldFixDataII::SetWndName()
{
    int _bPartFile = strlen(m_cPart.strPartFile);
    if(!_bPartFile) {
        ui->partFileNameLabel->setText(QString(tr("Not Load")));
    }
    char buf[256];
    if(_bPartFile) {
        strcpy(buf, m_cPart.strPartFile);
        CharFilter(buf, (char*)"/");
        ui->partFileNameLabel->setText(QString(tr(buf)));
    }
    ui->partFileNameLabel->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgb(180, 180, 180);");
    ui->pathLabel->setText(m_path);
}

void DialogWeldFixDataII::ListPartFiles()
{
    QDir dir(m_path);
    if(!dir.exists()) {
        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0) {
        return;
    }
    QStringList strList;
    for(int i = 0; i<file_count; i++){
        QFileInfo file_info = list.at(i);
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("dxf"), Qt::CaseInsensitive) == 0){
            QString absolute_file_path = file_info.fileName();
            strList.append(absolute_file_path);
        }
    }
    QStandardItemModel *standardItemModel = new QStandardItemModel(this);
    int nCount = strList.size();
    for(int i = 0; i < nCount; i++){
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        standardItemModel->appendRow(item);
    }
    ui->partFileListView->setModel(standardItemModel);
    ui->partFileListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DialogWeldFixDataII::weldTypeChanged(int index)
{
    m_cPart.weld_ii.eType = (setup_WELD_TYPE_II)index;
    blockSignals(true);

    if(m_cPart.weld_ii.eType==ASYMMETRIC)
    {
    ui->symmetryLabel->setText(tr("alignment:"));
    ui->symmetryComboBox->setItemText(0,tr("top"));
    ui->symmetryComboBox->setItemText(1,tr("Center"));
    ui->symmetryComboBox->setItemText(2,tr("bottom"));
    }else{
        ui->symmetryLabel->setText(tr("Symmetry:"));
        ui->symmetryComboBox->setItemText(0,tr("Symmetry"));
        ui->symmetryComboBox->setItemText(1,tr("Right"));
        ui->symmetryComboBox->setItemText(2,tr("Left"));
        }

    switch (m_cPart.weld_ii.eType) {
    case NONE_TYPE:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/none.jpg"));
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->hide();
        ui->HAZDoubleSpinBox->hide();
        ui->HAZUnitLabel->hide();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->show();
        ui->HAZDoubleSpinBox->show();
        ui->HAZUnitLabel->show();
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
    case TKY:
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/tky.jpg"));
        ui->symmetryLabel->hide();
        ui->symmetryComboBox->hide();
        ui->probePosLabel->show();
        ui->ProbePosComboBox->show();
        ui->HAZLabel->hide();
        ui->HAZDoubleSpinBox->hide();
        ui->HAZUnitLabel->hide();
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
        ui->w3Label->hide();
        ui->w3DoubleSpinBox->hide();
        ui->w3UnitLabel->hide();
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.w1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.h1);
        ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.a1);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.w2);
        ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.h2);
        ui->r2DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.a2);
        break;   
    case ASYMMETRIC:
        if(m_cPart.weld_ii.align==0||m_cPart.weld_ii.align==1||m_cPart.weld_ii.align==2)
        {
//        char buf[100];
//        sprintf(buf,":/file/resource/weld/asymmetric_weld%d.png", m_cPart.weld_ii.align);
        QString str;
        str=QString(":/file/resource/weld/asymmetric_weld%1.png").arg(m_cPart.weld_ii.align+1);
        ui->weldImageLabel->setPixmap(QPixmap(str));
        ui->symmetryComboBox->setCurrentIndex(m_cPart.weld_ii.align);
        }
        else
        {
        ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/asymmetric_weld0.png"));
        }
        ui->symmetryLabel->show();
        ui->symmetryComboBox->show();
        ui->probePosLabel->hide();
        ui->ProbePosComboBox->hide();
        ui->HAZLabel->hide();
        ui->HAZDoubleSpinBox->hide();
        ui->HAZUnitLabel->hide();
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
        ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W1);
        ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.H1);
//        ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.A1);
        ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W2);
        ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.H2);
        ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W3);
//        ui->r2DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.A2);



        break;

    default:
        break;
    }
    blockSignals(false);
    if(m_cPart.weld_ii.eType == DXF){
        ui->symmetryComboBox->setEnabled(false);
        ui->ProbePosComboBox->setEnabled(false);
        ui->w1DoubleSpinBox->setEnabled(false);
        ui->h1DoubleSpinBox->setEnabled(false);
        ui->r1DoubleSpinBox->setEnabled(false);
        ui->w2DoubleSpinBox->setEnabled(false);
        ui->h2DoubleSpinBox->setEnabled(false);
        ui->r2DoubleSpinBox->setEnabled(false);
        ui->w3DoubleSpinBox->setEnabled(false);
    }else{
        ui->symmetryComboBox->setEnabled(true);
        ui->ProbePosComboBox->setEnabled(true);
        ui->w1DoubleSpinBox->setEnabled(true);
        ui->h1DoubleSpinBox->setEnabled(true);
        ui->r1DoubleSpinBox->setEnabled(true);
        ui->w2DoubleSpinBox->setEnabled(true);
        ui->h2DoubleSpinBox->setEnabled(true);
        ui->r2DoubleSpinBox->setEnabled(true);
        ui->w3DoubleSpinBox->setEnabled(true);
    }
    if(m_cPart.weld_ii.eType == TKY){
        ui->r1Label->setText(tr("A1"));
        ui->r2Label->setText(tr("A2"));
        ui->r1UnitLabel->setText(tr("deg"));
        ui->r2UnitLabel->setText(tr("deg"));
    }else{
        ui->r1Label->setText(tr("R1"));
        ui->r2Label->setText(tr("R2"));
        ui->r1UnitLabel->setText(tr("mm"));
        ui->r2UnitLabel->setText(tr("mm"));
    }
    ui->showWidget->clear_point();
    ui->showWidget->update();
}

void DialogWeldFixDataII::symmetryChanged( int index)
{    
    if(m_cPart.weld_ii.eType==ASYMMETRIC)
    {
        ui->showWidget->clear_point();
        m_cPart.weld_ii.align = static_cast<setup_PLANE_ALIGN_TYPE>(index);
        if(m_cPart.weld_ii.align==setup_PLANE_TOP)
            ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/asymmetric_weld1.png"));
        else if(m_cPart.weld_ii.align==setup_PLANE_CENTER)
            ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/asymmetric_weld2.png"));
        else
            ui->weldImageLabel->setPixmap(QPixmap(":/file/resource/weld/asymmetric_weld3.png"));

    }
    else
        m_cPart.weld_ii.eSymmetry = static_cast<setup_WELD_SYMMETRY_TYPE>(index);
    ui->showWidget->update();
}

void DialogWeldFixDataII::probePosChanged( int index)
{
    m_cPart.weld_ii.eProbePos = static_cast<KTY_ProbePosition>(index);
    ui->showWidget->update();
}

void DialogWeldFixDataII::weldFormChanged(int index)
{
    SetDisplayMode((DISPLAY_MODE)index);
}

void DialogWeldFixDataII::HAZValueChanged(double value)
{
    m_cPart.weld_ii.eHAZ = value;
}

void DialogWeldFixDataII::w1ValueChanged( double value)
{
    if(m_cPart.weld_ii.eType == U){
        if(m_cPart.weld_ii.U.r > value){
            ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.U.r);
            return;
        }
    }
    else if( m_cPart.weld_ii.eType == UU || m_cPart.weld_ii.eType == UV){
        if(m_cPart.weld_ii.UU.r1 > value){
            ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.UU.r1);
        }
    }else if(m_cPart.weld_ii.eType == ASYMMETRIC)
    {

        if(value >m_cPart.weld_ii.l1)
        {


            m_cPart.weld_ii.ASY.W1 = m_cPart.weld_ii.l1;;
            ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W1);
            ui->showWidget->update();
            return ;
        }else{


            m_cPart.weld_ii.ASY.W1 = value;
            ui->w1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W1);
            ui->showWidget->update();
            return ;

        }



    }
    m_cPart.weld_ii.I.w = value;
    ui->showWidget->update();
}

void DialogWeldFixDataII::w2ValueChanged( double value)
{
    if(m_cPart.weld_ii.eType == ASYMMETRIC)
            {
            m_cPart.weld_ii.ASY.W2 = value;
            ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W2);
            ui->showWidget->update();
            return ;
            }
    if(m_cPart.weld_ii.eType == TKY){
        m_cPart.weld_ii.TKY.w2 = value;
    }else{
        if(m_cPart.weld_ii.V.w1 < value){
            ui->w2DoubleSpinBox->setValue(m_cPart.weld_ii.V.w1);
            return;
        }
        m_cPart.weld_ii.V.w2 = value;
    }
    ui->showWidget->update();

}

void DialogWeldFixDataII::w3ValueChanged( double value)
{
    switch (m_cPart.weld_ii.eType) {
    case VY:
        if( value > m_cPart.weld_ii.VY.w2){
            ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.VY.w3);
            return;
        }        
    case VV:
    case UU:
    case UV:
        if( value < m_cPart.weld_ii.VV.w2)
        {
            ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.VV.w3);
            return;
        }
        break;

    case ASYMMETRIC:
        m_cPart.weld_ii.ASY.W3 = value;
        ui->w3DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.W3);
        ui->showWidget->update();
        return;
        break;
    default:
        break;
    }
    m_cPart.weld_ii.VY.w3 = value;
    ui->showWidget->update();
}

void DialogWeldFixDataII::h1ValueChanged( double value)
{

    switch (m_cPart.weld_ii.eType){
    case V:
        if( m_cPart.afSize[0] < value)
        {
            ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.V.h);
            return;
        }
        break;
    case U:
        if( m_cPart.afSize[0] < value || m_cPart.weld_ii.U.r*2 > value)
        {
            ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.U.h);
            return;
        }
        break;
    case VY:
    case VV:
        if( value + m_cPart.weld_ii.VY.h2 > m_cPart.afSize[0])
        {
            ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.VV.h1);
            return;
        }
        break;
    case UU:
    case UV:
        if( value + m_cPart.weld_ii.VY.h2 > m_cPart.afSize[0] || m_cPart.weld_ii.UV.r > value){
            ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.UV.h1);
        }
        break;
    case ASYMMETRIC:
        if(value < m_cPart.weld_ii.ASY.m_thickness-m_cPart.weld_ii.h2)
        {
//            if(value>=m_cPart.weld_ii.h1)
//            {
//             ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.h1);

//            }

            m_cPart.weld_ii.ASY.H1 = value;
            ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.H1);
            ui->showWidget->update();
            return;
        }else{

            ui->h1DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.m_thickness-m_cPart.weld_ii.h2);
            m_cPart.weld_ii.ASY.H1 = m_cPart.weld_ii.ASY.m_thickness-m_cPart.weld_ii.h2;
            ui->showWidget->update();
            return;
        }
        break;
    default:
        break;
    }
    m_cPart.weld_ii.V.h = value;
    ui->showWidget->update();
}

void DialogWeldFixDataII::h2ValueChanged( double value)
{
    switch (m_cPart.weld_ii.eType) {
    case VY:
    case VV:
        if(value + m_cPart.weld_ii.VY.h1 > m_cPart.afSize[0])
        {
            ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.VY.h2);
            return;
        }
        break;
    case UU:
        if(value + m_cPart.weld_ii.VY.h1 > m_cPart.afSize[0] || m_cPart.weld_ii.UU.r2 > value)
        {
            ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.UU.h2);
            return;
        }
        break;
    case UV:
        if( value + m_cPart.weld_ii.UV.h1 > m_cPart.afSize[0]){
            ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.UV.h2);
        }
        break;
    case ASYMMETRIC:
            m_cPart.weld_ii.ASY.H2 = value;
            ui->h2DoubleSpinBox->setValue(m_cPart.weld_ii.ASY.H2);
            ui->showWidget->update();
            return;
    default:
        break;
    }
    m_cPart.weld_ii.VY.h2 = value;
    ui->showWidget->update();
}

void DialogWeldFixDataII::r1ValueChanged( double value)
{
    switch (m_cPart.weld_ii.eType) {
    case U:
        if(value > m_cPart.weld_ii.U.w1){
            ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.U.r);
            return;
        }
        m_cPart.weld_ii.U.r = value;
        break;
    case UU:
    case UV:
        if(value > m_cPart.weld_ii.UV.w1){
            ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.UV.r);
            return;
        }
        m_cPart.weld_ii.UV.r = value;
        break;
    case TKY:
        if(value > 89){
            ui->r1DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.a1);
            return;
        }
        m_cPart.weld_ii.TKY.a1 = value;
        break;
    default:
        break;
    }
    ui->showWidget->update();
}

void DialogWeldFixDataII::r2ValueChanged( double value)
{
    switch (m_cPart.weld_ii.eType) {
    case UU:
        if(value >m_cPart.weld_ii.UU.w3){
            ui->r2DoubleSpinBox->setValue(m_cPart.weld_ii.UU.r2);
            return;
        }
        m_cPart.weld_ii.UU.r2 = value;
        break;
    case TKY:
        if(value > 89){
            ui->r2DoubleSpinBox->setValue(m_cPart.weld_ii.TKY.a2);
            return;
        }
        m_cPart.weld_ii.TKY.a2 = value;
        break;
    default:
        break;
    }
    ui->showWidget->update();
}

void DialogWeldFixDataII::PartFileListClicked(QModelIndex index)
{
     std::string _str = index.data().toString().toStdString();
     m_cPart.weld_ii.eType = DXF;
     m_cPart.CADFresh = false;
     std::string str = m_path.toStdString();
     const char* p = str.c_str();
     sprintf(m_cPart.strPartFile, "%s%s", p, (char*)(_str.c_str()));
     SetWndName();
     ui->weldTypeComboBox->setCurrentIndex(DXF);
     weldTypeChanged(DXF);
}

void DialogWeldFixDataII::zoomValueChanged(double value)
{
    ui->zoomDoubleSpinBox->setValue(value);
}

void DialogWeldFixDataII::on_nccDefaultPathBt_clicked()
{
    m_path = QCoreApplication::applicationDirPath() + "/init/part/dxf/";
    SetWndName();
    ListPartFiles();
}

void DialogWeldFixDataII::on_nccPathBt_clicked()
{
    //DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QString _strPath = QFileDialog::getExistingDirectory(this,
                                                         QString(tr("Open Dxf File")),
                                                         m_path);
    if(QFileInfo(_strPath).isRoot()) {
        m_path = _strPath;
    } else {
        m_path = _strPath + "/";
    }
    SetWndName();
    ListPartFiles();
}
