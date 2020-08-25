/*************************************
Copyright: Yshy
Date     : 2016-12-06
*************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog/DialogAddOneGroup.h"
#include "dialog/dialogmethodselect.h"
#include "threads/DataRefreshThread.h"
#include "InstrumentSettingWidget.h"
#include "DopplerConfigure.h"
#include "DopplerDataFileOperateor.h"
#include "dopplermergedatafileoperateor.h"
#include "gHeader.h"
#include "DopplerDataView.h"
#include "doppler_view/DopplerViewItems.h"
#include "ParameterProcess.h"
#include "ProcessDisplay.h"
#include "report/DopplerHtmlReport.h"
#include "dialog/DialogReportSetting.h"
#include "DopplerTofdOpp.h"
#include "doppler_view/DopplerLineItem.h"
#include "doppler_view/dopplercscanlinemark.h"
#include <QSplitterHandle>
#include <QMessageBox>
#include <QToolBox>
#include <QLabel>
#include <QFileDialog>
#include <QPixmap>
#include "dialog/DialogAbouVersion.h"
#include "remote_monitoring/RemoteMonitoring.h"
#include "remote_monitoring/assemblyremotesdialog.h"
#include "version.h"

int lastgroup = 0;
int currentgroup = 0; //-1表示全部组的那个tab

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_baseName("Report"),
    m_assemblyRemotes(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_ui();

    m_pGroupList.append(ui->Group1);
    m_pThreadDraw  = DataRefreshThread::Instance();
    translator = new QTranslator(this);
    qApp->installTranslator(translator);

    DopplerConfigure* pConfig = DopplerConfigure::Instance();
    m_currentLang = pConfig->AppEvn.eLanguage;

    if(m_currentLang == setup_LANG_ENGLISH) {
        slot_actionEnglish_triggered();

    }else if(m_currentLang == setup_LANG_CHINESE){
        slot_actionChinese_triggered();
    }
    SliderWidget = new QWidget(this);
    SliderWidget->setFixedWidth(300);
    SliderWidget->setFixedHeight(ui->toolBar->height()-4);
    sliderh = new QSlider(Qt::Horizontal);
    sliderh->setBaseSize(QSize(50,50));
    sliderh->setGeometry(20,0,260,ui->toolBar->height()-4);
    sliderh->setParent(SliderWidget);
    ui->toolBar->addWidget(SliderWidget);
    ui->actionAided_Analysis->setEnabled(false);

    scanSpin = new QDoubleSpinBox(this);
    scanSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    scanSpin->setFixedWidth(40);
    scanSpin->setDecimals(2);
    scanSpin->setEnabled(false);
    ui->toolBar->addWidget(scanSpin);

    indexSliderWidget = new QWidget(this);
    indexSliderWidget->setFixedWidth(300);
    indexSliderWidget->setFixedHeight(ui->toolBar->height()-4);
    indexSliderh = new QSlider(Qt::Horizontal);
    indexSliderh->setBaseSize(QSize(50,50));
    indexSliderh->setGeometry(20,0,260,ui->toolBar->height()-4);
    indexSliderh->setParent(indexSliderWidget);
    ui->toolBar->addWidget(indexSliderWidget);

    connect(ui->TabWidget_parameter, SIGNAL(signalLastTabBottonCliecked(Qt::MouseButton)), this, SLOT(slotsLeftTabButton(Qt::MouseButton)));
    connect(ui->TabWidget_parameter, SIGNAL(signalRightButtonDoubleClicked(int)), this, SLOT(slotLeftTabRightButtonDoubleClicked(int)));
    connect(ui->TabWidget_parameter, SIGNAL(currentChanged(int)), this, SLOT(slotCurrentGroupChanged(int)));
    connect(ui->TabWidget_display, SIGNAL(signalLastTabBottonCliecked(Qt::MouseButton)), this, SLOT(slotsRightTabButton(Qt::MouseButton)));
    connect(ui->TabWidget_display, SIGNAL(signalRightButtonDoubleClicked(int)), this, SLOT(slotRightTabRightButtonDoubleClicked(int)));    
    connect(ui->TabWidget_display, SIGNAL(currentChanged(int)), this, SLOT(slotCurrentDispChanged(int)));

    connect(ui->actionEnglish, SIGNAL(triggered()), this, SLOT(slot_actionEnglish_triggered()));
    connect(ui->actionChinese, SIGNAL(triggered()), this, SLOT(slot_actionChinese_triggered()));
    connect(sliderh,SIGNAL(valueChanged(int)),this,SLOT(slotSliderhChanged(int)));
    connect(indexSliderh, SIGNAL(valueChanged(int)), this, SLOT(slotIndexSliderHChanged(int)));
    connect(scanSpin, SIGNAL(valueChanged(double)), this, SLOT(slotScanSpinChanged(double)));

    //m_remoteMonitoring = new RemoteMonitoring(this);
    //connect(ui->actionConnect, SIGNAL(triggered()), m_remoteMonitoring, SLOT(connect_remote_monitor()));
    //connect(ui->actionDisconnect, SIGNAL(triggered()), m_remoteMonitoring, SLOT(disconnect_remote_monitor()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(connect_remote_monitor()));
    connect(ui->ScanHardware, SIGNAL(topcMergeCompareViewShow(bool)), this, SLOT(slotTopcMergeCompareViewShow(bool)));
    indexSliderh->hide();
    //indexSliderWidget->hide();
}

MainWindow::~MainWindow()
{
    if(m_pThreadDraw){
        m_pThreadDraw->terminate();
    }

    for(int i = 0; i < MAX_LIST_QTY; i++)
    {
        for(int j = 0; j < m_pViewList[i]->count(); j++ )
        {
            delete m_pViewList[i]->at(j);
        }
        delete m_pViewList[i];
    }

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    delete _pConfig;

    delete ui;
}

void MainWindow::init_ui()
{
    setMinimumSize(1024, 720);

    ui->TabWidget_display->SetHideAble(false);
    ui->actionNew_Config->setDisabled(true);
    ui->actionSave->setDisabled(true);
    ui->actionNew->setDisabled(true);
    ui->actionSaveFile->setDisabled(true);
    ui->actionSaveDisplay->setDisabled(true);
    ui->actionLoadDisplay->setDisabled(true);
    ui->actionStop_Analysis->setDisabled(true);
    // init display widget list
    for(int i = 0 ; i < MAX_LIST_QTY ; i++)
    {
        m_pViewList[i] = new QList<QWidget*>;
        m_pViewList[i]->clear();
    }

    CreateStatusBar();

    // tofd setting dialog
    m_iCurGroup  = 0;
    m_nLawIdSel  = 0;
    m_nAlloff	 = 0;
    m_bCursorSel = true;
    m_bParamBackMode = false;
    m_bDefectBackMode = false;
    SetDispTabText();

    m_fileName  = "";
    m_titleName = tr(VERSION);
    m_titleName.append(" : ");
    this->setWindowTitle(m_titleName + m_fileName);
}

void MainWindow::closeEvent (QCloseEvent* e)
{
    QMainWindow::closeEvent(e);
}

void MainWindow::resizeEvent(QResizeEvent* )
{
    int _nWidth  = ui->centralwidget->width();
    int _nHeight = ui->centralwidget->height();
    ui->splitter->setGeometry(0, 0, _nWidth, _nHeight);

}

void MainWindow::CreateStatusBar()
{
    QStatusBar* _status = ui->statusbar;
    QPalette pal = this->palette();

    pal.setColor(QPalette::Background, Qt::black);
    _status->setPalette(pal);
    _status->setAutoFillBackground(true);

    m_pStatusCell[0] = new QLabel(_status) ;
    m_pStatusCell[1] = new QLabel(_status) ;
    m_pStatusCell[2] = new QLabel(_status) ;

    _status->addWidget(m_pStatusCell[0]);
    _status->addWidget(m_pStatusCell[1]);
    _status->addWidget(m_pStatusCell[2], 1);
    UpdateStatusBarInfo();
}

// update status bar information when new *.data or *.cfg file is loaded
void MainWindow::UpdateStatusBarInfo()
{
    QPalette pal = this->palette();
    pal.setColor(QPalette::Foreground, Qt::green);

    ParameterProcess* _pOpp = ParameterProcess::Instance();

    m_BarInfo.nGroupQty = _pOpp->GetGroupQty();
    m_BarInfo.nLawQty   = _pOpp->GetTotalLawQty();
    m_BarInfo.nDataSize = _pOpp->GetTotalDataSize();

    QLabel* _pCell = m_pStatusCell[0];
    QString _str;
    _str.sprintf("Setting Info: Group Qty:[%d] Law Qty:[%d] Data Size:[%d]",
                 m_BarInfo.nGroupQty, m_BarInfo.nLawQty, m_BarInfo.nDataSize);
    _pCell->setPalette(pal);
    _pCell->setText(_str);
}


/****************************************************************************
  Description: 开启全部窗口(DopplerDataView)扫查数据的更新
*****************************************************************************/
void MainWindow::RunDrawThread()
{
    DataRefreshThread* _pThread = DataRefreshThread::Instance();
    _pThread->start();
}
/****************************************************************************
  Description: 全部窗口(DopplerDataView)扫查数据更新一次
*****************************************************************************/
void MainWindow::RunDrawThreadOnce(bool bUseDrawThread_)
{
    DataRefreshThread* _pThread = DataRefreshThread::Instance();

    if(bUseDrawThread_){
        _pThread->RunOnce(RUN_IN_DRAW_THREAD);
    }else{
         _pThread->RunOnce(RUN_IN_MAIN_THREAD);
    }
}

