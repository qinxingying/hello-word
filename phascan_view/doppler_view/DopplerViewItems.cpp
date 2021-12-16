#include "DopplerViewItems.h"
//#include "painter/DopplerPart.h"
#include "painter/DrawDxf.h"
#include <QDebug>
#include <QColor>
#include <gHeader.h>
#include <process/ParameterProcess.h>
#include "../ui/ProcessDisplay.h"
#include<vector>
int bHideCursor = 0;
int HideMode = -1;
static const QColor COLOR_GATE_A  =  QColor(255 , 0 , 0)   ;
static const QColor COLOR_GATE_B  =  QColor(0 , 255 , 0)   ;
static const QColor COLOR_GATE_I  =  QColor(255 , 255 , 0) ;

static const QColor COLOR_DEFECT  =  QColor(0 , 125 , 0) ;
static const QColor COLOR_LW  =  QColor(0 , 0 , 255) ;
static const QColor COLOR_BW  =  QColor(0 , 0 , 255) ;

static const QColor COLOR_LAW_MARKER1  = QColor( 200 , 200 , 0	) ;
static const QColor COLOR_LAW_MARKER2  = QColor( 0   , 200 , 200  ) ;
static const QColor COLOR_LAW_MARKER3  = QColor( 200 , 200 , 200  ) ;

static const QColor COLOR_CURSOR_AREF  = QColor(255 , 0 , 0) ;
static const QColor COLOR_CURSOR_AMES  = QColor(0 , 255 , 0) ;
static const QColor COLOR_CURSOR_UREF  = QColor(255 , 0 , 0) ;
static const QColor COLOR_CURSOR_UMES  = QColor(0 , 255 , 0) ;
static const QColor COLOR_CURSOR_SREF  = QColor(255 , 0 , 0) ;
static const QColor COLOR_CURSOR_SMES  = QColor(0 , 255 , 0) ;
static const QColor COLOR_CURSOR_IREF  = QColor(255 , 0 , 0) ;
static const QColor COLOR_CURSOR_IMES  = QColor(255 , 0 , 0) ;

static const QColor COLOR_WELD		 = QColor(180 , 180 , 180) ;
static const QColor COLOR_THICKNESS	= QColor(128 , 128 , 128) ;
static const QColor COLOR_SCAN_MARKER  = QColor(0 , 0 , 0  ) ;

static const QColor COLOR_CAL  =  QColor(255 , 0, 0)   ;

DopplerViewItems::DopplerViewItems(QObject *parent) :
	QObject(parent)
{
	m_eShow  = OVERLAYS_NONE ;
	m_pDataView = (DopplerDataView*)parent  ;

	for(int i = 0; i < DEFECT_SIGN_MAX; i++)
	{
		m_pDefect[i] = NULL;
	}
	ClearDefect();
	m_fLW = 10;
	m_fBW = 10;
	m_iLwId = 0;
	m_iBwId = 1;
    m_iCalibrationbId = 0;

	m_pItemLw = NULL;
	m_pItemBw = NULL;
    m_pItemCaiblration = NULL;
	//---------------------------------------
    memset((void*)m_pGate, 0, 3 * sizeof(void *)) ;
    memset((void*)m_pCursor, 0, 4 * sizeof(void *)) ;
    memset((void*)m_pThickness, 0, 10 * sizeof(void *)) ;
    memset((void*)m_pTOPCWidth, 0, 2 * sizeof(void *));
    memset((void*)m_pWeldBorder, 0, 3 * sizeof(void *));
	//m_pWeld		= 0;
	m_pLawMarker	= 0;
    m_pLawMarkerCScan = 0;
	m_pScanMarker	= 0;
	m_pParabola[0]	= m_pParabola[1]  = 0;

	m_eGateMode		= GATE_MODE_GATE_HORIZENTAL  ;
	m_bHorizental	= m_bScanMarkerHorizental = true;
	m_fInterval		= 20.0;
	m_fScanPos		=  0 ;
}

DopplerViewItems::~DopplerViewItems()
{
	int i ;

	for(int i = 0; i < DEFECT_SIGN_MAX; i++)
	{
		if(m_pDefect[i]) delete m_pDefect[i] ;
		m_pDefect[i] = NULL;
	}
	if(m_pItemLw) delete m_pItemLw ;
	if(m_pItemBw) delete m_pItemBw ;

	m_pItemLw = NULL;
	m_pItemBw = NULL;

    if(m_pItemCaiblration) delete m_pItemCaiblration ;
    m_pItemCaiblration = NULL;
	//---------------------------------------
	for(i = 0 ; i < 3 ; i++)
	{
		if(m_pGate[i]) delete m_pGate[i]  ;
		m_pGate[i] = NULL ;
	}
	for(i = 0 ; i < 4 ; i++)
	{
		if(m_pCursor[i]) delete m_pCursor[i]  ;
		m_pCursor[i] = NULL ;
	}
	for(i = 0 ; i < 10 ; i++)
	{
		if(m_pThickness[i]) delete m_pThickness[i]  ;
		m_pThickness[i] = NULL ;
	}
    for(i = 0; i < 3; i++){
        if(m_pWeldBorder[i]) delete m_pWeldBorder[i];
        m_pWeldBorder[i] = NULL;
    }
    for(i = 0; i < 2; i++){
        if(m_pTOPCWidth[i]) delete m_pTOPCWidth[i];
        m_pTOPCWidth[i] = NULL;
    }
	if(m_pLawMarker)  delete m_pLawMarker ;
    if(m_pLawMarkerCScan)  delete m_pLawMarkerCScan ;
	//if(m_pWeld)	   delete m_pWeld	  ;
	if(m_pParabola[0])   delete m_pParabola[0] ;
	if(m_pParabola[1])   delete m_pParabola[1] ;
	m_pLawMarker = NULL ;
    m_pLawMarkerCScan = NULL ;
	//m_pWeld	  = NULL ;
	m_pScanMarker= NULL ;
	m_pParabola[0] = m_pParabola[1]  = NULL ;
}


void DopplerViewItems::EnableItems(OVERLAYS eItems_)
{
   if(eItems_)
	   m_eShow = (OVERLAYS)(m_eShow | eItems_) ;
   else
	   m_eShow = OVERLAYS_NONE ;
}
OVERLAYS DopplerViewItems::GetItemsEnable() const
{   
	return m_eShow ;   
}


void DopplerViewItems::UpdateItems()
{
	UpdateItemsDefect();
	UpdateScanMarker();
	UpdateItemsLwBw();
	UpdateItemsGate();
	UpdateItemsCursor() ;
    UpdateItemsLawMarker() ;
    UpdateItemsLawMarkerCScan();
	UpdateItemsThickness() ;
    UpdateItemsWeldBorder();
    UpdateItemsTOPCWidth();
	UpdateItemsWeld() ;
    UpdateItemCalibration();
}

void DopplerViewItems::UpdateItemsDefect()
{
	if(!(m_eShow & OVERLAYS_DEFECT))
	{
		for(int i = 0; i < DEFECT_SIGN_MAX; i++)
		{
			if(m_pDefect[i])
			{
				m_pDefect[i]->hide() ;
			}
		}
		return ;
	}

	for(int i = 0; i < DEFECT_SIGN_MAX; i++)
	{
		if(!m_pDefect[i])
		{
			m_pDefect[i] =  new DopplerDefectItem(COLOR_DEFECT);
			m_pDefect[i]->SetItemType(DOPPLER_GRAPHICS_ITEM_DEFECT ) ;
			m_pDefect[i]->SetItemId(i);
			m_pDefect[i]->SetDataView(m_pDataView);
			m_pDataView->AddOverlayItems(m_pDefect[i]);
		}

		if(m_iDefectId[i] >= 0)
		{
			m_pDataView->SetItemGeometry(m_pDefect[i], m_rcDefect[i]);
			m_pDefect[i]->show() ;
		}
		else
		{
			m_pDefect[i]->hide() ;
		}
	}
}

void DopplerViewItems::SetItemDefect(int id)
{
    ResetDefect();
    if(m_iDefectId[id] >= 0)
    m_pDefect[id]->IsSelected = id;
}

void DopplerViewItems::UpdateItemsLwBw()
{
	if(!(m_eShow & OVERLAYS_LW_BW))
	{
		if(m_pItemLw)	m_pItemLw->hide() ;
		if(m_pItemBw)	m_pItemBw->hide() ;
		return ;
	}

	setup_DISPLAY_MODE _eDisplay = (setup_DISPLAY_MODE)m_pDataView->GetDataViewDrawType();
	DopplerLineItem::LINE_TYPE	  _nLineType = DopplerLineItem::LINE_FREE;
	DopplerLineItem::LINE_MOVE_TYPE _nMoveType = DopplerLineItem::LINE_MOVE_NO;

	if(_eDisplay == setup_DISPLAY_MODE_A_H || _eDisplay == setup_DISPLAY_MODE_B_H)
	{
		_nLineType = DopplerLineItem::LINE_VERTICAL;
//		_nMoveType = DopplerLineItem::LINE_MOVE_HORIZENTAL;
	} else if(_eDisplay == setup_DISPLAY_MODE_A_V || _eDisplay == setup_DISPLAY_MODE_B_V) {
		_nLineType = DopplerLineItem::LINE_HORIZENTAL;
//		_nMoveType = DopplerLineItem::LINE_MOVE_VERTICAL;
	} else {
		int _nShow = (int)m_eShow;
		_nShow &= ~OVERLAYS_LW_BW;
		m_eShow = (OVERLAYS)_nShow;
		if(m_pItemLw)	m_pItemLw->hide() ;
		if(m_pItemBw)	m_pItemBw->hide() ;
		return;
	}

	if(!m_pItemLw)
	{
		m_pItemLw = new DopplerCalibrationMark(COLOR_LW);
		m_pItemLw->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pItemLw->SetLineType(_nLineType);
		m_pItemLw->SetMoveType(_nMoveType);
        m_pItemLw->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pItemLw);
	}

	if(!m_pItemBw)
	{
		m_pItemBw = new DopplerCalibrationMark(COLOR_BW);
		m_pItemBw->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pItemBw->SetLineType(_nLineType);
		m_pItemBw->SetMoveType(_nMoveType);
        m_pItemBw->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pItemBw);
	}

	m_pItemLw->SetItemId(m_iLwId);
	m_pItemBw->SetItemId(m_iBwId);
//----------------------------
	QRectF _rcLW(0 , 0 , 0 , 0);
	QRectF _rcBW(0 , 0 , 0 , 0);
	if(_nLineType == DopplerLineItem::LINE_VERTICAL) {
		_rcLW.setLeft(m_fLW);
		_rcBW.setLeft(m_fBW);
	} else {
		_rcLW.setTop (m_fLW);
		_rcBW.setTop (m_fBW);
	}

	m_pDataView->SetItemGeometry(m_pItemLw, _rcLW );
	m_pDataView->SetItemGeometry(m_pItemBw, _rcBW );

	m_pItemLw->SetScenceSize(m_pDataView->GetViewSize());
	m_pItemBw->SetScenceSize(m_pDataView->GetViewSize());

	m_pItemLw->show() ;
    m_pItemBw->show() ;
}

void DopplerViewItems::UpdateItemCalibration()
{
    if(!(m_eShow & OVERLAYS_CALIBRATION))
    {
        if(m_pItemCaiblration)	m_pItemCaiblration->hide() ;
        return ;
    }

    setup_DISPLAY_MODE _eDisplay = (setup_DISPLAY_MODE)m_pDataView->GetDataViewDrawType();
    DopplerLineItem::LINE_TYPE	  _nLineType = DopplerLineItem::LINE_FREE;
    DopplerLineItem::LINE_MOVE_TYPE _nMoveType = DopplerLineItem::LINE_MOVE_NO;

    if(_eDisplay == setup_DISPLAY_MODE_A_H || _eDisplay == setup_DISPLAY_MODE_B_H)
    {
        _nLineType = DopplerLineItem::LINE_VERTICAL;
        _nMoveType = DopplerLineItem::LINE_MOVE_HORIZENTAL;
    } else if(_eDisplay == setup_DISPLAY_MODE_A_V || _eDisplay == setup_DISPLAY_MODE_B_V) {
        _nLineType = DopplerLineItem::LINE_HORIZENTAL;
        _nMoveType = DopplerLineItem::LINE_MOVE_VERTICAL;
    } else {
        int _nShow = (int)m_eShow;
        _nShow &= ~OVERLAYS_CALIBRATION;
        m_eShow = (OVERLAYS)_nShow;
        if(m_pItemCaiblration)	m_pItemCaiblration->hide() ;
        return;
    }

    if(!m_pItemCaiblration)
    {
        m_pItemCaiblration = new DopplerCalibrationItem(COLOR_CAL);
        m_pItemCaiblration->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
        m_pItemCaiblration->SetLineType(_nLineType);
        m_pItemCaiblration->SetMoveType(_nMoveType);
        m_pItemCaiblration->SetDataView(m_pDataView);
        m_pDataView->AddOverlayItems(m_pItemCaiblration);
    }

    m_pItemCaiblration->SetItemId(m_iCalibrationbId);
//----------------------------
    QRectF _rc(0 , 0 , 0 , 0);
    if(_nLineType == DopplerLineItem::LINE_VERTICAL) {
        _rc.setLeft(m_fCalibrationPos);
    } else {
        _rc.setTop (m_fCalibrationPos);
    }

    m_pDataView->SetItemGeometry(m_pItemCaiblration, _rc );

    m_pItemCaiblration->SetScenceSize(m_pDataView->GetViewSize());
    m_pItemCaiblration->show() ;
}

void DopplerViewItems::UpdateItemsGate()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int groupId = m_pDataView->GetGroupId();
    int GateA = _pConfig->group[groupId].bShowGateA;
    int GateB = _pConfig->group[groupId].bShowGateB;
    int GateI = _pConfig->group[groupId].bShowGateI;
    //extern int _Gate;
    //extern int _GateA,_GateB,_GateI;
	if(!(m_eShow & OVERLAYS_GATE))
	{
        if(m_pGate[0] && !GateA)  m_pGate[0]->hide() ;
        if(m_pGate[1] && !GateB)  m_pGate[1]->hide() ;
        if(m_pGate[2] && !GateI)  m_pGate[2]->hide() ;
		return ;
	}

    if(!m_pGate[0])
	{
		m_pGate[0] = new DopplerGateItem(COLOR_GATE_A) ;
		m_pDataView->AddOverlayItems(m_pGate[0]);
	}
    if(!m_pGate[1])
	{
		m_pGate[1] = new DopplerGateItem(COLOR_GATE_B) ;
		m_pDataView->AddOverlayItems(m_pGate[1]);
	}
    if(!m_pGate[2])
	{
		m_pGate[2] = new DopplerGateItem(COLOR_GATE_I) ;
		m_pDataView->AddOverlayItems(m_pGate[2]);
	}

    for(int i = 0 ; i < 3 ; i++)
    {
        if(i == 0 && !GateA)
            continue;
        else if(i == 1 && !GateB)
            continue;
        else if(i ==2 && !GateI)
            continue;
		m_pGate[i]->SetDrawMode(m_eGateMode);
		m_pGate[i]->SetItemType(DOPPLER_GRAPHICS_ITEM_GATE ) ;
		m_pGate[i]->SetItemId(i);
		GateMove(i , afGatePos[i][0] , afGatePos[i][1] , afGatePos[i][2]);
    }
    if ( GateA){
        m_pGate[0]->show();
    }else{
        m_pGate[0]->hide();
    }
    if( GateB){
        m_pGate[1]->show();
    }else{
        m_pGate[1]->hide();
    }
    if( GateI){
        m_pGate[2]->show();
    }else{
        m_pGate[2]->hide();
    }

}

