#include "DialogDxfFileLoad.h"
#include "ui_DialogDxfFileLoad.h"
#include "ParameterProcess.h"
#include "DopplerConfigure.h"
#include "painter/DrawDxf.h"

#include <QFileDialog>
#include <QDir.h>
#include <QStandardItem>
#include <QDebug>

DialogDxfFileLoad::DialogDxfFileLoad(QWidget *parent , int nGroupId_) :
	QDialog(parent),
    ui(new Ui::DialogDxfFileLoad)
{
	ui->setupUi(this);
    SetDisplayMode(DISPLAY_WELD);
    m_nGroupId = nGroupId_;
	m_nWeldPartSel = 0;

	SetPart();
    UpdateWeld();
    ui->ExpoView->SerPart(&m_cPart);

	ui->ExpoView->setAutoFillBackground(true);
	QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    ui->ExpoView->setPalette(palette);

    m_path = QCoreApplication::applicationDirPath() + "/init/part/dxf/";
    SetWndName();
	UpdateDisplay();

	ListPartFiles();
    connect(ui->ListPartFile, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_PartFileListDbClicked(QModelIndex)));
    connect(ui->BtnNccPath, SIGNAL(clicked()), this, SLOT(on_BtnNccPathClicked()));
    connect(ui->BtnNccDefaultPath, SIGNAL(clicked()), this, SLOT(on_BtnNccDefaultPathClicked()));

    connect(ui->ExpoView, SIGNAL(zoom(double)), this, SLOT(slot_doubleSpinBox_zoom_setValue(double)));
    connect(ui->doubleSpinBox_zoom, SIGNAL(valueChanged(double)), ui->ExpoView, SLOT(do_zoom_change(double)));
}

DialogDxfFileLoad::~DialogDxfFileLoad()
{
	delete ui;
}

void DialogDxfFileLoad::SetWndName()
{
	int _bPartFile = strlen(m_cPart.strPartFile);

    if(!_bPartFile) {
        ui->LabelPartFileName->setText(QString(tr("Not Load")));
    }

    char buf[256];
    if(_bPartFile) {
		strcpy(buf, m_cPart.strPartFile);
        CharFilter(buf, (char*)"/");
        ui->LabelPartFileName->setText(QString(tr(buf)));
	}

	ui->LabelPartFileName->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgb(180, 180, 180);");
    ui->ComWeldType->setCurrentIndex(m_cPart.weld.eType);

    ui->LabelPartFilePath->setText(m_path);
}

void DialogDxfFileLoad::SetDisplayMode(DISPLAY_MODE eMode_)
{
    m_eDisplay = eMode_;
	if(eMode_ == DISPLAY_WELD)
	{
		ui->WeldGroupShow->show();
		ui->PartGroupShow->hide();
		ui->LabelPartFilePath->hide();
    }else{
		ui->PartGroupShow->show();
		ui->WeldGroupShow->hide();
		ui->LabelPartFilePath->show();
	}
}

void DialogDxfFileLoad::ListPartFiles()
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
    for(int i = 0; i<file_count; i++)
	{
		QFileInfo file_info = list.at(i);
		QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("dxf"), Qt::CaseInsensitive) == 0)
        {
			QString absolute_file_path = file_info.fileName();
			strList.append(absolute_file_path);
		}
	}

	QStandardItemModel *standardItemModel = new QStandardItemModel(this);
	int nCount = strList.size();
	for(int i = 0; i < nCount; i++)
	{
		QString string = static_cast<QString>(strList.at(i));
		QStandardItem *item = new QStandardItem(string);
		standardItemModel->appendRow(item);
	}
	ui->ListPartFile->setModel(standardItemModel);
	ui->ListPartFile->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DialogDxfFileLoad::SetPart()
{
    ParameterProcess* _process = ParameterProcess::Instance();
    PART_CONFIG* _pPart = _process->GetPart(m_nGroupId);
    memcpy((void*)&m_cPart, (void*)_pPart, sizeof(PART_CONFIG));
}

PART_CONFIG* DialogDxfFileLoad::GetPart()
{
    return &m_cPart;
}

void DialogDxfFileLoad::UpdateWeld()
{
	ui->ComWeldType->setCurrentIndex(m_cPart.weld.eType);
	ui->ComWeldSymetry->setCurrentIndex(m_cPart.weld.eSymmetry);
	ui->SpinWHeight->setValue(m_cPart.weld.weland_height);
	ui->SpinWoffset->setValue(m_cPart.weld.weland_offset);
	ui->SpinFHeight->setValue(m_cPart.weld.fizone_height);
	ui->SpinFRadius->setValue(m_cPart.weld.fizone_radius);
	ui->SpinFAngle->setValue(m_cPart.weld.fizone_angle);
    ui->SpinFHeight_2->setValue(m_cPart.weld.fizone_down_height);
    ui->SpinFAngle_2->setValue(m_cPart.weld.fizone_down_angle);
    if(m_cPart.weld.eType == setup_WELD_TKY)
    {
        ui->SpinWHeight->setValue(m_cPart.weld.weland_height);
        ui->SpinWoffset->setValue(m_cPart.weld.fizone_height);
        ui->SpinFHeight->setValue(m_cPart.weld.weland_offset);
        ui->SpinFRadius->setValue(m_cPart.afSize[0]);
        ui->SpinFAngle->setValue(m_cPart.weld.Diameter);
        ui->SpinFAngle->setMaximum(m_cPart.afSize[0]);
        ui->SpinFHeight_2->setValue(m_cPart.weld.fizone_radius);
        ui->SpinFAngle_2->setValue(m_cPart.weld.fizone_angle);

    }
}

