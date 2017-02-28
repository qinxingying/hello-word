#include "gHeader.h"
#include "const.h"

const char* g_strPartDir		= "init/part/" ;


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
}  ;


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

}  ;

const U8 g_iToolSeparator[] = {0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0};
const char* g_strToolBarIconName[] = {
	":/icon/toolbar/resource/toobar/0-01.png",
	":/icon/toolbar/resource/toobar/0-02.png",
	":/icon/toolbar/resource/toobar/0-03.png",
	":/icon/toolbar/resource/toobar/0-04.png",
	":/icon/toolbar/resource/toobar/0-05.png",
	":/icon/toolbar/resource/toobar/0-06.png",
	":/icon/toolbar/resource/toobar/0-07.png",
	":/icon/toolbar/resource/toobar/0-10.png",
	":/icon/toolbar/resource/toobar/0-11.png",
	":/icon/toolbar/resource/toobar/0-12.png",
	":/icon/toolbar/resource/toobar/0-13.png",
	":/icon/toolbar/resource/toobar/0-14.png",
	":/icon/toolbar/resource/toobar/0-15.png",
	":/icon/toolbar/resource/toobar/0-16.png",
	":/icon/toolbar/resource/toobar/0-17.png",
	":/icon/toolbar/resource/toobar/0-18.png",
	":/icon/toolbar/resource/toobar/0-19.png",
	":/icon/toolbar/resource/toobar/0-20.png",
	":/icon/toolbar/resource/toobar/0-21.png",
	(char*)0
};

const char* g_strLanguageName[] = {
	"English",
	"����",
	"�ձ���",
	"??",
};

const char* g_strToolBarName[][4] = {
	{"New", "�½�" , "", ""},
//	{"Open *.cfg", "�� *.cfg" , "", ""},
//	{"Save *.cfg", "���� *.cfg" , "", ""},
	{"Open", "��" , "", ""},
	{"Save", "����" , "", ""},
	{"Report Add One Item", "���ӱ�����" , "", ""},
	{"Report Del One Item", "ɾ��������" , "", ""},
	{"Report Setting", "��������" , "", ""},
	{"Save Report", "���ɱ���" , "", ""},
	{"TOFD LW Straitening", "TOFD ֱͨ������" , "", ""},
	{"TOFD BW Straitening", "TOFD �ײ�����" , "", ""},
	{"TOFD LW Removal", "TOFD ���" , "", ""},
	{"TOFD SAFT", "TOFD SAFT" , "", ""},
	{"TOFD repeal", "TOFD ����" , "", ""},
	{"TOFD redo", "TOFD ����" , "", ""},
	{"TOFD length-measurement", "TOFD �ⳤ" , "", ""},
	{"TOFD height-measurement", "TOFD ���" , "", ""},
	{"TOFD depth-measurement", "TOFD ����" , "", ""},
	{"Save defect", "����ȱ��" , "", ""},
	{"CH/EN ", "��/Ӣ �л�" , "", ""},
	{"Screenshot", "����" , "", ""},
};

const char* g_strTravelMode[][4] = {
	{"True Depth", "��ʵ���" , "", ""},
	{"Half Path" , "�� �� ��" , "", ""},
};

const char* g_strTxRxMode[][4] = {
	{"Pitch Catch"   , "һ��һ��"  , "", ""},
	{"Pitch Echo"	, "����ز�"  , "", ""},
	{"Through Trans" , "�� ͸ ��"  , "", ""},
	{"TOFD"		  , "����ʱ�" , "", ""},
};

const char* g_strScanMode[][4] = {//(report)
	{"Normal"   , "��ƽ��" , "", ""},
	{"Parallel" , "ƽ ��" , "", ""},
};

const char* g_strGeometry[][4]={// (report)
	{"Plate" , "ƽ��" , "", ""},
	{"OD"	, "͹��" , "", ""},
	{"ID"	, "����" , "", ""},
};

const char* g_strTofdScanMode[][4] = {
	{"Normal", "��ƽ��" , "", ""},
	{"Parallel" , "ƽ��" , "", ""},
};

