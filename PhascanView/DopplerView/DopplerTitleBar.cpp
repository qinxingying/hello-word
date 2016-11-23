#include "DopplerTitleBar.h"
#include <QPainter>
DopplerTitleBar::DopplerTitleBar(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(DOPPLER_TITLE_BAR_HEIGHT);
    //******* set default color
	QColor _cBgColor (0 , 0 , 0) ;
    SetBackgroudColor(_cBgColor);
    m_cFgColor = QColor(255, 255 , 255) ;
    setAutoFillBackground(true);
    //******* set default label
    m_strTitle = QString("Doppler A B S C Scan Data Display Window") ;
}


void DopplerTitleBar::SetBackgroudColor(QColor& pColor_)
{
    m_cBgColor = pColor_ ;
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background , m_cBgColor);
    setPalette(pal);
}

void DopplerTitleBar::SetTextColor(QColor& pColor_)
{
    m_cFgColor = pColor_ ;
    update();
}

void DopplerTitleBar::SetTitle(QString& strTitle_)
{
    m_strTitle = strTitle_ ;
    update();
}

void DopplerTitleBar::paintEvent(QPaintEvent* /*cEvent_*/)
{
    QPainter painter(this);
    QPen _OldPen = painter.pen() ;
    QPen _NewPen = _OldPen ;
    _NewPen.setColor(m_cFgColor);
    painter.setPen(_NewPen);
    painter.drawText( 22 , 2 , width() , height() , Qt::AlignLeft , m_strTitle);
    painter.setPen(_OldPen);
}