void DopplerViewItems::UpdateItemsCursor()
{
	if(!(m_eShow & OVERLAYS_CURSOR))
	{
		if(m_pCursor[0])  m_pCursor[0]->hide() ;
		if(m_pCursor[1])  m_pCursor[1]->hide() ;
		if(m_pCursor[2])  m_pCursor[2]->hide() ;
		if(m_pCursor[3])  m_pCursor[3]->hide() ;
		if(m_pParabola[0])   m_pParabola[0]->hide()  ;
		if(m_pParabola[1])   m_pParabola[1]->hide()  ;
		return ;
	}

	if(!m_pCursor[0])
	{
		m_pCursor[0] = new DopplerLineItem(COLOR_CURSOR_AREF);
        m_pCursor[0]->SetWheelEnable();
		m_pCursor[0]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[0]->SetLineType(DopplerLineItem::LINE_HORIZENTAL);
		m_pCursor[0]->SetMoveType(DopplerLineItem::LINE_MOVE_VERTICAL);
		m_pCursor[0]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[0]);
	}
	if(!m_pCursor[1])
	{
		m_pCursor[1] = new DopplerLineItem(COLOR_CURSOR_AMES);
        m_pCursor[1]->SetWheelEnable();
		m_pCursor[1]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[1]->SetLineType(DopplerLineItem::LINE_HORIZENTAL);
		m_pCursor[1]->SetMoveType(DopplerLineItem::LINE_MOVE_VERTICAL);
		m_pCursor[1]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[1]);
	}
	if(!m_pCursor[2])
	{
		m_pCursor[2] = new DopplerLineItem(COLOR_CURSOR_UREF);
        m_pCursor[2]->SetWheelEnable();
		m_pCursor[2]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[2]->SetLineType(DopplerLineItem::LINE_VERTICAL);
		m_pCursor[2]->SetMoveType(DopplerLineItem::LINE_MOVE_HORIZENTAL);
		m_pCursor[2]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[2]);
	}
	if(!m_pCursor[3])
	{
        m_pCursor[3] =new DopplerLineItem(COLOR_CURSOR_UMES);
        m_pCursor[3]->SetWheelEnable();
		m_pCursor[3]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[3]->SetLineType(DopplerLineItem::LINE_VERTICAL);
		m_pCursor[3]->SetMoveType(DopplerLineItem::LINE_MOVE_HORIZENTAL);
		m_pCursor[3]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[3]);
	}

    bool tofdDepth = false;
    float pcs;
    m_pDataView->GetTofdDepth(tofdDepth, pcs, DopplerDataView::DATA_VIEW_RULER_LEFT);
    if(tofdDepth){
        m_pCursor[0]->SetTofdPCS(true, pcs);
        m_pCursor[1]->SetTofdPCS(true, pcs);
    } else {
        m_pCursor[0]->SetTofdPCS(false, 0);
        m_pCursor[1]->SetTofdPCS(false, 0);
    }

    m_pDataView->GetTofdDepth(tofdDepth, pcs, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    if(tofdDepth){
        m_pCursor[2]->SetTofdPCS(true, pcs);
        m_pCursor[3]->SetTofdPCS(true, pcs);
    } else {
        m_pCursor[2]->SetTofdPCS(false, 0);
        m_pCursor[3]->SetTofdPCS(false, 0);
    }

	m_pCursor[0]->SetWndRect(m_pDataView->GetZoomRect());
	m_pCursor[1]->SetWndRect(m_pDataView->GetZoomRect());
	m_pCursor[2]->SetWndRect(m_pDataView->GetZoomRect());
	m_pCursor[3]->SetWndRect(m_pDataView->GetZoomRect());

	m_pCursor[0]->SetItemId(anCursorId[0]);
	m_pCursor[1]->SetItemId(anCursorId[1]);
	m_pCursor[2]->SetItemId(anCursorId[2]);
    m_pCursor[3]->SetItemId(anCursorId[3]);

    CursorMove(0 , afCursorPos[0])  ;
    CursorMove(1 , afCursorPos[1])  ;
    CursorMove(2 , afCursorPos[2])  ;
    CursorMove(3 , afCursorPos[3])  ;

    m_pCursor[0]->SetScenceSize(m_pDataView->GetViewSize());
    m_pCursor[1]->SetScenceSize(m_pDataView->GetViewSize());
    m_pCursor[2]->SetScenceSize(m_pDataView->GetViewSize());
    m_pCursor[3]->SetScenceSize(m_pDataView->GetViewSize());
    m_pCursor[0]->show() ;
    m_pCursor[1]->show() ;
    m_pCursor[2]->show() ;
    m_pCursor[3]->show() ;


    if(m_eShow & OVERLAYS_PARABOLA)
	{
		if(!m_pParabola[0])
		{
			m_pParabola[0] = new DopplerParabolaItem () ;
			m_pDataView->AddOverlayItems(m_pParabola[0]);
			m_pParabola[0]->SetDataView(m_pDataView);
		}
		QPointF _pos1(afCursorPos[2] , afCursorPos[0]) ;
		QPointF _pos  = m_pDataView->TranslateToScenePlan(&_pos1);
		m_pParabola[0]->SetPoint(_pos1);

		m_pParabola[0]->setPos(_pos);
        m_pParabola[0]->show();


		if(!m_pParabola[1])
		{
			m_pParabola[1] = new DopplerParabolaItem () ;
			m_pDataView->AddOverlayItems(m_pParabola[1]);
			m_pParabola[1]->SetDataView(m_pDataView);
		}
		_pos1 = QPointF(afCursorPos[3] , afCursorPos[1]) ;
		_pos  = m_pDataView->TranslateToScenePlan(&_pos1);
		m_pParabola[1]->SetPoint(_pos1);

		m_pParabola[1]->setPos(_pos);
        m_pParabola[1]->show();
	}

    if(bHideCursor)
    {
        if(HideMode == 0)
        {
            if(m_pCursor[0])  m_pCursor[0]->hide() ;
            if(m_pCursor[1])  m_pCursor[1]->hide() ;
        }
        else if(HideMode == 2)
        {
            if(m_pCursor[2])  m_pCursor[2]->hide() ;
            if(m_pCursor[3])  m_pCursor[3]->hide() ;
            qDebug()<<"hide here"<<endl;
        }

        if(anCursorId[2] == setup_CURSOR_VPA_REF)
        {
            if(m_pCursor[2])  m_pCursor[2]->hide() ;
            if(m_pCursor[3])  m_pCursor[3]->hide() ;
        }
        else if(anCursorId[0] == setup_CURSOR_VPA_REF)
        {
            if(m_pCursor[0])  m_pCursor[0]->hide() ;
            if(m_pCursor[1])  m_pCursor[1]->hide() ;
        }

    }


}

void DopplerViewItems::UpdateItemsLawMarker()
{
	if(!(m_eShow & OVERLAYS_LAW_MARKER))
	{
		if(m_pLawMarker) m_pLawMarker->hide();
		return ;
	}

	if(!m_pLawMarker)
	{
		m_pLawMarker = new DopplerLawMarker() ;
		m_pLawMarker->SetItemType(DOPPLER_GRAPHICS_ITEM_LAW_MARKER ) ;
		m_pDataView->AddOverlayItems(m_pLawMarker);
		QRectF _rect(0 , 0 , 0 , 0) ;
		m_pDataView->SetItemGeometry(m_pLawMarker , _rect);
		m_pLawMarker->EnableMarkerQty(m_nLawQty);
        m_pLawMarker->SetDataView(m_pDataView);
	}

	QVector<QLineF> _lines ; _lines.clear();
	QLineF _tmp , _line ;
	QPointF _pos1 , _pos2 ;
	for(int i = 0 ; i < markers.count() ; i++)
	{
		_tmp = markers.at(i) ;
		_pos1 = _tmp.p1()  ; _pos2 = _tmp.p2()  ;
        double _fX1   = _pos1.x()  ;double _fX2   = _pos2.x()  ;
        DopplerConfigure* _pConfig = DopplerConfigure::Instance();
        int groupId = m_pDataView->GetGroupId();
        if(_pConfig->group[groupId].m_Shows==ON)
        {
            _pos1 = m_pDataView->LawTranslateToScenePlan(&_pos1) ;
            _pos2 = m_pDataView->LawTranslateToScenePlan(&_pos2) ;

        }else
        {
            _pos1 = m_pDataView->TranslateToScenePlan(&_pos1) ;
            _pos2 = m_pDataView->TranslateToScenePlan(&_pos2) ;

        }

		_line = QLineF(_pos1 , _pos2);
		_lines.append(_line);
	}

	m_pLawMarker->SetupMarkers(&_lines);
	m_pLawMarker->SetupStringMarker(&strMarker);
    m_pLawMarker->show();
}

void DopplerViewItems::UpdateItemsLawMarkerCScan()
{
    if(!(m_eShow & OVERLAYS_LAW_MARKER_C_SCAN))
    {
        if(m_pLawMarkerCScan) m_pLawMarkerCScan->hide();
        return ;
    }

    setup_DISPLAY_MODE _eDisplay = (setup_DISPLAY_MODE)m_pDataView->GetDataViewDrawType();
    DopplerLineItem::LINE_TYPE	  _nLineType = DopplerLineItem::LINE_FREE;
    DopplerLineItem::LINE_MOVE_TYPE _nMoveType = DopplerLineItem::LINE_MOVE_NO;
    if(_eDisplay == setup_DISPLAY_MODE_C_H || _eDisplay == setup_DISPLAY_MODE_CC_H)
    {
        _nLineType = DopplerLineItem::LINE_HORIZENTAL;
        _nMoveType = DopplerLineItem::LINE_MOVE_VERTICAL;
    } else if(_eDisplay == setup_DISPLAY_MODE_C_V || _eDisplay == setup_DISPLAY_MODE_CC_V) {
        _nLineType = DopplerLineItem::LINE_VERTICAL;
        _nMoveType = DopplerLineItem::LINE_MOVE_HORIZENTAL;
    }

    if(!m_pLawMarkerCScan)
    {
        m_pLawMarkerCScan = new DopplerCScanLineMark(COLOR_CURSOR_AREF);
        m_pLawMarkerCScan->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
        m_pLawMarkerCScan->SetLineType(DopplerLineItem::LINE_HORIZENTAL);
        m_pLawMarkerCScan->SetMoveType(DopplerLineItem::LINE_MOVE_VERTICAL);
        m_pLawMarkerCScan->SetDataView(m_pDataView);
        m_pDataView->AddOverlayItems(m_pLawMarkerCScan);

    }
//        if(m_pLawMarker){
//            connect(m_pLawMarkerCScan, SIGNAL(SignalChangeSScanLawMarkIndex(int)), m_pLawMarker, SLOT(SlotChangeLinePos(int)));
//        }

//        QRectF _rect(0 , 0 , 0 , 0) ;
//        m_pDataView->SetItemGeometry(m_pLawMarkerCScan, _rect );
        m_pLawMarkerCScan->SetItemId(anCursorId[4]);
        m_pLawMarkerCScan->SetWndRect(m_pDataView->GetZoomRect());
        m_pLawMarkerCScan->SetScenceSize(m_pDataView->GetViewSize());
        m_pLawMarkerCScan->SetLineType(_nLineType);
        m_pLawMarkerCScan->SetMoveType(_nMoveType);

        QRectF _rect(0 , 0 , 0 , 0);
        if(_eDisplay == setup_DISPLAY_MODE_C_V || _eDisplay == setup_DISPLAY_MODE_CC_V)
            _rect.setLeft(afCursorPos[4]);
        else if(_eDisplay == setup_DISPLAY_MODE_C_H || _eDisplay == setup_DISPLAY_MODE_CC_H){
            _rect.setTop(afCursorPos[4]);
        }

        if(m_pLawMarkerCScan)
            m_pDataView->SetItemGeometry(m_pLawMarkerCScan, _rect );

        m_pLawMarkerCScan->show();
}

int DopplerViewItems::GetLawMarkerQty()
{
	if(m_pLawMarker) {
		return m_pLawMarker->GetMarkerQty();
	}
    return 0;
}

int DopplerViewItems::GetLawMarkerLinesCount()
{
    if(m_pLawMarker) {
        return m_pLawMarker->GetMarkerLinesCount();
    }
    return 0;
}

int DopplerViewItems::GetLawMarkerPos(int nId_)
{
	if(m_pLawMarker) {
		int _nLaw = m_pLawMarker->GetMarkerPos(nId_);
		return _nLaw;
		//return m_pLawMarker->GetMarkerPos(nId_);
	}
    return 0;
}

void DopplerViewItems::SetLawMarkerPos(int nId_, int nMarkerPos)
{
    if(m_pLawMarker) {
        m_pLawMarker->SetMarkerPos(nId_, nMarkerPos);
    }
}

//void DopplerViewItems::SetLawMarkerCScanPos(int fPos_)
//{

//}

