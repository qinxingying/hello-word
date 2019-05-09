/**********************************
  Description: 显示二代数据的焊缝图示的图像
**********************************/

#ifndef WELDSHOWDATAIIWIDGET_H
#define WELDSHOWDATAIIWIDGET_H

#include <QWidget>
#include "Instrument.h"

class WeldShowDataIIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WeldShowDataIIWidget(QWidget *parent = 0);
    void SerPart(PART_CONFIG *pInfo_);

protected:
    void paintEvent( QPaintEvent *event);

private:
    void UpdateDisplayRangle();
    void PositionTransfer( QPointF &pos_);
    void DrawWeld( QPainter &painter);
    void DrawWeldI( QPainter &painter);
    void DrawWeldV( QPainter &painter);
    void DrawWeldU( QPainter &painter);
    void DrawWeldVY( QPainter &painter);
    void DrawWeldVV( QPainter &painter);
    void DrawWeldUU( QPainter &painter);
    void DrawWeldUV( QPainter &painter);
    struct RANGE_INFO
    {
        double fWidth;
        double fHeight;
        double fStartY;
        double fStopY;
        double fPixelSize;
    };
    PART_CONFIG *m_pPart;
    RANGE_INFO m_cRange;
    float m_fThickness;
};

#endif // WELDSHOWDATAIIWIDGET_H