/****************************************************************************
  Description: 更新窗口(DopplerDataView)的全部设置
*****************************************************************************/
void MainWindow::UpdateAllDisplay()
{
    ProcessDisplay _process;
    _process.UpdateAllView();
}

void MainWindow::SetStatusBarMessageColor(int nId_, QColor& fgColor_, QColor& bgColor_)
{
    QLabel* _pCell = m_pStatusCell[nId_];
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, bgColor_);
    pal.setColor(QPalette::Foreground, fgColor_);
    _pCell->setAutoFillBackground(true);
    _pCell->setPalette(pal);
}

void MainWindow::SetStatusBarMessage(int nId_, QString& str_)
{
    QLabel* _pCell = m_pStatusCell[nId_];
    _pCell->setText(str_);
}

void MainWindow::slotsLeftTabButton(Qt::MouseButton btn_)
{
    //   return ;
    if(btn_ == Qt::LeftButton)
    {
        DialogAddOneGroup _dlg(this);

        if(_dlg.exec()){
            AddOneGroup();
        }
    }
}

void MainWindow::slotLeftTabRightButtonDoubleClicked(int)
{
    return;
}

void MainWindow::DestroyDisplayTab(int nId_)
{
    QList<QWidget*>* _pList = m_pViewList[nId_];

    for(int i = 0; i < _pList->count(); i++){
        delete _pList->at(i);
    }

    _pList->clear();

    QWidget* _pTmpWidget = ui->TabWidget_display->currentWidget();
    ui->TabWidget_display->removeTab(nId_);
    delete _pTmpWidget;
    // clear
    ui->TabWidget_display->setCurrentIndex(0);

    SetDispTabText();
}

void MainWindow::SetDispTabText()
{
    QString _str;
    int _nQty = ui->TabWidget_display->count();

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty;

    if(m_nAlloff)
        ui->TabWidget_display->setTabText(0, QString(tr("Com Groups")));

    for(int i = 0; i < _nGroupQty; i++){
        if(i + m_nAlloff < _nQty){
            _str.sprintf("Group %d", i+1);
            ui->TabWidget_display->setTabText(i + m_nAlloff, _str);
        }
    }

    if(_nQty > m_nAlloff + _nGroupQty + 1)
    {
        int _nCnt = 1;

        for(int i = m_nAlloff + _nGroupQty; i < _nQty; i++){
            _str.sprintf("Disp %d", _nCnt++);
            ui->TabWidget_display->setTabText(i, _str);
        }
    }

    ui->TabWidget_display->setTabText(_nQty - 1, QString(tr("")));
}

void MainWindow::slotRightTabRightButtonDoubleClicked(int)
{
    DopplerConfigure* _pConfig =  DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty;
    int _nQty      = ui->TabWidget_display->count();
    int _index     = ui->TabWidget_display->currentIndex();
//	if(_nQty <= 2)  return  ;
    int _nLimit = _nGroupQty + 1;
    if(_nGroupQty == 1)
            _nLimit = 1;
    if(_index < _nLimit)  return;
    _nLimit++;
    if(_nQty <= _nLimit)  return;

    QMessageBox messageBox(this);
    QAbstractButton* _pBtnYes;
    QAbstractButton* _pBtnNo;

    messageBox.setText(tr("Delete Current Display Table ?"));
    _pBtnYes = (QAbstractButton*)messageBox.addButton(tr("YES"), QMessageBox::ActionRole);
    _pBtnNo  = (QAbstractButton*)messageBox.addButton(tr("NO"), QMessageBox::ActionRole);

    messageBox.exec();
    if (messageBox.clickedButton() == _pBtnYes)
    {
        int _nIndex = ui->TabWidget_display->currentIndex();
        DestroyDisplayTab(_nIndex); // clear list
    }else if(messageBox.clickedButton() == _pBtnNo)
    {
    }
}

void MainWindow::DestroyAllDisplay()
{
    int _nQty = ui->TabWidget_display->count();

    for(int i = 0 ; i < _nQty - 1 ; i++){
        QList<QWidget*>* _pList = m_pViewList[i];

        for(int i = 0; i < _pList->count(); i++){
            delete _pList->at(i);
        }
        _pList->clear();
    }

    ui->TabWidget_display->setCurrentIndex(0);

    for(int i = 1; i <  _nQty - 1; i++){
        QWidget* _pTmpWidget = ui->TabWidget_display->widget(1);
        ui->TabWidget_display->removeTab(1);
        delete _pTmpWidget;
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
    return m_pViewList[ui->TabWidget_display->currentIndex()];
}

QList<QWidget*>* MainWindow::GetDisplayTableWidgetList(int nIndex_)
{
    return m_pViewList[nIndex_];
}

int  MainWindow::GetDisplayTableQty() const
{
    return ui->TabWidget_display->count();
}

int MainWindow::GetCurrentTabelIndex()
{
    return ui->TabWidget_display->currentIndex();
}

/****************************************************************************
  Description: 增加一个组参数 并用DopplerGroupTab显示出来
*****************************************************************************/
void MainWindow::AddOneGroup()
{
    DopplerConfigure* _pConfig =  DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty - 1;

    DopplerGroupTab* _pGroup = new DopplerGroupTab(this);
    _pGroup->SetGroupId(_nGroupQty);

    QString str(tr("Group "));
    QString str1;
    str1.sprintf("%d", _nGroupQty + 1);
    str += str1;
    QIcon icon(":/file/resource/main_menu/0-27.png");
    ui->TabWidget_parameter->insertTab(_nGroupQty, _pGroup, icon, str);
    ui->TabWidget_parameter->setCurrentIndex(_nGroupQty);
}

/****************************************************************************
  Description: 确定窗口焦点
*****************************************************************************/
void MainWindow::slotViewFrameButtonClicked(QWidget* pWidget_)
{
    SetSelectedDataView(pWidget_);
}

/****************************************************************************
  Description: 当删除和增加时 确定显示的组ID
*****************************************************************************/
void MainWindow::slotCurrentGroupChanged(int nIndex_)
{
    //qDebug()<<"index"<<nIndex_;
    static int _nOldIndex = 0;
    if(nIndex_ + 2 >= ui->TabWidget_parameter->count())  return;
    if(ui->TabWidget_parameter->count() < 4)  return;

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty;
    int _nCurRight = ui->TabWidget_display->currentIndex();

    if(_nCurRight < 0)		     _nCurRight = 0;
    if(_nCurRight >= MAX_LIST_QTY)   _nCurRight = MAX_LIST_QTY - 1;

    if(m_nAlloff && _nCurRight == 0) {
    } else {
        m_iCurGroup = nIndex_;
        if(m_iCurGroup >= _nGroupQty)  m_iCurGroup = 0;

        QList<QWidget*>* _list = m_pViewList[_nCurRight];
        DopplerDataView* _pDraw = NULL;

        if(_list->count() > 0) {
            _pDraw = (DopplerDataView*)_list->at(0);

            if(_pDraw->GetGroupId() != m_iCurGroup) {
                for(int i = m_nAlloff; i < ui->TabWidget_display->count(); i++) {
                    _list = m_pViewList[i];

                    if(_list->count() > 0) {
                        _pDraw = (DopplerDataView*)_list->at(0);

                        if(_pDraw->GetGroupId() == m_iCurGroup) {
                            ui->TabWidget_display->setCurrentIndex(i);
                            currentgroup = m_iCurGroup;
                            break;
                        }
                    }
                }
            }
        }
    }

    DopplerGroupTab* _pWidget = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nOldIndex);
    QToolBox* _toolBox = _pWidget->GetToolBox();

    if(_toolBox){
        int _nId = _toolBox->currentIndex();
        _pWidget = (DopplerGroupTab*)ui->TabWidget_parameter->widget(nIndex_);
        _nOldIndex = nIndex_;

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
    ui->TabWidget_parameter->setCurrentIndex(m_iCurGroup);
}

void MainWindow::slotCurrentDispChanged(int nIndex_)
{
    if(nIndex_ >= MAX_LIST_QTY)
    return;

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty;

    if(_nGroupQty > m_nAlloff){
        if(nIndex_ > 0){
            QList<QWidget*>* _list = m_pViewList[nIndex_];

            if(_list->count() > 0){
                DopplerDataView* _pDraw = (DopplerDataView*)_list->at(0);
                int _iGroup = _pDraw->GetGroupId();

                if(_iGroup < _nGroupQty){
                    m_iCurGroup = _iGroup;
                currentgroup = m_iCurGroup;
                    if(ui->TabWidget_parameter->currentIndex() < _nGroupQty){
                        ui->TabWidget_parameter->setCurrentIndex(m_iCurGroup);
                    }
                    InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidget_parameter->widget(_pConfig->common.nGroupQty);
                    _pScanner->UpdateScanPos();
                    UpdateSlider();

                }
            }

            ProcessDisplay _proDisplay;
            _proDisplay.UpdateAllView();
        }
        else if(m_nAlloff == 0)
        {
            currentgroup = 0;
        }
        else
            currentgroup = -1;
    }
    //------------------------------------------------------
    RunDrawThreadOnce(true);

}

void MainWindow::slotSliderhChanged(int value)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    SCANNER& _scanner = _pConfig->common.scanner ;
    if(_scanner.eScanEncoderType) {
            _scanner.fScanPos = _scanner.fScanStep * value + _scanner.fScanStart2;
    } else {
            _scanner.fScanPos =  value / _scanner.fPrf  + _scanner.fScanStart2;
    }
    scanSpin->setValue( _scanner.fScanPos);
    ProcessDisplay _proDisplay ;
    for(int i = 0; i < _pConfig->common.nGroupQty; i ++) {
         _proDisplay.UpdateAllViewCursorOfGroup(i);
    }
    InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidget_parameter->widget(_pConfig->common.nGroupQty);
    _pScanner->UpdateScanPos();
    RunDrawThreadOnce(true);
}

