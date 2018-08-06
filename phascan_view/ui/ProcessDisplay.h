/***************************
  Name:  ProcessDisplay
  Date : 2013-08-26
  Description:   用于设置显示模式
                 根据要求，设置显示窗口的组合，
                 设置显示窗口的类型 ，
                 设置显示窗口的标尺刻度 ，
                 显示窗口的颜色
                 .............
************************************/

#ifndef PROCESSDISPLAY_H
#define PROCESSDISPLAY_H

#include <QObject>
#include <QSize>

#include "DopplerViewFrame.h"
#include "DopplerConfigure.h"
#include "DopplerDataView.h"

class ProcessDisplay : public QObject
{
    Q_OBJECT
public:
    enum DISP_MODE
    {
        DISP_3D_ALL             = 2,
        DISP_3D_PART            = 3,
        DISP_3D_PROBE_WEDGE     = 4,
        DISP_3D_WELD            = 5,
        DISP_3D_SONIC_BEAMS     = 6,

        DISP_AH                 = 7,
        DISP_AH_BV              = 8,
        DISP_AV_BV              = 9,
        DISP_S                  = 10,
        DISP_S_AH               = 11,
        DISP_S_AV               = 12,
        DISP_S_AH_AH_AH         = 13,
        DISP_S_AH_AH_AH_CH      = 14,
        DISP_S_AV_BV            = 15,
        DISP_S_AV_BH            = 16,
        DISP_S_AH_BV            = 17,
        DISP_S_AV_BH_CH         = 18,
        DISP_S_AH_BH_CH         = 19,
        DISP_S_AH_BH_CV         = 20,
        DISP_S_AV_CH            = 21,
        DISP_S_AH_CV            = 22,
        DISP_S_AV_CH_CH         = 23,
        DISP_S_AH_CV_CV         = 24,
        DISP_S_AV_CH_BH         = 25,
        DISP_S_AV_CH_N          = 26,
        DISP_ALLGROUP           = 27
    };
    explicit ProcessDisplay(QObject *parent = 0);
    int CreateViews(QWidget* parent_ , int eType_);
    void SetCurrentGroupId(int nGroupId_);
    static QSize GetMinimumWidgetSize(int eType_);
    static int IsSizeAvailable(int nId_, QWidget* parent_);

    int CreateViews2(QWidget*);

    int CreateViews_AH(QWidget*);
    int CreateViews_AH_BV(QWidget*);
    int CreateViews_AV_BV(QWidget* );
    int CreateViews_S(QWidget*);
    int CreateViews_S_AH(QWidget*);
    int CreateViews_S_AV(QWidget*);
    int CreateViews_S_AH_AH_AH(QWidget*);
    int CreateViews_S_AH_AH_AH_CH(QWidget*);
    int CreateViews_S_AV_BV(QWidget*);
    int CreateViews_S_AV_BH(QWidget*);
    int CreateViews_S_AH_BV(QWidget*);
    int CreateViews_S_AV_BH_CH(QWidget*);
    int CreateViews_S_AH_BH_CH(QWidget*);
    int CreateViews_S_AH_BH_CV(QWidget*);
    int CreateViews_S_AV_CH(QWidget*);
    int CreateViews_S_AH_CV(QWidget*);
    int CreateViews_S_AV_CH_CH(QWidget*);
    int CreateViews_S_AH_CV_CV(QWidget*);
    int CreateViews_S_AV_CH_BH(QWidget*);
    int CreateViews_S_AV_CH_N(QWidget*);
    int CreateViews_AllGroups(QWidget*);

    void ConnectSingals(DopplerDataView** pViews_ , int nQty_) ;
    void ConnectSlots(DopplerDataView*);

    void SetViewPara(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_ , setup_DISPLAY_MODE eDsipaly_);
    void UpdateAll(DopplerDataView* pWidget_ );
    void UpdateAllView();

    void UpdateDataViewFrame(DopplerDataView* pWidget_ );
    void UpdateDataViewFrameAH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameAV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameBH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameBV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameCH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameCV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameSS(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameSA(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewFrameSL(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);

    void UpdateDataViewDraw(DopplerDataView* pWidget_ );
    void UpdateDataViewDrawAH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawAV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawBH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawBV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawCH(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawCV(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawSS(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawSA(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);
    void UpdateDataViewDrawSL(DopplerDataView* pWidget_ , int nGroupId_ , int nLawId_);

    void UpdateDataViewOverlay(DopplerDataView* pWidget_);
    void UpdateDataViewTitle(DopplerDataView* pWidget_);

    void UpdateAllViewOverlay();
    void UpdateAllViewFrame();
    void UpdateAllViewFrameOfGroup(int nGroupId_);
    void UpdateAllViewOverlayOfGroup(int nGroupId_);
    void UpdateAllViewOfGroup(int nGroupId_);
    void UpdateAllViewGateOfGroup(int);
    void UpdateAllViewCursorOfGroup(int) ;


protected:
    DopplerConfigure* m_pConfig ;
    int m_nGroupId;
signals:

public slots:

};

#endif // PROCESSDISPLAY_H