void DopplerViewItems::UpdateItemsThickness()
{
	int i ;
	if(!(m_eShow & OVERLAYS_THICKNESS))
	{
		for(i = 0 ; i < 10 ; i++)
			if(m_pThickness[i]) m_pThickness[i]->hide();
		return ;
	}

	double _fStart , _fStop , _fSliderStart , _fSliderStop;
    bool tofdDepth = false;
    float pcs;
    if(m_bHorizental){
        m_pDataView->GetRulerRange(&_fStart , &_fStop , &_fSliderStart , &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
        m_pDataView->GetTofdDepth(tofdDepth, pcs, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    }else{
        m_pDataView->GetRulerRange(&_fStart , &_fStop , &_fSliderStart , &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
        m_pDataView->GetTofdDepth(tofdDepth, pcs, DopplerDataView::DATA_VIEW_RULER_LEFT);
    }
    ParameterProcess* _pProcess = ParameterProcess::Instance();
    if(tofdDepth){
        double depthStart = _pProcess->transTofdHalfSoundPathToDepth(m_pDataView->GetGroupId(), _fStart);
        double depthEnd   = _pProcess->transTofdHalfSoundPathToDepth(m_pDataView->GetGroupId(), _fStop);
        if(depthStart > depthEnd){
            double _fTmp = depthEnd;
            depthEnd = depthStart;
            depthStart = _fTmp;
        }
        int _nQty = (int)(depthEnd / m_fInterval) - (int)(depthStart / m_fInterval);
        if(_nQty > 10) _nQty = 10;
        float _fStartPos = (1 + (int)(depthStart / m_fInterval)) * m_fInterval;
        QRectF _rect(0 , 0 , 0 , 0);
        for(i = 0 ; i < _nQty ; i++){
            if(!m_pThickness[i]){
                m_pThickness[i]  = new DopplerLineItem(COLOR_THICKNESS);
                m_pThickness[i]->SetLineStyle(Qt::DashLine) ;
                m_pThickness[i]->SetItemType(DOPPLER_GRAPHICS_ITEM_THICKNESS) ;
                m_pThickness[i]->SetItemId(i);
                m_pDataView->AddOverlayItems(m_pThickness[i]);
            }
            m_pThickness[i]->SetLineType(m_bHorizental ? DopplerLineItem::LINE_VERTICAL : DopplerLineItem::LINE_HORIZENTAL);
            m_pThickness[i]->SetMoveType(DopplerLineItem::LINE_MOVE_NO);
            m_bHorizental ? _rect.setLeft(_fStartPos + i * m_fInterval) : _rect.setTop(_fStartPos + i * m_fInterval);
            m_pDataView->SetTofdItemGeometry(m_pThickness[i] , _rect );
            m_pThickness[i]->show();
        }
        for(i = _nQty ; i < 10 ; i++){
            if(m_pThickness[i])  m_pThickness[i]->hide();
        }
    }else{
        if(_fStart > _fStop)
        {
            double _fTmp = _fStop ;
            _fStop = _fStart ;
            _fStart= _fTmp   ;
        }
        int _nQty =(int)(_fStop / m_fInterval) - (int)(_fStart / m_fInterval)  ;
        if(_nQty > 10) _nQty = 10 ;
        float _fStartPos = (1 + (int)(_fStart / m_fInterval)) * m_fInterval ;

        QRectF _rect(0 , 0 , 0 , 0);
        for(i = 0 ; i < _nQty ; i++)
        {
            if(!m_pThickness[i])
            {
                m_pThickness[i]  = new DopplerLineItem(COLOR_THICKNESS);
                m_pThickness[i]->SetLineStyle(Qt::DashLine) ;
                m_pThickness[i]->SetItemType(DOPPLER_GRAPHICS_ITEM_THICKNESS) ;
                m_pThickness[i]->SetItemId(i);
                m_pDataView->AddOverlayItems(m_pThickness[i]);
            }
            m_pThickness[i]->SetLineType(m_bHorizental ? DopplerLineItem::LINE_VERTICAL : DopplerLineItem::LINE_HORIZENTAL);
            m_pThickness[i]->SetMoveType(DopplerLineItem::LINE_MOVE_NO);
            m_bHorizental ? _rect.setLeft(_fStartPos + i * m_fInterval) : _rect.setTop(_fStartPos + i * m_fInterval)  ;
            m_pDataView->SetItemGeometry(m_pThickness[i] , _rect );
            m_pThickness[i]->show();
        }
        for(i = _nQty ; i < 10 ; i++)
        {
            if(m_pThickness[i])  m_pThickness[i]->hide();
        }
    }
}

void DopplerViewItems::UpdateItemsWeldBorder()
{
    int i;
    if(!(m_eShow & OVERLAYS_C_WELD_BORDER)){
        for(i = 0; i < 3; i++){
            if(m_pWeldBorder[i]) m_pWeldBorder[i]->hide();
        }
        return;
    }

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int groupId = m_pDataView->GetGroupId();
    bool topc, topcMerge;
    m_pDataView->GetCScanTopcDis( topc, topcMerge);
    bool status = topc || topcMerge;
    if( !_pConfig->group[groupId].TopCInfo.TOPCStatus && !status){
        for( i = 0; i < 3; i++){
            if(m_pWeldBorder[i]) m_pWeldBorder[i]->hide();
        }
        return;
    }

    float weldBorder = _pConfig->group[groupId].part.weld_border;
    float buff[3];
    buff[0] = -weldBorder;
    buff[1] = 0;
    buff[2] = weldBorder;
    QRectF _rect(0 , 0 , 0 , 0);
    for( i = 0; i < 3; i++){
        if(!m_pWeldBorder[i]){
            m_pWeldBorder[i] = new DopplerLineItem(COLOR_SCAN_MARKER);
            m_pWeldBorder[i]->SetLineStyle(Qt::DashLine);
            m_pWeldBorder[i]->SetItemType(DOPPLER_GRAPHICS_ITEM_THICKNESS);
            m_pWeldBorder[i]->SetItemId(i);
            m_pDataView->AddOverlayItems(m_pWeldBorder[i]);
        }
        m_pWeldBorder[i]->SetLineType( m_cWeldBorderHorizental ? DopplerLineItem::LINE_HORIZENTAL : DopplerLineItem::LINE_VERTICAL);
        m_pWeldBorder[i]->SetMoveType(DopplerLineItem::LINE_MOVE_NO);
        m_cWeldBorderHorizental ? _rect.setTop(buff[i]) : _rect.setLeft(buff[i]);
        m_pDataView->SetItemGeometry( m_pWeldBorder[i], _rect );
        m_pWeldBorder[i]->show();
    }
}

void DopplerViewItems::UpdateItemsTOPCWidth()
{
    int i;
    if(!(m_eShow & OVERLAYS_TOPC_WIDTH)){
        for( i = 0; i < 2; i++){
            if(m_pTOPCWidth[i]) m_pTOPCWidth[i]->hide();
        }
        return;
    }

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int groupId = m_pDataView->GetGroupId();
    bool topc, topcMerge;
    m_pDataView->GetCScanTopcDis( topc, topcMerge);
    if( !_pConfig->group[groupId].TopCInfo.TOPCStatus && !topc){
        for( i = 0; i < 2; i++){
            if(m_pTOPCWidth[i]) m_pTOPCWidth[i]->hide();
        }
        return;
    }

    double TOPCwidth = _pConfig->group[groupId].TopCInfo.TOPCWidth;
    double TOPCstart = 0 - TOPCwidth/2.0;
    double TOPCstop  = TOPCwidth/2.0;
    QRectF _rect(0 , 0 , 0 , 0);
    if(!m_pTOPCWidth[0]){
        m_pTOPCWidth[0]  = new DopplerLineItem(COLOR_THICKNESS);
        m_pTOPCWidth[0]->SetLineStyle(Qt::DashLine) ;
        m_pTOPCWidth[0]->SetItemType(DOPPLER_GRAPHICS_ITEM_THICKNESS) ;
        m_pTOPCWidth[0]->SetItemId(0);
        m_pDataView->AddOverlayItems(m_pTOPCWidth[0]);
    }
    m_pTOPCWidth[0]->SetLineType(DopplerLineItem::LINE_VERTICAL);
    m_pTOPCWidth[0]->SetMoveType(DopplerLineItem::LINE_MOVE_NO);
    _rect.setLeft(TOPCstart);
    m_pDataView->SetItemGeometry( m_pTOPCWidth[0], _rect );
    m_pTOPCWidth[0]->show();
    if(!m_pTOPCWidth[1]){
        m_pTOPCWidth[1]  = new DopplerLineItem(COLOR_THICKNESS);
        m_pTOPCWidth[1]->SetLineStyle(Qt::DashLine) ;
        m_pTOPCWidth[1]->SetItemType(DOPPLER_GRAPHICS_ITEM_THICKNESS) ;
        m_pTOPCWidth[1]->SetItemId(1);
        m_pDataView->AddOverlayItems(m_pTOPCWidth[1]);
    }
    m_pTOPCWidth[1]->SetLineType(DopplerLineItem::LINE_VERTICAL);
    m_pTOPCWidth[1]->SetMoveType(DopplerLineItem::LINE_MOVE_NO);
    _rect.setLeft(TOPCstop);
    m_pDataView->SetItemGeometry( m_pTOPCWidth[1], _rect);
    m_pTOPCWidth[1]->show();
}

void DopplerViewItems::UpdateItemsWeld()
{
	if(!(m_eShow & OVERLAYS_LAW_MARKER))
		return ;

	if(m_eShow & OVERLAYS_WELD )
	{
        QPainterPath _path;
        QPainterPath _HAZpath;
        bool brushHAZ;
        DrawWeld(_path, _HAZpath, brushHAZ);
		if(m_pLawMarker){
			m_pLawMarker->SetWeldColor(COLOR_WELD);
            if(brushHAZ){
                m_pLawMarker->SetWeldInfo(true , brushHAZ, &_path, &_HAZpath);
            }else{
                m_pLawMarker->SetWeldInfo(true , brushHAZ, &_path, NULL);
            }

		}
    }else{
        if(m_pLawMarker) m_pLawMarker->SetWeldInfo(false, false, NULL, NULL);
	}
}

void DopplerViewItems::UpdateScanMarker()
{
    if(!(m_eShow & OVERLAYS_SCAN_MARKER))
    {
        if(m_pScanMarker) m_pScanMarker->hide();
        return ;
    }

    if(!m_pScanMarker)
    {
        m_pScanMarker = new DopplerScanMarker(COLOR_SCAN_MARKER);
        m_pScanMarker->SetItemType(DOPPLER_GRAPHICS_ITEM_SCAN ) ;
        m_pScanMarker->SetLineType(m_bScanMarkerHorizental ? DopplerLineItem::LINE_HORIZENTAL : DopplerLineItem::LINE_VERTICAL );
        m_pScanMarker->SetMoveType(m_bScanMarkerHorizental ? DopplerLineItem::LINE_MOVE_VERTICAL : DopplerLineItem::LINE_MOVE_HORIZENTAL);
        m_pDataView->AddOverlayItems(m_pScanMarker);
    }
    QRectF _rect(0 , 0 , 0 , 0);
    if(m_bScanMarkerHorizental)
        _rect.setTop (m_fScanPos);
    else
        _rect.setLeft(m_fScanPos);
    m_pDataView->SetItemGeometry(m_pScanMarker, _rect);
    m_pScanMarker->SetScenceSize(m_pDataView->GetViewSize());
    m_pScanMarker->show();

}

void DopplerViewItems::SetGateDrawMode(GATE_DRAW_MODE eMode_)
{
	m_eGateMode   = eMode_  ;
}

void DopplerViewItems::SetParabolaScale(float scaleH, float scaleV)
{
    if(m_eShow & OVERLAYS_PARABOLA){
        if(m_pParabola[0]){
            m_pParabola[0]->Set_Scale( scaleH, scaleV);
        }
        if(m_pParabola[1]){
            m_pParabola[1]->Set_Scale( scaleH, scaleV);
        }
    }
}

void DopplerViewItems::SetLwBwPos(float fLw_ , float fBw_)
{
	m_fLW = fLw_;
	m_fBW = fBw_;
}

void DopplerViewItems::SetLwBwId(int iLwId_ , int iBwId_)
{
	m_iLwId = iLwId_;
    m_iBwId = iBwId_;
}

void DopplerViewItems::SetCalibrationPos(float fCalPos_)
{
    m_fCalibrationPos = fCalPos_;
}

void DopplerViewItems::SetCalibrationId(int iCalibrationId_)
{
    m_iCalibrationbId = iCalibrationId_;
}

void DopplerViewItems::SetDefect(int index_ , QRectF rect_)
{
	m_iDefectId[index_] = index_;
	m_rcDefect[index_] = rect_;
}

void DopplerViewItems::SetDefectIndex(int index_)
{
	m_iDefectIndex = -index_;
}

void DopplerViewItems::ClearDefect()
{
	for(int i = 0; i < DEFECT_SIGN_MAX; i++)
	{
	m_iDefectId[i] = -1;
	}
	m_iDefectIndex = -1;
}

void DopplerViewItems::SetGatePos(int eGate_ , float fStart_ , float fWidth_ , float fHeight_)
{
	afGatePos[eGate_][0]  = fStart_  ;
	afGatePos[eGate_][1]  = fWidth_  ;
	afGatePos[eGate_][2]  = fHeight_ ;
}

void DopplerViewItems::GateMove(int eGate_ , float fStart_ , float fWidth_ , float fHeight_)
{
	QRectF _rect(0 , 0 , 0 , 0);
    DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
    int _GroupId = m_pDataView->GetGroupId();
    if(_pConfig->group[_GroupId].eTxRxMode == setup_TX_RX_MODE_TOFD)
        fHeight_ = (fHeight_+100)/2.0;
	switch(m_eGateMode)
	{
	case GATE_MODE_GATE_HORIZENTAL:
	case GATE_MODE_LINE_HORIZENTAL:
		_rect = QRectF(fStart_ , fHeight_ , fWidth_ , 0);
		if(m_pGate[eGate_])
			m_pDataView->SetItemGeometry(m_pGate[eGate_] , _rect );
		break;
	case GATE_MODE_GATE_VERTICAL:
	case GATE_MODE_LINE_VERTICAL:
		_rect = QRectF(fHeight_ , fStart_ , 0 , fWidth_ );
		if(m_pGate[eGate_])
			m_pDataView->SetItemGeometry(m_pGate[eGate_] , _rect );
		break;
    case GATE_MODE_S_TRUEDEPTH:
        if(_pConfig->group[_GroupId].gate[eGate_].gTravelMode == setup_GATE_DEPTH){
            _rect = QRectF(fHeight_, fStart_, 0, fWidth_);
            if(m_pGate[eGate_]){
                m_pDataView->SetItemGeometry(m_pGate[eGate_], _rect);
                m_pGate[eGate_]->clearCurveGate();
            }
        }else{
            m_pDataView->setSTCurveGatePoints( m_pGate[eGate_], eGate_);
        }
        break;
    case GATE_MODE_S_SOUNDPATH:
        if(_pConfig->group[_GroupId].gate[eGate_].gTravelMode == setup_GATE_DEPTH){
            if( _pConfig->group[_GroupId].law.eLawType == setup_LAW_TYPE_AZIMUTHAL){
                m_pDataView->setSSCurveGatePoints( m_pGate[eGate_], eGate_);
            }else{
                _rect = QRectF(fStart_, fHeight_, fWidth_, 0);
                if(m_pGate[eGate_]){
                    m_pDataView->SetItemGeometry(m_pGate[eGate_], _rect);
                    m_pGate[eGate_]->clearCurveGate();
                }
            }
        }else{
            _rect = QRectF(fStart_, fHeight_, fWidth_, 0);
            if(m_pGate[eGate_]){
                m_pDataView->SetItemGeometry(m_pGate[eGate_], _rect);
                m_pGate[eGate_]->clearCurveGate();
            }
        }
        break;
	default:
		break;
	}
}

void DopplerViewItems::CursorMove(int eCursor_ , float fPos_)
{
	QRectF _rect(0 , 0 , 0 , 0);
	if(eCursor_ > 1 )
		_rect.setLeft(fPos_);
	else
		_rect.setTop(fPos_);
	if(m_pCursor[eCursor_])
		m_pDataView->SetItemGeometry(m_pCursor[eCursor_] , _rect );
}


void DopplerViewItems::SetCursorPos(int eCursor_ , float fPos_)
{
	afCursorPos[eCursor_]  = fPos_;
}

void DopplerViewItems::SetCursorId(int eCursor_ , int nId_)
{
	anCursorId[eCursor_] = nId_ ;
}


void DopplerViewItems::SetupMarkersVector(QVector<QLineF>* pLines_)
{
	markers.clear();
	for(int i = 0 ; i < pLines_->count() ; i++)
	{
		markers.append(pLines_->at(i));
	}

}

void DopplerViewItems::SetupLawMarkerString(QVector<QString>* pMarkers_)
{
	strMarker.clear();
	for(int i = 0 ; i < pMarkers_->count() ; i++)
	{
		strMarker.append(pMarkers_->at(i));
	}
}

void DopplerViewItems::SetMarkerColor(int nId_ , QColor* pColor_)
{
	if(m_pLawMarker)
		m_pLawMarker->SetMarkerColor(nId_ , pColor_);
}

void DopplerViewItems::EnableMarkerQty(unsigned int nQty_)
{
	m_nLawQty  = nQty_ ;
}


void DopplerViewItems::SetThicknessDirection(bool bHorizental_)
{
	m_bHorizental = bHorizental_;
}

void DopplerViewItems::SetWeldBorderDirection(bool direction)
{
    m_cWeldBorderHorizental = direction;
}

void DopplerViewItems::SetThicknessInterval(float fInterval_)
{
	m_fInterval   = fInterval_;
}

void DopplerViewItems::SetScanMarkerDirectionHorizental(bool bHorizental_)
{
	m_bScanMarkerHorizental = bHorizental_ ;
}

void DopplerViewItems::SetScanMarkerPos(float fPos_)
{
	m_fScanPos  = fPos_ ;
}

void DopplerViewItems::SetPartInfo(PART_CONFIG* pPart_)
{
	if(pPart_)
		memcpy((void*)&m_cPart, (void*)pPart_ , sizeof(PART_CONFIG)) ;
}

void DopplerViewItems::SetParabolaDirection(bool bVertical_)
{
	m_bParabolaVertical = bVertical_ ;
}

void DopplerViewItems::ResetDefect()
{
    for(int i = 0; i < DEFECT_SIGN_MAX; i++)
    {
        if(m_iDefectId[i] >= 0)
        m_pDefect[i]->IsSelected = -1;
    }
}

void  DopplerViewItems::DrawWeld(QPainterPath& path, QPainterPath& HAZpath, bool &brushHAZ)
{
    //qDebug()<<"indndn";
    if(m_cPart.weldFormat)
    {
        brushHAZ = true;
        switch (m_cPart.weld_ii.eType) {
        case NONE_TYPE:
            brushHAZ = false;
            DrawWeldNoneDataII( path);
        case I:
            DrawWeldIDataII( path, HAZpath);
            break;
        case V:
            DrawWeldVDataII( path, HAZpath);
            break;
        case U:
            DrawWeldUDataII( path, HAZpath);
            break;
        case VY:
            DrawWeldVYDataII( path, HAZpath);
            break;
        case VV:
            DrawWeldVVDataII( path, HAZpath);
            break;
        case UU:
            DrawWeldUUDataII( path, HAZpath);
            break;
        case UV:
            DrawWeldUVDataII( path, HAZpath);
            break;
        case TKY:
            brushHAZ = false;
            DrawWeldTKYDataII( path);
            break;
        case DXF:
            brushHAZ = false;
            DrawWeldDxf(path);
            break;

        case ASYMMETRIC: //不等厚焊缝

           DrawWeldASYDataII(path);
           //brushHAZ = false;
           break;

        default:
            brushHAZ = false;
            DrawWeldNoneDataII( path);
            break;
        }
    }
    else
    {
        brushHAZ = false;
        switch (m_cPart.weld.eType)
        {
        case setup_WELD_I :
            DrawWeldI(path) ;
            break;
        case setup_WELD_V :
            DrawWeldV(path) ;
            break;
        case setup_WELD_DV :
            DrawWeldDV(path) ;
            break;
        case setup_WELD_U :
            DrawWeldU(path) ;
            break;
        case setup_WELD_DIFF_DV://New Add
            DrawWeldDiffDV(path);
            break;
        case setup_WELD_J: //New Add
            DrawWeldJ(path);
            break;
        case setup_WELD_VY: //New Add
            DrawWeldVY(path);
            break;
        case setup_WELD_TKY:
            DrawWeldTKY(path);

            break;
    //	case setup_WELD_NCC :
    //		DrawWeldNcc(path);
    //		break;
        case setup_WELD_DXF: //New Add
            DrawWeldDxf(path);
            break;
        default:
            break;
        }
    }
}

void  DopplerViewItems::DrawWeldI (QPainterPath& path)
{
	QPointF _pos[2] ;
	double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
	m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
	_pos[0].setX(0);
	_pos[0].setY(_fStartV);
	_pos[1].setX(0);
	_pos[1].setY(_fStopV);
	_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
	_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
	path.moveTo(_pos[0]);
	path.lineTo(_pos[1]);

	int _nStart = _fStartV / m_fInterval ;
	int _nStop  = _fStopV  / m_fInterval + 1;
	for(int i = _nStart ; i < _nStop ; i++)
	{
		if(i%2)
		{
			double _nOffsetY = m_fInterval * ( i + 1 ) ;
			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-m_cPart.weld.weland_offset);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY - m_cPart.weld.weland_height );

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(m_cPart.weld.weland_offset);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
			}
        }else{
			double _nOffsetY = m_fInterval * i ;
			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-m_cPart.weld.weland_offset);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-m_cPart.weld.weland_offset);
				_pos[1].setY(m_cPart.weld.weland_height + _nOffsetY);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(m_cPart.weld.weland_offset);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(m_cPart.weld.weland_offset);
				_pos[1].setY(m_cPart.weld.weland_height + _nOffsetY);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
			}
		}
	}
}

void DopplerViewItems::DrawWeldNoneDataII(QPainterPath& path)
{
    QPointF _pos[2] ;
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
}

void DopplerViewItems::DrawWeldIDataII(QPainterPath& path, QPainterPath& HAZpath)
{
    QPointF _pos[4] ;
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
        _pos[0].setX( -m_cPart.weld_ii.I.w);
        _pos[0].setY( _fStartV);
        _pos[1].setX( -m_cPart.weld_ii.I.w);
        _pos[1].setY( _fStopV);
        _pos[2].setX( - m_cPart.weld_ii.I.w - m_cPart.weld_ii.eHAZ);
        _pos[2].setY( _fStartV);
        _pos[3].setX( - m_cPart.weld_ii.I.w - m_cPart.weld_ii.eHAZ);
        _pos[3].setY( _fStopV);

        _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
        _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
        _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
        _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
        path.moveTo( _pos[0]);
        path.lineTo( _pos[1]);
        path.moveTo( _pos[2]);
        path.lineTo( _pos[3]);
        HAZpath.moveTo( _pos[0]);
        HAZpath.lineTo( _pos[1]);
        HAZpath.lineTo( _pos[3]);
        HAZpath.lineTo( _pos[2]);
        HAZpath.lineTo( _pos[0]);
    }

    if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
        _pos[0].setX( m_cPart.weld_ii.I.w);
        _pos[0].setY( _fStartV);
        _pos[1].setX( m_cPart.weld_ii.I.w);
        _pos[1].setY( _fStopV);
        _pos[2].setX( m_cPart.weld_ii.I.w + m_cPart.weld_ii.eHAZ);
        _pos[2].setY( _fStartV);
        _pos[3].setX( m_cPart.weld_ii.I.w + m_cPart.weld_ii.eHAZ);
        _pos[3].setY( _fStopV);

        _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
        _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
        _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
        _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
        path.moveTo( _pos[0]);
        path.lineTo( _pos[1]);
        path.moveTo( _pos[2]);
        path.lineTo( _pos[3]);
        HAZpath.moveTo( _pos[0]);
        HAZpath.lineTo( _pos[1]);
        HAZpath.lineTo( _pos[3]);
        HAZpath.lineTo( _pos[2]);
        HAZpath.lineTo( _pos[0]);
    }
}