void MainWindow::slotIndexSliderHChanged(int value)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    SCANNER& _scanner  = _pConfig->common.scanner;
    _scanner.fIndexPos = _scanner.fIndexStep * value + _scanner.fIndexStart;
    ProcessDisplay _proDisplay ;
    for(int i = 0; i < _pConfig->common.nGroupQty; i++) {
         _proDisplay.UpdateAllViewCursorOfGroup(i);
    }
    InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidget_parameter->widget(_pConfig->common.nGroupQty);
    _pScanner->UpdateIndexPos();
    RunDrawThreadOnce(true);
}

void MainWindow::slotScanSpinChanged(double value)
{
//    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
//    SCANNER& _scanner  = _pConfig->common.scanner;
//    _scanner.fScanPos = value;
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nPos = _process->SAxisDistToIndex(value);
    sliderh->setValue(_nPos);
}

void MainWindow::SetSelectedDataView(QWidget* pWidget_)
{
    m_pCurrentDataView = pWidget_;
}

void MainWindow::updateAllTabwidgetSscanPos(int _nGroupId, int pos)
{
    if(m_nAlloff){
        for(int i = 0; i < ui->TabWidget_display->count(); i++){
            for(int j = 0; j < m_pViewList[i]->count(); j++){
                int tmpGroupID, tmpLawId, tmpDisplay;
                DopplerDataView* _pView = (DopplerDataView*)m_pViewList[i]->at(j);
                _pView->GetDataViewConfigure(&tmpGroupID ,  &tmpLawId ,  &tmpDisplay);
                if(_nGroupId == tmpGroupID){
                    for(int nQty = 0; nQty<_pView->GetSScanLawQty(); nQty++){
                        _pView->SetSScanLaw(nQty, pos);
                        //_pView->SetDataViewConfigure(_nGroupId,  pos,  tmpDisplay);
                    }
                }
                //slotDataViewResized(_pView);
            }
        }

    }
}

void MainWindow::updateCscanLawPos(int _nPos, int _nGroupId)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[_nGroupId];
    LAW_CONFIG _law = _group.law ;
    ParameterProcess* _process = ParameterProcess::Instance();
    float tmp = _process->CScanLineAngleToScanLineAngle(_nGroupId, _nPos);
    if(_law.eLawType == setup_LAW_TYPE_LINEAR || _law.eLawType == setup_LAW_TYPE_TFM)
        _group.afCursor[setup_CURSOR_C_ANGLE] = _group.afCursor[setup_CURSOR_LAW];
    else
        _group.afCursor[setup_CURSOR_C_ANGLE] = tmp;
}

float MainWindow::GetCurrentTabLinearScanMaxLineCount(int _nGroupId)
{
    float maxTmp = 0;
    for(int i = 0; i < m_pViewList[ui->TabWidget_display->currentIndex()]->count(); i++){
        int _nCurGroup, _nLawId, _nDisplay;
        DopplerDataView* _pView = (DopplerDataView*)m_pViewList[ui->TabWidget_display->currentIndex()]->at(i);
        _pView->GetDataViewConfigure( &_nCurGroup,  &_nLawId,  &_nDisplay);
        if(_nGroupId == _nCurGroup){
            setup_DISPLAY_MODE _eDisplay = (setup_DISPLAY_MODE)_pView->GetDataViewDrawType();
            if(_eDisplay >= setup_DISPLAY_MODE_S){
                qDebug("$$$$ %s[%d]: ScanQty %d, _eDisplay:%d, qty2:%d", __FUNCTION__, __LINE__, _pView->GetSScanLaw(0),
                       _eDisplay,  _pView->GetItemGroup()->GetLawMarkerLinesCount());
                maxTmp = _pView->GetItemGroup()->GetLawMarkerLinesCount();
                return maxTmp;
            }
        }
    }
    return maxTmp;
}


/****************************************************************************
  Description: 参数和数据加载时  更新参数窗口
*****************************************************************************/
void MainWindow::UpdateTableParameter()
{
    // disconnect for signal unpredicted
    disconnect(ui->TabWidget_parameter, SIGNAL(currentChanged(int)), 0, 0) ;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty;
    int _nTabQty   = ui->TabWidget_parameter->count();

    while(_nTabQty > 2)
    {
     //   QWidget* _pWidget = ui->TabWidget_parameter->widget(0);
        ui->TabWidget_parameter->removeTab(0);
    //    delete _pWidget;
        _nTabQty = ui->TabWidget_parameter->count();
    }
    qDeleteAll( m_pGroupList);
    m_pGroupList.clear();
    for(int i = 0; i < _nGroupQty; i++)
    {
        DopplerGroupTab *_pGroup = new DopplerGroupTab(ui->TabWidget_parameter);

        _pGroup->SetGroupId(i);
        _pGroup->LoadStandardFormConifg();

        QString str(tr("Group "));
        QString str1;
        str1.sprintf("%d", i + 1);
        str += str1;
        QIcon icon(":/file/resource/main_menu/0-27.png");
        connect(_pGroup, SIGNAL(thicknessChange(double)), this, SLOT(allThicknessChange(double)));
        ui->TabWidget_parameter->insertTab(i, _pGroup, icon, str);
        m_pGroupList.append(_pGroup);
    }

    ui->TabWidget_parameter->setCurrentIndex(0);
    connect(ui->TabWidget_parameter, SIGNAL(currentChanged(int)), this, SLOT(slotCurrentGroupChanged(int)));
}

void MainWindow::SetWndName()
{
    int _nQty = ui->TabWidget_parameter->count();
    if(_nQty < 3)  return;

    for(int i = 0; i< _nQty - 2; i++)
    {
        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidget_parameter->widget(i);
        _pGroup->SetWndName();
        _pGroup->UpdateGroupConfig();
    }
}

void MainWindow::UpdateCombinationDisplay(void)
{
    ui->TabWidget_display->setCurrentIndex(0);
    DopplerViewFrame* _pViewFrame = (DopplerViewFrame*)ui->TabWidget_display->currentWidget();
    _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_ALLGROUP);
    _pViewFrame->SetViewFrameId(0);
    _pViewFrame->update();

    SetWndName();
}

int MainWindow::SaveCurScreenshot(QString strPath_)
{
    QString _strPath = strPath_;
    QPixmap pixmap = QPixmap::grabWidget(ui->TabWidget_display->currentWidget());
    if(0 == pixmap.save(_strPath, "png"))
        return 0;
    else
        return 1;
}

/*!
  \brief 初始化工具栏上的扫查轴滑动条

*/
void MainWindow::initSlider()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    SCANNER& _scanner = _pConfig->common.scanner ;
    sliderh->blockSignals(true);
    sliderh->setMinimum(0);
//    sliderh->setSingleStep(_scanner.fScanStep);
//    sliderh->setPageStep(_scanner.fScanStep);
    sliderh->setSingleStep(1);
    sliderh->setPageStep(1);
    sliderh->setMaximum((_scanner.fScanStop - _scanner.fScanStart) / _scanner.fScanStep );
    sliderh->blockSignals(false);

    scanSpin->blockSignals(true);
    scanSpin->setMinimum( _scanner.fScanStart2);
    scanSpin->setMaximum( _scanner.fScanend);
    scanSpin->setSingleStep( _scanner.fScanStep);
    scanSpin->blockSignals(false);
    scanSpin->setEnabled(true);
}

/*!
  \brief 初始化工具栏上的步进轴滑动条，用于栅格扫查

*/
void MainWindow::initIndexSlider()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    SCANNER& _scanner = _pConfig->common.scanner;
    if( _scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
        indexSliderh->hide();
    }else{
        indexSliderh->blockSignals(true);
        indexSliderh->setMinimum(0);
        //indexSliderh->setSingleStep(_scanner.fIndexStep);
        indexSliderh->setSingleStep(1);
        indexSliderh->setMaximum((_scanner.fIndexStop - _scanner.fIndexStart) / _scanner.fIndexStep);
        indexSliderh->blockSignals(false);
        indexSliderh->show();
    }
}

/*!
  \brief 更新扫查轴滑动条

*/
void MainWindow::UpdateSlider()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    SCANNER& _scanner = _pConfig->common.scanner ;
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nPos = _process->SAxisDistToIndex(_scanner.fScanPos);
    sliderh->setValue(_nPos);
}

/*!
  \brief 更新步进轴滑动条，用于二维扫查

*/
void MainWindow::UpdateIndexSlider()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    SCANNER& _scanner = _pConfig->common.scanner ;
    ParameterProcess* _process = ParameterProcess::Instance();
    int _nPos = _process->TransforIndexPosToIndex(_scanner.fIndexPos);
    indexSliderh->setValue(_nPos);
}

void MainWindow::AidedAnalysisDone(bool status)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();

    //_pConfig->common.aidedAnalysis.aidedStatus  = false;
    int _nGroupId = _pConfig->common.aidedAnalysis.aidedGroupId;
