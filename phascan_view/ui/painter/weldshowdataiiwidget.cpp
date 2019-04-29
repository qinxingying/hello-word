#include "weldshowdataiiwidget.h"

WeldShowDataIIWidget::WeldShowDataIIWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pPart = NULL;
}

void WeldShowDataIIWidget::SerPart(PART_CONFIG *pInfo_)
{
    m_pPart = pInfo_;
    m_fThickness = m_pPart->afSize[0];
}

void WeldShowDataIIWidget::paintEvent( QPaintEvent *event)
{

}
