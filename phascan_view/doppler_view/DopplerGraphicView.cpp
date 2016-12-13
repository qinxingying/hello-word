#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

#include "DopplerViewItems.h"
#include "DopplerGraphicView.h"
#include "DopplerDrawScan.h"
#include "DopplerTofdOpp.h"
#include "DopplerGateItem.h"
#include "DopplerDataView.h"

#include <QPrintDialog>
#include <QPrinter>
#include <qmath.h>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QTimer>
#include <gHeader.h>
#include <QObject>
#include <QMutex>

static const QSize FIXED_SCENE_SIZE( 480 , 360) ;


#define DPL_BASE_IMAGE_FORMATE	 (QImage::Format_RGB888)

class GraphicsViewBase:public QGraphicsWidget
{
public:
	GraphicsViewBase(QGraphicsItem *parent = 0 , QSize cSize_ = QSize(480 , 360))
		: QGraphicsWidget(parent)
	{
		//m_hMutex.lock();
		setWindowFlags(Qt::Window | Qt::CustomizeWindowHint
									 | Qt::WindowTitleHint | Qt::FramelessWindowHint);
		m_cSize = cSize_ ;
		m_pImage = new QImage(m_cSize , DPL_BASE_IMAGE_FORMATE) ;
		ClearImage() ;
		setZValue(1);
		//m_hMutex.unlock();
		setAcceptDrops(true);
	}

	~GraphicsViewBase()
	{
		delete m_pImage;
	}

	QImage* GetBaseImage()
	{
		return m_pImage;
	}

	void ResetBaseImage(QSizeF size_)
	{
		//m_hMutex.lock();
		m_cSize = QSize((int)size_.width() , (int)size_.height())  ;
		if(m_pImage) delete m_pImage ;
		m_pImage = new QImage(m_cSize , DPL_BASE_IMAGE_FORMATE) ;
		ClearImage() ;
		//m_hMutex.unlock();
	}

	void ClearImage()
	{
		unsigned char* _pData = m_pImage->bits() ;
		memset(_pData, 0 , m_pImage->bytesPerLine() * m_pImage->height() );
	}

	void resizeEvent(QGraphicsSceneResizeEvent *event)
	{
		ResetBaseImage(event->newSize())  ;
		QGraphicsWidget::resizeEvent(event) ;
	}

	void paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0)
	{
		if(m_pImage)
		{
			m_hMutex.lock();
			painter->drawImage(QRect(0 , 0 , m_cSize.width() , m_cSize.height()), *m_pImage);
			m_hMutex.unlock();
		}
	}
public:
	QMutex m_hMutex;
private:
	QImage* m_pImage ;
	QSize   m_cSize  ;

};


DopplerGraphicView::DopplerGraphicView(QWidget *parent , QSize size_) :
	QGraphicsView(parent)
{
	// disable scroll bar
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//****************************************************
	// inittialize this view
	resize(size_);
	setRenderHint(QPainter::Antialiasing, true);
	setDragMode(QGraphicsView::RubberBandDrag);
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	m_pDrawScan   = NULL ;
	m_pScene	  = NULL ;
	m_pBackGround = NULL ;
	m_nScaleH = 1.0 ;
	m_nScaleV = 1.0 ;
	InitGraphicView(size());
	//****************************************************
	// connect update signal for multi threads update user interface
	connect( this , SIGNAL(signalUpdateDrawing())  ,
					SLOT(slotUpdateDrawing())
					//,Qt::QueuedConnection
			 )  ;
	// pass the drop event to father widget
	setAcceptDrops(false);
	// use openGL to render drawing
	//##############################
	//EnableRenderOpenGL(true) ;
	//##############################
	setRenderHint(QPainter::Antialiasing, true);
	for(int i = 0 ; i < 5 ; i++)  m_strMeasure[i].clear();
	m_nMeasureQty  = 0 ;

//	m_bBCAutoZomm = true;
//	m_bZommInit = false;
	m_bZoom     = false;
//	m_nTimerId = startTimer(100);
}


