#include "DopplerViewItems.h"
#include "painter/DopplerPart.h"
#include "painter/DrawDxf.h"

#include <QColor>
#include <gHeader.h>
#include <process/ParameterProcess.h>

static const QColor COLOR_GATE_A  =  QColor(255 , 0 , 0)   ;
static const QColor COLOR_GATE_B  =  QColor(0 , 255 , 0)   ;
static const QColor COLOR_GATE_I  =  QColor(255 , 255 , 0) ;

static const QColor COLOR_DEFECT  =  QColor(255 , 0 , 0) ;
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
static const QColor COLOR_SCAN_MARKER  = QColor(255 , 255 , 0  ) ;


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

	m_pItemLw = NULL;
	m_pItemBw = NULL;
	//---------------------------------------
	memset((void*)m_pGate ,   0 , 12) ;
	memset((void*)m_pCursor , 0 , 16) ;
	memset((void*)m_pThickness , 0 , 40 ) ;
	//m_pWeld		= 0;
	m_pLawMarker	= 0;
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
	if(m_pLawMarker)  delete m_pLawMarker ;
	//if(m_pWeld)	   delete m_pWeld	  ;
	if(m_pParabola[0])   delete m_pParabola[0] ;
	if(m_pParabola[1])   delete m_pParabola[1] ;
	m_pLawMarker = NULL ;
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
	UpdateItemsThickness() ;
	UpdateItemsWeld() ;
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
		_nMoveType = DopplerLineItem::LINE_MOVE_HORIZENTAL;
	} else if(_eDisplay == setup_DISPLAY_MODE_A_V || _eDisplay == setup_DISPLAY_MODE_B_V) {
		_nLineType = DopplerLineItem::LINE_HORIZENTAL;
		_nMoveType = DopplerLineItem::LINE_MOVE_VERTICAL;
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
		m_pDataView->AddOverlayItems(m_pItemLw);
	}

	if(!m_pItemBw)
	{
		m_pItemBw = new DopplerCalibrationMark(COLOR_BW);
		m_pItemBw->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pItemBw->SetLineType(_nLineType);
		m_pItemBw->SetMoveType(_nMoveType);
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

void DopplerViewItems::UpdateItemsGate()
{
	if(!(m_eShow & OVERLAYS_GATE))
	{
		if(m_pGate[0])  m_pGate[0]->hide() ;
		if(m_pGate[1])  m_pGate[1]->hide() ;
		if(m_pGate[2])  m_pGate[2]->hide() ;
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
		m_pGate[i]->SetDrawMode(m_eGateMode);
		m_pGate[i]->SetItemType(DOPPLER_GRAPHICS_ITEM_GATE ) ;
		m_pGate[i]->SetItemId(i);
		GateMove(i , afGatePos[i][0] , afGatePos[i][1] , afGatePos[i][2]);
	}

	m_pGate[0]->show() ;
	m_pGate[1]->show() ;
	m_pGate[2]->show() ;

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
		m_pCursor[0]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[0]->SetLineType(DopplerLineItem::LINE_HORIZENTAL);
		m_pCursor[0]->SetMoveType(DopplerLineItem::LINE_MOVE_VERTICAL);
		m_pCursor[0]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[0]);
	}
	if(!m_pCursor[1])
	{
		m_pCursor[1] = new DopplerLineItem(COLOR_CURSOR_AMES);
		m_pCursor[1]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[1]->SetLineType(DopplerLineItem::LINE_HORIZENTAL);
		m_pCursor[1]->SetMoveType(DopplerLineItem::LINE_MOVE_VERTICAL);
		m_pCursor[1]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[1]);
	}
	if(!m_pCursor[2])
	{
		m_pCursor[2] = new DopplerLineItem(COLOR_CURSOR_UREF);
		m_pCursor[2]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[2]->SetLineType(DopplerLineItem::LINE_VERTICAL);
		m_pCursor[2]->SetMoveType(DopplerLineItem::LINE_MOVE_HORIZENTAL);
		m_pCursor[2]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[2]);
	}
	if(!m_pCursor[3])
	{
		m_pCursor[3] = new DopplerLineItem(COLOR_CURSOR_UMES);
		m_pCursor[3]->SetItemType(DOPPLER_GRAPHICS_ITEM_CURSOR ) ;
		m_pCursor[3]->SetLineType(DopplerLineItem::LINE_VERTICAL);
		m_pCursor[3]->SetMoveType(DopplerLineItem::LINE_MOVE_HORIZENTAL);
		m_pCursor[3]->SetDataView(m_pDataView);
		m_pDataView->AddOverlayItems(m_pCursor[3]);
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
	}

	QVector<QLineF> _lines ; _lines.clear();
	QLineF _tmp , _line ;
	QPointF _pos1 , _pos2 ;
	for(int i = 0 ; i < markers.count() ; i++)
	{
		_tmp = markers.at(i) ;
		_pos1 = _tmp.p1()  ; _pos2 = _tmp.p2()  ;
		_pos1 = m_pDataView->TranslateToScenePlan(&_pos1) ;
		_pos2 = m_pDataView->TranslateToScenePlan(&_pos2) ;

		_line = QLineF(_pos1 , _pos2);
		_lines.append(_line);
	}

	m_pLawMarker->SetupMarkers(&_lines);
	m_pLawMarker->SetupStringMarker(&strMarker);
	m_pLawMarker->show();
}