const char* g_strTofdProMode[][4] = {
	{"Whole", "ȫ��" , "", ""},
	{"Area" , "����" , "", ""},
};

const char* g_strWeldType[][4] = {
	{"I shape"	   , "I��" , "", ""},
	{"V shape"	   , "V��" , "", ""},
	{"double V shpe" , "˫V" , "", ""},
	{"U shpe"		, "U��" , "", ""},
//	{"double U shpe" , "˫U" , "", ""},
	{"Part file"	 , "�߼�����" , "", ""},
};

const char* g_strSymmetry[][4] = {
	{"Symmetry", "�Գ�" , "", ""},
	{"Left"	, "�󵥱��¿�" , "", ""},
	{"Right"   , "�ҵ����¿�" , "", ""},
};

const char* g_strLawType[][4] = {
	{"Azimuthal Sector" , "����ɨ��" , "", ""},
	{"Linear Sector"	, "����ɨ��" , "", ""},
};

const char* g_strAngleType[][4] = {
	{"Refracted Angle",		"�����" , "", ""},
	{"Primary Steering Angle", "����ƫת��" , "", ""},
	{"Beam Skew Angle",		"����ת���" , "", ""},
};

const char* g_strFocalType[][4] = {// (report)
	{"Half Path"  , "������"   , "", ""},
	{"True Depth" , "��ʵ���"  , "", ""},
	{"Projection" , "ͶӰ"	 , "", ""},
	{"Focal Plane", "������"   , "", ""},
	{"Automatic"  , "�Զ�"	, "", ""},
};

const char* g_strSkewAngle[][4] = {
	{"  0degree" , "  0��"   , "", ""},
	{" 90degree" , " 90��"  , "", ""},
	{"180degree" , "180��"	 , "", ""},
	{"270degree" , "270��"   , "", ""},
};

const char* g_strGateSelect[][4] = {
	{"Gate A" , "բ�� A"   , "", ""},
	{"Gate B" , "բ�� B"  , "", ""},
	{"Gate I" , "բ�� I"	 , "", ""},
};

const char* g_strGateSync[][4] = {
	{"Pulse", "����" , "", ""},
	{"I/"   , "I/"  , "", ""},
	{"A/"   , "A/"  , "", ""},
};

const char* g_strGateMeasure[][4] = {
	{"Peak ^" , "��ֵ"   , "", ""},
	{"Edge /" , "ǰ��"  , "", ""},
};

const char* g_strSizingCurve[][4] = {
	{"NULL"	   , "��"   , "", ""},
	{"DAC"		, "DAC"   , "", ""},
	{"Linear DAC" , "���� DAC"  , "", ""},
	{"TCG"		, "TCG"	 , "", ""},
};


const char* g_strColorLineColor[][4] = {
	{"Yellow" , "��" , "", ""},
	{"Green"  , "��" , "", ""},
	{"Red"	, "��" , "", ""},
	{"White"  , "��" , "", ""},
};

const char* g_strCScanSource[][4] = {
	{"Gate A  Amplitude"  , "բ�� A ��ֵ" , "", ""},
	{"Gate B  Amplitude"  , "բ�� B ��ֵ" , "", ""},
	{"Gate I  Position"   , "բ�� I λ��" , "", ""},
	{"Gate A  Position"   , "բ�� A λ��" , "", ""},
	{"Gate B  Position"   , "բ�� B λ��" , "", ""},
	{"Gate A-I  Position" , "բ�� A-I λ��" , "", ""},
	{"Gate B-I  Position" , "բ�� B-I λ��" , "", ""},
	{"Gate B-A  Position" , "բ�� B-A λ��" , "", ""},
};

const char* g_strWeldPartSel[][4] = {
	{"Weld"			, "��������" , "", ""},
	{"Load Part File"  , "�߼���������" , "", ""},
};

const char* g_strScanType[][4] = {
	{"One Line Scan"	, "����ɨ��" , "", ""},
	{"Raster Scan"	  , "դ��ɨ��" , "", ""},
	{"Helicoidal Scan"  , "����ɨ��" , "", ""},
};