void  DopplerViewItems::DrawWeldV (QPainterPath& path)
{
	QPointF _pos[3] ;
	double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
	m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
	_pos[0].setX(0);
	_pos[0].setY(_fStartV);
	_pos[1].setX(0);
	_pos[1].setY(_fStopV);
	_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
	_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
	path.moveTo(_pos[0]);
	path.lineTo(_pos[1]);

	int _nStart = _fStartV / m_fInterval ;
	int _nStop  = _fStopV  / m_fInterval + 1;
	for(int i = _nStart ; i < _nStop ; i++)
	{
		if(i%2)
		{
			double _nOffsetY = m_fInterval * ( i + 1) ;
			double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height ;
			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
				_pos[2].setX(-m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
				_pos[2].setX(m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
			}
        }else{
			double _nOffsetY = m_fInterval * i ;
			double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height ;
			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
				_pos[2].setX(-m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
				_pos[2].setX(m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
			}
		}
	}
}

void DopplerViewItems::DrawWeldVDataII( QPainterPath& path, QPainterPath& HAZpath)
{
    QPointF _pos[6] ;
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    int _nStart = _fStartV / m_fInterval ;
    int _nStop  = _fStopV  / m_fInterval + 1;
    double w1 = m_cPart.weld_ii.V.w1;
    double w2 = m_cPart.weld_ii.V.w2;
    double h  = m_cPart.weld_ii.V.h;
    double HAZ = m_cPart.weld_ii.eHAZ;

    if( h > m_fInterval)
    {
        double _xOffset = ( h - m_fInterval)*( w1 - w2)/h + w2;
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1);
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-_xOffset);
                    _pos[1].setY(_nOffsetY - m_fInterval);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-_xOffset - HAZ);
                    _pos[3].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(_xOffset);
                    _pos[1].setY(_nOffsetY - m_fInterval);
                    _pos[2].setX(w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(_xOffset + HAZ);
                    _pos[3].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-_xOffset);
                    _pos[1].setY(_nOffsetY + m_fInterval);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-_xOffset - HAZ);
                    _pos[3].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(_xOffset);
                    _pos[1].setY(_nOffsetY + m_fInterval);
                    _pos[2].setX(w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(_xOffset + HAZ);
                    _pos[3].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }

    }
    else
    {
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1) ;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-m_cPart.weld_ii.V.w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-m_cPart.weld_ii.V.w2);
                    _pos[1].setY(_nOffsetY - m_cPart.weld_ii.V.h);
                    _pos[2].setX(-m_cPart.weld_ii.V.w2);
                    _pos[2].setY(_nOffsetY - m_fInterval);
                    _pos[3].setX(-m_cPart.weld_ii.V.w1 - HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(-m_cPart.weld_ii.V.w2 - HAZ);
                    _pos[4].setY(_nOffsetY - m_cPart.weld_ii.V.h);
                    _pos[5].setX(-m_cPart.weld_ii.V.w2 - HAZ);
                    _pos[5].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]) ;
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(m_cPart.weld_ii.V.w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(m_cPart.weld_ii.V.w2);
                    _pos[1].setY(_nOffsetY - m_cPart.weld_ii.V.h);
                    _pos[2].setX(m_cPart.weld_ii.V.w2);
                    _pos[2].setY(_nOffsetY - m_fInterval);
                    _pos[3].setX(m_cPart.weld_ii.V.w1 + HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(m_cPart.weld_ii.V.w2 + HAZ);
                    _pos[4].setY(_nOffsetY - m_cPart.weld_ii.V.h);
                    _pos[5].setX(m_cPart.weld_ii.V.w2 + HAZ);
                    _pos[5].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]) ;
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-m_cPart.weld_ii.V.w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-m_cPart.weld_ii.V.w2);
                    _pos[1].setY(_nOffsetY + m_cPart.weld_ii.V.h);
                    _pos[2].setX(-m_cPart.weld_ii.V.w2);
                    _pos[2].setY(_nOffsetY + m_fInterval);
                    _pos[3].setX(-m_cPart.weld_ii.V.w1 - HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(-m_cPart.weld_ii.V.w2 - HAZ);
                    _pos[4].setY(_nOffsetY + m_cPart.weld_ii.V.h);
                    _pos[5].setX(-m_cPart.weld_ii.V.w2 - HAZ);
                    _pos[5].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(m_cPart.weld_ii.V.w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(m_cPart.weld_ii.V.w2);
                    _pos[1].setY(_nOffsetY + m_cPart.weld_ii.V.h);
                    _pos[2].setX(m_cPart.weld_ii.V.w2);
                    _pos[2].setY(_nOffsetY + m_fInterval);
                    _pos[3].setX(m_cPart.weld_ii.V.w1 + HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(m_cPart.weld_ii.V.w2 + HAZ);
                    _pos[4].setY(_nOffsetY + m_cPart.weld_ii.V.h);
                    _pos[5].setX(m_cPart.weld_ii.V.w2 + HAZ);
                    _pos[5].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }
}

void  DopplerViewItems::DrawWeldDV(QPainterPath& path)
{
	QPointF _pos[4] ;
	double _fStartV , _fStopV ,_fSliderStartV, _fSliderStopV;
	m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
	_pos[0].setX(0);
	_pos[0].setY(_fStartV);
	_pos[1].setX(0);
	_pos[1].setY(_fStopV);
	_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
	_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
	path.moveTo(_pos[0]);
	path.lineTo(_pos[1]);

	int _nStart = _fStartV / m_fInterval ;
	int _nStop  = _fStopV  / m_fInterval + 1;
	for(int i = _nStart ; i < _nStop ; i++)
	{
		if(i%2)
		{
			double _nOffsetY = m_fInterval * ( i + 1) ;
			double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height ;
			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
				_pos[2].setX(-m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);
				_pos[3].setX(-_fTmpPosX1);
				_pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height * 2 - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
				path.lineTo(_pos[3]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
				_pos[2].setX(m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);
				_pos[3].setX(_fTmpPosX1);
				_pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height * 2 - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
				path.lineTo(_pos[3]);
			}
        }else{
			double _nOffsetY = m_fInterval * i ;
			double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height ;
			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
				_pos[2].setX(-m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);
				_pos[3].setX(-_fTmpPosX1);
				_pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height * 2 + m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
				path.lineTo(_pos[3]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(_fTmpPosX1);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(m_cPart.weld.weland_offset);
				_pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
				_pos[2].setX(m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);
				_pos[3].setX(_fTmpPosX1);
				_pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height * 2 + m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.lineTo(_pos[2]);
				path.lineTo(_pos[3]);
			}
		}
	}
}

void  DopplerViewItems::DrawWeldU (QPainterPath& path)
{
	if(m_cPart.weld.weland_offset >= m_cPart.weld.fizone_radius )
	{
		DrawWeldV(path) ;
		return ;
	}

	QPointF _pos[4] ;
	double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
	m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
	_pos[0].setX(0);
	_pos[0].setY(_fStartV);
	_pos[1].setX(0);
	_pos[1].setY(_fStopV);
	_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
	_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
	path.moveTo(_pos[0]);
	path.lineTo(_pos[1]);

	double _fFizoneAngle = DEGREE_TO_ARCH(m_cPart.weld.fizone_angle) ;
	double _nTmpY2 = sin(_fFizoneAngle) * m_cPart.weld.fizone_radius  ;
	double _nTmpY1 = sqrt(m_cPart.weld.fizone_radius * m_cPart.weld.fizone_radius - m_cPart.weld.weland_offset * m_cPart.weld.weland_offset );
	if(_nTmpY2 > _nTmpY1)
	{
		DrawWeldV( path ) ;
		return ;
	}
	double _fPosX = cos(_fFizoneAngle) * m_cPart.weld.fizone_radius  ;
	double _fPosY = m_cPart.weld.fizone_height - _nTmpY1 + _nTmpY2   ;

	double _fAngleStart = m_cPart.weld.fizone_angle + 180 ;
	double _asine = ARCH_TO_DEGREE(asin(m_cPart.weld.weland_offset / m_cPart.weld.fizone_radius)) ;
	double _fAngleStop   = 270  - _asine  - _fAngleStart	 ;
	double _fAngleStart1 = 180  - _fAngleStart - _fAngleStop ;

	int _nStart = _fStartV / m_fInterval ;
	int _nStop  = _fStopV  / m_fInterval + 1;
	for(int i = _nStart ; i < _nStop  ; i++)
	{
		if(i%2)
		{
			double _nOffsetY = m_fInterval * (i+1) ;
			QPointF _lefttop , _rightbottom;
			_lefttop.setX(-m_cPart.weld.fizone_radius);
			_lefttop.setY(_nOffsetY - m_cPart.weld.fizone_height + _nTmpY1 + m_cPart.weld.fizone_radius);
			_rightbottom.setX(m_cPart.weld.fizone_radius);
			_rightbottom.setY(_nOffsetY - m_cPart.weld.fizone_height + _nTmpY1 - m_cPart.weld.fizone_radius);
			_lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
			_rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom) ;
			QRectF rectangle(_lefttop , _rightbottom);

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-_fPosX - tan(_fFizoneAngle) * _fPosY);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-_fPosX);
				_pos[1].setY(_nOffsetY - _fPosY);
				_pos[2].setX(-m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height);
				_pos[3].setX(-m_cPart.weld.weland_offset);
				_pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.arcTo( rectangle , _fAngleStart , _fAngleStop);
				path.moveTo(_pos[2]);
				path.lineTo(_pos[3]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(_fPosX + tan(_fFizoneAngle) * _fPosY);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(_fPosX);
				_pos[1].setY(_nOffsetY - _fPosY);
				_pos[2].setX(m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height);
				_pos[3].setX(m_cPart.weld.weland_offset);
				_pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;

				path.moveTo(_pos[2]);
				path.lineTo(_pos[3]);
				path.arcTo(rectangle , _fAngleStart1 , _fAngleStop);
				path.moveTo(_pos[1]);
				path.lineTo(_pos[0]);
			}
        }else{
			double _nOffsetY = m_fInterval * i ;
			QPointF _lefttop , _rightbottom;
			_lefttop.setX(-m_cPart.weld.fizone_radius);
			_lefttop.setY(_nOffsetY + m_cPart.weld.fizone_height - _nTmpY1 - m_cPart.weld.fizone_radius);
			_rightbottom.setX(m_cPart.weld.fizone_radius);
			_rightbottom.setY(_nOffsetY + m_cPart.weld.fizone_height - _nTmpY1 + m_cPart.weld.fizone_radius);
			_lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
			_rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom) ;
			QRectF rectangle(_lefttop , _rightbottom);

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
			{
				_pos[0].setX(-_fPosX - tan(_fFizoneAngle) * _fPosY);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(-_fPosX);
				_pos[1].setY(_nOffsetY + _fPosY);
				_pos[2].setX(-m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height);
				_pos[3].setX(-m_cPart.weld.weland_offset);
				_pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
				path.moveTo(_pos[0]);
				path.lineTo(_pos[1]);
				path.arcTo(rectangle , _fAngleStart , _fAngleStop);
				path.moveTo(_pos[2]);
				path.lineTo(_pos[3]);
			}

			if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
			{
				_pos[0].setX(_fPosX + tan(_fFizoneAngle) * _fPosY);
				_pos[0].setY(_nOffsetY);
				_pos[1].setX(_fPosX);
				_pos[1].setY(_nOffsetY + _fPosY);
				_pos[2].setX(m_cPart.weld.weland_offset);
				_pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height);
				_pos[3].setX(m_cPart.weld.weland_offset);
				_pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

				_pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
				_pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
				_pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
				_pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;

				path.moveTo(_pos[2]);
				path.lineTo(_pos[3]);
				path.arcTo(rectangle , _fAngleStart1 , _fAngleStop);
				path.moveTo(_pos[1]);
				path.lineTo(_pos[0]);
			}
		}
    }
}

