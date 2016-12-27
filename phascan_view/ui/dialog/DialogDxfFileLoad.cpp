#include "DialogDxfFileLoad.h"
#include "ui_DialogDxfFileLoad.h"
#include "ParameterProcess.h"

#include <QFileDialog>
#include <QDir.h>
#include <QStandardItem>

DialogDxfFileLoad::DialogDxfFileLoad(QWidget *parent , int nGroupId_) :
	QDialog(parent),
    ui(new Ui::DialogDxfFileLoad)
{
	ui->setupUi(this);
    SetDisplayMode(DISPLAY_WELD);
	m_nGroupId = nGroupId_ ;
	m_nWeldPartSel = 0;

    m_pConfig = DopplerConfigure::Instance();

	SetPart();
    UpdateWeld();
    ui->ExpoView->SerPart(&m_cPart);

	ui->ExpoView->setAutoFillBackground(true);
	QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    ui->ExpoView->setPalette(palette);

    SetWndName();
	UpdateDisplay();

	ListPartFiles();
    connect(ui->ListPartFile, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_PartFileListDbClicked(QModelIndex)));
    connect(ui->BtnNccPath, SIGNAL(clicked()), this, SLOT(on_BtnNccPathClicked()));
    connect(ui->BtnNccDefaultPath, SIGNAL(clicked()), this, SLOT(on_BtnNccDefaultPathClicked()));
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

	if(_bPartFile) {
		char buf[256];
		strcpy(buf, m_cPart.strPartFile);
		CharFilter(buf, (char*)"/");
        ui->LabelPartFileName->setText(QString(tr(buf)));
	}

	ui->LabelPartFileName->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgb(180, 180, 180);");
    ui->ComWeldType->setCurrentIndex(m_cPart.weld.eType);
    ui->LabelPartFilePath->setText(QString(tr(m_pConfig->AppEvn.strNccFilePath)));
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
    QString g_strPartDir = QDir::currentPath() + "/init/part_dxf/";
    QDir dir(g_strPartDir);
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
}

void DialogDxfFileLoad::UpdateDisplay()
{
	ui->ExpoView->update();
	switch(m_cPart.weld.eType)
	{
	case setup_WELD_I :
		ui->SpinFHeight->setVisible(false);
		ui->SpinFRadius->setVisible(false);
		ui->SpinFAngle->setVisible(false);

        ui->LabelFHeight->setVisible(false);
        ui->LabelFAngle->setVisible(false);
        ui->LabelFRadius->setVisible(false);
		ui->LabelUnitFHeight->setVisible(false);
		ui->LabelUnitFAngle->setVisible(false);
		ui->LabelUnitFRadius->setVisible(false);
		break;
	case setup_WELD_V :
	case setup_WELD_DV :
		ui->SpinFHeight->setVisible(true);
		ui->SpinFRadius->setVisible(false);
		ui->SpinFAngle->setVisible(true);

        ui->LabelFHeight->setVisible(true);
        ui->LabelFAngle->setVisible(true);
        ui->LabelFRadius->setVisible(false);
		ui->LabelUnitFHeight->setVisible(true);
		ui->LabelUnitFAngle->setVisible(true);
		ui->LabelUnitFRadius->setVisible(false);
		break;
	case setup_WELD_U :
	case setup_WELD_NCC:
		ui->SpinFHeight->setVisible(true);
		ui->SpinFRadius->setVisible(true);
		ui->SpinFAngle->setVisible(true);

        ui->LabelFHeight->setVisible(true);
        ui->LabelFAngle->setVisible(true);
        ui->LabelFRadius->setVisible(true);
		ui->LabelUnitFHeight->setVisible(true);
		ui->LabelUnitFAngle->setVisible(true);
		ui->LabelUnitFRadius->setVisible(true);
		break;
	default:
		break;
    };

	if(m_cPart.weld.eType == setup_WELD_NCC) {
        ui->ComWeldSymetry->setEnabled(false);
        ui->frame_5->setDisabled(true);
	} else {
        ui->ComWeldSymetry->setEnabled(true);
        ui->frame_5->setEnabled(true);
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
    m_cPart.weld.weland_offset = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFHeight_valueChanged(double arg1)
{
    if(!ui->SpinFHeight->hasFocus())  return;
	m_cPart.weld.fizone_height = arg1 ;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFRadius_valueChanged(double arg1)
{
    if(!ui->SpinFRadius->hasFocus())  return;
    m_cPart.weld.fizone_radius = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_SpinFAngle_valueChanged(double arg1)
{
    if(!ui->SpinFAngle->hasFocus())  return;
    m_cPart.weld.fizone_angle = arg1;
    UpdateDisplay();
}

void DialogDxfFileLoad::on_PartFileListDbClicked(QModelIndex index)
{
    QString g_strPartDir = QDir::currentPath() + "/init/part_dxf/";

	QString _str = index.data().toString();
	m_cPart.weld.eType = setup_WELD_NCC;

    sprintf(m_cPart.strPartFile, "%s%s", g_strPartDir.toLatin1().data(), (char*)(qPrintable(_str)));

    SetWndName();
	UpdateDisplay();
	UpdateWeld();
}

void DialogDxfFileLoad::on_BtnNccPathClicked()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    char _strBuf[256];

	QString _strPath = QFileDialog::getExistingDirectory(this,
														 QString(tr("")),
														 _pConfig->AppEvn.strNccFilePath
														 );
	strcpy(_strBuf, (char*)(qPrintable(_strPath)));
	sprintf(_pConfig->AppEvn.strNccFilePath, "%s/", _strBuf);
    SetWndName();
	UpdateDisplay();
	UpdateWeld();
	ListPartFiles();
}

void DialogDxfFileLoad::on_BtnNccDefaultPathClicked()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QString g_strPartDir = QDir::currentPath() + "/init/part_dxf/";
    strcpy(_pConfig->AppEvn.strNccFilePath, g_strPartDir.toLatin1().data());
    SetWndName();
	UpdateDisplay();
	UpdateWeld();
	ListPartFiles();
}
