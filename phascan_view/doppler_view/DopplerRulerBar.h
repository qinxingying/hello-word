#ifndef DOPPLERRULERBAR_H
#define DOPPLERRULERBAR_H

#include <QWidget>


#define DOPPLER_RULER_WIDTH	20

class DopplerRulerBar : public QWidget
{
public:
	enum RULER_BAR_TYPE
	{
		RULER_BAR_LEFT  = 0,
		RULER_BAR_RIGHT	,
		RULER_BAR_BOTTOM   ,
		RULER_BAR_TOP	  ,
		RULER_BAR_MAX
	};

	Q_OBJECT
public:
	explicit DopplerRulerBar(QWidget *parent = 0 , RULER_BAR_TYPE eType_ = RULER_BAR_LEFT);
	void   SetBackgroudColor(QColor* cColor_);
	void   SetMarkerColor(QColor* cColor_)   ;
	void   SetMarkerRange(double nStart_ , double nStop_, double nSliderStart_ , double nSliderStop_);
	void   GetMarkerRange(double* nStart_ , double* nStop_, double* nSliderStart_ , double* nSliderStop_);
	void   SetMarkerUnit(QString* strUnit_) ;
	void   ShowSlider(bool bDisp_) {m_bSliderON = bDisp_;}
    void   SetTofdStatus(bool tofdDepth, float pcs){ m_tofdDepth = tofdDepth; m_PCS = pcs;}
    void   GetTofdStatus(bool &tofdDepth, float &pcs){tofdDepth = m_tofdDepth; pcs = m_PCS;}
protected:
	void   paintEvent(QPaintEvent *) ;
	void   drawLeftRuler(QPainter& painter);
    void   drawTofdLeftRuler(QPainter& painter);
	void   drawRightRuler(QPainter& painter);
	void   drawBottomRuler(QPainter& painter);
    void   drawTofdBottomRuler(QPainter& painter);
	int	   getRulerMarkQty(int nLength_) ;
    double calDepth(double soundPath);
    double transDepthToSoundPath(double depth);
	double getRulerMarInterval(int nMarkQty_ , double nRange_) ;

//	void   getSliderArea(QPainter& painter);
//	void   getSliderRect(QPainter& painter);

	void   drawSlider(QPainter& painter);
	void   drawLeftSlider(QPainter& painter);
	void   drawRightSlider(QPainter& painter);
	void   drawBottomSlider(QPainter& painter);

	void   enterEvent(QEvent* event);
	void   leaveEvent(QEvent* event);

	void   mouseMoveEvent(QMouseEvent* event);
	void   mousePressEvent(QMouseEvent* event);
	void   mouseReleaseEvent(QMouseEvent* event);

	void   sliderDispPro(QPoint mousePos_);
	void   CalSliderArea();
	void   CalSliderRect();
	void   SliderMovePro(QPoint point_);

	//void dragEnterEvent(QDragEnterEvent *)  ;
	//void dragLeaveEvent(QDragLeaveEvent *)  ;
	//void dropEvent(QDropEvent *)  ;
protected:
	RULER_BAR_TYPE	m_eType ;
	QColor			m_cBgColor ;
	QColor			m_cFgColor ;

	QColor			m_cSlider;
	QRectF			m_rcSlArea;
	QRectF			m_rcSlider;
	QRectF			m_rcDrag;
	QPoint			m_ptDrag;

	bool			m_bSliderON;
	bool			m_bSliderDrag;
	double			m_nStart  ;
	double			m_nEnd	;
	double			m_nSliderStart;
	double			m_nSliderEnd;
	QString			m_strUnit ;
    bool            m_tofdDepth;
    float           m_PCS;

signals:
	void signalRulerMoved(double nStart_, double nStop_) ;

public slots:

};

#endif // DPLRULERBAR_H
