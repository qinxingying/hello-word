#include "DopplerViewFrame.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QSplitter>
#include <QBoxLayout>
#include <QMessageBox>
#include <gHeader.h>
#include "ProcessDisplay.h"


DopplerViewFrame::DopplerViewFrame(QWidget *parent) :
	QWidget(parent)
{
	m_nId = -1;
	//DopplerViewFrame::m_pChildWidgetList = new QList<QWidget*>  ;
	setAcceptDrops(true);
	//************ set back ground color
	//setAutoFillBackground(true);
	//QPalette pal = this->palette() ;
	//pal.setColor(QPalette::Background , QColor(0 , 0 , 0));
	//setPalette(pal);
	// 以异步的方式调用新窗口的创建
	connect(this,  SIGNAL(signalCreateDrawWindow(QWidget*, int , int)) ,
			SLOT(slotCreateDrawWindow(QWidget* , int , int))
			 , Qt::QueuedConnection) ;
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

#if 0
	//######################################################
	//##################	  reserve	 ##################
	//######################################################
	QByteArray pieceData = event->mimeData()->data("DOPPLER_DISPLAY_ITEM");
	QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
	QString data ; int _nId , _nGroupId;
	dataStream  >> data >> _nId >> _nGroupId;
	if(_nId < 2)  return  ; // id smaller than 2 is not a item need drop response

	QList<QWidget*>* _pList = g_pMainWnd->GetCurrentDisplayTableWidgetList();

	QPoint _pos1 = mapToGlobal(event->pos()) ;
	int _nChildWidgetListCount = _pList->count()  ;

	if(_nChildWidgetListCount)
	{
		//判断在哪个窗口中重新构建新窗口
		for(int i = 0 ; i< _nChildWidgetListCount ; i++)
		{
			QWidget* _pWidget = _pList->at(i) ;
			QPoint _pos = _pWidget->mapToGlobal( QPoint(0 , 0)) ;
			QRect _rect(_pos.x(), _pos.y(), _pWidget->width(), _pWidget->height()) ;
			// judge if the drop pos is in geometry of which m_pChildWidgetList DopplerDataView
			if(_rect.contains(_pos1))
			{
				if(ProcessDisplay::IsSizeAvailable(_nId , _pWidget))
				{
					QMessageBox::information(NULL, tr("Warning!"),
											 tr("Current Widget size is too small!") ,
											 QMessageBox::Yes, QMessageBox::Yes);
					return ;
				}
				// remove this view in list
				_pList->removeAt(i);
				QSplitter* _splitter = (QSplitter*)_pWidget->parentWidget()  ;
				int _nIndex = _splitter->indexOf(_pWidget);
				// add new and remove old widget
				QList<int> _size = _splitter->sizes();
				DopplerViewFrame* _frame = new DopplerViewFrame(this) ;
				_splitter->insertWidget(_nIndex , _frame);
				delete _pWidget ;

				_splitter->refresh();
				_splitter->setSizes(_size);
				_splitter->setCollapsible(_nIndex, false);

				emit signalCreateDrawWindow(_frame , _nId , _nGroupId)  ;
				break ;
			}
		}
	}
	else
	{
		emit signalCreateDrawWindow(this , _nId , _nGroupId)  ;
	}
	//######################################################
	//##################	  reserve	 ##################
	//######################################################
#endif
}

#include <MainWindow.h>
/*  *************************************************
 *  name : slotCreateDrawWindow
 *  function  : create scan data display window
 *  input:  pWidget_ ->  parent window
 *		  _nId	 ->  A - B - C - S scan display types id
 *		  nGroupId_->  group id
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
		delete _pList->at(i) ;
	}
	_pList->clear();
	delete this->layout();

	emit signalCreateDrawWindow(this , nId_ , nGroupId_)  ;
}


