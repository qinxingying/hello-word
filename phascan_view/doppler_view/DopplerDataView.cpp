#include "DopplerDataView.h"
#include "DopplerRulerBar.h"
#include "DopplerTitleBar.h"
#include "DopplerColorBar.h"
#include "DopplerGraphicView.h"
#include "DopplerGraphicsItem.h"
#include "DopplerViewItems.h"
#include <QGridLayout>
#include <QMouseEvent>
#include <gHeader.h>
#include <QMenu>
#include "ProcessDisplay.h"

static const QSize DEFAULT_SIZE( 800 , 600);
static const QSize MINIMUM_SIZE( 150 , 150);

DopplerDataView::DopplerDataView(QWidget *parent , DATA_VIEW_COMPONENT eComponent_) :
	QWidget(parent)
{
	m_nGroupId = 0  ;
	m_nLaw	 = 0  ;
	m_eDisplayMode  = 0  ;
	m_nIdentify	 = 0  ;

	m_pLayout	   = NULL  ;
	m_pTitleBar	 = NULL  ;
	m_pColorBar	 = NULL  ;
	m_pGraphicView  = NULL  ;
	m_eComponent	= eComponent_  ;
	m_bSelected	 = false ;

	for(int i = 0; i < DATA_VIEW_RULER_MAX ; i++)
	{
		m_pRulers[i] = NULL ;
		RulerRange[i].first  = 0	 ;
		RulerRange[i].second = 0	 ;
	}

	setMinimumSize(MINIMUM_SIZE);
	resize(DEFAULT_SIZE);
	//************ set back ground color
	QPalette pal = this->palette() ;
	pal.setColor(QPalette::Background , QColor(0 , 0 , 0));
	setPalette(pal);
	setAutoFillBackground(true);
	setFont(QFont("simsun" ,9));
	//*********** create widgets of this view
	CreateComponent() ;
	//connect(this, SIGNAL(signalMousePressed(QWidget*)) , g_pMainWnd , SLOT(slotViewFrameButtonClicked(QWidget*)));
	//connect(this, SIGNAL(signalViewFrameMenuSelection(DopplerDataView* , int)) , g_pMainWnd , SLOT(slotViewFrameMenuSelection(DopplerDataView* , int))) ;

	m_pItemsGroup = new DopplerViewItems(this);
}


DopplerDataView::~DopplerDataView()
{
	delete m_pItemsGroup ;
	DeleteAllWidget()	;
}

void DopplerDataView::DeleteAllWidget()
{
	for(int i = 0; i < DATA_VIEW_RULER_MAX ; i++)
	{
		delete m_pRulers[i] ;
		m_pRulers[i] = NULL ;
	}

	if(m_pTitleBar	 != NULL)  {delete m_pTitleBar	 ;   m_pTitleBar  =  NULL ;}
	if(m_pColorBar	 != NULL)  {delete m_pColorBar	 ;   m_pColorBar  =  NULL ;}
	if(m_pGraphicView  != NULL)  {delete m_pGraphicView  ;   m_pGraphicView  =  NULL ;}
	if(m_pLayout	   != NULL)  {delete m_pLayout	   ;   m_pLayout  =  NULL ;}
}

void DopplerDataView::SetDataViewConfigure(int nGroupId_ , int nLaw_ , int eDisplayMode_)
{
	m_nGroupId = nGroupId_  ;
	m_nLaw	 = nLaw_	  ;
	m_eDisplayMode  = eDisplayMode_  ;

}

void DopplerDataView::GetDataViewConfigure(int* nGroupId_ , int* nLaw_ , int* eDisplayMode_) const
{
	*nGroupId_  =  m_nGroupId  ;
	*nLaw_	  =  m_nLaw	  ;
	*eDisplayMode_ = m_eDisplayMode  ;
}

int DopplerDataView::GetDataViewDrawType()
{
	return m_eDisplayMode ;
}

int DopplerDataView::GetGroupId()
{
	return m_nGroupId ;
}

int DopplerDataView::GetLawId()
{
	return m_nLaw ;
}

