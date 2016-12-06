#ifndef DOPPLERPART_H
#define DOPPLERPART_H

//#include <math.h>
#include <QPainter>
#include <QObject>
#include <configure/Instrument.h>
#include <QPolygonF>

enum NCC_CMD_TYPE
{
	NCC_CMD_NULL			= -1,
	NCC_CMD_SCALE			= 0,
	NCC_CMD_MOVE_TO			= 1,
	NCC_CMD_LINE_TO			= 2,
	NCC_CMD_CURVE_TO		= 3,
	NCC_CMD_ARC_POSITIVE	= 4,
	NCC_CMD_ARC_NEGATIVE	= 5,
	NCC_CMD_LINE_WIDTH		= 6,
	NCC_CMD_LINE_MODE		= 7,
	NCC_CMD_COLOR_CHANGE	= 8,
	NCC_CMD_MAX				= 9
};

typedef struct _NCC_CMD
{
	NCC_CMD_TYPE	eCmd;
	float			data[4];
}NCC_CMD;

typedef struct _DRAW_PART_INFO
{
//	QPointF	Origin;
	float fX;
	float fY;
	int   fWidth;
	int   fHeight;
	float fScaleX;
	float fScaleY;
}DRAW_PART_INFO;


class DopplerPart : public QObject
{
    Q_OBJECT
public:
	QList<NCC_CMD*>*  m_listCmd;
	//QList<QPointF*>*  m_listLines;
	//QPolygonF         m_Lines;

	QPointF			m_ptCur;
	PART_CONFIG*	m_pPart;
	DRAW_PART_INFO	m_Info;
	float m_fThickness ;

public:
	void SetInfo(DRAW_PART_INFO info_) {m_Info = info_;}
	int SetPart(PART_CONFIG* pInfo_);
	void AdaptiveArea();
	void DrawOriginLine(QPainter& painter);
	void DrawNccPart(QPainter& painter);

	void DrawNccPart(QPainterPath& path);

private:
	NCC_CMD* GetNccCmd(char* str_);
	int GetNccCmdList(QList<NCC_CMD*>* listCmd_);

	//-----------------------------------------------------------------------
	void CmdMoveTo(NCC_CMD* pCmd_);
	void CmdLineTo(QPainter& painter, NCC_CMD* pCmd_);
	void CmdCurveTo(QPainter& painter, NCC_CMD* pCmd_);
	void CmdArcPositive(QPainter& painter, NCC_CMD* pCmd_);
	void CmdArcNegative(QPainter& painter, NCC_CMD* pCmd_);
	void DrawCurveTo(QPainter& painter, QPointF pt1_, QPointF pt2_, QPointF pt3_);
	//-----------------------------------------------------------------------
	void CmdMoveTo(QPainterPath& path, NCC_CMD* pCmd_);
	void CmdLineTo(QPainterPath& path, NCC_CMD* pCmd_);
	void CmdCurveTo(QPainterPath& path, NCC_CMD* pCmd_);
	void CmdArcPositive(QPainterPath& path, NCC_CMD* pCmd_);
	void CmdArcNegative(QPainterPath& path, NCC_CMD* pCmd_);
	void DrawCurveTo(QPainterPath& path, QPointF pt1_, QPointF pt2_, QPointF pt3_);
	//-----------------------------------------------------------------------

	QPointF CoordinateTrans(float x_, float y_);

public:
	explicit DopplerPart(QObject *parent = 0);
	//DopplerPart* m_pDopplerPart;
	static   DopplerPart* Instance() ;

signals:

public slots:

};

#endif // DOPPLERPART_H
