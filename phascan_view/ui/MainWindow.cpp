#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog/DialogAddOneGroup.h"
#include "threads/DataRefreshThread.h"
#include "InstrumentSettingWidget.h"
#include "DopplerConfigure.h"
#include "DopplerDataFileOperateor.h"
#include "gHeader.h"
#include "DopplerDataView.h"
#include "ParameterProcess.h"
#include "ProcessDisplay.h"

#include <QSplitterHandle>
#include <QMessageBox>
#include <QToolBox>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::NoContextMenu);
    setMinimumSize(1024 , 720);

    m_pThreadDraw  = DataRefreshThread::Instance()  ;
    m_bParamBackMode = false;

    ui->TabWidgetRight->SetHideAble(false) ;

    ui->actionNew_Config->setDisabled(true);
    ui->actionSave->setDisabled(true);
    // tool bar
    ui->actionNew->setDisabled(true);
    ui->actionSaveFile->setDisabled(true);

    // init right display widget list
    for(int i = 0 ; i < MAX_LIST_QTY ; i++)
    {
        m_pViewList[i] = new QList<QWidget*>;
        m_pViewList[i]->clear();
    }

    // status bar
    CreateStatusBar() ;

    //CreateInstrumentSettingWidget(ui->Group1);
    connect(ui->TabWidgetLeft  , SIGNAL(signalLastTabBottonCliecked(Qt::MouseButton)) , this , SLOT(slotsLeftTabButton(Qt::MouseButton))) ;
    connect(ui->TabWidgetLeft  , SIGNAL(signalRightButtonDoubleClicked(int)) , this , SLOT(slotLeftTabRightButtonDoubleClicked(int)));
    connect(ui->TabWidgetRight , SIGNAL(signalLastTabBottonCliecked(Qt::MouseButton)) , this , SLOT(slotsRightTabButton(Qt::MouseButton))) ;
    connect(ui->TabWidgetRight , SIGNAL(signalRightButtonDoubleClicked(int)) , this , SLOT(slotRightTabRightButtonDoubleClicked(int))) ;
    connect(ui->TabWidgetLeft  , SIGNAL(currentChanged(int)) , SLOT(slotCurrentGroupChanged(int))) ;
    connect(ui->TabWidgetRight , SIGNAL(currentChanged(int)) , SLOT(slotCurrentDispChanged(int))) ;

    // tofd setting dialog
    m_iCurGroup  = 0;
    m_nLawIdSel  = 0;
    m_bCursorSel = true;
    m_nAlloff	= 0;
    SetDispTabText();

    //------------ Language----------------//
    translator = new QTranslator(this);
    qApp->installTranslator(translator);
    slot_actionChinese_triggered(); // default Chinese
    UI_LanguageSwitch = true;

    connect(ui->actionEnglish, SIGNAL(triggered()), this, SLOT(slot_actionEnglish_triggered()));
    connect(ui->actionChinese, SIGNAL(triggered()), this, SLOT(slot_actionChinese_triggered()));
}

MainWindow::~MainWindow()
{
        if(m_pThreadDraw)
                m_pThreadDraw->terminate();

        for(int i = 0 ; i < MAX_LIST_QTY ; i++)
        {
                for(int j = 0 ; j < m_pViewList[i]->count() ; j++ )
                {
                        delete m_pViewList[i]->at(j) ;
                }
                delete m_pViewList[i]  ;
        }

        DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
        delete _pConfig ;

//	delete ui;
}

void MainWindow::closeEvent (QCloseEvent* e)
{
        QMainWindow::closeEvent (e) ;
}

void MainWindow::resizeEvent(QResizeEvent* )
{
        int _nWidth   = ui->centralwidget->width();
        int _nHeight  = ui->centralwidget->height();
        ui->splitter->setGeometry(0 , 0 , _nWidth , _nHeight);
}

// create status bar
void MainWindow::CreateStatusBar()
{
        QStatusBar* _status = ui->statusbar ;
        QPalette pal = this->palette() ;
        pal.setColor(QPalette::Background , QColor(0 , 0 , 0));
        _status->setPalette(pal);
        _status->setAutoFillBackground(true);
        //################################
        m_pStatusCell[0] = new QLabel(_status) ;
        m_pStatusCell[1] = new QLabel(_status) ;
        m_pStatusCell[2] = new QLabel(_status) ;

        _status->addWidget(m_pStatusCell[0]);
        _status->addWidget(m_pStatusCell[1]);
        _status->addWidget(m_pStatusCell[2] , 1);
        UpdateStatusBarInfo() ;
}

// update status bar information when new *.data or *.cfg file is loaded
void MainWindow::UpdateStatusBarInfo()
{
        QPalette pal = this->palette() ;
        pal.setColor(QPalette::Foreground , QColor(0, 255 , 0));

        ParameterProcess* _pOpp = ParameterProcess::Instance() ;

        m_BarInfo.nGroupQty = _pOpp->GetGroupQty() ;
        m_BarInfo.nLawQty   = _pOpp->GetTotalLawQty() ;
        m_BarInfo.nDataSize = _pOpp->GetTotalDataSize() ;

        QLabel* _pCell = m_pStatusCell[0]  ;
        QString _str; _str.sprintf("Setting Info: Group Qty:[%d] Law Qty:[%d] Data Size:[%d]" ,m_BarInfo.nGroupQty , m_BarInfo.nLawQty , m_BarInfo.nDataSize) ;
        _pCell->setPalette(pal);
        _pCell->setText(_str);
}