DopplerGraphicView::~DopplerGraphicView()
{
	delete   m_pBackGround	;
	delete   m_pScene;		;
	delete   m_pDrawScan	  ;

//	if(m_nTimerId != 0)
//		killTimer(m_nTimerId);
}

static QRect mRect ;

//void DopplerGraphicView::timerEvent( QTimerEvent *event )
//{
//}

void DopplerGraphicView::InitGraphicView(const QSize& cSize_)
{

	QRect cRect(0 , 0 , cSize_.width() , cSize_.height()) ;
	mRect = cRect ;
	// 创建背景
	if(!m_pBackGround) //delete m_pBackGround ;
		m_pBackGround = new GraphicsViewBase(0);
	m_pBackGround->setGeometry (cRect);
	// 创建场景
	if(!m_pScene)
	{
		m_pScene = new QGraphicsScene();
		m_pScene->setItemIndexMethod(QGraphicsScene::NoIndex);
		setScene(m_pScene);
		m_pScene->addItem(m_pBackGround);
	}
	//set display zoom
	this->setSceneRect(cRect);
}

void DopplerGraphicView::slotResetView()
{
	m_bZoom     = false;
	SetupMatrixScale(1.0 , 1.0 );
	ensureVisible(QRectF(0 , 0 , 0 , 0));
}

//----------------------------------------------------------
//  wuhan cursor 2015-05-19
void DopplerGraphicView::mouseCursorPro(QMouseEvent *event)
{
	setCursor(QCursor(Qt::ArrowCursor));
	QList<QGraphicsItem*> listCursor = m_pScene->items() ;
	for(int i = 0; i < listCursor.count(); i++)
	{
		DopplerGraphicsItem* _item = (DopplerGraphicsItem*)listCursor.at(i);
		if(!_item->isWindow())
		{
			if(_item->GetItemType() == DOPPLER_GRAPHICS_ITEM_CURSOR)
			{
				DopplerLineItem* _Line = (DopplerLineItem*)_item;
				Qt::CursorShape _cursorShape = _Line->GetCursorShape(event->pos());

				if(_cursorShape != Qt::ArrowCursor)
				{
					setCursor(QCursor(_cursorShape));
					return;
				}
			}
		}
	}
	setCursor(QCursor(Qt::ArrowCursor));
}
//----------------------------------------------------------

void DopplerGraphicView::SetupMatrixScale(double nScaleH_ , double nScaleV_)
{
	m_nScaleH = nScaleH_  ; m_nScaleV = nScaleV_;
	QMatrix matrix;
	matrix.scale(m_nScaleH * m_nScaleBaseH , m_nScaleV  * m_nScaleBaseV);
	setMatrix(matrix);
	GeometryChanged() ;
}

void DopplerGraphicView::slotPrint()
{
#ifndef QT_NO_PRINTER
	QPrinter printer;
	QPrintDialog dialog(&printer, this);
	if (dialog.exec() == QDialog::Accepted) {
		QPainter painter(&printer);
		render(&painter);
	}
#endif
}

