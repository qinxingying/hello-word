#include <stdlib.h>
#include <math.h>
#include <QFile>
//#include <QMessageBox>
#include "DopplerPart.h"
#include <gHeader.h>

#define  NCC_CMD_START				1
#define  NCC_CMD_RUN				2
#define  NCC_CMD_END				3



const char* g_strCmdName[] = {
	"G0",
	"G1",
	"G2",
	"G3",
	"G4",
	"G5",
	"G6",
	"G7",
	"G8",
	"G9",
};

int g_nSReadtatus = 0;

static int GetNccCmdIndex(char* str_) {
	for(int i = 0; i < NCC_CMD_MAX; i++) {
		if(strcmp(str_, g_strCmdName[i]) == 0) {
			return i;
		}
	}
	return -1;
}

static void InitNccCmd(NCC_CMD* pCmd_) {
	pCmd_->eCmd = NCC_CMD_NULL;
	memset((void*)pCmd_->data, 0x00, sizeof(pCmd_->data));
}

// 获得点相对于线的位置关系 1 -- 线的上方 | 0 -- 线上 | -1 -- 线的下方
double GetPositionRelationForLine(double s64X1, double s64Y1, double s64X2, double s64Y2, double s64Xf, double s64Yf)
{
	//为了避免误使用s64X1==s64X2来调用这个函数,我们对数据稍微做下改变
	if(s64X1 == s64X2)  s64X2 = s64X2 + 1;       //偏移一下下,看不出来的

	double s64YTmp = s64Yf - s64Y1 - (s64Xf - s64X1) * (s64Y2 - s64Y1) / (s64X2 - s64X1);

	return s64YTmp;
}

