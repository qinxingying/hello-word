#ifndef DOPPLER_GRAPHICVIEW_H
#define DOPPLER_GRAPHICVIEW_H

#include <QGraphicsView>
#include <QRect>
#include <QRectF>

class QGraphicsScene;
class DopplerGraphicsItem;
class GraphicsViewBase;
class DopplerDrawScan;

#define MAX_MEASURE_DATA_DISPLAY  24

class DopplerGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DopplerGraphicView(QWidget *parent = 0 , QSize size = QSize(600 , 360));
    ~DopplerGraphicView();

    void   SetDrawOperation(DopplerDrawScan* pDrawScan_);
    void   SetupMatrixScale(double nScaleH_ , double nScaleV_);
    void   EnableRenderOpenGL(bool bEnable_ = true) ;
    void   SetBackgroundBrush(const QColor& cColor_)  ;
    void   AddOverlayItems(QGraphicsItem* item_) ;
    void   SetDrawScan(DopplerDrawScan*  pDrawScan_) ;
    DopplerDrawScan* GetDrawScan() const ;
    void   UpdateDrawing() ;
    void   UpdateSceneRegion();
    QSize  GetSceneSize() ;
    void   SetMeasureString(int nIndex_ , QString* str_) ;
    void   SetMeasureStringQty(int nQty_);
	void   zoomAction(QRect rect) ;
	QRect  GetZoomRect() {return m_cZoomRect;}
	bool   GetZoomStatus() {return m_bZoom;}
	//bool   GetBCZoomStatus() {return m_bBCAutoZomm;}
public:
    QMutex m_mutex;
protected:
    void   wheelEvent ( QWheelEvent * event ) ;
    void   resizeEvent(QResizeEvent *event) ;
    void   mousePressEvent(QMouseEvent *event);
    void   mouseDoubleClickEvent(QMouseEvent *event);
    void   mouseReleaseEvent(QMouseEvent *event);
    void   mouseMoveEvent(QMouseEvent *event);
    void   paintEvent(QPaintEvent *event);
    void   InitGraphicView(const QSize& cSize_); 
    void mouseCursorPro(QMouseEvent *event);
    int    tofdProAction();
    void CScanZoomAction();
	void   GeometryChanged() ;
    void   DrawMeasureValue();
    QRectF RangeTranslate(QRectF& rect_) ;

private:
    QGraphicsScene*   m_pScene        ;
    GraphicsViewBase* m_pBackGround   ;
    DopplerDrawScan*  m_pDrawScan     ;
    //**************************************
    double            m_nScaleH       ;
    double            m_nScaleV       ;
    double            m_nScaleBaseH   ;
    double            m_nScaleBaseV   ;
    QRect             m_cZoomRect     ;
    QPoint            m_cPosStart     ;
    QPoint            m_cPosStop      ;
    bool              m_bItemSelected ;
	QString           m_strMeasure[MAX_MEASURE_DATA_DISPLAY]  ;
    int               m_nMeasureQty  ;
	//int               m_nTimerId     ;

	//bool              m_bBCAutoZomm  ;
	//bool              m_bZommInit    ;
	bool              m_bZoom        ;
signals:
    void signalViewChanged(QRectF rect)  ;
    void signalUpdateDrawing();
    void signalItemMoved(DopplerGraphicsItem* item_) ;
    void signalButtonRelease(QMouseEvent *event);
    void signalButtonPressed(QMouseEvent* event);
    void signalButtonDoubleClicked(QPointF pos_);
    void signalTofdDragProAction(QPointF ptS_, QPointF ptE_);
public slots:
    void slotResetView();
    void slotPrint();
    void slotUpdateDrawing();

};

#endif // DOPPLER_GRAPHICVIEW_H