void DopplerGraphicView::wheelEvent ( QWheelEvent * event )
{
	if(tofdProAction() < 0)
	{
		int numDegrees = event->delta() / 8;
		int numSteps = numDegrees / 15;

		m_nScaleH += numSteps / 10.0 ;
		m_nScaleV += numSteps / 10.0 ;

		if(m_nScaleH < 1) {m_nScaleV = m_nScaleH = 1 ;}
		if(m_nScaleH > 10) {m_nScaleV = m_nScaleH = 10 ;}
		//****************************************
		QPointF _nCenter = mapToScene((event->pos()));
		if(m_nScaleH > 1) {
			QSize _size = size();
			//float _fWidth   = ((double)_size.width()) / m_nScaleH;
			//float _nHeight  = ((double)_size.height()) / m_nScaleV;
			int _fWidth   = ((double)_size.width()) / m_nScaleH;
			int _nHeight  = ((double)_size.height()) / m_nScaleV;

			QRect _rect;
			_rect.setLeft(_nCenter.x() - _fWidth / 2);
			_rect.setTop(_nCenter.y() - _nHeight / 2);
			_rect.setWidth(_fWidth);
			_rect.setHeight(_nHeight);
			if(_rect.left() < 0) {
				_rect.setLeft(0);
				_rect.setWidth(_fWidth);
			}

			if(_rect.top() < 0) {
				_rect.setTop(0);
				_rect.setHeight(_nHeight);
			}

			if(_rect.right() >= _size.width()) {
				_rect.setLeft(_size.width() - _fWidth);
				_rect.setWidth(_fWidth);
			}

			if(_rect.right() >= _size.height()) {
				_rect.setTop(_size.height() - _nHeight);
				_rect.setHeight(_nHeight);
			}

			_nCenter.setX(_rect.left() + _fWidth / 2);
			_nCenter.setY(_rect.top() + _nHeight / 2);

			m_cZoomRect = _rect;
			m_bZoom     = true;
		} else {
			m_bZoom     = false;
		}
		//****************************************
		//centerOn(mapToScene((event->pos())));
		centerOn(_nCenter);
		SetupMatrixScale( m_nScaleH , m_nScaleV ) ;
	}
}

void DopplerGraphicView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	int _nWidth = event->size().width() ;
	int _nHeight= event->size().height() ;

	if(m_pBackGround)
	{
		m_pBackGround->setGeometry(0 , 0 , _nWidth, _nHeight);
		setSceneRect(0 , 0 , _nWidth, _nHeight);
	}

	m_nScaleBaseH =  _nWidth / m_pBackGround->size().width()  ;
	m_nScaleBaseV =  _nHeight/ m_pBackGround->size().height() ;

	centerOn(m_pScene->sceneRect().center());
	SetupMatrixScale( 1 , 1) ;

	DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
	QList<QGraphicsItem*> list = m_pScene->items() ;
	for(int i = 0 ; i < list.count() ; i++)
	{
		DopplerGraphicsItem* _item = (DopplerGraphicsItem*)list.at(i);
		if(!_item->isWindow())
		{
			QRectF _rect = _item->GetItemGeometryReal() ;
			_pParent->SetItemGeometry(_item, _rect);
		}
	}
	_pParent->GetItemGroup()->UpdateItemsLawMarker();
	//***重绘画图区*********
	//UpdateDrawing();
	//**********************
}

void DopplerGraphicView::SetDrawOperation(DopplerDrawScan* pDrawScan_)
{
	m_pDrawScan = pDrawScan_ ;
}

void DopplerGraphicView::mousePressEvent(QMouseEvent *event)
{
	if(Qt::LeftButton == event->button())
	{
		m_cPosStart = event->pos() ;
	}

	QGraphicsView::mousePressEvent(event) ;
	if(m_pScene->selectedItems().isEmpty())
		m_bItemSelected = 0  ;
	else
		m_bItemSelected = 1  ;

	emit signalButtonPressed(event) ;
}

void  DopplerGraphicView::mouseDoubleClickEvent(QMouseEvent* event)
{
	if(Qt::LeftButton  != event->button() )
		return  ;
	QPoint  _pos = event->pos() ;
	QPointF _pos1 = mapToScene(_pos) ;
	emit signalButtonDoubleClicked(_pos1);

}

void DopplerGraphicView::mouseMoveEvent(QMouseEvent *event)
{
	QGraphicsView::mouseMoveEvent(event) ;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  wuhan cursor 2015-05-19
//	mouseCursorPro(event);	还有问题
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	QList<QGraphicsItem*> list = m_pScene->selectedItems();
	if(!list.empty() && m_bItemSelected)
	{
		DopplerGraphicsItem* _item = (DopplerGraphicsItem*)list.at(0) ;
		emit signalItemMoved(_item) ;
	}
}

