/***************************
  Name:  DopplerDataView
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   ��ʾ���ݴ���
                 1�� ������ �� ��3�����  ��1����ɫ��
                 ���м��������ʾ������ɡ�
                 ���εĻ��ƣ��ṩ��DopplerDrawScan �ӿڣ�
                 ��ʵ�� A B S C����ʾ
                 .............
************************************/
#ifndef DOPPLERDataView_H
#define DOPPLERDataView_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPair>
#include <QPointF>
#include <QSize>

class DopplerRulerBar      ;
class DopplerTitleBar      ;
class DopplerColorBar      ;
class DopplerGraphicView   ;
//class DopplerColorIndex    ;
class DopplerDrawScan      ;
class QGraphicsItem        ;
class QGridLayout          ;
class DopplerGraphicsItem  ;
class DopplerViewItems     ;
class DopplerDataView : public QWidget
{
    Q_OBJECT
public:
    enum DATA_VIEW_COMPONENT
    {
       DATA_VIEW_COMPONENT_NONE       =  0 ,
       DATA_VIEW_COMPONENT_TITLE      =  1 ,
       DATA_VIEW_COMPONENT_LEFTRULER  =  2 ,
       DATA_VIEW_COMPONENT_RIGHTRULER =  4 ,
       DATA_VIEW_COMPONENT_BOTTOMRULER=  8 ,
       DATA_VIEW_COMPONENT_COLORBAR   =  16,
       DATA_VIEW_COMPONENT_ALL        =  0xFFFF
    } ;

    enum DATA_VIEW_RULER
    {
        DATA_VIEW_RULER_LEFT = 0 ,
        DATA_VIEW_RULER_RIGHT ,
        DATA_VIEW_RULER_BOTTOM ,
        DATA_VIEW_RULER_MAX
    };

    explicit DopplerDataView(QWidget *parent = 0 , DATA_VIEW_COMPONENT eComponent_ = DATA_VIEW_COMPONENT_ALL);
    ~DopplerDataView();
    void DeleteAllWidget();
    QSize GetViewSize();

    void SetDataViewConfigure(int nGroupId_ , int nLaw_ , int eDisplayMode_ );
    void GetDataViewConfigure(int* nGroupId_ , int* nLaw_ , int* eDisplayMode_) const ;
    int  GetDataViewDrawType();
    int  GetGroupId() ;
    int  GetLawId () ;

    void SetLawIdentify(int nId_) ;
    int  GetLawIdentify() const;
	int  GetSScanLawQty();
	int  GetSScanLaw(int index_);

    void EnableComponent(DATA_VIEW_COMPONENT eComponent_);
	void SetRulerRange(double nStart_ , double nStop_ , double nSliderStart_ , double nSliderStop_ , DATA_VIEW_RULER eRuler_ ) ;
	void GetRulerRange(double* nStart_, double* nStop_, double *nSliderStart_, double *nSliderStop_, DATA_VIEW_RULER eRuler_ ) ;
    void SetRulerColor(QColor* color , DATA_VIEW_RULER eRuler_ ) ;
    void SetRulerMarkerColor(QColor* color , DATA_VIEW_RULER eRuler_ ) ;
    void SetRulerUnit(QString* unit  , DATA_VIEW_RULER eRuler_) ;
    void SetTitleBarColor(QColor& color_) ;
    void SetTitleBarString(QString& str_)  ;
	void SetTitleBarStringColor(QColor color_) ;
    void SetColorBarColorIndex (void* index) ;
    void AddOverlayItems(QGraphicsItem* item_);
    void SetDrawScan(DopplerDrawScan* pDraw_)  ;
    DopplerDrawScan* GetDrawScan() const;
    void UpdateDrawing();
    void UpdateMeasure() ;


    void SetItemGeometry(DopplerGraphicsItem* item , QRectF& rect) ;
    QPointF TranslateToScenePlan(QPointF* pPos_) ;
    void SetWidgetSelected(bool bSelect_) ;
    DopplerViewItems* GetItemGroup() const ;
    void UpdateScene();
	QRect GetZoomRect();
private:
    void CreateComponent();
    void RangeTransfer(QPair<double , double> range_ , QPair<double , double>* pos_) ;
    QPointF PixTransferToReal(QPointF& pos_) ;
    void resizeEvent(QResizeEvent *) ;
    void paintEvent(QPaintEvent *) ;
    void mouseReleaseEvent(QMouseEvent *) ;
    void mousePressEvent(QMouseEvent *) ;
private:
    QGridLayout*        m_pLayout           ;
    DopplerRulerBar*    m_pRulers[DATA_VIEW_RULER_MAX]  ;
    DopplerTitleBar*    m_pTitleBar     ;
    DopplerColorBar*    m_pColorBar     ;
    DopplerGraphicView* m_pGraphicView ;
    DATA_VIEW_COMPONENT m_eComponent ;
    DopplerViewItems*   m_pItemsGroup ;
    int m_nGroupId , m_nLaw , m_eDisplayMode , m_nIdentify;
	QPair<double , double>  RulerRange[4];
	QPair<double , double>  SliderRange[4];
	//QPair<double , double>  ZoomRange[4];
	bool   m_bSelected ;

signals:
    void signalMousePressed(QWidget*);
    //void signalViewFrameMenuSelection(DopplerDataView* , int);
    void signalItemMoved(DopplerDataView* , DopplerGraphicsItem*)  ;
    void signalDataViewResized(DopplerDataView*);
    void signalMouseDoubleClicked(DopplerDataView* , QPointF pos_) ;

public slots:
	void slotZoomAction(QRectF rect) ;
protected slots:

    void slotItemMoved(DopplerGraphicsItem* item_);
    void slotViewMouseRelease(QMouseEvent*) ;
    void slotViewMousePressed(QMouseEvent*) ;
    void slotMouseDoubleClicked(QPointF pos_);
    void slotTofdDragProAction(QPointF, QPointF);
	void slotLeftRulerMoved(double nStart_, double nStop_) ;
	void slotBottomRulerMoved(double nStart_, double nStop_) ;
	void slotScanRangeMove(int nType_, int nStart_, int nStop_) ;
};

#endif // DOPPLERDataView_H
