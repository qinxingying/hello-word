#include "gHeader.h"
#include "const.h"

const char* g_strMeasureFildName[][4] =
{
	{"None  "  , "None"} ,
	{"A%    "  , "Peak amplitude in gate A"} ,
	{"AdBA  "  , "Signal in gate minus gate level for gate A" } ,
	{"AdBr  "  , "Diff. between signal and reference in gate A" },
	{"B%    "  , "Peak amplitude in gate B"},
	{"BdBB  "  , "Signal in gate minus gate level for gate B"},
	{"BdBr  "  , "Diff. between signal and reference in gate B"},
	{"A^    "  , "Peak in gate A" , "A/" , "Edge in gate A"},
	{"B^    "  , "Peak in gate B" , "B/" , "Edge in gate B"},
	{"I/    "  , "Edge in gate I"},
	{"I(w)/ "  , "Edge in gate I in water"},
	{"T(A^) "  , "Thickness" , "T(A/)" , "Thickness"},
	{"ML    "  , "Percentage of material loss"},
	{"%(r)  "  , "Amplitude value for the reference cursor"},
	{"%(m)  "  , "Amplitude value of the measurement cursor"},
	{"%(m-r)"  , "Amplitude (measurement cursor - reference cursor)"},
	{"U(r)  "  , "Ultrasonic position of the reference cursor"},
	{"U(m)  "  , "Ultrasonic position of the measurement cursor"},
	{"U(m-r)"  , "Ultrasonic axis (measurement cursor - reference cursor)"},
	{"P(r)  "  , "Probe position of the reference cursor"},
	{"P(m)  "  , "Probe position of the measurement cursor"},
	{"P(m-r)"  , "Probe (measurement cursor - reference cursor)"},
	{"S(r)  "  , "Scan position of the reference cursor"},
	{"S(m)  "  , "Scan position of the measurement cursor"},
	{"S(m-r)"  , "Scan axis (measurement cursor - reference cursor)"},
	{"I(r)  "  , "Index position of the reference cursor"},
	{"I(m)  "  , "Index position of the measurement cursor"},
	{"I(m-r)"  , "Index axis (measurement cursor - reference cursor)"},
	{"RA^   "  , "Reference point to the indication in gate A" , "RA/" , "Reference point to the indication in gate A"},
	{"RB^   "  , "Reference point to the indication in gate B" , "RB/" , "Reference point to the indication in gate B"},
	{"PA^   "  , "Probe front face to the indication in gate A" ,  "PA/" , "Probe front face to the indication in gate A" },
	{"PB^   "  , "Probe front face to the indication in gate B" ,  "PB/" , "Probe front face to the indication in gate B" },
	{"DA^   "  , "Depth of the indication in gate A" , "DA/" , "Depth of the indication in gate A" },
	{"DB^   "  , "Depth of the indication in gate B" , "DB/" , "Depth of the indication in gate B"},
	{"SA^   "  , "Sound path of the indication in gate A" , "SA/" , "Sound path of the indication in gate A" },
	{"SB^   "  , "Sound path of the indication in gate B" , "SB/" , "Sound path of the indication in gate B" },
	{"ViA^  "  , "Volumetric position in gate A on the index axis" , "ViA/" , "Volumetric position in gate A on the index axis" },
	{"ViB^  "  , "Volumetric position in gate B on the index axis" , "ViB/" , "Volumetric position in gate B on the index axis" },
	{"VsA^  "  , "Volumetric position in gate A on the scan axis"  , "VsA/" , "Volumetric position in gate A on the scan axis"  },
	{"VsB^  "  , "Volumetric position in gate B on the scan axis"  , "VsB/" , "Volumetric position in gate B on the scan axis"  },
	{"LA^   "  , "Leg (skip) of the indication in gate A" , "LA/" , "Leg (skip) of the indication in gate A" },
	{"LB^   "  , "Leg (skip) of the indication in gate B" , "LB/" , "Leg (skip) of the indication in gate B" },
	{"T-D(r)"	  , "Tofd Ultrasonic Axis Reference Cursor Depth"} ,
	{"T-D(m)"	  , "Tofd Ultrasonic Axis Measure Cursor Depth"} ,
	{"T-S(m-r)"	, "Tofd Scan Axis Cursor Measure to Reference"} ,
	{"T-D(m-r)"	, "Tofd Ultrasonic Axis Cursor Measure to Reference"} ,
};

const char* g_strMeasureFildUnit[][4] =
{
	{"None  ", "NONE"} ,
	{"A%	", "%"} ,
	{"AdBA  ", "db"} ,
	{"AdBr  ", "db"},
	{"B%	", "%"},
	{"BdBB  ", "db"},
	{"BdBr  ", "db"},
	{"A^	", "mm"},
	{"B^	", "mm"},
	{"I/	", "mm"},
	{"I(w)/ ", "mm"},
	{"T(A^) ", "mm"},
	{"ML	", "%"},
	{"%(r)  ", "%"},
	{"%(m)  ", "%"},
	{"%(m-r)", "%"},
	{"U(r)  ", "mm"  },
	{"U(m)  ", "mm" },
	{"U(m-r)", "mm"  },
	{"P(r)  " , "mm" },
	{"P(m)  ", "mm"  },
	{"P(m-r)" , "mm" },
	{"S(r)  ", "mm" },
	{"S(m)  ", "mm" },
	{"S(m-r)", "mm"  },
	{"I(r)  ", "mm" },
	{"I(m)  ", "mm"  },
	{"I(m-r)", "mm"  },
	{"RA^   ", "mm"  },
	{"RB^   ", "mm"  },
	{"PA^   " , "mm" },
	{"PB^   " , "mm" },
	{"DA^   " , "mm" },
	{"DB^   " , "mm" },
	{"SA^   " , "mm" },
	{"SB^   " , "mm" },
	{"ViA^  " , "mm" },
	{"ViB^  " , "mm" },
	{"VsA^  " , "mm" },
	{"VsB^  " , "mm" },
	{"LA^   " , "mm" },
	{"LB^   " , "mm" },
	{"T-D(r)" , "mm"} ,
	{"T-D(m)" , "mm"} ,
	{"T-S(m-r)" , "mm"} ,
	{"T-D(m-r)" , "mm"}
};