void DopplerGraphicView::mouseReleaseEvent(QMouseEvent *event)
{
	if(Qt::LeftButton == event->button())
	{
		if(!m_bItemSelected)
		{
			if(Qt::LeftButton == event->button())
			{
				if(FLOAT_EQ(m_nScaleH , 1) && FLOAT_EQ(m_nScaleH , 1))
				{
					m_cPosStop = event->pos() ;
					QRectF _rect = this->geometry();
					if(_rect.contains(m_cPosStop) )
					{
						QRect rect(m_cPosStart , m_cPosStop) ;
						if(tofdProAction() < 0)
						{
							if(!m_bZoom)
								zoomAction(rect);
						}
					}
				}
			}
		}
		else
		{
			QList<QGraphicsItem*> list = m_pScene->selectedItems();
			if(!list.empty())
			{
				DopplerGraphicsItem* _item = (DopplerGraphicsItem*)list.at(0) ;
				emit signalItemMoved(_item) ;
			}
		}
	}
	else if (Qt::RightButton == event->button())
	{
		DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
		int _iGroupId, _iLaw, _iDisplay;
		_pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
		DopplerTofdOpp opp;
		opp.TofdClearDragStatus(_iGroupId);
		UpdateDrawing();

		// 
		DopplerConfigure* _pConfig = DopplerConfigure::Instance();
		_pConfig->ClearDefectInfo(_iGroupId);
		if(FLOAT_EQ(m_nScaleH , 1.0) && FLOAT_EQ(m_nScaleV , 1.0))
			emit signalButtonRelease(event);
		else {
			slotResetView();
		}
	}

	QList<QGraphicsItem*> list = m_pScene->selectedItems();
	for(int i = 0 ; i < list.count() ; i++)
	list.at(i)->setSelected(false);

	QGraphicsView::mouseReleaseEvent(event) ;
}

void DopplerGraphicView::paintEvent(QPaintEvent *event)
{
	QGraphicsView::paintEvent(event) ;
	DrawMeasureValue() ;
	//if(m_bZommInit) {
	//	if(m_bBCAutoZomm) {
	//		CScanZoomAction();
	//	}
	//}
}

void DopplerGraphicView::SetMeasureString(int nIndex_ , QString* str_)
{
	m_strMeasure[nIndex_] = *str_ ;
}

void DopplerGraphicView::SetMeasureStringQty(int nQty_)
{
	m_nMeasureQty = nQty_ > MAX_MEASURE_DATA_DISPLAY ? MAX_MEASURE_DATA_DISPLAY : nQty_  ;
}

