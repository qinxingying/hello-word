#ifndef DOPPLER_GRAPHICVIEW_H
#define DOPPLER_GRAPHICVIEW_H

#include <QGraphicsView>
#include <QRect>
#include <QRectF>
#include <QMutex>
class QGraphicsScene;
class DopplerGraphicsItem;
class GraphicsViewBase;
class DopplerDrawScan;
class DopplerLineItem;
class QMenu;

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
    void   SetZoomAction(double bottomStart, double bottomEnd, double leftStart, double leftEnd);
    void   setInteractionStatus(bool status){m_interactionView = status;}
    void   respondView(QPoint startPos, QPoint endPos, bool zoomStatus);
	//bool   GetBCZoomStatus() {return m_bBCAutoZomm;}
public:
    QMutex m_mutex;
protected:
    void   wheelEvent(QWheelEvent * event);
    void   resizeEvent(QResizeEvent *event);
    void   mousePressEvent(QMouseEvent *event);
    void   mouseDoubleClickEvent(QMouseEvent *event);
    void   mouseReleaseEvent(QMouseEvent *event);
    void   mouseMoveEvent(QMouseEvent *event);
    void   keyPressEvent(QKeyEvent *event);
    void   paintEvent(QPaintEvent *event);
    void   InitGraphicView(const QSize& cSize_);
    void   mouseCursorPro(QMouseEvent *event);
    int    tofdProAction();
    void   CScanZoomAction();
    void   GeometryChanged();
    void   DrawMeasureValue();
    void   DrawSelectArea(QRect &_rect, QColor _color);
    QRectF RangeTranslate(QRectF& rect_);


private slots:
    void scaleRecover();
    void setDataMode(bool status);
    void setShowCursor(bool status);
    void setShowDefect(bool status);
    void showCoupleInScanA(bool status);
private:
    void backNoZoom();
    void creatActionAndMenu();
    QGraphicsScene*   m_pScene        ;
    GraphicsViewBase* m_pBackGround   ;
    DopplerDrawScan*  m_pDrawScan     ;
    DopplerLineItem*  m_tempItem;
    //**************************************
    double            m_nScaleH       ;
    double            m_nScaleV       ;
    double            m_nScaleBaseH   ;
    double            m_nScaleBaseV   ;
    QRect             m_cZoomRect     ;
    QPoint            m_cPosStart     ;
    QPoint            m_cPosStop      ;
    bool              m_bItemSelected ;     // 是否选中光标
	QString           m_strMeasure[MAX_MEASURE_DATA_DISPLAY]  ;
    int               m_nMeasureQty  ;
	//int               m_nTimerId     ;

	//bool              m_bBCAutoZomm  ;
	//bool              m_bZommInit    ;
	bool              m_bZoom        ;
    bool              m_wheelItemSelect;
    bool              m_interactionView;
    bool              m_flashMenu;
    QAction *m_scaleRecover;
    QAction *m_dataMode;
    QAction *m_showCursor;
    QAction *m_showDefect;
    QAction *m_showCouple;
    QAction *m_startAnalysis;
    QAction *m_selectMeasureMethod;
    QMenu *m_contextMenu;

    QRect m_selectedArea;
    bool m_isDrawSelectArea {false};
signals:
    void signalViewChanged(QRectF rect)  ;
    void signalUpdateDrawing();
    void signalItemMoved(DopplerGraphicsItem* item_) ;
    void signalItemPressed(DopplerGraphicsItem* item_) ;
    //void signalButtonRelease(QMouseEvent *event);
    void signalButtonPressed(QMouseEvent* event);
    void signalButtonDoubleClicked(QPointF pos_);
    void signalTofdDragProAction(QPointF ptS_, QPointF ptE_);
    void signalScanPosChange(int steps);
    void signalLawPosChange(int groupId, int lawId, int steps);
    void signalCursorScanChange(int groupId, bool orientation);
    void signalCursorUChange(int groupId, int lawId, bool orientation);
    void signalNotifyOtherView(QPoint startPos, QPoint endPos, bool zoomStatus);
    void signalShowCursor(int groupId, bool status);
    void signalShowDefect(int groupId, bool status);
    void signalCscanShowallChange(int groupId);
    void signalMeasureGate(int groupId);
    void signalMarkNextDefect();
    void signalMarkPreviousDefect();
    void signalStartAnalysis();
    void signalStopAnalysis();
    void signalDeleteDefect();
public slots:
    void slotResetView();
    void slotPrint();
    void slotUpdateDrawing();

};

#endif // DOPPLER_GRAPHICVIEW_H