void DopplerViewItems::DrawWeldUDataII(QPainterPath& path, QPainterPath& HAZpath)
{
    if( m_cPart.weld_ii.U.w2 >= m_cPart.weld_ii.U.r)
    {
        DrawWeldVDataII( path, HAZpath);
        return;
    }

    QPointF _pos[8];
    double _fStartV, _fStopV, _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double w1 = m_cPart.weld_ii.U.w1;
    double w2 = m_cPart.weld_ii.U.w2;
    double h  = m_cPart.weld_ii.U.h;
    double r  = m_cPart.weld_ii.U.r;
    double HAZ = m_cPart.weld_ii.eHAZ;
    //double R  = 2*r;
    double h1 = sqrt(pow(r,2) - pow(w2,2));
    double h2 = h - h1;
    double l1 = sqrt(pow(w1,2) + pow(h2,2));
    double l2 = sqrt(pow(l1,2) - pow(r,2));
    double angle1 = atan(h2 / w1);
    double angle2 = atan(r / l2);
    double h3 = l2 * sin(angle1 + angle2);
    double w3 = w1 - l2 * cos(angle1 + angle2);
    angle1  = M_PI/2  - (angle1 + angle2) ;
    angle2 = asin(w2 / r);
    int b = (int)(angle1 * 180 / M_PI);
    int e = (90 - b - (int)(angle2 * 180 / M_PI));

    int _nStart = _fStartV / m_fInterval;
    int _nStop  = _fStopV  / m_fInterval + 1;
    //显示V+U+I
    if( h < m_fInterval)
    {
        for(int i = _nStart; i < _nStop; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * (i+1);
                QPointF _lefttop , _rightbottom;
                _lefttop.setX(-r);
                _lefttop.setY(_nOffsetY - h2 + r);
                _rightbottom.setX(r);
                _rightbottom.setY(_nOffsetY - h2 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle( _lefttop, _rightbottom);

                _lefttop.setX(-r - HAZ);
                _lefttop.setY(_nOffsetY - h2 + r);
                _rightbottom.setX(r - HAZ);
                _rightbottom.setY(_nOffsetY - h2 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1( _lefttop, _rightbottom);

                _lefttop.setX(-r + HAZ);
                _lefttop.setY(_nOffsetY - h2 + r);
                _rightbottom.setX(r + HAZ);
                _rightbottom.setY(_nOffsetY - h2 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2( _lefttop, _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w3);
                    _pos[1].setY(_nOffsetY - h3);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY - h);
                    _pos[3].setX(-w2);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[4].setX(-w1 - HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(-w3 - HAZ);
                    _pos[5].setY(_nOffsetY - h3);
                    _pos[6].setX(-w2 - HAZ);
                    _pos[6].setY(_nOffsetY - h);
                    _pos[7].setX(-w2 - HAZ);
                    _pos[7].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, 180+b, e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.arcTo( rectangle1, 180+b, e);
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, 180+b, e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.arcTo( rectangle1, 180+b+e, -e);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX( w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX( w3);
                    _pos[1].setY(_nOffsetY - h3);
                    _pos[2].setX( w2);
                    _pos[2].setY(_nOffsetY - h);
                    _pos[3].setX( w2);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[4].setX( w1 + HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX( w3 + HAZ);
                    _pos[5].setY(_nOffsetY - h3);
                    _pos[6].setX( w2 + HAZ);
                    _pos[6].setY(_nOffsetY - h);
                    _pos[7].setX( w2 + HAZ);
                    _pos[7].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, -b, -e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.arcTo( rectangle2, -b, -e);
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, -b, -e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.arcTo( rectangle2, -b-e, e);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                QPointF _lefttop , _rightbottom;
                _lefttop.setX(-r);
                _lefttop.setY(_nOffsetY + h2 - r);
                _rightbottom.setX(r);
                _rightbottom.setY(_nOffsetY + h2 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop);
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle(_lefttop , _rightbottom);

                _lefttop.setX(-r - HAZ);
                _lefttop.setY(_nOffsetY + h2 - r);
                _rightbottom.setX(r - HAZ);
                _rightbottom.setY(_nOffsetY + h2 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop);
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1(_lefttop , _rightbottom);

                _lefttop.setX(-r + HAZ);
                _lefttop.setY(_nOffsetY + h2 - r);
                _rightbottom.setX(r + HAZ);
                _rightbottom.setY(_nOffsetY + h2 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop);
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2(_lefttop , _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w3);
                    _pos[1].setY(_nOffsetY + h3);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY + h);
                    _pos[3].setX(-w2);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[4].setX(-w1 - HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(-w3 - HAZ);
                    _pos[5].setY(_nOffsetY + h3);
                    _pos[6].setX(-w2 - HAZ);
                    _pos[6].setY(_nOffsetY + h);
                    _pos[7].setX(-w2 - HAZ);
                    _pos[7].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, (180+b), e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.arcTo( rectangle1, 180+b, e);
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, 180+b, e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.arcTo( rectangle1, 180+b+e, -e);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX( w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX( w3);
                    _pos[1].setY(_nOffsetY + h3);
                    _pos[2].setX( w2);
                    _pos[2].setY(_nOffsetY + h);
                    _pos[3].setX( w2);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[4].setX( w1 + HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX( w3 + HAZ);
                    _pos[5].setY(_nOffsetY + h3);
                    _pos[6].setX( w2 + HAZ);
                    _pos[6].setY(_nOffsetY + h);
                    _pos[7].setX( w2 + HAZ);
                    _pos[7].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, -b, -e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.arcTo( rectangle2, -b, -e);
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, -b, -e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.arcTo( rectangle2, -b-e, e);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }//显示V+U
    else if( h3 < m_fInterval)
    {
        angle2 = acos((m_fInterval - h2) / r);
        e = (90 - b - (int)(angle2 * 180 / M_PI));
        for(int i = _nStart; i < _nStop; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * (i+1);
                QPointF _lefttop , _rightbottom;
                _lefttop.setX(-r);
                _lefttop.setY(_nOffsetY - h2 + r);
                _rightbottom.setX(r);
                _rightbottom.setY(_nOffsetY - h2 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle( _lefttop, _rightbottom);

                _lefttop.setX(-r - HAZ);
                _lefttop.setY(_nOffsetY - h2 + r);
                _rightbottom.setX(r - HAZ);
                _rightbottom.setY(_nOffsetY - h2 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1( _lefttop, _rightbottom);

                _lefttop.setX(-r + HAZ);
                _lefttop.setY(_nOffsetY - h2 + r);
                _rightbottom.setX(r + HAZ);
                _rightbottom.setY(_nOffsetY - h2 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2( _lefttop, _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w3);
                    _pos[1].setY(_nOffsetY - h3);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-w3 - HAZ);
                    _pos[3].setY(_nOffsetY - h3);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, 180+b, e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.arcTo( rectangle1, 180+b, e);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, 180+b, e);
                    HAZpath.arcTo( rectangle1, 180+b+e, -e);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX( w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX( w3);
                    _pos[1].setY(_nOffsetY - h3);
                    _pos[2].setX( w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX( w3 + HAZ);
                    _pos[3].setY(_nOffsetY - h3);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, -b, -e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.arcTo( rectangle2, -b, -e);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, -b, -e);
                    HAZpath.arcTo( rectangle, -b-e, e);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                QPointF _lefttop , _rightbottom;
                _lefttop.setX(-r);
                _lefttop.setY(_nOffsetY + h2 - r);
                _rightbottom.setX(r);
                _rightbottom.setY(_nOffsetY + h2 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop);
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle(_lefttop , _rightbottom);

                _lefttop.setX(-r - HAZ);
                _lefttop.setY(_nOffsetY + h2 - r);
                _rightbottom.setX(r - HAZ);
                _rightbottom.setY(_nOffsetY + h2 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop);
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1(_lefttop , _rightbottom);

                _lefttop.setX(-r + HAZ);
                _lefttop.setY(_nOffsetY + h2 - r);
                _rightbottom.setX(r + HAZ);
                _rightbottom.setY(_nOffsetY + h2 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop);
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2(_lefttop , _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w3);
                    _pos[1].setY(_nOffsetY + h3);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-w3 - HAZ);
                    _pos[3].setY(_nOffsetY + h3);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, (180+b), e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.arcTo( rectangle1, 180+b, e);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, 180+b, e);
                    HAZpath.arcTo( rectangle1, 180+b+e, -e);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX( w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX( w3);
                    _pos[1].setY(_nOffsetY + h3);
                    _pos[2].setX( w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX( w3 + HAZ);
                    _pos[3].setY(_nOffsetY + h3);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, -b, -e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.arcTo( rectangle2, -b, -e);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, -b, -e);
                    HAZpath.arcTo( rectangle, -b-e, e);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }

    }//显示V
    else
    {
        double _xOffset = ( h3 - m_fInterval)*( w1 - w3)/h3 + w3;
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1);
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-_xOffset);
                    _pos[1].setY(_nOffsetY - m_fInterval);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-_xOffset - HAZ);
                    _pos[3].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(_xOffset);
                    _pos[1].setY(_nOffsetY - m_fInterval);
                    _pos[2].setX(w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(_xOffset + HAZ);
                    _pos[3].setY(_nOffsetY - m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-_xOffset);
                    _pos[1].setY(_nOffsetY + m_fInterval);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-_xOffset - HAZ);
                    _pos[3].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(_xOffset);
                    _pos[1].setY(_nOffsetY + m_fInterval);
                    _pos[2].setX(w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(_xOffset + HAZ);
                    _pos[3].setY(_nOffsetY + m_fInterval);

                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }
}

void DopplerViewItems::DrawWeldDiffDV(QPainterPath &path)
{
    QPointF _pos[4] ;
    double _fStartV , _fStopV ,_fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    int _nStart = _fStartV / m_fInterval ;
    int _nStop  = _fStopV  / m_fInterval + 1;
    for(int i = _nStart ; i < _nStop ; i++)
    {
        if(i%2)
        {
            double _nOffsetY = m_fInterval * ( i + 1) ;
            double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height ;
            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
            {
                _pos[0].setX(-_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(-m_cPart.weld.weland_offset);
                _pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
                _pos[2].setX(-m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);
                _pos[3].setX(-m_cPart.weld.weland_offset - tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height -m_cPart.weld.fizone_down_height - m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
            {
                _pos[0].setX(_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(m_cPart.weld.weland_offset);
                _pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
                _pos[2].setX(m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);
                _pos[3].setX(m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.fizone_down_height - m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }
        }else{
            double _nOffsetY = m_fInterval * i ;
            double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height ;
            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
            {
                _pos[0].setX(-_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(-m_cPart.weld.weland_offset);
                _pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
                _pos[2].setX(-m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);
                _pos[3].setX(-m_cPart.weld.weland_offset - tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.fizone_down_height + m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
            {
                _pos[0].setX(_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(m_cPart.weld.weland_offset);
                _pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
                _pos[2].setX(m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);
                _pos[3].setX(m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.fizone_down_height + m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }
        }
    }
}

void DopplerViewItems::DrawWeldJ(QPainterPath &path)
{
    if(m_cPart.weld.weland_offset >= m_cPart.weld.fizone_radius )
    {
        DrawWeldV(path) ;
        return ;
    }

    QPointF _pos[5] ;
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double _fFizoneAngle = DEGREE_TO_ARCH(m_cPart.weld.fizone_angle) ;
    double _nTmpY2 = sin(_fFizoneAngle) * m_cPart.weld.fizone_radius  ;
    double _nTmpY1 = sqrt(m_cPart.weld.fizone_radius * m_cPart.weld.fizone_radius - m_cPart.weld.weland_offset * m_cPart.weld.weland_offset );
    if(_nTmpY2 > _nTmpY1)
    {
        DrawWeldV( path ) ;
        return ;
    }
    double _fPosX = cos(_fFizoneAngle) * m_cPart.weld.fizone_radius  ;
    double _fPosY = m_cPart.weld.fizone_height - _nTmpY1 + _nTmpY2   ;

    double _fAngleStart = m_cPart.weld.fizone_angle + 180 ;
    double _asine = ARCH_TO_DEGREE(asin(m_cPart.weld.weland_offset / m_cPart.weld.fizone_radius)) ;
    double _fAngleStop   = 270  - _asine  - _fAngleStart	 ;
    double _fAngleStart1 = 180  - _fAngleStart - _fAngleStop ;

    int _nStart = _fStartV / m_fInterval ;
    int _nStop  = _fStopV  / m_fInterval + 1;
    for(int i = _nStart ; i < _nStop  ; i++)
    {
        if(i%2)
        {
            double _nOffsetY = m_fInterval * (i+1) ;
            QPointF _lefttop , _rightbottom;
            _lefttop.setX(-m_cPart.weld.fizone_radius);
            _lefttop.setY(_nOffsetY - m_cPart.weld.fizone_height + _nTmpY1 + m_cPart.weld.fizone_radius);
            _rightbottom.setX(m_cPart.weld.fizone_radius);
            _rightbottom.setY(_nOffsetY - m_cPart.weld.fizone_height + _nTmpY1 - m_cPart.weld.fizone_radius);
            _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
            _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom) ;
            QRectF rectangle(_lefttop , _rightbottom);

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
            {
                _pos[0].setX(-_fPosX - tan(_fFizoneAngle) * _fPosY);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(-_fPosX);
                _pos[1].setY(_nOffsetY - _fPosY);
                _pos[2].setX(-m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height);
                _pos[3].setX(-m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

                _pos[4].setX(-m_cPart.weld.weland_offset - tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[4].setY(_nOffsetY - m_cPart.weld.fizone_down_height - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.arcTo( rectangle , _fAngleStart , _fAngleStop);
                path.moveTo(_pos[2]);
                path.lineTo(_pos[3]);
                path.lineTo(_pos[4]);
            }

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
            {
                _pos[0].setX(_fPosX + tan(_fFizoneAngle) * _fPosY);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(_fPosX);
                _pos[1].setY(_nOffsetY - _fPosY);
                _pos[2].setX(m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height);
                _pos[3].setX(m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

                _pos[4].setX(m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[4].setY(_nOffsetY - m_cPart.weld.fizone_down_height - m_cPart.weld.fizone_height - m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;

                path.moveTo(_pos[4]);
                path.lineTo(_pos[3]);
                path.lineTo(_pos[2]);
                path.arcTo(rectangle , _fAngleStart1 , _fAngleStop);
                path.moveTo(_pos[1]);
                path.lineTo(_pos[0]);
            }
        }else{
            double _nOffsetY = m_fInterval * i ;
            QPointF _lefttop , _rightbottom;
            _lefttop.setX(-m_cPart.weld.fizone_radius);
            _lefttop.setY(_nOffsetY + m_cPart.weld.fizone_height - _nTmpY1 - m_cPart.weld.fizone_radius);
            _rightbottom.setX(m_cPart.weld.fizone_radius);
            _rightbottom.setY(_nOffsetY + m_cPart.weld.fizone_height - _nTmpY1 + m_cPart.weld.fizone_radius);
            _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
            _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom) ;
            QRectF rectangle(_lefttop , _rightbottom);

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
            {
                _pos[0].setX(-_fPosX - tan(_fFizoneAngle) * _fPosY);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(-_fPosX);
                _pos[1].setY(_nOffsetY + _fPosY);
                _pos[2].setX(-m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height);
                _pos[3].setX(-m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

                _pos[4].setX(-m_cPart.weld.weland_offset - tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[4].setY(_nOffsetY + m_cPart.weld.fizone_down_height + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.arcTo(rectangle , _fAngleStart , _fAngleStop);
                path.moveTo(_pos[2]);
                path.lineTo(_pos[3]);
                path.lineTo(_pos[4]);
            }

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
            {
                _pos[0].setX(_fPosX + tan(_fFizoneAngle) * _fPosY);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(_fPosX);
                _pos[1].setY(_nOffsetY + _fPosY);
                _pos[2].setX(m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height);
                _pos[3].setX(m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

                _pos[4].setX(m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[4].setY(_nOffsetY + m_cPart.weld.fizone_down_height + m_cPart.weld.fizone_height + m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;

                path.moveTo(_pos[4]);
                path.lineTo(_pos[3]);
                path.lineTo(_pos[2]);
                path.arcTo(rectangle , _fAngleStart1 , _fAngleStop);
                path.moveTo(_pos[1]);
                path.lineTo(_pos[0]);
            }
        }
    }
}

void DopplerViewItems::DrawWeldVY(QPainterPath &path)
{
    QPointF _pos[4] ;
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    int _nStart = _fStartV / m_fInterval ;
    int _nStop  = _fStopV  / m_fInterval + 1;
    for(int i = _nStart ; i < _nStop ; i++)
    {
        if(i%2)
        {
            double _nOffsetY = m_fInterval * ( i + 1) ;
            double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height
                              + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height;
            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
            {
                _pos[0].setX(-_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(-m_cPart.weld.weland_offset - tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
                _pos[2].setX(-m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.fizone_down_height);
                _pos[3].setX(-m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.fizone_down_height - m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
            {
                _pos[0].setX(_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[1].setY(_nOffsetY - m_cPart.weld.fizone_height);
                _pos[2].setX(m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.fizone_down_height);
                _pos[3].setX(m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY - m_cPart.weld.fizone_height - m_cPart.weld.fizone_down_height - m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }
        }else{
            double _nOffsetY = m_fInterval * i ;
            double _fTmpPosX1 = m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)) * m_cPart.weld.fizone_height
                              + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height;
            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_LEFT )
            {
                _pos[0].setX(-_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(-m_cPart.weld.weland_offset - tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
                _pos[2].setX(-m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.fizone_down_height);
                _pos[3].setX(-m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.fizone_down_height + m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }

            if(m_cPart.weld.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld.eSymmetry == setup_WELD_RIGHT )
            {
                _pos[0].setX(_fTmpPosX1);
                _pos[0].setY(_nOffsetY);
                _pos[1].setX(m_cPart.weld.weland_offset + tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_down_angle)) * m_cPart.weld.fizone_down_height);
                _pos[1].setY(_nOffsetY + m_cPart.weld.fizone_height);
                _pos[2].setX(m_cPart.weld.weland_offset);
                _pos[2].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.fizone_down_height);
                _pos[3].setX(m_cPart.weld.weland_offset);
                _pos[3].setY(_nOffsetY + m_cPart.weld.fizone_height + m_cPart.weld.fizone_down_height + m_cPart.weld.weland_height);

                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
            }
        }
    }
}

void  DopplerViewItems::DrawWeldVYDataII(QPainterPath& path, QPainterPath& HAZpath)
{
    QPointF _pos[8] ;
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double w1 = m_cPart.weld_ii.VY.w1;
    double h1 = m_cPart.weld_ii.VY.h1;
    double w2 = m_cPart.weld_ii.VY.w2;
    double h2 = m_cPart.weld_ii.VY.h2;
    double w3 = m_cPart.weld_ii.VY.w3;
    double HAZ = m_cPart.weld_ii.eHAZ;

    int _nStart = _fStartV / m_fInterval ;
    int _nStop  = _fStopV  / m_fInterval + 1;
    //显示VY
    if( h1 + h2 < m_fInterval)
    {
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1);
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w2);
                    _pos[1].setY(_nOffsetY - h1);
                    _pos[2].setX(-w3);
                    _pos[2].setY(_nOffsetY - h1 - h2);
                    _pos[3].setX(-w3);
                    _pos[3].setY(_nOffsetY - m_fInterval);                    
                    _pos[4].setX(-w1 - HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(-w2 - HAZ);
                    _pos[5].setY(_nOffsetY - h1);
                    _pos[6].setX(-w3 - HAZ);
                    _pos[6].setY(_nOffsetY - h1 - h2);
                    _pos[7].setX(-w3 - HAZ);
                    _pos[7].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);

                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w2);
                    _pos[1].setY(_nOffsetY - h1);
                    _pos[2].setX(w3);
                    _pos[2].setY(_nOffsetY - h1 - h2);
                    _pos[3].setX(w3);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[4].setX(w1 + HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(w2 + HAZ);
                    _pos[5].setY(_nOffsetY - h1);
                    _pos[6].setX(w3 + HAZ);
                    _pos[6].setY(_nOffsetY - h1 - h2);
                    _pos[7].setX(w3 + HAZ);
                    _pos[7].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w2);
                    _pos[1].setY(_nOffsetY + h1);
                    _pos[2].setX(-w3);
                    _pos[2].setY(_nOffsetY + h1 + h2);
                    _pos[3].setX(-w3);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[4].setX(-w1 - HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(-w2 - HAZ);
                    _pos[5].setY(_nOffsetY + h1);
                    _pos[6].setX(-w3 - HAZ);
                    _pos[6].setY(_nOffsetY + h1 + h2);
                    _pos[7].setX(-w3 - HAZ);
                    _pos[7].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w2);
                    _pos[1].setY(_nOffsetY + h1);
                    _pos[2].setX(w3);
                    _pos[2].setY(_nOffsetY + h1 + h2);
                    _pos[3].setX(w3);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[4].setX(w1 + HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(w2 + HAZ);
                    _pos[5].setY(_nOffsetY + h1);
                    _pos[6].setX(w3 + HAZ);
                    _pos[6].setY(_nOffsetY + h1 + h2);
                    _pos[7].setX(w3 + HAZ);
                    _pos[7].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }//显示VV
    else if( h1 < m_fInterval)
    {
        double _xOffset = ( h2 - m_fInterval + h1)*( w2 - w3)/h2 + w3;
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1);
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w2);
                    _pos[1].setY(_nOffsetY - h1);
                    _pos[2].setX(-_xOffset);
                    _pos[2].setY(_nOffsetY - m_fInterval);
                    _pos[3].setX(-w1 - HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(-w2 - HAZ);
                    _pos[4].setY(_nOffsetY - h1);
                    _pos[5].setX(-_xOffset - HAZ);
                    _pos[5].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w2);
                    _pos[1].setY(_nOffsetY - h1);
                    _pos[2].setX(_xOffset);
                    _pos[2].setY(_nOffsetY - m_fInterval);
                    _pos[3].setX(w1 + HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(w2 + HAZ);
                    _pos[4].setY(_nOffsetY - h1);
                    _pos[5].setX(_xOffset + HAZ);
                    _pos[5].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w2);
                    _pos[1].setY(_nOffsetY + h1);
                    _pos[2].setX(-_xOffset);
                    _pos[2].setY(_nOffsetY + m_fInterval);
                    _pos[3].setX(-w1 - HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(-w2 - HAZ);
                    _pos[4].setY(_nOffsetY + h1);
                    _pos[5].setX(-_xOffset - HAZ);
                    _pos[5].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w2);
                    _pos[1].setY(_nOffsetY + h1);
                    _pos[2].setX(_xOffset);
                    _pos[2].setY(_nOffsetY + m_fInterval);
                    _pos[3].setX(w1 + HAZ);
                    _pos[3].setY(_nOffsetY);
                    _pos[4].setX(w2 + HAZ);
                    _pos[4].setY(_nOffsetY + h1);
                    _pos[5].setX(_xOffset + HAZ);
                    _pos[5].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.moveTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }//显示V
    else
    {
        double _xOffset = ( h1 - m_fInterval)*( w1 - w2)/h1 + w2;
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1);
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-_xOffset);
                    _pos[1].setY(_nOffsetY - m_fInterval);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-_xOffset - HAZ);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(_xOffset);
                    _pos[1].setY(_nOffsetY - m_fInterval);
                    _pos[2].setX(w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(_xOffset + HAZ);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-_xOffset);
                    _pos[1].setY(_nOffsetY + m_fInterval);
                    _pos[2].setX(-w1 - HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(-_xOffset - HAZ);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(_xOffset);
                    _pos[1].setY(_nOffsetY + m_fInterval);
                    _pos[2].setX(w1 + HAZ);
                    _pos[2].setY(_nOffsetY);
                    _pos[3].setX(_xOffset + HAZ);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }
}

void DopplerViewItems::DrawWeldVVDataII(QPainterPath& path, QPainterPath& HAZpath)
{
    QPointF _pos[8];
    double _fStartV, _fStopV, _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange( &_fStartV, &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT);
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double w1 = m_cPart.weld_ii.VV.w1;
    double h1 = m_cPart.weld_ii.VV.h1;
    double w2 = m_cPart.weld_ii.VV.w2;
    double h2 = m_cPart.weld_ii.VV.h2;
    double w3 = m_cPart.weld_ii.VV.w3;
    double HAZ = m_cPart.weld_ii.eHAZ;

    int _nStart = _fStartV / m_fInterval ;
    int _nStop  = _fStopV  / m_fInterval + 1;

    //if( h1 + h2 < m_fInterval)
    {
        for(int i = _nStart ; i < _nStop ; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * ( i + 1);
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w2);
                    _pos[1].setY(_nOffsetY - h1);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY - m_fInterval + h2);
                    _pos[3].setX(-w3);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[4].setX(-w1 - HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(-w2 - HAZ);
                    _pos[5].setY(_nOffsetY - h1);
                    _pos[6].setX(-w2 - HAZ);
                    _pos[6].setY(_nOffsetY - m_fInterval + h2);
                    _pos[7].setX(-w3 - HAZ);
                    _pos[7].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w2);
                    _pos[1].setY(_nOffsetY - h1);
                    _pos[2].setX(w2);
                    _pos[2].setY(_nOffsetY - m_fInterval + h2);
                    _pos[3].setX(w3);
                    _pos[3].setY(_nOffsetY - m_fInterval);
                    _pos[4].setX(w1 + HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(w2 + HAZ);
                    _pos[5].setY(_nOffsetY - h1);
                    _pos[6].setX(w2 + HAZ);
                    _pos[6].setY(_nOffsetY - m_fInterval + h2);
                    _pos[7].setX(w3 + HAZ);
                    _pos[7].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w2);
                    _pos[1].setY(_nOffsetY + h1);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY + m_fInterval - h2);
                    _pos[3].setX(-w3);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[4].setX(-w1 - HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(-w2 - HAZ);
                    _pos[5].setY(_nOffsetY + h1);
                    _pos[6].setX(-w2 - HAZ);
                    _pos[6].setY(_nOffsetY + m_fInterval - h2);
                    _pos[7].setX(-w3 - HAZ);
                    _pos[7].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w2);
                    _pos[1].setY(_nOffsetY + h1);
                    _pos[2].setX(w2);
                    _pos[2].setY(_nOffsetY + m_fInterval - h2);
                    _pos[3].setX(w3);
                    _pos[3].setY(_nOffsetY + m_fInterval);
                    _pos[4].setX(w1 + HAZ);
                    _pos[4].setY(_nOffsetY);
                    _pos[5].setX(w2 + HAZ);
                    _pos[5].setY(_nOffsetY + h1);
                    _pos[6].setX(w2 + HAZ);
                    _pos[6].setY(_nOffsetY + m_fInterval - h2);
                    _pos[7].setX(w3 + HAZ);
                    _pos[7].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.lineTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[4]);
                    path.lineTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.lineTo(_pos[2]);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }
//    else
//    {

//    }
}

void  DopplerViewItems::DrawWeldUUDataII(QPainterPath& path, QPainterPath& HAZpath)
{
    if( m_cPart.weld_ii.UU.w2 >= m_cPart.weld_ii.UU.r1 && m_cPart.weld_ii.UU.w2 >= m_cPart.weld_ii.UU.r2)
    {
        DrawWeldVVDataII( path, HAZpath);
        return;
    }
    QPointF _pos[12];
    double _fStartV, _fStopV, _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange( &_fStartV, &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT);
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double w1 = m_cPart.weld_ii.UU.w1;
    double h1 = m_cPart.weld_ii.UU.h1;
    double r1 = m_cPart.weld_ii.UU.r1;
    double w2 = m_cPart.weld_ii.UU.w2;
    double h2 = m_cPart.weld_ii.UU.h2;
    double r2 = m_cPart.weld_ii.UU.r2;
    double w3 = m_cPart.weld_ii.UU.w3;
    double HAZ = m_cPart.weld_ii.eHAZ;
    double h3 =  sqrt(pow(r1,2) - pow(w2,2));
    double h4 = h1 - h3;
    double l1 = sqrt(pow(w1,2) + pow(h4,2));
    double l2 = sqrt(pow(l1,2) - pow(r1,2));
    double angle1 = atan(h4 / w1);
    double angle2 = atan(r1 / l2);
    double h5 = l2 * sin(angle1 + angle2);
    double w4 = w1 - l2 * cos(angle1 + angle2);
    angle1  = M_PI/2  - (angle1 + angle2);
    angle2 = asin(w2 / r1);
    int a1 = (int)(angle1 * 180 / M_PI);
    int a2 = (90 - a1 - (int)(angle2 * 180 / M_PI));
    double h6 = sqrt(pow(r2, 2) - pow(w2, 2));
    double h7 = h2 - h6;
    double l3 = sqrt(pow(w3, 2) + pow(h7, 2));
    double l4 = sqrt(pow(l3, 2) - pow(r2, 2));
    double angle3 = atan(h7 / w3);
    double angle4 = atan(r2 / l4);
    double h8 = l4 * sin(angle3 + angle4);
    double w5 = w3 - l4 * cos(angle3 + angle4);
    angle3 = M_PI/2 - (angle3 + angle4);
    angle4 = asin(w2 / r2);
    int a3 = (int)(angle3 * 180 / M_PI);
    int a4 = (90 - a3 - (int)(angle4 * 180 / M_PI));

    int _nStart = _fStartV / m_fInterval;
    int _nStop  = _fStopV  / m_fInterval + 1;
    //if( h1 + h2 < m_fInterval)
    {
        for(int i = _nStart; i < _nStop; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * (i+1);
                QPointF _lefttop, _rightbottom;
                _lefttop.setX(-r1);
                _lefttop.setY(_nOffsetY - h4 + r1);
                _rightbottom.setX(r1);
                _rightbottom.setY(_nOffsetY - h4 - r1);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1( _lefttop, _rightbottom);

                _lefttop.setX(-r1 - HAZ);
                _lefttop.setY(_nOffsetY - h4 + r1);
                _rightbottom.setX(r1 - HAZ);
                _rightbottom.setY(_nOffsetY - h4 - r1);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle11( _lefttop, _rightbottom);

                _lefttop.setX(-r1 + HAZ);
                _lefttop.setY(_nOffsetY - h4 + r1);
                _rightbottom.setX(r1 + HAZ);
                _rightbottom.setY(_nOffsetY - h4 - r1);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle12( _lefttop, _rightbottom);

                _lefttop.setX(-r2);
                _lefttop.setY(_nOffsetY - m_fInterval + h7 + r2);
                _rightbottom.setX(r2);
                _rightbottom.setY(_nOffsetY - m_fInterval + h7 - r2);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2( _lefttop, _rightbottom);

                _lefttop.setX(-r2 - HAZ);
                _lefttop.setY(_nOffsetY - m_fInterval + h7 + r2);
                _rightbottom.setX(r2 - HAZ);
                _rightbottom.setY(_nOffsetY - m_fInterval + h7 - r2);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle21( _lefttop, _rightbottom);

                _lefttop.setX(-r2 + HAZ);
                _lefttop.setY(_nOffsetY - m_fInterval + h7 + r2);
                _rightbottom.setX(r2 + HAZ);
                _rightbottom.setY(_nOffsetY - m_fInterval + h7 - r2);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle22( _lefttop, _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w4);
                    _pos[1].setY(_nOffsetY - h5);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY - h1);
                    _pos[3].setX(-w2);
                    _pos[3].setY(_nOffsetY - m_fInterval + h2);
                    _pos[4].setX(-w5);
                    _pos[4].setY(_nOffsetY - m_fInterval + h8);
                    _pos[5].setX(-w3);
                    _pos[5].setY(_nOffsetY - m_fInterval);                    
                    _pos[6].setX(-w1 - HAZ);
                    _pos[6].setY(_nOffsetY);
                    _pos[7].setX(-w4 - HAZ);
                    _pos[7].setY(_nOffsetY - h5);
                    _pos[8].setX(-w2 - HAZ);
                    _pos[8].setY(_nOffsetY - h1);
                    _pos[9].setX(-w2 - HAZ);
                    _pos[9].setY(_nOffsetY - m_fInterval + h2);
                    _pos[10].setX(-w5 - HAZ);
                    _pos[10].setY(_nOffsetY - m_fInterval + h8);
                    _pos[11].setX(-w3 - HAZ);
                    _pos[11].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    _pos[10] = m_pDataView->TranslateToScenePlan(&_pos[10]);
                    _pos[11] = m_pDataView->TranslateToScenePlan(&_pos[11]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle1, 180+a1, a2);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[4]);
                    path.arcTo( rectangle2, 180-a3, -a4);                    
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    path.arcTo( rectangle11, 180+a1, a2);
                    path.moveTo(_pos[8]);
                    path.lineTo(_pos[9]);
                    path.moveTo(_pos[11]);
                    path.lineTo(_pos[10]);
                    path.arcTo( rectangle21, 180-a3, -a4);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle1, 180+a1, a2);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.arcTo( rectangle2, 180-a3-a4, a4);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[11]);
                    HAZpath.lineTo(_pos[10]);
                    HAZpath.arcTo( rectangle21, 180-a3, -a4);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.arcTo( rectangle11, 180+a1+a2, -a2);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[0]);

                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w4);
                    _pos[1].setY(_nOffsetY - h5);
                    _pos[2].setX(w2);
                    _pos[2].setY(_nOffsetY - h1);
                    _pos[3].setX(w2);
                    _pos[3].setY(_nOffsetY - m_fInterval + h2);
                    _pos[4].setX(w5);
                    _pos[4].setY(_nOffsetY - m_fInterval + h8);
                    _pos[5].setX(w3);
                    _pos[5].setY(_nOffsetY - m_fInterval);
                    _pos[6].setX(w1 + HAZ);
                    _pos[6].setY(_nOffsetY);
                    _pos[7].setX(w4 + HAZ);
                    _pos[7].setY(_nOffsetY - h5);
                    _pos[8].setX(w2 + HAZ);
                    _pos[8].setY(_nOffsetY - h1);
                    _pos[9].setX(w2 + HAZ);
                    _pos[9].setY(_nOffsetY - m_fInterval + h2);
                    _pos[10].setX(w5 + HAZ);
                    _pos[10].setY(_nOffsetY - m_fInterval + h8);
                    _pos[11].setX(w3 + HAZ);
                    _pos[11].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    _pos[10] = m_pDataView->TranslateToScenePlan(&_pos[10]);
                    _pos[11] = m_pDataView->TranslateToScenePlan(&_pos[11]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle1, -a1, -a2);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[4]);
                    path.arcTo( rectangle2, a3, a4);                    
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    path.arcTo( rectangle12, -a1, -a2);
                    path.moveTo(_pos[8]);
                    path.lineTo(_pos[9]);
                    path.moveTo(_pos[11]);
                    path.lineTo(_pos[10]);
                    path.arcTo( rectangle22, a3, a4);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle1, -a1, -a2);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.arcTo( rectangle2, a3+a4, -a4);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[11]);
                    HAZpath.lineTo(_pos[10]);
                    HAZpath.arcTo( rectangle22, a3, a4);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.arcTo( rectangle12, -a1-a2, a2);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                QPointF _lefttop, _rightbottom;
                _lefttop.setX(-r1);
                _lefttop.setY(_nOffsetY + h4 - r1);
                _rightbottom.setX(r1);
                _rightbottom.setY(_nOffsetY + h4 + r1);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1( _lefttop, _rightbottom);

                _lefttop.setX(-r1 - HAZ);
                _lefttop.setY(_nOffsetY + h4 - r1);
                _rightbottom.setX(r1 - HAZ);
                _rightbottom.setY(_nOffsetY + h4 + r1);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle11( _lefttop, _rightbottom);

                _lefttop.setX(-r1 + HAZ);
                _lefttop.setY(_nOffsetY + h4 - r1);
                _rightbottom.setX(r1 + HAZ);
                _rightbottom.setY(_nOffsetY + h4 + r1);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle12( _lefttop, _rightbottom);

                _lefttop.setX(-r2);
                _lefttop.setY(_nOffsetY + m_fInterval - h7 - r2);
                _rightbottom.setX(r2);
                _rightbottom.setY(_nOffsetY + m_fInterval - h7 + r2);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2( _lefttop, _rightbottom);

                _lefttop.setX(-r2 - HAZ);
                _lefttop.setY(_nOffsetY + m_fInterval - h7 - r2);
                _rightbottom.setX(r2 - HAZ);
                _rightbottom.setY(_nOffsetY + m_fInterval - h7 + r2);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle21( _lefttop, _rightbottom);

                _lefttop.setX(-r2 + HAZ);
                _lefttop.setY(_nOffsetY + m_fInterval - h7 - r2);
                _rightbottom.setX(r2 + HAZ);
                _rightbottom.setY(_nOffsetY + m_fInterval - h7 + r2);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle22( _lefttop, _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w4);
                    _pos[1].setY(_nOffsetY + h5);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY + h1);
                    _pos[3].setX(-w2);
                    _pos[3].setY(_nOffsetY + m_fInterval - h2);
                    _pos[4].setX(-w5);
                    _pos[4].setY(_nOffsetY + m_fInterval - h8);
                    _pos[5].setX(-w3);
                    _pos[5].setY(_nOffsetY + m_fInterval);
                    _pos[6].setX(-w1 - HAZ);
                    _pos[6].setY(_nOffsetY);
                    _pos[7].setX(-w4 - HAZ);
                    _pos[7].setY(_nOffsetY + h5);
                    _pos[8].setX(-w2 - HAZ);
                    _pos[8].setY(_nOffsetY + h1);
                    _pos[9].setX(-w2 - HAZ);
                    _pos[9].setY(_nOffsetY + m_fInterval - h2);
                    _pos[10].setX(-w5 - HAZ);
                    _pos[10].setY(_nOffsetY + m_fInterval - h8);
                    _pos[11].setX(-w3 - HAZ);
                    _pos[11].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    _pos[10] = m_pDataView->TranslateToScenePlan(&_pos[10]);
                    _pos[11] = m_pDataView->TranslateToScenePlan(&_pos[11]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle1, 180+a1, a2);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[4]);
                    path.arcTo( rectangle2, 180-a3, -a4);
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    path.arcTo( rectangle11, 180+a1, a2);
                    path.moveTo(_pos[8]);
                    path.lineTo(_pos[9]);
                    path.moveTo(_pos[11]);
                    path.lineTo(_pos[10]);
                    path.arcTo( rectangle21, 180-a3, -a4);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle1, 180+a1, a2);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.arcTo( rectangle2, 180-a3-a4, a4);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[11]);
                    HAZpath.lineTo(_pos[10]);
                    HAZpath.arcTo( rectangle21, 180-a3, -a4);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.arcTo( rectangle11, 180+a1+a2, -a2);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w4);
                    _pos[1].setY(_nOffsetY + h5);
                    _pos[2].setX(w2);
                    _pos[2].setY(_nOffsetY + h1);
                    _pos[3].setX(w2);
                    _pos[3].setY(_nOffsetY + m_fInterval - h2);
                    _pos[4].setX(w5);
                    _pos[4].setY(_nOffsetY + m_fInterval - h8);
                    _pos[5].setX(w3);
                    _pos[5].setY(_nOffsetY + m_fInterval);                    
                    _pos[6].setX(w1 + HAZ);
                    _pos[6].setY(_nOffsetY);
                    _pos[7].setX(w4 + HAZ);
                    _pos[7].setY(_nOffsetY + h5);
                    _pos[8].setX(w2 + HAZ);
                    _pos[8].setY(_nOffsetY + h1);
                    _pos[9].setX(w2 + HAZ);
                    _pos[9].setY(_nOffsetY + m_fInterval - h2);
                    _pos[10].setX(w5 + HAZ);
                    _pos[10].setY(_nOffsetY + m_fInterval - h8);
                    _pos[11].setX(w3 + HAZ);
                    _pos[11].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    _pos[10] = m_pDataView->TranslateToScenePlan(&_pos[10]);
                    _pos[11] = m_pDataView->TranslateToScenePlan(&_pos[11]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle1, -a1, -a2);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[4]);
                    path.arcTo( rectangle2, a3, a4);
                    path.moveTo(_pos[6]);
                    path.lineTo(_pos[7]);
                    path.arcTo( rectangle12, -a1, -a2);
                    path.moveTo(_pos[8]);
                    path.lineTo(_pos[9]);
                    path.moveTo(_pos[11]);
                    path.lineTo(_pos[10]);
                    path.arcTo( rectangle22, a3, a4);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle1, -a1, -a2);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.arcTo( rectangle2, a3+a4, -a4);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[11]);
                    HAZpath.lineTo(_pos[10]);
                    HAZpath.arcTo( rectangle22, a3, a4);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.arcTo( rectangle12, -a1-a2, a2);
                    HAZpath.lineTo(_pos[6]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }
}

void  DopplerViewItems::DrawWeldUVDataII(QPainterPath& path, QPainterPath& HAZpath)
{
    if( m_cPart.weld_ii.UV.w2 >= m_cPart.weld_ii.UV.r)
    {
        DrawWeldVVDataII( path, HAZpath);
        return;
    }
    QPointF _pos[10];
    double _fStartV, _fStopV, _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange( &_fStartV, &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT);
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double w1 = m_cPart.weld_ii.UV.w1;
    double h1 = m_cPart.weld_ii.UV.h1;
    double r  = m_cPart.weld_ii.UV.r;
    double w2 = m_cPart.weld_ii.UV.w2;
    double h2 = m_cPart.weld_ii.UV.h2;
    double w3 = m_cPart.weld_ii.UV.w3;
    double HAZ = m_cPart.weld_ii.eHAZ;
    double h3 =  sqrt(pow(r,2) - pow(w2,2));
    double h4 = h1 - h3;
    double l1 = sqrt(pow(w1,2) + pow(h4,2));
    double l2 = sqrt(pow(l1,2) - pow(r,2));
    double angle1 = atan(h4 / w1);
    double angle2 = atan(r / l2);
    double h5 = l2 * sin(angle1 + angle2);
    double w4 = w1 - l2 * cos(angle1 + angle2);
    angle1  = M_PI/2  - (angle1 + angle2);
    angle2 = asin(w2 / r);
    int b = (int)(angle1 * 180 / M_PI);
    int e = (90 - b - (int)(angle2 * 180 / M_PI));

    int _nStart = _fStartV / m_fInterval;
    int _nStop  = _fStopV  / m_fInterval + 1;
    //if( h1 + h2 < m_fInterval)
    {
        for(int i = _nStart; i < _nStop; i++)
        {
            if(i%2)
            {
                double _nOffsetY = m_fInterval * (i+1);
                QPointF _lefttop , _rightbottom;
                _lefttop.setX(-r);
                _lefttop.setY(_nOffsetY - h4 + r);
                _rightbottom.setX(r);
                _rightbottom.setY(_nOffsetY - h4 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle( _lefttop, _rightbottom);

                _lefttop.setX(-r - HAZ);
                _lefttop.setY(_nOffsetY - h4 + r);
                _rightbottom.setX(r - HAZ);
                _rightbottom.setY(_nOffsetY - h4 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1( _lefttop, _rightbottom);

                _lefttop.setX(-r + HAZ);
                _lefttop.setY(_nOffsetY - h4 + r);
                _rightbottom.setX(r + HAZ);
                _rightbottom.setY(_nOffsetY - h4 - r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2( _lefttop, _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w4);
                    _pos[1].setY(_nOffsetY - h5);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY - h1);
                    _pos[3].setX(-w2);
                    _pos[3].setY(_nOffsetY - m_fInterval + h2);
                    _pos[4].setX(-w3);
                    _pos[4].setY(_nOffsetY - m_fInterval);
                    _pos[5].setX(-w1 - HAZ);
                    _pos[5].setY(_nOffsetY);
                    _pos[6].setX(-w4 - HAZ);
                    _pos[6].setY(_nOffsetY - h5);
                    _pos[7].setX(-w2 - HAZ);
                    _pos[7].setY(_nOffsetY - h1);
                    _pos[8].setX(-w2 - HAZ);
                    _pos[8].setY(_nOffsetY - m_fInterval + h2);
                    _pos[9].setX(-w3 - HAZ);
                    _pos[9].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, 180+b, e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.arcTo( rectangle1, 180+b, e);
                    path.moveTo(_pos[7]);
                    path.lineTo(_pos[8]);
                    path.lineTo(_pos[9]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, 180+b, e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[9]);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.arcTo( rectangle1, 180+b+e, -e);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w4);
                    _pos[1].setY(_nOffsetY - h5);
                    _pos[2].setX(w2);
                    _pos[2].setY(_nOffsetY - h1);
                    _pos[3].setX(w2);
                    _pos[3].setY(_nOffsetY - m_fInterval + h2);
                    _pos[4].setX(w3);
                    _pos[4].setY(_nOffsetY - m_fInterval);
                    _pos[5].setX(w1 + HAZ);
                    _pos[5].setY(_nOffsetY);
                    _pos[6].setX(w4 + HAZ);
                    _pos[6].setY(_nOffsetY - h5);
                    _pos[7].setX(w2 + HAZ);
                    _pos[7].setY(_nOffsetY - h1);
                    _pos[8].setX(w2 + HAZ);
                    _pos[8].setY(_nOffsetY - m_fInterval + h2);
                    _pos[9].setX(w3 + HAZ);
                    _pos[9].setY(_nOffsetY - m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, -b, -e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.arcTo( rectangle2, -b, -e);
                    path.moveTo(_pos[7]);
                    path.lineTo(_pos[8]);
                    path.lineTo(_pos[9]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, -b, -e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[9]);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.arcTo( rectangle2, -b-e, e);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
            else
            {
                double _nOffsetY = m_fInterval * i;
                QPointF _lefttop , _rightbottom;
                _lefttop.setX(-r);
                _lefttop.setY(_nOffsetY + h4 - r);
                _rightbottom.setX(r);
                _rightbottom.setY(_nOffsetY + h4 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle( _lefttop, _rightbottom);

                _lefttop.setX(-r - HAZ);
                _lefttop.setY(_nOffsetY + h4 - r);
                _rightbottom.setX(r - HAZ);
                _rightbottom.setY(_nOffsetY + h4 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle1( _lefttop, _rightbottom);

                _lefttop.setX(-r + HAZ);
                _lefttop.setY(_nOffsetY + h4 - r);
                _rightbottom.setX(r + HAZ);
                _rightbottom.setY(_nOffsetY + h4 + r);
                _lefttop = m_pDataView->TranslateToScenePlan(&_lefttop) ;
                _rightbottom = m_pDataView->TranslateToScenePlan(&_rightbottom);
                QRectF rectangle2( _lefttop, _rightbottom);

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_LEFT){
                    _pos[0].setX(-w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(-w4);
                    _pos[1].setY(_nOffsetY + h5);
                    _pos[2].setX(-w2);
                    _pos[2].setY(_nOffsetY + h1);
                    _pos[3].setX(-w2);
                    _pos[3].setY(_nOffsetY + m_fInterval - h2);
                    _pos[4].setX(-w3);
                    _pos[4].setY(_nOffsetY + m_fInterval);
                    _pos[5].setX(-w1 - HAZ);
                    _pos[5].setY(_nOffsetY);
                    _pos[6].setX(-w4 - HAZ);
                    _pos[6].setY(_nOffsetY + h5);
                    _pos[7].setX(-w2 - HAZ);
                    _pos[7].setY(_nOffsetY + h1);
                    _pos[8].setX(-w2 - HAZ);
                    _pos[8].setY(_nOffsetY + m_fInterval - h2);
                    _pos[9].setX(-w3 - HAZ);
                    _pos[9].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, 180+b, e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.arcTo( rectangle1, 180+b, e);
                    path.moveTo(_pos[7]);
                    path.lineTo(_pos[8]);
                    path.lineTo(_pos[9]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, 180+b, e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[9]);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.arcTo( rectangle1, 180+b+e, -e);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[0]);
                }

                if( m_cPart.weld_ii.eSymmetry == setup_WELD_SYMMETRY || m_cPart.weld_ii.eSymmetry == setup_WELD_RIGHT){
                    _pos[0].setX(w1);
                    _pos[0].setY(_nOffsetY);
                    _pos[1].setX(w4);
                    _pos[1].setY(_nOffsetY + h5);
                    _pos[2].setX(w2);
                    _pos[2].setY(_nOffsetY + h1);
                    _pos[3].setX(w2);
                    _pos[3].setY(_nOffsetY + m_fInterval - h2);
                    _pos[4].setX(w3);
                    _pos[4].setY(_nOffsetY + m_fInterval);
                    _pos[5].setX(w1 + HAZ);
                    _pos[5].setY(_nOffsetY);
                    _pos[6].setX(w4 + HAZ);
                    _pos[6].setY(_nOffsetY + h5);
                    _pos[7].setX(w2 + HAZ);
                    _pos[7].setY(_nOffsetY + h1);
                    _pos[8].setX(w2 + HAZ);
                    _pos[8].setY(_nOffsetY + m_fInterval - h2);
                    _pos[9].setX(w3 + HAZ);
                    _pos[9].setY(_nOffsetY + m_fInterval);
                    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
                    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
                    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
                    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
                    _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
                    _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
                    _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
                    _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
                    _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
                    _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
                    path.moveTo(_pos[0]);
                    path.lineTo(_pos[1]);
                    path.arcTo( rectangle, -b, -e);
                    path.moveTo(_pos[2]);
                    path.lineTo(_pos[3]);
                    path.lineTo(_pos[4]);
                    path.moveTo(_pos[5]);
                    path.lineTo(_pos[6]);
                    path.arcTo( rectangle2, -b, -e);
                    path.moveTo(_pos[7]);
                    path.lineTo(_pos[8]);
                    path.lineTo(_pos[9]);

                    HAZpath.moveTo(_pos[0]);
                    HAZpath.lineTo(_pos[1]);
                    HAZpath.arcTo( rectangle, -b, -e);
                    HAZpath.lineTo(_pos[3]);
                    HAZpath.lineTo(_pos[4]);
                    HAZpath.lineTo(_pos[9]);
                    HAZpath.lineTo(_pos[8]);
                    HAZpath.lineTo(_pos[7]);
                    HAZpath.arcTo( rectangle2, -b-e, e);
                    HAZpath.lineTo(_pos[5]);
                    HAZpath.lineTo(_pos[0]);
                }
            }
        }
    }
}

void  DopplerViewItems::DrawWeldTKYDataII(QPainterPath& path)
{
    QPointF _pos[4];
    double _fStartV, _fStopV, _fSliderStartV, _fSliderStopV;
    m_pDataView->GetRulerRange( &_fStartV, &_fStopV, &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT);
    double _fStartH, _fStopH, _fSliderStartH, _fSliderStopH;
    m_pDataView->GetRulerRange( &_fStartH, &_fStopH, &_fSliderStartH, &_fSliderStopH, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double w1 = m_cPart.weld_ii.TKY.w1;
    double w2 = m_cPart.weld_ii.TKY.w2;
    double h1 = m_cPart.weld_ii.TKY.h1;
    double h2 = m_cPart.weld_ii.TKY.h2;
    double a1 = DEGREE_TO_ARCH(m_cPart.weld_ii.TKY.a1);
    double a2 = DEGREE_TO_ARCH(m_cPart.weld_ii.TKY.a2);
    double _btoT = m_cPart.weld_ii.eBottomThinkness;

    switch (m_cPart.weld_ii.eProbePos) {
    case KTY_WED_1:
    {
        if(m_cPart.weld_ii.eAngle == 90){
            DrawWeld90degTKYWeb(w2, h1, h2, a1, a2, _fStartV, _fStopV, _fStartH, path);
        }else{
            DrawWeldTKYWeb( m_cPart.weld_ii.TKY, _fStartV, _fStopV, _fStartH, m_cPart.weld_ii.eAngle, path);
        }
    }
        break;
    case KTY_WED_2:
    {
        if(m_cPart.weld_ii.eAngle == 90){
            DrawWeld90degTKYWeb(w1, h2, h1, a2, a1, _fStartV, _fStopV, _fStartH, path);
        }else{
            WELD_FORMAT_TKY temp_tky;
            temp_tky.w1 = m_cPart.weld_ii.TKY.w2;
            temp_tky.w2 = m_cPart.weld_ii.TKY.w1;
            temp_tky.h1 = m_cPart.weld_ii.TKY.h2;
            temp_tky.h2 = m_cPart.weld_ii.TKY.h1;
            temp_tky.a1 = m_cPart.weld_ii.TKY.a2;
            temp_tky.a2 = m_cPart.weld_ii.TKY.a1;

            double temp_angle = 180 - m_cPart.weld_ii.eAngle;
            DrawWeldTKYWeb( temp_tky, _fStartV, _fStopV, _fStartH, temp_angle, path);
        }
    }
        break;
    case KTY_WING_1:
    case KTY_WING_2:
        DrawWeldTKYPlain(_fStartH, _fStopH, _fStartV, _btoT, path);
        break;
    case KTY_WING_3:
    {
        DrawWeldTKYPlain(_fStartH, _fStopH, _fStartV, _btoT, path);
        if(m_cPart.weld_ii.eAngle == 90){
            DrawWeld90degTKY(w1, w2, h1, h2, a1, a2, _fStartV, _fStopV, path);
        }else{
            DrawWeldTKYWing( m_cPart.weld_ii.TKY, _fStartV, _fStopV, m_cPart.weld_ii.eAngle, path);
        }
    }
        break;
    case KTY_WING_4:
    {
        DrawWeldTKYPlain(_fStartH, _fStopH, _fStartV, _btoT, path);
        if(m_cPart.weld_ii.eAngle == 90){
            DrawWeld90degTKY(w2, w1, h2, h1, a2, a1, _fStartV, _fStopV, path);
        }else{
            WELD_FORMAT_TKY temp_tky;
            temp_tky.w1 = m_cPart.weld_ii.TKY.w2;
            temp_tky.w2 = m_cPart.weld_ii.TKY.w1;
            temp_tky.h1 = m_cPart.weld_ii.TKY.h2;
            temp_tky.h2 = m_cPart.weld_ii.TKY.h1;
            temp_tky.a1 = m_cPart.weld_ii.TKY.a2;
            temp_tky.a2 = m_cPart.weld_ii.TKY.a1;

            double temp_angle = 180 - m_cPart.weld_ii.eAngle;
            DrawWeldTKYWing( temp_tky, _fStartV, _fStopV, temp_angle, path);
        }
    }
        break;
    default:
        break;
    }
}

void DopplerViewItems::DrawWeldASYDataII(QPainterPath &path)
{

    //QPointF _pos[11] ;
    QVector<QPointF>_pos(11);
    double _fStartV , _fStopV , _fSliderStartV, _fSliderStopV;
    double _fStartV2 , _fStopV2 , _fSliderStartV2, _fSliderStopV2;
    double W1= m_cPart.weld_ii.ASY.W1;

    double H1= m_cPart.weld_ii.ASY.H1;
    double W2 = m_cPart.weld_ii.ASY.W2;
    double H2 = m_cPart.weld_ii.ASY.H2;
    double W3=  m_cPart.weld_ii.ASY.W3;

    double T1=m_cPart.weld_ii.ASY.m_thickness;
    double T2=m_cPart.weld_ii.ASY.s_thickness;

    double l1=m_cPart.weld_ii.l1;
    double l2=m_cPart.weld_ii.l2;
    double h1=m_cPart.weld_ii.h1;
    double h2=m_cPart.weld_ii.h2;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV, &_fSliderStopV, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
    //绘制中心线
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    m_pDataView->GetRulerRange(&_fStartV2 , &_fStopV2 , &_fSliderStartV2, &_fSliderStopV2, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;

    if(setup_PLANE_TOP==m_cPart.weld_ii.align)
    {

        // 厚板3个点
        _pos[0].setX(-W1-W3/2);
        _pos[0].setY(h1-h1/l1*W1);
        _pos[1].setX(-W3/2);
        _pos[1].setY(h1-h1/l1*W1+H1);
        _pos[2].setX(-W3/2);
        _pos[2].setY(T1-h2);

        //薄板3个点
        _pos[3].setX(W2+W3/2);
        _pos[3].setY(0);

        _pos[4].setX(W3/2);
        _pos[4].setY(H2);
        _pos[5].setX(W3/2);
        _pos[5].setY(T2);

        //厚板的削边起点
        _pos[6].setX(-W3/2-l1);
        _pos[6].setY(0);

        //厚板的左下端点
        _pos[7].setX(_fStartV2);
        _pos[7].setY(T1);

        //厚板的下削边下端点
        _pos[10].setX(-W3/2-l2);
        _pos[10].setY(T1);

        //薄板的右上边框端点
        _pos[8].setX(_fStopV2);
        _pos[8].setY(0);

        //薄板的右下边框端点
        _pos[9].setX(_fStopV2);
        _pos[9].setY(T2);

        _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
        _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
        _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
        _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
        _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
        _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
        _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
        _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
        _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
        _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
        _pos[10] = m_pDataView->TranslateToScenePlan(&_pos[10]);

        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[5]);
        path.lineTo(_pos[4]);
        path.lineTo(_pos[3]);
        path.lineTo(_pos[0]);

        //厚板上边框
        path.moveTo(_pos[0]);
        path.lineTo(_pos[6]);

        //厚板下削边
        path.moveTo(_pos[2]);
        path.lineTo(_pos[10]);

        //厚板下边框
        path.moveTo(_pos[10]);
        path.lineTo(_pos[7]);

        //薄板上边框
        path.moveTo(_pos[3]);
        path.lineTo(_pos[8]);

        //薄板下边框
        path.moveTo(_pos[5]);
        path.lineTo(_pos[9]);
    }
    else if(setup_PLANE_CENTER==m_cPart.weld_ii.align)
    {

        // 厚板3个点
        _pos[0].setX(-W1-W3/2);
        _pos[0].setY(h1-h1/l1*W1);
        _pos[1].setX(-W3/2);
        _pos[1].setY( h1-h1/l1*W1+H1);
        _pos[2].setX(-W3/2);
        _pos[2].setY(T1-h2);//厚板的厚度

        //薄板3个点
        _pos[3].setX(W2+W3/2);
        _pos[3].setY(T1/2-T2/2);

        _pos[4].setX(W3/2);
        _pos[4].setY(T1/2-T2/2+H2);
        _pos[5].setX(W3/2);
        _pos[5].setY(T1/2-T2/2+T2);

        //厚板的削边起点
        _pos[6].setX(-W3/2-l1);
        _pos[6].setY(0);

        //厚板的左下端点
        _pos[7].setX(_fStartV2);
        _pos[7].setY(T1);

        //厚板的下削边下端点
        _pos[10].setX(-W3/2-l2);
        _pos[10].setY(T1);

        //薄板的上边框端点
        _pos[8].setX(_fStopV2);
        _pos[8].setY(T1/2-T2/2);

        //薄板的右边框端点
        _pos[9].setX(_fStopV2);
        _pos[9].setY(T1/2-T2/2+T2);

        _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
        _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
        _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
        _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
        _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
        _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
        _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
        _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
        _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
        _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
        _pos[10]= m_pDataView->TranslateToScenePlan(&_pos[10]);

        //焊缝
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[5]);
        path.lineTo(_pos[4]);
        path.lineTo(_pos[3]);
        path.lineTo(_pos[0]);

        //厚板上边框
        path.moveTo(_pos[0]);
        path.lineTo(_pos[6]);

        //厚板下边框
        path.moveTo(_pos[2]);
        path.lineTo(_pos[10]);


        path.moveTo(_pos[10]);
        path.lineTo(_pos[7]);

        //薄板上边框
        path.moveTo(_pos[3]);
        path.lineTo(_pos[8]);

        //薄板下边框
        path.moveTo(_pos[5]);
        path.lineTo(_pos[9]);


    }
    else
    {

        // 厚板3个点
        _pos[0].setX(-W1-W3/2);
        _pos[0].setY(h1-h1/l1*W1);
        _pos[1].setX(-W3/2);
        _pos[1].setY( h1-h1/l1*W1+H1);
        _pos[2].setX(-W3/2);
        _pos[2].setY(T1-h2);

        //薄板3个点
        _pos[3].setX(W2+W3/2);
        _pos[3].setY(T1-T2);

        _pos[4].setX(W3/2);
        _pos[4].setY(T1-T2+H2);
        _pos[5].setX(W3/2);
        _pos[5].setY(T1);

        //厚板的削边起点
        _pos[6].setX(-W3/2-l1);
        _pos[6].setY(0);

        //厚板的左下端点
        _pos[7].setX(_fStartV2);
        _pos[7].setY(T1);

        //厚板的下削边下端点
        _pos[10].setX(-W3/2-l2);
        _pos[10].setY(T1);

        //薄板的上边框端点
        _pos[8].setX(_fStopV2);
        _pos[8].setY(T1-T2);

        //薄板的右边框端点
        _pos[9].setX(_fStopV2);
        _pos[9].setY(T1);

        _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
        _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
        _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
        _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
        _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]);
        _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]);
        _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]);
        _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]);
        _pos[8] = m_pDataView->TranslateToScenePlan(&_pos[8]);
        _pos[9] = m_pDataView->TranslateToScenePlan(&_pos[9]);
        _pos[10] = m_pDataView->TranslateToScenePlan(&_pos[10]);

        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[5]);
        path.lineTo(_pos[4]);
        path.lineTo(_pos[3]);
        path.lineTo(_pos[0]);

        //厚板上边框
        path.moveTo(_pos[0]);
        path.lineTo(_pos[6]);

        //厚板下边框
        path.moveTo(_pos[2]);
        path.lineTo(_pos[10]);

        path.moveTo(_pos[10]);
        path.lineTo(_pos[7]);

        //薄板上边框
        path.moveTo(_pos[3]);
        path.lineTo(_pos[8]);

        //薄板下边框
        path.moveTo(_pos[5]);
        path.lineTo(_pos[9]);

    }

}


void DopplerViewItems::DrawWeldTKYPlain(double startH, double stopH, double startV, double thinkness, QPainterPath& path)
{
    QPointF _pos[2];
    _pos[0].setX(startH);
    _pos[0].setY(startV);
    _pos[1].setX(stopH);
    _pos[1].setY(startV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    _pos[0].setX(startH);
    _pos[0].setY(startV + thinkness);
    _pos[1].setX(stopH);
    _pos[1].setY(startV + thinkness);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
}

void  DopplerViewItems::DrawWeld90degTKY(double w1, double w2, double h1, double h2, double a1, double a2,
                                         double startV, double stopV, QPainterPath& path)
{
    QPointF _pos[4];
    double topT = m_cPart.weld_ii.eTopThinkness / 2;
    double _btoT = m_cPart.weld_ii.eBottomThinkness;
    _pos[0].setX(-w1 - topT);
    _pos[0].setY(startV + _btoT);
    _pos[1].setX(- topT);
    _pos[1].setY(startV + _btoT + h1);
    _pos[2].setX(- topT + tan(a1)*h1);
    _pos[2].setY(startV + _btoT);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);

    _pos[3].setX(- topT);
    _pos[3].setY(stopV);
    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
    path.moveTo(_pos[1]);
    path.lineTo(_pos[3]);

    _pos[0].setX( w2 + topT);
    _pos[0].setY(startV + _btoT);
    _pos[1].setX( topT);
    _pos[1].setY(startV + _btoT + h2);
    _pos[2].setX( topT - tan(a2)*h2);
    _pos[2].setY(startV + _btoT);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);

    _pos[3].setX( topT);
    _pos[3].setY( stopV);
    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
    path.moveTo(_pos[1]);
    path.lineTo(_pos[3]);
}