//    menuBar()->setEnabled(true);
//    ui->toolBar->setEnabled(true);
//    ui->TabWidget_parameter->setEnabled(true);
    if(status){
        ProcessDisplay _proDispy;
        GROUP_CONFIG& _group = _pConfig->group[_nGroupId];
        int _nPos = _pConfig->common.aidedAnalysis.aidedBeamId;
        _group.afCursor[setup_CURSOR_LAW] = _nPos;
        updateCscanLawPos( _nPos, _nGroupId);
        InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidget_parameter->widget(_pConfig->common.nGroupQty);
        _pScanner->UpdateIndexBox();

        DopplerGroupTab* _pGroupTab = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);
        _pGroupTab->UpdateCurrentAngleCom();
        _pGroupTab->UpdateSizeingCurves();

        updateAllTabwidgetSscanPos(_nGroupId, _nPos);

        int _nTabIndex = ui->TabWidget_display->currentIndex();
        for(int i = 0; i < m_pViewList[_nTabIndex]->count(); i++){
            int tmpGroupID, tmpLawId, tmpDisplay;
            DopplerDataView* _pView = (DopplerDataView*)m_pViewList[_nTabIndex]->at(i);
            _pView->GetDataViewConfigure(&tmpGroupID ,  &tmpLawId ,  &tmpDisplay);
            if(_nGroupId == tmpGroupID){
                for(int nQty = 0; nQty<_pView->GetSScanLawQty(); nQty++){
                    _pView->SetSScanLaw(nQty, _nPos);
                }
            }
        }

        int _nLawId , _nDisplay;
        for(int _nTabIndex=0; _nTabIndex < ui->TabWidget_display->count(); _nTabIndex++)
        for(int i = 0; i < m_pViewList[_nTabIndex]->count(); i++){
            int _nCurGroup;
            DopplerDataView* _pView = (DopplerDataView*)m_pViewList[_nTabIndex]->at(i);
            _pView->GetDataViewConfigure( &_nCurGroup,  &_nLawId,  &_nDisplay);
//            if(_nDisplay < 4 && _nGroupId == _nCurGroup) {
//                _pView->SetDataViewConfigure(_nCurGroup,  _nPos,  _nDisplay);
//                _proDispy.UpdateAll(_pView);
//            }else if((_nDisplay >= 4 && _nDisplay <= 11) && _nGroupId == _nCurGroup){
//                _pView->SetDataViewConfigure(_nCurGroup,  _nPos,  _nDisplay);
//                _proDispy.UpdateAll(_pView);
//                _proDispy.UpdateDataViewTitle(_pView);
//                _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
//            }else{
//                _proDispy.UpdateDataViewTitle(_pView);
//                _proDispy.UpdateAll(_pView);
//            }
            if( _nGroupId == _nCurGroup){
                _pView->SetDataViewConfigure(_nCurGroup,  _nPos,  _nDisplay);
                _pView->UpdateMeasure();
                _proDispy.UpdateAll(_pView, false);
            }else{
                _proDispy.UpdateAll(_pView, false);
            }
        }
        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);
        _pGroup->UpdateCursorValue();
        _pGroup->UpdateDefectValue();
        _pGroup->UpdateTofdParam();

        _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
        RunDrawThreadOnce(true);
    }
}

void MainWindow::setAllTopcWidht(double value)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    for(int i = 0; i < m_pGroupList.size(); i++){
        if(_pConfig->group[i].eGroupMode <= setup_GROUP_MODE_PA){
            m_pGroupList[i]->setTopcWidthValue(value);
        }
    }
}

void MainWindow::UpdateTableDisplay()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    int _nGroupQty = _pConfig->common.nGroupQty;
    int _nTabQty   = ui->TabWidget_display->count();

    m_nAlloff = 1;
    if(_nGroupQty < 2)  m_nAlloff = 0;

    ui->toolBar->setEnabled(false);
    ui->TabWidget_parameter->setEnabled(false);
    ui->TabWidget_display->setEnabled(false);

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
            //ui->TabWidget_parameter->setCurrentIndex(i);
            ui->TabWidget_display->setCurrentIndex(i);
            m_iCurGroup = i-1;
            //sleep(2000);
            _pViewFrame = (DopplerViewFrame*)ui->TabWidget_display->currentWidget();
            _pViewFrame->SetViewFrameId(i);

            //int disp_mode = DopplerConfigure::getSetting(i-1,"DISP_MODE");
            int disp_mode = _pConfig->group[m_iCurGroup].DisplayMode;
            if(disp_mode < 0){
                disp_mode = (int)ProcessDisplay::DISP_S_AV;
            }
            if(_pConfig->group[m_iCurGroup].eGroupMode == setup_GROUP_MODE_PA) {
                _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_MODE(disp_mode));
            } else {
                _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_AH_BV);
            }

            sleep(600);
        }
        ui->TabWidget_display->setCurrentIndex(0);
    } else {
        ui->TabWidget_display->setCurrentIndex(0);
        m_iCurGroup = 0;
        _pViewFrame = (DopplerViewFrame*)ui->TabWidget_display->currentWidget();
        _pViewFrame->SetViewFrameId(0);

        //int disp_mode = DopplerConfigure::getSetting(0,"DISP_MODE");
        int disp_mode = _pConfig->group[0].DisplayMode;
        if(disp_mode < 0){
            disp_mode = (int)ProcessDisplay::DISP_S_AV;
        }
        if(_pConfig->group[m_iCurGroup].eGroupMode == setup_GROUP_MODE_PA) {
            _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_MODE(disp_mode));
        } else {
            _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_AH_BV);
        }
    }
    ui->TabWidget_parameter->setEnabled(true);
    ui->TabWidget_display->setEnabled(true);
    ui->actionSaveDisplay->setEnabled(true);
    ui->actionLoadDisplay->setEnabled(true);
    ui->toolBar->setEnabled(true);
    SetDispTabText();
}

void MainWindow::InsertRightTab()
{
    int _nIndex = ui->TabWidget_display->count();
    if(_nIndex > 9) return; // max group number is 8
    DopplerViewFrame* _pViewFrame = new DopplerViewFrame(ui->TabWidget_display);
    QString _str ;
    _str.sprintf("DISP %d", _nIndex);
    ui->TabWidget_display->insertTab(_nIndex -1, _pViewFrame, _str);
    ui->TabWidget_display->setCurrentIndex(_nIndex -1);
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
        DopplerConfigure* _pConfig = DopplerConfigure::Instance();
        _pConfig->InitCommonConfig();
        UpdateTableParameter();

        m_fileName = tr("New Setting");
        this->setWindowTitle(m_titleName + m_fileName);
    }

    UpdateStatusBarInfo();
}

/*!
  \brief 界面点击"打开文件"的响应函数

*/
void MainWindow::OpenFile()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QStringList fileNameLst = QFileDialog::getOpenFileNames(this,
                            "Open File Dialog",
                            QString::fromLocal8Bit(_pConfig->AppEvn.strDataFilePath, 256),
                            "Doppler Files(*.cfg *.data)");

    if (fileNameLst.isEmpty()) return ;
    if (1 != fileNameLst.size()) {
        fileMergePro(fileNameLst);
    } else {
        OpenFilePro(fileNameLst.at(0));
    }
}

void MainWindow::OpenFilePro(QString strFileName_)
{
    if(strFileName_.isEmpty())  return;
    QString suffix = strFileName_.section('.', -1);

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();

    DestroyAllDisplay();

    int _ret  = 0;
    if( suffix == "cfg"){
        _ret = _pConfig->OpenConfig(strFileName_);
    }else if( suffix == "data"){
        _ret = _pConfig->OpenData(strFileName_);
    }

    if(!_ret)
    {
        _pConfig->ResetShadowData();
        _pConfig->initScanPos();
        UpdateTableParameter();
        UpdateStatusBarInfo();
        UpdateTableDisplay();
        initSlider();
        initIndexSlider();
        sliderh->setValue(0);
        scanSpin->setValue(scanSpin->minimum());
        indexSliderh->setValue(0);
        m_iCurGroup = 0;
        ui->actionAided_Analysis->setEnabled(true);

    }else{
        QMessageBox::warning(this, tr("Illegal Datafile"), tr("This is illegal datafile. Please Choose another one."));
        return;
    }
    if(m_nAlloff)
    {
        lastgroup = -1;
        currentgroup = -1;
    }
    else
    {
        lastgroup = 0;
        currentgroup = 0;
    }
    m_fileName = strFileName_;
    QFileInfo fi(strFileName_);
    m_baseName = fi.baseName();
    DopplerHtmlReport* _pReport = _pConfig->GetReportOpp();
    _pReport->set_reportName(m_baseName);
    this->setWindowTitle(m_titleName + m_fileName);



//    ParameterProcess* _process = ParameterProcess::Instance();
//    WDATA *ppdata = _process->GetShadowDataPointer();
//    int nPointQty  = _process->GetGroupPointQty(0);
//    for(int i = 0; i < 10; i++){
//        WDATA *pdata  =  _process->GetDataAbsolutePosPointer( 0, i, 0, ppdata);
//        pdata += nPointQty;
//        int *p = (int *)pdata;
//        qDebug()<<"pdata"<<p[4];
//    }
}

