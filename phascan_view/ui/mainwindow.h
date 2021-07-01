﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "const.h"
#include "Struct.h"
#include "DopplerConfigure.h"
#include "DopplerDataView.h"
#include "DopplerGraphicsItem.h"
#include "DopplerLineItem.h"
#include "DopplerGateItem.h"
#include "DopplerLawMarker.h"
#include <qslider.h>
#include <QMainWindow>
#include <QTranslator>
#include <QDoubleSpinBox>
#include "dialog/dialogdefectmethodselect.h"

#define MAX_LIST_QTY     10
class DataRefreshThread;
class DopplerGroupTab;
class QTabWidget;
class QLabel;
class DopplerViewFrame;
class InstrumentSettingWidget;
class RemoteMonitoring;
class assemblyRemotesDialog;

struct STATUS_BAR_INFO
{
    int nGroupQty;
    int nLawQty;
    int nDataSize;

    int nBatery1;
    int nBatery2;
    int nTmperature;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QList<QWidget*>* GetCurrentDisplayTableWidgetList();
    QList<QWidget*>* GetDisplayTableWidgetList(int nIndex_);
    int  GetDisplayTableQty() const;
    int  GetCurrentTabelIndex();
    void SetStatusBarMessageColor(int nId_, QColor& fgColor_, QColor& bgColor_);
    void SetStatusBarMessage(int nId_, QString& str_);
    void UpdateStatusBarInfo();
    void RunDrawThread();
    void RunDrawThreadOnce(bool bUseDrawThread_ = true);

    void UpdateAllDisplay();
    int GetCurGroup() {return m_iCurGroup;}
    void SetCurGroup(int nGroupID_);
    void SetWndName();
    void fileMergePro(QStringList &fileNameLst);
    void OpenFilePro(QString strFileName_);
    void ScreenShot();
    bool ParamBackMode(void) {return m_bParamBackMode;}
    void SetParamBackMode(bool mode_) {m_bParamBackMode = mode_;}
    bool DefectBackMode(void) {return m_bDefectBackMode;}
    void SetDefectBackMode(bool mode_) {m_bDefectBackMode = mode_;}
    void UpdateCombinationDisplay();
    int SaveCurScreenshot(QString strPath_);
    void initSlider();
    void initIndexSlider();
    void UpdateSlider();
    void UpdateIndexSlider();
    void AidedAnalysisDone(bool);
    void setAllTopcWidht(double value);
    void updateAllDefectBox();
    void loadDefectPosition(int groupId, int index);
    void loadDefectPositionAndSave(int groupId, DEFECT_INFO &defect);
    void setDefectIdentifyCScanArea(double scanStart, double scanStop, double beamStart, double beamStop);
    void setDefectIdentifySScanArea(QRectF _rect);
    void setSelectSscanAreaValid(bool _isValid);
    int selectDefectMeasureMethod();
    void startDefectIdentify();
    void reloadDefect();

protected:
    void CreateStatusBar();
    void DestroyDisplayTab(int);
    void DestroyAllDisplay();

    void AddOneGroup();
    void UpdateTableParameter();
    void UpdateTableDisplay();
    void InsertRightTab();
    void NewConfigure();
    void OpenFile();
    void SaveFile();

    void ReportAddOneItem();
    void ReportDelOneItem();
    void ReportSetting();
    void ReportSave();

    void TofdDataPro(TOFD_PRO_STATUS proSt_);

    void DefectSign(DEFECT_SIGN_TYPE signType_);
    void SetSelectedDataView(QWidget* pWidget_);
    void updateAllTabwidgetSscanPos(int _nGroupId, int pos);
    void updateCscanLawPos(int _nPos, int _nGroupId);
    float GetCurrentTabLinearScanMaxLineCount(int _nGroupId);
    QList<QWidget*>* m_pViewList[MAX_LIST_QTY];

    virtual void closeEvent(QCloseEvent *event);
    //virtual void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *);

private:
    void set_ToolBarStatus( bool status);
    void updateCurLawPos(int _nGroupId, int lawPos, int _nId);
    Ui::MainWindow *ui;
    DataRefreshThread* m_pThreadDraw;
    QTranslator *translator;
    QSlider* sliderh;
    QDoubleSpinBox *scanSpin;
    QWidget* SliderWidget;
    QSlider* indexSliderh;
    QWidget* indexSliderWidget;
    QWidget* m_pCurrentDataView;
    QLabel* m_pStatusCell[3];
    STATUS_BAR_INFO m_BarInfo;
    QString m_titleName;
    QString m_fileName;
    QString m_baseName;
    DialogDefectMethodSelect defectMethodNew;

