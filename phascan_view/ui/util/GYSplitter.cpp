#include "GYSplitter.h"

GYSplitter::GYSplitter(QWidget *parent) :
    QSplitter(parent)
{
	m_nTimerId = startTimer(500);
}

void GYSplitter::timerEvent( QTimerEvent *event )
{
	if(m_nTimerId != 0)
		killTimer(m_nTimerId);
    Q_UNUSED(event);
}