int DopplerViewItems::GetLawMarkerQty()
{
	if(m_pLawMarker) {
		return m_pLawMarker->GetMarkerQty();
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
	if(m_bHorizental)
		m_pDataView->GetRulerRange(&_fStart , &_fStop , &_fSliderStart , &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	else
		m_pDataView->GetRulerRange(&_fStart , &_fStop , &_fSliderStart , &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);

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

void DopplerViewItems::UpdateItemsWeld()
{
	if(!(m_eShow & OVERLAYS_LAW_MARKER))
		return ;

	if(m_eShow & OVERLAYS_WELD )
	{
        QPainterPath _path;
		DrawWeld(_path);
		if(m_pLawMarker){
			m_pLawMarker->SetWeldColor(COLOR_WELD);
			m_pLawMarker->SetWeldInfo(true , &_path);
		}
    }else{
		if(m_pLawMarker) m_pLawMarker->SetWeldInfo(false, NULL);
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

	m_pDataView->SetItemGeometry(m_pScanMarker, _rect );
	m_pScanMarker->SetScenceSize(m_pDataView->GetViewSize());
	m_pScanMarker->show();
}

void DopplerViewItems::SetGateDrawMode(GATE_DRAW_MODE eMode_)
{
	m_eGateMode   = eMode_  ;
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

void  DopplerViewItems::DrawWeld(QPainterPath& path)
{
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

	case setup_WELD_NCC :
		DrawWeldNcc(path);
		break;
    case setup_WELD_DXF: //New Add
        DrawWeldDxf(path);
        break;
	default:
		break;
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

void  DopplerViewItems::DrawWeldNcc (QPainterPath& path)
{
	DRAW_PART_INFO _info;
	DopplerPart* _pPart = DopplerPart::Instance();

	QSize size = m_pDataView->GetViewSize();

	double _fXStart, _fXStop, _fYStart, _fYStop;
	double _fXSliderStart, _fXSliderStop, _fYSliderStart, _fYSliderStop;
	m_pDataView->GetRulerRange(&_fXStart, &_fXStop, &_fXSliderStart, &_fXSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
	m_pDataView->GetRulerRange(&_fYStart, &_fYStop, &_fYSliderStart, &_fYSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);

	double _fWidth  = size.width();
    double _fHeight = size.height();

	double _fXScale = (_fXStop - _fXStart) / _fWidth;
	double _fYScale = (_fYStop - _fYStart) / _fHeight;

    double _x0 = (0 - _fXStart) / _fXScale;
	double _y0 = (0 - _fYStart) / _fYScale;

	_info.fWidth  = _fWidth;
	_info.fHeight = _fHeight;
	_info.fX      = _x0;
	_info.fY      = _y0;
	_info.fScaleX = _fXScale;
	_info.fScaleY = _fYScale;

    _pPart->SetPart(&m_cPart);
	_pPart->SetInfo(_info);
  //  _pPart->AdaptiveArea();
	_pPart->DrawNccPart(path);

}

void DopplerViewItems::DrawWeldDxf(QPainterPath &path)
{
    DRAW_DXF_INFO _info;
    DplDxf::DrawDxf* pDxfPart = DplDxf::DrawDxf::Instance();

    QSize size = m_pDataView->GetViewSize();

    double _fXStart, _fXStop, _fYStart, _fYStop;
    double _fXSliderStart, _fXSliderStop, _fYSliderStart, _fYSliderStop;
    m_pDataView->GetRulerRange(&_fXStart, &_fXStop, &_fXSliderStart, &_fXSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
    m_pDataView->GetRulerRange(&_fYStart, &_fYStop, &_fYSliderStart, &_fYSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);

    double _fWidth  = size.width();
    double _fHeight = size.height();

    double _fXScale = (_fXStop - _fXStart) / _fWidth;
    double _fYScale = (_fYStop - _fYStart) / _fHeight;

    double _x0 = (0 - _fXStart) / _fXScale;
    double _y0 = (0 - _fYStart) / _fYScale;

    _info.fWidth  = _fWidth;
    _info.fHeight = _fHeight;
    _info.fX      = _x0;
    _info.fY      = _y0;
    _info.fScaleX = _fXScale;
    _info.fScaleY = _fYScale;

    pDxfPart->setPart(&m_cPart);
    pDxfPart->SetInfo(_info);
    pDxfPart->DrawDxfPart(path, _x0, 1/_fXScale, 1/_fYScale);
}