const char* g_strEncoderType[][4] = {
	{"Time",	  "ʱ��" , "", ""},
	{"Encoder X", "������ X" , "", ""},
	{"Encoder Y", "������ Y" , "", ""},
};

const char* g_strPolarity[][4] = {
	{"Normal",  "����" , "", ""},
	{"Reverse", "��ת" , "", ""},
};

const char* g_strDirection[][4] = {
	{"Quad", "����" , "", ""},
	{"Up",   "����" , "", ""},
	{"Down", "����" , "", ""},
};

//report
const char* g_strReportName[4] = {
	"Phascan Report" , "Phascan����" , "", "",
};

const char* g_strRectifier[][4] = {//UpdateGroupConfig()
	{"RF"  , "��Ƶ" , "", ""},
	{"HW+" , "����" , "", ""},
	{"HW-" , "����" , "", ""},
	{"FW"  , "ȫ��" , "", ""},
};

const char* g_strTofdReportHead[][4] = {
	{"Channel"					, "ͨ��"	   , "", ""},
	{"Frequency"				  , "Ƶ��"	   , "", ""},
	{"Chip Size"				  , "��Ƭ�ߴ�"	, "", ""},
	{"Wedge Angle"				, "Ш��Ƕ�"	, "", ""},
	{"Probe Dealy"				, "̽ͷ�ӳ�"	, "", ""},
	{"The Probe Center Distance"  , "PCS" , "", ""},
	{"The Time Window Set"		, "ʱ�䴰���趨" , "", ""},
	{"DB Set"					 , "����������"   , "", ""},
	{"Scan Incremental"		   , "ɨ������"	, "", ""},
	{"Scan Mode"				  , "ɨ�跽ʽ"	, "", ""},
};

const char* g_strReportHead[][4] = {
	{"Part Name" , "��������" , "", ""},
	{"Part No."  , "�������" , "", ""},
	{"Position"  , "����λ��" , "", ""},
	{"Date"	  , "����"	, "", ""},
};

const char* g_strReportPath[][4] = {
	{"Path" , "·��" , "", ""},
};

const char* g_strLawConfig[][4] = {
	{"Azimuthal" , "����ɨ��" , "", ""},
	{"Linear"	, "����ɨ��" , "", ""},
	{"Depth"	 , "���"	, "", ""},
	{"Static"	, "��̬"	, "", ""},
};


#include <string.h>
const char* g_strProbe[][4] = {//fprintfReportGroupProbe()
	{"Probe Characterization" , "̽ͷ����" , "", ""},
	{"Probe Model"			, "̽ͷ�ͺ�" , "", ""},
	{"Probe Serial"		   , "̽ͷ����" , "", ""},
	{"Probe Frequency"		, "̽ͷƵ��" , "", ""},
	{"Probe Model"			, "Ш���ͺ�" , "", ""},
	{"Probe Angle"			, "Ш��Ƕ�" , "", ""},
	{"Probe Aperture"		 , "̽ͷ�׾�" , "", ""},
};

const char* g_strGroupSetup[][4] = {//fprintfReportGroupSetup()
	{"Setup"			, "����" , "", ""},
	//1
	{"Beam Delay"	   , "�����ӳ�" , "", ""},
	{"Sample Start"	 , "�������" , "", ""},
	{"Sample Range"	 , "������Χ" , "", ""},
	{"PRF"			  , "PRF" , "", ""},
	{"Type"			 , "���ģʽ" , "", ""},
	{"Averaging Factor" , "ƽ��" , "", ""},
	//7
	{"Scale Factor"	 , "��������" , "", ""},
	{"Video Filter"	 , "��Ƶ�˲���" , "", ""},
	{"Rectification"	, "�첨��ʽ" , "", ""},
	{"Band-Pass Filter" , "��ͨ�˲���" , "", ""},
	//11
	{"Gain"			 , "����" , "", ""},
	{"Mode"			 , "�շ�ģʽ" , "", ""},
	{"Sound Velocity"   , "����" , "", ""},
	{"Pulse Width"	  , "������" , "", ""},
	//15
	{"Scan Offset"	  , "ɨ��ƫ��" , "", ""},
	{"Index Offset"	 , "����ƫ��" , "", ""},
	{"Skew"			 , "ת���" , "", ""},
	{"Gate"			 , "բ��" , "", ""},
	{"Start"			, "���" , "", ""},
	{"Width"			, "���" , "", ""},
	{"Threshold"		, "��ֵ" , "", ""},
	{"Synchro"		  , "ͬ��" , "", ""},
	//23
} ;

