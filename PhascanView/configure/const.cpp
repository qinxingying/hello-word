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
	"中文",
	"日本语",
	"??",
};

const char* g_strToolBarName[][4] = {
	{"New", "新建" , "", ""},
//	{"Open *.cfg", "打开 *.cfg" , "", ""},
//	{"Save *.cfg", "保存 *.cfg" , "", ""},
	{"Open", "打开" , "", ""},
	{"Save", "保存" , "", ""},
	{"Report Add One Item", "增加报告项" , "", ""},
	{"Report Del One Item", "删除报告项" , "", ""},
	{"Report Setting", "报告设置" , "", ""},
	{"Save Report", "生成报告" , "", ""},
	{"TOFD LW Straitening", "TOFD 直通波对齐" , "", ""},
	{"TOFD BW Straitening", "TOFD 底波对齐" , "", ""},
	{"TOFD LW Removal", "TOFD 差分" , "", ""},
	{"TOFD SAFT", "TOFD SAFT" , "", ""},
	{"TOFD repeal", "TOFD 撤销" , "", ""},
	{"TOFD redo", "TOFD 重做" , "", ""},
	{"TOFD length-measurement", "TOFD 测长" , "", ""},
	{"TOFD height-measurement", "TOFD 测高" , "", ""},
	{"TOFD depth-measurement", "TOFD 测深" , "", ""},
	{"Save defect", "保存缺陷" , "", ""},
	{"CH/EN ", "中/英 切换" , "", ""},
	{"Screenshot", "截屏" , "", ""},
};

const char* g_strTravelMode[][4] = {
	{"True Depth", "真实深度" , "", ""},
	{"Half Path" , "半 声 程" , "", ""},
};

const char* g_strTxRxMode[][4] = {
	{"Pitch Catch"   , "一发一收"  , "", ""},
	{"Pitch Echo"	, "脉冲回波"  , "", ""},
	{"Through Trans" , "穿 透 法"  , "", ""},
	{"TOFD"		  , "衍射时差法" , "", ""},
};

const char* g_strScanMode[][4] = {//(report)
	{"Normal"   , "非平行" , "", ""},
	{"Parallel" , "平 行" , "", ""},
};

const char* g_strGeometry[][4]={// (report)
	{"Plate" , "平板" , "", ""},
	{"OD"	, "凸面" , "", ""},
	{"ID"	, "凹面" , "", ""},
};

const char* g_strTofdScanMode[][4] = {
	{"Normal", "非平行" , "", ""},
	{"Parallel" , "平行" , "", ""},
};

const char* g_strTofdProMode[][4] = {
	{"Whole", "全局" , "", ""},
	{"Area" , "区域" , "", ""},
};

const char* g_strWeldType[][4] = {
	{"I shape"	   , "I型" , "", ""},
	{"V shape"	   , "V型" , "", ""},
	{"double V shpe" , "双V" , "", ""},
	{"U shpe"		, "U型" , "", ""},
//	{"double U shpe" , "双U" , "", ""},
	{"Part file"	 , "高级工件" , "", ""},
};

const char* g_strSymmetry[][4] = {
	{"Symmetry", "对称" , "", ""},
	{"Left"	, "左单边坡口" , "", ""},
	{"Right"   , "右单边坡口" , "", ""},
};

const char* g_strLawType[][4] = {
	{"Azimuthal Sector" , "扇形扫查" , "", ""},
	{"Linear Sector"	, "线性扫查" , "", ""},
};

const char* g_strAngleType[][4] = {
	{"Refracted Angle",		"折射角" , "", ""},
	{"Primary Steering Angle", "主轴偏转角" , "", ""},
	{"Beam Skew Angle",		"声束转向角" , "", ""},
};

const char* g_strFocalType[][4] = {// (report)
	{"Half Path"  , "半声程"   , "", ""},
	{"True Depth" , "真实深度"  , "", ""},
	{"Projection" , "投影"	 , "", ""},
	{"Focal Plane", "任意面"   , "", ""},
	{"Automatic"  , "自动"	, "", ""},
};

const char* g_strSkewAngle[][4] = {
	{"  0degree" , "  0度"   , "", ""},
	{" 90degree" , " 90度"  , "", ""},
	{"180degree" , "180度"	 , "", ""},
	{"270degree" , "270度"   , "", ""},
};

const char* g_strGateSelect[][4] = {
	{"Gate A" , "闸门 A"   , "", ""},
	{"Gate B" , "闸门 B"  , "", ""},
	{"Gate I" , "闸门 I"	 , "", ""},
};