void DopplerDataView::SetLawIdentify(int nId_)
{
	m_nIdentify = nId_ ;
}

int DopplerDataView::GetLawIdentify() const
{
	return m_nIdentify ;
}

int DopplerDataView::GetSScanLawQty()
{
	return m_pItemsGroup->GetLawMarkerQty();
}

int DopplerDataView::GetSScanLaw(int index_)
{
    return m_pItemsGroup->GetLawMarkerPos(index_);
}

void DopplerDataView::SetSScanLaw(int index_, int nMarkerLawPos)
{
    m_pItemsGroup->SetLawMarkerPos(index_, nMarkerLawPos);
}

void DopplerDataView::EnableComponent(DATA_VIEW_COMPONENT eComponent_)
{
	m_eComponent	= eComponent_  ;
	CreateComponent() ;
}

void DopplerDataView::SetRulerRange(double nStart_ , double nStop_ , double nSliderStart_ , double nSliderStop_ , DATA_VIEW_RULER eRuler_ )
{
	if(eRuler_ >= DATA_VIEW_RULER_MAX)  return ;

	// if value not changed , return ,
	// for  slotResetView will zoom the display view
	if((FLOAT_EQ(RulerRange[eRuler_].first , nStart_))
	   && (FLOAT_EQ(RulerRange[eRuler_].second ,nStop_ )))
		return ;

	RulerRange[eRuler_].first  = nStart_  ;
	RulerRange[eRuler_].second = nStop_   ;

	SliderRange[eRuler_].first  = nSliderStart_  ;
	SliderRange[eRuler_].second = nSliderStop_  ;

	if(m_pRulers[eRuler_]) {
		m_pRulers[eRuler_]->SetMarkerRange(nStart_ , nStop_, nSliderStart_, nSliderStop_);
	}

	if(m_pGraphicView) {
		m_pGraphicView->slotResetView();
	}
}

void DopplerDataView::GetRulerRange(double* nStart_ , double* nStop_ , double *nSliderStart_ , double *nSliderStop_ , DATA_VIEW_RULER eRuler_ )
{
	if(eRuler_ >= DATA_VIEW_RULER_MAX)  return ;
	*nStart_  = RulerRange[eRuler_].first ;
	*nStop_   = RulerRange[eRuler_].second ;

	*nSliderStart_  = SliderRange[eRuler_].first ;
	*nSliderStop_   = SliderRange[eRuler_].second ;
}

void DopplerDataView::SetRulerColor(QColor* color , DATA_VIEW_RULER eRuler_)
{
	if(m_pRulers[eRuler_])
		m_pRulers[eRuler_]->SetBackgroudColor(color);
}
void DopplerDataView::SetRulerMarkerColor(QColor* color , DATA_VIEW_RULER eRuler_ )
{
	if(m_pRulers[eRuler_])
		m_pRulers[eRuler_]->SetMarkerColor(color);
}

void DopplerDataView::SetRulerUnit(QString* unit  , DATA_VIEW_RULER eRuler_)
{
	if(m_pRulers[eRuler_])
		m_pRulers[eRuler_]->SetMarkerUnit(unit);
}

void DopplerDataView::SetTitleBarColor(QColor& color_)
{
	if(m_pTitleBar)
		m_pTitleBar->SetBackgroudColor(color_);
}

void DopplerDataView::SetTitleBarString(QString& str_)
{
	if(m_pTitleBar)
		m_pTitleBar->SetTitle(str_);
}

void DopplerDataView::SetTitleBarStringColor(QColor color_)
{
	if(m_pTitleBar)
		m_pTitleBar->SetTextColor(color_);
}

void DopplerDataView::SetColorBarColorIndex(void* index)
{
	if(m_pColorBar)
		m_pColorBar->setColorIndex(index);
}

void DopplerDataView::AddOverlayItems(QGraphicsItem* item_)
{
	if(m_pGraphicView)
		m_pGraphicView->AddOverlayItems(item_);
}