// 两点间距离
double GetPositionLength(double s64X1, double s64Y1, double s64X2, double s64Y2)
{
	double dX = s64X2 - s64X1;
	double dY = s64Y2 - s64Y1;
	return sqrt(dX*dX + dY*dY);
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------


DopplerPart* g_pDopplerPar = NULL ;

DopplerPart* DopplerPart::Instance()
{
	if(!g_pDopplerPar)
	{
		g_pDopplerPar = new DopplerPart() ;
	}
	return g_pDopplerPar ;
}

DopplerPart::DopplerPart(QObject *parent) :  QObject(parent)
{
	//g_pDopplerPar = DopplerPart::Instance() ;

	m_pPart      = NULL;
	m_fThickness = 20;

	m_Info.fScaleX = 1;
	m_Info.fScaleY = 1;
	m_Info.fX = 0;
	m_Info.fY = 0;

	m_listCmd   = new QList<NCC_CMD*>;
//	m_listLines = new QList<QPointF*>;
}
/*
DopplerPart::~DopplerPart()
{
	m_listCmd->clear();
	QObject::~QObject();
}
*/

int DopplerPart::SetPart(PART_CONFIG* pInfo_)
{
	m_pPart = pInfo_;
	m_fThickness = m_pPart->afSize[0];

	int _nRet = GetNccCmdList(m_listCmd);

	return _nRet;
}

void DopplerPart::AdaptiveArea()
{
	NCC_CMD*  _pCmd;
	double x1 = 10000;
	double y1 = 10000;
	double x2 = -10000;
	double y2 = -10000;

	for(int i = 0 ; i < m_listCmd->count(); i++) {
		_pCmd = m_listCmd->at(i);

		if(_pCmd->data[0] < x1)	x1 = _pCmd->data[0];
		if(_pCmd->data[2] < x1)	x1 = _pCmd->data[2];
		if(_pCmd->data[1] < y1)	y1 = _pCmd->data[1];
		if(_pCmd->data[3] < y1)	y1 = _pCmd->data[3];

		if(_pCmd->data[0] > x2)	x2 = _pCmd->data[0];
		if(_pCmd->data[2] > x2)	x2 = _pCmd->data[2];
		if(_pCmd->data[1] > y2)	y2 = _pCmd->data[1];
		if(_pCmd->data[3] > y2)	y2 = _pCmd->data[3];
	}

	double _fW = x2 - x1;
	double _fH = y2 - y1;

	double _fW1, _fH1;

	if(_fH > _fW) {
		int _Mar = _fH / 40;

		m_Info.fScaleY = (_fH + 2 * _Mar) / m_Info.fHeight;
		m_Info.fScaleX = m_Info.fScaleY;

		_fW1 = m_Info.fWidth * m_Info.fScaleX;
		_fH1 = _fH + 2 * _Mar;

		double _fOff = (_fW1 - _fW) / 2;

		m_Info.fX = (0 - x1 + _fOff + _Mar) / m_Info.fScaleX;
		m_Info.fY = (0 - y1 + _Mar) / m_Info.fScaleY;
	} else {
		int _Mar = _fW / 40;

		m_Info.fScaleX = (_fW + 2 * _Mar) / m_Info.fWidth;
		m_Info.fScaleY = m_Info.fScaleX;

		_fW1 = _fW + 2 * _Mar;
		_fH1 = m_Info.fHeight * m_Info.fScaleY;

		double _fOff = (_fH1 - _fH) / 2;

		m_Info.fX = (0 - x1 + _Mar) / m_Info.fScaleX;
		m_Info.fY = (0 - y1 + _fOff + _Mar) / m_Info.fScaleY;
	}
}
NCC_CMD* DopplerPart::GetNccCmd(char* str_)
{
	char* _strCmd = str_;

	if(strcmp(_strCmd, "#DOPPLER NCC FILE\n") == 0) {
		g_nSReadtatus = NCC_CMD_START;
		return NULL;
	}

	if(strcmp(_strCmd, "#end\n") == 0) {
		g_nSReadtatus = NCC_CMD_END;
		return NULL;
	}

	if(g_nSReadtatus == NCC_CMD_START) {
		NCC_CMD* _pCmd = new NCC_CMD;
		InitNccCmd(_pCmd);

		char c[] = " ";
		char *_str = strtok(_strCmd,c);

		_pCmd->eCmd = (NCC_CMD_TYPE)GetNccCmdIndex(_str);
		for(int i = 0; i < 4; i++)
		{
			_str = strtok(NULL,c);
			if(!_str)
				break;
			_pCmd->data[i] = atof(_str);

		}
		return _pCmd;
	}
	return NULL;
}

int DopplerPart::GetNccCmdList(QList<NCC_CMD*>* listCmd_)
{
	if(m_pPart == NULL)
		return -1;

	QFile file(m_pPart->strPartFile);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return -1;
	}

	NCC_CMD*   _pCmd;
	QByteArray _line;
	QString    _str;

	listCmd_->clear();
	g_nSReadtatus = 0;
	while(!file.atEnd()) {
		_line = file.readLine();
		_str  = QString(_line);

		_pCmd = GetNccCmd((char*)qPrintable(_str));
		if(_pCmd) {
			listCmd_->append(_pCmd);
		}
	}
	file.close();
	return 0;
}

void DopplerPart::DrawOriginLine(QPainter& painter)
{
	QPointF _pt1 = QPointF(m_Info.fX, 0);
	QPointF _pt2 = QPointF(m_Info.fX, m_Info.fHeight);
	painter.drawLine(_pt1, _pt2);

	_pt1 = QPointF(0, m_Info.fY);
	_pt2 = QPointF(m_Info.fWidth, m_Info.fY);
	painter.drawLine(_pt1, _pt2);
}