void DialogDxfFileLoad::UpdateDisplay()
{
    ui->ExpoView->clear_point();
    ui->ExpoView->update();
    ui->LabelWHeight->setText(tr("Weland Height:"));
    ui->LabelWOffset->setText(tr("Weland Offset:"));
    ui->LabelFHeight->setText(tr("Fizone Height:"));
    ui->LabelFHeight_2->setText(tr("Fiz_down Height:"));
    ui->LabelFRadius->setText(tr("Fizone Radius:"));
    ui->LabelFAngle->setText(tr("Fizone Angle:"));
    ui->LabelFAngle_2->setText(tr("Fiz_down Angle:"));
    ui->LabelUnitFAngle->setText(tr("deg"));
    ui->ComWeldSymetry->setItemText(0,tr("Symmetry"));
    ui->ComWeldSymetry->setItemText(1,tr("Left"));
    ui->ComWeldSymetry->setItemText(2,tr("Right"));
    while(ui->ComWeldSymetry->count() > 3 && m_cPart.weld.eType != setup_WELD_TKY)
    {
        ui->ComWeldSymetry->removeItem(3);
        ui->ComWeldSymetry->removeItem(4);
        ui->ComWeldSymetry->removeItem(5);
        ui->ComWeldSymetry->removeItem(6);
    }
    ui->LabelSymetry->setText(tr("Symmetry:"));
    switch(m_cPart.weld.eType)
    {
    case setup_WELD_I:
        ui->frame_3->setVisible(false);
        ui->frame_4->setVisible(false);
        ui->frame_5->setVisible(false);
        ui->frame_6->setVisible(false);
        ui->frame_7->setVisible(false);
        break;
    case setup_WELD_V:
    case setup_WELD_DV:
        ui->frame_3->setVisible(true);
        ui->frame_4->setVisible(false);
        ui->frame_5->setVisible(false);
        ui->frame_6->setVisible(true);
        ui->frame_7->setVisible(false);
        break;
    case setup_WELD_U:
        ui->frame_3->setVisible(true);
        ui->frame_4->setVisible(false);
        ui->frame_5->setVisible(true);
        ui->frame_6->setVisible(true);
        ui->frame_7->setVisible(false);
        break;
    case setup_WELD_DIFF_DV:
        ui->frame_3->setVisible(true);
        ui->frame_4->setVisible(true);
        ui->frame_5->setVisible(false);
        ui->frame_6->setVisible(true);
        ui->frame_7->setVisible(true);
        break;
    case setup_WELD_J:
        ui->frame_3->setVisible(true);
        ui->frame_4->setVisible(true);
        ui->frame_5->setVisible(true);
        ui->frame_6->setVisible(true);
        ui->frame_7->setVisible(true);
        break;
    case setup_WELD_VY:
        ui->frame_3->setVisible(true);
        ui->frame_4->setVisible(true);
        ui->frame_5->setVisible(false);
        ui->frame_6->setVisible(true);
        ui->frame_7->setVisible(true);
        break;
    case setup_WELD_TKY:
        ui->frame_3->setVisible(true);
        ui->frame_4->setVisible(true);
        ui->frame_5->setVisible(true);
        ui->frame_6->setVisible(true);
        ui->frame_7->setVisible(true);
        ui->LabelWHeight->setText(tr("X1:"));
        ui->LabelWOffset->setText(tr("X2:"));
        ui->LabelFHeight->setText(tr("Y1:"));
        ui->LabelFHeight_2->setText(tr("Y2:"));
        ui->LabelFRadius->setText(tr("T1:"));
        ui->LabelFAngle->setText(tr("T2:"));
        ui->LabelFAngle_2->setText(tr("angle:"));
        ui->LabelUnitFAngle->setText(tr("mm"));
        ui->SpinFAngle_2->setRange(0,180.0);
        ui->LabelSymetry->setText(tr("Position:"));
        if(ui->ComWeldSymetry->count() != 7)
        {
        ui->ComWeldSymetry->addItem("none",3);
        ui->ComWeldSymetry->addItem("none",4);
        ui->ComWeldSymetry->addItem("none",5);
        ui->ComWeldSymetry->addItem("none",6);
        }
        ui->ComWeldSymetry->setItemText(0,tr("1"));
        ui->ComWeldSymetry->setItemText(1,tr("2"));
        ui->ComWeldSymetry->setItemText(2,tr("3"));
        ui->ComWeldSymetry->setItemText(3,tr("4"));
        ui->ComWeldSymetry->setItemText(4,tr("5"));
        ui->ComWeldSymetry->setItemText(5,tr("6"));
        ui->ComWeldSymetry->setItemText(6,tr("7"));
        qDebug()<<"ui->SpinFAngle_2->maximum() is"<<ui->SpinFAngle_2->maximum()<<endl;
        break;
    case setup_WELD_DXF:

        break;
    default :
        break;
    };

    if(m_cPart.weld.eType == setup_WELD_DXF) {
        ui->ComWeldSymetry->setEnabled(false);
        ui->frame_value->setDisabled(true);
    } else {
        ui->ComWeldSymetry->setEnabled(true);
        ui->frame_value->setEnabled(true);
    }
}

