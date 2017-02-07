#include "DialogWeldPartLoad.h"
#include "ui_DialogWeldPartLoad.h"
#include "ParameterProcess.h"
#include "DopplerConfigure.h"

#include <QFileDialog>
#include <QDir.h>
#include <QStandardItem>
#include <QDebug>

DialogWeldPartLoad::DialogWeldPartLoad(QWidget *parent , int nGroupId_) :
	QDialog(parent),
	ui(new Ui::DialogWeldPartLoad)
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

    SetWndName();
	UpdateDisplay();

	ListPartFiles();
    connect(ui->ListPartFile, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_PartFileListDbClicked(QModelIndex)));
    connect(ui->BtnNccPath, SIGNAL(clicked()), this, SLOT(on_BtnNccPathClicked()));
    connect(ui->BtnNccDefaultPath, SIGNAL(clicked()), this, SLOT(on_BtnNccDefaultPathClicked()));
}

DialogWeldPartLoad::~DialogWeldPartLoad()
{
	delete ui;
}

void DialogWeldPartLoad::SetWndName()
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
    DopplerConfigure* m_pConfig = DopplerConfigure::Instance();
    ui->LabelPartFilePath->setText(m_pConfig->AppEvn.strNccFilePath);

}

void DialogWeldPartLoad::SetDisplayMode(DISPLAY_MODE eMode_)
{
    m_eDisplay = eMode_;
	if(eMode_ == DISPLAY_WELD)
	{
		ui->WeldGroupShow->show();
		ui->PartGroupShow->hide();
		//ui->BtnNccPath->hide();
		ui->LabelPartFilePath->hide();
    }else{
		ui->PartGroupShow->show();
		ui->WeldGroupShow->hide();
		//ui->BtnNccPath->show();
		ui->LabelPartFilePath->show();
	}
}

void DialogWeldPartLoad::ListPartFiles()
{
    QString g_strPartDir = QDir::currentPath() + "/init/part/ncc/";
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
	for(int i=0; i<file_count; i++)
	{
		QFileInfo file_info = list.at(i);
		QString suffix = file_info.suffix();
		if(QString::compare(suffix, QString("ncc"), Qt::CaseInsensitive) == 0)
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

void DialogWeldPartLoad::SetPart()
{
    ParameterProcess* _process = ParameterProcess::Instance();
    PART_CONFIG* _pPart = _process->GetPart(m_nGroupId);
    memcpy((void*)&m_cPart, (void*)_pPart, sizeof(PART_CONFIG));
}

PART_CONFIG* DialogWeldPartLoad::GetPart()
{
    return &m_cPart;
}

void DialogWeldPartLoad::UpdateWeld()
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
}

void DialogWeldPartLoad::UpdateDisplay()
{
	ui->ExpoView->update();

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
	case setup_WELD_NCC:

		break;
    default :
		break;
    };

	if(m_cPart.weld.eType == setup_WELD_NCC) {
        ui->ComWeldSymetry->setEnabled(false);
        ui->frame_value->setDisabled(true);
	} else {
        ui->ComWeldSymetry->setEnabled(true);
        ui->frame_value->setEnabled(true);
	}
}

void DialogWeldPartLoad::on_comboBox_currentIndexChanged(int index)
{
    if(!ui->comboBox->hasFocus())  return;
	m_nWeldPartSel = index;
    SetDisplayMode((DISPLAY_MODE)m_nWeldPartSel);
}

void DialogWeldPartLoad::on_ComWeldType_currentIndexChanged(int index)
{
    if(!ui->ComWeldType->hasFocus())  return;
    m_cPart.weld.eType = (setup_WELD_TYPE) index;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_ComWeldSymetry_currentIndexChanged(int index)
{
    if(!ui->ComWeldSymetry->hasFocus())  return;
    m_cPart.weld.eSymmetry = (setup_WELD_SYMMETRY_TYPE) index;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinWHeight_valueChanged(double arg1)
{
    if(!ui->SpinWHeight->hasFocus())  return;
	m_cPart.weld.weland_height = arg1;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinWoffset_valueChanged(double arg1)
{
    if(!ui->SpinWoffset->hasFocus())  return;
    m_cPart.weld.weland_offset = arg1;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinFHeight_valueChanged(double arg1)
{
    if(!ui->SpinFHeight->hasFocus())  return;
	m_cPart.weld.fizone_height = arg1 ;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinFRadius_valueChanged(double arg1)
{
    if(!ui->SpinFRadius->hasFocus())  return;
    m_cPart.weld.fizone_radius = arg1;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinFAngle_valueChanged(double arg1)
{
    if(!ui->SpinFAngle->hasFocus())  return;
    m_cPart.weld.fizone_angle = arg1;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinFHeight_2_valueChanged(double arg1)
{
    if(!ui->SpinFHeight_2->hasFocus())  return;
    m_cPart.weld.fizone_down_height = arg1 ;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_SpinFAngle_2_valueChanged(double arg1)
{
    if(!ui->SpinFAngle_2->hasFocus())  return;
    m_cPart.weld.fizone_down_angle = arg1;
    UpdateDisplay();
}

void DialogWeldPartLoad::on_PartFileListDbClicked(QModelIndex index)
{
    QString g_strPartDir = QDir::currentPath() + "/init/part/ncc/";

	QString _str = index.data().toString();
	m_cPart.weld.eType = setup_WELD_NCC;

    sprintf(m_cPart.strPartFile, "%s%s", g_strPartDir.toLatin1().data(), (char*)(qPrintable(_str)));

    SetWndName();
	UpdateDisplay();
	UpdateWeld();
}

void DialogWeldPartLoad::on_BtnNccPathClicked()
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

void DialogWeldPartLoad::on_BtnNccDefaultPathClicked()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QString g_strPartDir = QDir::currentPath() + "/init/part/ncc/";
    strcpy(_pConfig->AppEvn.strNccFilePath, g_strPartDir.toLatin1().data());
    SetWndName();
	UpdateDisplay();
	UpdateWeld();
	ListPartFiles();
}
