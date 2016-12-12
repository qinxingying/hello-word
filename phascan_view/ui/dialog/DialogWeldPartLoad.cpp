#include "DialogWeldPartLoad.h"
#include "ui_DialogWeldPartLoad.h"
#include <process/ParameterProcess.h>



DialogWeldPartLoad::DialogWeldPartLoad(QWidget *parent , int nGroupId_) :
	QDialog(parent),
	ui(new Ui::DialogWeldPartLoad)
{
	ui->setupUi(this);
	SetDisplayMode(DISPLAY_WELD) ;
	m_nGroupId = nGroupId_ ;
	m_nWeldPartSel = 0;

//	m_pConfig = DopplerConfigure::Instance();

	SetPart();
	UpdateWeld() ;
	ui->ExpoView->SerPart(&m_cPart);

	ui->ExpoView->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(0,0,0));
	ui->ExpoView->setPalette(palette);

    SetWndName();
	UpdateDisplay();

	ListPartFiles();
	connect(ui->ListPartFile,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_PartFileListDbClicked(QModelIndex)));
	connect(ui->BtnNccPath,SIGNAL(clicked()),this,SLOT(on_BtnNccPathClicked()));
	connect(ui->BtnNccDefaultPath,SIGNAL(clicked()),this,SLOT(on_BtnNccDefaultPathClicked()));
}

DialogWeldPartLoad::~DialogWeldPartLoad()
{
	delete ui;
}
#include <QPushButton>
void DialogWeldPartLoad::SetWndName()
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	int _bPartFile = strlen(m_cPart.strPartFile);

    setWindowTitle(QString(tr("WELD"))) ;

    ui->WeldGroupShow->setTitle(QString(tr("Weld Parameter")));
    ui->LabelType->setText(QString(tr("Type:")));
    ui->LabelSymetry->setText(QString(tr("Symmetry:")));
    ui->LabelWHeight->setText(QString(tr("Weland Height:")));
    ui->LabelWOffset->setText(QString(tr("Weland Offset:")));
    ui->LabelFHeight->setText(QString(tr("Fizone Height:")));
    ui->LabelFRadius->setText(QString(tr("Fizone Radius:")));
    ui->LabelFAngle->setText(QString(tr("Fizone Angle:")));

    ui->PartGroupShow->setTitle(QString(tr("Part File")));
    ui->BtnNccPath->setText(QString(tr("Path Setting")));
    ui->BtnNccDefaultPath->setText(QString(tr("Default path")));
    if(!_bPartFile) {
        ui->LabelPartFileName->setText(QString(tr("Not Load")));
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString(tr("Ok")));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QString(tr("Cancel")));

	if(_bPartFile) {
		char buf[256];
		strcpy(buf, m_cPart.strPartFile);
		CharFilter(buf, (char*)"/");
		ui->LabelPartFileName->setText(QString(tr(buf)));
	}
	ui->LabelPartFileName->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgb(180, 180, 180);");

//	int iLang = eLang;

	ui->comboBox->clear();
	for(int i = 0; i < 2; i++) {
        ui->comboBox->addItem(g_strWeldPartSel[i]);
	}
	ui->comboBox->setCurrentIndex(m_nWeldPartSel);
	//----------------------------
	ui->ComWeldType->clear();
	if(_bPartFile) {
		for(int i = 0; i < setup_WELD_MAX; i++) {
            ui->ComWeldType->addItem(g_strWeldType[i]);
		}
	} else {
		for(int i = 0; i < setup_WELD_MAX-1; i++) {
            ui->ComWeldType->addItem(g_strWeldType[i]);
		}
	}

	ui->ComWeldType->setCurrentIndex(m_cPart.weld.eType);

	ui->LabelPartFilePath->setText(QString(tr(m_pConfig->AppEvn.strNccFilePath)));
	//----------------------------
	ui->ComWeldSymetry->clear();
	for(int i = 0; i < 3; i++) {
        ui->ComWeldSymetry->addItem(g_strSymmetry[i]);
	}
}

