#include <QtGui/QApplication>
#include <QApplication>
#include <QTextCodec>
#include "ui/MainWindow.h"
#include "configure/const.h"
#include "dialog/DialogRegister.h"


#define REG_DAYS_MIN						0

MainWindow* g_pMainWnd = NULL;

#ifdef QT_NO_DEBUG
int SoftwareRegister();
#endif


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));

	MainWindow _mainWindow;
	g_pMainWnd  = &_mainWindow;
	_mainWindow.show();
	_mainWindow.showMaximized();
	_mainWindow.setMinimumSize(_mainWindow.width(), _mainWindow.height());

#ifdef QT_NO_DEBUG
	if(SoftwareRegister() < REG_DAYS_MIN) {
		_mainWindow.SoftwareRegisterError();
	} else
#endif
	{
		if(argc > 1) {
			sleep(200);
			if(argv[1]) {
				_mainWindow.OpenFilePro(QString(QObject::tr(argv[1])));
			}
		}
	}

	return app.exec();
}

#ifdef QT_NO_DEBUG
int SoftwareRegister()
{
	while(g_pMainWnd == NULL);
	char _strCpuID[256];
	GetHardwareInfo(_strCpuID);

	int  _regDays = -1;
	DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
	QDate _last = _pConfig->GetLastDate();
	QDate _curDate = GetSysTime();


	if(_last.daysTo(_curDate) < 0) {
		_regDays = SYSTEM_TIME_ERROR;
		char buff[256];
		sprintf(buff,"(1)error! (%04d-%02d-%02d)(%04d-%02d-%02d) - %d ",
				_last.year(), _last.month(), _last.day(),
				_curDate.year(), _curDate.month(), _curDate.day(), _last.daysTo(_curDate));
		QMessageBox::information(NULL, "Note", buff, QMessageBox::Yes);
	} else {
		char _strSN[64];
		char _strRegInfo[64];

		strcpy(_strSN, _pConfig->AppEvn.strSoftwareReg);
		if(UnLockRegStr(_strSN, _strRegInfo, (const char*)_strCpuID, 32)) {
			if(VerRegInfo(_strRegInfo, _strCpuID)) {
				_regDays = GetRegDays(_strRegInfo, _last);
			}
		}

		if(_regDays > SYSTEM_TIME_ERROR && _regDays < REG_DAYS_MIN) {
			DialogRegister _dialog(g_pMainWnd);
			_dialog.exec();

			strcpy(_strSN, _pConfig->AppEvn.strSoftwareReg);
			if(UnLockRegStr(_strSN, _strRegInfo, (const char*)_strCpuID, 32)) {
				if(VerRegInfo(_strRegInfo, _strCpuID)) {
					_regDays = GetRegDays(_strRegInfo, _last);
				}
			}
		}
	}

	if(_regDays == SYSTEM_TIME_ERROR) {
		switch(_pConfig->AppEvn.eLanguage)
		{
		case setup_LANG_ENGLISH:
			QMessageBox::information(NULL, "Note", "System time error !", QMessageBox::Yes);
			break;
		case setup_LANG_CHINESS:
			QMessageBox::information(NULL, "注意", "系统时间错误！", QMessageBox::Yes);
			break;
		default:
			_pConfig->AppEvn.bRegStatus = true;
			break;
		}
	}

	return _regDays;
}
#endif