/****************************************************************************
  Description: 开启全部窗口(DopplerDataView)扫查数据的更新
*****************************************************************************/
void MainWindow::RunDrawThread()
{
        DataRefreshThread* _pThread = DataRefreshThread::Instance() ;
        _pThread->start();
}
/****************************************************************************
  Description: 全部窗口(DopplerDataView)扫查数据更新一次
*****************************************************************************/
void MainWindow::RunDrawThreadOnce(bool bUseDrawThread_)
{
        DataRefreshThread* _pThread = DataRefreshThread::Instance() ;
        if(bUseDrawThread_)
                _pThread->RunOnce(RUN_IN_DRAW_THREAD);
        else
                _pThread->RunOnce(RUN_IN_MAIN_THREAD);
}

/****************************************************************************
  Description: 更新窗口(DopplerDataView)的全部设置
*****************************************************************************/
void MainWindow::UpdateAllDisplay()
{
        ProcessDisplay _process ;
        _process.UpdateAllView();
}

void MainWindow::SetStatusBarMessageColor(int nId_, QColor& fgColor_ , QColor& bgColor_)
{
        QLabel* _pCell = m_pStatusCell[nId_]  ;
        QPalette pal = this->palette() ;
        pal.setColor(QPalette::Background , bgColor_ );
        pal.setColor(QPalette::Foreground , fgColor_ );
        _pCell->setAutoFillBackground(true);
        _pCell->setPalette(pal);
}

void MainWindow::SetStatusBarMessage(int nId_ , QString& str_)
{
        QLabel* _pCell = m_pStatusCell[nId_]  ;
        _pCell->setText(str_);
}

void MainWindow::slotsLeftTabButton(Qt::MouseButton btn_)
{
        return ;
        if(btn_ == Qt::LeftButton)
        {
                DialogAddOneGroup _dlg(this) ;
                int ret = _dlg.exec();
                if(ret)
                {
                        AddOneGroup() ;
                }
        }
}

void MainWindow::slotLeftTabRightButtonDoubleClicked(int)
{
        return;
}

void MainWindow::DestroyDisplayTab(int nId_)
{
        int _nQty = ui->TabWidgetRight->count() ;
        QList<QWidget*>* _pList = m_pViewList[nId_]   ;
        for(int i = 0 ; i < _pList->count() ; i++)
        {
                delete _pList->at(i) ;
        }
        _pList->clear();

        QWidget* _pTmpWidget = ui->TabWidgetRight->currentWidget() ;
        ui->TabWidgetRight->removeTab(nId_);
        delete _pTmpWidget ;
        // clear
        ui->TabWidgetRight->setCurrentIndex(0);
        _nQty = ui->TabWidgetRight->count() ;

        SetDispTabText();
}

void MainWindow::SetDispTabText()
{
        QString _str ;
        int _nQty = ui->TabWidgetRight->count() ;

        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty  ;

        if(m_nAlloff)
                ui->TabWidgetRight->setTabText(0 , QString(tr("Com Groups")));

        for(int i = 0 ; i < _nGroupQty ; i++)
        {
                if(i+m_nAlloff < _nQty)
                {
                        _str.sprintf("Group %d" , i+1) ;
                        ui->TabWidgetRight->setTabText(i+m_nAlloff , _str);
                }
        }

        if(_nQty > m_nAlloff + _nGroupQty + 1)
        {
                int _nCnt = 1;
                for(int i = m_nAlloff + _nGroupQty ; i < _nQty ; i++)
                {
                        _str.sprintf("Disp %d" , _nCnt++) ;
                        ui->TabWidgetRight->setTabText(i , _str);
                }
        }

        ui->TabWidgetRight->setTabText(_nQty - 1, QString(tr("")));
}

void MainWindow::slotRightTabRightButtonDoubleClicked(int)
{
        DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty  ;
        int _nQty      = ui->TabWidgetRight->count() ;
        int _index     = ui->TabWidgetRight->currentIndex();
//	if(_nQty <= 2)  return  ;
        int _nLimit = _nGroupQty + 1;
        if(_nGroupQty == 1)
                _nLimit = 1;
        if(_index < _nLimit)  return  ;
        _nLimit++;
        if(_nQty <= _nLimit)  return  ;

        QMessageBox messageBox(this);
        QAbstractButton* _pBtnYes;
        QAbstractButton* _pBtnNo;

        messageBox.setText(tr("Delete Current Display Table ?"));
        _pBtnYes = (QAbstractButton*)messageBox.addButton(tr("YES"), QMessageBox::ActionRole);
        _pBtnNo  = (QAbstractButton*)messageBox.addButton(tr("NO"), QMessageBox::ActionRole);

        messageBox.exec();
        if (messageBox.clickedButton() == _pBtnYes)
        {
            int _nIndex = GetDisplayTableIndex() ;
            DestroyDisplayTab(_nIndex); // clear list
        }
        else if(messageBox.clickedButton() == _pBtnNo)
        {
        }
}

void MainWindow::DestroyAllDisplay()
{

        int _nQty = ui->TabWidgetRight->count() ;
        for(int i = 0 ; i < _nQty - 1 ; i++)
        {
                QList<QWidget*>* _pList = m_pViewList[i]   ;
                for(int i = 0 ; i < _pList->count() ; i++)
                {
                        delete _pList->at(i) ;
                }
                _pList->clear();
        }

        ui->TabWidgetRight->setCurrentIndex(0);
        for(int i = 1; i <  _nQty - 1 ; i++)
        {
                QWidget* _pTmpWidget = ui->TabWidgetRight->widget(1) ;
                ui->TabWidgetRight->removeTab(1);
                delete _pTmpWidget ;
        }
}