void  DopplerViewItems::DrawWeldTKYWing( WELD_FORMAT_TKY &weld_tky, double startV, double stopV,double eAngle, QPainterPath& path)
{
    QPointF _pos[4];
    double w1 = weld_tky.w1;
    double h1 = weld_tky.h1;
    double w2 = weld_tky.w2;
    double h2 = weld_tky.h2;
    double topT = m_cPart.weld_ii.eTopThinkness / 2;
    double TKYAngle = DEGREE_TO_ARCH(eAngle);
    double _btoT = m_cPart.weld_ii.eBottomThinkness;
    double tkyH = abs(stopV - startV) - _btoT;

    double TKYA1X = h1 / tan( TKYAngle);
    double topTx = topT / sin(TKYAngle);
    double _a1X, _a2X;
    double tkyHx = tkyH / tan( TKYAngle);
    double a1a = 180 - eAngle - weld_tky.a1;
    if(a1a == 90){
        _a1X = 0;
    }else{
        double a1aArch = DEGREE_TO_ARCH(a1a);
        _a1X = h1 / tan(a1aArch);
    }

    _pos[0].setX( TKYA1X - w1 - topTx);
    _pos[0].setY( startV + _btoT);
    _pos[1].setX( TKYA1X - topTx);
    _pos[1].setY( startV + _btoT + h1);
    _pos[2].setX( TKYA1X - topTx + _a1X);
    _pos[2].setY( startV + _btoT);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);

    _pos[3].setX( tkyHx - topTx);
    _pos[3].setY( stopV);
    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
    path.moveTo(_pos[1]);
    path.lineTo(_pos[3]);

    double TKYA2X = h2 / tan( TKYAngle);
    double a2a = eAngle - weld_tky.a2;
    double a2aArch = DEGREE_TO_ARCH(a2a);
    _a2X = h2 / tan(a2aArch);
    _pos[0].setX( TKYA2X + w2 + topTx);
    _pos[0].setY( startV + _btoT);
    _pos[1].setX( TKYA2X + topTx);
    _pos[1].setY( startV + _btoT + h2);
    _pos[2].setX( TKYA2X + topTx - _a2X);
    _pos[2].setY( startV + _btoT);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);

    _pos[3].setX( tkyHx + topTx);
    _pos[3].setY( stopV);
    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
    path.moveTo(_pos[1]);
    path.lineTo(_pos[3]);
}