void DopplerGraphicView::DrawMeasureValue()
{
	QWidget* _pViewPort = (QWidget*)this->viewport();
	QPainter _painter(_pViewPort) ;

	float _x0 = 10;
	float _y0 = 20;

	DopplerConfigure* _pConfig = DopplerConfigure::Instance();
	ParameterProcess* _process = ParameterProcess::Instance();
	DopplerDataView*  _pParent = (DopplerDataView*)parentWidget();
	int _iGroupId, _iLaw, _iDisplay;
	_pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);

	GROUP_CONFIG&  _group = _pConfig->group[_iGroupId] ;
	_painter.setPen(QPen(Qt::white));

	QBrush _brush(QColor(0,0,0));
	_painter.setBackground(_brush);
	if(g_pMainWnd->ParamBackMode()) {
		_painter.setBackgroundMode(Qt::OpaqueMode);
	} else {
		_painter.setBackgroundMode(Qt::TransparentMode);
	}
	//_painter.setBackgroundMode(g_pMainWnd->ParamBackMode());

	if(_iDisplay >= setup_DISPLAY_MODE_S) {
		int _nMeaNum = _process->GetShowMeasureNumber(_iGroupId);
		int _nLawNum = m_nMeasureQty / _nMeaNum;

		if(_iDisplay == setup_DISPLAY_MODE_S_ATHUMIZ || _iDisplay == setup_DISPLAY_MODE_S_LINEAR)
		{
			if(setup_GROUP_MODE_PA == _group.eGroupMode)
			{
				QSize _size((int)(m_pBackGround->size().width()) , (int)(m_pBackGround->size().height()))  ;
				setup_PROBE_ANGLE _eAngle =  _process->GetProbeAngle(_iGroupId) ;
				int _off = 80;
				switch(_nLawNum)
				{
				case 1:_off = 80;						break;
				case 2:_off = 80 + _nMeaNum * 12;		break;
				case 3:_off = 80 + 2 * _nMeaNum * 12;	break;
				}
				if(_eAngle >= setup_PROBE_PART_SKEW_180 )
				{
					//_iDirection   =  1 ;
					_x0 = _size.width() - 120;
					_y0 = _size.height() - _off;
				}
				else
				{
					//_iDirection   =  0 ;
					_x0 = 10;
					_y0 = _size.height() - _off;
				}
			}
		}

		if(_nLawNum <= 1) {
			int i= 0;
			for(; (i < m_nMeasureQty) && (i < MAX_MEASURE_DATA_DISPLAY) ; i++)
			{
				if(!m_strMeasure[i].isEmpty())
					_painter.drawText(_x0 , _y0 + 12 * i , m_strMeasure[i]);
			}
		} else {
			int idx = 0;
			int n = 0;
			for(int i = 0; i < _nLawNum; i++) {
				switch(i)
				{
				case 0:_painter.setPen(QPen(LAW_1_COLOR));break;
				case 1:_painter.setPen(QPen(LAW_2_COLOR));break;
				case 2:_painter.setPen(QPen(LAW_3_COLOR));break;
				}
				for(int k = 0; k < _nMeaNum; k++) {
					idx = i * _nMeaNum + k;
					if(!m_strMeasure[idx].isEmpty()) {
						_painter.drawText(_x0 , _y0 + 12 * n , m_strMeasure[idx]);
						n++;
					}
				}
				n++;
			}

		}
	} else {
		int i= 0;
		for(; (i < m_nMeasureQty) && (i < MAX_MEASURE_DATA_DISPLAY) ; i++)
		{
			if(!m_strMeasure[i].isEmpty())
				_painter.drawText(_x0 , _y0 + 12 * i , m_strMeasure[i]);
		}

		if(_iDisplay == setup_DISPLAY_MODE_B_H || _iDisplay == setup_DISPLAY_MODE_B_V)
		{
			DopplerTofdOpp opp;
			char _strBuf[256];

			if(opp.TofdProStr(_iGroupId, _strBuf) >= 0)
			{
				_painter.setPen(QPen(Qt::green));
				_painter.drawText(_x0 , _y0 + 12 * i , QString(_strBuf));
				i++;
			}

			if(opp.TofdDragProStr(_iGroupId, _strBuf) >= 0)
			{
				_painter.setPen(QPen(Qt::red));
				_painter.drawText(_x0 , _y0 + 12 * i , QString(_strBuf));
				i++;
			}

			if(_pConfig->m_dfParam[_iGroupId].dfInfo.bValid)
			{
				_painter.setPen(QPen(Qt::green));
				float _fStart;
				float _fData = _pConfig->DefectLengthValue(_iGroupId, &_fStart);
				QString _str ;

				if(_fData >= 0) {
					_str.sprintf("length: %.1f mm", _fData);
					_painter.drawText(_x0 , _y0 + 12 * i , _str);
					i++;
				}

				_fData = _pConfig->DefectHeightValue(_iGroupId, &_fStart);
				if(_fData >= 0) {
					_str.sprintf("height: %.1f mm", _fData);
					_painter.drawText(_x0 , _y0 + 12 * i , _str);
					i++;
				}

				_fData = _pConfig->DefectDepthValue(_iGroupId);
				if(_fData >= 0)	{
					_str.sprintf("depth: %.1f mm", _fData);
					_painter.drawText(_x0 , _y0 + 12 * i , _str);
					i++;
				}
			}

		}
	}

	_painter.end();
}