void MainWindow::slotsRightTabButton(Qt::MouseButton btn_)
{
    if(btn_ == Qt::LeftButton)
    {
        QMessageBox messageBox(this);
        QAbstractButton* _pBtnYes;
        QAbstractButton* _pBtnNo;

        messageBox.setText(tr("Add One View ?"));
        _pBtnYes = (QAbstractButton*)messageBox.addButton(tr("YES"), QMessageBox::ActionRole);
        _pBtnNo  = (QAbstractButton*)messageBox.addButton(tr("NO"), QMessageBox::ActionRole);

        messageBox.exec();
        if (messageBox.clickedButton() == _pBtnYes)
        {
                InsertRightTab();
        }
        else if(messageBox.clickedButton() == _pBtnNo)
        {
        }
    }
}

/****************************************************************************
  Description: 返回当前显示的所有数据显示窗口指针
*****************************************************************************/
QList<QWidget*>* MainWindow::GetCurrentDisplayTableWidgetList()
{
        int _nIndex = GetDisplayTableIndex();
        return m_pViewList[_nIndex]  ;
}

QList<QWidget*>* MainWindow::GetDisplayTableWidgetList(int nIndex_)
{
        return m_pViewList[nIndex_]  ;
}

int  MainWindow::GetDisplayTableQty() const
{
        return ui->TabWidgetRight->count() ;
}

int  MainWindow::GetDisplayTableIndex() const
{
        return ui->TabWidgetRight->currentIndex() ;
}

/****************************************************************************
  Description: 增加一个组参数 并用DopplerGroupTab显示出来
*****************************************************************************/
void MainWindow::AddOneGroup()
{
        DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty - 1;

        DopplerGroupTab* _pGroup = new DopplerGroupTab(ui->TabWidgetLeft);
        _pGroup->SetGroupId(_nGroupQty )  ;

        QString str(tr("Group ")) ; QString str1 ; str1.sprintf("%d", _nGroupQty + 1) ;
        str += str1 ;
        QIcon icon(":/file/resource/main_menu/0-27.png");
        ui->TabWidgetLeft->insertTab(_nGroupQty , _pGroup , icon, str);
        ui->TabWidgetLeft->setCurrentIndex(_nGroupQty);
}

/****************************************************************************
  Description: 确定窗口焦点
*****************************************************************************/
void MainWindow::slotViewFrameButtonClicked(QWidget* pWidget_)
{
        SetSelectedDataView( pWidget_) ;
}

/****************************************************************************
  Description: 当删除和增加时 确定显示的组ID
*****************************************************************************/
void MainWindow::slotCurrentGroupChanged(int nIndex_)
{
        static int _nOldIndex = 0 ;
        if(nIndex_ + 2 >= ui->TabWidgetLeft->count())  return ;
        if(ui->TabWidgetLeft->count() < 4)  return ;

        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty  ;
        int _nCurRight = ui->TabWidgetRight->currentIndex();
        if(_nCurRight < 0)				_nCurRight = 0;
        if(_nCurRight >= MAX_LIST_QTY)	_nCurRight = MAX_LIST_QTY - 1;

        if(m_nAlloff && _nCurRight == 0) {
        } else {
                m_iCurGroup = nIndex_;
                if(m_iCurGroup >= _nGroupQty)
                        m_iCurGroup = 0;

                QList<QWidget*>* _list = m_pViewList[_nCurRight];
                DopplerDataView* _pDraw = NULL;
                if(_list->count() > 0) {
                        _pDraw = (DopplerDataView*)_list->at(0);
                        if(_pDraw->GetGroupId() != m_iCurGroup) {
                                for(int i = m_nAlloff; i < ui->TabWidgetRight->count(); i++) {
                                        _list = m_pViewList[i];
                                        if(_list->count() > 0) {
                                                _pDraw = (DopplerDataView*)_list->at(0);
                                                if(_pDraw->GetGroupId() == m_iCurGroup) {
                                                        ui->TabWidgetRight->setCurrentIndex(i);
                                                        break;
                                                }
                                        }
                                }
                        }
                }
        }
        //------------------------------------------------------

        DopplerGroupTab* _pWidget = (DopplerGroupTab*)ui->TabWidgetLeft->widget(_nOldIndex)  ;

        //------------------------------------------------------
        QToolBox* _toolBox = _pWidget->GetToolBox();
        if(_toolBox)
        {
        int _nId = _toolBox->currentIndex()  ;

        _pWidget = (DopplerGroupTab*)ui->TabWidgetLeft->widget(nIndex_)  ;
        _nOldIndex = nIndex_ ;
        if(_pWidget)
        {
                _toolBox = _pWidget->GetToolBox();
                _toolBox->setCurrentIndex(_nId);
        }
        }
}

void MainWindow::SetCurGroup(int nGroupID_)
{
        m_iCurGroup = nGroupID_;
        ui->TabWidgetLeft->setCurrentIndex(m_iCurGroup);
}

void MainWindow::slotCurrentDispChanged(int nIndex_)
{
        if(nIndex_ >= MAX_LIST_QTY)
        return;

        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty  ;

        if(_nGroupQty > m_nAlloff)
        {
                if(nIndex_ > 0)
                {
                        QList<QWidget*>* _list = m_pViewList[nIndex_];
                        if(_list->count() > 0)
                        {
                                DopplerDataView* _pDraw = (DopplerDataView*)_list->at(0);
                                int _iGroup = _pDraw->GetGroupId();

                                if(_iGroup < _nGroupQty)
                                {
                                        m_iCurGroup = _iGroup;
                                        if(ui->TabWidgetLeft->currentIndex() < _nGroupQty)
                                        {
                                                ui->TabWidgetLeft->setCurrentIndex(m_iCurGroup);
                                        }
                                }
                        }

                        //ProcessDisplay _process ;
                        //_process.UpdateAllViewCursorOfGroup(m_iCurGroup);
                        ProcessDisplay _proDisplay ;
                   _proDisplay.UpdateAllView();
                }
        }
        //------------------------------------------------------
        RunDrawThreadOnce(true);
}

