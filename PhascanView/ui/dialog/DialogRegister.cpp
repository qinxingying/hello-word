#include "DialogRegister.h"
#include "ui_DialogRegister.h"
#include <stdio.h>
#include <configure/DopplerConfigure.h>

DialogRegister::DialogRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRegister)
{
    ui->setupUi(this);
	//setWindowTitle(tr("Software registration")) ;

	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	switch(_pConfig->AppEvn.eLanguage)
	{
	case setup_LANG_ENGLISH:
		setWindowTitle(tr("Software registration")) ;
		ui->RegBtn->setText(QString(tr("Enter")));
		break;
	case setup_LANG_CHINESS:
		setWindowTitle(tr("Èí¼þ×¢²á")) ;
		ui->RegBtn->setText(QString(tr("ÊäÈë")));
		break;
	default:
		break;
	}

	ui->lineEditSN1->setInputMethodHints(Qt::ImhUppercaseOnly);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	connect(ui->lineEditSN1, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged1(const QString &)));
/*
	connect(ui->lineEditSN2, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged2(const QString &)));
	connect(ui->lineEditSN3, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged3(const QString &)));
	connect(ui->lineEditSN4, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged4(const QString &)));

	connect(ui->lineEditSN5, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged5(const QString &)));
	connect(ui->lineEditSN6, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged6(const QString &)));
	connect(ui->lineEditSN7, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged7(const QString &)));
	connect(ui->lineEditSN8, SIGNAL(textChanged(const QString &)),this,SLOT(slotTextChanged8(const QString &)));
*/
	connect(ui->RegBtn,SIGNAL(clicked()),this,SLOT(slotRegBtnClicked()));
	ui->lineEditSN1->setFocus();
}

DialogRegister::~DialogRegister()
{
    delete ui;
}

void DialogRegister::slotTextChanged1(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN1->setText(QString(tr(strBuf)));

	if(_ret) ui->RegBtn->setFocus();
//	if(_ret) ui->lineEditSN2->setFocus();
}
/*
void DialogRegister::slotTextChanged2(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN2->setText(QString(tr(strBuf)));

	if(_ret) ui->lineEditSN3->setFocus();
}

void DialogRegister::slotTextChanged3(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN3->setText(QString(tr(strBuf)));

	if(_ret) ui->lineEditSN4->setFocus();
}

void DialogRegister::slotTextChanged4(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN4->setText(QString(tr(strBuf)));

	if(_ret) ui->lineEditSN5->setFocus();
}

void DialogRegister::slotTextChanged5(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN5->setText(QString(tr(strBuf)));

	if(_ret) ui->lineEditSN6->setFocus();
}

void DialogRegister::slotTextChanged6(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN6->setText(QString(tr(strBuf)));

	if(_ret) ui->lineEditSN7->setFocus();
}

void DialogRegister::slotTextChanged7(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN7->setText(QString(tr(strBuf)));

	if(_ret) ui->lineEditSN8->setFocus();
}

void DialogRegister::slotTextChanged8(const QString& str_)
{
	char strBuf[256];
	bool _ret = RegCharacterPro(str_, strBuf);
	ui->lineEditSN8->setText(QString(tr(strBuf)));

	//if(_ret) ui->lineEditSN7->setFocus();
	if(_ret) ui->RegBtn->setFocus();
}
*/
bool DialogRegister::RegCharacterPro(const QString& str_, char* buf_)
{
	strcpy(buf_, (char*)(qPrintable(str_)));
	int _nLen = strlen(buf_);
	if(_nLen > 0) {
		int i = _nLen - 1;
		int ascii = buf_[i];

		if(ascii > 96 && ascii < 123) {
			buf_[i] -= 32;
		} else if(ascii > 64 && ascii < 91) {
		} else {
			buf_[i] = '\0';
		}
	}

	const int REG_LEN = 39;
	if(strlen(buf_) >= REG_LEN) {
		buf_[REG_LEN] = '\0';
		return true;
	}
	return false;
}

void DialogRegister::slotRegBtnClicked()
{
/*	QString _str1 =  ui->lineEditSN1->text();
	QString _str2 =  ui->lineEditSN2->text();
	QString _str3 =  ui->lineEditSN3->text();
	QString _str4 =  ui->lineEditSN4->text();
	QString _str5 =  ui->lineEditSN5->text();
	QString _str6 =  ui->lineEditSN6->text();
	QString _str7 =  ui->lineEditSN7->text();
	QString _str8 =  ui->lineEditSN8->text();

	char strSN[256];
	sprintf(strSN, "%s%s%s%s%s%s%s%s",
			(char*)qPrintable(_str1),
			(char*)qPrintable(_str2),
			(char*)qPrintable(_str3),
			(char*)qPrintable(_str4),
			(char*)qPrintable(_str5),
			(char*)qPrintable(_str6),
			(char*)qPrintable(_str7),
			(char*)qPrintable(_str8));

	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	strcpy(_pConfig->AppEvn.strSoftwareReg, strSN);
	_pConfig->SetLastDate();
*/
	QString _str =  ui->lineEditSN1->text();
	char strSN[256];

	strcpy(strSN, (char*)qPrintable(_str));

	int _nLen = strlen(strSN);
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	memset(_pConfig->AppEvn.strSoftwareReg, 0, 33);
	int n = 0;
	for(int i = 0; i < _nLen; i++) {
		if(strSN[i] != '-') {
			_pConfig->AppEvn.strSoftwareReg[n] = strSN[i];
			n++;
		}
	}
	_pConfig->AppEvn.strSoftwareReg[n] = '\0';
	_pConfig->SaveEvn() ;

	close();
}