void DopplerPart::DrawNccPart(QPainter& painter)
{
	//int _nRet = GetNccCmdList(m_listCmd);
	//if(_nRet < 0) return;
	NCC_CMD*  _pCmd;
	for(int i = 0 ; i < m_listCmd->count(); i++)
	{
		_pCmd = m_listCmd->at(i);

		switch(_pCmd->eCmd)
		{
		case NCC_CMD_NULL:
			break;
		case NCC_CMD_SCALE:
			break;
		case NCC_CMD_MOVE_TO:
			CmdMoveTo(_pCmd);
			break;
		case NCC_CMD_LINE_TO:
			CmdLineTo(painter, _pCmd);
			break;
		case NCC_CMD_CURVE_TO:
			CmdCurveTo(painter, _pCmd);
			break;
		case NCC_CMD_ARC_POSITIVE:
			CmdArcPositive(painter, _pCmd);
			break;
		case NCC_CMD_ARC_NEGATIVE:
			CmdArcNegative(painter, _pCmd);
			break;
		case NCC_CMD_LINE_WIDTH:
			break;
		case NCC_CMD_LINE_MODE:
			break;
		case NCC_CMD_COLOR_CHANGE:
			break;
		default:
			break;
		}
	}
}

void DopplerPart::CmdMoveTo(NCC_CMD* pCmd_)
{
	m_ptCur.setX(pCmd_->data[0]);
	m_ptCur.setY(pCmd_->data[1]);
}

void DopplerPart::CmdLineTo(QPainter& painter, NCC_CMD* pCmd_)
{
	QPointF _point1 = CoordinateTrans(m_ptCur.x(), m_ptCur.y());
	QPointF _point2 = CoordinateTrans(pCmd_->data[0], pCmd_->data[1]);

	painter.drawLine(_point1, _point2);
	m_ptCur.setX(pCmd_->data[0]);
	m_ptCur.setY(pCmd_->data[1]);
}

void DopplerPart::CmdCurveTo(QPainter& painter, NCC_CMD* pCmd_)
{
	QPointF _pt1 = m_ptCur;
	QPointF _pt2(pCmd_->data[0], pCmd_->data[1]);
	QPointF _pt3(pCmd_->data[2], pCmd_->data[3]);

	DrawCurveTo(painter, _pt1, _pt2, _pt3);
	//m_ptCur = _pt3;
}

void DopplerPart::CmdArcPositive(QPainter& painter, NCC_CMD* pCmd_)
{
	int _nMode  = 1;
	double _fTmp = pCmd_->data[1];

	if(fabs(_fTmp - 1) < 0.5)		_nMode = 1;
	else if(fabs(_fTmp - 2) < 0.5)	_nMode = 2;
	else if(fabs(_fTmp - 3) < 0.5)	_nMode = 3;
	else if(fabs(_fTmp - 4) < 0.5)	_nMode = 4;

	_fTmp = pCmd_->data[0]; //* sin(80 * PI / 180) ;

	double x0 = m_ptCur.x();
	double y0 = m_ptCur.x();
	double x1 , y1 ;
	double x2 , y2 ;

	switch(_nMode)
	{
	case 1:
		x1  = _fTmp + x0 - pCmd_->data[0]  ;
		y1  = _fTmp + y0  ;
		x2 = x0 - pCmd_->data[0]  ;
		y2 = pCmd_->data[0] + y0  ;
		break;
	case 2:
		x1  = _fTmp + x0 - pCmd_->data[0]  ;
		y1  = _fTmp + y0  ;
		x2 = x0 - pCmd_->data[0]  ;
		y2 = pCmd_->data[0] + y0  ;
		break;
	case 3:
		x1  = pCmd_->data[0] -_fTmp + x0 ;
		y1  = -_fTmp + y0  ;
		x2 = x0 + pCmd_->data[0]  ;
		y2 = -pCmd_->data[0] + y0  ;
		break;
	case 4:
		x1  = x0  + _fTmp ;
		y1  = -_fTmp + y0 + pCmd_->data[0];
		x2 = x0 + pCmd_->data[0]  ;
		y2 = y0 + pCmd_->data[0] ;
		break;
	default:
		break;
	}

	QPointF _pt1 = m_ptCur;
	QPointF _pt2(x1, y1);
	QPointF _pt3(x2, y2);

	DrawCurveTo(painter, _pt1, _pt2, _pt3);
	//m_ptCur = _pt3;
}