void MainWindow::SetSelectedDataView(QWidget* pWidget_)
{
        m_pCurrentDataView = pWidget_ ;
}

/****************************************************************************
  Description: 参数和数据加载时  更新参数窗口
*****************************************************************************/
void MainWindow::UpdateTableLeft()
{
        // disconnect for signal unpredicted
        disconnect(ui->TabWidgetLeft  , SIGNAL(currentChanged(int)) , 0 , 0) ;
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty ;
        int _nTabQty   = ui->TabWidgetLeft->count() ;
        while(_nTabQty > 2)
        {
                QWidget* _pWidget  = ui->TabWidgetLeft->widget(0);
                ui->TabWidgetLeft->removeTab(0);
                delete _pWidget ;
                _nTabQty   = ui->TabWidgetLeft->count() ;
        }

        for(int i = 0 ; i < _nGroupQty ; i++)
        {
                DopplerGroupTab* _pGroup = new DopplerGroupTab(ui->TabWidgetLeft);
                _pGroup->SetGroupId(i)  ;
                QString str(tr("Group ")) ; QString str1 ; str1.sprintf("%d", i + 1) ;
                str += str1 ;
                QIcon icon(":/file/resource/main_menu/0-27.png");
                ui->TabWidgetLeft->insertTab(i , _pGroup , icon, str)  ;
        }

        ui->TabWidgetLeft->setCurrentIndex(0);
        connect(ui->TabWidgetLeft  , SIGNAL(currentChanged(int)) , SLOT(slotCurrentGroupChanged(int))) ;
}

void MainWindow::SetWndName()
{
    int _nQty = ui->TabWidgetLeft->count() ;
    if(_nQty < 3 )  return;

    for(int i = 0 ; i< _nQty - 2 ; i++)
    {
        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidgetLeft->widget(i);
        _pGroup->SetWndName();
        _pGroup->UpdateGroupConfig();
    }
}

void MainWindow::UpdateCombinationDisplay(void)
{
        ui->TabWidgetRight->setCurrentIndex(0);
        DopplerViewFrame* _pViewFrame = (DopplerViewFrame*)ui->TabWidgetRight->currentWidget();
        _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_ALLGROUP);
        _pViewFrame->SetViewFrameId(0);
        _pViewFrame->update();

        SetWndName();
}

void MainWindow::SaveCurScreenshot(QString strPath_)
{
        QString _strPath = strPath_;
        QPixmap pixmap = QPixmap::grabWidget(ui->TabWidgetRight->currentWidget());
        pixmap.save(_strPath , "png");
}

void MainWindow::UpdateTableRight()
{
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        int _nGroupQty = _pConfig->common.nGroupQty ;
        int _nTabQty   = ui->TabWidgetRight->count() ;

        m_nAlloff = 1;
        if(_nGroupQty < 2)
                m_nAlloff = 0;

        ui->toolBar->setEnabled(false);
        ui->TabWidgetLeft->setEnabled(false);
        ui->TabWidgetRight->setEnabled(false);

        DopplerViewFrame* _pViewFrame = NULL;
        if(_nGroupQty > 1) {
                for(int i = _nTabQty; i < _nGroupQty+2; i++)
                {
                        InsertRightTab();
                }

                UpdateCombinationDisplay();
                sleep(600);
                for(int i = 1; i < _nGroupQty+1; i++)
                {
                        //ui->TabWidgetLeft->setCurrentIndex(i);
                        ui->TabWidgetRight->setCurrentIndex(i);
                        m_iCurGroup = i-1;
                        //sleep(2000);
                        _pViewFrame = (DopplerViewFrame*)ui->TabWidgetRight->currentWidget();
                        _pViewFrame->SetViewFrameId(i);

                        if(_pConfig->group[m_iCurGroup].eGroupMode == setup_GROUP_MODE_PA) {
                                _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_S_AV);
                        } else {
                                _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_AH_BH);
                        }

                        sleep(600);
                }
                ui->TabWidgetRight->setCurrentIndex(0);
        } else {
                ui->TabWidgetRight->setCurrentIndex(0);
                m_iCurGroup = 0;
                _pViewFrame = (DopplerViewFrame*)ui->TabWidgetRight->currentWidget();
                _pViewFrame->SetViewFrameId(0);

                if(_pConfig->group[m_iCurGroup].eGroupMode == setup_GROUP_MODE_PA) {
                        _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_S_AV);
                } else {
                        _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_AH_BH);
                }
        }


        ui->TabWidgetLeft->setEnabled(true);
        ui->TabWidgetRight->setEnabled(true);
        ui->toolBar->setEnabled(true);
        SetDispTabText();
}

void MainWindow::InsertRightTab()
{
        int _nIndex = ui->TabWidgetRight->count() ;
        if(_nIndex > 9) return; // max group number is 8
        DopplerViewFrame* _pViewFrame = new DopplerViewFrame(ui->TabWidgetRight) ;
        QString _str ;
        _str.sprintf("DISP %d" , _nIndex) ;
        ui->TabWidgetRight->insertTab(_nIndex -1 , _pViewFrame , _str) ;
        ui->TabWidgetRight->setCurrentIndex(_nIndex -1);
        SetDispTabText();
}
void MainWindow::NewConfigure()
{
        QMessageBox messageBox(this);
        messageBox.setText(tr("New Configure ?"));
        QAbstractButton* _pBtnYes = (QAbstractButton*)messageBox.addButton(tr("YES"), QMessageBox::ActionRole);
        messageBox.addButton(tr("NO"), QMessageBox::ActionRole);
        messageBox.exec();
        if (messageBox.clickedButton() == _pBtnYes)
        {
                DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
                _pConfig->InitCommonConfig();
                UpdateTableLeft() ;
        this->setWindowTitle(QString("Doppler V1.1.1: New Setting"));
        }

        UpdateStatusBarInfo();
}