int DopplerGraphicView::tofdProAction()
{
	int _ret = -1;

	DopplerTofdOpp opp;
	DopplerDataView* _pParent = (DopplerDataView*)parentWidget();

	int _iGroupId, _iLaw, _iDisplay;
	_pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);

	if(opp.TofdDragProStatus(_iGroupId) != TOFD_PRO_NONE)
	{
		QSize  _size = size();
		QPointF _pt1;
		QPointF _pt2;

		float x1 = m_cPosStart.x();
		float y1 = m_cPosStart.y();
		float x2 = m_cPosStop.x();
		float y2 = m_cPosStop.y();
		if(m_bZoom) {
			float _nW = m_cZoomRect.width();
			float _nH = m_cZoomRect.height();
			x1 = m_cZoomRect.left() + x1 * _nW / _size.width();
			y1 = m_cZoomRect.top() + y1 * _nH / _size.height();

			x2 = m_cZoomRect.left() + x2 * _nW / _size.width();
			y2 = m_cZoomRect.top() + y2 * _nH / _size.height();
		}

		_pt1.setX(x1);
		_pt1.setY(y1);

		_pt2.setX(x2);
		_pt2.setY(y2);

		if(_iDisplay == setup_DISPLAY_MODE_B_H)
		{
			signalTofdDragProAction(_pt1, _pt2);
			_ret = 0;
		}
		else if(_iDisplay == setup_DISPLAY_MODE_B_V)
		{
			signalTofdDragProAction(_pt1, _pt2);
			_ret = 0;
		}
	}

	return _ret;
}

void DopplerGraphicView::CScanZoomAction()
{
	if(FLOAT_EQ(m_nScaleH , 1.0) && FLOAT_EQ(m_nScaleV , 1.0))
	{
		DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
		int _iGroupId, _iLaw, _iDisplay;
		_pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);

		ParameterProcess* _process = ParameterProcess::Instance();
		int _iScanLen = _process->GetScanMax() - 1;

		QSize _size = size();
		QRect _rect;
		switch(_iDisplay)
		{
		case setup_DISPLAY_MODE_B_V:
		case setup_DISPLAY_MODE_C_H:
		case setup_DISPLAY_MODE_CC_H:
			if(_iScanLen < _size.width())
			{
				_rect.setLeft(0);
				_rect.setRight(_iScanLen);
				_rect.setTop(0);
				_rect.setBottom(_size.height()-1);
				zoomAction(_rect);
				m_bZoom     = true;
			}
			break;
		case setup_DISPLAY_MODE_B_H:
		case setup_DISPLAY_MODE_C_V:
		case setup_DISPLAY_MODE_CC_V:
			if(_iScanLen < _size.height())
			{
				_rect.setLeft(0);
				_rect.setRight(_size.width()-1);
				//_rect.setTop(0);
				//_rect.setBottom(_iScanLen);
				_rect.setTop(_size.height() - _iScanLen);
				_rect.setBottom(_size.height());
				zoomAction(_rect);
				m_bZoom     = true;
			}
			break;
		}
	}
}

void DopplerGraphicView::zoomAction(QRect rect_)
{
	if(abs(rect_.height()) > 50 && abs(rect_.width()) > 50 )
	{
		m_cZoomRect = rect_;
		m_bZoom     = true;

		QSize _size = size();
		double _nScaleX = ((double)_size.width()) / rect_.width() ;
		double _nScaleY =  ((double)_size.height()) / rect_.height() ;
		//_nScaleX = ((int)(_nScaleX * 100 )) / 100.0  ;
		//_nScaleY = ((int)(_nScaleY * 100 )) / 100.0  ;

		centerOn(mapToScene(rect_.center()));
		SetupMatrixScale(fabs(_nScaleX) , fabs(_nScaleY));
	}

}