void MainWindow::fileMergePro(QStringList &fileNameLst)
{
    int count = fileNameLst.size();
    if (fileNameLst.isEmpty() || 1 == count) return ;
    for (int i = 0; i < count; i ++) {
        QString strFileName_ = fileNameLst.at(i);
        QString suffix = strFileName_.section('.', -1);
        if (suffix != "data") return ;
    }

    DestroyAllDisplay();

    m_fileName.clear();
    for (int i = 0; i < count; i ++) {
        QString strFileName_ = fileNameLst.at(i);
        QFileInfo _fi = QFileInfo(strFileName_);
        if (0 == i) {
            QString path = _fi.filePath();
            m_fileName.append(path);
        } else {
            QString fName = _fi.fileName();
            m_fileName.append(fName);
        }

    }
    QString suffStr(".data");
    m_fileName.replace(suffStr, QString("_"));
    m_fileName.chop(1);
    m_fileName.append(suffStr);
    this->setWindowTitle(m_titleName + m_fileName);

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    //将多个.data数据合并为一组数据
    DopplerMergeDataFileOperateor mergeDataOp;
    int _ret = mergeDataOp.LoadData(fileNameLst);
    if (0 != _ret) return ;
    _ret = mergeDataOp.MergeFile();
    if (0 != _ret) return ;
    mergeDataOp.WriteDataToFile(m_fileName);
    if (!_ret) {
        _ret  = _pConfig->OpenData(m_fileName);
        if(!_ret)
        {
            _pConfig->ResetShadowData();
            UpdateTableParameter();
            UpdateStatusBarInfo();
            UpdateTableDisplay();
            m_iCurGroup = 0;
        }
    }

    lastgroup = 0;
    currentgroup = 0;
}

void MainWindow::SaveFile()
{
    QString _strFileName =  QFileDialog::getSaveFileName(this,
                                                         "Save File Dialog",
                                                         "data",
                                                         "Doppler Files(*.cfg)");
    if(_strFileName.isEmpty())  return;

    m_fileName = _strFileName;
    this->setWindowTitle(m_titleName + m_fileName);

    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->SaveConfig(_strFileName);
}

void MainWindow::ScreenShot()
{
    static int _nScreenShotId = 0;
    QString _strPath;
    _strPath.sprintf("ScreenShot%04d.png", _nScreenShotId);
    QPixmap pixmap = QPixmap::grabWidget(this);
    QString _strTemp = QDir::currentPath() + "/" + _strPath;

    do{
        _strPath.sprintf("ScreenShot%04d.png", _nScreenShotId++);
        _strTemp = QDir::currentPath() + "/" + _strPath;
    }
    while(QFile(_strTemp).exists());

    if(pixmap.save(QDir::currentPath() + "/" + _strPath, "png"))
    {
    QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
    clipboard->setPixmap(pixmap);
    QMessageBox::information(this,tr("prompt"),tr("save in ")+QDir::currentPath()+"/"+_strPath);
    }
}

/****************************************************************************
  Description: 在报告中加入一条新数据记录
*****************************************************************************/
void MainWindow::ReportAddOneItem()
{
    static int _nPixId = 0;
    int _nIndex = ui->TabWidget_display->currentIndex();
    if(!m_pViewList[_nIndex]->count()) return;

    int _nGroup = m_iCurGroup;
    DopplerConfigure*  _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[_nGroup];
    int _nLawId = _group.afCursor[setup_CURSOR_LAW];

    DopplerHtmlReport* _pReport = _pConfig->GetReportOpp();
    ReportValueItem _value;

    _value.fPos     =  _pConfig->common.scanner.fScanPos;
    _value.nGroupId = _nGroup;
    _value.nLawId   = _nLawId;
    int* _pMeasure  = _group.aeMeasureType;
    int _nQty = 0;

    for(int i = 0; i < setup_MAX_MEASURE_QTY; i++)
    {
        if(_pMeasure[i]){
            _value.szValue[_nQty] = CalcMeasurement::GetMeasureValue(_nGroup, _nLawId, (FEILD_VALUE_INDEX)_pMeasure[i]);
            _value.szField[_nQty] = CalcMeasurement::GetMeasureString(_nGroup , (FEILD_VALUE_INDEX)_pMeasure[i]);
            _value.szFieldUnit[_nQty] = CalcMeasurement::GetMeasureUnit((FEILD_VALUE_INDEX)_pMeasure[i]) ;
            _nQty++;
        }
    }

    for(int i = _nQty; i < setup_MAX_MEASURE_QTY; i ++) {
        _value.szValue[i] = QString("-");
        _value.szField[i] = QString("-");
        _value.szFieldUnit[i] = QString("-");
    }
    QString _strPath;
    _strPath.sprintf("img%04d.png", _nPixId++);
    _value.szPixmap = _strPath;

    _pReport->AddOneValueItem(&_value);
    if(1 == SaveCurScreenshot(_strPath))
    QMessageBox::information(this,tr("prompt"),tr("increase success!"));
}

/****************************************************************************
  Description: 在报告中删除一条数据记录
*****************************************************************************/
void MainWindow::ReportDelOneItem()
{
    DopplerConfigure* _pConfig  = DopplerConfigure::Instance();
    DopplerHtmlReport* _pReport = _pConfig->GetReportOpp();
    if(0 == _pReport->DelOneValueItem())
        QMessageBox::information(this,tr("prompt"),tr("delete success!"));

}

/****************************************************************************
  Description: 设置报告格式
*****************************************************************************/
void MainWindow::ReportSetting()
{
    DialogReportSetting _dialog;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    DopplerHtmlReport* _pReport = _pConfig->GetReportOpp();
    ReportInfo* _pInfo = _pReport->GetReportInfo();
    _dialog.SetReportInfo(_pInfo);
    _dialog.SetRepotName(m_baseName);

    if(_dialog.exec())
    {
        _pInfo = _dialog.GetRePortInfo();
        _pReport->SetReportInfo(_pInfo);
    }
}

/****************************************************************************
  Description: 报告保存
*****************************************************************************/
void MainWindow::ReportSave()
{
    DopplerConfigure* _pConfig  = DopplerConfigure::Instance();
    DopplerHtmlReport* _pReport = _pConfig->GetReportOpp();
    _pReport->SaveReport();
}

void MainWindow::TofdDataPro(TOFD_PRO_STATUS proSt_)
{
    DopplerTofdOpp opp;

    if(proSt_ == TOFD_PRO_REPEAL){
        opp.TofdDataProRepeal(m_iCurGroup);
    }else if(proSt_ == TOFD_PRO_REDO){
        opp.TofdDataProRedo(m_iCurGroup);
    }else{
        if(opp.TofdDragProStart(m_iCurGroup, proSt_) < 0){
            opp.TofdDataProStart(m_iCurGroup, proSt_, NULL);
            opp.TofdDataToShadow(m_iCurGroup);
        }
    }

    RunDrawThreadOnce(false);
}

void MainWindow::DefectSign(DEFECT_SIGN_TYPE signType_)
{
    DopplerConfigure* _pConfig =  DopplerConfigure::Instance();
    int _ret = _pConfig->DefectSign(m_iCurGroup, signType_);

    if(_ret >= 0) {
        if(_ret == 3) {
            ProcessDisplay _process;
            //GROUP_CONFIG* _pGroup = &_pConfig->group[m_iCurGroup];
            DopplerGroupTab* _pLeftGroup = (DopplerGroupTab*)ui->TabWidget_parameter->widget(m_iCurGroup);
            _pLeftGroup->UpdateDefectBox();
            _pLeftGroup->UpdateDefectValue();

            int _index = _pConfig->m_dfParam[m_iCurGroup].index;
            //bool _bTmp = _pGroup->bShowDefect;
            //_pGroup->bShowDefect = false;
            _pConfig->m_nCutBmpNo[m_iCurGroup] = _index+1;
            _process.UpdateAllViewCursorOfGroup(m_iCurGroup);
            //RunDrawThreadOnce(true);
            sleep(400);

            DEFECT_INFO* _pDfInfo = _pConfig->GetDefectPointer(m_iCurGroup, _index);
            QString _strPath = _pConfig->m_szDefectPathName + QString(tr("/")) + QString(tr(_pDfInfo->srtImageName)) + QString(tr(".png"));
            if(0 == SaveCurScreenshot(_strPath))
                QMessageBox::information(this,tr("prompt"),tr("The defect was saved failed!"));
            else
                QMessageBox::information(this,tr("prompt"),tr("The defect was saved successfully!"));
            sleep(200);
            //_pGroup->bShowDefect = _bTmp;
            _pConfig->m_nCutBmpNo[m_iCurGroup] = 0;
            _process.UpdateAllViewCursorOfGroup(m_iCurGroup);
        }

        RunDrawThreadOnce(false);
    }
}