void MainWindow::OpenFile()
{
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        QString _strFileName = QFileDialog::getOpenFileName(
                                this,
                                "Open File Dialog",
                                _pConfig->AppEvn.strDataFilePath,
                                "Doppler Files(*.cfg *.data)");

        OpenFilePro(_strFileName);
}

void MainWindow::OpenFilePro(QString strFileName_)
{
        if(strFileName_.isEmpty())  return ;
        QString suffix = strFileName_.section('.',-1);

        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;

        DestroyAllDisplay()   ;

        int _ret  = 0;
        if ( suffix == "cfg")
                _ret = _pConfig->OpenConfig(strFileName_);
        else if ( suffix == "data")
                _ret = _pConfig->OpenData(strFileName_);

        if(!_ret)
        {
                UpdateTableLeft();
                UpdateStatusBarInfo();
                UpdateTableRight();
                m_iCurGroup = 0;
        }

    this->setWindowTitle(QString("Doppler V1.1.1: ") + strFileName_);
}

void MainWindow::SaveFile()
{
        QString _strFileName =  QFileDialog::getSaveFileName(this,
                                                                   "Save File Dialog",
                                                                   "data",
                                                                   "Doppler Files(*.cfg)");
        if(_strFileName.isEmpty())  return ;
        this->setWindowTitle(QString("Doppler V1.1.1: ") + _strFileName);
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        _pConfig->SaveConfig(_strFileName);
}

void MainWindow::ScreenShot()
{
    QString _strPath = QDir::currentPath();
    QPixmap pixmap = QPixmap::grabWidget(this);
    pixmap.save(_strPath , "png");
}

#include <report/DopplerHtmlReport.h>
#include <QPixmap>

/****************************************************************************
  Description: 在报告中加入一条新数据记录
*****************************************************************************/
void MainWindow::ReportAddOneItem()
{
        static int _nPixId = 0 ;
        int _nIndex = GetDisplayTableIndex();
        if(!m_pViewList[_nIndex]->count()) return ;
//	DopplerDataView* pView = (DopplerDataView* )m_pViewList[_nIndex]->at(0) ;

        int _nGroup = m_iCurGroup;
        DopplerConfigure*  _pConfig = DopplerConfigure::Instance() ;
        GROUP_CONFIG&        _group = _pConfig->group[_nGroup] ;
        int _nLawId = _group.afCursor[setup_CURSOR_LAW];

        DopplerHtmlReport* _pReport = _pConfig->GetReportOpp() ;
        ReportValueItem      _value ;

        _value.fPos     =  _pConfig->common.scanner.fScanPos ;
        _value.nGroupId = _nGroup ;
        _value.nLawId   = _nLawId;
        int* _pMeasure  = _group.aeMeasureType ;
        int _nQty = 0 ;
        for(int i = 0 ; i < 5 ; i++)
        {
                if(_pMeasure[i])
                {
                        _value.szValue[_nQty] = CalcMeasurement::GetMeasureValue(_nGroup , _nLawId , (FEILD_VALUE_INDEX)_pMeasure[i] );
                        _nQty++  ;
                }
        }
        for(int i = _nQty ; i < 5 ; i ++) _value.szValue[i] = QString("-") ;
        QString _strPath ;
        _strPath.sprintf("img%04d.png" , _nPixId++ ) ;
        _value.szPixmap = _strPath ;

        _pReport->AddOneValueItem(&_value);
        SaveCurScreenshot(_strPath);
}

/****************************************************************************
  Description: 在报告中删除一条数据记录
*****************************************************************************/
void MainWindow::ReportDelOneItem()
{
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        DopplerHtmlReport* _pReport = _pConfig->GetReportOpp() ;
        _pReport->DelOneValueItem();
}

/****************************************************************************
  Description: 设置报告格式
*****************************************************************************/
#include <ui/dialog/DialogReportSetting.h>
void MainWindow::ReportSetting()
{
        DialogReportSetting _dialog  ;
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        DopplerHtmlReport* _pReport = _pConfig->GetReportOpp() ;
        ReportInfo* _pInfo = _pReport->GetReportInfo() ;
        _dialog.SetReportInfo(_pInfo);
        int _nRet = _dialog.exec();
        if(_nRet)
        {
                _pInfo = _dialog.GetRePortInfo() ;
                _pReport->SetReportInfo(_pInfo);
        }
}

/****************************************************************************
  Description: 报告保存
*****************************************************************************/
void MainWindow::ReportSave()
{
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        DopplerHtmlReport* _pReport = _pConfig->GetReportOpp() ;
        _pReport->SaveReport();
}

/****************************************************************************
  Description: 在报告中加入一条新数据记录
*****************************************************************************/
void MainWindow::TofdSetting()
{
}

#include "DopplerTofdOpp.h"
void MainWindow::TofdDataPro(TOFD_PRO_STATUS proSt_)
{
        DopplerTofdOpp opp;

        if(proSt_ == TOFD_PRO_REPEAL)
        {
        opp.TofdDataProRepeal(m_iCurGroup);
        }
        else if(proSt_ == TOFD_PRO_REDO)
        {
        opp.TofdDataProRedo(m_iCurGroup);
        }
        else
        {
        if(opp.TofdDragProStart(m_iCurGroup, proSt_) < 0)
        {
                opp.TofdDataProStart(m_iCurGroup, proSt_, NULL);
                opp.TofdDataToShadow(m_iCurGroup);
        }
        }
        RunDrawThreadOnce(false);
}

