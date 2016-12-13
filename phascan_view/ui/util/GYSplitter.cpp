#include "GYSplitter.h"

GYSplitter::GYSplitter(QWidget *parent) :
    QSplitter(parent)
{
	/*
	this->setOpaqueResize(false);
//	this->setStretchFactor(1,1);
	this->setStyleSheet("QSplitter::handle { background-color: black }");

	for(int i = 0; i < this->count(); i++) {
		QSplitterHandle *splitterHandle = this->handle(i);
		if(splitterHandle) {
			splitterHandle->setDisabled(true);
		}
	}*/
	m_nTimerId = startTimer(500);
}

void GYSplitter::timerEvent( QTimerEvent *event )
{
	//this->setStyleSheet("QSplitter::handle { background-color: black }");
	/*
	for(int i = 0; i < this->count(); i++) {
		QSplitterHandle *splitterHandle = this->handle(i);
		if(splitterHandle) {
			splitterHandle->setDisabled(true);
		}
	}*/

	if(m_nTimerId != 0)
		killTimer(m_nTimerId);
    Q_UNUSED(event);
}