    QList<DopplerGroupTab*> m_pGroupList;
    //RemoteMonitoring *m_remoteMonitoring;
    assemblyRemotesDialog *m_assemblyRemotes;

    void init_ui();

    int  m_iCurGroup;
    int  m_iCurDefectMaxValue {0};  // 当前缺陷最大值
    //int  m_nLawIdSel;
    int  m_nTBCnt;
    int  m_nAlloff;  //0值时表示只有一个组
    bool m_bCursorSel;
    bool m_bParamBackMode;
    bool m_bDefectBackMode;
    setup_LANG m_currentLang;

signals:
    void setPixmap(QPixmap pixmap);

private slots:
    void slotsLeftTabButton(Qt::MouseButton);
    void slotsRightTabButton(Qt::MouseButton);
    void slotLeftTabRightButtonDoubleClicked(int);
    void SetDispTabText();
    void slotRightTabRightButtonDoubleClicked(int nId_);
    void slotViewFrameButtonClicked(QWidget* );
    void slotCurrentGroupChanged(int);
    void slotCurrentDispChanged(int);
    void slotSliderhChanged(int);
    void slotIndexSliderHChanged(int);
    void slotScanSpinChanged(double);
    void slotItemMoved(DopplerDataView* , DopplerGraphicsItem*);
    void slotDataViewResized(DopplerDataView*) ;
    void slotDataViewMouseDoubleClicked(DopplerDataView* pView_, QPointF pos_);
    void slotTopcMergeCompareViewShow(bool);
    void connect_remote_monitor();
    void allThicknessChange(double thickness);
    void slotScanPosChange(int steps);
    void slotLawPosChange(int groupId, int lawId, int steps);
    void slotCursorScanChange(int groupId, bool orientation);
    void slotCursorUChange(int groupId, int lawId, bool orientation);
    void slotShowCursor(int groupId, bool status);
    void slotShowDefect(int groupId, bool status);
    void slotCsanShowallChange(int groupId);
    void slotMeasureGate(int groupId);
    void slotMarkNextDefect();
    void slotMarkPreviousDefect();
    void slotDeleteDefect();
    void slotSaveDefect();

protected slots:
  void on_actionNew_Config_triggered();
  void on_actionOpen_triggered();
  void on_actionSave_triggered();
  void on_actionExit_triggered();
  void on_actionReport_PreView_triggered();
  void on_actionSaveReport_triggered();

  void on_actionNew_triggered();                    // (1).ToolBar
  void on_actionOpenFile_triggered();
  void on_actionSaveFile_triggered();
  void on_actionReport_Add_One_Item_triggered();
  void on_actionReport_Del_One_Item_triggered();
  void on_actionReport_Setting_triggered();
  void on_actionSave_Report_triggered();
  void on_actionTOFD_LW_Straitening_triggered();
  void on_actionTOFD_BW_Straitening_triggered();
  void on_actionTOFD_LW_Removal_triggered();
  void on_actionTOFD_SAFT_triggered();
  void on_actionTOFD_Repeal_triggered();
  void on_actionTOFD_Redo_triggered();
  void on_actionTOFD_Length_Measurement_triggered();
  void on_actionTOFD_Height_Measurement_triggered();
  void on_actionTOFD_Depth_Measurement_triggered();
  void on_actionSave_Defect_triggered();
  void on_actionLanguage_triggered();
  void on_actionScreenShot_triggered();
  void on_actionSaveDisplay_triggered();
  void on_actionLoadDisplay_triggered();
  void slot_actionEnglish_triggered();
  void slot_actionChinese_triggered();
  void on_actionJapanese_triggered();
  void on_actionHelp_triggered();
  void on_actionAbout_triggered();
  void on_actionAided_Analysis_triggered();
  void on_actionStop_Analysis_triggered();
  void on_actionFile_Properties_triggered();
  void slot_actionSaveCSacnData_triggered();
  void slot_actionSaveBSacnData_triggered();
};

extern MainWindow* g_pMainWnd;

#endif // MAINWINDOW_H