void DopplerPart::CmdArcNegative(QPainter& painter, NCC_CMD* pCmd_)
{
	int _nMode  = 1;
	double _fTmp = pCmd_->data[1];

	if(fabs(_fTmp - 1) < 0.5)		_nMode = 1;
	else if(fabs(_fTmp - 2) < 0.5)	_nMode = 2;
	else if(fabs(_fTmp - 3) < 0.5)	_nMode = 3;
	else if(fabs(_fTmp - 4) < 0.5)	_nMode = 4;

	_fTmp = pCmd_->data[0]; //* sin(80 * PI / 180) ;

	double x0 = m_ptCur.x();
	double y0 = m_ptCur.x();
	double x1 , y1 ;
	double x2 , y2 ;

	switch(_nMode)
	{
	case 1:
		x1 = _fTmp + x0 - pCmd_->data[0];
		y1 = -_fTmp + y0;
		x2 = x0 - pCmd_->data[0];
		y2 = -pCmd_->data[0] + y0;
		break;
	case 2:
		x1 = x0 - _fTmp;
		y1 = -_fTmp + y0 + pCmd_->data[0];
		x2 = x0 - pCmd_->data[0];
		y2 = y0 + pCmd_->data[0];
		break;
	case 3:
		x1 = -_fTmp + x0 + pCmd_->data[0];
		y1 = _fTmp + y0;
		x2 = x0 + pCmd_->data[0];
		y2 = pCmd_->data[0] + y0;
		break;
	case 4:
		x1 = x0 + _fTmp ;
		y1 = -_fTmp + y0 + pCmd_->data[0];
		x2 = x0 + pCmd_->data[0];
		y2 = y0 - pCmd_->data[0];
		break;
	default:
		break;
	}

	QPointF _pt1 = m_ptCur;
	QPointF _pt2(x1, y1);
	QPointF _pt3(x2, y2);

	DrawCurveTo(painter, _pt1, _pt2, _pt3);
	//m_ptCur = _pt3;
}

