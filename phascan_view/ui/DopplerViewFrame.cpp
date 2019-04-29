#include "DopplerViewFrame.h"
#include "gHeader.h"
#include "ProcessDisplay.h"
#include "MainWindow.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QSplitter>
#include <QBoxLayout>
#include <QMessageBox>



DopplerViewFrame::DopplerViewFrame(QWidget *parent) :
	QWidget(parent)
{
	m_nId = -1;

	setAcceptDrops(true);

	// 以异步的方式调用新窗口的创建
    connect(this,  SIGNAL(signalCreateDrawWindow(QWidget*, int , int)),
            SLOT(slotCreateDrawWindow(QWidget* , int , int)));  //Qt::QueuedConnection
}

DopplerViewFrame::~DopplerViewFrame()
{
}


void DopplerViewFrame::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("DOPPLER_DISPLAY_ITEM"))
		event->acceptProposedAction();
	else
		event->ignore();
	//setBackgroundRole(QPalette::Highlight);
}

void DopplerViewFrame::dragLeaveEvent(QDragLeaveEvent *)
{
	//setBackgroundRole(QPalette::Background);
}

void DopplerViewFrame::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasFormat("DOPPLER_DISPLAY_ITEM"))
	{
		DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
		int _nGroupQty = _pConfig->common.nGroupQty  ;
		if(m_nId == 0 && _nGroupQty > 1) {
		} else {
			DropEventProcess(event)  ;
		}
		//DropEventProcess(event)  ;
		event->ignore();
	}
	else
		event->ignore();
}

void DopplerViewFrame::DropEventProcess(QDropEvent* event)
{
	QByteArray pieceData = event->mimeData()->data("DOPPLER_DISPLAY_ITEM");
	QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
	QString data ; int _nId , _nGroupId;
	dataStream  >> data >> _nId >> _nGroupId;
	if(_nId < 2)  return  ; // id smaller than 2 is not a item need drop response

	if(ProcessDisplay::IsSizeAvailable(_nId , this))
	{
		QMessageBox::information(NULL, tr("Warning!"),
								 tr("Current Widget size is too small!") ,
								 QMessageBox::Yes, QMessageBox::Yes);
		return ;
	}

	CreateDrawView(_nGroupId, _nId);
}

/*  *************************************************
 *  function: create scan data display window
 *  input   : pWidget_ ->  parent window
 *		      _nId ->  A - B - C - S scan display types id
 *		      nGroupId_->  group id
*************************************************   */
void DopplerViewFrame::slotCreateDrawWindow(QWidget* pWidget_, int _nId , int nGroupId_)
{
    ProcessDisplay _display ;
	_display.SetCurrentGroupId(nGroupId_);
	_display.CreateViews(pWidget_  , _nId) ;
	pWidget_->show();
	g_pMainWnd->RunDrawThreadOnce(false);
	//emit signalDropEvent(_nId) ;
	//sleep(100);
	_display.UpdateAllViewOverlay();
}

void DopplerViewFrame::CreateDrawView(int nGroupId_, int nId_)
{
	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();
	for(int i = 0 ; i < _pList->count() ; i++)
	{
        delete _pList->at(i);
	}
	_pList->clear();
	delete this->layout();

    emit signalCreateDrawWindow(this , nId_ , nGroupId_);
}