void DopplerGraphicView::EnableRenderOpenGL(bool bEnable_)
{
#ifdef QT_OPENGL_LIB
	if(bEnable_)
	{
		QGLWidget* _pView = new QGLWidget(QGLFormat(QGL::SampleBuffers))  ;
		_pView->setAutoFillBackground(false);
		setViewport(_pView);
	}
	else
#endif
		setViewport(new QWidget);
}

void DopplerGraphicView::SetBackgroundBrush(const QColor& color)
{
	QImage* pImage = m_pBackGround->GetBaseImage() ;
	QPainter painter(pImage);
	painter.fillRect(pImage->rect() , color);
}

void DopplerGraphicView::GeometryChanged()
{
	QPolygonF _rect	= mapToScene (rect()) ;
	QRectF  rectDisplay = _rect.boundingRect();
	QRectF  rangeDisplay  = RangeTranslate(rectDisplay)  ;
	emit signalViewChanged(rangeDisplay)  ;
}

QRectF DopplerGraphicView::RangeTranslate(QRectF& rect_)
{
	QRectF scene = sceneRect() ;
	double _nSceneWidth = scene.width() , _nSceneHeight = scene.height() ;

	double _nStartX , _nStopX, _nStartY , _nStopY ;
	_nStartX = rect_.left() / _nSceneWidth  ;
	_nStopX  = rect_.right() / _nSceneWidth ;

	_nStartY = rect_.top() / _nSceneHeight	 ;
	_nStopY  = rect_.bottom() / _nSceneHeight  ;

	//_nStartX = ((int) (_nStartX * 100)) / 100.0 ;
	//_nStopX  = ((int) (_nStopX  * 100)) / 100.0 ;
	//_nStartY = ((int) (_nStartY * 100)) / 100.0 ;
	//_nStopY  = ((int) (_nStopY  * 100)) / 100.0 ;

	return QRectF( _nStartX , _nStartY , _nStopX - _nStartX ,  _nStopY - _nStartY )  ;
}


void DopplerGraphicView::AddOverlayItems(QGraphicsItem* item_)
{
	if(item_)
		m_pScene->addItem(item_);
}

QSize DopplerGraphicView::GetSceneSize()
{
	QSize _size((int)(m_pBackGround->size().width()) , (int)(m_pBackGround->size().height()))  ;
	return _size  ;
}

void DopplerGraphicView::SetDrawScan(DopplerDrawScan*  pDrawScan_)
{
	if(m_pDrawScan) delete m_pDrawScan ;
	m_pDrawScan = pDrawScan_  ;
}

DopplerDrawScan* DopplerGraphicView::GetDrawScan() const
{
	return  m_pDrawScan ;
}

/****************************************************************************
  Name:  UpdateDrawing
  Copyright: Sheng Shen
  Author: Sheng Shen
  Description:   调用DrawScan的Draw函数绘制数据 并发送刷新信号到主线程
*****************************************************************************/
void DopplerGraphicView::UpdateDrawing()
{
	if(m_pDrawScan)
	{
		m_pBackGround->m_hMutex.lock();
		m_pDrawScan->Draw (m_pBackGround->GetBaseImage());
		m_pBackGround->m_hMutex.unlock();
	}
	emit signalUpdateDrawing();
}
/****************************************************************************
  Name:  UpdateSceneRegion
  Copyright: Sheng Shen
  Author: Sheng Shen
  Description:   刷新场景
*****************************************************************************/
void DopplerGraphicView::UpdateSceneRegion()
{
	if(m_pScene)
		m_pScene->update();
}

/****************************************************************************
  Name:  slotUpdateDrawing
  Copyright: Sheng Shen
  Author: Sheng Shen
  Description:   刷新画布
*****************************************************************************/
void DopplerGraphicView::slotUpdateDrawing()
{
	if(m_pDrawScan)
	{
		m_pBackGround->update();
	}
}


