#ifndef ___DOPPLERDRAWASCANH_H____
#define ___DOPPLERDRAWASCANH_H____
#include "DopplerDrawScan.h"
#include <QColor>
#include <QLineF>
#include <QImage>
#include <QPolygonF>
#include "configure/const.h"

#define A_SCAN_LIMIT_BUFF_SIZE		8192
#define CURVES_CNT					5

struct A_SCAN_DRAW_INFO
{
	int	  nPointQty ;
	float fDRangeS;
} ;

class DopplerDrawAScanH : public DopplerDrawScan
{
	Q_OBJECT
public:

	enum A_SCAN_LINE_TYPE
	{
		A_SCAN_MAIN = 0   ,
		A_SCAN_DRAW_LIMIT ,
		A_SCAN_DRAW_FILL ,
		A_SCAN_LINE_TYPE_MAX
	}  ;

	DopplerDrawAScanH();
	void UpdateDrawInfo();
	unsigned int GetDataBeginOffset() ;
	virtual void Draw (QImage* pImage_);

	void SetColor(QColor* pColor_ , A_SCAN_LINE_TYPE eLineType_  =  A_SCAN_MAIN);
	void EndAbleLineDrawing(A_SCAN_LINE_TYPE eLineType_ , bool enalbe_ = true) ;
	WDATA* GetLimitValueHigh() ;
	WDATA* GetLimitValueLow()  ;
protected:
	A_SCAN_DRAW_INFO m_AScanInfo ;
	QPolygonF Lines ;
	QPolygonF LimitHigh ;
	QPolygonF LimitLow  ;
	QColor	color[A_SCAN_LINE_TYPE_MAX] ;
	bool	bDrawLimit ;
	int		m_nHeight ;
	int		m_nWidth ;

	WDATA aLimitHigh[A_SCAN_LIMIT_BUFF_SIZE] ;
	WDATA aLimitLow [A_SCAN_LIMIT_BUFF_SIZE] ;

	QPolygonF m_linCurves[CURVES_CNT];
	QPointF   m_ptPos[CURVES_CNT][18];
	int       m_iPtCnt[CURVES_CNT];

	QVector<qreal> m_dashes;

    void DrawDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode);
    void DrawLinearDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode);
    void DrawTcgCurve(QPainter *painter, int nWidth_, int nHeight_,int mode,int flag);
    virtual void DrawCoupleCurve(QImage* pImage_);
	void DrawPointRectangle(QPainter *painter_, float x_, float y_, QColor color_);
	void ClearAll(QPainter *painter_);
signals:

public slots:

};


class DopplerDrawAScanV : public DopplerDrawAScanH
{
	Q_OBJECT
public:
	DopplerDrawAScanV();
	virtual void Draw (QImage* pImage_);

protected:
    void DrawDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode);
    void DrawLinearDacCurve(QPainter *painter, int nWidth_, int nHeight_,int mode);
    void DrawTcgCurve(QPainter *painter, int nWidth_, int nHeight_,int mode,int flag);
    virtual void DrawCoupleCurve(QImage* pImage_);
signals:

public slots:
};

#endif // ___DOPPLERDRAWASCANH_H____
