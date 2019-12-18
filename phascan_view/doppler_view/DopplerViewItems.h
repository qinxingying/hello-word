#ifndef DOPPLERVIEWITEMS_H
#define DOPPLERVIEWITEMS_H

#include <QObject>
#include <QPainterPath>
#include <configure/Instrument.h>
#include "DopplerDataView.h"
#include "DopplerGraphicsItem.h"
#include "DopplerLineItem.h"
#include "dopplercscanlinemark.h"
#include "DopplerGateItem.h"
#include "DopplerLawMarker.h"
#include "DopplerParabolaItem.h"
#include "DopplerDefectItem.h"

enum OVERLAYS
{
    OVERLAYS_NONE              = 0x0000,
    OVERLAYS_DEFECT            = 0x0001,
    OVERLAYS_LW_BW             = 0x0002,
    OVERLAYS_GATE              = 0x0004,
    OVERLAYS_LAW_MARKER        = 0x0008,
    OVERLAYS_CURSOR            = 0x0010,
    OVERLAYS_THICKNESS         = 0x0020,
    OVERLAYS_WELD              = 0x0040,
    OVERLAYS_SCAN_MARKER       = 0x0080,
    OVERLAYS_PARABOLA          = 0x0100,
    OVERLAYS_LAW_MARKER_C_SCAN = 0x0200,
    OVERLAYS_TOPC_WIDTH        = 0x0400,
    OVERLAYS_C_WELD_BORDER     = 0x0800,
    OVERLAYS_ALL               = 0xFFFF
} ;



class DopplerViewItems : public QObject
{
	Q_OBJECT
public:
	explicit DopplerViewItems(QObject *parent = 0);
	~DopplerViewItems();

	void EnableItems(OVERLAYS eItems_) ;
	OVERLAYS GetItemsEnable() const ;
	void UpdateItems();
	void UpdateItemsGate();
	void UpdateItemsDefect();
    void SetItemDefect(int id);
	void UpdateItemsLwBw();
	void UpdateItemsCursor() ;
	void UpdateItemsLawMarker() ;
    void UpdateItemsLawMarkerCScan() ;
    int GetLawMarkerQty();
    int GetLawMarkerLinesCount();
    int GetLawMarkerPos(int nId_);
    void SetLawMarkerPos(int nId_, int nMarkerPos);
    //void SetLawMarkerCScanPos(int nMarkerPos);
	void UpdateItemsThickness() ;
    void UpdateItemsWeldBorder();
    void UpdateItemsTOPCWidth();
	void UpdateItemsWeld() ;
	void UpdateScanMarker();

	void SetThicknessInterval(float fInterval_);
	void SetGateDrawMode(GATE_DRAW_MODE eMode_);

    void SetParabolaScale(float scaleH, float scaleV);
	void SetLwBwPos(float fLw_ , float fBw_);
	void SetLwBwId(int iLwId_ , int iBwId_);
	void SetDefect(int index_ , QRectF rect_);
	void SetDefectIndex(int index_);
	void ClearDefect();
	void SetGatePos(int eGate_ , float fStart_ , float fWidth_ , float fHeight_);
	void SetCursorPos(int eCursor_ , float fPos_) ;
	void SetCursorId(int eCurosr_ , int nId_);

	void SetupMarkersVector(QVector<QLineF>* pLines_) ;
	void SetupLawMarkerString(QVector<QString>* pMarkers_);
	void SetMarkerColor(int nId_ , QColor* pColor_) ;
	void EnableMarkerQty(unsigned int nQty_);

	void SetThicknessDirection(bool bHorizental_);
    void SetWeldBorderDirection(bool direction);
	void SetScanMarkerDirectionHorizental(bool bHorizental_);
	void SetScanMarkerPos(float fInterval_);
	void SetPartInfo(PART_CONFIG* pPart_) ;
	void SetParabolaDirection(bool bVertical_) ;
    void ResetDefect();

protected:
	void GateMove(int eGate_ , float fStart_ , float fWidth_ , float fHeight_);
	void CursorMove(int eCursor , float fPos_) ;

	void  DrawWeld(QPainterPath& path)   ;
	void  DrawWeldI (QPainterPath& path) ;    
	void  DrawWeldV (QPainterPath& path) ;
	void  DrawWeldDV(QPainterPath& path) ;
	void  DrawWeldU (QPainterPath& path) ;
    void  DrawWeldDiffDV(QPainterPath& path);
    void  DrawWeldJ(QPainterPath& path);
    void  DrawWeldVY(QPainterPath& path);
    void  DrawWeldTKY(QPainterPath& path);
//	void  DrawWeldNcc (QPainterPath& path);
    void  DrawWeldDxf(QPainterPath &path);
    void  DrawWeldNoneDataII(QPainterPath& path);
    void  DrawWeldIDataII(QPainterPath& path);
    void  DrawWeldVDataII(QPainterPath& path);
    void  DrawWeldUDataII(QPainterPath& path);
    void  DrawWeldVYDataII(QPainterPath& path);
    void  DrawWeldVVDataII(QPainterPath& path);
    void  DrawWeldUUDataII(QPainterPath& path);
    void  DrawWeldUVDataII(QPainterPath& path);

	DopplerDataView*     m_pDataView  ;
	DopplerDefectItem*   m_pDefect[DEFECT_SIGN_MAX];
	DopplerCalibrationMark*  m_pItemLw    ;
	DopplerCalibrationMark*  m_pItemBw    ;
	DopplerGateItem*     m_pGate[3]   ;
	DopplerLineItem*     m_pCursor[4] ;
	DopplerLawMarker*    m_pLawMarker ;
    DopplerCScanLineMark*    m_pLawMarkerCScan ;
	DopplerLineItem*     m_pThickness[10]  ;
    DopplerLineItem*     m_pTOPCWidth[2];
    DopplerLineItem*     m_pWeldBorder[3];
	DopplerScanMarker*   m_pScanMarker  ;
	DopplerParabolaItem* m_pParabola[2]    ;

	float m_fLW;
	float m_fBW;
	int   m_iLwId;
	int   m_iBwId;
	QRectF m_rcDefect[DEFECT_SIGN_MAX];
	int    m_iDefectId[DEFECT_SIGN_MAX];
	int    m_iDefectIndex;
	float afGatePos[3][3]  ;
    float afCursorPos[5]   ;
    int   anCursorId[5]    ;
	bool  m_bHorizental ;
    bool  m_cWeldBorderHorizental;
	bool  m_bScanMarkerHorizental ;
	float m_fScanPos   ;
	float m_fInterval  ;
	int   m_nLawQty    ;
	bool  m_bParabolaVertical ;

	GATE_DRAW_MODE m_eGateMode ;
	QVector<QLineF> markers    ;
	QVector<QString> strMarker ;
	PART_CONFIG m_cPart;

	OVERLAYS m_eShow ;

signals:

public slots:

};

#endif // DOPPLERVIEWITEMS_H