void DopplerPart::DrawCurveTo(QPainter& painter, QPointF pt1_, QPointF pt2_, QPointF pt3_)
{
	QPointF _pt1 = CoordinateTrans(pt1_.x(), pt1_.y());
	QPointF _pt2 = CoordinateTrans(pt2_.x(), pt2_.y());
	QPointF _pt3 = CoordinateTrans(pt3_.x(), pt3_.y());

	double x[3], y[3];

	x[0] = _pt1.x();
	y[0] = _pt1.y();

	x[1] = _pt2.x();
	y[1] = _pt2.y();

	x[2] = _pt3.x();
	y[2] = _pt3.y();

	double L0 = GetPositionLength(x[0], y[0], x[2], y[2]);
	double L1 = GetPositionLength(x[0], y[0], x[1], y[1]);
	double L2 = GetPositionLength(x[1], y[1], x[2], y[2]);

	double fA = 0;
	double fL = 90;
	//double xPrec = 1 / m_Info.fScaleX;
	//double yPrec = 1 / m_Info.fScaleY;
	QRectF rect;

	double left   = GYMIN(x[0], x[2]);
	double right  = GYMAX(x[0], x[2]);
	double top    = GYMIN(y[0], y[2]);
	double bottom = GYMAX(y[0], y[2]);

	double fW  = right - left;
	double fH  = bottom - top;

	int nRelation = GetPositionRelationForLine(x[0], y[0], x[2], y[2], x[1], y[1]);
	int mode = 0;
	int status = 0;
	if(x[0] == left && y[0] == top)	{
		if(nRelation > 0) {
			rect = QRectF(x[0], y[0] - fH, 2*fW, 2*fH);			fA = 180;
			mode = 0;
		} else {
			rect = QRectF(x[0] - fW, y[0], 2*fW, 2*fH);			fA = 0;
			mode = 1;
		}
	} else if(x[0] == left && y[0] == bottom) {
		if(nRelation > 0) {
			rect = QRectF(x[0] - fW, y[0] - 2*fH, 2*fW, 2*fH);	fA = 270;
			mode = 2;
		} else {
			rect = QRectF(x[0], y[0] - fH, 2*fW, 2*fH);			fA = 90;
			mode = 3;
		}
	} else if(x[0] == right && y[0] == bottom) {
		if(nRelation > 0) {
			rect = QRectF(x[0] - fW, y[0] - 2*fH, 2*fW, 2*fH);	fA = 180;
			mode = 4;
		} else {
			mode = 5;
			rect = QRectF(x[0] - 2*fW, y[0] - fH, 2*fW, 2*fH);	fA = 0;
			if(L0 - 10*L1 > 0 ||  L0 - 10*L2 > 0) {
				status = -1;
			}
		}
	} else if(x[0] == right && y[0] == top) {
		if(nRelation > 0) {
			rect = QRectF(x[0] - 2*fW, y[0] - fH, 2*fW, 2*fH);	fA = 270;
			mode = 6;
		} else {
			rect = QRectF(x[0] - fW, y[0], 2*fW, 2*fH);			fA = 90;
			mode = 7;
		}
	}
	fA *= 16;
	fL *= 16;

	if(status < 0) {
		painter.drawLine(_pt1, _pt3);
	} else {
		painter.drawArc(rect, fA, fL);
	}
	m_ptCur = pt3_;
}
//***************************************************************************************************************
//***************************************************************************************************************
//***************************************************************************************************************
void DopplerPart::DrawNccPart(QPainterPath& path)
{
	//int _nRet = GetNccCmdList(m_listCmd);
	//if(_nRet < 0) return;
	NCC_CMD*  _pCmd;
	for(int i = 0 ; i < m_listCmd->count(); i++)
	{
		_pCmd = m_listCmd->at(i);

		switch(_pCmd->eCmd)
		{
		case NCC_CMD_NULL:
			break;
		case NCC_CMD_SCALE:
			break;
		case NCC_CMD_MOVE_TO:
			CmdMoveTo(path, _pCmd);
			break;
		case NCC_CMD_LINE_TO:
			CmdLineTo(path, _pCmd);
			break;
		case NCC_CMD_CURVE_TO:
			CmdCurveTo(path, _pCmd);
			break;
		case NCC_CMD_ARC_POSITIVE:
			CmdArcPositive(path, _pCmd);
			break;
		case NCC_CMD_ARC_NEGATIVE:
			CmdArcNegative(path, _pCmd);
			break;
		case NCC_CMD_LINE_WIDTH:
			break;
		case NCC_CMD_LINE_MODE:
			break;
		case NCC_CMD_COLOR_CHANGE:
			break;
		default:
			break;
		}
	}
}

void DopplerPart::CmdMoveTo(QPainterPath& path, NCC_CMD* pCmd_)
{
	QPointF _point = CoordinateTrans(pCmd_->data[0], pCmd_->data[1]);

	path.moveTo(_point);

	m_ptCur.setX(pCmd_->data[0]);
	m_ptCur.setY(pCmd_->data[1]);
}

void DopplerPart::CmdLineTo(QPainterPath& path, NCC_CMD* pCmd_)
{
	QPointF _point = CoordinateTrans(pCmd_->data[0], pCmd_->data[1]);

	path.lineTo(_point);

	m_ptCur.setX(pCmd_->data[0]);
	m_ptCur.setY(pCmd_->data[1]);
}

void DopplerPart::CmdCurveTo(QPainterPath& path, NCC_CMD* pCmd_)
{
	QPointF _pt1 = m_ptCur;
	QPointF _pt2(pCmd_->data[0], pCmd_->data[1]);
	QPointF _pt3(pCmd_->data[2], pCmd_->data[3]);

	DrawCurveTo(path, _pt1, _pt2, _pt3);
}