QSize DopplerDataView::GetViewSize()
{
	return m_pGraphicView->GetSceneSize();
}

void DopplerDataView::SetDrawScan(DopplerDrawScan* pDraw_)
{
	m_pGraphicView->SetDrawScan(pDraw_);
}

DopplerDrawScan* DopplerDataView::GetDrawScan() const
{
	return m_pGraphicView->GetDrawScan() ;
}

#include <configure/DopplerConfigure.h>
#include <process/CalcMeasurement.h>
void DopplerDataView::UpdateDrawing()
{
	UpdateMeasure() ;
	m_pGraphicView->UpdateDrawing();
    UpdateMeasure() ;
}

#include <process/ParameterProcess.h>
void DopplerDataView::UpdateMeasure()
{
	DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;

	if(_pConfig->group[m_nGroupId].bShowMeasure)
	{
		int* _pMeasure = _pConfig->group[m_nGroupId].aeMeasureType ;
		int _nQty = 0 ;
		if(m_eDisplayMode >= setup_DISPLAY_MODE_S) {
			int _nLawNum = m_pItemsGroup->GetLawMarkerQty();
			int _nLaw;

			for(int i = 0; i < _nLawNum; i++) {
				_nLaw = m_pItemsGroup->GetLawMarkerPos(i);
                for(int k = 0; k < 8; k++) {
					if(_pMeasure[k]) {
                        QString _str = CalcMeasurement::GetMeasureValueString(m_nGroupId , _nLaw , (FEILD_VALUE_INDEX)_pMeasure[k] );
                        m_pGraphicView->SetMeasureString(_nQty , &_str);
                        qDebug("%s[%d]: nLaw:%d", __FUNCTION__, __LINE__, _nLaw);
						_nQty++;
					}
				}
			}
			m_pGraphicView->SetMeasureStringQty(_nQty);

		} else {
            for(int i = 0 ; i < 8 ; i++) {
				if(_pMeasure[i]) {
                    QString _str = CalcMeasurement::GetMeasureValueString(m_nGroupId , m_nLaw , (FEILD_VALUE_INDEX)_pMeasure[i] );
                    m_pGraphicView->SetMeasureString(_nQty , &_str);
                    //qDebug("%s[%d]: nLaw:%d", __FUNCTION__, __LINE__, m_nLaw);
					_nQty++  ;
				}
			}
			m_pGraphicView->SetMeasureStringQty(_nQty);
		}
	}
	else
		m_pGraphicView->SetMeasureStringQty(0);
}


/****************************************************************************
  Description: 换算ITEM位置
*****************************************************************************/
void DopplerDataView::SetItemGeometry(DopplerGraphicsItem* item , QRectF& rect_)
{
	QPointF _pos1 = rect_.topLeft() ;
	QPointF _pos2 = rect_.bottomRight() ;
	_pos1 = TranslateToScenePlan(&_pos1)  ;
	_pos2 = TranslateToScenePlan(&_pos2)  ;
	QRectF _rect ( _pos1 ,  _pos2) ;
	item->SetItemGeometry(_rect);
	item->SetItemGeometryReal(rect_);
}

/****************************************************************************
  Description: 换算实际坐标到场景坐标
  Input:  的实际坐标
  Output: 坐标，以像素作单位
*****************************************************************************/
QPointF DopplerDataView::TranslateToScenePlan(QPointF* pPos_)
{
	double _nVStart = RulerRange[DATA_VIEW_RULER_LEFT].first  ;
	double _nVStop  = RulerRange[DATA_VIEW_RULER_LEFT].second ;
	double _nVHeight= _nVStop - _nVStart ;

	double _nHStart = RulerRange[DATA_VIEW_RULER_BOTTOM].first  ;
	double _nHStop  = RulerRange[DATA_VIEW_RULER_BOTTOM].second ;
	double _nHWidth = _nHStop - _nHStart ;

	int _nSceneWidth = m_pGraphicView->GetSceneSize().width()  ;
	int _nSceneHeight= m_pGraphicView->GetSceneSize().height() ;

	double _fX   = pPos_->x()  ;
	double _fY   = pPos_->y()  ;
	_fX = _nSceneWidth * (_fX - _nHStart) / _nHWidth  ;
	_fY   = _nSceneHeight * (_fY - _nVStart) / _nVHeight  ;

	return QPointF(_fX , _fY);
}