/****************************************************************************
  Description: 参数设置窗口与数据显示窗口同步   主要是光标
*****************************************************************************/
void MainWindow::slotItemMoved(DopplerDataView* pView_, DopplerGraphicsItem* pItem_)
{
    int _nGroupId , _nLawId , _nDisplay;
    int _nItemType = pItem_->GetItemType();

    pView_->GetDataViewConfigure(&_nGroupId,  &_nLawId,  &_nDisplay);

    ParameterProcess* _process = ParameterProcess::Instance();
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[_nGroupId];
    int _nGroupQty = _pConfig->common.nGroupQty;

    ProcessDisplay _proDispy;
    int _nTabIndex = ui->TabWidget_display->currentIndex();

    switch (_nItemType){
    case DOPPLER_GRAPHICS_ITEM_LAW_MARKER:
    {
        int _nId = ((DopplerLawMarker*)pItem_)->GetMarkerId();
        int _nPos = ((DopplerLawMarker*)pItem_)->GetMarkerPos(_nId);
        //int _nQty = ((DopplerLawMarker*)pItem_)->GetMarkerQty();

        m_nLawIdSel = _nId;
        _group.afCursor[setup_CURSOR_LAW] = _nPos;
        //qDebug()<<"_nId"<<_nId<<"_nPos"<<_nPos;
        updateCscanLawPos(_nPos, _nGroupId);
        //int paraIndex = ui->TabWidget_parameter->currentIndex();
        //qDebug()<<"_paraIndex"<<paraIndex;


        DopplerGroupTab* _pGroupTab = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);
        _pGroupTab->UpdateCurrentAngleCom();
        _pGroupTab->UpdateSizeingCurves();
        //ui->TabWidget_parameter->setCurrentIndex(paraIndex);
        InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidget_parameter->widget(_pConfig->common.nGroupQty);
        _pScanner->UpdateIndexBox();

        updateAllTabwidgetSscanPos(_nGroupId, _nPos);

        for(_nTabIndex=0; _nTabIndex < ui->TabWidget_display->count(); _nTabIndex++)
        for(int i = 0; i < m_pViewList[_nTabIndex]->count(); i++)
        {
            int _nCurGroup;

            DopplerDataView* _pView = (DopplerDataView*)m_pViewList[_nTabIndex]->at(i);
            _pView->GetDataViewConfigure( &_nCurGroup,  &_nLawId,  &_nDisplay);

            if(_nDisplay < 4 && _nGroupId == _nCurGroup) {  // A SCAN  & B SCAN
                if(_nId == _pView->GetLawIdentify()) {
                    _pView->SetDataViewConfigure(_nCurGroup,  _nPos,  _nDisplay);
                    _proDispy.UpdateAll(_pView, false);
                }
            } else if( (_nDisplay >= 4 && _nDisplay < 8) && _nGroupId == _nCurGroup) {
                _pView->SetDataViewConfigure(_nCurGroup,  _nPos,  _nDisplay);
                _proDispy.UpdateDataViewTitle(_pView);
                _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
            } else {
                _proDispy.UpdateDataViewTitle(_pView);
            }
        }
        RunDrawThreadOnce(true);
    }
    break;
    case DOPPLER_GRAPHICS_ITEM_CURSOR:
    {
        int tmp;
        float maxTmp;
        setup_DISPLAY_MODE _eMode = (setup_DISPLAY_MODE)_nDisplay;
        Q_UNUSED(_eMode);

        QRectF _rect = pItem_->GetItemGeometryReal();
        int _nItemId = pItem_->GetItemId();

        if(_nItemId < 0 || _nItemId > setup_CURSOR_MAX)   break;

        float _fCursor = 0;

        if(DopplerLineItem::LINE_HORIZENTAL == ((DopplerLineItem*)pItem_)->GetLineType()) {
            _fCursor = _rect.top();
        } else {
            _fCursor = _rect.left();
        }
        if(_isnan(_fCursor))
        {
            return;
        }
        _group.afCursor[_nItemId] = _fCursor;
//        qDebug()<<"aass"<<_fCursor;
//        qDebug("xxx== _nItemId:%d, _fCursor:%.2f, line_direction type:%d, _nLawId:%d", _nItemId, _fCursor,
//               ((DopplerLineItem*)pItem_)->GetLineType(), _nLawId);
        if(_nItemId == setup_CURSOR_C_ANGLE){
            if(DopplerLineItem::LINE_HORIZENTAL == ((DopplerCScanLineMark*)pItem_)->GetLineType()){
                _fCursor = _rect.top();
            }else{
                _fCursor = _rect.left();
            }
            if(_pConfig->common.scanner.eScanType == setup_SCAN_TYPE_ONE_LINE){
                maxTmp = GetCurrentTabLinearScanMaxLineCount(_nGroupId);

                if(_isnan(_fCursor))
                {
                    return;
                }

                LAW_CONFIG _law = _group.law ;
                if((_law.eLawType == setup_LAW_TYPE_LINEAR || _law.eLawType == setup_LAW_TYPE_TFM)&& _law.eFocalType == 1){
                    if(_fCursor > maxTmp){
                        _fCursor = maxTmp;
                        _group.afCursor[_nItemId] = _fCursor;
                    }else if(_fCursor < 0){
                        _fCursor = 0;
                        _group.afCursor[_nItemId] = _fCursor;
                    }
                }

                if(_law.eLawType == setup_LAW_TYPE_LINEAR || _law.eLawType == setup_LAW_TYPE_TFM){
                    tmp = _group.afCursor[setup_CURSOR_C_ANGLE];
                    _group.afCursor[setup_CURSOR_LAW] = tmp;
                }else{
                    tmp = _process->SCanAngleToCScanLineAngle(_nGroupId, _fCursor);
                    _group.afCursor[setup_CURSOR_LAW] = tmp;
                }
                qDebug("(tmp):%.2f,_fCursor:%.2f, rect.x:%.2f, rect.y:%.2f",
                       _group.afCursor[setup_CURSOR_LAW], _fCursor, _rect.x(), _rect.y());
            }else{
                float indexPos;
                int lawPos;
                _process->GetRasterIndexAndLaw(_nGroupId, _fCursor, &indexPos, &lawPos);
                qDebug()<<"_fCursor"<<_fCursor<<"indexPos"<<indexPos<<"lawPos"<<lawPos;
                _group.afCursor[setup_CURSOR_C_ANGLE] = lawPos;
                _group.afCursor[setup_CURSOR_LAW] = lawPos;
                tmp = lawPos;
                if( _pConfig->common.scanner.fIndexPos != indexPos){
                    _pConfig->common.scanner.fIndexPos = indexPos;
                    int pos_ = _process->TransforIndexPosToIndex(indexPos);
                    indexSliderh->blockSignals(true);
                    indexSliderh->setValue(pos_);
                    indexSliderh->blockSignals(false);
                }

            }

            DopplerGroupTab* _pGroupTab = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);

            _pGroupTab->UpdateCurrentAngleCom();
            _pGroupTab->UpdateSizeingCurves();


            for(int i = 0; i < m_pViewList[_nTabIndex]->count(); i++)
            {
                int tmpGroupID, tmpLawId, tmpDisplay;
                DopplerDataView* _pView = (DopplerDataView*)m_pViewList[_nTabIndex]->at(i);
                _pView->GetDataViewConfigure(&tmpGroupID ,  &tmpLawId ,  &tmpDisplay);
                if(_nGroupId == tmpGroupID){
                    qDebug("%s[%d]: LawQty:%d, tmp:%d", __FUNCTION__, __LINE__, _pView->GetSScanLawQty(), tmp);
                    for(int nQty = 0; nQty<_pView->GetSScanLawQty(); nQty++){
                        _pView->SetSScanLaw(nQty, tmp);
                    }
                }

            }

            updateAllTabwidgetSscanPos(_nGroupId, tmp);

            for(_nTabIndex=0; _nTabIndex < ui->TabWidget_display->count(); _nTabIndex++)
            for(int i = 0; i < m_pViewList[_nTabIndex]->count(); i++)
            {
                int _nCurGroup;

                DopplerDataView* _pView = (DopplerDataView*)m_pViewList[_nTabIndex]->at(i);
                _pView->GetDataViewConfigure( &_nCurGroup,  &_nLawId,  &_nDisplay);

                if(_nDisplay < 4 && _nGroupId == _nCurGroup) {  // A SCAN  & B SCAN
                        _pView->SetDataViewConfigure(_nCurGroup,  tmp,  _nDisplay);
                        _proDispy.UpdateAll(_pView, false);

                } else if(_nDisplay < 8  && _nGroupId == _nCurGroup) {
                    _pView->SetDataViewConfigure(_nCurGroup,  tmp,  _nDisplay);
                    _proDispy.UpdateDataViewTitle(_pView);
                    _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
                } else {
                    _proDispy.UpdateDataViewTitle(_pView);
                }
            }
        }
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
//        qDebug("*** %s[%d], _fCursor:%.2f, _nItemId:%d, _nDisplay:%d",
//               __FUNCTION__, __LINE__, _fCursor, _nItemId, _nDisplay);

        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);
        _pGroup->UpdateCursorValue();
        _pGroup->UpdateDefectValue();
        _pGroup->UpdateTofdParam();

        _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
        RunDrawThreadOnce(true);
    }
    break;
    //case OVERLAYS_THICKNESS:
    //case OVERLAYS_WELD:
    case DOPPLER_GRAPHICS_ITEM_SCAN:
    {
        QRectF _rect = pItem_->GetItemGeometryReal();
        float _fCursorPos;

        if(DopplerLineItem::LINE_HORIZENTAL == ((DopplerLineItem*)pItem_)->GetLineType()) {
            _fCursorPos = _rect.top();
        } else {
            _fCursorPos = _rect.left();
        }
        if(_isnan(_fCursorPos))
        {
            return;
        }
        InstrumentSettingWidget* _pScanner = (InstrumentSettingWidget*)ui->TabWidget_parameter->widget(_pConfig->common.nGroupQty);
        _pScanner->UpdateScanPos();
        UpdateSlider();
        if(_pConfig->AppEvn.bSAxisCursorSync) {
            pView_->GetDataViewConfigure(&_nGroupId,  &_nLawId,  &_nDisplay);

            for(int i = 0; i < _nGroupQty; i++) {
                if(m_bCursorSel) {
                    _pConfig->group[i].afCursor[setup_CURSOR_S_REF] = _fCursorPos;
                } else {
                    _pConfig->group[i].afCursor[setup_CURSOR_S_MES] = _fCursorPos;
                }
            }
        }

        DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);
        _pGroup->UpdateCursorValue();
        _proDispy.UpdateAllViewCursorOfGroup(_nGroupId);
        _process->SetupScanPos(_fCursorPos);

        RunDrawThreadOnce(true);
    }
    break;

    default: break;
    }
}