void DopplerPart::CmdArcPositive(QPainterPath& path, NCC_CMD* pCmd_)
{
	int _nMode  = 1;
	double _fTmp = pCmd_->data[1];

	if(fabs(_fTmp - 1) < 0.5)		_nMode = 1;
	else if(fabs(_fTmp - 2) < 0.5)	_nMode = 2;
	else if(fabs(_fTmp - 3) < 0.5)	_nMode = 3;
	else if(fabs(_fTmp - 4) < 0.5)	_nMode = 4;

	_fTmp = pCmd_->data[0]; //* sin(80 * PI / 180) ;

	double x0 = m_ptCur.x();
	double y0 = m_ptCur.x();
	double x1 , y1 ;
	double x2 , y2 ;

	switch(_nMode)
	{
	case 1:
		x1  = _fTmp + x0 - pCmd_->data[0]  ;
		y1  = _fTmp + y0  ;
		x2 = x0 - pCmd_->data[0]  ;
		y2 = pCmd_->data[0] + y0  ;
		break;
	case 2:
		x1  = _fTmp + x0 - pCmd_->data[0]  ;
		y1  = _fTmp + y0  ;
		x2 = x0 - pCmd_->data[0]  ;
		y2 = pCmd_->data[0] + y0  ;
		break;
	case 3:
		x1  = pCmd_->data[0] -_fTmp + x0 ;
		y1  = -_fTmp + y0  ;
		x2 = x0 + pCmd_->data[0]  ;
		y2 = -pCmd_->data[0] + y0  ;
		break;
	case 4:
		x1  = x0  + _fTmp ;
		y1  = -_fTmp + y0 + pCmd_->data[0];
		x2 = x0 + pCmd_->data[0]  ;
		y2 = y0 + pCmd_->data[0] ;
		break;
	default:
		break;
	}

	QPointF _pt1 = m_ptCur;
	QPointF _pt2(x1, y1);
	QPointF _pt3(x2, y2);

	DrawCurveTo(path, _pt1, _pt2, _pt3);
}

void DopplerPart::CmdArcNegative(QPainterPath& path, NCC_CMD* pCmd_)
{
	int _nMode  = 1;
	double _fTmp = pCmd_->data[1];

	if(fabs(_fTmp - 1) < 0.5)		_nMode = 1;
	else if(fabs(_fTmp - 2) < 0.5)	_nMode = 2;
	else if(fabs(_fTmp - 3) < 0.5)	_nMode = 3;
	else if(fabs(_fTmp - 4) < 0.5)	_nMode = 4;

	_fTmp = pCmd_->data[0]; //* sin(80 * PI / 180) ;

	double x0 = m_ptCur.x();
	double y0 = m_ptCur.x();
	double x1 , y1 ;
	double x2 , y2 ;

	switch(_nMode)
	{
	case 1:
		x1 = _fTmp + x0 - pCmd_->data[0];
		y1 = -_fTmp + y0;
		x2 = x0 - pCmd_->data[0];
		y2 = -pCmd_->data[0] + y0;
		break;
	case 2:
		x1 = x0 - _fTmp;
		y1 = -_fTmp + y0 + pCmd_->data[0];
		x2 = x0 - pCmd_->data[0];
		y2 = y0 + pCmd_->data[0];
		break;
	case 3:
		x1 = -_fTmp + x0 + pCmd_->data[0];
		y1 = _fTmp + y0;
		x2 = x0 + pCmd_->data[0];
		y2 = pCmd_->data[0] + y0;
		break;
	case 4:
		x1 = x0 + _fTmp ;
		y1 = -_fTmp + y0 + pCmd_->data[0];
		x2 = x0 + pCmd_->data[0];
		y2 = y0 - pCmd_->data[0];
		break;
	default:
		break;
	}

	QPointF _pt1 = m_ptCur;
	QPointF _pt2(x1, y1);
	QPointF _pt3(x2, y2);

	DrawCurveTo(path, _pt1, _pt2, _pt3);
}