/****************************************************************************
  Description: 创建所有的DATAVIEW部件 ， TITLE , RULERS , COLORBAR , CENTER VIEW
*****************************************************************************/
void DopplerDataView::CreateComponent()
{
	DeleteAllWidget();
	m_pLayout =new QGridLayout(this) ;
	//***** space between widget
	m_pLayout->setSpacing(0);
	//***** space offset of layout in parent window
	m_pLayout->setContentsMargins(0 , 0 , 0 , 0);

	QSize _size = this->size() ;
	int _nWidth = _size.width() ;
	int _nHeight= _size.height() ;
	//***************************
	//*   create widget of each cell
	//***************************
	if(m_eComponent & DATA_VIEW_COMPONENT_TITLE)
	{
		m_pTitleBar  = new DopplerTitleBar(this) ;
		m_pLayout->addWidget(m_pTitleBar , 0 , 0 , 1 , 4);
		_nHeight -=  m_pTitleBar->height() ;
	}

	if(m_eComponent & DATA_VIEW_COMPONENT_LEFTRULER)
	{
		m_pRulers[DATA_VIEW_RULER_LEFT] = new DopplerRulerBar(this , DopplerRulerBar::RULER_BAR_LEFT) ;
		m_pLayout->addWidget(m_pRulers[DATA_VIEW_RULER_LEFT] , 1 , 0);
		m_pRulers[DATA_VIEW_RULER_LEFT]->SetMarkerRange(
					RulerRange[DATA_VIEW_RULER_LEFT].first,
					RulerRange[DATA_VIEW_RULER_LEFT].second,
					SliderRange[DATA_VIEW_RULER_LEFT].first,
					SliderRange[DATA_VIEW_RULER_LEFT].second);
		_nWidth -= m_pRulers[DATA_VIEW_RULER_LEFT]->width() ;
	}

	if(m_eComponent & DATA_VIEW_COMPONENT_RIGHTRULER)
	{
		m_pRulers[DATA_VIEW_RULER_RIGHT] = new DopplerRulerBar(this , DopplerRulerBar::RULER_BAR_RIGHT) ;
		m_pLayout->addWidget(m_pRulers[DATA_VIEW_RULER_RIGHT] , 1 , 3);
		m_pRulers[DATA_VIEW_RULER_RIGHT]->SetMarkerRange(
					RulerRange[DATA_VIEW_RULER_RIGHT].first,
					RulerRange[DATA_VIEW_RULER_RIGHT].second,
					SliderRange[DATA_VIEW_RULER_RIGHT].first,
					SliderRange[DATA_VIEW_RULER_RIGHT].second);
		_nWidth -= m_pRulers[DATA_VIEW_RULER_RIGHT]->width() ;
	}

	if(m_eComponent & DATA_VIEW_COMPONENT_BOTTOMRULER)
	{
		m_pRulers[DATA_VIEW_RULER_BOTTOM] = new DopplerRulerBar(this , DopplerRulerBar::RULER_BAR_BOTTOM) ;
		m_pLayout->addWidget(m_pRulers[DATA_VIEW_RULER_BOTTOM] , 2 , 1);
		m_pRulers[DATA_VIEW_RULER_BOTTOM]->SetMarkerRange(
					RulerRange[DATA_VIEW_RULER_BOTTOM].first,
					RulerRange[DATA_VIEW_RULER_BOTTOM].second,
					SliderRange[DATA_VIEW_RULER_BOTTOM].first,
					SliderRange[DATA_VIEW_RULER_BOTTOM].second);
		_nHeight -=  m_pRulers[DATA_VIEW_RULER_BOTTOM]->height() ;
	}

	if(m_eComponent & DATA_VIEW_COMPONENT_COLORBAR)
	{
		m_pColorBar = new DopplerColorBar(this) ;
		m_pLayout->addWidget(m_pColorBar , 1, 2);
		_nWidth -= m_pColorBar->width() ;
	}

	//***************************************
	//** center widget for data displaying
	//***************************************
	m_pGraphicView = new DopplerGraphicView(this , QSize(_nWidth , _nHeight)) ;
	m_pLayout->addWidget(m_pGraphicView , 1 , 1)  ;
	connect(m_pGraphicView , SIGNAL(signalViewChanged(QRectF)) , SLOT(slotZoomAction(QRectF)));
	connect(m_pGraphicView , SIGNAL(signalItemMoved(DopplerGraphicsItem*)) , SLOT(slotItemMoved(DopplerGraphicsItem*)));
    connect(m_pGraphicView , SIGNAL(signalItemPressed(DopplerGraphicsItem*)) , SLOT(slotItemPressed(DopplerGraphicsItem*)));
	connect(m_pGraphicView , SIGNAL(signalButtonRelease(QMouseEvent*)) , SLOT(slotViewMouseRelease(QMouseEvent*)));
	connect(m_pGraphicView , SIGNAL(signalButtonPressed(QMouseEvent*)) , SLOT(slotViewMousePressed(QMouseEvent*)));
	connect(m_pGraphicView , SIGNAL(signalButtonDoubleClicked(QPointF)) , SLOT(slotMouseDoubleClicked(QPointF))) ;

	connect(m_pGraphicView , SIGNAL(signalTofdDragProAction(QPointF, QPointF)) , SLOT(slotTofdDragProAction(QPointF, QPointF))) ;

	setLayout(m_pLayout);
}


