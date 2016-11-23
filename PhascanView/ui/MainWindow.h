#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <configure/const.h>
#include <configure/Struct.h>
#include <configure/DopplerConfigure.h>
#include <DopplerView/DopplerDataView.h>
#include <DopplerView/DopplerGraphicsItem.h>
#include <DopplerView/DopplerLineItem.h>
#include <DopplerView/DopplerGateItem.h>
#include <DopplerView/DopplerLawMarker.h>

#include <QtGui/QMainWindow>
#include "ui_MainWindow.h"


#define MAX_LIST_QTY     10
class DataRefreshThread ;
class DopplerGroupTab ;
class QTabWidget ;
class QLabel ;
class DopplerViewFrame;

class InstrumentSettingWidget  ;

struct STATUS_BAR_INFO
{
    int nGroupQty ;
    int nLawQty   ;
    int nDataSize ;

    int nBatery1  ;
    int nBatery2  ;
    int nTmperature ;
} ;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();
    QList<QWidget*>* GetCurrentDisplayTableWidgetList();
    QList<QWidget*>* GetDisplayTableWidgetList(int nIndex_);
    int  GetDisplayTableQty() const ;
    int  GetDisplayTableIndex() const;
    void SetStatusBarMessageColor(int nId_, QColor& fgColor_ , QColor& bgColor_) ;
    void SetStatusBarMessage(int nId_ , QString& str_) ;
	void UpdateStatusBarInfo() ;
    void RunDrawThread();
    void RunDrawThreadOnce(bool bUseDrawThread_ = true);

    void UpdateAllDisplay() ;
    int GetCurGroup() {return m_iCurGroup;}
	void SetCurGroup(int nGroupID_);
    void SetWndName(setup_LANG eLang);
	void SoftwareRegisterError();
    void SetToolBarName(setup_LANG eLang);
    void OpenFilePro(QString strFileName_);
	void ScreenShot();
	bool ParamBackMode(void) {return m_bParamBackMode;}
	void SetParamBackMode(bool mode_) {m_bParamBackMode = mode_;}
	void UpdateCombinationDisplay();
	void SaveCurScreenshot(QString strPath_);
protected:
	void CreateToolBar()  ;
    void CreateStatusBar() ;
    void DestroyDisplayTab(int);
    void DestroyAllDisplay();

    void AddOneGroup();
    void UpdateTableLeft();
    void UpdateTableRight();
    void InsertRightTab();
    void NewConfigure();
    void OpenFile();
    void SaveFile();

    void ReportAddOneItem();
    void ReportDelOneItem();
    void ReportSetting();
    void ReportSave();

    void TofdSetting() ;
    void TofdDataPro(TOFD_PRO_STATUS proSt_);
    //  
    void DefectSign(DEFECT_SIGN_TYPE signType_);
    void SetSelectedDataView(QWidget* pWidget_);
    QList<QWidget*>* m_pViewList[MAX_LIST_QTY] ;

    // event
    virtual void closeEvent(QCloseEvent *event) ;
	void resizeEvent(QResizeEvent *);
	//void keyPressEvent(QKeyEvent  *event);
	//void keyReleaseEvent (QKeyEvent  *event);
private:

	int  m_iCurGroup;
	int  m_nLawIdSel;
    bool m_bCursorSel;

	Ui::MainWindow ui;
    DataRefreshThread* m_pThreadDraw ;

    QWidget* m_pCurrentDataView;
    QLabel* m_pStatusCell[3]  ;

    STATUS_BAR_INFO m_BarInfo ;

    QAction* m_actions[26] ;
    int      m_nTBCnt;
    int      m_nAlloff;

	//Qt::BGMode m_paramBackMode;
	bool m_bParamBackMode;
signals:
	void setPixmap(QPixmap pixmap);

private slots:
    void slotsLeftTabButton(Qt::MouseButton) ;
    void slotsRightTabButton(Qt::MouseButton) ;
    void slotActionTriggered(QAction* action_) ;
    void slotLeftTabRightButtonDoubleClicked(int nId_);
    void SetDispTabText();
    void slotRightTabRightButtonDoubleClicked(int nId_);
    void slotViewFrameButtonClicked(QWidget* );
    //void slotViewFrameMenuSelection(DopplerDataView* , int);
    void slotCurrentGroupChanged(int) ;
    void slotCurrentDispChanged(int) ;
    void slotItemMoved(DopplerDataView* , DopplerGraphicsItem*);
    void slotDataViewResized(DopplerDataView*) ;
    void slotDataViewMouseDoubleClicked(DopplerDataView* pView_, QPointF pos_) ;

};

extern MainWindow* g_pMainWnd;

#endif // MAINWINDOW_H