void DialogDxfFileLoad::on_comboBox_currentIndexChanged(int index)
{
    if(!ui->comboBox->hasFocus())  return;
	m_nWeldPartSel = index;
    SetDisplayMode((DISPLAY_MODE)m_nWeldPartSel);
}

void DialogDxfFileLoad::on_ComWeldType_currentIndexChanged(int index)
{
    if(!ui->ComWeldType->hasFocus())  return;
    m_cPart.weld.eType = (setup_WELD_TYPE) index;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_ComWeldSymetry_currentIndexChanged(int index)
{
    if(!ui->ComWeldSymetry->hasFocus())  return;
    if(index >= 0)
    m_cPart.weld.eSymmetry = (setup_WELD_SYMMETRY_TYPE) index;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinWHeight_valueChanged(double arg1)
{
    if(!ui->SpinWHeight->hasFocus())  return;
	m_cPart.weld.weland_height = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinWoffset_valueChanged(double arg1)
{
    if(!ui->SpinWoffset->hasFocus())  return;
    if(m_cPart.weld.eType == setup_WELD_TKY)
        m_cPart.weld.fizone_height = arg1;
    else
        m_cPart.weld.weland_offset = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFHeight_valueChanged(double arg1)
{
    if(!ui->SpinFHeight->hasFocus())  return;
    if(m_cPart.weld.eType == setup_WELD_TKY)
        m_cPart.weld.weland_offset = arg1;
    else
        m_cPart.weld.fizone_height = arg1 ;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFRadius_valueChanged(double arg1)
{
    if(!ui->SpinFRadius->hasFocus())  return;
    if(m_cPart.weld.eType == setup_WELD_TKY)
    {
        m_cPart.afSize[0] = arg1;
        ui->SpinFAngle->setMaximum(m_cPart.afSize[0]);
    }
    else
        m_cPart.weld.fizone_radius = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFAngle_valueChanged(double arg1)
{
    if(!ui->SpinFAngle->hasFocus())  return;
    if(m_cPart.weld.eType == setup_WELD_TKY)
    {
        m_cPart.weld.Diameter = arg1;
    }
    else
        m_cPart.weld.fizone_angle = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFHeight_2_valueChanged(double arg1)
{
    if(!ui->SpinFHeight_2->hasFocus())  return;
    if(m_cPart.weld.eType == setup_WELD_TKY)
        m_cPart.weld.fizone_radius = arg1;
    else
        m_cPart.weld.fizone_down_height = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFAngle_2_valueChanged(double arg1)
{
    if(!ui->SpinFAngle_2->hasFocus())  return;
    if(m_cPart.weld.eType == setup_WELD_TKY)
        m_cPart.weld.fizone_angle = arg1;
    else
        m_cPart.weld.fizone_down_angle = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_PartFileListDbClicked(QModelIndex index)
{
    QString _str = index.data().toString();
    m_cPart.weld.eType = setup_WELD_DXF;

    std::string str = m_path.toStdString();
    const char* p = str.c_str();

    sprintf(m_cPart.strPartFile, "%s%s", p, (char*)(qPrintable(_str)));

    SetWndName();
	UpdateDisplay();
	UpdateWeld();
}

void DialogDxfFileLoad::on_BtnNccPathClicked()
{
//    char _strBuf[256];
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QString _strPath = QFileDialog::getExistingDirectory(this,
                                                         QString(tr("Open Dxf File")),
                                                         QString::fromLocal8Bit(_pConfig->AppEvn.strNccFilePath));
    if(QFileInfo(_strPath).isRoot()) {
        m_path = _strPath;
    } else {
        m_path = _strPath + "/";
    }

//    strcpy(_strBuf, (char*)(qPrintable(_strPath)));
//    sprintf(m_path.toLatin1().data(), "%s/", _strBuf);
    SetWndName();
    UpdateDisplay();
    UpdateWeld();
    ListPartFiles();
}

void DialogDxfFileLoad::on_BtnNccDefaultPathClicked()
{
    m_path = QCoreApplication::applicationDirPath() + "/init/part/dxf/";
    SetWndName();
	UpdateDisplay();
	UpdateWeld();
    ListPartFiles();
}

void DialogDxfFileLoad::slot_doubleSpinBox_zoom_setValue(double value)
{
    ui->doubleSpinBox_zoom->setValue(value);
}
