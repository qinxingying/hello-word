#ifndef QWELDSHOWWIDGET_H
#define QWELDSHOWWIDGET_H

#include <QWidget>
#include <configure/Instrument.h>

class QWeldShowWidget : public QWidget
{
	Q_OBJECT
public:
	explicit QWeldShowWidget(QWidget *parent = 0);
	void SerPart(PART_CONFIG* pInfo_);

protected:
	struct RANGE_INFO
	{
		double fWidth  ;
		double fHeight ;
		double fStartY ;
		double fStopY  ;
		double fPixelSize  ;
	} ;

	void  paintEvent ( QPaintEvent * event ) ;
	void  DrawWeld(QPainter& painter) ;
	void  DrawWeldI(QPainter& painter);
	void  DrawWeldV(QPainter& painter);
	void  DrawWeldDV(QPainter& painter) ;
	void  DrawWeldU (QPainter& painter) ;
	void  UpdateDisplayRangle() ;
	void  PositionTransfer(QPointF& pos_) ;

	PART_CONFIG* m_pPart;
	RANGE_INFO m_cRange ;
	float m_fThickness ;

signals:
public slots:

};

#endif // QWELDSHOWWIDGET_H
