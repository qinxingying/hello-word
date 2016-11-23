/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
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
    QAction *actionClose_2;
    QAction *actionEnglish;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *actionMenu;
    QAction *actionAbout;
    QAction *actionReport_Format;
    QAction *actionReport_PreView;
    QAction *actionSave_2;
    QWidget *centralwidget;
    QSplitter *splitter;
    PoppingTabWidget *TabWidgetLeft;
    DopplerGroupTab *Group1;
    InstrumentSettingWidget *ScanHardware;
    QWidget *GroupAdd;
    PoppingTabWidget *TabWidgetRight;
    DopplerViewFrame *Display1;
    QWidget *AddDisplay;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuLanguage;
    QMenu *menuAbout;
    QMenu *menuReport;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(805, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setBold(false);
        font.setWeight(50);
        font.setStyleStrategy(QFont::PreferAntialias);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/Main/resource/Main/0-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew_Config = new QAction(MainWindow);
        actionNew_Config->setObjectName(QString::fromUtf8("actionNew_Config"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionOpen_Scan_Data = new QAction(MainWindow);
        actionOpen_Scan_Data->setObjectName(QString::fromUtf8("actionOpen_Scan_Data"));
        actionClose_2 = new QAction(MainWindow);
        actionClose_2->setObjectName(QString::fromUtf8("actionClose_2"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        actionMenu = new QAction(MainWindow);
        actionMenu->setObjectName(QString::fromUtf8("actionMenu"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionReport_Format = new QAction(MainWindow);
        actionReport_Format->setObjectName(QString::fromUtf8("actionReport_Format"));
        actionReport_PreView = new QAction(MainWindow);
        actionReport_PreView->setObjectName(QString::fromUtf8("actionReport_PreView"));
        actionSave_2 = new QAction(MainWindow);
        actionSave_2->setObjectName(QString::fromUtf8("actionSave_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(0, 0, 801, 521));
        splitter->setOrientation(Qt::Horizontal);
        TabWidgetLeft = new PoppingTabWidget(splitter);
        TabWidgetLeft->setObjectName(QString::fromUtf8("TabWidgetLeft"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TabWidgetLeft->sizePolicy().hasHeightForWidth());
        TabWidgetLeft->setSizePolicy(sizePolicy);
        TabWidgetLeft->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        font1.setKerning(true);
        TabWidgetLeft->setFont(font1);
        TabWidgetLeft->setAutoFillBackground(true);
        TabWidgetLeft->setTabPosition(QTabWidget::East);
        TabWidgetLeft->setTabShape(QTabWidget::Rounded);
        TabWidgetLeft->setIconSize(QSize(16, 16));
        TabWidgetLeft->setTabsClosable(false);
        Group1 = new DopplerGroupTab();
        Group1->setObjectName(QString::fromUtf8("Group1"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-27.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidgetLeft->addTab(Group1, icon1, QString());
        ScanHardware = new InstrumentSettingWidget();
        ScanHardware->setObjectName(QString::fromUtf8("ScanHardware"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-28.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidgetLeft->addTab(ScanHardware, icon2, QString());
        GroupAdd = new QWidget();
        GroupAdd->setObjectName(QString::fromUtf8("GroupAdd"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-36.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidgetLeft->addTab(GroupAdd, icon3, QString());
        splitter->addWidget(TabWidgetLeft);
        TabWidgetRight = new PoppingTabWidget(splitter);
        TabWidgetRight->setObjectName(QString::fromUtf8("TabWidgetRight"));
        TabWidgetRight->setBaseSize(QSize(16, 16));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        TabWidgetRight->setFont(font2);
        TabWidgetRight->setAutoFillBackground(false);
        TabWidgetRight->setTabShape(QTabWidget::Rounded);
        TabWidgetRight->setIconSize(QSize(16, 16));
        TabWidgetRight->setElideMode(Qt::ElideLeft);
        TabWidgetRight->setTabsClosable(false);
        Display1 = new DopplerViewFrame();
        Display1->setObjectName(QString::fromUtf8("Display1"));
        Display1->setAutoFillBackground(false);
        TabWidgetRight->addTab(Display1, QString());
        AddDisplay = new QWidget();
        AddDisplay->setObjectName(QString::fromUtf8("AddDisplay"));
        TabWidgetRight->addTab(AddDisplay, icon3, QString());
        splitter->addWidget(TabWidgetRight);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 805, 22));
        menubar->setAutoFillBackground(true);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuLanguage = new QMenu(menubar);
        menuLanguage->setObjectName(QString::fromUtf8("menuLanguage"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuReport = new QMenu(menubar);
        menuReport->setObjectName(QString::fromUtf8("menuReport"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setAutoFillBackground(true);
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMinimumSize(QSize(0, 32));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuLanguage->menuAction());
        menubar->addAction(menuReport->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew_Config);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_2);
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(action_2);
        menuLanguage->addAction(action_3);
        menuLanguage->addAction(action_4);
        menuAbout->addAction(actionMenu);
        menuAbout->addAction(actionAbout);
        menuReport->addAction(actionReport_Format);
        menuReport->addAction(actionReport_PreView);
        menuReport->addAction(actionSave_2);

        retranslateUi(MainWindow);

        TabWidgetLeft->setCurrentIndex(0);
        TabWidgetRight->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Doppler", 0, QApplication::UnicodeUTF8));
        actionNew_Config->setText(QApplication::translate("MainWindow", "New Configure", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open Configure", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save Configure", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close File", 0, QApplication::UnicodeUTF8));
        actionOpen_Scan_Data->setText(QApplication::translate("MainWindow", "Open Scan Data", 0, QApplication::UnicodeUTF8));
        actionClose_2->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("MainWindow", "\344\270\255\346\226\207", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindow", "\346\227\245\350\257\255", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("MainWindow", "\351\237\251\350\257\255", 0, QApplication::UnicodeUTF8));
        actionMenu->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionReport_Format->setText(QApplication::translate("MainWindow", "Report Format", 0, QApplication::UnicodeUTF8));
        actionReport_PreView->setText(QApplication::translate("MainWindow", "Report PreView", 0, QApplication::UnicodeUTF8));
        actionSave_2->setText(QApplication::translate("MainWindow", "Save ", 0, QApplication::UnicodeUTF8));
        TabWidgetLeft->setTabText(TabWidgetLeft->indexOf(Group1), QApplication::translate("MainWindow", "Group 1", 0, QApplication::UnicodeUTF8));
        TabWidgetLeft->setTabText(TabWidgetLeft->indexOf(ScanHardware), QApplication::translate("MainWindow", "Scan", 0, QApplication::UnicodeUTF8));
        TabWidgetLeft->setTabText(TabWidgetLeft->indexOf(GroupAdd), QString());
        TabWidgetRight->setTabText(TabWidgetRight->indexOf(Display1), QApplication::translate("MainWindow", "DISP 1", 0, QApplication::UnicodeUTF8));
        TabWidgetRight->setTabText(TabWidgetRight->indexOf(AddDisplay), QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuReport->setTitle(QApplication::translate("MainWindow", "Report", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