#include <string.h>
#include <qdatetime.h>
#include <QCoreApplication>

#include <stdio.h>

#ifndef QT_NO_DEBUG
#include <QDir>
#include <QMessageBox>
#endif

QString GetExePathName2(char* dir)
{
	char _strPathName[256];

	GetExePathName1(dir, _strPathName);
	return QString(QObject::tr(_strPathName));
}


void GetExePathName1(char* dir, char* _strPathName)
{
#ifdef QT_NO_DEBUG
	char _strAppPath[256];

	QString	 _str0 = QCoreApplication::applicationDirPath ();
	std::string _str1 = _str0.toStdString();
	const char* _str2 = _str1.c_str();

	if(_str2) {
		strcpy(_strAppPath, _str2);
	}
	sprintf(_strPathName, "%s/%s", _strAppPath, dir);
#else
	strcpy(_strPathName, dir);
#endif
}

QDate getDate(char* strDate_)
{
	char buf[10];

	memcpy(buf, strDate_, 4);
	buf[4] = '\0';
	int year = atoi(buf);

	memcpy(buf, &strDate_[4], 2);
	buf[2] = '\0';
	int month = atoi(buf);

	memcpy(buf, &strDate_[6], 2);
	buf[2] = '\0';
	int day = atoi(buf);

	QDate date;
	date.setDate(year, month, day);

	return date;
}

bool VerRegInfo(char* strRegInfo_, char* strCpuID_)
{
	char _strDate1[64];
	char _strDate2[64];

	strcpy(_strDate1, strRegInfo_);
	strcpy(_strDate2, strCpuID_);

	_strDate1[8] = '\0';
	_strDate2[8] = '\0';

	if(strcmp(_strDate1, _strDate2) == 0) {
		return true;
	}

	return false;
}

int GetRegDays(char* strRegInfo_, QDate last_)
{
	char _strDate1[16];
	char _strDate2[16];
	memset(_strDate1, 0x00, 16);
	memset(_strDate2, 0x00, 16);

	memcpy(_strDate1, &strRegInfo_[16], 8);
	memcpy(_strDate2, &strRegInfo_[24], 8);

	QDate _date1 = getDate(_strDate1);
	QDate _date2 = getDate(_strDate2);

	QDate _date = GetSysTime();

	if(_date.daysTo(last_) > 0) {
		return SYSTEM_TIME_ERROR;
		char buff[256];
		sprintf(buff,"(2)error! (%04d-%02d-%02d)(%04d-%02d-%02d)",
				_date.year(), _date.month(), _date.day(),
				last_.year(), last_.month(), last_.day());
		QMessageBox::information(NULL, "Note", buff, QMessageBox::Yes);
	}
	if(_date.daysTo(_date1) > 0) {
		return SYSTEM_TIME_ERROR;
		char buff[256];
		sprintf(buff,"(3)error! (%04d-%02d-%02d)(%04d-%02d-%02d)",
				_date.year(), _date.month(), _date.day(),
				_date1.year(), _date1.month(), _date1.day());
		QMessageBox::information(NULL, "Note", buff, QMessageBox::Yes);
	}

	int days = _date.daysTo(_date2);

	return days;
}

QDate GetSysTime(void)
{
#if 1
	return QDate::currentDate();
#else
	char _strFile[256];
	GetExePathName1((char*)"dt.dat", _strFile);

	QFile _file(_strFile);
	char _strTime[64];
	if(_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QByteArray _line = _file.readLine();
		strcpy(_strTime, (char*)_line.data());
		_file.close();
	}
	return getDate(_strTime);
#endif
}

#include <QtNetwork/QNetworkInterface>
const char INFOSWITCH[10] = {'M','N','O','P','Q','R','S','T','U','V'};
void GetHardwareInfo(char* strInfo_)
{
	QString _str;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	_str = list.at(0).hardwareAddress();	//mac


	char _strTmp[256];
	strcpy(_strTmp, (char*)(qPrintable(_str)));

	memset(strInfo_, 0x00, 256);
	U8 _nData;
	for(int i = 0, n = 0; i < 17; i++) {
		_nData = _strTmp[i];
		if(_nData != ':') {
			if(_nData >= '0' && _nData <= '9') {
				_nData -= '0';
				_nData = INFOSWITCH[_nData];
			}
			strInfo_[n++] = _nData;
		}
	}
	strcat (strInfo_,"GDPL");
	//-------------------------------------------------------------------
	GetExePathName1((char*)"cache.dat", _strTmp);
	QFile _fileExists(_strTmp);
	if(!_fileExists.exists()) {
		QFile file(_strTmp);
		file.open (QIODevice::WriteOnly);
		QDataStream write(&file);
		write.writeRawData(strInfo_, 256) ;
		file.close();

		char _strDesk[256];
        //_str = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);
        _str = QStandardPaths::displayName(QStandardPaths::DesktopLocation);
		sprintf(_strDesk, "%s\\cache.dat", (char*)(qPrintable(_str)));

		QFile::remove(_strDesk);
		sleep(200);
		QFile::copy(_strTmp, _strDesk);
	}
}

