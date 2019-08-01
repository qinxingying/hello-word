﻿#ifndef FILESTRUCT_H
#define FILESTRUCT_H
#include <string>
#include "Instrument.h"

#define CONFIG_FILE_VERSION    "VERSION1.1"

const int ENV_MAX_GROUP_QTY = 8;
enum FILE_TYPE
{
    FILE_TYPE_CONFIG = 0x11111111,
    FILE_TYPE_SCAN_DATA = 0x22222222
} ;

struct FILE_HEADER
{
    FILE_TYPE eType;
    char strVersion[64];
};

enum setup_LANG
{
    setup_LANG_ENGLISH = 0,
    setup_LANG_CHINESE,
    setup_LANG_JAPANESE,
    setup_LANG_KOREAN
};
enum setup_SOUND_UNIT
{
    setup_SOUND_AXIX_UNIT_MM = 0,
    setup_SOUND_AXIX_UNIT_INCH,
    setup_SOUND_AXIS_TIME
};


struct SYSTEM_ENVIRMENT
{
    setup_LANG       eLanguage;
    setup_SOUND_UNIT eUnit;

	char strDataFilePath[256];
	char strNccFilePath[256];
	char strSoftwareReg[64];

	int year;
	int month;
	int day;
	bool bRegStatus;
    int iTofdDataProMode;
	bool bSAxisCursorSync;
	bool bTrueDepth_A_S_Sync;
    //bool bShowGate   [ENV_MAX_GROUP_QTY];
    bool bShowWeld   [ENV_MAX_GROUP_QTY];
    bool bShowMeasure[ENV_MAX_GROUP_QTY];
    bool bShowCursor [ENV_MAX_GROUP_QTY];
    bool bShowThickness[ENV_MAX_GROUP_QTY];
    bool bShowLwBw[ENV_MAX_GROUP_QTY];
    bool bShowDefect[ENV_MAX_GROUP_QTY];
    unsigned int  anMeasureSelection[2][8];
    float	bCursor[ENV_MAX_GROUP_QTY][setup_CURSOR_MAX]; //保存参考线信息
    int bShowGateA[ENV_MAX_GROUP_QTY];    //表示A闸门可见性
    int bShowGateB[ENV_MAX_GROUP_QTY];    //表示B闸门可见性
    int bShowGateI[ENV_MAX_GROUP_QTY];    //表示I闸门可见性
    int CScanSource[ENV_MAX_GROUP_QTY][2];
    int DisplayMode[ENV_MAX_GROUP_QTY];
};

#endif // FILESTRUCT_H
