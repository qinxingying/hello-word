#include "PoppingTabWidget.h"
#include "PoppingTabBar.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QResizeEvent>

PoppingTabWidget::PoppingTabWidget(QWidget *parent) : QTabWidget(parent)
{
    tb = new PoppingTabBar(this);
    setTabBar(tb);
    connect(tb, SIGNAL(extend()), this, SLOT(slotExtend()));
    connect(tb, SIGNAL(shrink()), this, SLOT(slotShrink()));
    m_bHideAble = true;

    connect(tb, SIGNAL(signalLastTabButton(Qt::MouseButton)), SLOT(slotLastTabButtonClicked(Qt::MouseButton)));
    connect(tb, SIGNAL(signalRightButtonDoubleClicked(int)), SLOT(slotRightButtonDoubleClicked(int)));
}

void PoppingTabWidget::slotLastTabButtonClicked(Qt::MouseButton btn_)
{
    emit signalLastTabBottonCliecked(btn_);
}

void PoppingTabWidget::slotRightButtonDoubleClicked(int nId_)
{
    emit signalRightButtonDoubleClicked(nId_);
}

void PoppingTabWidget::SetHideAble(bool hide_)
{
    m_bHideAble = hide_;
}

void PoppingTabWidget::slotExtend()
{
   if(!m_bHideAble)  return;
   int _nWidth = getMinShowWidth();
   setFixedWidth(_nWidth);
}

void PoppingTabWidget::slotShrink()
{
    if(!m_bHideAble)  return ;
    setMinimumWidth(tabBar()->width());
    setMaximumWidth(tabBar()->width());
}

void PoppingTabWidget::showEvent (QShowEvent*)
{
    slotExtend();
}

void PoppingTabWidget::resizeEvent (QResizeEvent * e)
{
    QTabWidget::resizeEvent(e);
}

int PoppingTabWidget::getMinShowWidth() const
{
    return 350; //QApplication::desktop()->width() * 0.2;
}