void DopplerDataView::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	QSize _size = size() ;
	int _nWidth = _size.width() ;
	int _nHeight= _size.height() ;
	//***************************
	//*   create widget of each cell
	//***************************
	if(m_pTitleBar)
		_nHeight -=  m_pTitleBar->height() ;

	if(m_pRulers[DATA_VIEW_RULER_LEFT])
		_nWidth -= m_pRulers[DATA_VIEW_RULER_LEFT]->width() ;

	if(m_pRulers[DATA_VIEW_RULER_RIGHT])
		_nWidth -= m_pRulers[DATA_VIEW_RULER_RIGHT]->width() ;

	if(m_pRulers[DATA_VIEW_RULER_BOTTOM])
		_nHeight -=  m_pRulers[DATA_VIEW_RULER_BOTTOM]->height() ;

	if(m_pColorBar)
		_nWidth -= m_pColorBar->width() ;

	m_pGraphicView->resize(_nWidth , _nHeight);

	emit signalDataViewResized(this);
}

void DopplerDataView::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event) ;
}

void DopplerDataView::slotViewMouseRelease(QMouseEvent *event)
{
	mouseReleaseEvent(event);
}
void DopplerDataView::slotViewMousePressed(QMouseEvent* event)
{
	mousePressEvent(event);
}

void DopplerDataView::slotMouseDoubleClicked(QPointF pos_)
{
	QPointF _pos = PixTransferToReal(pos_) ;
	emit signalMouseDoubleClicked(this , _pos) ;
}

#include "DopplerTofdOpp.h"
void DopplerDataView::slotTofdDragProAction(QPointF ptS_, QPointF ptE_)
{
	QPointF _pt1 = PixTransferToReal(ptS_);
	QPointF _pt2 = PixTransferToReal(ptE_);

	AREAF _area;
	DopplerTofdOpp opp ;

	if(m_eDisplayMode == setup_DISPLAY_MODE_B_H)
	{
	_area.x = (_pt1.x() < _pt2.x()) ? _pt1.x() : _pt2.x();
	_area.y = (_pt1.y() < _pt2.y()) ? _pt1.y() : _pt2.y();
	_area.width  = fabs(_pt2.x() - _pt1.x());
	_area.height = fabs(_pt2.y() - _pt1.y());
	}
	else if(m_eDisplayMode == setup_DISPLAY_MODE_B_V)
	{
	_area.x = (_pt1.y() < _pt2.y()) ? _pt1.y() : _pt2.y();
	_area.y = (_pt1.x() < _pt2.x()) ? _pt1.x() : _pt2.x();
	_area.width  = fabs(_pt2.y() - _pt1.y());
	_area.height = fabs(_pt2.x() - _pt1.x());
	}
	else
	{
	opp.TofdClearDragStatus(m_nGroupId);
	return;
	}

	opp.TofdDragProcess(m_nGroupId, _area);
	g_pMainWnd->RunDrawThreadOnce(false);
}

