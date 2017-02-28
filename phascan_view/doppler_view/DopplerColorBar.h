/***************************
  Name:  DopplerColorBar
  Description:   数据显示窗口颜色条
*********************************/


#ifndef DOPPLERCOLORBAR_H
#define DOPPLERCOLORBAR_H

#include <QWidget>
#include <configure/DopplerColorIndex.h>

#define DOPPLER_COLOR_BAR_WIDTH   10

class DopplerColorBar : public QWidget
{
    Q_OBJECT
public:
    explicit DopplerColorBar(QWidget *parent = 0);
    void setColorIndex(void* color_);
private:
    unsigned char (*color)[3]  ;
    int m_nColorQty  ;
    unsigned int Color[256] ;
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // DOPPLERCOLORBAR_H
