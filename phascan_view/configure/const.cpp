#include "gHeader.h"
#include "const.h"

#include <string.h>
#include <QCoreApplication>
#include <stdio.h>

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

    QString _str0 = QCoreApplication::applicationDirPath();
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