void DopplerDataView::slotScanRangeMove(int nType_, int nStart_, int nStop_)
{
	if(m_pGraphicView->GetZoomStatus())
		return;
	ParameterProcess* _process = ParameterProcess::Instance();
	double _nStart = _process->SAxisIndexToDist(nStart_);
	double _nStop  = _process->SAxisIndexToDist(nStop_);

	double _nSliderStart , _nSliderStop;

	switch(nType_)
	{
	case 0:
	case 3:
		RulerRange[DATA_VIEW_RULER_LEFT].first  = _nStop;
		RulerRange[DATA_VIEW_RULER_LEFT].second = _nStart;
		if(m_pRulers[DATA_VIEW_RULER_LEFT]) {
			m_pRulers[DATA_VIEW_RULER_LEFT]->GetMarkerRange(&_nStart , &_nStop, &_nSliderStart , &_nSliderStop);
			m_pRulers[DATA_VIEW_RULER_LEFT]->SetMarkerRange(
						RulerRange[DATA_VIEW_RULER_LEFT].first ,
						RulerRange[DATA_VIEW_RULER_LEFT].second,
						_nSliderStart , _nSliderStop);
		}
		break;
	case 1:
	case 2:
		RulerRange[DATA_VIEW_RULER_BOTTOM].first  = _nStart;
		RulerRange[DATA_VIEW_RULER_BOTTOM].second = _nStop;
		if(m_pRulers[DATA_VIEW_RULER_BOTTOM]) {
			m_pRulers[DATA_VIEW_RULER_BOTTOM]->GetMarkerRange(&_nStart , &_nStop, &_nSliderStart , &_nSliderStop);
			m_pRulers[DATA_VIEW_RULER_BOTTOM]->SetMarkerRange(
						RulerRange[DATA_VIEW_RULER_BOTTOM].first ,
						RulerRange[DATA_VIEW_RULER_BOTTOM].second,
						_nSliderStart , _nSliderStop);
		}
		break;
    }
    this->update();
    if(m_pItemsGroup){
        m_pItemsGroup->UpdateItems();
    }
}

void DopplerDataView::mouseReleaseEvent(QMouseEvent* event)
{
	if(Qt::RightButton != event->button()) return ;

	if(m_pItemsGroup) {
		m_pItemsGroup->UpdateItems();
    }
}

void DopplerDataView::mousePressEvent (QMouseEvent* )
{
	g_pMainWnd->SetCurGroup(m_nGroupId);
	emit signalMousePressed(this) ;
}

void DopplerDataView::RangeTransfer(QPair<double , double> range_ , QPair<double , double>* pos_)
{
	double _nRange = range_.second  - range_.first  ;
	pos_->first = _nRange * pos_->first + range_.first  ;
	pos_->second= _nRange * pos_->second + range_.first ;
}

