#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

#include "DopplerViewItems.h"
#include "DopplerGraphicView.h"
#include "DopplerDrawScan.h"
#include "DopplerDrawBScan.h"
#include "DopplerDrawCScan.h"
#include "DopplerTofdOpp.h"
#include "DopplerGateItem.h"
#include "DopplerDataView.h"
#include "aidedanalysis.h"
#include "dialog/dialogdefectselect.h"
#include "CalcMeasurement.h"
#include <QDebug>
#include <QPrintDialog>
#include <QPrinter>
#include <qmath.h>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <gHeader.h>
#include <QObject>
#include <QMutex>
#include "defectidentify.h"

static const QSize FIXED_SCENE_SIZE( 480 , 360);


#define DPL_BASE_IMAGE_FORMATE	 (QImage::Format_RGB888)  //存入格式为R, G, B 对应 0,1,2

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
        m_scaleH = 1.0;
        m_scaleV = 1.0;
        m_fix    = false;
        m_transferX = 0;
        m_transferY = 0;
        ParameterProcess* _process = ParameterProcess::Instance();
        m_scanIndex = _process->GetScanIndexNum();
		ClearImage() ;
		setZValue(1);
		//m_hMutex.unlock();
		setAcceptDrops(true);
	}

	~GraphicsViewBase()
	{
		delete m_pImage;
        //m_hMutex.unlock();
	}

	QImage* GetBaseImage()
	{
		return m_pImage;
	}



	void ResetBaseImage(QSizeF size_)
	{
		//m_hMutex.lock();
        //m_cSize = QSize((int)size_.width() , (int)size_.height());
        m_cSize = QSize( size_.width()*m_scaleH, size_.height()*m_scaleV);
		if(m_pImage) delete m_pImage ;
		m_pImage = new QImage(m_cSize , DPL_BASE_IMAGE_FORMATE) ;
		ClearImage() ;
		//m_hMutex.unlock();
	}

    void SetFixStatus( bool status)
    {
        m_fix = status;
    }

    void SetFixDirection( int direction)
    {
        if(direction == 0 || direction == 1){
            m_fixDirection = direction;
        }
    }

    int GetScanIndex()
    {
        return m_scanIndex;
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

    void setScaleFactor( double scaleH, double scaleV)
    {
        m_scaleH = scaleH;
        m_scaleV = scaleV;
        QSizeF viewSize = size();
        if(m_fix){
            if(!m_fixDirection){
                double fix = m_scanIndex / viewSize.width();
                if( fix > 1.0){
                    m_cSize = QSize( viewSize.width()*m_scaleH*fix, viewSize.height()*m_scaleV);
                }else{
                    m_cSize = QSize( viewSize.width()*m_scaleH, viewSize.height()*m_scaleV);
                }
            }else{
                double fix = m_scanIndex / viewSize.height();
                if(fix > 1.0){
                    m_cSize = QSize( viewSize.width()*m_scaleH, viewSize.height()*m_scaleV*fix);
                }else{
                    m_cSize = QSize( viewSize.width()*m_scaleH, viewSize.height()*m_scaleV*fix);
                }
            }
        }else{
            m_cSize = QSize( viewSize.width()*m_scaleH, viewSize.height()*m_scaleV);
        }
        if(m_pImage) delete m_pImage ;
        m_pImage = new QImage(m_cSize , DPL_BASE_IMAGE_FORMATE) ;
        ClearImage();
    }

    void setImageTransfer(double bottomStart, double bottomEnd, double leftStart, double leftEnd)
    {
        if(m_fix){
            DopplerConfigure* _pConfig = DopplerConfigure::Instance();
            SCANNER& _scaner = _pConfig->common.scanner;
            float start = _scaner.fScanStart2;
            float end   = _scaner.fScanend;
            if(!m_fixDirection){
                m_transferY = 0;
                    m_transferX = (start - bottomStart) / (end - start) * m_cSize.width();
                    qDebug()<<"bottomStart"<<bottomStart<<"m_transferX"<<m_transferX<<"m_cSize.width"<<
                              m_cSize.width()<<"start"<<start<<"bottomEnd"<<bottomEnd<<"end"<<end;
            }else{
                m_transferX = 0;
                m_transferY = ( leftStart - end) / (end - start) * m_cSize.height();
                qDebug()<<"leftStart"<<leftStart<<"m_transferY"<<m_transferY<<"m_cSize.height"<<
                          m_cSize.height()<<"start"<<start<<"leftEnd"<<leftEnd<<"end"<<end;
            }
        }else{
            m_transferX = 0;
            m_transferY = 0;
        }
    }

    //重绘时由于是放大了image，item就不要缩放
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0)
	{
        if(m_pImage)
		{
			m_hMutex.lock();
            double scaleX = 1.0 / painter->matrix().m11();
            double scaleY = 1.0 / painter->matrix().m22();
            painter->scale( scaleX, scaleY);
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->drawImage(QRect( m_transferX, m_transferY, m_cSize.width() , m_cSize.height()), *m_pImage);
//            painter->drawImage(QRect(0 , 0 , m_cSize.width() , m_cSize.height()), *m_pImage);
			m_hMutex.unlock();
		}
	}

public:
	QMutex m_hMutex;

private:
    QImage* m_pImage;
    QSize   m_cSize;
    double m_scaleH;  //保存水平缩放比例，用于计算image尺寸
    double m_scaleV;  //保存垂直缩放比例，用于计算image尺寸
    bool   m_fix;     //是否需要修正，B，C扫数据大是缩放需要修正
    int    m_fixDirection; //修正的方向 0 水平 1 垂直
    int    m_scanIndex;    //scan的帧数
    int    m_transferX;
    int    m_transferY;
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

	// connect update signal for multi threads update user interface
    connect(this, SIGNAL(signalUpdateDrawing()), SLOT(slotUpdateDrawing()));
    connect(this, SIGNAL(signalScanPosChange(int)), g_pMainWnd, SLOT(slotScanPosChange(int)));
    connect(this, SIGNAL(signalLawPosChange(int,int,int)), g_pMainWnd, SLOT(slotLawPosChange(int,int,int)));
    connect(this, SIGNAL(signalCursorScanChange(int,bool)), g_pMainWnd, SLOT(slotCursorScanChange(int,bool)));
    connect(this, SIGNAL(signalCursorUChange(int,int,bool)), g_pMainWnd, SLOT(slotCursorUChange(int,int,bool)));
    connect(this, SIGNAL(signalShowCursor(int,bool)), g_pMainWnd, SLOT(slotShowCursor(int,bool)));
    connect(this, SIGNAL(signalShowDefect(int,bool)), g_pMainWnd, SLOT(slotShowDefect(int,bool)));
    connect(this, SIGNAL(signalCscanShowallChange(int)), g_pMainWnd, SLOT(slotCsanShowallChange(int)));
    connect(this, SIGNAL(signalMeasureGate(int)), g_pMainWnd, SLOT(slotMeasureGate(int)));
    connect(this, SIGNAL(signalMarkNextDefect()), g_pMainWnd, SLOT(slotMarkNextDefect()));
    connect(this, SIGNAL(signalMarkPreviousDefect()), g_pMainWnd, SLOT(slotMarkPreviousDefect()));
    connect(this, SIGNAL(signalStartAnalysis()), g_pMainWnd, SLOT(on_actionAided_Analysis_triggered()));
	// pass the drop event to father widget
	setAcceptDrops(false);
	// use openGL to render drawing

	//EnableRenderOpenGL(true) ;

	setRenderHint(QPainter::Antialiasing, true);
    for(int i = 0 ; i < 8 ; i++)  m_strMeasure[i].clear();
	m_nMeasureQty  = 0 ;

//	m_bBCAutoZomm = true;
//	m_bZommInit = false;
	m_bZoom     = false;
    m_wheelItemSelect = false;
    m_interactionView = false;
    m_flashMenu = true;
    setFocusPolicy(Qt::StrongFocus);
    creatActionAndMenu();
//	m_nTimerId = startTimer(100);
}


DopplerGraphicView::~DopplerGraphicView()
{
    delete   m_pBackGround;
    delete   m_pScene;
    delete   m_pDrawScan;
}
static QRect mRect;

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
        m_pScene->setSceneRect(cRect);
	}
	//set display zoom
	this->setSceneRect(cRect);
}

void DopplerGraphicView::slotResetView()
{
    //qDebug()<<"m_bZoom"<<m_bZoom;
    if( m_bZoom == false){
        return;
    }
    m_bZoom  = false;
    SetupMatrixScale(1.0, 1.0 );
    ensureVisible(QRectF(0, 0, 0, 0));
    //qDebug()<<"imagechange"<<"slotResetView";
}