void  DopplerViewItems::DrawWeld90degTKYWeb(double w2, double h1, double h2, double a1, double a2, double startV, double stopV,
                                            double startH,QPainterPath& path)
{
    QPointF _pos[4];
    double topT = m_cPart.weld_ii.eTopThinkness;
    double _btoT = m_cPart.weld_ii.eBottomThinkness;
    _pos[0].setX(0);
    _pos[0].setY(startV);
    _pos[1].setX(0);
    _pos[1].setY(stopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    _pos[0].setX(_btoT);
    _pos[0].setY(startV);
    _pos[1].setX(_btoT);
    _pos[1].setY(stopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    _pos[0].setX(0);
    _pos[0].setY(startV + topT - tan(a2)*h2);
    _pos[1].setX(-h2);
    _pos[1].setY(startV + topT);
    _pos[2].setX(0);
    _pos[2].setY(startV + topT + w2);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);

    _pos[3].setX(startH);
    _pos[3].setY(startV + topT);
    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
    path.moveTo(_pos[1]);
    path.lineTo(_pos[3]);

    _pos[0].setX(0);
    _pos[0].setY(startV + tan(a1)*h1);
    _pos[1].setX(-h1);
    _pos[1].setY(startV);
    _pos[2].setX(startH);
    _pos[2].setY(startV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);
}

void DopplerViewItems::DrawWeldTKYWeb( WELD_FORMAT_TKY &weld_tky, double startV, double stopV, double startH, double eAngle,
                                       QPainterPath& path)
{
    QPointF _pos[4];
    double h1 = weld_tky.h1;
    double w2 = weld_tky.w2;
    double h2 = weld_tky.h2;
    double topT = m_cPart.weld_ii.eTopThinkness / 2;
    double topT2 = topT * 2;
    double TKYAngle = DEGREE_TO_ARCH(eAngle);
    double _btoT = m_cPart.weld_ii.eBottomThinkness;
    double _rangeV = abs(stopV - startV);
    double _btoTx = _btoT/sin(TKYAngle);

    double _tanAngle = tan(TKYAngle);
    double _cosAngle = cos(TKYAngle);
    double _sinAngle = sin(TKYAngle);
    _pos[0].setX(topT/_tanAngle);
    _pos[0].setY(startV);
    _pos[1].setX((topT - _rangeV)/_tanAngle);
    _pos[1].setY(stopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    float _tranBotx = m_pDataView->TranslateToScenePlanH(_btoTx);
    _pos[0].setX(_pos[0].x() + _tranBotx);
    _pos[1].setX(_pos[1].x() + _tranBotx);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);

    double a2a = 90 - eAngle + weld_tky.a2;
    if(a2a > 89){
        return;
    }
    double a2aArch = DEGREE_TO_ARCH(a2a);
    double _a2X = h2 * tan(a2aArch);
    double pos1x = - (topT + _cosAngle*h2)/_tanAngle;
    double pos1y = topT2 + h2*_cosAngle;
    _pos[0].setX(pos1x + _a2X*_cosAngle);
    _pos[0].setY(startV + pos1y - _a2X*_sinAngle);
    _pos[1].setX(-h2/_sinAngle - topT/_tanAngle);
    _pos[1].setY(startV + topT2);
    _pos[2].setX(pos1x - w2*_cosAngle);
    _pos[2].setY(startV + pos1y + w2*_sinAngle);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    path.lineTo(_pos[2]);

    _pos[3].setX(startH);
    _pos[3].setY(startV + topT2);
    _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]);
    path.moveTo(_pos[1]);
    path.lineTo(_pos[3]);

    double _a1X;
    double a1a = 90 - eAngle - weld_tky.a1;
    if(a1a == 0){
        _a1X = 0;
    }else{
        double a1aArch = DEGREE_TO_ARCH(a1a);
        _a1X = h1 * tan(a1aArch);
    }
    _pos[0].setX(topT/_tanAngle + _a1X*_cosAngle - h1*_cosAngle/_tanAngle);
    _pos[0].setY(startV + h1*_cosAngle - _a1X*_sinAngle);
    _pos[1].setX(topT/_tanAngle - h1/_sinAngle);
    _pos[1].setY(startV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
}