void MainWindow::DefectSign(DEFECT_SIGN_TYPE signType_)
{
        DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
        int _ret = _pConfig->DefectSign(m_iCurGroup, signType_);
        if(_ret >= 0) {
                if(_ret == 3) {
                        ProcessDisplay _process ;
                        //GROUP_CONFIG* _pGroup = &_pConfig->group[m_iCurGroup] ;
                        DopplerGroupTab* _pLeftGroup = (DopplerGroupTab*)ui->TabWidgetLeft->widget(m_iCurGroup);
                        _pLeftGroup->UpdateDefectBox();
                        _pLeftGroup->UpdateDefectValue() ;

                        int _index = _pConfig->m_dfParam[m_iCurGroup].index;
                        //bool _bTmp = _pGroup->bShowDefect;
                        //_pGroup->bShowDefect = false;
                        _pConfig->m_nCutBmpNo[m_iCurGroup] = _index+1;
                        _process.UpdateAllViewCursorOfGroup(m_iCurGroup) ;
                        //RunDrawThreadOnce(true);
                        sleep(400);

                        DEFECT_INFO* _pDfInfo = _pConfig->GetDefectPointer(m_iCurGroup, _index);
                        QString _strPath = _pConfig->m_szDefectPathName + QString(tr("/")) + QString(tr(_pDfInfo->srtImageName)) + QString(tr(".png"));
                        SaveCurScreenshot(_strPath);
                        sleep(200);
                        //_pGroup->bShowDefect = _bTmp;
                        _pConfig->m_nCutBmpNo[m_iCurGroup] = 0;
                        _process.UpdateAllViewCursorOfGroup(m_iCurGroup) ;
                }
                RunDrawThreadOnce(false);
        }
}

/****************************************************************************
  Description: 参数设置窗口与数据显示窗口同步   主要是光标
*****************************************************************************/
void MainWindow::slotItemMoved(DopplerDataView* pView_, DopplerGraphicsItem* pItem_)
{
        int _nGroupId , _nLawId , _nDisplay  ;
        int _nItemType = pItem_->GetItemType()  ;

        pView_->GetDataViewConfigure( &_nGroupId ,  &_nLawId ,  &_nDisplay);

        ParameterProcess* _process = ParameterProcess::Instance();
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        GROUP_CONFIG&       _group = _pConfig->group[_nGroupId];
        int             _nGroupQty = _pConfig->common.nGroupQty;

        ProcessDisplay   _proDispy;
        switch (_nItemType)
        {
        //case OVERLAYS_GATE :
        case DOPPLER_GRAPHICS_ITEM_LAW_MARKER  :
                {
                        int _nId =  ((DopplerLawMarker*)pItem_)->GetMarkerId();
                        int _nPos = ((DopplerLawMarker*)pItem_)->GetMarkerPos(_nId) ;
                        int _nTabIndex = GetDisplayTableIndex() ;

                        m_nLawIdSel = _nId;
                        _group.afCursor[setup_CURSOR_LAW] = _nPos;
                        DopplerGroupTab* _pGroupTab = (DopplerGroupTab*)ui->TabWidgetLeft->widget(_nGroupId) ;
                        _pGroupTab->UpdateCurrentAngleCom();
                        _pGroupTab->UpdateSizeingCurves();

                        for(int i = 0 ; i < m_pViewList[_nTabIndex]->count() ; i++)
                        {
                                int _nCurGroup;
                                DopplerDataView* _pView = (DopplerDataView*)m_pViewList[_nTabIndex]->at(i)  ;
                                _pView->GetDataViewConfigure( &_nCurGroup ,  &_nLawId ,  &_nDisplay);
                                if(_nDisplay < 8 && _nGroupId == _nCurGroup) {  // A SCAN  & B SCAN
                                        if(_nId == _pView->GetLawIdentify()) {
                                                _pView->SetDataViewConfigure(_nCurGroup ,  _nPos ,  _nDisplay);
                                                _proDispy.UpdateAll(_pView);
                                        }
                                } else {
                                        _proDispy.UpdateDataViewTitle(_pView);
                                }
                        }
                        RunDrawThreadOnce(true);
                }
                break;
        case DOPPLER_GRAPHICS_ITEM_CURSOR	  :
                {
                        setup_DISPLAY_MODE _eMode = (setup_DISPLAY_MODE)_nDisplay  ;
                        Q_UNUSED(_eMode) ;

                        QRectF	_rect = pItem_->GetItemGeometryReal() ;

                        int _nItemId   = pItem_->GetItemId()	;
                        if(_nItemId < 0 || _nItemId > setup_CURSOR_MAX)   break ;

                        float _fCursor = 0;
                        if(DopplerLineItem::LINE_HORIZENTAL == ((DopplerLineItem*)pItem_)->GetLineType()) {
                                _fCursor = _rect.top();
                        } else {
                                _fCursor = _rect.left();
                        }

                        _group.afCursor[_nItemId] = _fCursor;
                        if(_nItemId == setup_CURSOR_S_REF || _nItemId == setup_CURSOR_U_REF) {
                                m_bCursorSel = true;
                        } else if(_nItemId == setup_CURSOR_S_MES || _nItemId == setup_CURSOR_U_MES) {
                                m_bCursorSel = false;
                        }

                        if(_pConfig->AppEvn.bSAxisCursorSync) {
                                if(_nItemId == setup_CURSOR_S_REF || _nItemId == setup_CURSOR_S_MES) {
                                        for(int i = 0; i < _nGroupQty; i++) {
                                                _pConfig->group[i].afCursor[_nItemId] = _fCursor;
                                        }

                                        if(_nDisplay == setup_DISPLAY_MODE_B_H
                                        || _nDisplay == setup_DISPLAY_MODE_B_V
                                        || _nDisplay == setup_DISPLAY_MODE_C_H
                                        || _nDisplay == setup_DISPLAY_MODE_CC_H
                                        || _nDisplay == setup_DISPLAY_MODE_C_V
                                        || _nDisplay == setup_DISPLAY_MODE_CC_V) {
                                                _process->SetupScanPos(_fCursor);
                                        }
                                }
                        }
                        //-------------------------------------
                        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidgetLeft->widget(_nGroupId);
                        _pGroup->UpdateCursorValue();
                        _pGroup->UpdateDefectValue();
                        _pGroup->UpdateTofdParam();

                        _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
                        RunDrawThreadOnce(true);
                }
                break;
        //case OVERLAYS_THICKNESS   :
        //case OVERLAYS_WELD  :
        case DOPPLER_GRAPHICS_ITEM_SCAN:
                {
                        QRectF _rect = pItem_->GetItemGeometryReal() ;
                        float _fCursorPos;
                        if(DopplerLineItem::LINE_HORIZENTAL == ((DopplerLineItem*)pItem_)->GetLineType()) {
                                _fCursorPos = _rect.top()  ;
                        } else {
                                _fCursorPos = _rect.left()  ;
                        }
                        InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidgetLeft->widget(_pConfig->common.nGroupQty);
                        _pScanner->UpdateScanPos();

                        if(_pConfig->AppEvn.bSAxisCursorSync) {
                                pView_->GetDataViewConfigure( &_nGroupId ,  &_nLawId ,  &_nDisplay);
                                for(int i = 0; i < _nGroupQty; i++) {
                                        if(m_bCursorSel) {
                                                _pConfig->group[i].afCursor[setup_CURSOR_S_REF] = _fCursorPos;
                                        } else {
                                                _pConfig->group[i].afCursor[setup_CURSOR_S_MES] = _fCursorPos;
                                        }
                                }

                        }
                        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidgetLeft->widget(_nGroupId);
                        _pGroup->UpdateCursorValue();
                        _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
                        _process->SetupScanPos(_fCursorPos);

                        RunDrawThreadOnce(true);
                }
                break;
        default:
                break;
        }
}