void DopplerPart::DrawCurveTo(QPainterPath& path, QPointF pt1_, QPointF pt2_, QPointF pt3_)
{
	QPointF _pt1 = CoordinateTrans(pt1_.x(), pt1_.y());
	QPointF _pt2 = CoordinateTrans(pt2_.x(), pt2_.y());
	QPointF _pt3 = CoordinateTrans(pt3_.x(), pt3_.y());

	double x[3], y[3];

	x[0] = _pt1.x();
	y[0] = _pt1.y();

	x[1] = _pt2.x();
	y[1] = _pt2.y();

	x[2] = _pt3.x();
	y[2] = _pt3.y();

	double L0 = GetPositionLength(x[0], y[0], x[2], y[2]);
	double L1 = GetPositionLength(x[0], y[0], x[1], y[1]);
	double L2 = GetPositionLength(x[1], y[1], x[2], y[2]);

	double fA = 0;
	double fL = 90;
	//double xPrec = 1 / m_Info.fScaleX;
	//double yPrec = 1 / m_Info.fScaleY;
	QRectF rect;

	double left   = GYMIN(x[0], x[2]);
	double right  = GYMAX(x[0], x[2]);
	double top    = GYMIN(y[0], y[2]);
	double bottom = GYMAX(y[0], y[2]);

	double fW  = right - left;
	double fH  = bottom - top;

	int nRelation = GetPositionRelationForLine(x[0], y[0], x[2], y[2], x[1], y[1]);
	int mode = 0;
	int status = 0;
	if(x[0] == left && y[0] == top)	{
		if(nRelation > 0) {
			rect = QRectF(x[0], y[0] - fH, 2*fW, 2*fH);			fA = 180;
			mode = 0;
		} else {
			rect = QRectF(x[0] - fW, y[0], 2*fW, 2*fH);			fA = 0;
			mode = 1;
		}
	} else if(x[0] == left && y[0] == bottom) {
		if(nRelation > 0) {
			rect = QRectF(x[0] - fW, y[0] - 2*fH, 2*fW, 2*fH);	fA = 270;
			mode = 2;
		} else {
			rect = QRectF(x[0], y[0] - fH, 2*fW, 2*fH);			fA = 90;
			mode = 3;
		}
	} else if(x[0] == right && y[0] == bottom) {
		if(nRelation > 0) {
			rect = QRectF(x[0] - fW, y[0] - 2*fH, 2*fW, 2*fH);	fA = 180;
			mode = 4;
		} else {
			mode = 5;
			rect = QRectF(x[0] - 2*fW, y[0] - fH, 2*fW, 2*fH);	fA = 0;
			if(L0 - 10*L1 > 0 ||  L0 - 10*L2 > 0) {
				status = -1;
			}
		}
	} else if(x[0] == right && y[0] == top) {
		if(nRelation > 0) {
			rect = QRectF(x[0] - 2*fW, y[0] - fH, 2*fW, 2*fH);	fA = 270;
			mode = 6;
		} else {
			rect = QRectF(x[0] - fW, y[0], 2*fW, 2*fH);			fA = 90;
			mode = 7;
		}
	}

	if(status < 0) {
		path.moveTo(_pt1);
		path.lineTo(_pt3);
	} else {
		path.arcMoveTo(rect, fA);
		path.arcTo(rect, fA, fL);
	}

	path.moveTo(_pt3);
	m_ptCur = pt3_;
}

QPointF DopplerPart::CoordinateTrans(float x_, float y_)
{
	float _fScaleX = m_Info.fScaleX;
	float _fScaleY = m_Info.fScaleY;
	float     _fX0 = m_Info.fX;
	float     _fY0 = m_Info.fY;

	float _fX = x_ / _fScaleX + _fX0;
	float _fY = y_ / _fScaleY + _fY0;

	QPointF _point;
	_point.setX(_fX);
	_point.setY(_fY);

	return _point;
}