void  DopplerViewItems::DrawWeldTKY(QPainterPath& path)
{
    QPointF _pos[8];
    double _fStartV , _fStopV , _fSliderStartV , _fSliderStopV;
    m_pDataView->GetRulerRange(&_fStartV , &_fStopV , &_fSliderStartV , &_fSliderStopV , DopplerDataView::DATA_VIEW_RULER_LEFT );
    _pos[0].setX(0);
    _pos[0].setY(_fStartV);
    _pos[1].setX(0);
    _pos[1].setY(_fStopV);
    _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]);
    _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]);
    path.moveTo(_pos[0]);
    path.lineTo(_pos[1]);
    
    double thickness = m_cPart.afSize[0];
    //double fx0,fx1,fx2,fx3,fx4,fx5,fy0,fy1,fy2,fy3,fx6;
    double width1 = m_cPart.weld.weland_height + 0.5 * m_cPart.weld.Diameter/sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle));
    double width2 = m_cPart.weld.fizone_height + 0.5 * m_cPart.weld.Diameter/sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle));
    double R = 4 * m_cPart.weld.weland_offset + thickness + 20;
    if(m_cPart.weld.eSymmetry == 0 || m_cPart.weld.eSymmetry == 1 || m_cPart.weld.eSymmetry == 6)
    {
    for(int i = 1 ; i*thickness < _fStopV ; i += 2)
    {
        _pos[0].setX(-width1);
        _pos[0].setY(i * thickness);
        _pos[1].setX(width2);
        _pos[1].setY(i * thickness);
        _pos[2].setX(0.5 * m_cPart.weld.Diameter/sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-m_cPart.weld.fizone_radius/tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
        _pos[2].setY(i * thickness + m_cPart.weld.fizone_radius);
        _pos[3].setX(-R * cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))+(m_cPart.weld.Diameter/2.0)*sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
        _pos[3].setY(i * thickness + R * sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))+(m_cPart.weld.Diameter/2.0)*cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
        _pos[4].setX(-R * cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-(m_cPart.weld.Diameter/2.0)*sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
        _pos[4].setY(i * thickness + R * sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-(m_cPart.weld.Diameter/2.0)*cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
        _pos[5].setX(-0.5 * m_cPart.weld.Diameter/sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-m_cPart.weld.weland_offset/tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
        _pos[5].setY(i * thickness + m_cPart.weld.weland_offset);
        _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
        _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
        _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
        _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
        _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
        _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]) ;
        path.moveTo(_pos[0]);
        path.lineTo(_pos[1]);
        path.lineTo(_pos[2]);
        path.lineTo(_pos[3]);
        path.lineTo(_pos[4]);
        path.lineTo(_pos[5]);
        path.lineTo(_pos[0]);

    }
    }
    else if(m_cPart.weld.eSymmetry == 2 || m_cPart.weld.eSymmetry == 3)
    {
        for(int i = 2 ; i*thickness < _fStopV ; i += 2)
        {
            _pos[0].setX(-width1);
            _pos[0].setY(i * thickness);
            _pos[1].setX(width2);
            _pos[1].setY(i * thickness);
            _pos[2].setX(0.5 * m_cPart.weld.Diameter/sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-m_cPart.weld.fizone_radius/tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
            _pos[2].setY(i * thickness + m_cPart.weld.fizone_radius);
            _pos[3].setX(-R * cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))+(m_cPart.weld.Diameter/2.0)*sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
            _pos[3].setY(i * thickness + R * sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))+(m_cPart.weld.Diameter/2.0)*cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
            _pos[4].setX(-R * cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-(m_cPart.weld.Diameter/2.0)*sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
            _pos[4].setY(i * thickness + R * sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-(m_cPart.weld.Diameter/2.0)*cos(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
            _pos[5].setX(-0.5 * m_cPart.weld.Diameter/sin(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle))-m_cPart.weld.weland_offset/tan(DEGREE_TO_ARCH(m_cPart.weld.fizone_angle)));
            _pos[5].setY(i * thickness + m_cPart.weld.weland_offset);
            _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
            _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
            _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
            _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
            _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
            _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]) ;
            path.moveTo(_pos[0]);
            path.lineTo(_pos[1]);
            path.lineTo(_pos[2]);
            path.lineTo(_pos[3]);
            path.lineTo(_pos[4]);
            path.lineTo(_pos[5]);
            path.lineTo(_pos[0]);
        }
    }
    else if(m_cPart.weld.eSymmetry == 4 || m_cPart.weld.eSymmetry == 5)
    {
        double _nFizoneAngle = m_cPart.weld.fizone_angle;
        double X1 = m_cPart.weld.weland_height;
        double X2 = m_cPart.weld.fizone_height;
        double Y1 = m_cPart.weld.weland_offset;
        double Y2 = m_cPart.weld.fizone_radius;
        double T2 = m_cPart.weld.Diameter;
        double tempX,tempY,firswidth,w1,w2,w3,w4,w5,l1,h1,h2;

        if((m_cPart.weld.eSymmetry == 4 && m_cPart.weld.fizone_angle >= 90.0) || ( m_cPart.weld.eSymmetry == 5 && m_cPart.weld.fizone_angle <90.0))
        {
            if(m_cPart.weld.fizone_angle >= 90.0)
                _nFizoneAngle = m_cPart.weld.fizone_angle - 90.0;
            else if(m_cPart.weld.fizone_angle < 90.0)
            {
                _nFizoneAngle = 180.0 - m_cPart.weld.fizone_angle - 90.0;
                tempX = X1;
                tempY = Y1;
                X1 = X2;
                Y1 = Y2;
                X2 = tempX;
                Y2 = tempY;
            }
            firswidth = T2 * tan(DEGREE_TO_ARCH(_nFizoneAngle));
            w1 = firswidth / 2;
            w2 = Y2 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
            w3 = X2 * sin(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
            R = 6 * w1 + 30;
            l1 = T2 / cos(DEGREE_TO_ARCH(_nFizoneAngle));
            w4 = Y1 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) - T2 *  tan(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
            w5 = (l1 + X1) * sin(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
            h1 = X2 * cos(DEGREE_TO_ARCH(_nFizoneAngle));
            h2 = (l1 + X1) * cos(DEGREE_TO_ARCH(_nFizoneAngle));

            //fx0 = w1;
            //fx1 = R;
            //fx2 = R;
            //fx3 = w2;
            //fx4 = w3;
            //fx5 = w4;
            //fx6 = w5;
            //fy0 = T2;
            //fy1 = T2 + h1;
            //fy2 = T2 / 2;
            //fy3 = T2 + h2;

            _pos[0].setX(w1);
            _pos[1].setX(-w3);
            _pos[2].setX(-w2);
            _pos[3].setX(-R);
            _pos[4].setX(-w1);
            _pos[5].setX(w5);
            _pos[6].setX(-w4);
            _pos[7].setX(-R);
            _pos[0].setY(0);
            _pos[1].setY(h1 + T2);
            _pos[2].setY(T2);
            _pos[3].setY(T2);
            _pos[4].setY(T2);
            _pos[5].setY(h2 + T2);
            _pos[6].setY(2 * T2);
            _pos[7].setY(2 * T2);

            _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
            _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
            _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
            _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
            _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
            _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]) ;
            _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]) ;
            _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]) ;
            path.moveTo(_pos[0]);
            path.lineTo(_pos[1]);
            path.lineTo(_pos[2]);
            path.lineTo(_pos[3]);
            path.moveTo(_pos[4]);
            path.lineTo(_pos[5]);
            path.lineTo(_pos[6]);
            path.lineTo(_pos[7]);
        }

        if((m_cPart.weld.eSymmetry == 5 && m_cPart.weld.fizone_angle >= 90.0) || (m_cPart.weld.eSymmetry == 4 && m_cPart.weld.fizone_angle < 90.0))
        {
            if(m_cPart.weld.fizone_angle >= 90.0)
                _nFizoneAngle = m_cPart.weld.fizone_angle - 90.0;
            else if(m_cPart.weld.fizone_angle < 90.0)
        {
                _nFizoneAngle = 180.0 - m_cPart.weld.fizone_angle - 90.0;
                tempX = X1;
                tempY = Y1;
                X1 = X2;
                Y1 = Y2;
                X2 = tempX;
                Y2 = tempY;
        }
                firswidth = T2 * tan(DEGREE_TO_ARCH(_nFizoneAngle));
                w1 = firswidth / 2;
                w2 = Y1 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
                w3 = X1 * sin(DEGREE_TO_ARCH(_nFizoneAngle)) + w1;
                R = 6 * w1 + 30;
                w4 = Y2 / cos(DEGREE_TO_ARCH(_nFizoneAngle)) + T2 * tan(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
                l1 = T2 / cos(DEGREE_TO_ARCH(_nFizoneAngle));
                w5 = (l1 + X2) * sin(DEGREE_TO_ARCH(_nFizoneAngle)) - w1;
                h1 = (l1 + X1) * cos(DEGREE_TO_ARCH(_nFizoneAngle));
                h2 = (l1 + X2) * cos(DEGREE_TO_ARCH(_nFizoneAngle));

                //fx0 = w1;
                //fx1 = R;
                //fx2 = R;
                //fx3 = w2;
                //fx4 = w3;
                //fx5 = w4;
                //fx6 = w5;
                //fy0 = T2;
                //fy1 = h1;
                //fy2 = T2 / 2;
                //fy3 = T2 + h2;
                _pos[0].setX(-w1);
                _pos[1].setX(w3);
                _pos[2].setX(-w2);
                _pos[3].setX(-R);
                _pos[4].setX(w1);
                _pos[5].setX(-w5);
                _pos[6].setX(-w4);
                _pos[7].setX(-R);
                _pos[0].setY(0);
                _pos[1].setY(h1);
                _pos[2].setY(T2);
                _pos[3].setY(T2);
                _pos[4].setY(T2);
                _pos[5].setY(T2+h2);
                _pos[6].setY(2 * T2);
                _pos[7].setY(2 * T2);
                _pos[0] = m_pDataView->TranslateToScenePlan(&_pos[0]) ;
                _pos[1] = m_pDataView->TranslateToScenePlan(&_pos[1]) ;
                _pos[2] = m_pDataView->TranslateToScenePlan(&_pos[2]) ;
                _pos[3] = m_pDataView->TranslateToScenePlan(&_pos[3]) ;
                _pos[4] = m_pDataView->TranslateToScenePlan(&_pos[4]) ;
                _pos[5] = m_pDataView->TranslateToScenePlan(&_pos[5]) ;
                _pos[6] = m_pDataView->TranslateToScenePlan(&_pos[6]) ;
                _pos[7] = m_pDataView->TranslateToScenePlan(&_pos[7]) ;
                path.moveTo(_pos[0]);
                path.lineTo(_pos[1]);
                path.lineTo(_pos[2]);
                path.lineTo(_pos[3]);
                path.moveTo(_pos[4]);
                path.lineTo(_pos[5]);
                path.lineTo(_pos[6]);
                path.lineTo(_pos[7]);

        }
    }
    ParameterProcess* _process = ParameterProcess::Instance();
    if(m_cPart.weld.eSymmetry == 0 || m_cPart.weld.eSymmetry == 2 || m_cPart.weld.eSymmetry == 4 || m_cPart.weld.eSymmetry == 5 || m_cPart.weld.eSymmetry == 6)
        _process->SetupWedgeSkewAngle(m_pDataView->GetGroupId()  , (setup_PROBE_ANGLE)1)  ;
    else if(m_cPart.weld.eSymmetry == 1 || m_cPart.weld.eSymmetry == 3)
        _process->SetupWedgeSkewAngle(m_pDataView->GetGroupId()  , (setup_PROBE_ANGLE)3)  ;

}

//void  DopplerViewItems::DrawWeldNcc (QPainterPath& path)
//{
//	DRAW_PART_INFO _info;
//	DopplerPart* _pPart = DopplerPart::Instance();

//	QSize size = m_pDataView->GetViewSize();

//	double _fXStart, _fXStop, _fYStart, _fYStop;
//	double _fXSliderStart, _fXSliderStop, _fYSliderStart, _fYSliderStop;
//	m_pDataView->GetRulerRange(&_fXStart, &_fXStop, &_fXSliderStart, &_fXSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
//	m_pDataView->GetRulerRange(&_fYStart, &_fYStop, &_fYSliderStart, &_fYSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);

//	double _fWidth  = size.width();
//    double _fHeight = size.height();

//	double _fXScale = (_fXStop - _fXStart) / _fWidth;
//	double _fYScale = (_fYStop - _fYStart) / _fHeight;

//    double _x0 = (0 - _fXStart) / _fXScale;
//	double _y0 = (0 - _fYStart) / _fYScale;

//	_info.fWidth  = _fWidth;
//	_info.fHeight = _fHeight;
//	_info.fX      = _x0;
//	_info.fY      = _y0;
//	_info.fScaleX = _fXScale;
//	_info.fScaleY = _fYScale;

//    _pPart->SetPart(&m_cPart);
//	_pPart->SetInfo(_info);
//  //  _pPart->AdaptiveArea();
//	_pPart->DrawNccPart(path);

//}

void DopplerViewItems::DrawWeldDxf(QPainterPath &path)
{

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QSize size = m_pDataView->GetViewSize();
    int nGroupId_, nLaw_, eDisplayMode_;
    m_pDataView->GetDataViewConfigure(&nGroupId_, &nLaw_, &eDisplayMode_);
    DplDxf::DrawDxf* pDxfPart = DplDxf::DrawDxf::Instance(nGroupId_);

    double _fXStart, _fXStop, _fYStart, _fYStop;
    double _fXSliderStart, _fXSliderStop, _fYSliderStart, _fYSliderStop;
    m_pDataView->GetRulerRange(&_fXStart, &_fXStop, &_fXSliderStart, &_fXSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    m_pDataView->GetRulerRange(&_fYStart, &_fYStop, &_fYSliderStart, &_fYSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);

    double _fWidth  = size.width();
    double _fHeight = size.height();

    double _fXScale = _fWidth / (_fXStop - _fXStart);
    double _fYScale = _fHeight / (_fYStop - _fYStart);

    double _x0 = (0 - _fXStart) * _fXScale;
    double _y0 = (0 - _fYStart) * _fYScale;
    if(!_pConfig->group[nGroupId_].part.CADFresh){
        pDxfPart->set_part(&m_cPart);
        _pConfig->group[nGroupId_].part.CADFresh = true;
    }

    pDxfPart->set_axis_orientation_s_scan(DplDxf::DrawDxf::Axis_Vertical_Flip);
    pDxfPart->set(_fWidth, _fHeight, _x0, _y0, _fXScale, _fYScale);

    pDxfPart->draw_dxf_part(path);
}