const char* g_strCalculator[][4] = {//fprintfReportGroupCalculator()
	{"Calculator"		, "����" , "", ""},
	//
	{"Element Qty"	   , "��Ԫ��" , "", ""},
	{"First TX Element"  , "TX��ʼ��Ԫ" , "", ""},
	{"Last TX Element"   , "TXĩ��Ԫ" , "", ""},
	{"First RX Element"  , "RX��ʼ��Ԫ" , "", ""},
	{"Last RX Element"   , "RXĩ��Ԫ" , "", ""},
	{"Resolution"		, "��Ԫ����" , "", ""},
	//
	{"Start Angle"	   , "��ʼ�Ƕ�" , "", ""},
	{"Stop Angle"		, "��ֹ�Ƕ�" , "", ""},
	{"Angle Resolution"  , "�ǶȲ���" , "", ""},
	{"Law Configuration" , "�۽���������" , "", ""},
	//
	{"Focal Type"		, "�۽�����" , "", ""},
	{"Position Start"	, "��ʼλ��" , "", ""},
	{"Position End"	  , "��ֹλ��" , "", ""},
	{"Position Step"	 , "λ�ò���" , "", ""},
	{"Offset Start"	  , "ƫ�����" , "", ""},
	{"Offset Stop"	   , "ƫ���յ�" , "", ""},
	{"Depth Start"	   , "������" , "", ""},
	{"Depth Stop"		, "����յ�" , "", ""},
};

const char* g_strGroupPart[][4] = {//fprintfReportGroupPart()
	{"Part"	  , "����" , "", ""},
	{"Material"  , "����" , "", ""},
	{"Geometry"  , "������״" , "", ""},
	{"Thickness" , "���" , "", ""},
} ;

const char* g_strSignature[][4] = {//SfprintfReportSignature()
	{"	Technician Name :", "		   ����Ա���� :" , "", ""},
	{"Technician Signature:", "		   ����Աǩ�� :" , "", ""},
	{"		 Contractor :", "			  �а��� :" , "", ""},
	{"			   Date :", "				���� :" , "", ""},
} ;

const char* g_strOnOff[][4] = {
	{"Off" , "��" , "", ""},
	{"ON"  , "��" , "", ""},
};

const char* g_strDefect[][4] =
{
	{"Defect"   ,       "ȱ   ��" , "", ""},
	{"Remark"   ,       "��   ע" , "", ""},
	{"Index"	,       "��   ��" , "", ""},
	{"Position start" , "��ʼλ��" , "", ""},
	{"Length"   ,       "��   ��" , "", ""},
	{"Depth start"	,   "��ʼ���" , "", ""},
	{"Height"   ,       "��   ��" , "", ""},
	{"Index pos",       "����λ��" , "", ""},
	{"Width"	,       "��   ��" , "", ""},
} ;

const char* g_strReportSetGroupParamMode[][4] = {
	{"Without Group Parameters" , "�����[��]" , "", ""},
	{"With Group Parameters"    , "�����[��]" , "", ""},
};

/*

*/

#include <qdatetime.h>
#include <QCoreApplication>
int ToolBarCnt()
{
	int i = 0;
	while((U32)g_strToolBarIconName[i] != 0)
	{
		i++;
	}
	return i;
}
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
//#include <QStandardPaths>
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
		_str = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);
		sprintf(_strDesk, "%s\\cache.dat", (char*)(qPrintable(_str)));

		QFile::remove(_strDesk);
		sleep(200);
		QFile::copy(_strTmp, _strDesk);
	}
}