void MainWindow::slotDataViewMouseDoubleClicked(DopplerDataView* pView_, QPointF pos_)
{
    m_bCursorSel = !m_bCursorSel;

    int _nGroupId, _nLawId, _nDisplay;
    pView_->GetDataViewConfigure(&_nGroupId, &_nLawId, &_nDisplay);

    setup_DISPLAY_MODE _eMode  = (setup_DISPLAY_MODE)_nDisplay;
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& _group = _pConfig->group[_nGroupId];

    bool _bScanPosSync = false;
    float _fSyncData = 0;

    switch(_eMode){
    case setup_DISPLAY_MODE_A_H:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_A_REF] = pos_.y();
            _group.afCursor[setup_CURSOR_U_REF] = pos_.x();
        } else {
            _group.afCursor[setup_CURSOR_A_MES] = pos_.y();
            _group.afCursor[setup_CURSOR_U_MES] = pos_.x();
        }
        break;
    case setup_DISPLAY_MODE_A_V:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_A_REF] = pos_.x();
            _group.afCursor[setup_CURSOR_U_REF] = pos_.y();
        } else {
            _group.afCursor[setup_CURSOR_A_MES] = pos_.x();
            _group.afCursor[setup_CURSOR_U_MES] = pos_.y();
        }
        break;
    case setup_DISPLAY_MODE_B_H:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_S_REF] = pos_.y();
            _group.afCursor[setup_CURSOR_U_REF] = pos_.x();
        } else {
            _group.afCursor[setup_CURSOR_S_MES] = pos_.y();
            _group.afCursor[setup_CURSOR_U_MES] = pos_.x();
        }

        _fSyncData = pos_.y();
        _bScanPosSync = true;
        break;
    case setup_DISPLAY_MODE_B_V:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_S_REF] = pos_.x();
            _group.afCursor[setup_CURSOR_U_REF] = pos_.y();
        } else {
            _group.afCursor[setup_CURSOR_S_MES] = pos_.x();
            _group.afCursor[setup_CURSOR_U_MES] = pos_.y();
        }

        _fSyncData = pos_.x();
        _bScanPosSync = true;
        break;
    case setup_DISPLAY_MODE_C_H:
    case setup_DISPLAY_MODE_CC_H:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_S_REF] = pos_.x();
            _group.afCursor[setup_CURSOR_VPA_REF] = pos_.y();
        } else {
            _group.afCursor[setup_CURSOR_S_MES] = pos_.x();
            _group.afCursor[setup_CURSOR_VPA_MES] = pos_.y();
        }
        _fSyncData = pos_.x();
        _bScanPosSync = true;
        break;
    case setup_DISPLAY_MODE_C_V:
    case setup_DISPLAY_MODE_CC_V:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_S_REF] = pos_.y();
            _group.afCursor[setup_CURSOR_VPA_REF] = pos_.x();
        } else {
            _group.afCursor[setup_CURSOR_S_MES] = pos_.y();
            _group.afCursor[setup_CURSOR_VPA_MES] = pos_.x();
        }
        _fSyncData = pos_.y();
        _bScanPosSync = true;
        break;
    case setup_DISPLAY_MODE_S_SOUNDPATH:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_U_REF] = pos_.x();
        } else {
            _group.afCursor[setup_CURSOR_U_MES] = pos_.x();
        }
        break;
    case setup_DISPLAY_MODE_S_ATHUMIZ:
    case setup_DISPLAY_MODE_S_LINEAR:
        if(m_bCursorSel) {
            _group.afCursor[setup_CURSOR_U_REF] = pos_.y();
            _group.afCursor[setup_CURSOR_I_REF] = pos_.x();
        } else {
            _group.afCursor[setup_CURSOR_U_MES] = pos_.y();
            _group.afCursor[setup_CURSOR_I_MES] = pos_.x();
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

    DopplerGroupTab* _pGroup = (DopplerGroupTab*)ui->TabWidget_parameter->widget(_nGroupId);
    _pGroup->UpdateCursorValue();
    ProcessDisplay _process;
    _process.UpdateAllViewCursorOfGroup(_nGroupId);
    RunDrawThreadOnce(true);
}

void MainWindow::slotTopcMergeCompareViewShow( bool status)
{
    ui->TabWidget_display->setCurrentIndex(0);
    sleep(600);
    DopplerViewFrame* _pViewFrame = (DopplerViewFrame*)ui->TabWidget_display->currentWidget();
    if(status){
        _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_TOPCMERGECOMPARE);
    }else{
        _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_ALLGROUP);
    }
    _pViewFrame->SetViewFrameId(0);
    _pViewFrame->update();

    SetWndName();
}

void MainWindow::connect_remote_monitor()
{
    if(m_assemblyRemotes == nullptr){
        m_assemblyRemotes = new assemblyRemotesDialog(this);
    }
    m_assemblyRemotes->exec();
}

void MainWindow::allThicknessChange(double thickness)
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    for(int i = 0; i < _pConfig->common.nGroupQty; i ++){
        _pConfig->group[i].part.afSize[0] = thickness;
        m_pGroupList[i]->setThicknessValue(thickness);
    }
    ProcessDisplay _proDisplay ;
    for(int i = 0; i < _pConfig->common.nGroupQty; i ++) {
         _proDisplay.UpdateAllViewOverlayOfGroup(i);
    }
    RunDrawThreadOnce(true);
}

void MainWindow::on_actionNew_Config_triggered()
{
    ui->actionNew_Config->setCheckable(true);
    NewConfigure();
}

void MainWindow::on_actionOpen_triggered()
{
    ui->actionOpen->setCheckable(true);
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

void MainWindow::on_actionReport_PreView_triggered()
{
    ReportSave();
}

void MainWindow::on_actionSaveReport_triggered()
{
    ReportSave();
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

void MainWindow::on_actionReport_Add_One_Item_triggered()
{
    ReportAddOneItem();
}

void MainWindow::on_actionReport_Del_One_Item_triggered()
{
    ReportDelOneItem();
}

void MainWindow::on_actionReport_Setting_triggered()
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
    //DopplerConfigure* pConfig = DopplerConfigure::Instance();

    if(m_currentLang == setup_LANG_ENGLISH) {
        //pConfig->AppEvn.eLanguage = setup_LANG_CHINESE;
        slot_actionChinese_triggered();
    }else if(m_currentLang == setup_LANG_CHINESE){
        //pConfig->AppEvn.eLanguage = setup_LANG_ENGLISH;
        slot_actionEnglish_triggered();
    }

    //m_currentLang = pConfig->AppEvn.eLanguage;
}

void MainWindow::on_actionScreenShot_triggered()
{
    ScreenShot();
}

void MainWindow::on_actionSaveDisplay_triggered()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QString strDirPath = QCoreApplication::applicationDirPath() + "/init/config/";
    QString strFileName = QFileDialog::getSaveFileName(this,
                            "Save Display Dialog",
                            strDirPath,
                            "Doppler Files(*.dis)");
    if( !strFileName.isEmpty()){
        DISPLAY_CONFIG buff;
        buff.bShowRL = CUR_RES.bShowRL;
        buff.bShowSL = CUR_RES.bShowSL;
        buff.bShowEL = CUR_RES.bShowEL;
        for( int i = 0; i < _pConfig->common.nGroupQty; i++){
            GROUP_CONFIG& _group  = _pConfig->group[i];
            buff.bShowDAC[i]       = _group.bShowCurve;
            buff.bShowThickness[i] = _group.bShowThickness;
            buff.bShowWeld[i]      = _group.bShowWeldPart;
            buff.bShowMeasure[i]   = _group.bShowMeasure;
            buff.bShowCursor[i]    = _group.bShowCursor;
            for(int j = 0; j < setup_MAX_MEASURE_QTY; j++){
                buff.anMeasureSelection[i][j] = _group.aeMeasureType[j];
            }
            buff.DisplayMode[i]    = _group.DisplayMode;
            buff.CScanSource[i][0] = (int)_group.eCScanSource[0];
            buff.CScanSource[i][1] = (int)_group.eCScanSource[1];
            buff.MinThickness[i]   = _group.fMinThickness;
            buff.MaxThickness[i]   = _group.fMaxThickness;
            buff.CurSS[i]          = CUR_RES.CurSS[i];
            buff.Standard[i]       = CUR_RES.Standard[i];
            buff.Thickness[i]      = CUR_RES.Thickness[i];
        }
        for(int i = _pConfig->common.nGroupQty; i < setup_MAX_GROUP_QTY; i++){
            buff.bShowDAC[i]       = true;
            buff.bShowThickness[i] = false;
            buff.bShowWeld[i]      = false;
            buff.bShowMeasure[i]   = true;
            buff.bShowCursor[i]    = true;
            buff.DisplayMode[i]    = 12;
            buff.CScanSource[i][0] = 0;
            buff.CScanSource[i][1] = 3;
            buff.MinThickness[i]   = 0;
            buff.MaxThickness[i]   = 50;
            buff.CurSS[i]          = 0;
            buff.Standard[i]       = 0;
            buff.Thickness[i]      = 0;
            buff.anMeasureSelection[i][0] = 1;
            buff.anMeasureSelection[i][1] = 32;
            buff.anMeasureSelection[i][2] = 34;
            buff.anMeasureSelection[i][3] = 0;
            buff.anMeasureSelection[i][4] = 0;
            buff.anMeasureSelection[i][5] = 0;
            buff.anMeasureSelection[i][6] = 0;
            buff.anMeasureSelection[i][7] = 0;
            buff.anMeasureSelection[i][8] = 0;
            buff.anMeasureSelection[i][9] = 0;
        }

        QFile file( strFileName);
        file.open(QIODevice::WriteOnly);
        QDataStream write(&file);
        write.writeRawData((char*)&buff, sizeof(DISPLAY_CONFIG));
        file.close();
    }
}