const char* g_strGateSync[][4] = {
	{"Pulse", "脉冲" , "", ""},
	{"I/"   , "I/"  , "", ""},
	{"A/"   , "A/"  , "", ""},
};

const char* g_strGateMeasure[][4] = {
	{"Peak ^" , "峰值"   , "", ""},
	{"Edge /" , "前沿"  , "", ""},
};

const char* g_strSizingCurve[][4] = {
	{"NULL"	   , "无"   , "", ""},
	{"DAC"		, "DAC"   , "", ""},
	{"Linear DAC" , "线性 DAC"  , "", ""},
	{"TCG"		, "TCG"	 , "", ""},
};


const char* g_strColorLineColor[][4] = {
	{"Yellow" , "黄" , "", ""},
	{"Green"  , "绿" , "", ""},
	{"Red"	, "红" , "", ""},
	{"White"  , "白" , "", ""},
};

const char* g_strCScanSource[][4] = {
	{"Gate A  Amplitude"  , "闸门 A 峰值" , "", ""},
	{"Gate B  Amplitude"  , "闸门 B 峰值" , "", ""},
	{"Gate I  Position"   , "闸门 I 位置" , "", ""},
	{"Gate A  Position"   , "闸门 A 位置" , "", ""},
	{"Gate B  Position"   , "闸门 B 位置" , "", ""},
	{"Gate A-I  Position" , "闸门 A-I 位置" , "", ""},
	{"Gate B-I  Position" , "闸门 B-I 位置" , "", ""},
	{"Gate B-A  Position" , "闸门 B-A 位置" , "", ""},
};

const char* g_strWeldPartSel[][4] = {
	{"Weld"			, "焊缝设置" , "", ""},
	{"Load Part File"  , "高级工件加载" , "", ""},
};

const char* g_strScanType[][4] = {
	{"One Line Scan"	, "单线扫查" , "", ""},
	{"Raster Scan"	  , "栅格扫查" , "", ""},
	{"Helicoidal Scan"  , "螺旋扫查" , "", ""},
};

const char* g_strEncoderType[][4] = {
	{"Time",	  "时间" , "", ""},
	{"Encoder X", "编码器 X" , "", ""},
	{"Encoder Y", "编码器 Y" , "", ""},
};

const char* g_strPolarity[][4] = {
	{"Normal",  "正常" , "", ""},
	{"Reverse", "反转" , "", ""},
};

const char* g_strDirection[][4] = {
	{"Quad", "正交" , "", ""},
	{"Up",   "向上" , "", ""},
	{"Down", "向下" , "", ""},
};

//report
const char* g_strReportName[4] = {
	"Phascan Report" , "Phascan报告" , "", "",
};

const char* g_strRectifier[][4] = {//UpdateGroupConfig()
	{"RF"  , "射频" , "", ""},
	{"HW+" , "正检" , "", ""},
	{"HW-" , "负检" , "", ""},
	{"FW"  , "全检" , "", ""},
};

const char* g_strTofdReportHead[][4] = {
	{"Channel"					, "通道"	   , "", ""},
	{"Frequency"				  , "频率"	   , "", ""},
	{"Chip Size"				  , "晶片尺寸"	, "", ""},
	{"Wedge Angle"				, "楔块角度"	, "", ""},
	{"Probe Dealy"				, "探头延迟"	, "", ""},
	{"The Probe Center Distance"  , "PCS" , "", ""},
	{"The Time Window Set"		, "时间窗口设定" , "", ""},
	{"DB Set"					 , "灵敏度设置"   , "", ""},
	{"Scan Incremental"		   , "扫描增量"	, "", ""},
	{"Scan Mode"				  , "扫描方式"	, "", ""},
};

const char* g_strReportHead[][4] = {
	{"Part Name" , "工件名称" , "", ""},
	{"Part No."  , "工件序号" , "", ""},
	{"Position"  , "工件位置" , "", ""},
	{"Date"	  , "日期"	, "", ""},
};

const char* g_strReportPath[][4] = {
	{"Path" , "路径" , "", ""},
};

const char* g_strLawConfig[][4] = {
	{"Azimuthal" , "扇形扫查" , "", ""},
	{"Linear"	, "线性扫查" , "", ""},
	{"Depth"	 , "深度"	, "", ""},
	{"Static"	, "静态"	, "", ""},
};


#include <string.h>
const char* g_strProbe[][4] = {//fprintfReportGroupProbe()
	{"Probe Characterization" , "探头表征" , "", ""},
	{"Probe Model"			, "探头型号" , "", ""},
	{"Probe Serial"		   , "探头序列" , "", ""},
	{"Probe Frequency"		, "探头频率" , "", ""},
	{"Probe Model"			, "楔块型号" , "", ""},
	{"Probe Angle"			, "楔块角度" , "", ""},
	{"Probe Aperture"		 , "探头孔径" , "", ""},
};