void DopplerGraphicView::mouseCursorPro(QMouseEvent *event)
{
	setCursor(QCursor(Qt::ArrowCursor));
    QList<QGraphicsItem*> listCursor = m_pScene->items();
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

/*!
  \brief 对view进行缩放

  \param nScaleH_ 水平缩放因子

  \param nScaleV_ 垂直缩放因子

*/
void DopplerGraphicView::SetupMatrixScale(double nScaleH_ , double nScaleV_)
{
	m_nScaleH = nScaleH_  ; m_nScaleV = nScaleV_;
    if( nScaleH_ == 1 && nScaleV_ == 1){
        m_pBackGround->SetFixStatus(false);
    }
	QMatrix matrix;
	matrix.scale(m_nScaleH * m_nScaleBaseH , m_nScaleV  * m_nScaleBaseV);
	setMatrix(matrix);
    m_pBackGround->setScaleFactor(m_nScaleH * m_nScaleBaseH , m_nScaleV  * m_nScaleBaseV);    
    GeometryChanged();
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

/*!
  \brief 响应鼠标滚轮事件
*/
void DopplerGraphicView::wheelEvent ( QWheelEvent * event )
{
    if(m_wheelItemSelect){
        int offset;
        //qDebug()<<event->angleDelta().y();
        if(event->angleDelta().y() > 0){
            offset = -1;
        }else{
            offset = 1;
        }
        DopplerLineItem::LINE_TYPE lineType = m_tempItem->GetLineType();
        if(lineType == DopplerLineItem::LINE_VERTICAL){
            QPointF temp = m_tempItem->GetItemScenePos();
            temp.setX(temp.x() + offset);
            m_tempItem->setPos(temp);
        }else if(lineType == DopplerLineItem::LINE_HORIZENTAL){
            QPointF temp = m_tempItem->GetItemScenePos();
            temp.setY(temp.y() + offset);
            m_tempItem->setPos(temp);
        }
        emit signalItemMoved(dynamic_cast<DopplerGraphicsItem*>(m_tempItem));
        return QGraphicsView::wheelEvent(event);
    }
//    if(tofdProAction() < 0)
//    {
//        int numDegrees = event->delta() / 8;
//        int numSteps = numDegrees / 15;

//        m_nScaleH += numSteps / 10.0 ;
//        m_nScaleV += numSteps / 10.0 ;

//        int index_scan = 0;
//        DopplerDrawCScanV* _cvDraw = dynamic_cast<DopplerDrawCScanV*>(m_pDrawScan);
//        if( _cvDraw != NULL){
//            if(_cvDraw->getShowAllStatus()){
//                m_pBackGround->SetFixStatus(false);
//            }else{
//                int _sacnIndex = m_pBackGround->GetScanIndex();
//                int _backIndex = m_pBackGround->size().height();
//                if(_sacnIndex > _backIndex){
//                    m_pBackGround->SetFixStatus(true);
//                    m_pBackGround->SetFixDirection(1);
//                    index_scan = 2;
//                }else{
//                    m_pBackGround->SetFixStatus(false);
//                }
//            }
//        }else if( dynamic_cast<DopplerDrawCScanH*>(m_pDrawScan)){
//            DopplerDrawCScanH* _chDraw = dynamic_cast<DopplerDrawCScanH*>(m_pDrawScan);
//            if(_chDraw->getShowAllStatus()){
//                m_pBackGround->SetFixStatus(false);
//            }else{
//                int _sacnIndex = m_pBackGround->GetScanIndex();
//                int _backIndex = m_pBackGround->size().width();
//                if(_sacnIndex > _backIndex){
//                    m_pBackGround->SetFixStatus(true);
//                    m_pBackGround->SetFixDirection(0);
//                    index_scan = 1;
//                }else{
//                    m_pBackGround->SetFixStatus(false);
//                }
//            }
//        }else if(dynamic_cast<DopplerDrawBScanV*>(m_pDrawScan)){
//            DopplerDrawBScanV* _bvDraw = dynamic_cast<DopplerDrawBScanV*>(m_pDrawScan);
//            if(_bvDraw->getShowAllStatus()){
//                m_pBackGround->SetFixStatus(false);
//            }else{
//                int _sacnIndex = m_pBackGround->GetScanIndex();
//                int _backIndex = m_pBackGround->size().width();
//                if(_sacnIndex > _backIndex){
//                    m_pBackGround->SetFixStatus(true);
//                    m_pBackGround->SetFixDirection(0);
//                    index_scan = 1;
//                }else{
//                    m_pBackGround->SetFixStatus(false);
//                }
//            }

//        }else if(dynamic_cast<DopplerDrawBScanH*>(m_pDrawScan)){
//            DopplerDrawBScanH* _bHDraw = dynamic_cast<DopplerDrawBScanH*>(m_pDrawScan);
//            if(_bHDraw->getShowAllStatus()){
//                m_pBackGround->SetFixStatus(false);
//            }else{
//                int _sacnIndex = m_pBackGround->GetScanIndex();
//                int _backIndex = m_pBackGround->size().height();
//                if(_sacnIndex > _backIndex){
//                    m_pBackGround->SetFixStatus(true);
//                    m_pBackGround->SetFixDirection(1);
//                    index_scan = 2;
//                }else{
//                    m_pBackGround->SetFixStatus(false);
//                }
//            }

//        }else{
//            m_pBackGround->SetFixStatus(false);
//        }

//        //缩放比例控制在1-10
//        if(m_nScaleH < 1) {m_nScaleH = 1 ;}
//        if(m_nScaleH > 10) {m_nScaleH = 10 ;}
//        if(m_nScaleV < 1) {m_nScaleV = 1 ;}
//        if(m_nScaleV > 10) {m_nScaleV = 10 ;}

//        //****************************************
//        QPointF _nCenter = mapToScene((event->pos()));

//        //计算在scene里面缩放后对应的矩形框，赋值给m_cZoomRect
//        if(m_nScaleH > 1 && m_nScaleV > 1) {
//            QSize _size = size();
//            int _fWidth   = ((double)_size.width()) / m_nScaleH;
//            int _nHeight  = ((double)_size.height()) / m_nScaleV;
//            //qDebug()<<"m_nScaleH"<<m_nScaleH;

//            QRect _rect;
//            if(index_scan == 1){
//                if( _nCenter.x() > _fWidth / 2){
//                    int _setX = _fWidth - _nCenter.x();
//                    _nCenter.setX(_setX);
//                }
//            }else if(index_scan == 2){
//                if( _nCenter.y() > _nHeight / 2){
//                    int _setY = _nHeight - _nCenter.y();
//                    _nCenter.setY(_setY);
//                }
//            }
//            _rect.setLeft(_nCenter.x() - _fWidth / 2);
//            _rect.setTop(_nCenter.y() - _nHeight / 2);
//            _rect.setWidth(_fWidth);
//            _rect.setHeight(_nHeight);
//            if(_rect.left() < 0) {
//                _rect.setLeft(0);
//                _rect.setWidth(_fWidth);

//            }

//            if(_rect.top() < 0) {
//                _rect.setTop(0);
//                _rect.setHeight(_nHeight);
//            }

//            if(_rect.right() >= _size.width()) {
//                _rect.setLeft(_size.width() - _fWidth);
//                _rect.setWidth(_fWidth);
//            }

//            if(_rect.bottom() >= _size.height()) {
//                _rect.setTop(_size.height() - _nHeight);
//                _rect.setHeight(_nHeight);
//            }
//            _nCenter.setX(_rect.left() + _fWidth / 2);
//            _nCenter.setY(_rect.top() + _nHeight / 2);

//            m_cZoomRect = _rect;
//            m_bZoom = true;
//        } else {
//            m_bZoom = false;

//        }

//        //centerOn(mapToScene((event->pos())));
//        centerOn(_nCenter);
//        SetupMatrixScale( m_nScaleH , m_nScaleV ) ;
//    }
}

void DopplerGraphicView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    int _nWidth = event->size().width();
    int _nHeight= event->size().height();

	if(m_pBackGround)
	{
        m_pBackGround->setGeometry(0, 0, _nWidth, _nHeight);
        setSceneRect(0, 0, _nWidth, _nHeight);
	}

    if(m_pScene)
    {
        m_pScene->setSceneRect(0, 0, _nWidth, _nHeight);
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
}

void DopplerGraphicView::SetDrawOperation(DopplerDrawScan* pDrawScan_)
{
	m_pDrawScan = pDrawScan_ ;
}

void DopplerGraphicView::mousePressEvent(QMouseEvent *event)
{
    if(Qt::RightButton == event->button()){
        DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
        int _iGroupId, _iLaw, _iDisplay;
        _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
        DopplerConfigure* _pConfig = DopplerConfigure::Instance();
        bool dataModeStatus, cursorStatus, defectStatus, showCoupleStatus;
        dataModeStatus = _pConfig->common.dataModeStatus;
        cursorStatus = _pConfig->group[_iGroupId].bShowCursor;
        defectStatus = _pConfig->group[_iGroupId].bShowDefect;
        showCoupleStatus = _pConfig->group[_iGroupId].bShowCoupleInAScan;
        m_dataMode->blockSignals(true);
        m_showCursor->blockSignals(true);
        m_showDefect->blockSignals(true);
        m_showCouple->blockSignals(true);
        m_dataMode->setChecked( dataModeStatus);
        m_showCursor->setChecked( cursorStatus);
        m_showDefect->setChecked( defectStatus);
        m_showCouple->setChecked( showCoupleStatus);
        m_dataMode->blockSignals(false);
        m_showCursor->blockSignals(false);
        m_showDefect->blockSignals(false);
        m_showCouple->blockSignals(false);

        m_scaleRecover->setText(tr("Scale Recover"));
        m_dataMode->setText(tr("Data Mode"));
        m_showCursor->setText(tr("Show Cursor"));
        m_showDefect->setText(tr("Show Defect"));
        m_showCouple->setText(tr("Show Couple"));
        m_selectMeasureMethod->setText(tr("Select Method"));
        m_startAnalysis->setText(tr("Start Analysis"));
        m_contextMenu->clear();
        if (_pConfig->common.bDefectIdentifyStatus) {
            m_contextMenu->addAction(m_startAnalysis);
            m_contextMenu->addAction(m_selectMeasureMethod);
            m_contextMenu->addAction(m_showCursor);
            m_contextMenu->addAction(m_showDefect);
        } else {
            m_contextMenu->addAction(m_scaleRecover);
            if(_iDisplay > 1){
                m_contextMenu->addAction(m_dataMode);
            } else {
                if (_pConfig->group[_iGroupId].coupleMonitoringState) {
                    m_contextMenu->addAction(m_showCouple);
                }
            }
            m_contextMenu->addAction(m_showCursor);
            m_contextMenu->addAction(m_showDefect);
        }

        m_contextMenu->exec(event->globalPos());
    }else{
        if(Qt::LeftButton == event->button())
        {
            m_cPosStart = event->pos() ;
        }

        {
            m_isDrawSelectArea = false;
            DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
            int _iGroupId, _iLaw, _iDisplay;
            _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
            setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;
            switch(_eMode){
            case setup_DISPLAY_MODE_S_ATHUMIZ:
            case setup_DISPLAY_MODE_S_LINEAR: {

                g_pMainWnd->setSelectSscanAreaValid(m_isDrawSelectArea);
                break;
            default:
                    break;
            }
            }
        }

        QGraphicsView::mousePressEvent(event) ;
        if(m_pScene->selectedItems().isEmpty())
            m_bItemSelected = 0  ;
        else
            m_bItemSelected = 1  ;
        QList<QGraphicsItem*> list = m_pScene->selectedItems();
        if(!list.empty() && m_bItemSelected)
        {
            DopplerGraphicsItem* _item = (DopplerGraphicsItem*)list.at(0) ;
            if(Qt::MiddleButton == event->button()){
                if(DopplerLineItem* wheelItem = dynamic_cast<DopplerLineItem*>(_item)){
                    if(wheelItem->GetWheelStatus()){
                        m_tempItem = wheelItem;
                        m_wheelItemSelect = true;
                    }
                }
            }
            emit signalItemPressed(_item) ;
        }

        emit signalButtonPressed(event) ;
    }
    //QGraphicsView::mousePressEvent(event) ;
}

void  DopplerGraphicView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(Qt::LeftButton != event->button())
        return;
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

void DopplerGraphicView::keyPressEvent(QKeyEvent *event)
{
    DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
    int _iGroupId, _iLaw, _iDisplay;
    _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
    //setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;
    if(event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Left){
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_CC_V){
            emit signalScanPosChange(-10);
        //}
        return;
    }else if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Right){
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_CC_V){
            emit signalScanPosChange(10);
        //}
        return;
    }
    switch (event->key()) {
    case Qt::Key_Left:
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_CC_V){
            emit signalScanPosChange(-1);
        //}
        break;
    case Qt::Key_Up:
        //if(_eMode >= setup_DISPLAY_MODE_S && _eMode <= setup_DISPLAY_MODE_S_LINEAR){
            emit signalLawPosChange(_iGroupId, _iLaw, 1);
        //}
        break;
    case Qt::Key_Right:
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_CC_V){
            emit signalScanPosChange(1);
        //}
        break;
    case Qt::Key_Down:
        //if(_eMode >= setup_DISPLAY_MODE_S && _eMode <= setup_DISPLAY_MODE_S_LINEAR){
            emit signalLawPosChange(_iGroupId, _iLaw, -1);
        //}
        break;
    case Qt::Key_0:
        emit signalCscanShowallChange(_iGroupId);
        break;
    case Qt::Key_A:
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_CC_V){
            emit signalCursorScanChange(_iGroupId, false);
        //}
        break;
    case Qt::Key_C:
    {
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_S_LINEAR){
            DopplerConfigure* _pConfig = DopplerConfigure::Instance();
            ParameterProcess* _process = ParameterProcess::Instance();
            if(_pConfig->group[_iGroupId].storeScanLawId.status){
                float scanPos = _pConfig->group[_iGroupId].storeScanLawId.scanPos;
                _process->SetupScanPos(scanPos);
                int lawId = _pConfig->group[_iGroupId].storeScanLawId.lawId;
                if(lawId != _iLaw){
                    emit signalLawPosChange(_iGroupId, lawId, 0);
                }
            }
        //}
        break;
    }
    case Qt::Key_D:
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_CC_V){
            emit signalCursorScanChange(_iGroupId, true);
        //}
        break;
    case Qt::Key_G:
        emit signalMeasureGate(_iGroupId);
        break;
    case Qt::Key_S:
        //if(_eMode >= setup_DISPLAY_MODE_S && _eMode <= setup_DISPLAY_MODE_S_LINEAR){
            emit signalCursorUChange(_iGroupId, _iLaw, false);
        //}
        break;
    case Qt::Key_W:
        //if(_eMode >= setup_DISPLAY_MODE_S && _eMode <= setup_DISPLAY_MODE_S_LINEAR){
            emit signalCursorUChange(_iGroupId, _iLaw, true);
        //}
        break;
    case Qt::Key_Z:
    {
        //if(_eMode >= setup_DISPLAY_MODE_C_H && _eMode <= setup_DISPLAY_MODE_S_LINEAR){
            QMessageBox msgBox;
            msgBox.setText(tr("Store Current LawId and ScanPos ?"));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();
            switch (ret) {
            case QMessageBox::Ok:
            {
                DopplerConfigure* _pConfig = DopplerConfigure::Instance();
                //ParameterProcess* _process = ParameterProcess::Instance();
                _pConfig->group[_iGroupId].storeScanLawId.status = true;
                _pConfig->group[_iGroupId].storeScanLawId.lawId = _iLaw;
                _pConfig->group[_iGroupId].storeScanLawId.scanPos = _pConfig->common.scanner.fScanPos;
                float pResult_ = 0;
                if(_pConfig->group[_iGroupId].measureGateStatus){
                    //_process->SscanGetPeakPoint(_iGroupId, _iLaw, setup_GATE_B, _point);
                    CalcMeasurement::Calc(_iGroupId, _iLaw, FEILD_DB, &pResult_);
                }else{
                    //_process->SscanGetPeakPoint(_iGroupId, _iLaw, setup_GATE_A, _point);
                    CalcMeasurement::Calc(_iGroupId, _iLaw, FEILD_DA, &pResult_);
                }
                _pConfig->group[_iGroupId].storeScanLawId.depth = pResult_;
                pResult_ = 0;
                CalcMeasurement::Calc(_iGroupId, _iLaw, FEILD_ZA, &pResult_);
                _pConfig->group[_iGroupId].storeScanLawId.ZA = static_cast<int>(pResult_);
                g_pMainWnd->RunDrawThreadOnce(true);
                break;
            }
            case QMessageBox::Cancel:
                break;
            default:
                break;
            }
        //}
        break;
    }
    case Qt::Key_Equal: {
        emit signalMarkNextDefect();
        break;
    }
    case Qt::Key_Minus:{
        emit signalMarkPreviousDefect();
        break;
    }
    case Qt::Key_Control: {
        emit signalStartAnalysis();
        break;
    }
    default:
        break;
    }
}

//extern float srcrangestart,srcrangestop;
void DopplerGraphicView::mouseReleaseEvent(QMouseEvent *event)
{
	if(Qt::LeftButton == event->button())
    {        
        if(!m_bItemSelected)
        {
            DopplerConfigure* _pConfig = DopplerConfigure::Instance();
            DopplerDrawCScanH* _cHDraw = dynamic_cast<DopplerDrawCScanH*>(m_pDrawScan);
            if (_pConfig->common.bDefectIdentifyStatus) {
                m_cPosStop = event->pos();
                QRectF _rect = this->geometry();
                if(_rect.contains(m_cPosStop)){
                    QPoint leftTop, rightBottom;
                    if( m_cPosStart.x() < m_cPosStop.x()){
                        leftTop.setX( m_cPosStart.x());
                        rightBottom.setX( m_cPosStop.x());
                    }else{
                        leftTop.setX( m_cPosStop.x());
                        rightBottom.setX( m_cPosStart.x());
                    }

                    if( m_cPosStart.y() < m_cPosStop.y()){
                        leftTop.setY( m_cPosStart.y());
                        rightBottom.setY( m_cPosStop.y());
                    }else{
                        leftTop.setY( m_cPosStop.y());
                        rightBottom.setY( m_cPosStart.y());
                    }
                    QRect rect( leftTop, rightBottom);
                    if(abs(rect.height()) > 5 && abs(rect.width()) > 5){
                        m_selectedArea = rect;

                        DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
                        int _iGroupId, _iLaw, _iDisplay;
                        _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
                        double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop;
                        double _nScaleX1,_nScaleX2,_nScaleY1,_nScaleY2;
                        double scanstart , scanstop;
                        double lawstart, lawstop;
                        QSize _size;
                        _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
                        qDebug()<<"ScanStart"<<_fScanStart<<"ScanStop"<<_fScanStop;
                        _size = size();
                        _nScaleX1 = ((double)leftTop.x()) / _size.width();
                        _nScaleY1 = ((double)leftTop.y()) / _size.height();
                        _nScaleX2 = ((double)rightBottom.x()) / _size.width();
                        _nScaleY2 = ((double)rightBottom.y()) / _size.height();
                        scanstart = _fScanStart + _nScaleX1 * (_fScanStop - _fScanStart);
                        scanstop  = _fScanStart + _nScaleX2 * (_fScanStop - _fScanStart);
                        _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
                        qDebug()<<"indexStart"<<_fScanStart<<"indexStop"<<_fScanStop;
                        lawstart = _fScanStart + _nScaleY1 * (_fScanStop - _fScanStart);
                        lawstop = _fScanStart + _nScaleY2 * (_fScanStop - _fScanStart);
                        qDebug()<<"scanstart"<<scanstart<<"scanstop"<<scanstop<<"lawstart"<<lawstart<<"lawstop"<<lawstop;

                        setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;

                        switch(_eMode){
                        case setup_DISPLAY_MODE_S_ATHUMIZ:
                        case setup_DISPLAY_MODE_S_LINEAR: {
                            QPointF topL(scanstart, lawstart);
                            QPointF bottomR(scanstop, lawstop);
                            QRectF rect(topL, bottomR);
                            g_pMainWnd->setDefectIdentifySScanArea(rect);
                            break;
                        }
                        case setup_DISPLAY_MODE_C_H:
                        case setup_DISPLAY_MODE_CC_H: {
                            g_pMainWnd->setDefectIdentifyCScanArea(scanstart, scanstop, lawstart, lawstop);
                            break;
                        }
                        case setup_DISPLAY_MODE_C_V:
                        case setup_DISPLAY_MODE_CC_V:
                            g_pMainWnd->setDefectIdentifyCScanArea(lawstop, lawstart, scanstart, scanstop);
                            break;
                        case setup_DISPLAY_MODE_B_H:
                            break;

                        case setup_DISPLAY_MODE_B_V:
                            break;
                        }
                        m_isDrawSelectArea = true;
                    } else if (m_cPosStart != m_cPosStop){
                        QMessageBox::warning(this, tr("Range too Small"), tr("Please Selected More Wider Range"));
                    }
                }

            }
            else if(_pConfig->common.aidedAnalysis.aidedStatus && _cHDraw){
                if(FLOAT_EQ(m_nScaleH , 1) && FLOAT_EQ(m_nScaleV , 1)){
                    m_cPosStop = event->pos();
                    QRectF _rect = this->geometry();
                    if(_rect.contains(m_cPosStop)){
                        QPoint leftTop, rightBottom;
                        if( m_cPosStart.x() < m_cPosStop.x()){
                            leftTop.setX( m_cPosStart.x());
                            rightBottom.setX( m_cPosStop.x());
                        }else{
                            leftTop.setX( m_cPosStop.x());
                            rightBottom.setX( m_cPosStart.x());
                        }

                        if( m_cPosStart.y() < m_cPosStop.y()){
                            leftTop.setY( m_cPosStart.y());
                            rightBottom.setY( m_cPosStop.y());
                        }else{
                            leftTop.setY( m_cPosStop.y());
                            rightBottom.setY( m_cPosStart.y());
                        }
                        QRect rect( leftTop, rightBottom);
                        //qDebug()<<"pos"<<m_cPosStart<<m_cPosStop<<rect;
                        if(abs(rect.height()) > 40 && abs(rect.width()) > 40 ){
                            VIEW_ORIENT dirction = ORIENT_HORIZONTAL;
                            if(dynamic_cast<DopplerDrawCScanV*>(m_pDrawScan)){
                                dirction = ORIENT_VERTICAL;
                            }
                            DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
                            int _iGroupId, _iLaw, _iDisplay;
                            _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
                            double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop;
                            double _nScaleX1,_nScaleX2,_nScaleY1,_nScaleY2;
                            double scanstart , scanstop;
                            double lawstart, lawstop;
                            QSize _size;
                            _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
                            qDebug()<<"ScanStart"<<_fScanStart<<"ScanStop"<<_fScanStop;
                            _size = size();
                            _nScaleX1 = ((double)leftTop.x()) / _size.width();
                            _nScaleY1 = ((double)leftTop.y()) / _size.height();
                            _nScaleX2 = ((double)rightBottom.x()) / _size.width();
                            _nScaleY2 = ((double)rightBottom.y()) / _size.height();
                            scanstart =_fScanStart + _nScaleX1 * (_fScanStop - _fScanStart);
                            scanstop = _fScanStart + _nScaleX2 * (_fScanStop - _fScanStart);
                            _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
                            qDebug()<<"indexStart"<<_fScanStart<<"indexStop"<<_fScanStop;
                            lawstart = _fScanStart + _nScaleY1 * (_fScanStop - _fScanStart);
                            lawstop = _fScanStart + _nScaleY2 * (_fScanStop - _fScanStart);
                            qDebug()<<"scanstart"<<scanstart<<"scanstop"<<scanstop<<"lawstart"<<lawstart<<"lawstop"<<lawstop;
                            AidedAnalysis *analysis = new AidedAnalysis(this);
                            analysis->setGroupId(_iGroupId);
                            analysis->setOrient(dirction);
                            if(dirction){
                                analysis->setRange(lawstop, lawstart, scanstart, scanstop);
                            }else{
                                analysis->setRange(scanstart, scanstop, lawstart, lawstop);
                            }

                            int defectNum = analysis->analysisDefect();
                            //qDebug()<<"defectNum"<<defectNum;
                            if(defectNum == 0){
                                QMessageBox::warning(this, tr("No Defect Found"), tr("No Defect Found"));
                                g_pMainWnd->AidedAnalysisDone(false);
                            }else if(defectNum == 1){
                                bool status = analysis->setSelectDefectIndex(0);
                                qDebug()<<"status"<<status;
                                if(status){
                                    g_pMainWnd->AidedAnalysisDone(true);
                                }else{
                                    QMessageBox::warning(this, tr("No Defect Found"), tr("No Defect Found"));
                                    g_pMainWnd->AidedAnalysisDone(false);
                                }
                            }else{
                                DialogDefectSelect defectView( defectNum, this);
                                analysis->paintDefectImage(defectView.getDefectImage());
                                defectView.setDefectCentre(analysis->getDefectCentre(), analysis->getDefectRect());
                                defectView.exec();
                                int selectDefect = defectView.getSelectDefect();
                                bool status = analysis->setSelectDefectIndex(selectDefect);
                                qDebug()<<"status"<<status;
                                if(status){
                                    g_pMainWnd->AidedAnalysisDone(true);
                                }else{
                                    QMessageBox::warning(this, tr("No Defect Found"), tr("No Defect Found"));
                                    g_pMainWnd->AidedAnalysisDone(false);
                                }
                            }
                        }else{
                           QMessageBox::warning(this, tr("Range too Small"), tr("Please Selected More Wider Range"));
                           g_pMainWnd->AidedAnalysisDone(false);
                        }
                    }else{
                        QMessageBox::warning(this, tr("Out of Range"), tr("Please Selected in C Scan View"));
                        g_pMainWnd->AidedAnalysisDone(false);
                    }
                }
            }
            else if(FLOAT_EQ(m_nScaleH , 1) && FLOAT_EQ(m_nScaleV , 1))
            {
                m_cPosStop = event->pos() ;
                QRectF _rect = this->geometry();

                if(_rect.contains(m_cPosStop) )
                {
                    QPoint leftTop, rightBottom;
                    if( m_cPosStart.x() < m_cPosStop.x())
                    {
                        leftTop.setX( m_cPosStart.x());
                        rightBottom.setX( m_cPosStop.x());
                    }
                    else
                    {
                        leftTop.setX( m_cPosStop.x());
                        rightBottom.setX( m_cPosStart.x());
                    }

                    if( m_cPosStart.y() < m_cPosStop.y())
                    {
                        leftTop.setY( m_cPosStart.y());
                        rightBottom.setY( m_cPosStop.y());
                    }
                    else
                    {
                        leftTop.setY( m_cPosStop.y());
                        rightBottom.setY( m_cPosStart.y());
                    }

                    //QRect rect(m_cPosStart , m_cPosStop) ;
                    QRect rect( leftTop, rightBottom);
                    m_cPosStart = leftTop;
                    m_cPosStop = rightBottom;
                    //qDebug()<<"rect"<<rect<<"m_cPosStart"<<m_cPosStart<<m_cPosStop;
                    if(tofdProAction() < 0)
                    {
                        DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
                        int _iGroupId, _iLaw, _iDisplay;
                        _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
                        setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;

                        double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop ;
                        double _nScaleX1,_nScaleX2,_nScaleY1,_nScaleY2;
                        double _fRangeStart,_fRangeStop;
                        double scanstart , scanstop ;
                        double lawstart, lawstop ;
                        int lawstart2,lawstop2;
                        double flag1,flag2;
                        int distance;

                        QSize _size;
                        ParameterProcess* _process = ParameterProcess::Instance();
                        if(!m_bZoom && m_cPosStart != m_cPosStop)
                        {
                            switch(_eMode){
                            case setup_DISPLAY_MODE_C_H:
                            case setup_DISPLAY_MODE_CC_H:
                                _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
                                if(m_pDrawScan->zoomflag == 0)
                                {
                                    m_pDrawScan->srcscanstart = _process->GetScanStart2();
                                    m_pDrawScan->srcscanstop = _process->GetScanend();
                                    m_pDrawScan->srclawstart = _process->GetLawStart();
                                    m_pDrawScan->srclawstop = _process->GetLawStop();
                                    m_pDrawScan->srcCstart = _fScanStart;
                                    m_pDrawScan->srcCend = _fScanStop;
                                }

                                _size = size();
                                _nScaleX1 = ((double)m_cPosStart.x()) / _size.width() ;
                                _nScaleY1 = ((double)m_cPosStart.y()) / _size.height() ;
                                _nScaleX2 = ((double)m_cPosStop.x()) / _size.width() ;
                                _nScaleY2 = ((double)m_cPosStop.y()) / _size.height() ;
                                scanstart =_fScanStart + _nScaleX1 * (_fScanStop - _fScanStart);
                                scanstop = _fScanStart + _nScaleX2 * (_fScanStop - _fScanStart);
                                _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
                                lawstart = _fScanStart + _nScaleY1 * (_fScanStop - _fScanStart);
                                lawstop = _fScanStart + _nScaleY2 * (_fScanStop - _fScanStart);
                                lawstart2 = (int)lawstart;
                                lawstop2 = (int)lawstop;
                                if(lawstart2 == lawstop2)
                                    break;
                                if(abs(rect.height()) > 50 && abs(rect.width()) > 50 )
                                {
                                    if((int)scanstart>=(int)scanstop)
                                        break;
                                    lawstart=(double)lawstart2;
                                    lawstop=(double)lawstop2;
                                    m_pDrawScan->curscanstart = scanstart;
                                    m_pDrawScan->curscanstop = scanstop;
                                    m_pDrawScan->curlawstart = lawstart;
                                    m_pDrawScan->curlawstop = lawstop;
                                    _pParent->SetRulerRange( lawstart , lawstop ,  lawstart , lawstop , DopplerDataView::DATA_VIEW_RULER_LEFT);
                                    _pParent->SetCopleCScanDisplayRange( scanstart, scanstop);
                                    m_pDrawScan->zoomflag = 1;
                                    UpdateDrawing();
                                    if(m_interactionView){
                                        emit signalNotifyOtherView(m_cPosStart, m_cPosStop, false);
                                    }
                                }
                                break;

                            case setup_DISPLAY_MODE_C_V:
                            case setup_DISPLAY_MODE_CC_V:
                                _pParent->GetRulerRange(&_fScanStop , &_fScanStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
                                if(m_pDrawScan->zoomflag == 0)
                                {
                                    m_pDrawScan->srcscanstart = _process->GetScanStart2();
                                    m_pDrawScan->srcscanstop = _process->GetScanend();
                                    m_pDrawScan->srclawstart = _process->GetLawStart();
                                    m_pDrawScan->srclawstop = _process->GetLawStop();
                                    m_pDrawScan->srcCstart = _fScanStart;
                                    m_pDrawScan->srcCend = _fScanStop;
                                }

                                _size = size();
                                _nScaleX1 = ((double)m_cPosStart.x()) / _size.width() ;
                                _nScaleY1 = ((double)m_cPosStart.y()) / _size.height() ;
                                _nScaleX2 = ((double)m_cPosStop.x()) / _size.width() ;
                                _nScaleY2 = ((double)m_cPosStop.y()) / _size.height() ;
                                scanstart =_fScanStop - _nScaleY2 * (_fScanStop - _fScanStart);
                                scanstop = _fScanStop - _nScaleY1 * (_fScanStop - _fScanStart);
                                _pParent->GetRulerRange(&_fScanStop , &_fScanStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
                                lawstart = _fScanStop + _nScaleX1 * (_fScanStart - _fScanStop);
                                lawstop = _fScanStop + _nScaleX2 * (_fScanStart - _fScanStop);
                                if((int)lawstart == (int)lawstop)
                                    break;
                                if(abs(rect.height()) > 50 && abs(rect.width()) > 50 )
                                {
                                    if((int)scanstart>=(int)scanstop)
                                        break;
                                    _process->ChangeCscanruler(scanstart,scanstop);
                                    m_pDrawScan->curscanstart = scanstart;
                                    m_pDrawScan->curscanstop = scanstop;
                                    m_pDrawScan->curlawstart = lawstart;
                                    m_pDrawScan->curlawstop = lawstop;
                                    _pParent->SetRulerRange( lawstart , lawstop ,  lawstart , lawstop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
                                    _pParent->SetCopleCScanDisplayRange( scanstart, scanstop);
                                    m_pDrawScan->zoomflag = 1;
                                    UpdateDrawing();
                                    if(m_interactionView){
                                        emit signalNotifyOtherView(m_cPosStart, m_cPosStop, false);
                                    }
                                }
                                break;
                            case setup_DISPLAY_MODE_B_H:
                                _pParent->GetRulerRange(&_fScanStop , &_fScanStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
                                if(m_pDrawScan->zoomflag == 0)
                                {
                                    m_pDrawScan->srcscanstart = _process->GetScanStart2();
                                    m_pDrawScan->srcscanstop = _process->GetScanend();
                                    //flag1 = 1;
                                    //flag2 = 1;
                                    m_pDrawScan->currangestart = 0;
                                    m_pDrawScan->currangestop = 0;
                                    m_pDrawScan->srcBstart = _fScanStart;
                                    m_pDrawScan->srcBend = _fScanStop;
                                }

                                _size = size();
                                _nScaleX1 = ((double)m_cPosStart.x()) / _size.width() ;
                                _nScaleY1 = ((double)m_cPosStart.y()) / _size.height() ;
                                _nScaleX2 = ((double)m_cPosStop.x()) / _size.width() ;
                                _nScaleY2 = ((double)m_cPosStop.y()) / _size.height() ;
                                scanstart =_fScanStop - _nScaleY2 * (_fScanStop - _fScanStart);
                                scanstop = _fScanStop - _nScaleY1 * (_fScanStop - _fScanStart);
                                if(scanstart < 0)
                                    scanstart = 0;
                                if(scanstop > _fScanStop)
                                    scanstop = _fScanStop;

                                _pParent->GetRulerRange(&_fScanStop , &_fScanStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
                                _fRangeStart = _fScanStop + _nScaleX1 * (_fScanStart - _fScanStop);
                                _fRangeStop = _fScanStop + _nScaleX2 * (_fScanStart - _fScanStop);
                                if(abs(rect.height()) > 50 && abs(rect.width()) > 50 )
                                {

                                    if((int)scanstart>=(int)scanstop)
                                        break;
                                    if(_fRangeStart>=_fRangeStop)
                                        break;
                                    if(m_pDrawScan->zoomflag == 0)
                                    {
                                        m_pDrawScan->currangestart = m_cPosStart.x();
                                        m_pDrawScan->currangestop = m_cPosStop.x();
                                    }
                                    else if(m_pDrawScan->zoomflag == 1)
                                    {
                                        distance = m_pDrawScan->currangestop - m_pDrawScan->currangestart;
                                        flag1 = (double)m_cPosStart.x()/_size.width();
                                        flag2 = (double)m_cPosStop.x()/_size.width();
                                        m_pDrawScan->currangestop = m_pDrawScan->currangestart +  distance * flag2;
                                        m_pDrawScan->currangestart = m_pDrawScan->currangestart + distance * flag1;
                                    }
                                    m_pDrawScan->curscanstart = scanstart;
                                    m_pDrawScan->curscanstop = scanstop;
                                    _pParent->SetRulerRange( _fRangeStart , _fRangeStop ,  _fRangeStart , _fRangeStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
                                    float scaleH = (float)_size.width() / (m_cPosStop.x() - m_cPosStart.x());
                                    float scaleV = (float)_size.width() / (m_cPosStop.y() - m_cPosStart.y());
                                    DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
                                    _pItemGroup->SetParabolaScale(scaleH, scaleV);

                                    m_pDrawScan->zoomflag = 1;
                                    UpdateDrawing();
                                    if(m_interactionView){
                                        emit signalNotifyOtherView(m_cPosStart, m_cPosStop, false);
                                    }
                                }
                                break;

                            case setup_DISPLAY_MODE_B_V:
                                _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
                                if(m_pDrawScan->zoomflag == 0)
                                {
                                    m_pDrawScan->srcscanstart = _process->GetScanStart2();
                                    m_pDrawScan->srcscanstop = _process->GetScanend();
                                    //flag1 = 1;
                                    //flag2 = 1;
                                    m_pDrawScan->currangestart = 0;
                                    m_pDrawScan->currangestop = 0;
                                    m_pDrawScan->srcBstart = _fScanStart;
                                    m_pDrawScan->srcBend = _fScanStop;
                                }

                                _size = size();
                                _nScaleX1 = ((double)m_cPosStart.x()) / _size.width() ;
                                _nScaleY1 = ((double)m_cPosStart.y()) / _size.height() ;
                                _nScaleX2 = ((double)m_cPosStop.x()) / _size.width() ;
                                _nScaleY2 = ((double)m_cPosStop.y()) / _size.height() ;
                                scanstart =_fScanStart + _nScaleX1 * (_fScanStop - _fScanStart);
                                scanstop = _fScanStart + _nScaleX2 * (_fScanStop - _fScanStart);
                                if(scanstart < 0)
                                    scanstart = 0;
                                if(scanstop > _fScanStop)
                                    scanstop = _fScanStop;

                                _pParent->GetRulerRange(&_fScanStart , &_fScanStop , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT ) ;
                                _fRangeStart = _fScanStart + _nScaleY1 * (_fScanStop - _fScanStart);
                                _fRangeStop = _fScanStart + _nScaleY2 * (_fScanStop - _fScanStart);
                                if(abs(rect.height()) > 50 && abs(rect.width()) > 50 )
                                {
                                    if((int)scanstart>=(int)scanstop)
                                        break;
                                    if(_fRangeStart>=_fRangeStop)
                                        break;
                                    if(m_pDrawScan->zoomflag == 0)
                                    {
                                        m_pDrawScan->currangestart = m_cPosStart.y();
                                        m_pDrawScan->currangestop = m_cPosStop.y();
                                    }
                                    else if(m_pDrawScan->zoomflag == 1)
                                    {
                                        distance = m_pDrawScan->currangestop - m_pDrawScan->currangestart;
                                        flag1 = (double)m_cPosStart.y()/_size.height();
                                        flag2 = (double)m_cPosStop.y()/_size.height();
                                        m_pDrawScan->currangestop = m_pDrawScan->currangestart +  distance * flag2;
                                        m_pDrawScan->currangestart = m_pDrawScan->currangestart + distance * flag1;
                                    }
                                    m_pDrawScan->curscanstart = scanstart;
                                    m_pDrawScan->curscanstop = scanstop;
                                    _pParent->SetRulerRange( _fRangeStart , _fRangeStop ,  _fRangeStart , _fRangeStop , DopplerDataView::DATA_VIEW_RULER_LEFT);
                                    float scaleH = (float)_size.width() / (m_cPosStop.x() - m_cPosStart.x());
                                    float scaleV = (float)_size.width() / (m_cPosStop.y() - m_cPosStart.y());
                                    DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
                                    _pItemGroup->SetParabolaScale(scaleH, scaleV);

                                    m_pDrawScan->zoomflag = 1;
                                    UpdateDrawing();
                                    if(m_interactionView){
                                        emit signalNotifyOtherView(m_cPosStart, m_cPosStop, false);
                                    }
                                }
                                break;
                            default:
                                zoomAction(rect);
                                break;


                            }


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
//		DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
//		int _iGroupId, _iLaw, _iDisplay;
//        double _fScanStart,_fScanStop;
//		_pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
//        setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;
//        DopplerTofdOpp opp;
//		opp.TofdClearDragStatus(_iGroupId);
//        if(m_pDrawScan->zoomflag == 1)
//        {

//            ParameterProcess* _process = ParameterProcess::Instance();
//            double _fStart, _fStop;
//            _fStart = _process->GetSampleStart(_iGroupId, _iLaw);
//            _fStop =  _fStart + _process->GetSampleRange(_iGroupId, _iLaw);
//            _process->ChangeCscanruler(m_pDrawScan->srcscanstart,m_pDrawScan->srcscanstop);
//            _process->ChangeLawStart(m_pDrawScan->srclawstart);
//            _process->ChangeLawStop(m_pDrawScan->srclawstop);
//            switch(_eMode){
//            case setup_DISPLAY_MODE_C_H:
//            case setup_DISPLAY_MODE_CC_H:
//                m_pDrawScan->zoomflag = 2;
//                _process->GetCScanIndexAxisRange(_iGroupId ,  &_fScanStart , &_fScanStop) ;
//                _pParent->SetRulerRange( _fScanStart , _fScanStop ,  _fScanStart , _fScanStop , DopplerDataView::DATA_VIEW_RULER_LEFT);
//                break;
//            case setup_DISPLAY_MODE_C_V:
//            case setup_DISPLAY_MODE_CC_V:
//                m_pDrawScan->zoomflag = 2;
//                _process->GetCScanIndexAxisRange(_iGroupId ,  &_fScanStart , &_fScanStop) ;
//                _pParent->SetRulerRange( _fScanStart , _fScanStop ,  _fScanStart , _fScanStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
//                break;
//            case setup_DISPLAY_MODE_B_H:
//            {
//                m_pDrawScan->zoomflag = 2;
//                DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
//                _pItemGroup->SetParabolaScale(1, 1);
//                _pParent->SetRulerRange( _fStart, _fStop,  _fStart, _fStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
//                //_pParent->SetRulerRange( srcrangestart , srcrangestop ,  srcrangestart , srcrangestop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
//                break;
//            }
//            case setup_DISPLAY_MODE_B_V:
//            {
//                m_pDrawScan->zoomflag = 2;
//                DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
//                _pItemGroup->SetParabolaScale(1, 1);
//                _pParent->SetRulerRange( _fStart, _fStop,  _fStart, _fStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
//                //_pParent->SetRulerRange( srcrangestart , srcrangestop ,  srcrangestart , srcrangestop , DopplerDataView::DATA_VIEW_RULER_LEFT);
//                break;
//            }
//            default:
//                break;
//            }
//        }
//		UpdateDrawing();

//		//
//		DopplerConfigure* _pConfig = DopplerConfigure::Instance();
//		_pConfig->ClearDefectInfo(_iGroupId);
//		if(FLOAT_EQ(m_nScaleH , 1.0) && FLOAT_EQ(m_nScaleV , 1.0))
//            _pParent->updateAllItems();
//            //emit signalButtonRelease(event);
//		else {
//			slotResetView();
//		}
        backNoZoom();
        if(m_interactionView){
            emit signalNotifyOtherView(QPoint(), QPoint(), true);
        }
    }else if(Qt::MiddleButton == event->button()){
        m_wheelItemSelect = false;
    }

	QList<QGraphicsItem*> list = m_pScene->selectedItems();
	for(int i = 0 ; i < list.count() ; i++)
	list.at(i)->setSelected(false);

    QGraphicsView::mouseReleaseEvent(event);
}

void DopplerGraphicView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    if (_pConfig->common.bDefectIdentifyStatus && m_isDrawSelectArea) {
        DrawSelectArea();
    } else {
        m_isDrawSelectArea = false;
    }
    DrawMeasureValue();
}

void DopplerGraphicView::SetMeasureString(int nIndex_, QString* str_)
{
    QMutexLocker locker(&m_mutex);
    m_strMeasure[nIndex_] = *str_;
}

void DopplerGraphicView::SetMeasureStringQty(int nQty_)
{
    m_nMeasureQty = nQty_ > MAX_MEASURE_DATA_DISPLAY ? MAX_MEASURE_DATA_DISPLAY : nQty_;
}

void DopplerGraphicView::DrawMeasureValue()
{
    QMutexLocker locker(&m_mutex);
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
        int _nLawNum;
        if (_nMeaNum !=0)
        {
            _nLawNum = m_nMeasureQty / _nMeaNum;
        }
        else
        {
             _nLawNum=0;
        }

		if(_iDisplay == setup_DISPLAY_MODE_S_ATHUMIZ || _iDisplay == setup_DISPLAY_MODE_S_LINEAR)
		{
			if(setup_GROUP_MODE_PA == _group.eGroupMode)
			{
				QSize _size((int)(m_pBackGround->size().width()) , (int)(m_pBackGround->size().height()))  ;
				setup_PROBE_ANGLE _eAngle =  _process->GetProbeAngle(_iGroupId) ;
                int _off = 120;
				switch(_nLawNum)
				{
                case 1:_off = 120;						break;
                case 2:_off = 120 + _nMeaNum * 12;		break;
                case 3:_off = 120 + 2 * _nMeaNum * 12;	break;
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
    this->viewport()->update();
    _painter.end();
}

void DopplerGraphicView::DrawSelectArea()
{
    QMutexLocker locker(&m_mutex);
    QWidget* _pViewPort = (QWidget*)this->viewport();
    QPainter _painter(_pViewPort) ;
    _painter.setPen(QPen(QColor(18,133,240)));

    QBrush _brush(QColor(0,0,0));
    _painter.setBackground(_brush);

    _brush.setColor(QColor(18,133,240,40));
    _painter.setBrush(_brush);
    _painter.drawRect(m_selectedArea);

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
    //qDebug()<<"ret"<<_ret<<opp.TofdDragProStatus(_iGroupId);

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
        m_cZoomRect = mapToScene(rect_).boundingRect().toRect();
		m_bZoom     = true;

        QSize _size = size();

        //QSizeF _size = m_pBackGround->size();
        //qDebug()<<"m_pBackGround"<<_size<<"rect_"<<rect_;
        //QRect sceneRect = mapToScene(rect_);
		double _nScaleX = ((double)_size.width()) / rect_.width() ;
		double _nScaleY =  ((double)_size.height()) / rect_.height() ;
        //qDebug()<<"_nScaleX"<<_nScaleX<<"_nScaleY"<<_nScaleY;
		//_nScaleX = ((int)(_nScaleX * 100 )) / 100.0  ;
		//_nScaleY = ((int)(_nScaleY * 100 )) / 100.0  ;
        //qDebug()<<"rect_.center"<<rect_.center()<<"mapToScene"<<mapToScene(rect_.center());

        centerOn(mapToScene(rect_.center()));
        //centerOn(rect_.center());
		SetupMatrixScale(fabs(_nScaleX) , fabs(_nScaleY));
	}

}

void DopplerGraphicView::SetZoomAction(double bottomStart, double bottomEnd, double leftStart, double leftEnd)
{
    m_pBackGround->setImageTransfer( bottomStart, bottomEnd, leftStart, leftEnd);
    UpdateDrawing();
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
    //qDebug()<<"rectDisplay"<<rectDisplay<<"rangeDisplay"<<rangeDisplay;
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

void DopplerGraphicView::scaleRecover()
{
    backNoZoom();
    if(m_interactionView){
        emit signalNotifyOtherView(QPoint(), QPoint(), true);
    }
}

void DopplerGraphicView::setDataMode(bool status)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->common.dataModeStatus = status;
}

void DopplerGraphicView::setShowCursor(bool status)
{
    DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
    int _iGroupId, _iLaw, _iDisplay;
    _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
    signalShowCursor(_iGroupId, status);
}

void DopplerGraphicView::setShowDefect(bool status)
{
    DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
    int _iGroupId, _iLaw, _iDisplay;
    _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
    signalShowDefect(_iGroupId, status);
}

/**
 * @brief DopplerGraphicView::showCoupleInScanA 在A扫中显示耦合监控曲线
 * @param status
 */
void DopplerGraphicView::showCoupleInScanA(bool status)
{
    DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
    int _iGroupId, _iLaw, _iDisplay;
    _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->group[_iGroupId].bShowCoupleInAScan = status;
    this->UpdateDrawing();
}

void DopplerGraphicView::backNoZoom()
{
    DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
    int _iGroupId, _iLaw, _iDisplay;
    double _fScanStart,_fScanStop;
    _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
    setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;
    DopplerTofdOpp opp;
    opp.TofdClearDragStatus(_iGroupId);
    if(m_pDrawScan->zoomflag == 1)
    {

        ParameterProcess* _process = ParameterProcess::Instance();
        double _fStart, _fStop;
        _fStart = _process->GetSampleStart(_iGroupId, _iLaw);
        _fStop =  _fStart + _process->GetSampleRange(_iGroupId, _iLaw);
        _process->ChangeCscanruler(m_pDrawScan->srcscanstart,m_pDrawScan->srcscanstop);
        _process->ChangeLawStart(m_pDrawScan->srclawstart);
        _process->ChangeLawStop(m_pDrawScan->srclawstop);
        switch(_eMode){
        case setup_DISPLAY_MODE_C_H:
        case setup_DISPLAY_MODE_CC_H:
            m_pDrawScan->zoomflag = 2;
            _process->GetCScanIndexAxisRange(_iGroupId ,  &_fScanStart , &_fScanStop) ;
            _pParent->SetRulerRange( _fScanStart , _fScanStop ,  _fScanStart , _fScanStop , DopplerDataView::DATA_VIEW_RULER_LEFT);
            break;
        case setup_DISPLAY_MODE_C_V:
        case setup_DISPLAY_MODE_CC_V:
            m_pDrawScan->zoomflag = 2;
            _process->GetCScanIndexAxisRange(_iGroupId ,  &_fScanStart , &_fScanStop) ;
            _pParent->SetRulerRange( _fScanStart , _fScanStop ,  _fScanStart , _fScanStop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            break;
        case setup_DISPLAY_MODE_B_H:
        {
            m_pDrawScan->zoomflag = 2;
            DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
            _pItemGroup->SetParabolaScale(1, 1);
            _pParent->SetRulerRange( _fStart, _fStop,  _fStart, _fStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            break;
        }
        case setup_DISPLAY_MODE_B_V:
        {
            m_pDrawScan->zoomflag = 2;
            DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
            _pItemGroup->SetParabolaScale(1, 1);
            _pParent->SetRulerRange( _fStart, _fStop,  _fStart, _fStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
            break;
        }
        default:
            break;
        }
    }
    UpdateDrawing();

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->ClearDefectInfo(_iGroupId);
    if(FLOAT_EQ(m_nScaleH , 1.0) && FLOAT_EQ(m_nScaleV , 1.0))
        _pParent->updateAllItems();
    else {
        slotResetView();
    }
}

void DopplerGraphicView::creatActionAndMenu()
{
//    DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
//    int _iGroupId, _iLaw, _iDisplay;
//    _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
//    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
//    bool cursorStatus, defectStatus;
//    cursorStatus = _pConfig->group[_iGroupId].bShowCursor;
//    defectStatus = _pConfig->group[_iGroupId].bShowDefect;

    m_contextMenu = new QMenu;

    m_scaleRecover = new QAction(this);
    m_scaleRecover->setIcon(QIcon(":/file/resource/main_menu/recover.png"));
    connect( m_scaleRecover, SIGNAL(triggered()), this, SLOT(scaleRecover()));

    m_dataMode = new QAction(tr("Data Mode"), this);
    //m_dataMode->setIcon(QIcon(":/file/resource/main_menu/dataMode.png"));
    m_dataMode->setCheckable( true);
    m_dataMode->setChecked(true);
    connect( m_dataMode, SIGNAL(toggled(bool)), this, SLOT(setDataMode(bool)));

    m_showCursor = new QAction(tr("Show Cursor"), this);
    //m_showCursor->setIcon(QIcon(":/file/resource/main_menu/cursor.png"));
    m_showCursor->setCheckable( true);
    m_showCursor->setChecked( true);
    connect( m_showCursor, SIGNAL(toggled(bool)), this, SLOT(setShowCursor(bool)));

    m_showDefect = new QAction(tr("Show Defect"), this);
    //m_showDefect->setIcon(QIcon(":/file/resource/main_menu/defect.png"));
    m_showDefect->setCheckable( true);
    m_showDefect->setChecked( true);
    connect( m_showDefect, SIGNAL(toggled(bool)), this, SLOT(setShowDefect(bool)));

    m_showCouple = new QAction(tr("Show Couple"), this);
    m_showCouple->setCheckable( true);
    m_showCouple->setChecked( false);
    connect(m_showCouple, &QAction::toggled, this, &DopplerGraphicView::showCoupleInScanA);

    m_startAnalysis = new QAction(tr("Start Analysis"), this);
    m_startAnalysis->setEnabled(true);
    connect(m_startAnalysis, &QAction::triggered, this, [=] {
        g_pMainWnd->startDefectIdentify();
    });

    m_selectMeasureMethod = new QAction(tr("Select Method"), this);
    m_selectMeasureMethod->setEnabled(true);
    connect(m_selectMeasureMethod, &QAction::triggered, this, [=] {
        g_pMainWnd->selectDefectMeasureMethod();
    });

//    m_contextMenu->addAction(m_scaleRecover);
//    m_contextMenu->addAction(m_dataMode);
//    m_contextMenu->addAction(m_showCursor);
//    m_contextMenu->addAction(m_showDefect);

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
  Description:   调用DrawScan的Draw函数绘制数据 并发送刷新信号到主线程
*****************************************************************************/
void DopplerGraphicView::UpdateDrawing()
{
	if(m_pDrawScan)
	{
        QMutexLocker locker(&m_pBackGround->m_hMutex);
        //m_pBackGround->m_hMutex.lock();
            m_pDrawScan->Draw (m_pBackGround->GetBaseImage());
        //m_pBackGround->m_hMutex.unlock();
	}
	emit signalUpdateDrawing();
}
/****************************************************************************
  Description:   刷新场景
*****************************************************************************/
void DopplerGraphicView::UpdateSceneRegion()
{
	if(m_pScene)
        m_pScene->update();
}

/****************************************************************************
  Description:   刷新画布
*****************************************************************************/
void DopplerGraphicView::slotUpdateDrawing()
{
	if(m_pDrawScan)
	{
        m_pBackGround->update();
	}
}

void DopplerGraphicView::respondView(QPoint startPos, QPoint endPos, bool zoomStatus)
{
    if(zoomStatus){
        backNoZoom();
    }else{
        DopplerDataView* _pParent = (DopplerDataView*)parentWidget();
        int _iGroupId, _iLaw, _iDisplay;
        _pParent->GetDataViewConfigure(&_iGroupId, &_iLaw, &_iDisplay);
        setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_iDisplay;

        double _fScanStart , _fScanStop , _fSliderStart, _fSliderStop ;
        double _nScaleX1,_nScaleX2,_nScaleY1,_nScaleY2;
        double _fRangeStart,_fRangeStop;
        double scanstart , scanstop ;
        double lawstart, lawstop ;
        //int lawstart2,lawstop2;
        double flag1,flag2;
        int distance;

        QSize _size;
        ParameterProcess* _process = ParameterProcess::Instance();
        switch (_eMode) {
        case setup_DISPLAY_MODE_C_H:
        case setup_DISPLAY_MODE_CC_H:
        {
            _pParent->GetRulerRange(&_fScanStart, &_fScanStop, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            if(m_pDrawScan->zoomflag == 0)
            {
                m_pDrawScan->srcscanstart = _process->GetScanStart2();
                m_pDrawScan->srcscanstop = _process->GetScanend();
                m_pDrawScan->srclawstart = _process->GetLawStart();
                m_pDrawScan->srclawstop = _process->GetLawStop();
                m_pDrawScan->srcCstart = _fScanStart;
                m_pDrawScan->srcCend = _fScanStop;
            }
            _size = size();
            _nScaleX1 = ((double)startPos.x()) / _size.width();
            //_nScaleY1 = ((double)startPos.y()) / _size.height();
            _nScaleX2 = ((double)endPos.x()) / _size.width();
            //_nScaleY2 = ((double)endPos.y()) / _size.height();
            scanstart =_fScanStart + _nScaleX1 * (_fScanStop - _fScanStart);
            scanstop = _fScanStart + _nScaleX2 * (_fScanStop - _fScanStart);
            _pParent->GetRulerRange(&_fScanStart, &_fScanStop, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
//            lawstart = _fScanStart + _nScaleY1 * (_fScanStop - _fScanStart);
//            lawstop = _fScanStart + _nScaleY2 * (_fScanStop - _fScanStart);
//            lawstart2 = (int)lawstart;
//            lawstop2 = (int)lawstop;

//            lawstart =(double)lawstart2;
//            lawstop =(double)lawstop2;
            lawstart = _fScanStart;
            lawstop = _fScanStop;
            m_pDrawScan->curscanstart = scanstart;
            m_pDrawScan->curscanstop = scanstop;
            m_pDrawScan->curlawstart = lawstart;
            m_pDrawScan->curlawstop = lawstop;
            _pParent->SetRulerRange( lawstart , lawstop ,  lawstart , lawstop , DopplerDataView::DATA_VIEW_RULER_LEFT);
            _pParent->SetCopleCScanDisplayRange( scanstart, scanstop);
            m_pDrawScan->zoomflag = 1;
            UpdateDrawing();
        }
            break;
        case setup_DISPLAY_MODE_C_V:
        case setup_DISPLAY_MODE_CC_V:
        {
            _pParent->GetRulerRange(&_fScanStop, &_fScanStart, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
            if(m_pDrawScan->zoomflag == 0){
                m_pDrawScan->srcscanstart = _process->GetScanStart2();
                m_pDrawScan->srcscanstop = _process->GetScanend();
                m_pDrawScan->srclawstart = _process->GetLawStart();
                m_pDrawScan->srclawstop = _process->GetLawStop();
                m_pDrawScan->srcCstart = _fScanStart;
                m_pDrawScan->srcCend = _fScanStop;
            }
            _size = size();
            //_nScaleX1 = ((double)startPos.x()) / _size.width();
            _nScaleY1 = ((double)startPos.y()) / _size.height();
            //_nScaleX2 = ((double)endPos.x()) / _size.width();
            _nScaleY2 = ((double)endPos.y()) / _size.height();
            scanstart =_fScanStop - _nScaleY2 * (_fScanStop - _fScanStart);
            scanstop = _fScanStop - _nScaleY1 * (_fScanStop - _fScanStart);
            _pParent->GetRulerRange(&_fScanStop, &_fScanStart, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            //lawstart = _fScanStop + _nScaleX1 * (_fScanStart - _fScanStop);
            //lawstop = _fScanStop + _nScaleX2 * (_fScanStart - _fScanStop);
            lawstart = _fScanStop;
            lawstop = _fScanStop;
            _process->ChangeCscanruler(scanstart,scanstop);
            m_pDrawScan->curscanstart = scanstart;
            m_pDrawScan->curscanstop = scanstop;
            m_pDrawScan->curlawstart = lawstart;
            m_pDrawScan->curlawstop = lawstop;
            _pParent->SetRulerRange( lawstart , lawstop ,  lawstart , lawstop , DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            _pParent->SetCopleCScanDisplayRange( scanstart, scanstop);
            m_pDrawScan->zoomflag = 1;
            UpdateDrawing();
        }
            break;
        case setup_DISPLAY_MODE_B_H:
        {
            _pParent->GetRulerRange(&_fScanStop, &_fScanStart, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
            if(m_pDrawScan->zoomflag == 0)
            {
                m_pDrawScan->srcscanstart = _process->GetScanStart2();
                m_pDrawScan->srcscanstop = _process->GetScanend();
                m_pDrawScan->currangestart = 0;
                m_pDrawScan->currangestop = 0;
                m_pDrawScan->srcBstart = _fScanStart;
                m_pDrawScan->srcBend = _fScanStop;
            }
            _size = size();
            startPos.setX(0);
            endPos.setX(_size.width());
            //_nScaleX1 = ((double)startPos.x()) / _size.width() ;
            _nScaleY1 = ((double)startPos.y()) / _size.height() ;
            //_nScaleX2 = ((double)endPos.x()) / _size.width() ;
            _nScaleY2 = ((double)endPos.y()) / _size.height() ;
            scanstart =_fScanStop - _nScaleY2 * (_fScanStop - _fScanStart);
            scanstop = _fScanStop - _nScaleY1 * (_fScanStop - _fScanStart);
            if(scanstart < 0)
                scanstart = 0;
            if(scanstop > _fScanStop)
                scanstop = _fScanStop;
            _pParent->GetRulerRange(&_fScanStop , &_fScanStart , &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM ) ;
            //_fRangeStart = _fScanStop + _nScaleX1 * (_fScanStart - _fScanStop);
            //_fRangeStop = _fScanStop + _nScaleX2 * (_fScanStart - _fScanStop);
            _fRangeStart = _fScanStop;
            _fRangeStop = _fScanStart;

            if(m_pDrawScan->zoomflag == 0)
            {
                m_pDrawScan->currangestart = startPos.x();
                m_pDrawScan->currangestop = endPos.x();
            }
            else if(m_pDrawScan->zoomflag == 1)
            {
                distance = m_pDrawScan->currangestop - m_pDrawScan->currangestart;
                flag1 = (double)startPos.x()/_size.width();
                flag2 = (double)endPos.x()/_size.width();
                m_pDrawScan->currangestop = m_pDrawScan->currangestart +  distance * flag2;
                m_pDrawScan->currangestart = m_pDrawScan->currangestart + distance * flag1;
            }
            m_pDrawScan->curscanstart = scanstart;
            m_pDrawScan->curscanstop = scanstop;
            _pParent->SetRulerRange( _fRangeStart, _fRangeStop,  _fRangeStart, _fRangeStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            float scaleH = (float)_size.width() / (endPos.x() - startPos.x());
            float scaleV = (float)_size.width() / (endPos.y() - startPos.y());
            DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
            _pItemGroup->SetParabolaScale(scaleH, scaleV);

            m_pDrawScan->zoomflag = 1;
            UpdateDrawing();
        }
            break;
        case setup_DISPLAY_MODE_B_V:
        {
            _pParent->GetRulerRange(&_fScanStart, &_fScanStop, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_BOTTOM);
            if(m_pDrawScan->zoomflag == 0){
                m_pDrawScan->srcscanstart = _process->GetScanStart2();
                m_pDrawScan->srcscanstop = _process->GetScanend();
                m_pDrawScan->currangestart = 0;
                m_pDrawScan->currangestop = 0;
                m_pDrawScan->srcBstart = _fScanStart;
                m_pDrawScan->srcBend = _fScanStop;
            }
            _size = size();
            startPos.setY(0);
            endPos.setY(_size.height());
            _nScaleX1 = ((double)startPos.x()) / _size.width();
            //_nScaleY1 = ((double)startPos.y()) / _size.height();
            _nScaleX2 = ((double)endPos.x()) / _size.width();
            //_nScaleY2 = ((double)endPos.y()) / _size.height();
            scanstart =_fScanStart + _nScaleX1 * (_fScanStop - _fScanStart);
            scanstop = _fScanStart + _nScaleX2 * (_fScanStop - _fScanStart);
            if(scanstart < 0)
                scanstart = 0;
            if(scanstop > _fScanStop)
                scanstop = _fScanStop;
            _pParent->GetRulerRange(&_fScanStart, &_fScanStop, &_fSliderStart, &_fSliderStop, DopplerDataView::DATA_VIEW_RULER_LEFT);
            //_fRangeStart = _fScanStart + _nScaleY1 * (_fScanStop - _fScanStart);
            //_fRangeStop = _fScanStart + _nScaleY2 * (_fScanStop - _fScanStart);
            _fRangeStart = _fScanStart;
            _fRangeStop = _fScanStop;

            if(m_pDrawScan->zoomflag == 0)
            {
                m_pDrawScan->currangestart = startPos.y();
                m_pDrawScan->currangestop = endPos.y();
            }
            else if(m_pDrawScan->zoomflag == 1)
            {
                distance = m_pDrawScan->currangestop - m_pDrawScan->currangestart;
                flag1 = (double)startPos.y()/_size.height();
                flag2 = (double)endPos.y()/_size.height();
                m_pDrawScan->currangestop = m_pDrawScan->currangestart +  distance * flag2;
                m_pDrawScan->currangestart = m_pDrawScan->currangestart + distance * flag1;
            }
            m_pDrawScan->curscanstart = scanstart;
            m_pDrawScan->curscanstop = scanstop;
            _pParent->SetRulerRange( _fRangeStart , _fRangeStop ,  _fRangeStart , _fRangeStop , DopplerDataView::DATA_VIEW_RULER_LEFT);
            float scaleH = (float)_size.width() / (endPos.x() - startPos.x());
            float scaleV = (float)_size.width() / (endPos.y() - startPos.y());
            DopplerViewItems* _pItemGroup = _pParent->GetItemGroup();
            _pItemGroup->SetParabolaScale(scaleH, scaleV);

            m_pDrawScan->zoomflag = 1;
            UpdateDrawing();
        }
            break;
        default:
            break;
        }
    }
}