void DopplerDataView::slotZoomAction(QRectF rect)
{
	double _nStart , _nStop, _nSliderStart , _nSliderStop;

	if(m_eComponent & DATA_VIEW_COMPONENT_LEFTRULER)
	{
		QPair<double , double> _marker ;
		_marker.first = rect.top() ;
		_marker.second= rect.bottom() ;
		RangeTransfer(RulerRange[DATA_VIEW_RULER_LEFT] , &_marker) ;

		//ZoomRange[DATA_VIEW_RULER_LEFT].first = _marker.first;
		//ZoomRange[DATA_VIEW_RULER_LEFT].second = _marker.second;
		m_pRulers[DATA_VIEW_RULER_LEFT]->GetMarkerRange(&_nStart , &_nStop, &_nSliderStart , &_nSliderStop);
		m_pRulers[DATA_VIEW_RULER_LEFT]->SetMarkerRange(_marker.first , _marker.second, _nSliderStart , _nSliderStop);
	}

	if(m_eComponent & DATA_VIEW_COMPONENT_BOTTOMRULER)
	{
		QPair<double , double> _marker ;
		_marker.first = rect.left() ;
		_marker.second= rect.right() ;
		RangeTransfer(RulerRange[DATA_VIEW_RULER_BOTTOM] , &_marker) ;

		//ZoomRange[DATA_VIEW_RULER_BOTTOM].first = _marker.first;
		//ZoomRange[DATA_VIEW_RULER_BOTTOM].second = _marker.second;
		m_pRulers[DATA_VIEW_RULER_BOTTOM]->GetMarkerRange(&_nStart , &_nStop, &_nSliderStart , &_nSliderStop);
		m_pRulers[DATA_VIEW_RULER_BOTTOM]->SetMarkerRange(_marker.first , _marker.second, _nSliderStart , _nSliderStop);
	}

	if(m_pItemsGroup) {
		m_pItemsGroup->UpdateItems();
	}

}

QRectF DopplerDataView::slotItemSetAngleLineLimit(QRectF &_rect, DopplerGraphicsItem* pItem_)
{
    int _nGroupId , _nLawId , _nDisplay;
    GetDataViewConfigure(&_nGroupId,  &_nLawId,  &_nDisplay);
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[_nGroupId];
    LAW_CONFIG _law = _group.law ;
    float _fAngleStop = _law.nAngleStopRefract / 10.0 ;
    float _fAngleStart = _law.nAngleStartRefract / 10.0 ;
    QRectF rect(_rect);
    if(DopplerLineItem::LINE_HORIZENTAL == ((DopplerCScanLineMark*)pItem_)->GetLineType()){
        qDebug("%s[%d]: MarkQty:%d \n", __FUNCTION__, __LINE__, m_pItemsGroup->GetLawMarkerLinesCount());
        if(_fAngleStop == 0 && _fAngleStart == 0 && _law.eLawType == 1){
            if(rect.top()<0)
            {
                rect.setTop(0);
            }/*else if(rect.top() > m_pItemsGroup->GetLawMarkerLinesCount()){
                rect.setTop(m_pItemsGroup->GetLawMarkerLinesCount());
            }*/
            return rect;
        }
        if(rect.top() > _fAngleStop){
            rect.setTop(_fAngleStop);
        }else if(rect.top() < _fAngleStart){
            rect.setTop(_fAngleStart);
        }
    }else{
        if(_fAngleStop == 0 && _fAngleStart == 0 && _law.eLawType == 1){
            if(rect.left()<0)
            {
                rect.setLeft(0);
            }/*else if(rect.left() > m_pItemsGroup->GetLawMarkerLinesCount()){
                rect.setLeft(m_pItemsGroup->GetLawMarkerLinesCount());
            }*/
            return rect;
        }
        if(rect.left() > _fAngleStop){
            rect.setLeft(_fAngleStop);
        }else if(rect.left() < _fAngleStart){
            rect.setLeft(_fAngleStart);
        }
    }
    return rect;
}

void DopplerDataView::slotItemMoved(DopplerGraphicsItem* item_)
{
	QPointF _pos1 = item_->GetItemScenePos()  ;
	QPointF _pos2 = PixTransferToReal(_pos1)  ;
	QRectF _rect = item_->GetItemGeometryReal();
	_rect = QRectF(_pos2.x() , _pos2.y() , _rect.width() , _rect.height())  ;
    int _nItemType = item_->GetItemType();
    int _nItemId = item_->GetItemId();
    if(_nItemType == DOPPLER_GRAPHICS_ITEM_CURSOR && _nItemId == setup_CURSOR_C_ANGLE){
        _rect = slotItemSetAngleLineLimit(_rect, item_);
    }

	item_->SetItemGeometryReal(_rect)   ;
	emit signalItemMoved(this , item_)  ;

}