const char* g_strGroupSetup[][4] = {//fprintfReportGroupSetup()
	{"Setup"			, "设置" , "", ""},
	//1
	{"Beam Delay"	   , "波束延迟" , "", ""},
	{"Sample Start"	 , "采样起点" , "", ""},
	{"Sample Range"	 , "采样范围" , "", ""},
	{"PRF"			  , "PRF" , "", ""},
	{"Type"			 , "检测模式" , "", ""},
	{"Averaging Factor" , "平均" , "", ""},
	//7
	{"Scale Factor"	 , "比例因子" , "", ""},
	{"Video Filter"	 , "视频滤波器" , "", ""},
	{"Rectification"	, "检波方式" , "", ""},
	{"Band-Pass Filter" , "带通滤波器" , "", ""},
	//11
	{"Gain"			 , "增益" , "", ""},
	{"Mode"			 , "收发模式" , "", ""},
	{"Sound Velocity"   , "声速" , "", ""},
	{"Pulse Width"	  , "脉冲宽度" , "", ""},
	//15
	{"Scan Offset"	  , "扫查偏置" , "", ""},
	{"Index Offset"	 , "步进偏置" , "", ""},
	{"Skew"			 , "转向角" , "", ""},
	{"Gate"			 , "闸门" , "", ""},
	{"Start"			, "起点" , "", ""},
	{"Width"			, "宽度" , "", ""},
	{"Threshold"		, "阀值" , "", ""},
	{"Synchro"		  , "同步" , "", ""},
	//23
} ;

const char* g_strCalculator[][4] = {//fprintfReportGroupCalculator()
	{"Calculator"		, "计算" , "", ""},
	//
	{"Element Qty"	   , "阵元数" , "", ""},
	{"First TX Element"  , "TX起始阵元" , "", ""},
	{"Last TX Element"   , "TX末阵元" , "", ""},
	{"First RX Element"  , "RX起始阵元" , "", ""},
	{"Last RX Element"   , "RX末阵元" , "", ""},
	{"Resolution"		, "阵元步进" , "", ""},
	//
	{"Start Angle"	   , "起始角度" , "", ""},
	{"Stop Angle"		, "终止角度" , "", ""},
	{"Angle Resolution"  , "角度步进" , "", ""},
	{"Law Configuration" , "聚焦法则类型" , "", ""},
	//
	{"Focal Type"		, "聚焦类型" , "", ""},
	{"Position Start"	, "起始位置" , "", ""},
	{"Position End"	  , "终止位置" , "", ""},
	{"Position Step"	 , "位置步进" , "", ""},
	{"Offset Start"	  , "偏置起点" , "", ""},
	{"Offset Stop"	   , "偏置终点" , "", ""},
	{"Depth Start"	   , "深度起点" , "", ""},
	{"Depth Stop"		, "深度终点" , "", ""},
};

const char* g_strGroupPart[][4] = {//fprintfReportGroupPart()
	{"Part"	  , "工件" , "", ""},
	{"Material"  , "材料" , "", ""},
	{"Geometry"  , "工件形状" , "", ""},
	{"Thickness" , "厚度" , "", ""},
} ;

const char* g_strSignature[][4] = {//SfprintfReportSignature()
	{"	Technician Name :", "		   技术员姓名 :" , "", ""},
	{"Technician Signature:", "		   技术员签名 :" , "", ""},
	{"		 Contractor :", "			  承包商 :" , "", ""},
	{"			   Date :", "				日期 :" , "", ""},
} ;

const char* g_strOnOff[][4] = {
	{"Off" , "关" , "", ""},
	{"ON"  , "开" , "", ""},
};

const char* g_strDefect[][4] =
{
	{"Defect"   ,       "缺   陷" , "", ""},
	{"Remark"   ,       "备   注" , "", ""},
	{"Index"	,       "序   号" , "", ""},
	{"Position start" , "起始位置" , "", ""},
	{"Length"   ,       "长   度" , "", ""},
	{"Depth start"	,   "起始深度" , "", ""},
	{"Heigth"   ,       "高   度" , "", ""},
	{"Index pos",       "步进位置" , "", ""},
	{"Width"	,       "宽   度" , "", ""},
} ;

const char* g_strReportSetGroupParamMode[][4] = {
	{"Without Group Parameters" , "组参数[关]" , "", ""},
	{"With Group Parameters"    , "组参数[开]" , "", ""},
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