void DialogWeldPartLoad::SetDisplayMode(DISPLAY_MODE eMode_)
{
	m_eDisplay = eMode_ ;
	if(eMode_ == DISPLAY_WELD)
	{
		ui->WeldGroupShow->show();
		ui->PartGroupShow->hide();
		//ui->BtnNccPath->hide();
		ui->LabelPartFilePath->hide();
	}
	else//(eMode_ == DISPLAY_PART)
	{
		ui->PartGroupShow->show();
		ui->WeldGroupShow->hide();
		//ui->BtnNccPath->show();
		ui->LabelPartFilePath->show();
	}
}
#include <QDir.h>
#include <QStandardItem>
void DialogWeldPartLoad::ListPartFiles()
{
	char _strPath[256];
	//GetExePathName1((char*)m_pConfig->AppEvn.strNccFilePath, _strPath);
	strcpy(_strPath, (char*)m_pConfig->AppEvn.strNccFilePath);
	QDir dir(_strPath);
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
			//QString absolute_file_path = file_info.absoluteFilePath();
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
		/*if(i % 2 == 1)
		{
			QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
			linearGrad.setColorAt(0, Qt::darkGreen);
			linearGrad.setColorAt(1, Qt::yellow);
			QBrush brush(linearGrad);
			item->setBackground(brush);
		}*/
		standardItemModel->appendRow(item);
	}
	ui->ListPartFile->setModel(standardItemModel);
	ui->ListPartFile->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void DialogWeldPartLoad::SetPart()
{
	ParameterProcess* _process = ParameterProcess::Instance() ;
	PART_CONFIG* _pPart = _process->GetPart(m_nGroupId) ;
	memcpy((void*)&m_cPart , (void*)_pPart, sizeof(PART_CONFIG))  ;
}

PART_CONFIG* DialogWeldPartLoad::GetPart()
{
	return &m_cPart ;
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
}

void DialogWeldPartLoad::UpdateDisplay()
{
	ui->ExpoView->update();
	switch(m_cPart.weld.eType)
	{
	case setup_WELD_I :
		ui->SpinFHeight->setVisible(false);
		ui->SpinFRadius->setVisible(false);
		ui->SpinFAngle->setVisible(false);

		ui->LabelFHeight->setVisible (false);
		ui->LabelFAngle->setVisible  (false);
		ui->LabelFRadius->setVisible (false);
		ui->LabelUnitFHeight->setVisible(false);
		ui->LabelUnitFAngle->setVisible(false);
		ui->LabelUnitFRadius->setVisible(false);
		break;
	case setup_WELD_V :
	case setup_WELD_DV :
		ui->SpinFHeight->setVisible(true);
		ui->SpinFRadius->setVisible(false);
		ui->SpinFAngle->setVisible(true);

		ui->LabelFHeight->setVisible (true);
		ui->LabelFAngle->setVisible  (true);
		ui->LabelFRadius->setVisible (false);
		ui->LabelUnitFHeight->setVisible(true);
		ui->LabelUnitFAngle->setVisible(true);
		ui->LabelUnitFRadius->setVisible(false);
		break;
	case setup_WELD_U :
	case setup_WELD_NCC:
		ui->SpinFHeight->setVisible(true);
		ui->SpinFRadius->setVisible(true);
		ui->SpinFAngle->setVisible(true);

		ui->LabelFHeight->setVisible (true);
		ui->LabelFAngle->setVisible  (true);
		ui->LabelFRadius->setVisible (true);
		ui->LabelUnitFHeight->setVisible(true);
		ui->LabelUnitFAngle->setVisible(true);
		ui->LabelUnitFRadius->setVisible(true);
		break;
	default:
		break;
	} ;


	if(m_cPart.weld.eType == setup_WELD_NCC) {
		ui->ComWeldSymetry->setEnabled(false);
		ui->SpinWHeight->setEnabled(false);
		ui->SpinWoffset->setEnabled(false);
		ui->SpinFHeight->setEnabled(false);
		ui->SpinFRadius->setEnabled(false);
		ui->SpinFAngle->setEnabled(false);
	} else {
		ui->ComWeldSymetry->setEnabled(true);
		ui->SpinWHeight->setEnabled(true);
		ui->SpinWoffset->setEnabled(true);
		ui->SpinFHeight->setEnabled(true);
		ui->SpinFRadius->setEnabled(true);
		ui->SpinFAngle->setEnabled(true);
	}
}