void MainWindow::slotDataViewMouseDoubleClicked(DopplerDataView* pView_, QPointF pos_)
{
        m_bCursorSel = !m_bCursorSel;

        int _nGroupId , _nLawId , _nDisplay  ;
        pView_->GetDataViewConfigure( &_nGroupId ,  &_nLawId ,  &_nDisplay);
        setup_DISPLAY_MODE _eMode = (setup_DISPLAY_MODE)_nDisplay  ;
        DopplerConfigure* _pConfig = DopplerConfigure::Instance() ;
        GROUP_CONFIG& _group = _pConfig->group[_nGroupId];

        bool  _bScanPosSync = false;
        float _fSyncData = 0;

        switch(_eMode)
        {
        case  setup_DISPLAY_MODE_A_H:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_A_REF ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_U_REF ] = pos_.x()  ;
                } else {
                        _group.afCursor[setup_CURSOR_A_MES ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_U_MES ] = pos_.x()  ;
                }
                break;
        case  setup_DISPLAY_MODE_A_V:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_A_REF ] = pos_.x()  ;
                        _group.afCursor[setup_CURSOR_U_REF ] = pos_.y()  ;
                } else {
                        _group.afCursor[setup_CURSOR_A_MES ] = pos_.x()  ;
                        _group.afCursor[setup_CURSOR_U_MES ] = pos_.y()  ;
                }
                break;
        case  setup_DISPLAY_MODE_B_H:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_S_REF ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_U_REF ] = pos_.x()  ;
                } else {
                        _group.afCursor[setup_CURSOR_S_MES ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_U_MES ] = pos_.x()  ;
                }
                _fSyncData = pos_.y();
                _bScanPosSync = true;
                break;
        case setup_DISPLAY_MODE_B_V:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_S_REF ] = pos_.x()  ;
                        _group.afCursor[setup_CURSOR_U_REF ] = pos_.y()  ;
                } else {
                        _group.afCursor[setup_CURSOR_S_MES ] = pos_.x()  ;
                        _group.afCursor[setup_CURSOR_U_MES ] = pos_.y()  ;
                }
                _fSyncData = pos_.x();
                _bScanPosSync = true;
                break;
        case setup_DISPLAY_MODE_C_H:
        case setup_DISPLAY_MODE_CC_H:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_S_REF ] = pos_.x()  ;
                        _group.afCursor[setup_CURSOR_VPA_REF ] = pos_.y()  ;
                } else {
                        _group.afCursor[setup_CURSOR_S_MES ] = pos_.x()  ;
                        _group.afCursor[setup_CURSOR_VPA_MES ] = pos_.y()  ;
                }
                _fSyncData = pos_.x();
                _bScanPosSync = true;
                break;
        case setup_DISPLAY_MODE_C_V:
        case setup_DISPLAY_MODE_CC_V:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_S_REF ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_VPA_REF ] = pos_.x()  ;
                } else {
                        _group.afCursor[setup_CURSOR_S_MES ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_VPA_MES ] = pos_.x()  ;
                }
                _fSyncData = pos_.y();
                _bScanPosSync = true;
                break;
        case setup_DISPLAY_MODE_S_SOUNDPATH:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_U_REF ] = pos_.x()  ;
                } else {
                        _group.afCursor[setup_CURSOR_U_MES ] = pos_.x()  ;
                }
                break;
        case setup_DISPLAY_MODE_S_ATHUMIZ:
        case setup_DISPLAY_MODE_S_LINEAR:
                if(m_bCursorSel) {
                        _group.afCursor[setup_CURSOR_U_REF ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_I_REF ] = pos_.x()  ;
                } else {
                        _group.afCursor[setup_CURSOR_U_MES ] = pos_.y()  ;
                        _group.afCursor[setup_CURSOR_I_MES ] = pos_.x()  ;
                }
                break;
        default:
                break;
        };

        if(_pConfig->AppEvn.bSAxisCursorSync) {
                if(_bScanPosSync) {
                        ParameterProcess* _process = ParameterProcess::Instance();
                        _process->SetupScanPos(_fSyncData);
                        for(int i = 0; i < _pConfig->common.nGroupQty; i++) {
                                if(m_bCursorSel) {
                                        _pConfig->group[i].afCursor[setup_CURSOR_S_REF] = _fSyncData;
                                } else {
                                        _pConfig->group[i].afCursor[setup_CURSOR_S_MES] = _fSyncData;
                                }
                        }
                }
        }

        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidgetLeft->widget(_nGroupId);
        _pGroup->UpdateCursorValue();
        ProcessDisplay _process ;
        _process.UpdateAllViewCursorOfGroup(_nGroupId) ;
        RunDrawThreadOnce(true);
}