void MainWindow::on_actionLoadDisplay_triggered()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    QString strDirPath = QCoreApplication::applicationDirPath() + "/init/config/";
    QString strFileName = QFileDialog::getOpenFileName(this,
                            "Load Display Dialog",
                            strDirPath,
                            "Doppler Files(*.dis)");
    if( !strFileName.isEmpty()){
        DISPLAY_CONFIG buff;
        QFile file(strFileName);
        file.open (QIODevice::ReadOnly);
        QDataStream reader(&file);

        int ret = reader.readRawData((char*)&buff, sizeof(DISPLAY_CONFIG));
        if( ret != sizeof(DISPLAY_CONFIG)){
            return;
        }
        int _nGroupQty = _pConfig->common.nGroupQty;
        CUR_RES.bShowRL = buff.bShowRL;
        CUR_RES.bShowSL = buff.bShowSL;
        CUR_RES.bShowEL = buff.bShowEL;
        for( int i = 0; i < _nGroupQty; i++){
            GROUP_CONFIG& _group  = _pConfig->group[i];
            _group.bShowCurve     = buff.bShowDAC[i];
            _group.bShowThickness = buff.bShowThickness[i];
            _group.bShowWeldPart  = buff.bShowWeld[i];
            _group.bShowMeasure   = buff.bShowMeasure[i];
            _group.bShowCursor    = buff.bShowCursor[i];
            for(int j = 0; j < setup_MAX_MEASURE_QTY; j++){
                _group.aeMeasureType[j] = buff.anMeasureSelection[i][j];
            }
            _group.DisplayMode = buff.DisplayMode[i];
            _group.eCScanSource[0] = (setup_CSCAN_SOURCE_MODE)buff.CScanSource[i][0];
            _group.eCScanSource[1] = (setup_CSCAN_SOURCE_MODE)buff.CScanSource[i][1];
            _group.fMinThickness = buff.MinThickness[i];
            _group.fMaxThickness = buff.MaxThickness[i];
            CUR_RES.CurSS[i]     = buff.CurSS[i];
            CUR_RES.Standard[i]  = buff.Standard[i];
            CUR_RES.Thickness[i] = buff.Thickness[i];
        }

        for(int i = 0; i < _nGroupQty; i++){
            m_pGroupList.at(i)->UpdateGroupConfig();
            m_pGroupList.at(i)->LoadStandardFormConifg();
        }
        DopplerViewFrame* _pViewFrame = NULL;
        if(_nGroupQty > 1){
            for(int i = 1; i < _nGroupQty+1; i++){

                ui->TabWidget_display->setCurrentIndex(i);
                sleep(600); //这里一定要sleep不然会崩
                m_iCurGroup = i-1;
                _pViewFrame = (DopplerViewFrame*)ui->TabWidget_display->currentWidget();

                int disp_mode = _pConfig->group[m_iCurGroup].DisplayMode;
                if(disp_mode < 0){
                    disp_mode = (int)ProcessDisplay::DISP_S_AV;
                }
                if(_pConfig->group[m_iCurGroup].eGroupMode == setup_GROUP_MODE_PA) {
                    _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_MODE(disp_mode));
                } else {
                    _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_AH_BV);
                }

            }
        }else{
            ui->TabWidget_display->setCurrentIndex(0);
            sleep(600);
            m_iCurGroup = 0;
            _pViewFrame = (DopplerViewFrame*)ui->TabWidget_display->currentWidget();
            _pViewFrame->SetViewFrameId(0);
            int disp_mode = _pConfig->group[0].DisplayMode;
            if(disp_mode < 0){
                disp_mode = (int)ProcessDisplay::DISP_S_AV;
            }
            if(_pConfig->group[m_iCurGroup].eGroupMode == setup_GROUP_MODE_PA) {
                _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_MODE(disp_mode));
            } else {
                _pViewFrame->CreateDrawView(m_iCurGroup, ProcessDisplay::DISP_AH_BV);
            }
        }
    }
}

void MainWindow::slot_actionEnglish_triggered()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->AppEvn.eLanguage = setup_LANG_ENGLISH;
    m_currentLang = setup_LANG_ENGLISH;

    ui->actionEnglish->setChecked(true);
    ui->actionChinese->setChecked(false);
    ui->actionJapanese->setChecked(false);
    ui->actionLanguage->setIcon(QIcon(":/file/resource/toolbar/0-20.png"));

    translator->load(":/file/translator/phascan_view_english.qm");

    ui->ScanHardware->retranslateUi();

    int _nGroupQty = _pConfig->common.nGroupQty;
    for(int i = 0; i < _nGroupQty; i++){
        m_pGroupList.at(i)->retranslateGroupTabUi();
        m_pGroupList.at(i)->UpdateGroupConfig();
    }

    ui->retranslateUi(this);
    this->setWindowTitle(m_titleName + m_fileName);
}

void MainWindow::slot_actionChinese_triggered()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->AppEvn.eLanguage = setup_LANG_CHINESE;
    m_currentLang = setup_LANG_CHINESE;

    ui->actionChinese->setChecked(true);
    ui->actionEnglish->setChecked(false);
    ui->actionJapanese->setChecked(false);
    ui->actionLanguage->setIcon(QIcon(":/file/resource/toolbar/0-22.png"));

    translator->load(":/file/translator/phascan_view_chinese.qm");

    ui->ScanHardware->retranslateUi();

    int _nGroupQty = _pConfig->common.nGroupQty;
    for(int i = 0; i < _nGroupQty; i++){
        m_pGroupList.at(i)->retranslateGroupTabUi();
        m_pGroupList.at(i)->UpdateGroupConfig();
    }

    ui->retranslateUi(this);
    this->setWindowTitle(m_titleName + m_fileName);
}

void MainWindow::on_actionJapanese_triggered()
{
    ui->actionJapanese->setChecked(true);
    ui->actionChinese->setChecked(false);
    ui->actionEnglish->setChecked(false);

    translator->load(":/file/translator/phascan_view_japanese.qm");

    ui->retranslateUi(this);
}

/****************************************************************************
  Description: 窗口尺寸变化后  数据显示需要刷新
*****************************************************************************/
void MainWindow::slotDataViewResized(DopplerDataView* pView_)
{
    ProcessDisplay _process;
    _process.UpdateDataViewFrame(pView_);
    _process.UpdateDataViewOverlay(pView_);
    pView_->UpdateDrawing();
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAboutVersion dialog(this);
    dialog.exec();
}

void MainWindow::on_actionAided_Analysis_triggered()
{
    if(currentgroup == -1){
        QMessageBox::warning(this, tr("Wrong View"), tr("Please Choose a Group View"));
        return;
    }
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    GROUP_CONFIG& group = _pConfig->group[currentgroup];
    if(group.eGroupMode != setup_GROUP_MODE_PA){
        QMessageBox::warning(this, tr("Wrong GroupMode"), tr("This is not PA Group"));
        return;
    }
    if(!group.TopCInfo.TOPCStatus){
        QMessageBox::warning(this, tr("TOPC not Open"), tr("Please Open TOPC Mode"));
        return;
    }
    int _displayIndex = group.DisplayMode;
    if(_displayIndex < 16 || _displayIndex > 24){
        QMessageBox::warning(this, tr("Worng View Mode"), tr("Please Choose a View Has S Scan And C Scan"));
        return;
    }
    int methodId = _pConfig->common.aidedAnalysis.aidedMethodId;
    DialogMethodSelect defectView( methodId, this);
    defectView.exec();
    methodId = defectView.getMethodId();
    //qDebug()<<"methodId"<<methodId;
    _pConfig->common.aidedAnalysis.aidedGroupId = currentgroup;
    _pConfig->common.aidedAnalysis.aidedStatus  = true;
    _pConfig->common.aidedAnalysis.aidedMethodId = methodId;
    menuBar()->setEnabled(false);
    //ui->toolBar->setEnabled(false);
    set_ToolBarStatus(false);
    ui->TabWidget_parameter->setEnabled(false);
}

void MainWindow::on_actionStop_Analysis_triggered()
{
    DopplerConfigure* _pConfig = DopplerConfigure::Instance();
    _pConfig->common.aidedAnalysis.aidedStatus  = false;
    //int _nGroupId = _pConfig->common.aidedAnalysis.aidedGroupId;
    menuBar()->setEnabled(true);
    set_ToolBarStatus(true);
    ui->TabWidget_parameter->setEnabled(true);
}

void MainWindow::set_ToolBarStatus( bool status)
{
    ui->actionOpenFile->setEnabled(status);
    ui->actionReport_Add_One_Item->setEnabled(status);
    ui->actionReport_Del_One_Item->setEnabled(status);
    ui->actionReport_Setting->setEnabled(status);
    ui->actionSave_Report->setEnabled(status);
    ui->actionTOFD_LW_Straitening->setEnabled(status);
    ui->actionTOFD_BW_Straitening->setEnabled(status);
    ui->actionTOFD_LW_Removal->setEnabled(status);
    ui->actionTOFD_SAFT->setEnabled(status);
    ui->actionTOFD_Repeal->setEnabled(status);
    ui->actionTOFD_Redo->setEnabled(status);
    ui->actionTOFD_Length_Measurement->setEnabled(status);
    ui->actionTOFD_Height_Measurement->setEnabled(status);
    ui->actionTOFD_Depth_Measurement->setEnabled(status);
    //ui->actionSave_Defect->setEnabled(status);
    ui->actionLanguage->setEnabled(status);
    ui->actionScreenShot->setEnabled(status);
    ui->actionAided_Analysis->setEnabled(status);
    ui->actionStop_Analysis->setEnabled(!status);
    //sliderh->setEnabled(status);
}