void DialogWeldPartLoad::on_comboBox_currentIndexChanged(int index)
{
	if(!ui->comboBox->hasFocus())  return ;
	m_nWeldPartSel = index;
	SetDisplayMode((DISPLAY_MODE)m_nWeldPartSel) ;
}

void DialogWeldPartLoad::on_ComWeldType_currentIndexChanged(int index)
{
	if(!ui->ComWeldType->hasFocus())  return ;
	m_cPart.weld.eType = (setup_WELD_TYPE) index  ;
	UpdateDisplay() ;
}

void DialogWeldPartLoad::on_ComWeldSymetry_currentIndexChanged(int index)
{
	if(!ui->ComWeldSymetry->hasFocus())  return ;
	m_cPart.weld.eSymmetry = (setup_WELD_SYMMETRY_TYPE) index  ;
	UpdateDisplay() ;
}

void DialogWeldPartLoad::on_SpinWHeight_valueChanged(double arg1)
{
	if(!ui->SpinWHeight->hasFocus())  return ;
	m_cPart.weld.weland_height = arg1;
	UpdateDisplay() ;
}

void DialogWeldPartLoad::on_SpinWoffset_valueChanged(double arg1)
{
	if(!ui->SpinWoffset->hasFocus())  return ;
	m_cPart.weld.weland_offset = arg1 ;
	UpdateDisplay() ;
}

void DialogWeldPartLoad::on_SpinFHeight_valueChanged(double arg1)
{
	if(!ui->SpinFHeight->hasFocus())  return ;
	m_cPart.weld.fizone_height = arg1 ;
	UpdateDisplay() ;
}

void DialogWeldPartLoad::on_SpinFRadius_valueChanged(double arg1)
{
	if(!ui->SpinFRadius->hasFocus())  return ;
	m_cPart.weld.fizone_radius = arg1 ;
	UpdateDisplay() ;
}

void DialogWeldPartLoad::on_SpinFAngle_valueChanged(double arg1)
{
	if(!ui->SpinFAngle->hasFocus())  return ;
	m_cPart.weld.fizone_angle = arg1 ;
	UpdateDisplay() ;
}

//#include <QMessageBox>
void DialogWeldPartLoad::on_PartFileListDbClicked(QModelIndex index)
{
	char _strPath[256];
	//GetExePathName1((char*)m_pConfig->AppEvn.strNccFilePath, _strPath);
	strcpy(_strPath, (char*)m_pConfig->AppEvn.strNccFilePath);

	QString _str = index.data().toString();
	m_cPart.weld.eType = setup_WELD_NCC;
	//strcpy(m_cPart.strPartFile, (char*)(qPrintable(_str)));
	sprintf(m_cPart.strPartFile, "%s%s", _strPath, (char*)(qPrintable(_str)));

	//QMessageBox::information(NULL, "Title", m_cPart.strPartFile, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    SetWndName();
	UpdateDisplay();
	UpdateWeld();
}
#include <QFileDialog>

void DialogWeldPartLoad::on_BtnNccPathClicked()
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance()  ;
	char _strBuf[256];
	//strcpy(_strBuf, _pConfig->AppEvn.strNccFilePath);
	//QString _strPath = QFileDialog::getExistingDirectory(this, QString(tr(_strBuf)), );
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
	DopplerConfigure* _pConfig = DopplerConfigure::Instance()  ;
	char _strBuf[256];

	GetExePathName1((char*)g_strPartDir, _strBuf);
	strcpy(_pConfig->AppEvn.strNccFilePath, _strBuf);
    SetWndName();
	UpdateDisplay();
	UpdateWeld();
	ListPartFiles();
}


