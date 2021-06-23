/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <measurewidget.h>
#include <ui/DopplerGroupTab.h>
#include <ui/DopplerViewFrame.h>
#include <ui/InstrumentSettingWidget.h>
#include <ui/PoppingTabWidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Config;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionOpen_Scan_Data;
    QAction *actionExit;
    QAction *actionEnglish;
    QAction *actionChinese;
    QAction *actionJapanese;
    QAction *actionKorean;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionReport_Format;
    QAction *actionReport_PreView;
    QAction *actionSaveReport;
    QAction *actionOpenFile;
    QAction *actionNew;
    QAction *actionSaveFile;
    QAction *actionReport_Add_One_Item;
    QAction *actionReport_Del_One_Item;
    QAction *actionReport_Setting;
    QAction *actionSave_Report;
    QAction *actionTOFD_LW_Straitening;
    QAction *actionTOFD_BW_Straitening;
    QAction *actionTOFD_LW_Removal;
    QAction *actionTOFD_SAFT;
    QAction *actionTOFD_Repeal;
    QAction *actionTOFD_Redo;
    QAction *actionTOFD_Length_Measurement;
    QAction *actionTOFD_Height_Measurement;
    QAction *actionTOFD_Depth_Measurement;
    QAction *actionSave_Defect;
    QAction *actionLanguage;
    QAction *actionScreenShot;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionSaveDisplay;
    QAction *actionLoadDisplay;
    QAction *actionAided_Analysis;
    QAction *actionStop_Analysis;
    QAction *actionFile_Properties;
    QAction *actionSave_Data;
    QAction *actionSave_B_Scan_Data;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    MeasureWidget *measureWidget;
    PoppingTabWidget *TabWidget_display;
    DopplerViewFrame *Display1;
    QWidget *AddDisplay;
    PoppingTabWidget *TabWidget_parameter;
    DopplerGroupTab *Group1;
    InstrumentSettingWidget *ScanHardware;
    QWidget *GroupAdd;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuLanguage;
    QMenu *menuAbout;
    QMenu *menuReport;
    QMenu *menuConnect;
    QMenu *menuDisplay;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(757, 555);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setBold(false);
        font.setWeight(50);
        font.setStyleStrategy(QFont::PreferAntialias);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/file/resource/main/0-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew_Config = new QAction(MainWindow);
        actionNew_Config->setObjectName(QStringLiteral("actionNew_Config"));
        actionNew_Config->setCheckable(true);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen->setCheckable(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setCheckable(true);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionOpen_Scan_Data = new QAction(MainWindow);
        actionOpen_Scan_Data->setObjectName(QStringLiteral("actionOpen_Scan_Data"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setCheckable(true);
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionEnglish->setCheckable(true);
        actionChinese = new QAction(MainWindow);
        actionChinese->setObjectName(QStringLiteral("actionChinese"));
        actionChinese->setCheckable(true);
        actionJapanese = new QAction(MainWindow);
        actionJapanese->setObjectName(QStringLiteral("actionJapanese"));
        actionJapanese->setCheckable(true);
        actionKorean = new QAction(MainWindow);
        actionKorean->setObjectName(QStringLiteral("actionKorean"));
        actionKorean->setCheckable(true);
        actionKorean->setEnabled(false);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionHelp->setEnabled(true);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout->setEnabled(true);
        actionReport_Format = new QAction(MainWindow);
        actionReport_Format->setObjectName(QStringLiteral("actionReport_Format"));
        actionReport_PreView = new QAction(MainWindow);
        actionReport_PreView->setObjectName(QStringLiteral("actionReport_PreView"));
        actionSaveReport = new QAction(MainWindow);
        actionSaveReport->setObjectName(QStringLiteral("actionSaveReport"));
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/file/resource/toolbar/0-02.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/file/resource/toolbar/0-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon2);
        actionSaveFile = new QAction(MainWindow);
        actionSaveFile->setObjectName(QStringLiteral("actionSaveFile"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/file/resource/toolbar/0-03.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveFile->setIcon(icon3);
        actionReport_Add_One_Item = new QAction(MainWindow);
        actionReport_Add_One_Item->setObjectName(QStringLiteral("actionReport_Add_One_Item"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/file/resource/toolbar/0-04.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReport_Add_One_Item->setIcon(icon4);
        actionReport_Del_One_Item = new QAction(MainWindow);
        actionReport_Del_One_Item->setObjectName(QStringLiteral("actionReport_Del_One_Item"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/file/resource/toolbar/0-05.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReport_Del_One_Item->setIcon(icon5);
        actionReport_Setting = new QAction(MainWindow);
        actionReport_Setting->setObjectName(QStringLiteral("actionReport_Setting"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/file/resource/toolbar/0-06.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReport_Setting->setIcon(icon6);
        actionSave_Report = new QAction(MainWindow);
        actionSave_Report->setObjectName(QStringLiteral("actionSave_Report"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/file/resource/toolbar/0-07.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Report->setIcon(icon7);
        actionTOFD_LW_Straitening = new QAction(MainWindow);
        actionTOFD_LW_Straitening->setObjectName(QStringLiteral("actionTOFD_LW_Straitening"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/file/resource/toolbar/0-10.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_LW_Straitening->setIcon(icon8);
        actionTOFD_BW_Straitening = new QAction(MainWindow);
        actionTOFD_BW_Straitening->setObjectName(QStringLiteral("actionTOFD_BW_Straitening"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/file/resource/toolbar/0-11.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_BW_Straitening->setIcon(icon9);
        actionTOFD_LW_Removal = new QAction(MainWindow);
        actionTOFD_LW_Removal->setObjectName(QStringLiteral("actionTOFD_LW_Removal"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/file/resource/toolbar/0-12.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_LW_Removal->setIcon(icon10);
        actionTOFD_SAFT = new QAction(MainWindow);
        actionTOFD_SAFT->setObjectName(QStringLiteral("actionTOFD_SAFT"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/file/resource/toolbar/0-13.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_SAFT->setIcon(icon11);
        actionTOFD_Repeal = new QAction(MainWindow);
        actionTOFD_Repeal->setObjectName(QStringLiteral("actionTOFD_Repeal"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/file/resource/toolbar/0-14.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_Repeal->setIcon(icon12);
        actionTOFD_Redo = new QAction(MainWindow);
        actionTOFD_Redo->setObjectName(QStringLiteral("actionTOFD_Redo"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/file/resource/toolbar/0-15.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_Redo->setIcon(icon13);
        actionTOFD_Length_Measurement = new QAction(MainWindow);
        actionTOFD_Length_Measurement->setObjectName(QStringLiteral("actionTOFD_Length_Measurement"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/file/resource/toolbar/0-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_Length_Measurement->setIcon(icon14);
        actionTOFD_Height_Measurement = new QAction(MainWindow);
        actionTOFD_Height_Measurement->setObjectName(QStringLiteral("actionTOFD_Height_Measurement"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/file/resource/toolbar/0-17.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_Height_Measurement->setIcon(icon15);
        actionTOFD_Depth_Measurement = new QAction(MainWindow);
        actionTOFD_Depth_Measurement->setObjectName(QStringLiteral("actionTOFD_Depth_Measurement"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/file/resource/toolbar/0-18.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTOFD_Depth_Measurement->setIcon(icon16);
        actionSave_Defect = new QAction(MainWindow);
        actionSave_Defect->setObjectName(QStringLiteral("actionSave_Defect"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/file/resource/toolbar/0-19.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Defect->setIcon(icon17);
        actionLanguage = new QAction(MainWindow);
        actionLanguage->setObjectName(QStringLiteral("actionLanguage"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/file/resource/toolbar/0-20.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLanguage->setIcon(icon18);
        actionScreenShot = new QAction(MainWindow);
        actionScreenShot->setObjectName(QStringLiteral("actionScreenShot"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/file/resource/toolbar/0-21.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScreenShot->setIcon(icon19);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionSaveDisplay = new QAction(MainWindow);
        actionSaveDisplay->setObjectName(QStringLiteral("actionSaveDisplay"));
        actionLoadDisplay = new QAction(MainWindow);
        actionLoadDisplay->setObjectName(QStringLiteral("actionLoadDisplay"));
        actionAided_Analysis = new QAction(MainWindow);
        actionAided_Analysis->setObjectName(QStringLiteral("actionAided_Analysis"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/file/resource/toolbar/0-23.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAided_Analysis->setIcon(icon20);
        actionStop_Analysis = new QAction(MainWindow);
        actionStop_Analysis->setObjectName(QStringLiteral("actionStop_Analysis"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/file/resource/toolbar/0-24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop_Analysis->setIcon(icon21);
        actionFile_Properties = new QAction(MainWindow);
        actionFile_Properties->setObjectName(QStringLiteral("actionFile_Properties"));
        actionFile_Properties->setEnabled(false);
        actionSave_Data = new QAction(MainWindow);
        actionSave_Data->setObjectName(QStringLiteral("actionSave_Data"));
        actionSave_B_Scan_Data = new QAction(MainWindow);
        actionSave_B_Scan_Data->setObjectName(QStringLiteral("actionSave_B_Scan_Data"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        measureWidget = new MeasureWidget(splitter);
        measureWidget->setObjectName(QStringLiteral("measureWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(measureWidget->sizePolicy().hasHeightForWidth());
        measureWidget->setSizePolicy(sizePolicy);
        measureWidget->setMaximumSize(QSize(250, 16777215));
        splitter->addWidget(measureWidget);
        TabWidget_display = new PoppingTabWidget(splitter);
        TabWidget_display->setObjectName(QStringLiteral("TabWidget_display"));
        TabWidget_display->setBaseSize(QSize(16, 16));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        TabWidget_display->setFont(font1);
        TabWidget_display->setAutoFillBackground(false);
        TabWidget_display->setTabPosition(QTabWidget::North);
        TabWidget_display->setTabShape(QTabWidget::Rounded);
        TabWidget_display->setIconSize(QSize(16, 16));
        TabWidget_display->setElideMode(Qt::ElideLeft);
        TabWidget_display->setTabsClosable(false);
        Display1 = new DopplerViewFrame();
        Display1->setObjectName(QStringLiteral("Display1"));
        Display1->setAutoFillBackground(false);
        TabWidget_display->addTab(Display1, QString());
        AddDisplay = new QWidget();
        AddDisplay->setObjectName(QStringLiteral("AddDisplay"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/file/resource/main_menu/0-36.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidget_display->addTab(AddDisplay, icon22, QString());
        splitter->addWidget(TabWidget_display);
        TabWidget_parameter = new PoppingTabWidget(splitter);
        TabWidget_parameter->setObjectName(QStringLiteral("TabWidget_parameter"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TabWidget_parameter->sizePolicy().hasHeightForWidth());
        TabWidget_parameter->setSizePolicy(sizePolicy1);
        TabWidget_parameter->setMinimumSize(QSize(370, 0));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        font2.setKerning(true);
        TabWidget_parameter->setFont(font2);
        TabWidget_parameter->setAutoFillBackground(true);
        TabWidget_parameter->setTabPosition(QTabWidget::West);
        TabWidget_parameter->setTabShape(QTabWidget::Rounded);
        TabWidget_parameter->setIconSize(QSize(16, 16));
        TabWidget_parameter->setTabsClosable(false);
        Group1 = new DopplerGroupTab();
        Group1->setObjectName(QStringLiteral("Group1"));
        Group1->setMinimumSize(QSize(360, 0));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/file/resource/main_menu/0-27.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidget_parameter->addTab(Group1, icon23, QString());
        ScanHardware = new InstrumentSettingWidget();
        ScanHardware->setObjectName(QStringLiteral("ScanHardware"));
        ScanHardware->setMinimumSize(QSize(360, 0));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/file/resource/main_menu/0-28.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidget_parameter->addTab(ScanHardware, icon24, QString());
        GroupAdd = new QWidget();
        GroupAdd->setObjectName(QStringLiteral("GroupAdd"));
        GroupAdd->setMinimumSize(QSize(360, 0));
        TabWidget_parameter->addTab(GroupAdd, icon22, QString());
        splitter->addWidget(TabWidget_parameter);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 757, 22));
        menubar->setAutoFillBackground(true);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuLanguage = new QMenu(menubar);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuReport = new QMenu(menubar);
        menuReport->setObjectName(QStringLiteral("menuReport"));
        menuConnect = new QMenu(menubar);
        menuConnect->setObjectName(QStringLiteral("menuConnect"));
        menuDisplay = new QMenu(menubar);
        menuDisplay->setObjectName(QStringLiteral("menuDisplay"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setAutoFillBackground(true);
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy2);
        toolBar->setMinimumSize(QSize(0, 32));
        toolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuLanguage->menuAction());
        menubar->addAction(menuReport->menuAction());
        menubar->addAction(menuConnect->menuAction());
        menubar->addAction(menuDisplay->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew_Config);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionFile_Properties);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_B_Scan_Data);
        menuFile->addAction(actionSave_Data);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(actionChinese);
        menuAbout->addAction(actionHelp);
        menuAbout->addAction(actionAbout);
        menuReport->addAction(actionReport_PreView);
        menuReport->addAction(actionSaveReport);
        menuConnect->addAction(actionConnect);
        menuDisplay->addAction(actionSaveDisplay);
        menuDisplay->addAction(actionLoadDisplay);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpenFile);
        toolBar->addAction(actionSaveFile);
        toolBar->addSeparator();
        toolBar->addAction(actionReport_Add_One_Item);
        toolBar->addAction(actionReport_Del_One_Item);
        toolBar->addAction(actionReport_Setting);
        toolBar->addAction(actionSave_Report);
        toolBar->addSeparator();
        toolBar->addAction(actionTOFD_LW_Straitening);
        toolBar->addAction(actionTOFD_BW_Straitening);
        toolBar->addAction(actionTOFD_LW_Removal);
        toolBar->addAction(actionTOFD_SAFT);
        toolBar->addSeparator();
        toolBar->addAction(actionTOFD_Repeal);
        toolBar->addAction(actionTOFD_Redo);
        toolBar->addSeparator();
        toolBar->addAction(actionTOFD_Length_Measurement);
        toolBar->addAction(actionTOFD_Height_Measurement);
        toolBar->addAction(actionTOFD_Depth_Measurement);
        toolBar->addAction(actionSave_Defect);
        toolBar->addSeparator();
        toolBar->addAction(actionLanguage);
        toolBar->addSeparator();
        toolBar->addAction(actionAided_Analysis);
        toolBar->addAction(actionStop_Analysis);
        toolBar->addAction(actionScreenShot);

        retranslateUi(MainWindow);

        TabWidget_display->setCurrentIndex(0);
        TabWidget_parameter->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        actionNew_Config->setText(QApplication::translate("MainWindow", "New File", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save File", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close File", Q_NULLPTR));
        actionOpen_Scan_Data->setText(QApplication::translate("MainWindow", "Open Scan Data", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", Q_NULLPTR));
        actionChinese->setText(QApplication::translate("MainWindow", "Chinese", Q_NULLPTR));
        actionJapanese->setText(QApplication::translate("MainWindow", "Japanese", Q_NULLPTR));
        actionKorean->setText(QApplication::translate("MainWindow", "Korean", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        actionReport_Format->setText(QApplication::translate("MainWindow", "Report Format", Q_NULLPTR));
        actionReport_PreView->setText(QApplication::translate("MainWindow", "Report PreView", Q_NULLPTR));
        actionSaveReport->setText(QApplication::translate("MainWindow", "Save ", Q_NULLPTR));
        actionOpenFile->setText(QApplication::translate("MainWindow", "OpenFile", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpenFile->setToolTip(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "New", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSaveFile->setText(QApplication::translate("MainWindow", "SaveFile", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSaveFile->setToolTip(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionReport_Add_One_Item->setText(QApplication::translate("MainWindow", "Report Add One Item", Q_NULLPTR));
        actionReport_Add_One_Item->setIconText(QApplication::translate("MainWindow", "Report Add One Item", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReport_Add_One_Item->setToolTip(QApplication::translate("MainWindow", "Report Add One Item", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionReport_Del_One_Item->setText(QApplication::translate("MainWindow", "Report Del One Item", Q_NULLPTR));
        actionReport_Del_One_Item->setIconText(QApplication::translate("MainWindow", "Report Del One Item", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReport_Del_One_Item->setToolTip(QApplication::translate("MainWindow", "Report Del One Item", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionReport_Setting->setText(QApplication::translate("MainWindow", "Report Setting", Q_NULLPTR));
        actionReport_Setting->setIconText(QApplication::translate("MainWindow", "Report Setting", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReport_Setting->setToolTip(QApplication::translate("MainWindow", "Report Setting", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_Report->setText(QApplication::translate("MainWindow", "Save Report", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_Report->setToolTip(QApplication::translate("MainWindow", "Save Report", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_LW_Straitening->setText(QApplication::translate("MainWindow", "TOFD LW Straitening", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_LW_Straitening->setToolTip(QApplication::translate("MainWindow", "TOFD LW Straitening", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_BW_Straitening->setText(QApplication::translate("MainWindow", "TOFD BW Straitening", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_BW_Straitening->setToolTip(QApplication::translate("MainWindow", "TOFD BW Straitening", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_LW_Removal->setText(QApplication::translate("MainWindow", "TOFD LW Removal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_LW_Removal->setToolTip(QApplication::translate("MainWindow", "TOFD LW Removal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_SAFT->setText(QApplication::translate("MainWindow", "TOFD SAFT", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_SAFT->setToolTip(QApplication::translate("MainWindow", "TOFD SAFT", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_Repeal->setText(QApplication::translate("MainWindow", "TOFD Repeal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_Repeal->setToolTip(QApplication::translate("MainWindow", "TOFD Repeal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_Redo->setText(QApplication::translate("MainWindow", "TOFD Redo", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_Redo->setToolTip(QApplication::translate("MainWindow", "TOFD Redo", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_Length_Measurement->setText(QApplication::translate("MainWindow", "TOFD Length Measurement", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_Length_Measurement->setToolTip(QApplication::translate("MainWindow", "TOFD Length Measurement", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_Height_Measurement->setText(QApplication::translate("MainWindow", "TOFD Height Measurement", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_Height_Measurement->setToolTip(QApplication::translate("MainWindow", "TOFD Height Measurement", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTOFD_Depth_Measurement->setText(QApplication::translate("MainWindow", "TOFD Depth Measurement", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTOFD_Depth_Measurement->setToolTip(QApplication::translate("MainWindow", "TOFD Depth Measurement", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_Defect->setText(QApplication::translate("MainWindow", "Save Defect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_Defect->setToolTip(QApplication::translate("MainWindow", "Save Defect", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLanguage->setText(QApplication::translate("MainWindow", "Language", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLanguage->setToolTip(QApplication::translate("MainWindow", "CH/EN", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionScreenShot->setText(QApplication::translate("MainWindow", "ScreenShot", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionScreenShot->setToolTip(QApplication::translate("MainWindow", "ScreenShot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        actionSaveDisplay->setText(QApplication::translate("MainWindow", "Save Display", Q_NULLPTR));
        actionLoadDisplay->setText(QApplication::translate("MainWindow", "Load Display", Q_NULLPTR));
        actionAided_Analysis->setText(QApplication::translate("MainWindow", "Aided Analysis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAided_Analysis->setToolTip(QApplication::translate("MainWindow", "Aided Analysis Defect", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionStop_Analysis->setText(QApplication::translate("MainWindow", "actionStop_Analysis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStop_Analysis->setToolTip(QApplication::translate("MainWindow", "Stop Analysis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFile_Properties->setText(QApplication::translate("MainWindow", "File Properties", Q_NULLPTR));
        actionSave_Data->setText(QApplication::translate("MainWindow", "Save C Scan Data", Q_NULLPTR));
        actionSave_B_Scan_Data->setText(QApplication::translate("MainWindow", "Save B Scan Data", Q_NULLPTR));
        TabWidget_display->setTabText(TabWidget_display->indexOf(Display1), QApplication::translate("MainWindow", "DISP 1", Q_NULLPTR));
        TabWidget_display->setTabText(TabWidget_display->indexOf(AddDisplay), QString());
        TabWidget_parameter->setTabText(TabWidget_parameter->indexOf(Group1), QApplication::translate("MainWindow", "Group 1", Q_NULLPTR));
        TabWidget_parameter->setTabText(TabWidget_parameter->indexOf(ScanHardware), QApplication::translate("MainWindow", "Scan", Q_NULLPTR));
        TabWidget_parameter->setTabText(TabWidget_parameter->indexOf(GroupAdd), QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        menuReport->setTitle(QApplication::translate("MainWindow", "Report", Q_NULLPTR));
        menuConnect->setTitle(QApplication::translate("MainWindow", "Remote Monitor", Q_NULLPTR));
        menuDisplay->setTitle(QApplication::translate("MainWindow", "Display Config", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