void MainWindow::on_actionNew_Config_triggered()
{
    ui->actionNew_Config->setCheckable(true);
    NewConfigure();
}

void MainWindow::on_actionOpen_triggered()
{
    ui->actionOpen->setDisabled(true);
    OpenFile();
}

void MainWindow::on_actionSave_triggered()
{
    SaveFile();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionNew_triggered()
{
    NewConfigure();
}

void MainWindow::on_actionOpenFile_triggered()
{
    OpenFile();
}

void MainWindow::on_actionSaveFile_triggered()
{
    SaveFile();
}

void MainWindow::on_actionRepoet_Add_One_Item_triggered()
{
    ReportAddOneItem();
}

void MainWindow::on_actionRepoet_Del_One_Item_triggered()
{
    ReportDelOneItem();
}

void MainWindow::on_actionRepoet_Setting_triggered()
{
    ReportSetting();
}

void MainWindow::on_actionSave_Report_triggered()
{
    ReportSave();
}

void MainWindow::on_actionTOFD_LW_Straitening_triggered()
{
    TofdDataPro(TOFD_PRO_STRAIGHT);
}

void MainWindow::on_actionTOFD_BW_Straitening_triggered()
{
    TofdDataPro(TOFD_PRO_BOTTOM);
}

void MainWindow::on_actionTOFD_LW_Removal_triggered()
{
    TofdDataPro(TOFD_PRO_DIFFERENC);
}

void MainWindow::on_actionTOFD_SAFT_triggered()
{
    TofdDataPro(TOFD_PRO_SAFT);
}

void MainWindow::on_actionTOFD_Repeal_triggered()
{
    TofdDataPro(TOFD_PRO_REPEAL);
}

void MainWindow::on_actionTOFD_Redo_triggered()
{
    TofdDataPro(TOFD_PRO_REDO);
}

void MainWindow::on_actionTOFD_Length_Measurement_triggered()
{
    DefectSign(DEFECT_SIGN_LENGTH);
}

void MainWindow::on_actionTOFD_Height_Measurement_triggered()
{
    DefectSign(DEFECT_SIGN_HEIGHT);
}

void MainWindow::on_actionTOFD_Depth_Measurement_triggered()
{
    DefectSign(DEFECT_SIGN_DEPTH);
}

void MainWindow::on_actionSave_Defect_triggered()
{
    DefectSign(DEFECT_SIGN_SAVE);
}

void MainWindow::on_actionLanguage_triggered()
{
    if(!UI_LanguageSwitch)
    {
      slot_actionChinese_triggered();
    }else{
      slot_actionEnglish_triggered();
    }
    UI_LanguageSwitch = !UI_LanguageSwitch;
}

void MainWindow::on_actionScreenShot_triggered()
{
    ScreenShot();
}

void MainWindow::slot_actionEnglish_triggered()
{
    ui->actionEnglish->setChecked(true);
    ui->actionChinese->setChecked(false);
    ui->actionLanguage->setIcon(QIcon(":/file/resource/toolbar/0-20.png"));
    translator->load(":/file/translator/phascan_view_english.qm");

    ui->retranslateUi(this);
    ui->Group1->retranslateUi();
    ui->ScanHardware->retranslateUi();
}

void MainWindow::slot_actionChinese_triggered()
{
    ui->actionChinese->setChecked(true);
    ui->actionEnglish->setChecked(false);
    ui->actionLanguage->setIcon(QIcon(":/file/resource/toolbar/0-22.png"));
    translator->load(":/file/translator/phascan_view_chinese.qm");

    ui->retranslateUi(this);
    ui->Group1->retranslateUi();
    ui->ScanHardware->retranslateUi();
}

/****************************************************************************
  Description: 窗口尺寸变化后  数据显示需要刷新
*****************************************************************************/
void MainWindow::slotDataViewResized(DopplerDataView* pView_)
{
        ProcessDisplay _process ;
        _process.UpdateDataViewFrame(pView_);
        _process.UpdateDataViewOverlay(pView_);
        pView_->UpdateDrawing();
}