void DopplerDataView::slotItemPressed(DopplerGraphicsItem* item_)
{
    int _nItemType =item_->GetItemType();
    static int id = -1;
    if(_nItemType == DOPPLER_GRAPHICS_ITEM_DEFECT)
    {
        if(id == item_->GetItemId())
        {
            if(((DopplerDefectItem*)item_)->IsSelected == id)
            {
                m_pItemsGroup->ResetDefect();
            }
            else
            {
                m_pItemsGroup->ResetDefect();
                ((DopplerDefectItem*)item_)->IsSelected = item_->GetItemId();
            }
        }
        else
        {
            m_pItemsGroup->ResetDefect();
            ((DopplerDefectItem*)item_)->IsSelected = item_->GetItemId();
        }
        id = item_->GetItemId();
    }
}

void DopplerDataView::SetDefect(int id)
{
    m_pItemsGroup->SetItemDefect(id);

}

void DopplerDataView::ResetDefect()
{
    m_pItemsGroup->ResetDefect();

}

/****************************************************************************
  Description: 换算  在场景中的像素位置 到  标尺刻度对应的位置
  Input:	 场景位置
  Output:	标尺对应位置
*****************************************************************************/
QPointF DopplerDataView::PixTransferToReal(QPointF& pos_)
{
	double _nPosX = pos_.x() ;
	double _nPosY = pos_.y() ;

	double _nVStart = RulerRange[DATA_VIEW_RULER_LEFT].first  ;
	double _nVStop  = RulerRange[DATA_VIEW_RULER_LEFT].second ;
	double _nVHeight= _nVStop - _nVStart ;

	double _nHStart = RulerRange[DATA_VIEW_RULER_BOTTOM].first  ;
	double _nHStop  = RulerRange[DATA_VIEW_RULER_BOTTOM].second ;
	double _nHWidth = _nHStop - _nHStart ;

	int _nSceneWidth = m_pGraphicView->GetSceneSize().width()  ;
	int _nSceneHeight= m_pGraphicView->GetSceneSize().height() ;

	_nPosX  = _nHWidth * _nPosX / _nSceneWidth +  _nHStart  ;
	_nPosY  = _nVHeight* _nPosY / _nSceneHeight + _nVStart  ;


	return QPointF(_nPosX , _nPosY) ;
}

void DopplerDataView::SetWidgetSelected(bool bSelect_)
{
	if(bSelect_ != m_bSelected)
	{
		m_bSelected = bSelect_;
		setBackgroundRole(m_bSelected ? QPalette::Highlight : QPalette::Background);
	}
}


void DopplerDataView::UpdateScene()
{
	m_pGraphicView->UpdateSceneRegion();
}


DopplerViewItems* DopplerDataView::GetItemGroup() const
{
	return m_pItemsGroup ;
}

QRect DopplerDataView::GetZoomRect()
{
	QRect _rect(0,0,0,0);
	if(m_pGraphicView) {
		if(m_pGraphicView->GetZoomStatus()) {
			_rect = m_pGraphicView->GetZoomRect();
		} else {
			_rect.setLeft(0);
			_rect.setTop(0);
			_rect.setWidth(m_pGraphicView->width());
			_rect.setHeight(m_pGraphicView->height());
		}
	}
	int _nWidth  = _rect.width();
	int _nHeight = _rect.height();
	_rect.setLeft(_rect.left());
	_rect.setTop(_rect.top());
	_rect.setWidth(_nWidth - 4);
	_rect.setHeight(_nHeight - 4);
	/*
	int _nWidth  = _rect.width();
	int _nHeight = _rect.height();
	_rect.setLeft(_rect.left()+1);
	_rect.setTop(_rect.top()+1);
	_rect.setWidth(_nWidth - 4);
	_rect.setHeight(_nHeight - 4);
	*/
	return _rect;
}
