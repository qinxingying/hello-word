/********************************************************************************
** Form generated from reading UI file 'DopplerGroupTab.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOPPLERGROUPTAB_H
#define UI_DOPPLERGROUPTAB_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpinBox>
#include <QtGui/QToolBox>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <ui/DopplerColorBtn.h>

QT_BEGIN_NAMESPACE

class Ui_DopplerGroupTab
{
public:
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *PageUtSetting;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollAreaUtSetting;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *BoxGeneral;
    QLabel *LabelTravelMode;
    QComboBox *ComTravelMode;
    QLabel *LabelCurrentAngle;
    QComboBox *ComCurrentAngle;
    QLabel *LabelRangeUnit;
    QLabel *LabelStart;
    QDoubleSpinBox *ValueRange;
    QLabel *LabelGain;
    QDoubleSpinBox *ValueGain;
    QLabel *LabelGainUnit;
    QDoubleSpinBox *ValueStart;
    QLabel *LabelStartUnit;
    QLabel *LabelRange;
    QLabel *LabelVelocity;
    QDoubleSpinBox *ValueVelocity;
    QLabel *LabelVelocityUnit;
    QComboBox *ComVelocitySelection;
    QLabel *LabelWedgeDelay;
    QDoubleSpinBox *ValueWedgeDelay;
    QLabel *LabelWedgeDelayUnit;
    QLabel *LabelGainUnit_2;
    QDoubleSpinBox *ValueRefGain;
    QGroupBox *BoxPulserReceiver;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QLabel *LabelPulser;
    QSpinBox *ValuePulser;
    QFrame *line_5;
    QLabel *LabelReceiver;
    QSpinBox *ValueReceiver;
    QCheckBox *CheckVideoFilter;
    QLabel *LabelViedoFilter;
    QWidget *layoutWidget91;
    QFormLayout *formLayout_2;
    QLabel *LabelFilter;
    QComboBox *ComFilter;
    QLabel *LabelTxRxMode;
    QComboBox *ComTxRxMode;
    QLabel *LabelRectifier;
    QComboBox *ComRectifier;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout;
    QLabel *LabelPointQty;
    QSpinBox *ValuePointQty;
    QLabel *LabelSumGain;
    QDoubleSpinBox *ValueSumGain;
    QLabel *LabelSumGainUnit;
    QWidget *layoutWidget111;
    QHBoxLayout *horizontalLayout_123;
    QLabel *LabelAverage;
    QComboBox *ComAverage;
    QCheckBox *CheckSumGainAuto;
    QCheckBox *CheckPointQtyAuto;
    QWidget *ProbWedge;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollAreaProbeWedge;
    QWidget *scrollAreaWidgetContents_2;
    QGroupBox *BoxWedgeTrigger;
    QPushButton *BtnWedgeSelection;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_9;
    QLabel *LabelWedgeT_Line1;
    QLabel *LabelWedgeT_Line2;
    QLabel *LabelWedgeT_Line3;
    QLabel *LabelWedgeT_Line4;
    QComboBox *ComGroupMode;
    QGroupBox *BoxProbeTrigger;
    QPushButton *BtnProbeSelection;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_8;
    QLabel *LabelProbeT_Line1;
    QLabel *LabelProbeT_Line2;
    QLabel *LabelProbeT_Line3;
    QLabel *LabelProbeT_Line4;
    QLabel *LabelGroupMode;
    QGroupBox *BoxWedgeTrigger_2;
    QPushButton *BtnWedgeSelection_2;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_10;
    QLabel *LabelWedgeT_Line1_2;
    QLabel *LabelWedgeT_Line2_2;
    QLabel *LabelWedgeT_Line3_2;
    QLabel *LabelWedgeT_Line4_2;
    QGroupBox *BoxProbeTrigger_2;
    QPushButton *BtnProbeSelection_2;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_11;
    QLabel *LabelProbeT_Line1_2;
    QLabel *LabelProbeT_Line2_2;
    QLabel *LabelProbeT_Line3_2;
    QLabel *LabelProbeT_Line4_2;
    QFrame *line;
    QWidget *FocalLaw;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QGroupBox *BoxFocalPoint;
    QWidget *layoutWidget11;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LabelFocalType;
    QComboBox *ComFocalType;
    QWidget *layoutWidget12322;
    QGridLayout *gridLayout_5;
    QLabel *LabelFocalStart;
    QLabel *LabelFocalStop;
    QLabel *LabelFocalStep;
    QLabel *LabelFocalPosition;
    QDoubleSpinBox *ValueFocusPositionStart;
    QDoubleSpinBox *ValueFocusPositionStop;
    QDoubleSpinBox *ValueFocusPositionStep;
    QLabel *LabelFocusStartUnit_2;
    QLabel *LabelFocalOffset;
    QDoubleSpinBox *ValueFocusOffsetStart;
    QDoubleSpinBox *ValueFocusOffsetStop;
    QLabel *LabelFocusOffsetStartUnit;
    QLabel *LabelFocalDepth;
    QDoubleSpinBox *ValueFocusDepthStart;
    QDoubleSpinBox *ValueFocusDepthStop;
    QLabel *LabelFocusOffsetStopUnit;
    QGroupBox *BoxAperture;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_12;
    QLabel *LabelElementStart;
    QLabel *LabelElementSelect;
    QLabel *LlabelPriAxis;
    QSpinBox *ValueElementQtyPri;
    QSpinBox *ValueElementQtySec;
    QLabel *LlabelSecAxis;
    QLabel *LabelElementStop;
    QLabel *LabelElementStep;
    QSpinBox *ValueElementStartPri;
    QSpinBox *ValueElementStartSec;
    QSpinBox *ValueElementStopPri;
    QSpinBox *ValueElementStopSec;
    QSpinBox *ValueElementStepPri;
    QSpinBox *ValueElementStepSec;
    QGroupBox *BoxAngle;
    QWidget *layoutWidget123;
    QGridLayout *gridLayout_4;
    QLabel *LabelAngStart;
    QLabel *LabelAngStop;
    QLabel *LabelAngStep;
    QLabel *LabelPriSteering;
    QDoubleSpinBox *ValuePriSteerStart;
    QDoubleSpinBox *ValuePriSteerStop;
    QDoubleSpinBox *ValuePriSteerStep;
    QLabel *LabelFocusStartUnit_4;
    QLabel *LabelSecSteering;
    QDoubleSpinBox *ValueSecSteerStart;
    QDoubleSpinBox *ValueSecSteerStop;
    QDoubleSpinBox *ValueSecSteerStep;
    QLabel *LabelFocusOffsetStartUnit_3;
    QLabel *LlabelRefract;
    QDoubleSpinBox *ValueRefractStart;
    QDoubleSpinBox *ValueRefractStop;
    QDoubleSpinBox *ValueRefractStep;
    QLabel *LabelFocusOffsetStopUnit_3;
    QLabel *LlabelBeamSkew;
    QDoubleSpinBox *ValueSkewStart;
    QDoubleSpinBox *ValueSkewStop;
    QDoubleSpinBox *ValueSkewStep;
    QLabel *LabelFocusOffsetStopUnit_4;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *LabelAngleType;
    QComboBox *ComAngleType;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *LabelLawType;
    QComboBox *ComLawType;
    QPushButton *BtnProcessLaw;
    QWidget *GateSizingcurves;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollAreaGateAndCurve;
    QWidget *scrollAreaWidgetContents_4;
    QFrame *line_8;
    QLabel *LabelGate;
    QCheckBox *CheckGateShow;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_13;
    QLabel *LabelGateSelect;
    QComboBox *ComGateSelect;
    QLabel *LabelGateStart;
    QDoubleSpinBox *ValueGateStart;
    QLabel *LabelGateStartUnit;
    QLabel *LabelGateWidth;
    QDoubleSpinBox *ValueGateWidth;
    QLabel *LabelGateWidthUnit;
    QLabel *LabelGateHeight;
    QLabel *LabelGateSync;
    QComboBox *ComGateSync;
    QLabel *LabelGateMeasure;
    QComboBox *ComGateMeasure;
    QDoubleSpinBox *ValueGateHeight;
    QFrame *line_10;
    QLabel *LabelSizingCurves;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *LabelCurveSel;
    QComboBox *ComSizingCurve;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_11;
    QLabel *DacPointPos;
    QComboBox *ComCurvePointId;
    QPushButton *BtnAddPoint;
    QPushButton *BtnDelPoint;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QLabel *LabelSizingCure1;
    QDoubleSpinBox *ValueSizingCurve1;
    QLabel *LabelSizingCureUnit1;
    QLabel *LabelSizingCure2;
    QDoubleSpinBox *ValueSizingCurve2;
    QLabel *LabelSizingCureUnit2;
    QLabel *LabelSizingCure4;
    QLabel *LabelSizingCure5;
    QLabel *LabelSizingCure6;
    QDoubleSpinBox *ValueSizingCurve3;
    QDoubleSpinBox *ValueSizingCurve4;
    QDoubleSpinBox *ValueSizingCurve5;
    QDoubleSpinBox *ValueSizingCurve6;
    QLabel *LabelSizingCureUnit3;
    QLabel *LabelSizingCureUnit4;
    QLabel *LabelSizingCureUnit5;
    QLabel *LabelSizingCureUnit6;
    QLabel *LabelSizingCure3;
    QLabel *LabelSizingCure7;
    QLabel *LabelSizingCure8;
    QLabel *LabelSizingCure9;
    QLabel *LabelSizingCure10;
    QLabel *LabelSizingCure11;
    QLabel *LabelSizingCure12;
    QLabel *LabelSizingCure13;
    QLabel *LabelSizingCure14;
    QLabel *LabelSizingCure15;
    QLabel *LabelSizingCure16;
    QDoubleSpinBox *ValueSizingCurve7;
    QDoubleSpinBox *ValueSizingCurve8;
    QDoubleSpinBox *ValueSizingCurve9;
    QDoubleSpinBox *ValueSizingCurve10;
    QDoubleSpinBox *ValueSizingCurve11;
    QDoubleSpinBox *ValueSizingCurve12;
    QDoubleSpinBox *ValueSizingCurve13;
    QDoubleSpinBox *ValueSizingCurve14;
    QDoubleSpinBox *ValueSizingCurve15;
    QDoubleSpinBox *ValueSizingCurve16;
    QLabel *LabelSizingCureUnit7;
    QLabel *LabelSizingCureUnit8;
    QLabel *LabelSizingCureUnit9;
    QLabel *LabelSizingCureUnit10;
    QLabel *LabelSizingCureUnit11;
    QLabel *LabelSizingCureUnit12;
    QLabel *LabelSizingCureUnit13;
    QLabel *LabelSizingCureUnit14;
    QLabel *LabelSizingCureUnit15;
    QLabel *LabelSizingCureUnit16;
    QWidget *Geometry;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollGeometry;
    QWidget *scrollAreaWidgetContents_5;
    QWidget *layoutWidget15;
    QGridLayout *gridLayout_8;
    QLabel *LabelPartFile;
    QLabel *LabelPartFileLoad;
    QPushButton *BtnLoadPartFile;
    QCheckBox *CheckPartFileShow;
    QGroupBox *BoxPart;
    QWidget *layoutWidget14;
    QHBoxLayout *horizontalLayout_3;
    QLabel *LabelGeometry;
    QComboBox *ComGeometry;
    QCheckBox *CheckUnifiedPartSetting;
    QWidget *layoutWidget16;
    QGridLayout *gridLayout_7;
    QLabel *LabelPartSize1;
    QDoubleSpinBox *ValuePartSize1;
    QLabel *LabelPartSizeUnit1;
    QLabel *LabelPartSize2;
    QDoubleSpinBox *ValuePartSize2;
    QLabel *LabelPartSizeUnit2;
    QLabel *LabelPartSize3;
    QDoubleSpinBox *ValuePartSize3;
    QLabel *LabelPartSizeUnit3;
    QLabel *LabelMaterial;
    QComboBox *ComMaterial;
    QCheckBox *CheckShowThickness;
    QGroupBox *BoxPartTofd;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *LabelTofdScanMode;
    QComboBox *ComBoxScanMode;
    QLabel *LabelTofdProMode;
    QComboBox *ComBoxProMode;
    QLabel *LabelTofdWedgeSep;
    QDoubleSpinBox *SpinBoxWedgeSeperation;
    QLabel *LabelCursorUnit3_8;
    QLabel *LabelTofdPcs;
    QDoubleSpinBox *SpinBoxPCS;
    QLabel *LabelCursorUnit3_9;
    QLabel *LabelZeroOff;
    QDoubleSpinBox *SpinBoxZeroOff;
    QLabel *LabelCursorUnit3_6;
    QLabel *LabelDepthStart;
    QDoubleSpinBox *SpinBoxDepthStart;
    QLabel *LabelCursorUnit3_5;
    QLabel *LabelDepthEnd;
    QDoubleSpinBox *SpinBoxDepthEnd;
    QLabel *LabelCursorUnit3_7;
    QLabel *LabelTofdPcsCal;
    QDoubleSpinBox *SpinBoxCalPCS;
    QLabel *LabelCalPCSUnit;
    QLabel *LabelShowLwBw;
    QCheckBox *CheckLwBwShow;
    QGroupBox *BoxDepthCal;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_11;
    QLabel *LabelDepthCal;
    QDoubleSpinBox *SpinBoxDepthCal;
    QLabel *LabelCursorUnit3_19;
    QPushButton *BtnDepthCal;
    QGroupBox *BoxPartPosition;
    QWidget *layoutWidget13;
    QGridLayout *gridLayout_9;
    QLabel *LabelScanOffset;
    QDoubleSpinBox *ValueScanOffset;
    QLabel *LabelScanOffsetUnit;
    QLabel *LabelIndexOffset;
    QDoubleSpinBox *ValueIndexOffset;
    QLabel *LabelIndexOffsetUnit;
    QLabel *LabelSkewAngle;
    QComboBox *ComSkewAngle;
    QWidget *Measurement;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollAreaMeasure;
    QWidget *scrollAreaWidgetContents_8;
    QLabel *LabelMeasureValue;
    QFrame *line_6;
    QLabel *LabelCursor;
    QFrame *line_7;
    QCheckBox *CheckMeasureShow;
    QCheckBox *CheckCursorShow;
    QWidget *layoutWidget17;
    QGridLayout *gridLayout_15;
    QLabel *LabelField1;
    QComboBox *ComField1;
    QLabel *LabelField2;
    QComboBox *ComField2;
    QLabel *LabelField3;
    QComboBox *ComField3;
    QLabel *LabelField4;
    QComboBox *ComField4;
    QLabel *LabelField5;
    QComboBox *ComField5;
    QWidget *layoutWidget18;
    QGridLayout *gridLayout_16;
    QDoubleSpinBox *ValueARef;
    QLabel *LabelCursorUnit1;
    QLabel *label_199;
    QDoubleSpinBox *ValueAMes;
    QLabel *LabelCursorUnit2;
    QLabel *label_201;
    QDoubleSpinBox *ValueURef;
    QLabel *LabelCursorUnit3;
    QLabel *label_203;
    QDoubleSpinBox *ValueUMes;
    QLabel *LabelCursorUnit4;
    QLabel *label_205;
    QDoubleSpinBox *ValueSRef;
    QLabel *LabelCursorUnit5;
    QLabel *label_207;
    QDoubleSpinBox *ValueSMes;
    QLabel *LabelCursorUnit6;
    QLabel *label_209;
    QDoubleSpinBox *ValueIRef;
    QLabel *LabelCursorUnit7;
    QLabel *label_211;
    QDoubleSpinBox *ValueIMes;
    QLabel *LabelCursorUnit8;
    QLabel *label_197;
    QFrame *line_9;
    QLabel *LabelDefect;
    QCheckBox *CheckDefectShow;
    QWidget *layoutWidget15_2;
    QGridLayout *gridLayout_10;
    QComboBox *ComDefectIndex;
    QLabel *LabelDefectIndex;
    QLabel *labelDefectStart;
    QDoubleSpinBox *ValueDefectLStart;
    QLabel *LabelCursorUnit3_2;
    QLabel *labelDefectLength;
    QDoubleSpinBox *ValueDefectLength;
    QLabel *LabelCursorUnit3_3;
    QLabel *labelDefectDepth;
    QDoubleSpinBox *ValueDefectHStart;
    QLabel *LabelCursorUnit3_4;
    QLabel *labelDefectHeight;
    QDoubleSpinBox *ValueDefectHeight;
    QLabel *LabelCursorUnit3_10;
    QLabel *LabelCursorUnit3_11;
    QDoubleSpinBox *ValueDefectWStart;
    QLabel *labelDefectOffset;
    QDoubleSpinBox *ValueDefectWidth;
    QLabel *labelDefectWidth;
    QLabel *LabelCursorUnit3_12;
    QPushButton *BtnDefectDelete;
    QLabel *LabelReMark;
    QLineEdit *lineEditReMark;
    QCheckBox *CheckBackShow;
    QCheckBox *CheckCursorSync;
    QWidget *Display;
    QVBoxLayout *verticalLayout_12;
    QScrollArea *scrollAreaDisplay;
    QWidget *scrollAreaWidgetContents_6;
    QTreeView *treeView;
    QLabel *LabelLanguage;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *LabelCScanSource1;
    QComboBox *ComCScanSource1;
    QLabel *LabelCScanSource2;
    QComboBox *ComCScanSource2;
    QLabel *LabelCScanThickness;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *LabelCScanThicknessMin;
    QDoubleSpinBox *ValueCScanThicknessMin;
    QLabel *LabelCScanThicknessMax_3;
    QLabel *LabelCScanThicknessMax;
    QDoubleSpinBox *ValueCScanThicknessMax;
    QLabel *LabelCScanThicknessMax_2;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_14;
    QComboBox *ComColorLineSelection;
    QComboBox *ComColorLineColor;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_3;
    QLabel *LabelAmpColor;
    DopplerColorBtn *BtnColorAmp;
    QLabel *LabelColorRF;
    DopplerColorBtn *BtnColorRf;
    QLabel *label_5;
    DopplerColorBtn *BtnColorThickness;
    QComboBox *ComLanguage;
    QGroupBox *groupBoxComDisp;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *ComComDisp1;
    QComboBox *ComComDisp2;
    QComboBox *ComComDisp3;
    QComboBox *ComComDisp4;
    QPushButton *BtnRefurbishComDisp;

    void setupUi(QWidget *DopplerGroupTab)
    {
        if (DopplerGroupTab->objectName().isEmpty())
            DopplerGroupTab->setObjectName(QString::fromUtf8("DopplerGroupTab"));
        DopplerGroupTab->resize(330, 896);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DopplerGroupTab->sizePolicy().hasHeightForWidth());
        DopplerGroupTab->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        DopplerGroupTab->setFont(font);
        verticalLayout = new QVBoxLayout(DopplerGroupTab);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        toolBox = new QToolBox(DopplerGroupTab);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setMinimumSize(QSize(0, 700));
        toolBox->setBaseSize(QSize(0, 0));
        PageUtSetting = new QWidget();
        PageUtSetting->setObjectName(QString::fromUtf8("PageUtSetting"));
        PageUtSetting->setGeometry(QRect(0, 0, 330, 707));
        verticalLayout_2 = new QVBoxLayout(PageUtSetting);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollAreaUtSetting = new QScrollArea(PageUtSetting);
        scrollAreaUtSetting->setObjectName(QString::fromUtf8("scrollAreaUtSetting"));
        scrollAreaUtSetting->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollAreaUtSetting->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaUtSetting->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 318, 610));
        BoxGeneral = new QGroupBox(scrollAreaWidgetContents);
        BoxGeneral->setObjectName(QString::fromUtf8("BoxGeneral"));
        BoxGeneral->setGeometry(QRect(10, 10, 300, 211));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(BoxGeneral->sizePolicy().hasHeightForWidth());
        BoxGeneral->setSizePolicy(sizePolicy1);
        BoxGeneral->setMinimumSize(QSize(270, 0));
        BoxGeneral->setMaximumSize(QSize(300, 16777215));
        LabelTravelMode = new QLabel(BoxGeneral);
        LabelTravelMode->setObjectName(QString::fromUtf8("LabelTravelMode"));
        LabelTravelMode->setGeometry(QRect(12, 180, 81, 25));
        ComTravelMode = new QComboBox(BoxGeneral);
        ComTravelMode->setObjectName(QString::fromUtf8("ComTravelMode"));
        ComTravelMode->setGeometry(QRect(90, 180, 91, 21));
        LabelCurrentAngle = new QLabel(BoxGeneral);
        LabelCurrentAngle->setObjectName(QString::fromUtf8("LabelCurrentAngle"));
        LabelCurrentAngle->setGeometry(QRect(200, 57, 81, 25));
        ComCurrentAngle = new QComboBox(BoxGeneral);
        ComCurrentAngle->setObjectName(QString::fromUtf8("ComCurrentAngle"));
        ComCurrentAngle->setGeometry(QRect(200, 80, 91, 21));
        LabelRangeUnit = new QLabel(BoxGeneral);
        LabelRangeUnit->setObjectName(QString::fromUtf8("LabelRangeUnit"));
        LabelRangeUnit->setGeometry(QRect(160, 92, 22, 16));
        LabelStart = new QLabel(BoxGeneral);
        LabelStart->setObjectName(QString::fromUtf8("LabelStart"));
        LabelStart->setGeometry(QRect(13, 56, 75, 25));
        sizePolicy.setHeightForWidth(LabelStart->sizePolicy().hasHeightForWidth());
        LabelStart->setSizePolicy(sizePolicy);
        LabelStart->setMinimumSize(QSize(75, 25));
        ValueRange = new QDoubleSpinBox(BoxGeneral);
        ValueRange->setObjectName(QString::fromUtf8("ValueRange"));
        ValueRange->setGeometry(QRect(94, 89, 60, 20));
        sizePolicy.setHeightForWidth(ValueRange->sizePolicy().hasHeightForWidth());
        ValueRange->setSizePolicy(sizePolicy);
        ValueRange->setMinimumSize(QSize(60, 20));
        ValueRange->setMaximumSize(QSize(60, 20));
        ValueRange->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueRange->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueRange->setDecimals(1);
        ValueRange->setMinimum(1);
        ValueRange->setMaximum(5000);
        ValueRange->setSingleStep(1);
        ValueRange->setValue(100);
        LabelGain = new QLabel(BoxGeneral);
        LabelGain->setObjectName(QString::fromUtf8("LabelGain"));
        LabelGain->setGeometry(QRect(13, 27, 75, 25));
        sizePolicy.setHeightForWidth(LabelGain->sizePolicy().hasHeightForWidth());
        LabelGain->setSizePolicy(sizePolicy);
        LabelGain->setMinimumSize(QSize(75, 25));
        LabelGain->setMaximumSize(QSize(75, 20));
        ValueGain = new QDoubleSpinBox(BoxGeneral);
        ValueGain->setObjectName(QString::fromUtf8("ValueGain"));
        ValueGain->setGeometry(QRect(94, 27, 60, 20));
        sizePolicy.setHeightForWidth(ValueGain->sizePolicy().hasHeightForWidth());
        ValueGain->setSizePolicy(sizePolicy);
        ValueGain->setMinimumSize(QSize(60, 20));
        ValueGain->setMaximumSize(QSize(60, 20));
        ValueGain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueGain->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueGain->setDecimals(1);
        ValueGain->setMaximum(80);
        LabelGainUnit = new QLabel(BoxGeneral);
        LabelGainUnit->setObjectName(QString::fromUtf8("LabelGainUnit"));
        LabelGainUnit->setGeometry(QRect(160, 30, 16, 16));
        ValueStart = new QDoubleSpinBox(BoxGeneral);
        ValueStart->setObjectName(QString::fromUtf8("ValueStart"));
        ValueStart->setGeometry(QRect(94, 58, 60, 20));
        sizePolicy.setHeightForWidth(ValueStart->sizePolicy().hasHeightForWidth());
        ValueStart->setSizePolicy(sizePolicy);
        ValueStart->setMinimumSize(QSize(60, 20));
        ValueStart->setMaximumSize(QSize(60, 20));
        ValueStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueStart->setDecimals(1);
        ValueStart->setMaximum(5000);
        ValueStart->setSingleStep(1);
        LabelStartUnit = new QLabel(BoxGeneral);
        LabelStartUnit->setObjectName(QString::fromUtf8("LabelStartUnit"));
        LabelStartUnit->setGeometry(QRect(160, 61, 22, 16));
        LabelRange = new QLabel(BoxGeneral);
        LabelRange->setObjectName(QString::fromUtf8("LabelRange"));
        LabelRange->setGeometry(QRect(13, 87, 75, 25));
        sizePolicy.setHeightForWidth(LabelRange->sizePolicy().hasHeightForWidth());
        LabelRange->setSizePolicy(sizePolicy);
        LabelRange->setMinimumSize(QSize(75, 25));
        LabelVelocity = new QLabel(BoxGeneral);
        LabelVelocity->setObjectName(QString::fromUtf8("LabelVelocity"));
        LabelVelocity->setGeometry(QRect(13, 118, 75, 25));
        sizePolicy.setHeightForWidth(LabelVelocity->sizePolicy().hasHeightForWidth());
        LabelVelocity->setSizePolicy(sizePolicy);
        LabelVelocity->setMinimumSize(QSize(75, 25));
        ValueVelocity = new QDoubleSpinBox(BoxGeneral);
        ValueVelocity->setObjectName(QString::fromUtf8("ValueVelocity"));
        ValueVelocity->setGeometry(QRect(94, 120, 60, 20));
        sizePolicy.setHeightForWidth(ValueVelocity->sizePolicy().hasHeightForWidth());
        ValueVelocity->setSizePolicy(sizePolicy);
        ValueVelocity->setMinimumSize(QSize(60, 20));
        ValueVelocity->setMaximumSize(QSize(60, 20));
        ValueVelocity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueVelocity->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueVelocity->setDecimals(0);
        ValueVelocity->setMinimum(0);
        ValueVelocity->setMaximum(50000);
        ValueVelocity->setSingleStep(100);
        ValueVelocity->setValue(5920);
        LabelVelocityUnit = new QLabel(BoxGeneral);
        LabelVelocityUnit->setObjectName(QString::fromUtf8("LabelVelocityUnit"));
        LabelVelocityUnit->setGeometry(QRect(160, 123, 21, 16));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LabelVelocityUnit->sizePolicy().hasHeightForWidth());
        LabelVelocityUnit->setSizePolicy(sizePolicy2);
        ComVelocitySelection = new QComboBox(BoxGeneral);
        ComVelocitySelection->setObjectName(QString::fromUtf8("ComVelocitySelection"));
        ComVelocitySelection->setGeometry(QRect(188, 120, 100, 20));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ComVelocitySelection->sizePolicy().hasHeightForWidth());
        ComVelocitySelection->setSizePolicy(sizePolicy3);
        ComVelocitySelection->setMinimumSize(QSize(100, 20));
        ComVelocitySelection->setMaximumSize(QSize(100, 20));
        LabelWedgeDelay = new QLabel(BoxGeneral);
        LabelWedgeDelay->setObjectName(QString::fromUtf8("LabelWedgeDelay"));
        LabelWedgeDelay->setGeometry(QRect(13, 149, 75, 25));
        sizePolicy.setHeightForWidth(LabelWedgeDelay->sizePolicy().hasHeightForWidth());
        LabelWedgeDelay->setSizePolicy(sizePolicy);
        LabelWedgeDelay->setMinimumSize(QSize(75, 25));
        ValueWedgeDelay = new QDoubleSpinBox(BoxGeneral);
        ValueWedgeDelay->setObjectName(QString::fromUtf8("ValueWedgeDelay"));
        ValueWedgeDelay->setGeometry(QRect(94, 151, 60, 20));
        sizePolicy.setHeightForWidth(ValueWedgeDelay->sizePolicy().hasHeightForWidth());
        ValueWedgeDelay->setSizePolicy(sizePolicy);
        ValueWedgeDelay->setMinimumSize(QSize(60, 10));
        ValueWedgeDelay->setMaximumSize(QSize(60, 20));
        ValueWedgeDelay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueWedgeDelay->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueWedgeDelay->setDecimals(2);
        LabelWedgeDelayUnit = new QLabel(BoxGeneral);
        LabelWedgeDelayUnit->setObjectName(QString::fromUtf8("LabelWedgeDelayUnit"));
        LabelWedgeDelayUnit->setGeometry(QRect(160, 154, 16, 16));
        LabelGainUnit_2 = new QLabel(BoxGeneral);
        LabelGainUnit_2->setObjectName(QString::fromUtf8("LabelGainUnit_2"));
        LabelGainUnit_2->setGeometry(QRect(270, 30, 16, 16));
        ValueRefGain = new QDoubleSpinBox(BoxGeneral);
        ValueRefGain->setObjectName(QString::fromUtf8("ValueRefGain"));
        ValueRefGain->setGeometry(QRect(204, 27, 60, 20));
        sizePolicy.setHeightForWidth(ValueRefGain->sizePolicy().hasHeightForWidth());
        ValueRefGain->setSizePolicy(sizePolicy);
        ValueRefGain->setMinimumSize(QSize(60, 20));
        ValueRefGain->setMaximumSize(QSize(60, 20));
        ValueRefGain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueRefGain->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueRefGain->setDecimals(1);
        ValueRefGain->setMinimum(-20);
        ValueRefGain->setMaximum(20);
        BoxPulserReceiver = new QGroupBox(scrollAreaWidgetContents);
        BoxPulserReceiver->setObjectName(QString::fromUtf8("BoxPulserReceiver"));
        BoxPulserReceiver->setGeometry(QRect(10, 230, 300, 161));
        BoxPulserReceiver->setMaximumSize(QSize(300, 16777215));
        layoutWidget2 = new QWidget(BoxPulserReceiver);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(11, 20, 259, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LabelPulser = new QLabel(layoutWidget2);
        LabelPulser->setObjectName(QString::fromUtf8("LabelPulser"));
        sizePolicy.setHeightForWidth(LabelPulser->sizePolicy().hasHeightForWidth());
        LabelPulser->setSizePolicy(sizePolicy);
        LabelPulser->setMinimumSize(QSize(60, 25));
        LabelPulser->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(LabelPulser);

        ValuePulser = new QSpinBox(layoutWidget2);
        ValuePulser->setObjectName(QString::fromUtf8("ValuePulser"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ValuePulser->sizePolicy().hasHeightForWidth());
        ValuePulser->setSizePolicy(sizePolicy4);
        ValuePulser->setMinimumSize(QSize(50, 20));
        ValuePulser->setMaximumSize(QSize(16777215, 20));
        ValuePulser->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePulser->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePulser->setMinimum(1);
        ValuePulser->setMaximum(128);

        horizontalLayout->addWidget(ValuePulser);

        line_5 = new QFrame(layoutWidget2);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        LabelReceiver = new QLabel(layoutWidget2);
        LabelReceiver->setObjectName(QString::fromUtf8("LabelReceiver"));
        sizePolicy.setHeightForWidth(LabelReceiver->sizePolicy().hasHeightForWidth());
        LabelReceiver->setSizePolicy(sizePolicy);
        LabelReceiver->setMinimumSize(QSize(70, 25));
        LabelReceiver->setMaximumSize(QSize(70, 20));

        horizontalLayout->addWidget(LabelReceiver);

        ValueReceiver = new QSpinBox(layoutWidget2);
        ValueReceiver->setObjectName(QString::fromUtf8("ValueReceiver"));
        sizePolicy4.setHeightForWidth(ValueReceiver->sizePolicy().hasHeightForWidth());
        ValueReceiver->setSizePolicy(sizePolicy4);
        ValueReceiver->setMinimumSize(QSize(50, 20));
        ValueReceiver->setMaximumSize(QSize(16777215, 20));
        ValueReceiver->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueReceiver->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueReceiver->setMinimum(1);
        ValueReceiver->setMaximum(128);

        horizontalLayout->addWidget(ValueReceiver);

        CheckVideoFilter = new QCheckBox(BoxPulserReceiver);
        CheckVideoFilter->setObjectName(QString::fromUtf8("CheckVideoFilter"));
        CheckVideoFilter->setGeometry(QRect(92, 134, 54, 19));
        LabelViedoFilter = new QLabel(BoxPulserReceiver);
        LabelViedoFilter->setObjectName(QString::fromUtf8("LabelViedoFilter"));
        LabelViedoFilter->setGeometry(QRect(11, 133, 75, 25));
        sizePolicy.setHeightForWidth(LabelViedoFilter->sizePolicy().hasHeightForWidth());
        LabelViedoFilter->setSizePolicy(sizePolicy);
        LabelViedoFilter->setMinimumSize(QSize(75, 25));
        layoutWidget91 = new QWidget(BoxPulserReceiver);
        layoutWidget91->setObjectName(QString::fromUtf8("layoutWidget91"));
        layoutWidget91->setGeometry(QRect(10, 50, 261, 89));
        formLayout_2 = new QFormLayout(layoutWidget91);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        LabelFilter = new QLabel(layoutWidget91);
        LabelFilter->setObjectName(QString::fromUtf8("LabelFilter"));
        sizePolicy.setHeightForWidth(LabelFilter->sizePolicy().hasHeightForWidth());
        LabelFilter->setSizePolicy(sizePolicy);
        LabelFilter->setMinimumSize(QSize(75, 25));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, LabelFilter);

        ComFilter = new QComboBox(layoutWidget91);
        ComFilter->setObjectName(QString::fromUtf8("ComFilter"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, ComFilter);

        LabelTxRxMode = new QLabel(layoutWidget91);
        LabelTxRxMode->setObjectName(QString::fromUtf8("LabelTxRxMode"));
        sizePolicy.setHeightForWidth(LabelTxRxMode->sizePolicy().hasHeightForWidth());
        LabelTxRxMode->setSizePolicy(sizePolicy);
        LabelTxRxMode->setMinimumSize(QSize(75, 25));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, LabelTxRxMode);

        ComTxRxMode = new QComboBox(layoutWidget91);
        ComTxRxMode->setObjectName(QString::fromUtf8("ComTxRxMode"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, ComTxRxMode);

        LabelRectifier = new QLabel(layoutWidget91);
        LabelRectifier->setObjectName(QString::fromUtf8("LabelRectifier"));
        sizePolicy.setHeightForWidth(LabelRectifier->sizePolicy().hasHeightForWidth());
        LabelRectifier->setSizePolicy(sizePolicy);
        LabelRectifier->setMinimumSize(QSize(75, 25));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, LabelRectifier);

        ComRectifier = new QComboBox(layoutWidget91);
        ComRectifier->setObjectName(QString::fromUtf8("ComRectifier"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, ComRectifier);

        layoutWidget4 = new QWidget(scrollAreaWidgetContents);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(20, 403, 181, 58));
        gridLayout = new QGridLayout(layoutWidget4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        LabelPointQty = new QLabel(layoutWidget4);
        LabelPointQty->setObjectName(QString::fromUtf8("LabelPointQty"));
        sizePolicy.setHeightForWidth(LabelPointQty->sizePolicy().hasHeightForWidth());
        LabelPointQty->setSizePolicy(sizePolicy);
        LabelPointQty->setMinimumSize(QSize(80, 25));
        LabelPointQty->setMaximumSize(QSize(70, 20));

        gridLayout->addWidget(LabelPointQty, 0, 0, 1, 1);

        ValuePointQty = new QSpinBox(layoutWidget4);
        ValuePointQty->setObjectName(QString::fromUtf8("ValuePointQty"));
        sizePolicy4.setHeightForWidth(ValuePointQty->sizePolicy().hasHeightForWidth());
        ValuePointQty->setSizePolicy(sizePolicy4);
        ValuePointQty->setMinimumSize(QSize(50, 20));
        ValuePointQty->setMaximumSize(QSize(16777215, 20));
        ValuePointQty->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePointQty->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePointQty->setMinimum(1);
        ValuePointQty->setMaximum(8192);

        gridLayout->addWidget(ValuePointQty, 0, 1, 1, 1);

        LabelSumGain = new QLabel(layoutWidget4);
        LabelSumGain->setObjectName(QString::fromUtf8("LabelSumGain"));
        sizePolicy.setHeightForWidth(LabelSumGain->sizePolicy().hasHeightForWidth());
        LabelSumGain->setSizePolicy(sizePolicy);
        LabelSumGain->setMinimumSize(QSize(80, 25));
        LabelSumGain->setMaximumSize(QSize(75, 20));

        gridLayout->addWidget(LabelSumGain, 1, 0, 1, 1);

        ValueSumGain = new QDoubleSpinBox(layoutWidget4);
        ValueSumGain->setObjectName(QString::fromUtf8("ValueSumGain"));
        sizePolicy.setHeightForWidth(ValueSumGain->sizePolicy().hasHeightForWidth());
        ValueSumGain->setSizePolicy(sizePolicy);
        ValueSumGain->setMinimumSize(QSize(60, 20));
        ValueSumGain->setMaximumSize(QSize(60, 20));
        ValueSumGain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSumGain->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSumGain->setDecimals(1);
        ValueSumGain->setMinimum(20);
        ValueSumGain->setMaximum(48);

        gridLayout->addWidget(ValueSumGain, 1, 1, 1, 1);

        LabelSumGainUnit = new QLabel(layoutWidget4);
        LabelSumGainUnit->setObjectName(QString::fromUtf8("LabelSumGainUnit"));

        gridLayout->addWidget(LabelSumGainUnit, 1, 2, 1, 1);

        layoutWidget111 = new QWidget(scrollAreaWidgetContents);
        layoutWidget111->setObjectName(QString::fromUtf8("layoutWidget111"));
        layoutWidget111->setGeometry(QRect(21, 463, 151, 30));
        horizontalLayout_123 = new QHBoxLayout(layoutWidget111);
        horizontalLayout_123->setObjectName(QString::fromUtf8("horizontalLayout_123"));
        horizontalLayout_123->setContentsMargins(0, 0, 0, 0);
        LabelAverage = new QLabel(layoutWidget111);
        LabelAverage->setObjectName(QString::fromUtf8("LabelAverage"));
        sizePolicy.setHeightForWidth(LabelAverage->sizePolicy().hasHeightForWidth());
        LabelAverage->setSizePolicy(sizePolicy);
        LabelAverage->setMinimumSize(QSize(75, 25));

        horizontalLayout_123->addWidget(LabelAverage);

        ComAverage = new QComboBox(layoutWidget111);
        ComAverage->setObjectName(QString::fromUtf8("ComAverage"));

        horizontalLayout_123->addWidget(ComAverage);

        CheckSumGainAuto = new QCheckBox(scrollAreaWidgetContents);
        CheckSumGainAuto->setObjectName(QString::fromUtf8("CheckSumGainAuto"));
        CheckSumGainAuto->setGeometry(QRect(212, 440, 54, 19));
        CheckPointQtyAuto = new QCheckBox(scrollAreaWidgetContents);
        CheckPointQtyAuto->setObjectName(QString::fromUtf8("CheckPointQtyAuto"));
        CheckPointQtyAuto->setGeometry(QRect(212, 410, 54, 19));
        scrollAreaUtSetting->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollAreaUtSetting);

        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(PageUtSetting, icon, QString::fromUtf8("Ut Setting"));
        ProbWedge = new QWidget();
        ProbWedge->setObjectName(QString::fromUtf8("ProbWedge"));
        ProbWedge->setGeometry(QRect(0, 0, 330, 707));
        verticalLayout_3 = new QVBoxLayout(ProbWedge);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollAreaProbeWedge = new QScrollArea(ProbWedge);
        scrollAreaProbeWedge->setObjectName(QString::fromUtf8("scrollAreaProbeWedge"));
        scrollAreaProbeWedge->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaProbeWedge->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 335, 610));
        BoxWedgeTrigger = new QGroupBox(scrollAreaWidgetContents_2);
        BoxWedgeTrigger->setObjectName(QString::fromUtf8("BoxWedgeTrigger"));
        BoxWedgeTrigger->setGeometry(QRect(10, 180, 301, 141));
        BtnWedgeSelection = new QPushButton(BoxWedgeTrigger);
        BtnWedgeSelection->setObjectName(QString::fromUtf8("BtnWedgeSelection"));
        BtnWedgeSelection->setGeometry(QRect(10, 18, 281, 23));
        layoutWidget5 = new QWidget(BoxWedgeTrigger);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(10, 44, 281, 92));
        verticalLayout_9 = new QVBoxLayout(layoutWidget5);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        LabelWedgeT_Line1 = new QLabel(layoutWidget5);
        LabelWedgeT_Line1->setObjectName(QString::fromUtf8("LabelWedgeT_Line1"));

        verticalLayout_9->addWidget(LabelWedgeT_Line1);

        LabelWedgeT_Line2 = new QLabel(layoutWidget5);
        LabelWedgeT_Line2->setObjectName(QString::fromUtf8("LabelWedgeT_Line2"));

        verticalLayout_9->addWidget(LabelWedgeT_Line2);

        LabelWedgeT_Line3 = new QLabel(layoutWidget5);
        LabelWedgeT_Line3->setObjectName(QString::fromUtf8("LabelWedgeT_Line3"));

        verticalLayout_9->addWidget(LabelWedgeT_Line3);

        LabelWedgeT_Line4 = new QLabel(layoutWidget5);
        LabelWedgeT_Line4->setObjectName(QString::fromUtf8("LabelWedgeT_Line4"));

        verticalLayout_9->addWidget(LabelWedgeT_Line4);

        ComGroupMode = new QComboBox(scrollAreaWidgetContents_2);
        ComGroupMode->setObjectName(QString::fromUtf8("ComGroupMode"));
        ComGroupMode->setGeometry(QRect(100, 10, 131, 21));
        BoxProbeTrigger = new QGroupBox(scrollAreaWidgetContents_2);
        BoxProbeTrigger->setObjectName(QString::fromUtf8("BoxProbeTrigger"));
        BoxProbeTrigger->setGeometry(QRect(10, 40, 301, 141));
        BtnProbeSelection = new QPushButton(BoxProbeTrigger);
        BtnProbeSelection->setObjectName(QString::fromUtf8("BtnProbeSelection"));
        BtnProbeSelection->setGeometry(QRect(10, 18, 281, 23));
        layoutWidget6 = new QWidget(BoxProbeTrigger);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 44, 281, 92));
        verticalLayout_8 = new QVBoxLayout(layoutWidget6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        LabelProbeT_Line1 = new QLabel(layoutWidget6);
        LabelProbeT_Line1->setObjectName(QString::fromUtf8("LabelProbeT_Line1"));

        verticalLayout_8->addWidget(LabelProbeT_Line1);

        LabelProbeT_Line2 = new QLabel(layoutWidget6);
        LabelProbeT_Line2->setObjectName(QString::fromUtf8("LabelProbeT_Line2"));

        verticalLayout_8->addWidget(LabelProbeT_Line2);

        LabelProbeT_Line3 = new QLabel(layoutWidget6);
        LabelProbeT_Line3->setObjectName(QString::fromUtf8("LabelProbeT_Line3"));

        verticalLayout_8->addWidget(LabelProbeT_Line3);

        LabelProbeT_Line4 = new QLabel(layoutWidget6);
        LabelProbeT_Line4->setObjectName(QString::fromUtf8("LabelProbeT_Line4"));

        verticalLayout_8->addWidget(LabelProbeT_Line4);

        LabelGroupMode = new QLabel(scrollAreaWidgetContents_2);
        LabelGroupMode->setObjectName(QString::fromUtf8("LabelGroupMode"));
        LabelGroupMode->setGeometry(QRect(20, 11, 75, 25));
        sizePolicy.setHeightForWidth(LabelGroupMode->sizePolicy().hasHeightForWidth());
        LabelGroupMode->setSizePolicy(sizePolicy);
        LabelGroupMode->setMinimumSize(QSize(75, 25));
        BoxWedgeTrigger_2 = new QGroupBox(scrollAreaWidgetContents_2);
        BoxWedgeTrigger_2->setObjectName(QString::fromUtf8("BoxWedgeTrigger_2"));
        BoxWedgeTrigger_2->setGeometry(QRect(10, 470, 301, 151));
        BtnWedgeSelection_2 = new QPushButton(BoxWedgeTrigger_2);
        BtnWedgeSelection_2->setObjectName(QString::fromUtf8("BtnWedgeSelection_2"));
        BtnWedgeSelection_2->setGeometry(QRect(10, 18, 281, 23));
        layoutWidget7 = new QWidget(BoxWedgeTrigger_2);
        layoutWidget7->setObjectName(QString::fromUtf8("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(10, 44, 281, 92));
        verticalLayout_10 = new QVBoxLayout(layoutWidget7);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        LabelWedgeT_Line1_2 = new QLabel(layoutWidget7);
        LabelWedgeT_Line1_2->setObjectName(QString::fromUtf8("LabelWedgeT_Line1_2"));

        verticalLayout_10->addWidget(LabelWedgeT_Line1_2);

        LabelWedgeT_Line2_2 = new QLabel(layoutWidget7);
        LabelWedgeT_Line2_2->setObjectName(QString::fromUtf8("LabelWedgeT_Line2_2"));

        verticalLayout_10->addWidget(LabelWedgeT_Line2_2);

        LabelWedgeT_Line3_2 = new QLabel(layoutWidget7);
        LabelWedgeT_Line3_2->setObjectName(QString::fromUtf8("LabelWedgeT_Line3_2"));

        verticalLayout_10->addWidget(LabelWedgeT_Line3_2);

        LabelWedgeT_Line4_2 = new QLabel(layoutWidget7);
        LabelWedgeT_Line4_2->setObjectName(QString::fromUtf8("LabelWedgeT_Line4_2"));

        verticalLayout_10->addWidget(LabelWedgeT_Line4_2);

        BoxProbeTrigger_2 = new QGroupBox(scrollAreaWidgetContents_2);
        BoxProbeTrigger_2->setObjectName(QString::fromUtf8("BoxProbeTrigger_2"));
        BoxProbeTrigger_2->setGeometry(QRect(10, 330, 301, 141));
        BtnProbeSelection_2 = new QPushButton(BoxProbeTrigger_2);
        BtnProbeSelection_2->setObjectName(QString::fromUtf8("BtnProbeSelection_2"));
        BtnProbeSelection_2->setGeometry(QRect(10, 18, 281, 23));
        layoutWidget8 = new QWidget(BoxProbeTrigger_2);
        layoutWidget8->setObjectName(QString::fromUtf8("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(10, 44, 281, 92));
        verticalLayout_11 = new QVBoxLayout(layoutWidget8);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        LabelProbeT_Line1_2 = new QLabel(layoutWidget8);
        LabelProbeT_Line1_2->setObjectName(QString::fromUtf8("LabelProbeT_Line1_2"));

        verticalLayout_11->addWidget(LabelProbeT_Line1_2);

        LabelProbeT_Line2_2 = new QLabel(layoutWidget8);
        LabelProbeT_Line2_2->setObjectName(QString::fromUtf8("LabelProbeT_Line2_2"));

        verticalLayout_11->addWidget(LabelProbeT_Line2_2);

        LabelProbeT_Line3_2 = new QLabel(layoutWidget8);
        LabelProbeT_Line3_2->setObjectName(QString::fromUtf8("LabelProbeT_Line3_2"));

        verticalLayout_11->addWidget(LabelProbeT_Line3_2);

        LabelProbeT_Line4_2 = new QLabel(layoutWidget8);
        LabelProbeT_Line4_2->setObjectName(QString::fromUtf8("LabelProbeT_Line4_2"));

        verticalLayout_11->addWidget(LabelProbeT_Line4_2);

        line = new QFrame(scrollAreaWidgetContents_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(5, 320, 321, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        scrollAreaProbeWedge->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(scrollAreaProbeWedge);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-02.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(ProbWedge, icon1, QString::fromUtf8("Probe/Wedge"));
        FocalLaw = new QWidget();
        FocalLaw->setObjectName(QString::fromUtf8("FocalLaw"));
        FocalLaw->setGeometry(QRect(0, 0, 330, 707));
        verticalLayout_4 = new QVBoxLayout(FocalLaw);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea = new QScrollArea(FocalLaw);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 600));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 326, 703));
        BoxFocalPoint = new QGroupBox(scrollAreaWidgetContents_3);
        BoxFocalPoint->setObjectName(QString::fromUtf8("BoxFocalPoint"));
        BoxFocalPoint->setGeometry(QRect(2, 246, 331, 161));
        layoutWidget11 = new QWidget(BoxFocalPoint);
        layoutWidget11->setObjectName(QString::fromUtf8("layoutWidget11"));
        layoutWidget11->setGeometry(QRect(20, 18, 241, 30));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        LabelFocalType = new QLabel(layoutWidget11);
        LabelFocalType->setObjectName(QString::fromUtf8("LabelFocalType"));
        sizePolicy.setHeightForWidth(LabelFocalType->sizePolicy().hasHeightForWidth());
        LabelFocalType->setSizePolicy(sizePolicy);
        LabelFocalType->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(LabelFocalType);

        ComFocalType = new QComboBox(layoutWidget11);
        ComFocalType->setObjectName(QString::fromUtf8("ComFocalType"));

        horizontalLayout_2->addWidget(ComFocalType);

        layoutWidget12322 = new QWidget(BoxFocalPoint);
        layoutWidget12322->setObjectName(QString::fromUtf8("layoutWidget12322"));
        layoutWidget12322->setGeometry(QRect(3, 52, 296, 101));
        gridLayout_5 = new QGridLayout(layoutWidget12322);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        LabelFocalStart = new QLabel(layoutWidget12322);
        LabelFocalStart->setObjectName(QString::fromUtf8("LabelFocalStart"));

        gridLayout_5->addWidget(LabelFocalStart, 0, 1, 1, 1);

        LabelFocalStop = new QLabel(layoutWidget12322);
        LabelFocalStop->setObjectName(QString::fromUtf8("LabelFocalStop"));

        gridLayout_5->addWidget(LabelFocalStop, 0, 2, 1, 1);

        LabelFocalStep = new QLabel(layoutWidget12322);
        LabelFocalStep->setObjectName(QString::fromUtf8("LabelFocalStep"));

        gridLayout_5->addWidget(LabelFocalStep, 0, 3, 1, 1);

        LabelFocalPosition = new QLabel(layoutWidget12322);
        LabelFocalPosition->setObjectName(QString::fromUtf8("LabelFocalPosition"));

        gridLayout_5->addWidget(LabelFocalPosition, 1, 0, 1, 1);

        ValueFocusPositionStart = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusPositionStart->setObjectName(QString::fromUtf8("ValueFocusPositionStart"));
        ValueFocusPositionStart->setFrame(true);
        ValueFocusPositionStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusPositionStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusPositionStart->setKeyboardTracking(true);
        ValueFocusPositionStart->setDecimals(1);
        ValueFocusPositionStart->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusPositionStart, 1, 1, 1, 1);

        ValueFocusPositionStop = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusPositionStop->setObjectName(QString::fromUtf8("ValueFocusPositionStop"));
        ValueFocusPositionStop->setFrame(true);
        ValueFocusPositionStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusPositionStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusPositionStop->setKeyboardTracking(true);
        ValueFocusPositionStop->setDecimals(1);
        ValueFocusPositionStop->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusPositionStop, 1, 2, 1, 1);

        ValueFocusPositionStep = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusPositionStep->setObjectName(QString::fromUtf8("ValueFocusPositionStep"));
        ValueFocusPositionStep->setFrame(true);
        ValueFocusPositionStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusPositionStep->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusPositionStep->setKeyboardTracking(true);
        ValueFocusPositionStep->setDecimals(1);
        ValueFocusPositionStep->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusPositionStep, 1, 3, 1, 1);

        LabelFocusStartUnit_2 = new QLabel(layoutWidget12322);
        LabelFocusStartUnit_2->setObjectName(QString::fromUtf8("LabelFocusStartUnit_2"));

        gridLayout_5->addWidget(LabelFocusStartUnit_2, 1, 4, 1, 1);

        LabelFocalOffset = new QLabel(layoutWidget12322);
        LabelFocalOffset->setObjectName(QString::fromUtf8("LabelFocalOffset"));

        gridLayout_5->addWidget(LabelFocalOffset, 2, 0, 1, 1);

        ValueFocusOffsetStart = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusOffsetStart->setObjectName(QString::fromUtf8("ValueFocusOffsetStart"));
        ValueFocusOffsetStart->setFrame(true);
        ValueFocusOffsetStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusOffsetStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusOffsetStart->setKeyboardTracking(true);
        ValueFocusOffsetStart->setDecimals(1);
        ValueFocusOffsetStart->setMinimum(-5000);
        ValueFocusOffsetStart->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusOffsetStart, 2, 1, 1, 1);

        ValueFocusOffsetStop = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusOffsetStop->setObjectName(QString::fromUtf8("ValueFocusOffsetStop"));
        ValueFocusOffsetStop->setFrame(true);
        ValueFocusOffsetStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusOffsetStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusOffsetStop->setKeyboardTracking(true);
        ValueFocusOffsetStop->setDecimals(1);
        ValueFocusOffsetStop->setMinimum(-5000);
        ValueFocusOffsetStop->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusOffsetStop, 2, 2, 1, 1);

        LabelFocusOffsetStartUnit = new QLabel(layoutWidget12322);
        LabelFocusOffsetStartUnit->setObjectName(QString::fromUtf8("LabelFocusOffsetStartUnit"));

        gridLayout_5->addWidget(LabelFocusOffsetStartUnit, 2, 3, 1, 1);

        LabelFocalDepth = new QLabel(layoutWidget12322);
        LabelFocalDepth->setObjectName(QString::fromUtf8("LabelFocalDepth"));

        gridLayout_5->addWidget(LabelFocalDepth, 3, 0, 1, 1);

        ValueFocusDepthStart = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusDepthStart->setObjectName(QString::fromUtf8("ValueFocusDepthStart"));
        ValueFocusDepthStart->setFrame(true);
        ValueFocusDepthStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusDepthStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusDepthStart->setKeyboardTracking(true);
        ValueFocusDepthStart->setDecimals(1);
        ValueFocusDepthStart->setMinimum(-5000);
        ValueFocusDepthStart->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusDepthStart, 3, 1, 1, 1);

        ValueFocusDepthStop = new QDoubleSpinBox(layoutWidget12322);
        ValueFocusDepthStop->setObjectName(QString::fromUtf8("ValueFocusDepthStop"));
        ValueFocusDepthStop->setFrame(true);
        ValueFocusDepthStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueFocusDepthStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueFocusDepthStop->setKeyboardTracking(true);
        ValueFocusDepthStop->setDecimals(1);
        ValueFocusDepthStop->setMinimum(-5000);
        ValueFocusDepthStop->setMaximum(5000);

        gridLayout_5->addWidget(ValueFocusDepthStop, 3, 2, 1, 1);

        LabelFocusOffsetStopUnit = new QLabel(layoutWidget12322);
        LabelFocusOffsetStopUnit->setObjectName(QString::fromUtf8("LabelFocusOffsetStopUnit"));

        gridLayout_5->addWidget(LabelFocusOffsetStopUnit, 3, 3, 1, 1);

        BoxAperture = new QGroupBox(scrollAreaWidgetContents_3);
        BoxAperture->setObjectName(QString::fromUtf8("BoxAperture"));
        BoxAperture->setGeometry(QRect(2, 417, 331, 161));
        gridLayoutWidget_3 = new QWidget(BoxAperture);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(4, 14, 241, 141));
        gridLayout_12 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        LabelElementStart = new QLabel(gridLayoutWidget_3);
        LabelElementStart->setObjectName(QString::fromUtf8("LabelElementStart"));
        sizePolicy.setHeightForWidth(LabelElementStart->sizePolicy().hasHeightForWidth());
        LabelElementStart->setSizePolicy(sizePolicy);
        LabelElementStart->setMinimumSize(QSize(81, 25));
        LabelElementStart->setMaximumSize(QSize(70, 20));

        gridLayout_12->addWidget(LabelElementStart, 3, 0, 1, 1);

        LabelElementSelect = new QLabel(gridLayoutWidget_3);
        LabelElementSelect->setObjectName(QString::fromUtf8("LabelElementSelect"));
        sizePolicy2.setHeightForWidth(LabelElementSelect->sizePolicy().hasHeightForWidth());
        LabelElementSelect->setSizePolicy(sizePolicy2);
        LabelElementSelect->setMinimumSize(QSize(104, 25));
        LabelElementSelect->setMaximumSize(QSize(70, 20));

        gridLayout_12->addWidget(LabelElementSelect, 2, 0, 1, 1);

        LlabelPriAxis = new QLabel(gridLayoutWidget_3);
        LlabelPriAxis->setObjectName(QString::fromUtf8("LlabelPriAxis"));

        gridLayout_12->addWidget(LlabelPriAxis, 0, 1, 1, 1);

        ValueElementQtyPri = new QSpinBox(gridLayoutWidget_3);
        ValueElementQtyPri->setObjectName(QString::fromUtf8("ValueElementQtyPri"));
        sizePolicy4.setHeightForWidth(ValueElementQtyPri->sizePolicy().hasHeightForWidth());
        ValueElementQtyPri->setSizePolicy(sizePolicy4);
        ValueElementQtyPri->setMinimumSize(QSize(50, 20));
        ValueElementQtyPri->setMaximumSize(QSize(16777215, 20));
        ValueElementQtyPri->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementQtyPri->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementQtyPri->setMinimum(1);
        ValueElementQtyPri->setMaximum(32);

        gridLayout_12->addWidget(ValueElementQtyPri, 2, 1, 1, 1);

        ValueElementQtySec = new QSpinBox(gridLayoutWidget_3);
        ValueElementQtySec->setObjectName(QString::fromUtf8("ValueElementQtySec"));
        sizePolicy4.setHeightForWidth(ValueElementQtySec->sizePolicy().hasHeightForWidth());
        ValueElementQtySec->setSizePolicy(sizePolicy4);
        ValueElementQtySec->setMinimumSize(QSize(50, 20));
        ValueElementQtySec->setMaximumSize(QSize(16777215, 20));
        ValueElementQtySec->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementQtySec->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementQtySec->setMinimum(1);
        ValueElementQtySec->setMaximum(32);

        gridLayout_12->addWidget(ValueElementQtySec, 2, 2, 1, 1);

        LlabelSecAxis = new QLabel(gridLayoutWidget_3);
        LlabelSecAxis->setObjectName(QString::fromUtf8("LlabelSecAxis"));

        gridLayout_12->addWidget(LlabelSecAxis, 0, 2, 1, 1);

        LabelElementStop = new QLabel(gridLayoutWidget_3);
        LabelElementStop->setObjectName(QString::fromUtf8("LabelElementStop"));
        sizePolicy.setHeightForWidth(LabelElementStop->sizePolicy().hasHeightForWidth());
        LabelElementStop->setSizePolicy(sizePolicy);
        LabelElementStop->setMinimumSize(QSize(81, 25));
        LabelElementStop->setMaximumSize(QSize(70, 20));

        gridLayout_12->addWidget(LabelElementStop, 4, 0, 1, 1);

        LabelElementStep = new QLabel(gridLayoutWidget_3);
        LabelElementStep->setObjectName(QString::fromUtf8("LabelElementStep"));
        sizePolicy.setHeightForWidth(LabelElementStep->sizePolicy().hasHeightForWidth());
        LabelElementStep->setSizePolicy(sizePolicy);
        LabelElementStep->setMinimumSize(QSize(81, 25));
        LabelElementStep->setMaximumSize(QSize(70, 20));

        gridLayout_12->addWidget(LabelElementStep, 5, 0, 1, 1);

        ValueElementStartPri = new QSpinBox(gridLayoutWidget_3);
        ValueElementStartPri->setObjectName(QString::fromUtf8("ValueElementStartPri"));
        sizePolicy4.setHeightForWidth(ValueElementStartPri->sizePolicy().hasHeightForWidth());
        ValueElementStartPri->setSizePolicy(sizePolicy4);
        ValueElementStartPri->setMinimumSize(QSize(50, 20));
        ValueElementStartPri->setMaximumSize(QSize(16777215, 20));
        ValueElementStartPri->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementStartPri->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementStartPri->setMinimum(1);
        ValueElementStartPri->setMaximum(128);

        gridLayout_12->addWidget(ValueElementStartPri, 3, 1, 1, 1);

        ValueElementStartSec = new QSpinBox(gridLayoutWidget_3);
        ValueElementStartSec->setObjectName(QString::fromUtf8("ValueElementStartSec"));
        sizePolicy4.setHeightForWidth(ValueElementStartSec->sizePolicy().hasHeightForWidth());
        ValueElementStartSec->setSizePolicy(sizePolicy4);
        ValueElementStartSec->setMinimumSize(QSize(50, 20));
        ValueElementStartSec->setMaximumSize(QSize(16777215, 20));
        ValueElementStartSec->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementStartSec->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementStartSec->setMinimum(1);
        ValueElementStartSec->setMaximum(128);

        gridLayout_12->addWidget(ValueElementStartSec, 3, 2, 1, 1);

        ValueElementStopPri = new QSpinBox(gridLayoutWidget_3);
        ValueElementStopPri->setObjectName(QString::fromUtf8("ValueElementStopPri"));
        sizePolicy4.setHeightForWidth(ValueElementStopPri->sizePolicy().hasHeightForWidth());
        ValueElementStopPri->setSizePolicy(sizePolicy4);
        ValueElementStopPri->setMinimumSize(QSize(50, 20));
        ValueElementStopPri->setMaximumSize(QSize(16777215, 20));
        ValueElementStopPri->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementStopPri->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementStopPri->setMinimum(1);
        ValueElementStopPri->setMaximum(128);

        gridLayout_12->addWidget(ValueElementStopPri, 4, 1, 1, 1);

        ValueElementStopSec = new QSpinBox(gridLayoutWidget_3);
        ValueElementStopSec->setObjectName(QString::fromUtf8("ValueElementStopSec"));
        sizePolicy4.setHeightForWidth(ValueElementStopSec->sizePolicy().hasHeightForWidth());
        ValueElementStopSec->setSizePolicy(sizePolicy4);
        ValueElementStopSec->setMinimumSize(QSize(50, 20));
        ValueElementStopSec->setMaximumSize(QSize(16777215, 20));
        ValueElementStopSec->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementStopSec->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementStopSec->setMinimum(1);
        ValueElementStopSec->setMaximum(128);

        gridLayout_12->addWidget(ValueElementStopSec, 4, 2, 1, 1);

        ValueElementStepPri = new QSpinBox(gridLayoutWidget_3);
        ValueElementStepPri->setObjectName(QString::fromUtf8("ValueElementStepPri"));
        sizePolicy4.setHeightForWidth(ValueElementStepPri->sizePolicy().hasHeightForWidth());
        ValueElementStepPri->setSizePolicy(sizePolicy4);
        ValueElementStepPri->setMinimumSize(QSize(50, 20));
        ValueElementStepPri->setMaximumSize(QSize(16777215, 20));
        ValueElementStepPri->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementStepPri->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementStepPri->setMinimum(1);
        ValueElementStepPri->setMaximum(128);

        gridLayout_12->addWidget(ValueElementStepPri, 5, 1, 1, 1);

        ValueElementStepSec = new QSpinBox(gridLayoutWidget_3);
        ValueElementStepSec->setObjectName(QString::fromUtf8("ValueElementStepSec"));
        sizePolicy4.setHeightForWidth(ValueElementStepSec->sizePolicy().hasHeightForWidth());
        ValueElementStepSec->setSizePolicy(sizePolicy4);
        ValueElementStepSec->setMinimumSize(QSize(50, 20));
        ValueElementStepSec->setMaximumSize(QSize(16777215, 20));
        ValueElementStepSec->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueElementStepSec->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueElementStepSec->setMinimum(1);
        ValueElementStepSec->setMaximum(128);

        gridLayout_12->addWidget(ValueElementStepSec, 5, 2, 1, 1);

        BoxAngle = new QGroupBox(scrollAreaWidgetContents_3);
        BoxAngle->setObjectName(QString::fromUtf8("BoxAngle"));
        BoxAngle->setGeometry(QRect(2, 45, 331, 191));
        layoutWidget123 = new QWidget(BoxAngle);
        layoutWidget123->setObjectName(QString::fromUtf8("layoutWidget123"));
        layoutWidget123->setGeometry(QRect(4, 53, 311, 131));
        gridLayout_4 = new QGridLayout(layoutWidget123);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        LabelAngStart = new QLabel(layoutWidget123);
        LabelAngStart->setObjectName(QString::fromUtf8("LabelAngStart"));

        gridLayout_4->addWidget(LabelAngStart, 0, 1, 1, 1);

        LabelAngStop = new QLabel(layoutWidget123);
        LabelAngStop->setObjectName(QString::fromUtf8("LabelAngStop"));

        gridLayout_4->addWidget(LabelAngStop, 0, 2, 1, 1);

        LabelAngStep = new QLabel(layoutWidget123);
        LabelAngStep->setObjectName(QString::fromUtf8("LabelAngStep"));

        gridLayout_4->addWidget(LabelAngStep, 0, 3, 1, 1);

        LabelPriSteering = new QLabel(layoutWidget123);
        LabelPriSteering->setObjectName(QString::fromUtf8("LabelPriSteering"));

        gridLayout_4->addWidget(LabelPriSteering, 1, 0, 1, 1);

        ValuePriSteerStart = new QDoubleSpinBox(layoutWidget123);
        ValuePriSteerStart->setObjectName(QString::fromUtf8("ValuePriSteerStart"));
        ValuePriSteerStart->setFrame(true);
        ValuePriSteerStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePriSteerStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePriSteerStart->setKeyboardTracking(true);
        ValuePriSteerStart->setDecimals(1);
        ValuePriSteerStart->setMinimum(-89);
        ValuePriSteerStart->setMaximum(89);

        gridLayout_4->addWidget(ValuePriSteerStart, 1, 1, 1, 1);

        ValuePriSteerStop = new QDoubleSpinBox(layoutWidget123);
        ValuePriSteerStop->setObjectName(QString::fromUtf8("ValuePriSteerStop"));
        ValuePriSteerStop->setFrame(true);
        ValuePriSteerStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePriSteerStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePriSteerStop->setKeyboardTracking(true);
        ValuePriSteerStop->setDecimals(1);
        ValuePriSteerStop->setMinimum(-89);
        ValuePriSteerStop->setMaximum(89);

        gridLayout_4->addWidget(ValuePriSteerStop, 1, 2, 1, 1);

        ValuePriSteerStep = new QDoubleSpinBox(layoutWidget123);
        ValuePriSteerStep->setObjectName(QString::fromUtf8("ValuePriSteerStep"));
        ValuePriSteerStep->setFrame(true);
        ValuePriSteerStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePriSteerStep->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePriSteerStep->setKeyboardTracking(true);
        ValuePriSteerStep->setDecimals(1);
        ValuePriSteerStep->setMinimum(0.1);
        ValuePriSteerStep->setMaximum(30);

        gridLayout_4->addWidget(ValuePriSteerStep, 1, 3, 1, 1);

        LabelFocusStartUnit_4 = new QLabel(layoutWidget123);
        LabelFocusStartUnit_4->setObjectName(QString::fromUtf8("LabelFocusStartUnit_4"));

        gridLayout_4->addWidget(LabelFocusStartUnit_4, 1, 4, 1, 1);

        LabelSecSteering = new QLabel(layoutWidget123);
        LabelSecSteering->setObjectName(QString::fromUtf8("LabelSecSteering"));

        gridLayout_4->addWidget(LabelSecSteering, 2, 0, 1, 1);

        ValueSecSteerStart = new QDoubleSpinBox(layoutWidget123);
        ValueSecSteerStart->setObjectName(QString::fromUtf8("ValueSecSteerStart"));
        ValueSecSteerStart->setFrame(true);
        ValueSecSteerStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSecSteerStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSecSteerStart->setKeyboardTracking(true);
        ValueSecSteerStart->setDecimals(1);
        ValueSecSteerStart->setMinimum(-89);
        ValueSecSteerStart->setMaximum(89);

        gridLayout_4->addWidget(ValueSecSteerStart, 2, 1, 1, 1);

        ValueSecSteerStop = new QDoubleSpinBox(layoutWidget123);
        ValueSecSteerStop->setObjectName(QString::fromUtf8("ValueSecSteerStop"));
        ValueSecSteerStop->setFrame(true);
        ValueSecSteerStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSecSteerStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSecSteerStop->setKeyboardTracking(true);
        ValueSecSteerStop->setDecimals(1);
        ValueSecSteerStop->setMinimum(-89);
        ValueSecSteerStop->setMaximum(89);

        gridLayout_4->addWidget(ValueSecSteerStop, 2, 2, 1, 1);

        ValueSecSteerStep = new QDoubleSpinBox(layoutWidget123);
        ValueSecSteerStep->setObjectName(QString::fromUtf8("ValueSecSteerStep"));
        ValueSecSteerStep->setFrame(true);
        ValueSecSteerStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSecSteerStep->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSecSteerStep->setKeyboardTracking(true);
        ValueSecSteerStep->setDecimals(1);
        ValueSecSteerStep->setMaximum(5000);

        gridLayout_4->addWidget(ValueSecSteerStep, 2, 3, 1, 1);

        LabelFocusOffsetStartUnit_3 = new QLabel(layoutWidget123);
        LabelFocusOffsetStartUnit_3->setObjectName(QString::fromUtf8("LabelFocusOffsetStartUnit_3"));

        gridLayout_4->addWidget(LabelFocusOffsetStartUnit_3, 2, 4, 1, 1);

        LlabelRefract = new QLabel(layoutWidget123);
        LlabelRefract->setObjectName(QString::fromUtf8("LlabelRefract"));

        gridLayout_4->addWidget(LlabelRefract, 3, 0, 1, 1);

        ValueRefractStart = new QDoubleSpinBox(layoutWidget123);
        ValueRefractStart->setObjectName(QString::fromUtf8("ValueRefractStart"));
        ValueRefractStart->setFrame(true);
        ValueRefractStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueRefractStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueRefractStart->setKeyboardTracking(true);
        ValueRefractStart->setDecimals(1);
        ValueRefractStart->setMinimum(-89);
        ValueRefractStart->setMaximum(89);

        gridLayout_4->addWidget(ValueRefractStart, 3, 1, 1, 1);

        ValueRefractStop = new QDoubleSpinBox(layoutWidget123);
        ValueRefractStop->setObjectName(QString::fromUtf8("ValueRefractStop"));
        ValueRefractStop->setFrame(true);
        ValueRefractStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueRefractStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueRefractStop->setKeyboardTracking(true);
        ValueRefractStop->setDecimals(1);
        ValueRefractStop->setMinimum(-89);
        ValueRefractStop->setMaximum(89);

        gridLayout_4->addWidget(ValueRefractStop, 3, 2, 1, 1);

        ValueRefractStep = new QDoubleSpinBox(layoutWidget123);
        ValueRefractStep->setObjectName(QString::fromUtf8("ValueRefractStep"));
        ValueRefractStep->setFrame(true);
        ValueRefractStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueRefractStep->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueRefractStep->setKeyboardTracking(true);
        ValueRefractStep->setDecimals(1);
        ValueRefractStep->setMaximum(5000);

        gridLayout_4->addWidget(ValueRefractStep, 3, 3, 1, 1);

        LabelFocusOffsetStopUnit_3 = new QLabel(layoutWidget123);
        LabelFocusOffsetStopUnit_3->setObjectName(QString::fromUtf8("LabelFocusOffsetStopUnit_3"));

        gridLayout_4->addWidget(LabelFocusOffsetStopUnit_3, 3, 4, 1, 1);

        LlabelBeamSkew = new QLabel(layoutWidget123);
        LlabelBeamSkew->setObjectName(QString::fromUtf8("LlabelBeamSkew"));

        gridLayout_4->addWidget(LlabelBeamSkew, 4, 0, 1, 1);

        ValueSkewStart = new QDoubleSpinBox(layoutWidget123);
        ValueSkewStart->setObjectName(QString::fromUtf8("ValueSkewStart"));
        ValueSkewStart->setFrame(true);
        ValueSkewStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSkewStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSkewStart->setKeyboardTracking(true);
        ValueSkewStart->setDecimals(1);
        ValueSkewStart->setMaximum(5000);

        gridLayout_4->addWidget(ValueSkewStart, 4, 1, 1, 1);

        ValueSkewStop = new QDoubleSpinBox(layoutWidget123);
        ValueSkewStop->setObjectName(QString::fromUtf8("ValueSkewStop"));
        ValueSkewStop->setFrame(true);
        ValueSkewStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSkewStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSkewStop->setKeyboardTracking(true);
        ValueSkewStop->setDecimals(1);
        ValueSkewStop->setMaximum(5000);

        gridLayout_4->addWidget(ValueSkewStop, 4, 2, 1, 1);

        ValueSkewStep = new QDoubleSpinBox(layoutWidget123);
        ValueSkewStep->setObjectName(QString::fromUtf8("ValueSkewStep"));
        ValueSkewStep->setFrame(true);
        ValueSkewStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSkewStep->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSkewStep->setKeyboardTracking(true);
        ValueSkewStep->setDecimals(1);
        ValueSkewStep->setMaximum(5000);

        gridLayout_4->addWidget(ValueSkewStep, 4, 3, 1, 1);

        LabelFocusOffsetStopUnit_4 = new QLabel(layoutWidget123);
        LabelFocusOffsetStopUnit_4->setObjectName(QString::fromUtf8("LabelFocusOffsetStopUnit_4"));

        gridLayout_4->addWidget(LabelFocusOffsetStopUnit_4, 4, 4, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(BoxAngle);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(18, 14, 251, 31));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        LabelAngleType = new QLabel(horizontalLayoutWidget_2);
        LabelAngleType->setObjectName(QString::fromUtf8("LabelAngleType"));
        sizePolicy.setHeightForWidth(LabelAngleType->sizePolicy().hasHeightForWidth());
        LabelAngleType->setSizePolicy(sizePolicy);
        LabelAngleType->setMinimumSize(QSize(75, 25));

        horizontalLayout_8->addWidget(LabelAngleType);

        ComAngleType = new QComboBox(horizontalLayoutWidget_2);
        ComAngleType->setObjectName(QString::fromUtf8("ComAngleType"));

        horizontalLayout_8->addWidget(ComAngleType);

        horizontalLayoutWidget = new QWidget(scrollAreaWidgetContents_3);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 6, 291, 31));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        LabelLawType = new QLabel(horizontalLayoutWidget);
        LabelLawType->setObjectName(QString::fromUtf8("LabelLawType"));
        sizePolicy.setHeightForWidth(LabelLawType->sizePolicy().hasHeightForWidth());
        LabelLawType->setSizePolicy(sizePolicy);
        LabelLawType->setMinimumSize(QSize(75, 25));

        horizontalLayout_7->addWidget(LabelLawType);

        ComLawType = new QComboBox(horizontalLayoutWidget);
        ComLawType->setObjectName(QString::fromUtf8("ComLawType"));

        horizontalLayout_7->addWidget(ComLawType);

        BtnProcessLaw = new QPushButton(horizontalLayoutWidget);
        BtnProcessLaw->setObjectName(QString::fromUtf8("BtnProcessLaw"));

        horizontalLayout_7->addWidget(BtnProcessLaw);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(scrollArea);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-03.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(FocalLaw, icon2, QString::fromUtf8("Focallaw"));
        GateSizingcurves = new QWidget();
        GateSizingcurves->setObjectName(QString::fromUtf8("GateSizingcurves"));
        GateSizingcurves->setGeometry(QRect(0, 0, 330, 707));
        verticalLayout_5 = new QVBoxLayout(GateSizingcurves);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        scrollAreaGateAndCurve = new QScrollArea(GateSizingcurves);
        scrollAreaGateAndCurve->setObjectName(QString::fromUtf8("scrollAreaGateAndCurve"));
        scrollAreaGateAndCurve->setMinimumSize(QSize(0, 700));
        scrollAreaGateAndCurve->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 326, 703));
        line_8 = new QFrame(scrollAreaWidgetContents_4);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setGeometry(QRect(21, 20, 221, 20));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        LabelGate = new QLabel(scrollAreaWidgetContents_4);
        LabelGate->setObjectName(QString::fromUtf8("LabelGate"));
        LabelGate->setGeometry(QRect(23, 10, 111, 16));
        CheckGateShow = new QCheckBox(scrollAreaWidgetContents_4);
        CheckGateShow->setObjectName(QString::fromUtf8("CheckGateShow"));
        CheckGateShow->setGeometry(QRect(167, 10, 71, 16));
        gridLayoutWidget_6 = new QWidget(scrollAreaWidgetContents_4);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(20, 37, 221, 182));
        gridLayout_13 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_13->setContentsMargins(0, 0, 0, 0);
        LabelGateSelect = new QLabel(gridLayoutWidget_6);
        LabelGateSelect->setObjectName(QString::fromUtf8("LabelGateSelect"));
        sizePolicy.setHeightForWidth(LabelGateSelect->sizePolicy().hasHeightForWidth());
        LabelGateSelect->setSizePolicy(sizePolicy);
        LabelGateSelect->setMinimumSize(QSize(50, 25));
        LabelGateSelect->setMaximumSize(QSize(50, 16777215));

        gridLayout_13->addWidget(LabelGateSelect, 0, 0, 1, 1);

        ComGateSelect = new QComboBox(gridLayoutWidget_6);
        ComGateSelect->setObjectName(QString::fromUtf8("ComGateSelect"));

        gridLayout_13->addWidget(ComGateSelect, 0, 1, 1, 1);

        LabelGateStart = new QLabel(gridLayoutWidget_6);
        LabelGateStart->setObjectName(QString::fromUtf8("LabelGateStart"));
        sizePolicy.setHeightForWidth(LabelGateStart->sizePolicy().hasHeightForWidth());
        LabelGateStart->setSizePolicy(sizePolicy);
        LabelGateStart->setMinimumSize(QSize(50, 25));
        LabelGateStart->setMaximumSize(QSize(50, 16777215));

        gridLayout_13->addWidget(LabelGateStart, 1, 0, 1, 1);

        ValueGateStart = new QDoubleSpinBox(gridLayoutWidget_6);
        ValueGateStart->setObjectName(QString::fromUtf8("ValueGateStart"));
        sizePolicy.setHeightForWidth(ValueGateStart->sizePolicy().hasHeightForWidth());
        ValueGateStart->setSizePolicy(sizePolicy);
        ValueGateStart->setMinimumSize(QSize(60, 20));
        ValueGateStart->setMaximumSize(QSize(200, 20));
        ValueGateStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueGateStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueGateStart->setDecimals(1);
        ValueGateStart->setSingleStep(0.1);

        gridLayout_13->addWidget(ValueGateStart, 1, 1, 1, 1);

        LabelGateStartUnit = new QLabel(gridLayoutWidget_6);
        LabelGateStartUnit->setObjectName(QString::fromUtf8("LabelGateStartUnit"));
        LabelGateStartUnit->setMaximumSize(QSize(60, 16777215));

        gridLayout_13->addWidget(LabelGateStartUnit, 1, 2, 1, 1);

        LabelGateWidth = new QLabel(gridLayoutWidget_6);
        LabelGateWidth->setObjectName(QString::fromUtf8("LabelGateWidth"));
        sizePolicy.setHeightForWidth(LabelGateWidth->sizePolicy().hasHeightForWidth());
        LabelGateWidth->setSizePolicy(sizePolicy);
        LabelGateWidth->setMinimumSize(QSize(50, 25));
        LabelGateWidth->setMaximumSize(QSize(50, 16777215));

        gridLayout_13->addWidget(LabelGateWidth, 2, 0, 1, 1);

        ValueGateWidth = new QDoubleSpinBox(gridLayoutWidget_6);
        ValueGateWidth->setObjectName(QString::fromUtf8("ValueGateWidth"));
        sizePolicy.setHeightForWidth(ValueGateWidth->sizePolicy().hasHeightForWidth());
        ValueGateWidth->setSizePolicy(sizePolicy);
        ValueGateWidth->setMinimumSize(QSize(60, 20));
        ValueGateWidth->setMaximumSize(QSize(200, 20));
        ValueGateWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueGateWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueGateWidth->setDecimals(1);
        ValueGateWidth->setSingleStep(0.1);

        gridLayout_13->addWidget(ValueGateWidth, 2, 1, 1, 1);

        LabelGateWidthUnit = new QLabel(gridLayoutWidget_6);
        LabelGateWidthUnit->setObjectName(QString::fromUtf8("LabelGateWidthUnit"));

        gridLayout_13->addWidget(LabelGateWidthUnit, 2, 2, 1, 1);

        LabelGateHeight = new QLabel(gridLayoutWidget_6);
        LabelGateHeight->setObjectName(QString::fromUtf8("LabelGateHeight"));
        sizePolicy.setHeightForWidth(LabelGateHeight->sizePolicy().hasHeightForWidth());
        LabelGateHeight->setSizePolicy(sizePolicy);
        LabelGateHeight->setMinimumSize(QSize(50, 25));
        LabelGateHeight->setMaximumSize(QSize(70, 20));

        gridLayout_13->addWidget(LabelGateHeight, 3, 0, 1, 1);

        LabelGateSync = new QLabel(gridLayoutWidget_6);
        LabelGateSync->setObjectName(QString::fromUtf8("LabelGateSync"));
        sizePolicy.setHeightForWidth(LabelGateSync->sizePolicy().hasHeightForWidth());
        LabelGateSync->setSizePolicy(sizePolicy);
        LabelGateSync->setMinimumSize(QSize(75, 25));

        gridLayout_13->addWidget(LabelGateSync, 4, 0, 1, 1);

        ComGateSync = new QComboBox(gridLayoutWidget_6);
        ComGateSync->setObjectName(QString::fromUtf8("ComGateSync"));

        gridLayout_13->addWidget(ComGateSync, 4, 1, 1, 1);

        LabelGateMeasure = new QLabel(gridLayoutWidget_6);
        LabelGateMeasure->setObjectName(QString::fromUtf8("LabelGateMeasure"));
        sizePolicy.setHeightForWidth(LabelGateMeasure->sizePolicy().hasHeightForWidth());
        LabelGateMeasure->setSizePolicy(sizePolicy);
        LabelGateMeasure->setMinimumSize(QSize(75, 25));

        gridLayout_13->addWidget(LabelGateMeasure, 5, 0, 1, 1);

        ComGateMeasure = new QComboBox(gridLayoutWidget_6);
        ComGateMeasure->setObjectName(QString::fromUtf8("ComGateMeasure"));

        gridLayout_13->addWidget(ComGateMeasure, 5, 1, 1, 1);

        ValueGateHeight = new QDoubleSpinBox(gridLayoutWidget_6);
        ValueGateHeight->setObjectName(QString::fromUtf8("ValueGateHeight"));
        sizePolicy.setHeightForWidth(ValueGateHeight->sizePolicy().hasHeightForWidth());
        ValueGateHeight->setSizePolicy(sizePolicy);
        ValueGateHeight->setMinimumSize(QSize(60, 20));
        ValueGateHeight->setMaximumSize(QSize(200, 20));
        ValueGateHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueGateHeight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueGateHeight->setDecimals(0);
        ValueGateHeight->setValue(1);

        gridLayout_13->addWidget(ValueGateHeight, 3, 1, 1, 1);

        line_10 = new QFrame(scrollAreaWidgetContents_4);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setGeometry(QRect(22, 244, 221, 20));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);
        LabelSizingCurves = new QLabel(scrollAreaWidgetContents_4);
        LabelSizingCurves->setObjectName(QString::fromUtf8("LabelSizingCurves"));
        LabelSizingCurves->setGeometry(QRect(24, 234, 111, 16));
        horizontalLayoutWidget_6 = new QWidget(scrollAreaWidgetContents_4);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(20, 261, 181, 27));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        LabelCurveSel = new QLabel(horizontalLayoutWidget_6);
        LabelCurveSel->setObjectName(QString::fromUtf8("LabelCurveSel"));
        sizePolicy.setHeightForWidth(LabelCurveSel->sizePolicy().hasHeightForWidth());
        LabelCurveSel->setSizePolicy(sizePolicy);
        LabelCurveSel->setMinimumSize(QSize(50, 25));
        LabelCurveSel->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_12->addWidget(LabelCurveSel);

        ComSizingCurve = new QComboBox(horizontalLayoutWidget_6);
        ComSizingCurve->setObjectName(QString::fromUtf8("ComSizingCurve"));

        horizontalLayout_12->addWidget(ComSizingCurve);

        horizontalLayoutWidget_5 = new QWidget(scrollAreaWidgetContents_4);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(20, 290, 259, 27));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        DacPointPos = new QLabel(horizontalLayoutWidget_5);
        DacPointPos->setObjectName(QString::fromUtf8("DacPointPos"));
        sizePolicy2.setHeightForWidth(DacPointPos->sizePolicy().hasHeightForWidth());
        DacPointPos->setSizePolicy(sizePolicy2);
        DacPointPos->setMinimumSize(QSize(50, 25));
        DacPointPos->setMaximumSize(QSize(11111, 16777215));

        horizontalLayout_11->addWidget(DacPointPos);

        ComCurvePointId = new QComboBox(horizontalLayoutWidget_5);
        ComCurvePointId->setObjectName(QString::fromUtf8("ComCurvePointId"));

        horizontalLayout_11->addWidget(ComCurvePointId);

        BtnAddPoint = new QPushButton(horizontalLayoutWidget_5);
        BtnAddPoint->setObjectName(QString::fromUtf8("BtnAddPoint"));

        horizontalLayout_11->addWidget(BtnAddPoint);

        BtnDelPoint = new QPushButton(horizontalLayoutWidget_5);
        BtnDelPoint->setObjectName(QString::fromUtf8("BtnDelPoint"));

        horizontalLayout_11->addWidget(BtnDelPoint);

        gridLayoutWidget_4 = new QWidget(scrollAreaWidgetContents_4);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(20, 320, 259, 421));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        LabelSizingCure1 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure1->setObjectName(QString::fromUtf8("LabelSizingCure1"));
        LabelSizingCure1->setMaximumSize(QSize(160, 20));

        gridLayout_2->addWidget(LabelSizingCure1, 0, 0, 1, 1);

        ValueSizingCurve1 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve1->setObjectName(QString::fromUtf8("ValueSizingCurve1"));
        sizePolicy.setHeightForWidth(ValueSizingCurve1->sizePolicy().hasHeightForWidth());
        ValueSizingCurve1->setSizePolicy(sizePolicy);
        ValueSizingCurve1->setMinimumSize(QSize(80, 20));
        ValueSizingCurve1->setMaximumSize(QSize(100, 20));
        ValueSizingCurve1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve1->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve1, 0, 1, 1, 1);

        LabelSizingCureUnit1 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit1->setObjectName(QString::fromUtf8("LabelSizingCureUnit1"));
        LabelSizingCureUnit1->setMaximumSize(QSize(60, 20));

        gridLayout_2->addWidget(LabelSizingCureUnit1, 0, 2, 1, 1);

        LabelSizingCure2 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure2->setObjectName(QString::fromUtf8("LabelSizingCure2"));
        LabelSizingCure2->setMaximumSize(QSize(160, 20));

        gridLayout_2->addWidget(LabelSizingCure2, 1, 0, 1, 1);

        ValueSizingCurve2 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve2->setObjectName(QString::fromUtf8("ValueSizingCurve2"));
        sizePolicy.setHeightForWidth(ValueSizingCurve2->sizePolicy().hasHeightForWidth());
        ValueSizingCurve2->setSizePolicy(sizePolicy);
        ValueSizingCurve2->setMinimumSize(QSize(80, 20));
        ValueSizingCurve2->setMaximumSize(QSize(60, 20));
        ValueSizingCurve2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve2->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve2, 1, 1, 1, 1);

        LabelSizingCureUnit2 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit2->setObjectName(QString::fromUtf8("LabelSizingCureUnit2"));
        LabelSizingCureUnit2->setMaximumSize(QSize(16777215, 20));

        gridLayout_2->addWidget(LabelSizingCureUnit2, 1, 2, 1, 1);

        LabelSizingCure4 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure4->setObjectName(QString::fromUtf8("LabelSizingCure4"));
        LabelSizingCure4->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure4, 3, 0, 1, 1);

        LabelSizingCure5 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure5->setObjectName(QString::fromUtf8("LabelSizingCure5"));
        LabelSizingCure5->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure5, 4, 0, 1, 1);

        LabelSizingCure6 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure6->setObjectName(QString::fromUtf8("LabelSizingCure6"));
        LabelSizingCure6->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure6, 5, 0, 1, 1);

        ValueSizingCurve3 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve3->setObjectName(QString::fromUtf8("ValueSizingCurve3"));
        sizePolicy.setHeightForWidth(ValueSizingCurve3->sizePolicy().hasHeightForWidth());
        ValueSizingCurve3->setSizePolicy(sizePolicy);
        ValueSizingCurve3->setMinimumSize(QSize(80, 20));
        ValueSizingCurve3->setMaximumSize(QSize(1, 20));
        ValueSizingCurve3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve3->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve3->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve3, 2, 1, 1, 1);

        ValueSizingCurve4 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve4->setObjectName(QString::fromUtf8("ValueSizingCurve4"));
        sizePolicy.setHeightForWidth(ValueSizingCurve4->sizePolicy().hasHeightForWidth());
        ValueSizingCurve4->setSizePolicy(sizePolicy);
        ValueSizingCurve4->setMinimumSize(QSize(80, 20));
        ValueSizingCurve4->setMaximumSize(QSize(60, 20));
        ValueSizingCurve4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve4->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve4, 3, 1, 1, 1);

        ValueSizingCurve5 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve5->setObjectName(QString::fromUtf8("ValueSizingCurve5"));
        sizePolicy.setHeightForWidth(ValueSizingCurve5->sizePolicy().hasHeightForWidth());
        ValueSizingCurve5->setSizePolicy(sizePolicy);
        ValueSizingCurve5->setMinimumSize(QSize(80, 20));
        ValueSizingCurve5->setMaximumSize(QSize(60, 20));
        ValueSizingCurve5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve5->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve5, 4, 1, 1, 1);

        ValueSizingCurve6 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve6->setObjectName(QString::fromUtf8("ValueSizingCurve6"));
        sizePolicy.setHeightForWidth(ValueSizingCurve6->sizePolicy().hasHeightForWidth());
        ValueSizingCurve6->setSizePolicy(sizePolicy);
        ValueSizingCurve6->setMinimumSize(QSize(80, 20));
        ValueSizingCurve6->setMaximumSize(QSize(60, 20));
        ValueSizingCurve6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve6->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve6->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve6, 5, 1, 1, 1);

        LabelSizingCureUnit3 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit3->setObjectName(QString::fromUtf8("LabelSizingCureUnit3"));

        gridLayout_2->addWidget(LabelSizingCureUnit3, 2, 2, 1, 1);

        LabelSizingCureUnit4 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit4->setObjectName(QString::fromUtf8("LabelSizingCureUnit4"));

        gridLayout_2->addWidget(LabelSizingCureUnit4, 3, 2, 1, 1);

        LabelSizingCureUnit5 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit5->setObjectName(QString::fromUtf8("LabelSizingCureUnit5"));

        gridLayout_2->addWidget(LabelSizingCureUnit5, 4, 2, 1, 1);

        LabelSizingCureUnit6 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit6->setObjectName(QString::fromUtf8("LabelSizingCureUnit6"));

        gridLayout_2->addWidget(LabelSizingCureUnit6, 5, 2, 1, 1);

        LabelSizingCure3 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure3->setObjectName(QString::fromUtf8("LabelSizingCure3"));
        LabelSizingCure3->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure3, 2, 0, 1, 1);

        LabelSizingCure7 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure7->setObjectName(QString::fromUtf8("LabelSizingCure7"));
        LabelSizingCure7->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure7, 6, 0, 1, 1);

        LabelSizingCure8 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure8->setObjectName(QString::fromUtf8("LabelSizingCure8"));
        LabelSizingCure8->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure8, 7, 0, 1, 1);

        LabelSizingCure9 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure9->setObjectName(QString::fromUtf8("LabelSizingCure9"));
        LabelSizingCure9->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure9, 8, 0, 1, 1);

        LabelSizingCure10 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure10->setObjectName(QString::fromUtf8("LabelSizingCure10"));
        LabelSizingCure10->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure10, 9, 0, 1, 1);

        LabelSizingCure11 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure11->setObjectName(QString::fromUtf8("LabelSizingCure11"));
        LabelSizingCure11->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure11, 10, 0, 1, 1);

        LabelSizingCure12 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure12->setObjectName(QString::fromUtf8("LabelSizingCure12"));
        LabelSizingCure12->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure12, 11, 0, 1, 1);

        LabelSizingCure13 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure13->setObjectName(QString::fromUtf8("LabelSizingCure13"));
        LabelSizingCure13->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure13, 12, 0, 1, 1);

        LabelSizingCure14 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure14->setObjectName(QString::fromUtf8("LabelSizingCure14"));
        LabelSizingCure14->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure14, 13, 0, 1, 1);

        LabelSizingCure15 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure15->setObjectName(QString::fromUtf8("LabelSizingCure15"));
        LabelSizingCure15->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure15, 14, 0, 1, 1);

        LabelSizingCure16 = new QLabel(gridLayoutWidget_4);
        LabelSizingCure16->setObjectName(QString::fromUtf8("LabelSizingCure16"));
        LabelSizingCure16->setMaximumSize(QSize(160, 16777215));

        gridLayout_2->addWidget(LabelSizingCure16, 15, 0, 1, 1);

        ValueSizingCurve7 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve7->setObjectName(QString::fromUtf8("ValueSizingCurve7"));
        sizePolicy.setHeightForWidth(ValueSizingCurve7->sizePolicy().hasHeightForWidth());
        ValueSizingCurve7->setSizePolicy(sizePolicy);
        ValueSizingCurve7->setMinimumSize(QSize(80, 20));
        ValueSizingCurve7->setMaximumSize(QSize(60, 20));
        ValueSizingCurve7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve7->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve7->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve7, 6, 1, 1, 1);

        ValueSizingCurve8 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve8->setObjectName(QString::fromUtf8("ValueSizingCurve8"));
        sizePolicy.setHeightForWidth(ValueSizingCurve8->sizePolicy().hasHeightForWidth());
        ValueSizingCurve8->setSizePolicy(sizePolicy);
        ValueSizingCurve8->setMinimumSize(QSize(80, 20));
        ValueSizingCurve8->setMaximumSize(QSize(60, 20));
        ValueSizingCurve8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve8->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve8->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve8, 7, 1, 1, 1);

        ValueSizingCurve9 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve9->setObjectName(QString::fromUtf8("ValueSizingCurve9"));
        sizePolicy.setHeightForWidth(ValueSizingCurve9->sizePolicy().hasHeightForWidth());
        ValueSizingCurve9->setSizePolicy(sizePolicy);
        ValueSizingCurve9->setMinimumSize(QSize(80, 20));
        ValueSizingCurve9->setMaximumSize(QSize(60, 20));
        ValueSizingCurve9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve9->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve9->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve9, 8, 1, 1, 1);

        ValueSizingCurve10 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve10->setObjectName(QString::fromUtf8("ValueSizingCurve10"));
        sizePolicy.setHeightForWidth(ValueSizingCurve10->sizePolicy().hasHeightForWidth());
        ValueSizingCurve10->setSizePolicy(sizePolicy);
        ValueSizingCurve10->setMinimumSize(QSize(80, 20));
        ValueSizingCurve10->setMaximumSize(QSize(60, 20));
        ValueSizingCurve10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve10->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve10->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve10, 9, 1, 1, 1);

        ValueSizingCurve11 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve11->setObjectName(QString::fromUtf8("ValueSizingCurve11"));
        sizePolicy.setHeightForWidth(ValueSizingCurve11->sizePolicy().hasHeightForWidth());
        ValueSizingCurve11->setSizePolicy(sizePolicy);
        ValueSizingCurve11->setMinimumSize(QSize(80, 20));
        ValueSizingCurve11->setMaximumSize(QSize(60, 20));
        ValueSizingCurve11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve11->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve11->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve11, 10, 1, 1, 1);

        ValueSizingCurve12 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve12->setObjectName(QString::fromUtf8("ValueSizingCurve12"));
        sizePolicy.setHeightForWidth(ValueSizingCurve12->sizePolicy().hasHeightForWidth());
        ValueSizingCurve12->setSizePolicy(sizePolicy);
        ValueSizingCurve12->setMinimumSize(QSize(80, 20));
        ValueSizingCurve12->setMaximumSize(QSize(60, 20));
        ValueSizingCurve12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve12->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve12->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve12, 11, 1, 1, 1);

        ValueSizingCurve13 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve13->setObjectName(QString::fromUtf8("ValueSizingCurve13"));
        sizePolicy.setHeightForWidth(ValueSizingCurve13->sizePolicy().hasHeightForWidth());
        ValueSizingCurve13->setSizePolicy(sizePolicy);
        ValueSizingCurve13->setMinimumSize(QSize(80, 20));
        ValueSizingCurve13->setMaximumSize(QSize(60, 20));
        ValueSizingCurve13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve13->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve13->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve13, 12, 1, 1, 1);

        ValueSizingCurve14 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve14->setObjectName(QString::fromUtf8("ValueSizingCurve14"));
        sizePolicy.setHeightForWidth(ValueSizingCurve14->sizePolicy().hasHeightForWidth());
        ValueSizingCurve14->setSizePolicy(sizePolicy);
        ValueSizingCurve14->setMinimumSize(QSize(80, 20));
        ValueSizingCurve14->setMaximumSize(QSize(60, 20));
        ValueSizingCurve14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve14->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve14->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve14, 13, 1, 1, 1);

        ValueSizingCurve15 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve15->setObjectName(QString::fromUtf8("ValueSizingCurve15"));
        sizePolicy.setHeightForWidth(ValueSizingCurve15->sizePolicy().hasHeightForWidth());
        ValueSizingCurve15->setSizePolicy(sizePolicy);
        ValueSizingCurve15->setMinimumSize(QSize(80, 20));
        ValueSizingCurve15->setMaximumSize(QSize(60, 20));
        ValueSizingCurve15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve15->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve15->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve15, 14, 1, 1, 1);

        ValueSizingCurve16 = new QDoubleSpinBox(gridLayoutWidget_4);
        ValueSizingCurve16->setObjectName(QString::fromUtf8("ValueSizingCurve16"));
        sizePolicy.setHeightForWidth(ValueSizingCurve16->sizePolicy().hasHeightForWidth());
        ValueSizingCurve16->setSizePolicy(sizePolicy);
        ValueSizingCurve16->setMinimumSize(QSize(80, 20));
        ValueSizingCurve16->setMaximumSize(QSize(60, 20));
        ValueSizingCurve16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSizingCurve16->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSizingCurve16->setDecimals(1);

        gridLayout_2->addWidget(ValueSizingCurve16, 15, 1, 1, 1);

        LabelSizingCureUnit7 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit7->setObjectName(QString::fromUtf8("LabelSizingCureUnit7"));

        gridLayout_2->addWidget(LabelSizingCureUnit7, 6, 2, 1, 1);

        LabelSizingCureUnit8 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit8->setObjectName(QString::fromUtf8("LabelSizingCureUnit8"));

        gridLayout_2->addWidget(LabelSizingCureUnit8, 7, 2, 1, 1);

        LabelSizingCureUnit9 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit9->setObjectName(QString::fromUtf8("LabelSizingCureUnit9"));

        gridLayout_2->addWidget(LabelSizingCureUnit9, 8, 2, 1, 1);

        LabelSizingCureUnit10 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit10->setObjectName(QString::fromUtf8("LabelSizingCureUnit10"));

        gridLayout_2->addWidget(LabelSizingCureUnit10, 9, 2, 1, 1);

        LabelSizingCureUnit11 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit11->setObjectName(QString::fromUtf8("LabelSizingCureUnit11"));

        gridLayout_2->addWidget(LabelSizingCureUnit11, 10, 2, 1, 1);

        LabelSizingCureUnit12 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit12->setObjectName(QString::fromUtf8("LabelSizingCureUnit12"));

        gridLayout_2->addWidget(LabelSizingCureUnit12, 11, 2, 1, 1);

        LabelSizingCureUnit13 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit13->setObjectName(QString::fromUtf8("LabelSizingCureUnit13"));

        gridLayout_2->addWidget(LabelSizingCureUnit13, 12, 2, 1, 1);

        LabelSizingCureUnit14 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit14->setObjectName(QString::fromUtf8("LabelSizingCureUnit14"));

        gridLayout_2->addWidget(LabelSizingCureUnit14, 13, 2, 1, 1);

        LabelSizingCureUnit15 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit15->setObjectName(QString::fromUtf8("LabelSizingCureUnit15"));

        gridLayout_2->addWidget(LabelSizingCureUnit15, 14, 2, 1, 1);

        LabelSizingCureUnit16 = new QLabel(gridLayoutWidget_4);
        LabelSizingCureUnit16->setObjectName(QString::fromUtf8("LabelSizingCureUnit16"));

        gridLayout_2->addWidget(LabelSizingCureUnit16, 15, 2, 1, 1);

        scrollAreaGateAndCurve->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_5->addWidget(scrollAreaGateAndCurve);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-04.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(GateSizingcurves, icon3, QString::fromUtf8("Gate and Sizing Curves"));
        Geometry = new QWidget();
        Geometry->setObjectName(QString::fromUtf8("Geometry"));
        Geometry->setGeometry(QRect(0, 0, 313, 800));
        verticalLayout_6 = new QVBoxLayout(Geometry);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        scrollGeometry = new QScrollArea(Geometry);
        scrollGeometry->setObjectName(QString::fromUtf8("scrollGeometry"));
        scrollGeometry->setMinimumSize(QSize(0, 800));
        scrollGeometry->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 309, 796));
        layoutWidget15 = new QWidget(scrollAreaWidgetContents_5);
        layoutWidget15->setObjectName(QString::fromUtf8("layoutWidget15"));
        layoutWidget15->setGeometry(QRect(30, 340, 272, 54));
        gridLayout_8 = new QGridLayout(layoutWidget15);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        LabelPartFile = new QLabel(layoutWidget15);
        LabelPartFile->setObjectName(QString::fromUtf8("LabelPartFile"));

        gridLayout_8->addWidget(LabelPartFile, 0, 0, 1, 2);

        LabelPartFileLoad = new QLabel(layoutWidget15);
        LabelPartFileLoad->setObjectName(QString::fromUtf8("LabelPartFileLoad"));
        sizePolicy.setHeightForWidth(LabelPartFileLoad->sizePolicy().hasHeightForWidth());
        LabelPartFileLoad->setSizePolicy(sizePolicy);
        LabelPartFileLoad->setMinimumSize(QSize(40, 25));
        LabelPartFileLoad->setMaximumSize(QSize(40, 16777215));

        gridLayout_8->addWidget(LabelPartFileLoad, 1, 0, 1, 1);

        BtnLoadPartFile = new QPushButton(layoutWidget15);
        BtnLoadPartFile->setObjectName(QString::fromUtf8("BtnLoadPartFile"));
        BtnLoadPartFile->setMinimumSize(QSize(150, 0));
        BtnLoadPartFile->setMaximumSize(QSize(150, 16777215));

        gridLayout_8->addWidget(BtnLoadPartFile, 1, 1, 1, 1);

        CheckPartFileShow = new QCheckBox(layoutWidget15);
        CheckPartFileShow->setObjectName(QString::fromUtf8("CheckPartFileShow"));

        gridLayout_8->addWidget(CheckPartFileShow, 1, 2, 1, 1);

        BoxPart = new QGroupBox(scrollAreaWidgetContents_5);
        BoxPart->setObjectName(QString::fromUtf8("BoxPart"));
        BoxPart->setGeometry(QRect(10, 9, 291, 211));
        layoutWidget14 = new QWidget(BoxPart);
        layoutWidget14->setObjectName(QString::fromUtf8("layoutWidget14"));
        layoutWidget14->setGeometry(QRect(21, 21, 160, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget14);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        LabelGeometry = new QLabel(layoutWidget14);
        LabelGeometry->setObjectName(QString::fromUtf8("LabelGeometry"));
        sizePolicy.setHeightForWidth(LabelGeometry->sizePolicy().hasHeightForWidth());
        LabelGeometry->setSizePolicy(sizePolicy);
        LabelGeometry->setMinimumSize(QSize(75, 25));

        horizontalLayout_3->addWidget(LabelGeometry);

        ComGeometry = new QComboBox(layoutWidget14);
        ComGeometry->setObjectName(QString::fromUtf8("ComGeometry"));

        horizontalLayout_3->addWidget(ComGeometry);

        CheckUnifiedPartSetting = new QCheckBox(BoxPart);
        CheckUnifiedPartSetting->setObjectName(QString::fromUtf8("CheckUnifiedPartSetting"));
        CheckUnifiedPartSetting->setGeometry(QRect(20, 180, 131, 19));
        layoutWidget16 = new QWidget(BoxPart);
        layoutWidget16->setObjectName(QString::fromUtf8("layoutWidget16"));
        layoutWidget16->setGeometry(QRect(22, 82, 181, 89));
        gridLayout_7 = new QGridLayout(layoutWidget16);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        LabelPartSize1 = new QLabel(layoutWidget16);
        LabelPartSize1->setObjectName(QString::fromUtf8("LabelPartSize1"));
        sizePolicy.setHeightForWidth(LabelPartSize1->sizePolicy().hasHeightForWidth());
        LabelPartSize1->setSizePolicy(sizePolicy);
        LabelPartSize1->setMinimumSize(QSize(75, 25));

        gridLayout_7->addWidget(LabelPartSize1, 0, 0, 1, 1);

        ValuePartSize1 = new QDoubleSpinBox(layoutWidget16);
        ValuePartSize1->setObjectName(QString::fromUtf8("ValuePartSize1"));
        sizePolicy.setHeightForWidth(ValuePartSize1->sizePolicy().hasHeightForWidth());
        ValuePartSize1->setSizePolicy(sizePolicy);
        ValuePartSize1->setMinimumSize(QSize(60, 20));
        ValuePartSize1->setMaximumSize(QSize(60, 20));
        ValuePartSize1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePartSize1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePartSize1->setDecimals(1);
        ValuePartSize1->setMaximum(50000);

        gridLayout_7->addWidget(ValuePartSize1, 0, 1, 1, 1);

        LabelPartSizeUnit1 = new QLabel(layoutWidget16);
        LabelPartSizeUnit1->setObjectName(QString::fromUtf8("LabelPartSizeUnit1"));

        gridLayout_7->addWidget(LabelPartSizeUnit1, 0, 2, 1, 1);

        LabelPartSize2 = new QLabel(layoutWidget16);
        LabelPartSize2->setObjectName(QString::fromUtf8("LabelPartSize2"));
        sizePolicy.setHeightForWidth(LabelPartSize2->sizePolicy().hasHeightForWidth());
        LabelPartSize2->setSizePolicy(sizePolicy);
        LabelPartSize2->setMinimumSize(QSize(75, 25));

        gridLayout_7->addWidget(LabelPartSize2, 1, 0, 1, 1);

        ValuePartSize2 = new QDoubleSpinBox(layoutWidget16);
        ValuePartSize2->setObjectName(QString::fromUtf8("ValuePartSize2"));
        sizePolicy.setHeightForWidth(ValuePartSize2->sizePolicy().hasHeightForWidth());
        ValuePartSize2->setSizePolicy(sizePolicy);
        ValuePartSize2->setMinimumSize(QSize(60, 20));
        ValuePartSize2->setMaximumSize(QSize(60, 20));
        ValuePartSize2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePartSize2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePartSize2->setDecimals(1);
        ValuePartSize2->setMaximum(50000);

        gridLayout_7->addWidget(ValuePartSize2, 1, 1, 1, 1);

        LabelPartSizeUnit2 = new QLabel(layoutWidget16);
        LabelPartSizeUnit2->setObjectName(QString::fromUtf8("LabelPartSizeUnit2"));

        gridLayout_7->addWidget(LabelPartSizeUnit2, 1, 2, 1, 1);

        LabelPartSize3 = new QLabel(layoutWidget16);
        LabelPartSize3->setObjectName(QString::fromUtf8("LabelPartSize3"));
        sizePolicy.setHeightForWidth(LabelPartSize3->sizePolicy().hasHeightForWidth());
        LabelPartSize3->setSizePolicy(sizePolicy);
        LabelPartSize3->setMinimumSize(QSize(75, 25));

        gridLayout_7->addWidget(LabelPartSize3, 2, 0, 1, 1);

        ValuePartSize3 = new QDoubleSpinBox(layoutWidget16);
        ValuePartSize3->setObjectName(QString::fromUtf8("ValuePartSize3"));
        sizePolicy.setHeightForWidth(ValuePartSize3->sizePolicy().hasHeightForWidth());
        ValuePartSize3->setSizePolicy(sizePolicy);
        ValuePartSize3->setMinimumSize(QSize(60, 20));
        ValuePartSize3->setMaximumSize(QSize(60, 20));
        ValuePartSize3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePartSize3->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePartSize3->setDecimals(1);
        ValuePartSize3->setMaximum(50000);

        gridLayout_7->addWidget(ValuePartSize3, 2, 1, 1, 1);

        LabelPartSizeUnit3 = new QLabel(layoutWidget16);
        LabelPartSizeUnit3->setObjectName(QString::fromUtf8("LabelPartSizeUnit3"));

        gridLayout_7->addWidget(LabelPartSizeUnit3, 2, 2, 1, 1);

        LabelMaterial = new QLabel(BoxPart);
        LabelMaterial->setObjectName(QString::fromUtf8("LabelMaterial"));
        LabelMaterial->setGeometry(QRect(22, 52, 75, 25));
        sizePolicy.setHeightForWidth(LabelMaterial->sizePolicy().hasHeightForWidth());
        LabelMaterial->setSizePolicy(sizePolicy);
        LabelMaterial->setMinimumSize(QSize(75, 25));
        ComMaterial = new QComboBox(BoxPart);
        ComMaterial->setObjectName(QString::fromUtf8("ComMaterial"));
        ComMaterial->setGeometry(QRect(72, 54, 211, 21));
        ComMaterial->setMinimumSize(QSize(150, 0));
        CheckShowThickness = new QCheckBox(BoxPart);
        CheckShowThickness->setObjectName(QString::fromUtf8("CheckShowThickness"));
        CheckShowThickness->setGeometry(QRect(210, 86, 71, 20));
        BoxPartTofd = new QGroupBox(scrollAreaWidgetContents_5);
        BoxPartTofd->setObjectName(QString::fromUtf8("BoxPartTofd"));
        BoxPartTofd->setGeometry(QRect(10, 399, 291, 341));
        gridLayoutWidget = new QWidget(BoxPartTofd);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(19, 25, 261, 238));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        LabelTofdScanMode = new QLabel(gridLayoutWidget);
        LabelTofdScanMode->setObjectName(QString::fromUtf8("LabelTofdScanMode"));

        gridLayout_3->addWidget(LabelTofdScanMode, 1, 0, 1, 1);

        ComBoxScanMode = new QComboBox(gridLayoutWidget);
        ComBoxScanMode->setObjectName(QString::fromUtf8("ComBoxScanMode"));
        ComBoxScanMode->setEnabled(false);

        gridLayout_3->addWidget(ComBoxScanMode, 1, 1, 1, 1);

        LabelTofdProMode = new QLabel(gridLayoutWidget);
        LabelTofdProMode->setObjectName(QString::fromUtf8("LabelTofdProMode"));

        gridLayout_3->addWidget(LabelTofdProMode, 2, 0, 1, 1);

        ComBoxProMode = new QComboBox(gridLayoutWidget);
        ComBoxProMode->setObjectName(QString::fromUtf8("ComBoxProMode"));

        gridLayout_3->addWidget(ComBoxProMode, 2, 1, 1, 1);

        LabelTofdWedgeSep = new QLabel(gridLayoutWidget);
        LabelTofdWedgeSep->setObjectName(QString::fromUtf8("LabelTofdWedgeSep"));

        gridLayout_3->addWidget(LabelTofdWedgeSep, 3, 0, 1, 1);

        SpinBoxWedgeSeperation = new QDoubleSpinBox(gridLayoutWidget);
        SpinBoxWedgeSeperation->setObjectName(QString::fromUtf8("SpinBoxWedgeSeperation"));
        SpinBoxWedgeSeperation->setMaximum(500);
        SpinBoxWedgeSeperation->setSingleStep(0.01);

        gridLayout_3->addWidget(SpinBoxWedgeSeperation, 3, 1, 1, 1);

        LabelCursorUnit3_8 = new QLabel(gridLayoutWidget);
        LabelCursorUnit3_8->setObjectName(QString::fromUtf8("LabelCursorUnit3_8"));

        gridLayout_3->addWidget(LabelCursorUnit3_8, 3, 2, 1, 1);

        LabelTofdPcs = new QLabel(gridLayoutWidget);
        LabelTofdPcs->setObjectName(QString::fromUtf8("LabelTofdPcs"));

        gridLayout_3->addWidget(LabelTofdPcs, 4, 0, 1, 1);

        SpinBoxPCS = new QDoubleSpinBox(gridLayoutWidget);
        SpinBoxPCS->setObjectName(QString::fromUtf8("SpinBoxPCS"));
        SpinBoxPCS->setEnabled(false);
        SpinBoxPCS->setMaximum(10000);

        gridLayout_3->addWidget(SpinBoxPCS, 4, 1, 1, 1);

        LabelCursorUnit3_9 = new QLabel(gridLayoutWidget);
        LabelCursorUnit3_9->setObjectName(QString::fromUtf8("LabelCursorUnit3_9"));

        gridLayout_3->addWidget(LabelCursorUnit3_9, 4, 2, 1, 1);

        LabelZeroOff = new QLabel(gridLayoutWidget);
        LabelZeroOff->setObjectName(QString::fromUtf8("LabelZeroOff"));

        gridLayout_3->addWidget(LabelZeroOff, 6, 0, 1, 1);

        SpinBoxZeroOff = new QDoubleSpinBox(gridLayoutWidget);
        SpinBoxZeroOff->setObjectName(QString::fromUtf8("SpinBoxZeroOff"));
        SpinBoxZeroOff->setDecimals(2);
        SpinBoxZeroOff->setMinimum(-50);
        SpinBoxZeroOff->setMaximum(50);
        SpinBoxZeroOff->setSingleStep(0.01);

        gridLayout_3->addWidget(SpinBoxZeroOff, 6, 1, 1, 1);

        LabelCursorUnit3_6 = new QLabel(gridLayoutWidget);
        LabelCursorUnit3_6->setObjectName(QString::fromUtf8("LabelCursorUnit3_6"));

        gridLayout_3->addWidget(LabelCursorUnit3_6, 6, 2, 1, 1);

        LabelDepthStart = new QLabel(gridLayoutWidget);
        LabelDepthStart->setObjectName(QString::fromUtf8("LabelDepthStart"));

        gridLayout_3->addWidget(LabelDepthStart, 7, 0, 1, 1);

        SpinBoxDepthStart = new QDoubleSpinBox(gridLayoutWidget);
        SpinBoxDepthStart->setObjectName(QString::fromUtf8("SpinBoxDepthStart"));
        SpinBoxDepthStart->setEnabled(true);
        SpinBoxDepthStart->setMaximum(500);
        SpinBoxDepthStart->setSingleStep(0.1);

        gridLayout_3->addWidget(SpinBoxDepthStart, 7, 1, 1, 1);

        LabelCursorUnit3_5 = new QLabel(gridLayoutWidget);
        LabelCursorUnit3_5->setObjectName(QString::fromUtf8("LabelCursorUnit3_5"));

        gridLayout_3->addWidget(LabelCursorUnit3_5, 7, 2, 1, 1);

        LabelDepthEnd = new QLabel(gridLayoutWidget);
        LabelDepthEnd->setObjectName(QString::fromUtf8("LabelDepthEnd"));

        gridLayout_3->addWidget(LabelDepthEnd, 8, 0, 1, 1);

        SpinBoxDepthEnd = new QDoubleSpinBox(gridLayoutWidget);
        SpinBoxDepthEnd->setObjectName(QString::fromUtf8("SpinBoxDepthEnd"));
        SpinBoxDepthEnd->setEnabled(true);
        SpinBoxDepthEnd->setDecimals(1);
        SpinBoxDepthEnd->setMaximum(500);
        SpinBoxDepthEnd->setSingleStep(0.1);

        gridLayout_3->addWidget(SpinBoxDepthEnd, 8, 1, 1, 1);

        LabelCursorUnit3_7 = new QLabel(gridLayoutWidget);
        LabelCursorUnit3_7->setObjectName(QString::fromUtf8("LabelCursorUnit3_7"));

        gridLayout_3->addWidget(LabelCursorUnit3_7, 8, 2, 1, 1);

        LabelTofdPcsCal = new QLabel(gridLayoutWidget);
        LabelTofdPcsCal->setObjectName(QString::fromUtf8("LabelTofdPcsCal"));

        gridLayout_3->addWidget(LabelTofdPcsCal, 5, 0, 1, 1);

        SpinBoxCalPCS = new QDoubleSpinBox(gridLayoutWidget);
        SpinBoxCalPCS->setObjectName(QString::fromUtf8("SpinBoxCalPCS"));
        SpinBoxCalPCS->setEnabled(false);
        SpinBoxCalPCS->setMaximum(10000);

        gridLayout_3->addWidget(SpinBoxCalPCS, 5, 1, 1, 1);

        LabelCalPCSUnit = new QLabel(gridLayoutWidget);
        LabelCalPCSUnit->setObjectName(QString::fromUtf8("LabelCalPCSUnit"));

        gridLayout_3->addWidget(LabelCalPCSUnit, 5, 2, 1, 1);

        LabelShowLwBw = new QLabel(gridLayoutWidget);
        LabelShowLwBw->setObjectName(QString::fromUtf8("LabelShowLwBw"));

        gridLayout_3->addWidget(LabelShowLwBw, 0, 0, 1, 1);

        CheckLwBwShow = new QCheckBox(gridLayoutWidget);
        CheckLwBwShow->setObjectName(QString::fromUtf8("CheckLwBwShow"));

        gridLayout_3->addWidget(CheckLwBwShow, 0, 1, 1, 1);

        BoxDepthCal = new QGroupBox(BoxPartTofd);
        BoxDepthCal->setObjectName(QString::fromUtf8("BoxDepthCal"));
        BoxDepthCal->setGeometry(QRect(14, 270, 271, 61));
        gridLayoutWidget_2 = new QWidget(BoxDepthCal);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(3, 21, 261, 31));
        gridLayout_11 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        LabelDepthCal = new QLabel(gridLayoutWidget_2);
        LabelDepthCal->setObjectName(QString::fromUtf8("LabelDepthCal"));

        gridLayout_11->addWidget(LabelDepthCal, 0, 0, 1, 1);

        SpinBoxDepthCal = new QDoubleSpinBox(gridLayoutWidget_2);
        SpinBoxDepthCal->setObjectName(QString::fromUtf8("SpinBoxDepthCal"));
        SpinBoxDepthCal->setEnabled(true);
        SpinBoxDepthCal->setDecimals(1);
        SpinBoxDepthCal->setMaximum(500);
        SpinBoxDepthCal->setSingleStep(0.1);

        gridLayout_11->addWidget(SpinBoxDepthCal, 0, 1, 1, 1);

        LabelCursorUnit3_19 = new QLabel(gridLayoutWidget_2);
        LabelCursorUnit3_19->setObjectName(QString::fromUtf8("LabelCursorUnit3_19"));

        gridLayout_11->addWidget(LabelCursorUnit3_19, 0, 2, 1, 1);

        BtnDepthCal = new QPushButton(gridLayoutWidget_2);
        BtnDepthCal->setObjectName(QString::fromUtf8("BtnDepthCal"));

        gridLayout_11->addWidget(BtnDepthCal, 0, 3, 1, 1);

        BoxPartPosition = new QGroupBox(scrollAreaWidgetContents_5);
        BoxPartPosition->setObjectName(QString::fromUtf8("BoxPartPosition"));
        BoxPartPosition->setGeometry(QRect(10, 220, 291, 111));
        layoutWidget13 = new QWidget(BoxPartPosition);
        layoutWidget13->setObjectName(QString::fromUtf8("layoutWidget13"));
        layoutWidget13->setGeometry(QRect(20, 21, 201, 92));
        gridLayout_9 = new QGridLayout(layoutWidget13);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        LabelScanOffset = new QLabel(layoutWidget13);
        LabelScanOffset->setObjectName(QString::fromUtf8("LabelScanOffset"));
        sizePolicy.setHeightForWidth(LabelScanOffset->sizePolicy().hasHeightForWidth());
        LabelScanOffset->setSizePolicy(sizePolicy);
        LabelScanOffset->setMinimumSize(QSize(75, 25));

        gridLayout_9->addWidget(LabelScanOffset, 0, 0, 1, 1);

        ValueScanOffset = new QDoubleSpinBox(layoutWidget13);
        ValueScanOffset->setObjectName(QString::fromUtf8("ValueScanOffset"));
        sizePolicy.setHeightForWidth(ValueScanOffset->sizePolicy().hasHeightForWidth());
        ValueScanOffset->setSizePolicy(sizePolicy);
        ValueScanOffset->setMinimumSize(QSize(60, 20));
        ValueScanOffset->setMaximumSize(QSize(60, 20));
        ValueScanOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueScanOffset->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanOffset->setDecimals(1);
        ValueScanOffset->setMinimum(-10000);
        ValueScanOffset->setMaximum(10000);

        gridLayout_9->addWidget(ValueScanOffset, 0, 1, 1, 1);

        LabelScanOffsetUnit = new QLabel(layoutWidget13);
        LabelScanOffsetUnit->setObjectName(QString::fromUtf8("LabelScanOffsetUnit"));

        gridLayout_9->addWidget(LabelScanOffsetUnit, 0, 2, 1, 1);

        LabelIndexOffset = new QLabel(layoutWidget13);
        LabelIndexOffset->setObjectName(QString::fromUtf8("LabelIndexOffset"));
        sizePolicy.setHeightForWidth(LabelIndexOffset->sizePolicy().hasHeightForWidth());
        LabelIndexOffset->setSizePolicy(sizePolicy);
        LabelIndexOffset->setMinimumSize(QSize(75, 25));

        gridLayout_9->addWidget(LabelIndexOffset, 1, 0, 1, 1);

        ValueIndexOffset = new QDoubleSpinBox(layoutWidget13);
        ValueIndexOffset->setObjectName(QString::fromUtf8("ValueIndexOffset"));
        sizePolicy.setHeightForWidth(ValueIndexOffset->sizePolicy().hasHeightForWidth());
        ValueIndexOffset->setSizePolicy(sizePolicy);
        ValueIndexOffset->setMinimumSize(QSize(60, 20));
        ValueIndexOffset->setMaximumSize(QSize(60, 20));
        ValueIndexOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueIndexOffset->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexOffset->setDecimals(1);
        ValueIndexOffset->setMinimum(-10000);
        ValueIndexOffset->setMaximum(10000);

        gridLayout_9->addWidget(ValueIndexOffset, 1, 1, 1, 1);

        LabelIndexOffsetUnit = new QLabel(layoutWidget13);
        LabelIndexOffsetUnit->setObjectName(QString::fromUtf8("LabelIndexOffsetUnit"));

        gridLayout_9->addWidget(LabelIndexOffsetUnit, 1, 2, 1, 1);

        LabelSkewAngle = new QLabel(layoutWidget13);
        LabelSkewAngle->setObjectName(QString::fromUtf8("LabelSkewAngle"));
        sizePolicy.setHeightForWidth(LabelSkewAngle->sizePolicy().hasHeightForWidth());
        LabelSkewAngle->setSizePolicy(sizePolicy);
        LabelSkewAngle->setMinimumSize(QSize(80, 25));
        LabelSkewAngle->setMaximumSize(QSize(40, 16777215));

        gridLayout_9->addWidget(LabelSkewAngle, 2, 0, 1, 1);

        ComSkewAngle = new QComboBox(layoutWidget13);
        ComSkewAngle->setObjectName(QString::fromUtf8("ComSkewAngle"));

        gridLayout_9->addWidget(ComSkewAngle, 2, 1, 1, 2);

        scrollGeometry->setWidget(scrollAreaWidgetContents_5);

        verticalLayout_6->addWidget(scrollGeometry);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-05.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(Geometry, icon4, QString::fromUtf8("Geometry"));
        Measurement = new QWidget();
        Measurement->setObjectName(QString::fromUtf8("Measurement"));
        Measurement->setGeometry(QRect(0, -143, 313, 850));
        verticalLayout_7 = new QVBoxLayout(Measurement);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollAreaMeasure = new QScrollArea(Measurement);
        scrollAreaMeasure->setObjectName(QString::fromUtf8("scrollAreaMeasure"));
        scrollAreaMeasure->setMinimumSize(QSize(0, 850));
        scrollAreaMeasure->setWidgetResizable(true);
        scrollAreaWidgetContents_8 = new QWidget();
        scrollAreaWidgetContents_8->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_8"));
        scrollAreaWidgetContents_8->setGeometry(QRect(0, 0, 309, 846));
        LabelMeasureValue = new QLabel(scrollAreaWidgetContents_8);
        LabelMeasureValue->setObjectName(QString::fromUtf8("LabelMeasureValue"));
        LabelMeasureValue->setGeometry(QRect(10, 10, 111, 16));
        line_6 = new QFrame(scrollAreaWidgetContents_8);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(11, 26, 201, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        LabelCursor = new QLabel(scrollAreaWidgetContents_8);
        LabelCursor->setObjectName(QString::fromUtf8("LabelCursor"));
        LabelCursor->setGeometry(QRect(10, 210, 81, 16));
        line_7 = new QFrame(scrollAreaWidgetContents_8);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(10, 225, 201, 20));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        CheckMeasureShow = new QCheckBox(scrollAreaWidgetContents_8);
        CheckMeasureShow->setObjectName(QString::fromUtf8("CheckMeasureShow"));
        CheckMeasureShow->setGeometry(QRect(130, 10, 71, 16));
        CheckCursorShow = new QCheckBox(scrollAreaWidgetContents_8);
        CheckCursorShow->setObjectName(QString::fromUtf8("CheckCursorShow"));
        CheckCursorShow->setGeometry(QRect(130, 210, 71, 16));
        layoutWidget17 = new QWidget(scrollAreaWidgetContents_8);
        layoutWidget17->setObjectName(QString::fromUtf8("layoutWidget17"));
        layoutWidget17->setGeometry(QRect(21, 41, 241, 151));
        gridLayout_15 = new QGridLayout(layoutWidget17);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        LabelField1 = new QLabel(layoutWidget17);
        LabelField1->setObjectName(QString::fromUtf8("LabelField1"));
        sizePolicy.setHeightForWidth(LabelField1->sizePolicy().hasHeightForWidth());
        LabelField1->setSizePolicy(sizePolicy);
        LabelField1->setMinimumSize(QSize(75, 25));

        gridLayout_15->addWidget(LabelField1, 0, 0, 1, 1);

        ComField1 = new QComboBox(layoutWidget17);
        ComField1->setObjectName(QString::fromUtf8("ComField1"));

        gridLayout_15->addWidget(ComField1, 0, 1, 1, 1);

        LabelField2 = new QLabel(layoutWidget17);
        LabelField2->setObjectName(QString::fromUtf8("LabelField2"));
        sizePolicy.setHeightForWidth(LabelField2->sizePolicy().hasHeightForWidth());
        LabelField2->setSizePolicy(sizePolicy);
        LabelField2->setMinimumSize(QSize(75, 25));

        gridLayout_15->addWidget(LabelField2, 1, 0, 1, 1);

        ComField2 = new QComboBox(layoutWidget17);
        ComField2->setObjectName(QString::fromUtf8("ComField2"));

        gridLayout_15->addWidget(ComField2, 1, 1, 1, 1);

        LabelField3 = new QLabel(layoutWidget17);
        LabelField3->setObjectName(QString::fromUtf8("LabelField3"));
        sizePolicy.setHeightForWidth(LabelField3->sizePolicy().hasHeightForWidth());
        LabelField3->setSizePolicy(sizePolicy);
        LabelField3->setMinimumSize(QSize(75, 25));

        gridLayout_15->addWidget(LabelField3, 2, 0, 1, 1);

        ComField3 = new QComboBox(layoutWidget17);
        ComField3->setObjectName(QString::fromUtf8("ComField3"));

        gridLayout_15->addWidget(ComField3, 2, 1, 1, 1);

        LabelField4 = new QLabel(layoutWidget17);
        LabelField4->setObjectName(QString::fromUtf8("LabelField4"));
        sizePolicy.setHeightForWidth(LabelField4->sizePolicy().hasHeightForWidth());
        LabelField4->setSizePolicy(sizePolicy);
        LabelField4->setMinimumSize(QSize(75, 25));

        gridLayout_15->addWidget(LabelField4, 3, 0, 1, 1);

        ComField4 = new QComboBox(layoutWidget17);
        ComField4->setObjectName(QString::fromUtf8("ComField4"));

        gridLayout_15->addWidget(ComField4, 3, 1, 1, 1);

        LabelField5 = new QLabel(layoutWidget17);
        LabelField5->setObjectName(QString::fromUtf8("LabelField5"));
        sizePolicy.setHeightForWidth(LabelField5->sizePolicy().hasHeightForWidth());
        LabelField5->setSizePolicy(sizePolicy);
        LabelField5->setMinimumSize(QSize(75, 25));

        gridLayout_15->addWidget(LabelField5, 4, 0, 1, 1);

        ComField5 = new QComboBox(layoutWidget17);
        ComField5->setObjectName(QString::fromUtf8("ComField5"));

        gridLayout_15->addWidget(ComField5, 4, 1, 1, 1);

        layoutWidget18 = new QWidget(scrollAreaWidgetContents_8);
        layoutWidget18->setObjectName(QString::fromUtf8("layoutWidget18"));
        layoutWidget18->setGeometry(QRect(22, 240, 271, 244));
        gridLayout_16 = new QGridLayout(layoutWidget18);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        gridLayout_16->setContentsMargins(0, 0, 0, 0);
        ValueARef = new QDoubleSpinBox(layoutWidget18);
        ValueARef->setObjectName(QString::fromUtf8("ValueARef"));
        sizePolicy.setHeightForWidth(ValueARef->sizePolicy().hasHeightForWidth());
        ValueARef->setSizePolicy(sizePolicy);
        ValueARef->setMinimumSize(QSize(60, 20));
        ValueARef->setMaximumSize(QSize(60, 20));
        ValueARef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueARef->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueARef->setDecimals(1);
        ValueARef->setMinimum(-10000);
        ValueARef->setMaximum(10000);

        gridLayout_16->addWidget(ValueARef, 0, 1, 1, 1);

        LabelCursorUnit1 = new QLabel(layoutWidget18);
        LabelCursorUnit1->setObjectName(QString::fromUtf8("LabelCursorUnit1"));

        gridLayout_16->addWidget(LabelCursorUnit1, 0, 2, 1, 1);

        label_199 = new QLabel(layoutWidget18);
        label_199->setObjectName(QString::fromUtf8("label_199"));
        sizePolicy.setHeightForWidth(label_199->sizePolicy().hasHeightForWidth());
        label_199->setSizePolicy(sizePolicy);
        label_199->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_199, 1, 0, 1, 1);

        ValueAMes = new QDoubleSpinBox(layoutWidget18);
        ValueAMes->setObjectName(QString::fromUtf8("ValueAMes"));
        sizePolicy.setHeightForWidth(ValueAMes->sizePolicy().hasHeightForWidth());
        ValueAMes->setSizePolicy(sizePolicy);
        ValueAMes->setMinimumSize(QSize(60, 20));
        ValueAMes->setMaximumSize(QSize(60, 20));
        ValueAMes->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueAMes->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueAMes->setDecimals(1);
        ValueAMes->setMinimum(-10000);
        ValueAMes->setMaximum(10000);

        gridLayout_16->addWidget(ValueAMes, 1, 1, 1, 1);

        LabelCursorUnit2 = new QLabel(layoutWidget18);
        LabelCursorUnit2->setObjectName(QString::fromUtf8("LabelCursorUnit2"));

        gridLayout_16->addWidget(LabelCursorUnit2, 1, 2, 1, 1);

        label_201 = new QLabel(layoutWidget18);
        label_201->setObjectName(QString::fromUtf8("label_201"));
        sizePolicy.setHeightForWidth(label_201->sizePolicy().hasHeightForWidth());
        label_201->setSizePolicy(sizePolicy);
        label_201->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_201, 2, 0, 1, 1);

        ValueURef = new QDoubleSpinBox(layoutWidget18);
        ValueURef->setObjectName(QString::fromUtf8("ValueURef"));
        sizePolicy.setHeightForWidth(ValueURef->sizePolicy().hasHeightForWidth());
        ValueURef->setSizePolicy(sizePolicy);
        ValueURef->setMinimumSize(QSize(60, 20));
        ValueURef->setMaximumSize(QSize(60, 20));
        ValueURef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueURef->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueURef->setDecimals(1);
        ValueURef->setMinimum(-10000);
        ValueURef->setMaximum(10000);
        ValueURef->setSingleStep(0.1);

        gridLayout_16->addWidget(ValueURef, 2, 1, 1, 1);

        LabelCursorUnit3 = new QLabel(layoutWidget18);
        LabelCursorUnit3->setObjectName(QString::fromUtf8("LabelCursorUnit3"));

        gridLayout_16->addWidget(LabelCursorUnit3, 2, 2, 1, 1);

        label_203 = new QLabel(layoutWidget18);
        label_203->setObjectName(QString::fromUtf8("label_203"));
        sizePolicy.setHeightForWidth(label_203->sizePolicy().hasHeightForWidth());
        label_203->setSizePolicy(sizePolicy);
        label_203->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_203, 3, 0, 1, 1);

        ValueUMes = new QDoubleSpinBox(layoutWidget18);
        ValueUMes->setObjectName(QString::fromUtf8("ValueUMes"));
        sizePolicy.setHeightForWidth(ValueUMes->sizePolicy().hasHeightForWidth());
        ValueUMes->setSizePolicy(sizePolicy);
        ValueUMes->setMinimumSize(QSize(60, 20));
        ValueUMes->setMaximumSize(QSize(60, 20));
        ValueUMes->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueUMes->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueUMes->setDecimals(1);
        ValueUMes->setMinimum(-10000);
        ValueUMes->setMaximum(10000);
        ValueUMes->setSingleStep(0.1);

        gridLayout_16->addWidget(ValueUMes, 3, 1, 1, 1);

        LabelCursorUnit4 = new QLabel(layoutWidget18);
        LabelCursorUnit4->setObjectName(QString::fromUtf8("LabelCursorUnit4"));

        gridLayout_16->addWidget(LabelCursorUnit4, 3, 2, 1, 1);

        label_205 = new QLabel(layoutWidget18);
        label_205->setObjectName(QString::fromUtf8("label_205"));
        sizePolicy.setHeightForWidth(label_205->sizePolicy().hasHeightForWidth());
        label_205->setSizePolicy(sizePolicy);
        label_205->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_205, 4, 0, 1, 1);

        ValueSRef = new QDoubleSpinBox(layoutWidget18);
        ValueSRef->setObjectName(QString::fromUtf8("ValueSRef"));
        sizePolicy.setHeightForWidth(ValueSRef->sizePolicy().hasHeightForWidth());
        ValueSRef->setSizePolicy(sizePolicy);
        ValueSRef->setMinimumSize(QSize(60, 20));
        ValueSRef->setMaximumSize(QSize(60, 20));
        ValueSRef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSRef->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSRef->setDecimals(1);
        ValueSRef->setMinimum(-10000);
        ValueSRef->setMaximum(10000);

        gridLayout_16->addWidget(ValueSRef, 4, 1, 1, 1);

        LabelCursorUnit5 = new QLabel(layoutWidget18);
        LabelCursorUnit5->setObjectName(QString::fromUtf8("LabelCursorUnit5"));

        gridLayout_16->addWidget(LabelCursorUnit5, 4, 2, 1, 1);

        label_207 = new QLabel(layoutWidget18);
        label_207->setObjectName(QString::fromUtf8("label_207"));
        sizePolicy.setHeightForWidth(label_207->sizePolicy().hasHeightForWidth());
        label_207->setSizePolicy(sizePolicy);
        label_207->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_207, 5, 0, 1, 1);

        ValueSMes = new QDoubleSpinBox(layoutWidget18);
        ValueSMes->setObjectName(QString::fromUtf8("ValueSMes"));
        sizePolicy.setHeightForWidth(ValueSMes->sizePolicy().hasHeightForWidth());
        ValueSMes->setSizePolicy(sizePolicy);
        ValueSMes->setMinimumSize(QSize(60, 20));
        ValueSMes->setMaximumSize(QSize(60, 20));
        ValueSMes->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueSMes->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueSMes->setDecimals(1);
        ValueSMes->setMinimum(-10000);
        ValueSMes->setMaximum(10000);

        gridLayout_16->addWidget(ValueSMes, 5, 1, 1, 1);

        LabelCursorUnit6 = new QLabel(layoutWidget18);
        LabelCursorUnit6->setObjectName(QString::fromUtf8("LabelCursorUnit6"));

        gridLayout_16->addWidget(LabelCursorUnit6, 5, 2, 1, 1);

        label_209 = new QLabel(layoutWidget18);
        label_209->setObjectName(QString::fromUtf8("label_209"));
        sizePolicy.setHeightForWidth(label_209->sizePolicy().hasHeightForWidth());
        label_209->setSizePolicy(sizePolicy);
        label_209->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_209, 6, 0, 1, 1);

        ValueIRef = new QDoubleSpinBox(layoutWidget18);
        ValueIRef->setObjectName(QString::fromUtf8("ValueIRef"));
        sizePolicy.setHeightForWidth(ValueIRef->sizePolicy().hasHeightForWidth());
        ValueIRef->setSizePolicy(sizePolicy);
        ValueIRef->setMinimumSize(QSize(60, 20));
        ValueIRef->setMaximumSize(QSize(60, 20));
        ValueIRef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueIRef->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIRef->setDecimals(1);
        ValueIRef->setMinimum(-10000);
        ValueIRef->setMaximum(10000);

        gridLayout_16->addWidget(ValueIRef, 6, 1, 1, 1);

        LabelCursorUnit7 = new QLabel(layoutWidget18);
        LabelCursorUnit7->setObjectName(QString::fromUtf8("LabelCursorUnit7"));

        gridLayout_16->addWidget(LabelCursorUnit7, 6, 2, 1, 1);

        label_211 = new QLabel(layoutWidget18);
        label_211->setObjectName(QString::fromUtf8("label_211"));
        sizePolicy.setHeightForWidth(label_211->sizePolicy().hasHeightForWidth());
        label_211->setSizePolicy(sizePolicy);
        label_211->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_211, 7, 0, 1, 1);

        ValueIMes = new QDoubleSpinBox(layoutWidget18);
        ValueIMes->setObjectName(QString::fromUtf8("ValueIMes"));
        sizePolicy.setHeightForWidth(ValueIMes->sizePolicy().hasHeightForWidth());
        ValueIMes->setSizePolicy(sizePolicy);
        ValueIMes->setMinimumSize(QSize(60, 20));
        ValueIMes->setMaximumSize(QSize(60, 20));
        ValueIMes->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueIMes->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIMes->setDecimals(1);
        ValueIMes->setMinimum(-10000);
        ValueIMes->setMaximum(10000);

        gridLayout_16->addWidget(ValueIMes, 7, 1, 1, 1);

        LabelCursorUnit8 = new QLabel(layoutWidget18);
        LabelCursorUnit8->setObjectName(QString::fromUtf8("LabelCursorUnit8"));

        gridLayout_16->addWidget(LabelCursorUnit8, 7, 2, 1, 1);

        label_197 = new QLabel(layoutWidget18);
        label_197->setObjectName(QString::fromUtf8("label_197"));
        sizePolicy.setHeightForWidth(label_197->sizePolicy().hasHeightForWidth());
        label_197->setSizePolicy(sizePolicy);
        label_197->setMinimumSize(QSize(75, 25));

        gridLayout_16->addWidget(label_197, 0, 0, 1, 1);

        line_9 = new QFrame(scrollAreaWidgetContents_8);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setGeometry(QRect(10, 520, 201, 20));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        LabelDefect = new QLabel(scrollAreaWidgetContents_8);
        LabelDefect->setObjectName(QString::fromUtf8("LabelDefect"));
        LabelDefect->setGeometry(QRect(10, 505, 81, 16));
        CheckDefectShow = new QCheckBox(scrollAreaWidgetContents_8);
        CheckDefectShow->setObjectName(QString::fromUtf8("CheckDefectShow"));
        CheckDefectShow->setGeometry(QRect(140, 505, 81, 16));
        layoutWidget15_2 = new QWidget(scrollAreaWidgetContents_8);
        layoutWidget15_2->setObjectName(QString::fromUtf8("layoutWidget15_2"));
        layoutWidget15_2->setGeometry(QRect(20, 540, 281, 275));
        gridLayout_10 = new QGridLayout(layoutWidget15_2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        ComDefectIndex = new QComboBox(layoutWidget15_2);
        ComDefectIndex->setObjectName(QString::fromUtf8("ComDefectIndex"));
        ComDefectIndex->setMaximumSize(QSize(150, 16777215));
        ComDefectIndex->setLayoutDirection(Qt::LeftToRight);

        gridLayout_10->addWidget(ComDefectIndex, 0, 1, 1, 1);

        LabelDefectIndex = new QLabel(layoutWidget15_2);
        LabelDefectIndex->setObjectName(QString::fromUtf8("LabelDefectIndex"));
        sizePolicy.setHeightForWidth(LabelDefectIndex->sizePolicy().hasHeightForWidth());
        LabelDefectIndex->setSizePolicy(sizePolicy);
        LabelDefectIndex->setMinimumSize(QSize(75, 25));
        LabelDefectIndex->setMaximumSize(QSize(50, 16777215));

        gridLayout_10->addWidget(LabelDefectIndex, 0, 0, 1, 1);

        labelDefectStart = new QLabel(layoutWidget15_2);
        labelDefectStart->setObjectName(QString::fromUtf8("labelDefectStart"));
        sizePolicy.setHeightForWidth(labelDefectStart->sizePolicy().hasHeightForWidth());
        labelDefectStart->setSizePolicy(sizePolicy);
        labelDefectStart->setMinimumSize(QSize(75, 25));
        labelDefectStart->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(labelDefectStart, 2, 0, 1, 1);

        ValueDefectLStart = new QDoubleSpinBox(layoutWidget15_2);
        ValueDefectLStart->setObjectName(QString::fromUtf8("ValueDefectLStart"));
        ValueDefectLStart->setMaximumSize(QSize(150, 16777215));
        ValueDefectLStart->setAlignment(Qt::AlignCenter);
        ValueDefectLStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueDefectLStart->setKeyboardTracking(true);
        ValueDefectLStart->setDecimals(1);
        ValueDefectLStart->setMinimum(-10000);
        ValueDefectLStart->setMaximum(10000);

        gridLayout_10->addWidget(ValueDefectLStart, 2, 1, 1, 1);

        LabelCursorUnit3_2 = new QLabel(layoutWidget15_2);
        LabelCursorUnit3_2->setObjectName(QString::fromUtf8("LabelCursorUnit3_2"));
        LabelCursorUnit3_2->setMaximumSize(QSize(30, 16777215));

        gridLayout_10->addWidget(LabelCursorUnit3_2, 2, 2, 1, 1);

        labelDefectLength = new QLabel(layoutWidget15_2);
        labelDefectLength->setObjectName(QString::fromUtf8("labelDefectLength"));
        sizePolicy.setHeightForWidth(labelDefectLength->sizePolicy().hasHeightForWidth());
        labelDefectLength->setSizePolicy(sizePolicy);
        labelDefectLength->setMinimumSize(QSize(75, 25));
        labelDefectLength->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(labelDefectLength, 3, 0, 1, 1);

        ValueDefectLength = new QDoubleSpinBox(layoutWidget15_2);
        ValueDefectLength->setObjectName(QString::fromUtf8("ValueDefectLength"));
        ValueDefectLength->setMaximumSize(QSize(150, 16777215));
        ValueDefectLength->setAlignment(Qt::AlignCenter);
        ValueDefectLength->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueDefectLength->setKeyboardTracking(true);
        ValueDefectLength->setDecimals(1);
        ValueDefectLength->setMinimum(-10000);
        ValueDefectLength->setMaximum(10000);

        gridLayout_10->addWidget(ValueDefectLength, 3, 1, 1, 1);

        LabelCursorUnit3_3 = new QLabel(layoutWidget15_2);
        LabelCursorUnit3_3->setObjectName(QString::fromUtf8("LabelCursorUnit3_3"));

        gridLayout_10->addWidget(LabelCursorUnit3_3, 3, 2, 1, 1);

        labelDefectDepth = new QLabel(layoutWidget15_2);
        labelDefectDepth->setObjectName(QString::fromUtf8("labelDefectDepth"));
        sizePolicy.setHeightForWidth(labelDefectDepth->sizePolicy().hasHeightForWidth());
        labelDefectDepth->setSizePolicy(sizePolicy);
        labelDefectDepth->setMinimumSize(QSize(75, 25));
        labelDefectDepth->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(labelDefectDepth, 4, 0, 1, 1);

        ValueDefectHStart = new QDoubleSpinBox(layoutWidget15_2);
        ValueDefectHStart->setObjectName(QString::fromUtf8("ValueDefectHStart"));
        ValueDefectHStart->setMaximumSize(QSize(150, 16777215));
        ValueDefectHStart->setAlignment(Qt::AlignCenter);
        ValueDefectHStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueDefectHStart->setKeyboardTracking(true);
        ValueDefectHStart->setDecimals(1);
        ValueDefectHStart->setMinimum(-10000);
        ValueDefectHStart->setMaximum(10000);

        gridLayout_10->addWidget(ValueDefectHStart, 4, 1, 1, 1);

        LabelCursorUnit3_4 = new QLabel(layoutWidget15_2);
        LabelCursorUnit3_4->setObjectName(QString::fromUtf8("LabelCursorUnit3_4"));

        gridLayout_10->addWidget(LabelCursorUnit3_4, 4, 2, 1, 1);

        labelDefectHeight = new QLabel(layoutWidget15_2);
        labelDefectHeight->setObjectName(QString::fromUtf8("labelDefectHeight"));
        sizePolicy.setHeightForWidth(labelDefectHeight->sizePolicy().hasHeightForWidth());
        labelDefectHeight->setSizePolicy(sizePolicy);
        labelDefectHeight->setMinimumSize(QSize(75, 25));
        labelDefectHeight->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(labelDefectHeight, 5, 0, 1, 1);

        ValueDefectHeight = new QDoubleSpinBox(layoutWidget15_2);
        ValueDefectHeight->setObjectName(QString::fromUtf8("ValueDefectHeight"));
        ValueDefectHeight->setMaximumSize(QSize(150, 16777215));
        ValueDefectHeight->setAlignment(Qt::AlignCenter);
        ValueDefectHeight->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueDefectHeight->setKeyboardTracking(true);
        ValueDefectHeight->setDecimals(1);
        ValueDefectHeight->setMinimum(-10000);
        ValueDefectHeight->setMaximum(10000);

        gridLayout_10->addWidget(ValueDefectHeight, 5, 1, 1, 1);

        LabelCursorUnit3_10 = new QLabel(layoutWidget15_2);
        LabelCursorUnit3_10->setObjectName(QString::fromUtf8("LabelCursorUnit3_10"));

        gridLayout_10->addWidget(LabelCursorUnit3_10, 5, 2, 1, 1);

        LabelCursorUnit3_11 = new QLabel(layoutWidget15_2);
        LabelCursorUnit3_11->setObjectName(QString::fromUtf8("LabelCursorUnit3_11"));

        gridLayout_10->addWidget(LabelCursorUnit3_11, 6, 2, 1, 1);

        ValueDefectWStart = new QDoubleSpinBox(layoutWidget15_2);
        ValueDefectWStart->setObjectName(QString::fromUtf8("ValueDefectWStart"));
        ValueDefectWStart->setMaximumSize(QSize(150, 16777215));
        ValueDefectWStart->setAlignment(Qt::AlignCenter);
        ValueDefectWStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueDefectWStart->setKeyboardTracking(true);
        ValueDefectWStart->setDecimals(1);
        ValueDefectWStart->setMinimum(-10000);
        ValueDefectWStart->setMaximum(10000);

        gridLayout_10->addWidget(ValueDefectWStart, 6, 1, 1, 1);

        labelDefectOffset = new QLabel(layoutWidget15_2);
        labelDefectOffset->setObjectName(QString::fromUtf8("labelDefectOffset"));
        sizePolicy.setHeightForWidth(labelDefectOffset->sizePolicy().hasHeightForWidth());
        labelDefectOffset->setSizePolicy(sizePolicy);
        labelDefectOffset->setMinimumSize(QSize(75, 25));
        labelDefectOffset->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(labelDefectOffset, 6, 0, 1, 1);

        ValueDefectWidth = new QDoubleSpinBox(layoutWidget15_2);
        ValueDefectWidth->setObjectName(QString::fromUtf8("ValueDefectWidth"));
        ValueDefectWidth->setMaximumSize(QSize(150, 16777215));
        ValueDefectWidth->setAlignment(Qt::AlignCenter);
        ValueDefectWidth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueDefectWidth->setKeyboardTracking(true);
        ValueDefectWidth->setDecimals(1);
        ValueDefectWidth->setMinimum(-10000);
        ValueDefectWidth->setMaximum(10000);

        gridLayout_10->addWidget(ValueDefectWidth, 7, 1, 1, 1);

        labelDefectWidth = new QLabel(layoutWidget15_2);
        labelDefectWidth->setObjectName(QString::fromUtf8("labelDefectWidth"));
        sizePolicy.setHeightForWidth(labelDefectWidth->sizePolicy().hasHeightForWidth());
        labelDefectWidth->setSizePolicy(sizePolicy);
        labelDefectWidth->setMinimumSize(QSize(75, 25));
        labelDefectWidth->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(labelDefectWidth, 7, 0, 1, 1);

        LabelCursorUnit3_12 = new QLabel(layoutWidget15_2);
        LabelCursorUnit3_12->setObjectName(QString::fromUtf8("LabelCursorUnit3_12"));

        gridLayout_10->addWidget(LabelCursorUnit3_12, 7, 2, 1, 1);

        BtnDefectDelete = new QPushButton(layoutWidget15_2);
        BtnDefectDelete->setObjectName(QString::fromUtf8("BtnDefectDelete"));
        BtnDefectDelete->setMinimumSize(QSize(100, 0));
        BtnDefectDelete->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_10->addWidget(BtnDefectDelete, 8, 1, 1, 1);

        LabelReMark = new QLabel(layoutWidget15_2);
        LabelReMark->setObjectName(QString::fromUtf8("LabelReMark"));
        sizePolicy.setHeightForWidth(LabelReMark->sizePolicy().hasHeightForWidth());
        LabelReMark->setSizePolicy(sizePolicy);
        LabelReMark->setMinimumSize(QSize(75, 25));
        LabelReMark->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(LabelReMark, 1, 0, 1, 1);

        lineEditReMark = new QLineEdit(layoutWidget15_2);
        lineEditReMark->setObjectName(QString::fromUtf8("lineEditReMark"));
        lineEditReMark->setMaximumSize(QSize(150, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        lineEditReMark->setFont(font1);
        lineEditReMark->setInputMethodHints(Qt::ImhUppercaseOnly);
        lineEditReMark->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(lineEditReMark, 1, 1, 1, 1);

        CheckBackShow = new QCheckBox(scrollAreaWidgetContents_8);
        CheckBackShow->setObjectName(QString::fromUtf8("CheckBackShow"));
        CheckBackShow->setGeometry(QRect(202, 10, 90, 16));
        CheckCursorSync = new QCheckBox(scrollAreaWidgetContents_8);
        CheckCursorSync->setObjectName(QString::fromUtf8("CheckCursorSync"));
        CheckCursorSync->setGeometry(QRect(202, 210, 90, 16));
        scrollAreaMeasure->setWidget(scrollAreaWidgetContents_8);

        verticalLayout_7->addWidget(scrollAreaMeasure);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-06.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(Measurement, icon5, QString::fromUtf8("Measurement"));
        Display = new QWidget();
        Display->setObjectName(QString::fromUtf8("Display"));
        Display->setGeometry(QRect(0, 0, 313, 750));
        verticalLayout_12 = new QVBoxLayout(Display);
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        scrollAreaDisplay = new QScrollArea(Display);
        scrollAreaDisplay->setObjectName(QString::fromUtf8("scrollAreaDisplay"));
        scrollAreaDisplay->setMinimumSize(QSize(0, 750));
        scrollAreaDisplay->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 309, 746));
        treeView = new QTreeView(scrollAreaWidgetContents_6);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(3, 2, 301, 361));
        treeView->setDragEnabled(true);
        LabelLanguage = new QLabel(scrollAreaWidgetContents_6);
        LabelLanguage->setObjectName(QString::fromUtf8("LabelLanguage"));
        LabelLanguage->setGeometry(QRect(40, 813, 58, 15));
        groupBox = new QGroupBox(scrollAreaWidgetContents_6);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(3, 370, 301, 261));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(7, 151, 291, 71));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        LabelCScanSource1 = new QLabel(layoutWidget);
        LabelCScanSource1->setObjectName(QString::fromUtf8("LabelCScanSource1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, LabelCScanSource1);

        ComCScanSource1 = new QComboBox(layoutWidget);
        ComCScanSource1->setObjectName(QString::fromUtf8("ComCScanSource1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, ComCScanSource1);

        LabelCScanSource2 = new QLabel(layoutWidget);
        LabelCScanSource2->setObjectName(QString::fromUtf8("LabelCScanSource2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, LabelCScanSource2);

        ComCScanSource2 = new QComboBox(layoutWidget);
        ComCScanSource2->setObjectName(QString::fromUtf8("ComCScanSource2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, ComCScanSource2);

        LabelCScanThickness = new QLabel(layoutWidget);
        LabelCScanThickness->setObjectName(QString::fromUtf8("LabelCScanThickness"));

        formLayout->setWidget(2, QFormLayout::LabelRole, LabelCScanThickness);

        horizontalLayoutWidget_3 = new QWidget(groupBox);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(7, 223, 291, 31));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        LabelCScanThicknessMin = new QLabel(horizontalLayoutWidget_3);
        LabelCScanThicknessMin->setObjectName(QString::fromUtf8("LabelCScanThicknessMin"));

        horizontalLayout_9->addWidget(LabelCScanThicknessMin);

        ValueCScanThicknessMin = new QDoubleSpinBox(horizontalLayoutWidget_3);
        ValueCScanThicknessMin->setObjectName(QString::fromUtf8("ValueCScanThicknessMin"));
        sizePolicy.setHeightForWidth(ValueCScanThicknessMin->sizePolicy().hasHeightForWidth());
        ValueCScanThicknessMin->setSizePolicy(sizePolicy);
        ValueCScanThicknessMin->setMinimumSize(QSize(60, 20));
        ValueCScanThicknessMin->setMaximumSize(QSize(60, 20));
        ValueCScanThicknessMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueCScanThicknessMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueCScanThicknessMin->setDecimals(1);
        ValueCScanThicknessMin->setMaximum(300);
        ValueCScanThicknessMin->setSingleStep(0.1);

        horizontalLayout_9->addWidget(ValueCScanThicknessMin);

        LabelCScanThicknessMax_3 = new QLabel(horizontalLayoutWidget_3);
        LabelCScanThicknessMax_3->setObjectName(QString::fromUtf8("LabelCScanThicknessMax_3"));

        horizontalLayout_9->addWidget(LabelCScanThicknessMax_3);

        LabelCScanThicknessMax = new QLabel(horizontalLayoutWidget_3);
        LabelCScanThicknessMax->setObjectName(QString::fromUtf8("LabelCScanThicknessMax"));

        horizontalLayout_9->addWidget(LabelCScanThicknessMax);

        ValueCScanThicknessMax = new QDoubleSpinBox(horizontalLayoutWidget_3);
        ValueCScanThicknessMax->setObjectName(QString::fromUtf8("ValueCScanThicknessMax"));
        sizePolicy.setHeightForWidth(ValueCScanThicknessMax->sizePolicy().hasHeightForWidth());
        ValueCScanThicknessMax->setSizePolicy(sizePolicy);
        ValueCScanThicknessMax->setMinimumSize(QSize(60, 20));
        ValueCScanThicknessMax->setMaximumSize(QSize(60, 20));
        ValueCScanThicknessMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueCScanThicknessMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueCScanThicknessMax->setDecimals(1);
        ValueCScanThicknessMax->setMaximum(300);
        ValueCScanThicknessMax->setSingleStep(0.1);

        horizontalLayout_9->addWidget(ValueCScanThicknessMax);

        LabelCScanThicknessMax_2 = new QLabel(horizontalLayoutWidget_3);
        LabelCScanThicknessMax_2->setObjectName(QString::fromUtf8("LabelCScanThicknessMax_2"));

        horizontalLayout_9->addWidget(LabelCScanThicknessMax_2);

        horizontalLayoutWidget_4 = new QWidget(groupBox);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(8, 19, 291, 31));
        horizontalLayout_14 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        ComColorLineSelection = new QComboBox(horizontalLayoutWidget_4);
        ComColorLineSelection->setObjectName(QString::fromUtf8("ComColorLineSelection"));

        horizontalLayout_14->addWidget(ComColorLineSelection);

        ComColorLineColor = new QComboBox(horizontalLayoutWidget_4);
        ComColorLineColor->setObjectName(QString::fromUtf8("ComColorLineColor"));

        horizontalLayout_14->addWidget(ComColorLineColor);

        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(8, 57, 291, 89));
        formLayout_3 = new QFormLayout(layoutWidget_2);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        LabelAmpColor = new QLabel(layoutWidget_2);
        LabelAmpColor->setObjectName(QString::fromUtf8("LabelAmpColor"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, LabelAmpColor);

        BtnColorAmp = new DopplerColorBtn(layoutWidget_2);
        BtnColorAmp->setObjectName(QString::fromUtf8("BtnColorAmp"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, BtnColorAmp);

        LabelColorRF = new QLabel(layoutWidget_2);
        LabelColorRF->setObjectName(QString::fromUtf8("LabelColorRF"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, LabelColorRF);

        BtnColorRf = new DopplerColorBtn(layoutWidget_2);
        BtnColorRf->setObjectName(QString::fromUtf8("BtnColorRf"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, BtnColorRf);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_5);

        BtnColorThickness = new DopplerColorBtn(layoutWidget_2);
        BtnColorThickness->setObjectName(QString::fromUtf8("BtnColorThickness"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, BtnColorThickness);

        ComLanguage = new QComboBox(scrollAreaWidgetContents_6);
        ComLanguage->setObjectName(QString::fromUtf8("ComLanguage"));
        ComLanguage->setGeometry(QRect(107, 810, 161, 22));
        groupBoxComDisp = new QGroupBox(scrollAreaWidgetContents_6);
        groupBoxComDisp->setObjectName(QString::fromUtf8("groupBoxComDisp"));
        groupBoxComDisp->setGeometry(QRect(4, 640, 301, 81));
        horizontalLayoutWidget_7 = new QWidget(groupBoxComDisp);
        horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(5, 17, 312, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        ComComDisp1 = new QComboBox(horizontalLayoutWidget_7);
        ComComDisp1->setObjectName(QString::fromUtf8("ComComDisp1"));

        horizontalLayout_4->addWidget(ComComDisp1);

        ComComDisp2 = new QComboBox(horizontalLayoutWidget_7);
        ComComDisp2->setObjectName(QString::fromUtf8("ComComDisp2"));

        horizontalLayout_4->addWidget(ComComDisp2);

        ComComDisp3 = new QComboBox(horizontalLayoutWidget_7);
        ComComDisp3->setObjectName(QString::fromUtf8("ComComDisp3"));

        horizontalLayout_4->addWidget(ComComDisp3);

        ComComDisp4 = new QComboBox(horizontalLayoutWidget_7);
        ComComDisp4->setObjectName(QString::fromUtf8("ComComDisp4"));

        horizontalLayout_4->addWidget(ComComDisp4);

        BtnRefurbishComDisp = new QPushButton(groupBoxComDisp);
        BtnRefurbishComDisp->setObjectName(QString::fromUtf8("BtnRefurbishComDisp"));
        BtnRefurbishComDisp->setGeometry(QRect(76, 51, 151, 23));
        scrollAreaDisplay->setWidget(scrollAreaWidgetContents_6);

        verticalLayout_12->addWidget(scrollAreaDisplay);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/notebook/resource/notebook/0-07.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(Display, icon6, QString::fromUtf8("Display"));

        verticalLayout->addWidget(toolBox);

        QWidget::setTabOrder(ValueGain, ValueStart);
        QWidget::setTabOrder(ValueStart, ValueRange);
        QWidget::setTabOrder(ValueRange, ValueVelocity);
        QWidget::setTabOrder(ValueVelocity, ComVelocitySelection);
        QWidget::setTabOrder(ComVelocitySelection, ValueWedgeDelay);
        QWidget::setTabOrder(ValueWedgeDelay, ValuePulser);
        QWidget::setTabOrder(ValuePulser, ValueReceiver);
        QWidget::setTabOrder(ValueReceiver, ComFilter);
        QWidget::setTabOrder(ComFilter, ComRectifier);
        QWidget::setTabOrder(ComRectifier, CheckVideoFilter);
        QWidget::setTabOrder(CheckVideoFilter, ValuePointQty);
        QWidget::setTabOrder(ValuePointQty, ValueSumGain);
        QWidget::setTabOrder(ValueSumGain, scrollAreaUtSetting);
        QWidget::setTabOrder(scrollAreaUtSetting, ComGroupMode);
        QWidget::setTabOrder(ComGroupMode, BtnProbeSelection);
        QWidget::setTabOrder(BtnProbeSelection, BtnWedgeSelection);
        QWidget::setTabOrder(BtnWedgeSelection, scrollAreaProbeWedge);

        retranslateUi(DopplerGroupTab);

        toolBox->setCurrentIndex(5);
        toolBox->layout()->setSpacing(3);


        QMetaObject::connectSlotsByName(DopplerGroupTab);
    } // setupUi

    void retranslateUi(QWidget *DopplerGroupTab)
    {
        DopplerGroupTab->setWindowTitle(QApplication::translate("DopplerGroupTab", "Form", 0, QApplication::UnicodeUTF8));
        BoxGeneral->setTitle(QApplication::translate("DopplerGroupTab", "General", 0, QApplication::UnicodeUTF8));
        LabelTravelMode->setText(QApplication::translate("DopplerGroupTab", "Travel Mode:", 0, QApplication::UnicodeUTF8));
        ComTravelMode->clear();
        ComTravelMode->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "True Depth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Half Path", 0, QApplication::UnicodeUTF8)
        );
        LabelCurrentAngle->setText(QApplication::translate("DopplerGroupTab", "Current Angle:", 0, QApplication::UnicodeUTF8));
        ComCurrentAngle->clear();
        ComCurrentAngle->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "21", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "22", 0, QApplication::UnicodeUTF8)
        );
        LabelRangeUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelStart->setText(QApplication::translate("DopplerGroupTab", "Start:", 0, QApplication::UnicodeUTF8));
        LabelGain->setText(QApplication::translate("DopplerGroupTab", "Gain:", 0, QApplication::UnicodeUTF8));
        LabelGainUnit->setText(QApplication::translate("DopplerGroupTab", "db", 0, QApplication::UnicodeUTF8));
        LabelStartUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelRange->setText(QApplication::translate("DopplerGroupTab", "Range:", 0, QApplication::UnicodeUTF8));
        LabelVelocity->setText(QApplication::translate("DopplerGroupTab", "Velocity:", 0, QApplication::UnicodeUTF8));
        LabelVelocityUnit->setText(QApplication::translate("DopplerGroupTab", "m/s", 0, QApplication::UnicodeUTF8));
        ComVelocitySelection->clear();
        ComVelocitySelection->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Material", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Longtitude 5920", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Transverse 3230", 0, QApplication::UnicodeUTF8)
        );
        LabelWedgeDelay->setText(QApplication::translate("DopplerGroupTab", "WedgeDelay:", 0, QApplication::UnicodeUTF8));
        LabelWedgeDelayUnit->setText(QApplication::translate("DopplerGroupTab", "us", 0, QApplication::UnicodeUTF8));
        LabelGainUnit_2->setText(QApplication::translate("DopplerGroupTab", "db", 0, QApplication::UnicodeUTF8));
        BoxPulserReceiver->setTitle(QApplication::translate("DopplerGroupTab", "Pulser/Receiver", 0, QApplication::UnicodeUTF8));
        LabelPulser->setText(QApplication::translate("DopplerGroupTab", "Pulser:", 0, QApplication::UnicodeUTF8));
        LabelReceiver->setText(QApplication::translate("DopplerGroupTab", "Receiver:", 0, QApplication::UnicodeUTF8));
        CheckVideoFilter->setText(QApplication::translate("DopplerGroupTab", "on/off", 0, QApplication::UnicodeUTF8));
        LabelViedoFilter->setText(QApplication::translate("DopplerGroupTab", "Video Filter:", 0, QApplication::UnicodeUTF8));
        LabelFilter->setText(QApplication::translate("DopplerGroupTab", "Filter:", 0, QApplication::UnicodeUTF8));
        ComFilter->clear();
        ComFilter->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "None 0.5-20 MHz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Auto", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "1 MHz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "1.5 - 2.5 MHz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "3 - 5 MHz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "7.5 MHz", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", ">= 10 MHz", 0, QApplication::UnicodeUTF8)
        );
        LabelTxRxMode->setText(QApplication::translate("DopplerGroupTab", "TX RX mode:", 0, QApplication::UnicodeUTF8));
        ComTxRxMode->clear();
        ComTxRxMode->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Pitch Catch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Pitch Echo", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Through Trans", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "TOFD", 0, QApplication::UnicodeUTF8)
        );
        LabelRectifier->setText(QApplication::translate("DopplerGroupTab", "Rectifier:", 0, QApplication::UnicodeUTF8));
        ComRectifier->clear();
        ComRectifier->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "RF", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "HW+", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "HW-", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "FW", 0, QApplication::UnicodeUTF8)
        );
        LabelPointQty->setText(QApplication::translate("DopplerGroupTab", "Point Qty:", 0, QApplication::UnicodeUTF8));
        LabelSumGain->setText(QApplication::translate("DopplerGroupTab", "Sum Gain:", 0, QApplication::UnicodeUTF8));
        LabelSumGainUnit->setText(QApplication::translate("DopplerGroupTab", "db", 0, QApplication::UnicodeUTF8));
        LabelAverage->setText(QApplication::translate("DopplerGroupTab", "Average:", 0, QApplication::UnicodeUTF8));
        ComAverage->clear();
        ComAverage->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "16", 0, QApplication::UnicodeUTF8)
        );
        CheckSumGainAuto->setText(QApplication::translate("DopplerGroupTab", "Auto", 0, QApplication::UnicodeUTF8));
        CheckPointQtyAuto->setText(QApplication::translate("DopplerGroupTab", "Auto", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(PageUtSetting), QApplication::translate("DopplerGroupTab", "Ut Setting", 0, QApplication::UnicodeUTF8));
        BoxWedgeTrigger->setTitle(QApplication::translate("DopplerGroupTab", "Tx Wedge", 0, QApplication::UnicodeUTF8));
        BtnWedgeSelection->setText(QApplication::translate("DopplerGroupTab", "PushButton", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line1->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line3->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line4->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        ComGroupMode->clear();
        ComGroupMode->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "PA-UT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "PA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "UT-1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "UT-2", 0, QApplication::UnicodeUTF8)
        );
        BoxProbeTrigger->setTitle(QApplication::translate("DopplerGroupTab", "Tx Probe", 0, QApplication::UnicodeUTF8));
        BtnProbeSelection->setText(QApplication::translate("DopplerGroupTab", "PushButton", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line1->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line3->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line4->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelGroupMode->setText(QApplication::translate("DopplerGroupTab", "Group Mode:", 0, QApplication::UnicodeUTF8));
        BoxWedgeTrigger_2->setTitle(QApplication::translate("DopplerGroupTab", "Rx Probe", 0, QApplication::UnicodeUTF8));
        BtnWedgeSelection_2->setText(QApplication::translate("DopplerGroupTab", "PushButton", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line1_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line2_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line3_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelWedgeT_Line4_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        BoxProbeTrigger_2->setTitle(QApplication::translate("DopplerGroupTab", "Rx Probe", 0, QApplication::UnicodeUTF8));
        BtnProbeSelection_2->setText(QApplication::translate("DopplerGroupTab", "PushButton", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line1_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line2_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line3_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        LabelProbeT_Line4_2->setText(QApplication::translate("DopplerGroupTab", "TextLabel", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(ProbWedge), QApplication::translate("DopplerGroupTab", "Probe/Wedge", 0, QApplication::UnicodeUTF8));
        BoxFocalPoint->setTitle(QApplication::translate("DopplerGroupTab", "Focal Point", 0, QApplication::UnicodeUTF8));
        LabelFocalType->setText(QApplication::translate("DopplerGroupTab", "Focal Type:", 0, QApplication::UnicodeUTF8));
        ComFocalType->clear();
        ComFocalType->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Half Path", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "True Depth", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Projection", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Focal Plane", 0, QApplication::UnicodeUTF8)
        );
        LabelFocalStart->setText(QApplication::translate("DopplerGroupTab", "   Start", 0, QApplication::UnicodeUTF8));
        LabelFocalStop->setText(QApplication::translate("DopplerGroupTab", "   Stop", 0, QApplication::UnicodeUTF8));
        LabelFocalStep->setText(QApplication::translate("DopplerGroupTab", "   Step", 0, QApplication::UnicodeUTF8));
        LabelFocalPosition->setText(QApplication::translate("DopplerGroupTab", "Position:", 0, QApplication::UnicodeUTF8));
        LabelFocusStartUnit_2->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelFocalOffset->setText(QApplication::translate("DopplerGroupTab", "Offset:", 0, QApplication::UnicodeUTF8));
        LabelFocusOffsetStartUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelFocalDepth->setText(QApplication::translate("DopplerGroupTab", "Depth:", 0, QApplication::UnicodeUTF8));
        LabelFocusOffsetStopUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        BoxAperture->setTitle(QApplication::translate("DopplerGroupTab", "Aperture", 0, QApplication::UnicodeUTF8));
        LabelElementStart->setText(QApplication::translate("DopplerGroupTab", "Start Element:", 0, QApplication::UnicodeUTF8));
        LabelElementSelect->setText(QApplication::translate("DopplerGroupTab", "Element Selected:", 0, QApplication::UnicodeUTF8));
        LlabelPriAxis->setText(QApplication::translate("DopplerGroupTab", " Pri Axis", 0, QApplication::UnicodeUTF8));
        LlabelSecAxis->setText(QApplication::translate("DopplerGroupTab", " Sec Axis", 0, QApplication::UnicodeUTF8));
        LabelElementStop->setText(QApplication::translate("DopplerGroupTab", "Stop Element:", 0, QApplication::UnicodeUTF8));
        LabelElementStep->setText(QApplication::translate("DopplerGroupTab", "Step Element:", 0, QApplication::UnicodeUTF8));
        BoxAngle->setTitle(QApplication::translate("DopplerGroupTab", "Angle", 0, QApplication::UnicodeUTF8));
        LabelAngStart->setText(QApplication::translate("DopplerGroupTab", "  Start", 0, QApplication::UnicodeUTF8));
        LabelAngStop->setText(QApplication::translate("DopplerGroupTab", "  Stop", 0, QApplication::UnicodeUTF8));
        LabelAngStep->setText(QApplication::translate("DopplerGroupTab", "  Step", 0, QApplication::UnicodeUTF8));
        LabelPriSteering->setText(QApplication::translate("DopplerGroupTab", "Pri Steering:", 0, QApplication::UnicodeUTF8));
        LabelFocusStartUnit_4->setText(QApplication::translate("DopplerGroupTab", "deg", 0, QApplication::UnicodeUTF8));
        LabelSecSteering->setText(QApplication::translate("DopplerGroupTab", "Sec Steering:", 0, QApplication::UnicodeUTF8));
        LabelFocusOffsetStartUnit_3->setText(QApplication::translate("DopplerGroupTab", "deg", 0, QApplication::UnicodeUTF8));
        LlabelRefract->setText(QApplication::translate("DopplerGroupTab", "Refract:", 0, QApplication::UnicodeUTF8));
        LabelFocusOffsetStopUnit_3->setText(QApplication::translate("DopplerGroupTab", "deg", 0, QApplication::UnicodeUTF8));
        LlabelBeamSkew->setText(QApplication::translate("DopplerGroupTab", "Beam Skew:", 0, QApplication::UnicodeUTF8));
        LabelFocusOffsetStopUnit_4->setText(QApplication::translate("DopplerGroupTab", "deg", 0, QApplication::UnicodeUTF8));
        LabelAngleType->setText(QApplication::translate("DopplerGroupTab", "Angle Type:", 0, QApplication::UnicodeUTF8));
        ComAngleType->clear();
        ComAngleType->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Refracted Angle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Primary Steering Angle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Beam Skew Angle", 0, QApplication::UnicodeUTF8)
        );
        LabelLawType->setText(QApplication::translate("DopplerGroupTab", "Law Type:", 0, QApplication::UnicodeUTF8));
        ComLawType->clear();
        ComLawType->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Azimuthal Sector", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Linear Sector", 0, QApplication::UnicodeUTF8)
        );
        BtnProcessLaw->setText(QApplication::translate("DopplerGroupTab", "Process", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(FocalLaw), QApplication::translate("DopplerGroupTab", "Focallaw", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        GateSizingcurves->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        LabelGate->setText(QApplication::translate("DopplerGroupTab", "Gate", 0, QApplication::UnicodeUTF8));
        CheckGateShow->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        LabelGateSelect->setText(QApplication::translate("DopplerGroupTab", "Select:", 0, QApplication::UnicodeUTF8));
        ComGateSelect->clear();
        ComGateSelect->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Gate A", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate I", 0, QApplication::UnicodeUTF8)
        );
        LabelGateStart->setText(QApplication::translate("DopplerGroupTab", "Start\357\274\232", 0, QApplication::UnicodeUTF8));
        LabelGateStartUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelGateWidth->setText(QApplication::translate("DopplerGroupTab", "Width:", 0, QApplication::UnicodeUTF8));
        LabelGateWidthUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelGateHeight->setText(QApplication::translate("DopplerGroupTab", "Height:", 0, QApplication::UnicodeUTF8));
        LabelGateSync->setText(QApplication::translate("DopplerGroupTab", "Synchro.:", 0, QApplication::UnicodeUTF8));
        ComGateSync->clear();
        ComGateSync->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Pulse", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "I/", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "A/", 0, QApplication::UnicodeUTF8)
        );
        LabelGateMeasure->setText(QApplication::translate("DopplerGroupTab", "Measure:", 0, QApplication::UnicodeUTF8));
        ComGateMeasure->clear();
        ComGateMeasure->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Peak ^", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Edge /", 0, QApplication::UnicodeUTF8)
        );
        LabelSizingCurves->setText(QApplication::translate("DopplerGroupTab", "Sizing  Curves", 0, QApplication::UnicodeUTF8));
        LabelCurveSel->setText(QApplication::translate("DopplerGroupTab", "Select:", 0, QApplication::UnicodeUTF8));
        ComSizingCurve->clear();
        ComSizingCurve->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "None", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "DAC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Linear DAC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "TCG", 0, QApplication::UnicodeUTF8)
        );
        DacPointPos->setText(QApplication::translate("DopplerGroupTab", "Point No.:", 0, QApplication::UnicodeUTF8));
        ComCurvePointId->clear();
        ComCurvePointId->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "5", 0, QApplication::UnicodeUTF8)
        );
        BtnAddPoint->setText(QApplication::translate("DopplerGroupTab", "ADD", 0, QApplication::UnicodeUTF8));
        BtnDelPoint->setText(QApplication::translate("DopplerGroupTab", "DEL", 0, QApplication::UnicodeUTF8));
        LabelSizingCure1->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit1->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCure2->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit2->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCure4->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure5->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure6->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit3->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit4->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit5->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit6->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCure3->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure7->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure8->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure9->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure10->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure11->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure12->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure13->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure14->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure15->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCure16->setText(QApplication::translate("DopplerGroupTab", "Ref Amplitude:", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit7->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit8->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit9->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit10->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit11->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit12->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit13->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit14->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit15->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        LabelSizingCureUnit16->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(GateSizingcurves), QApplication::translate("DopplerGroupTab", "Gate and Sizing Curves", 0, QApplication::UnicodeUTF8));
        LabelPartFile->setText(QApplication::translate("DopplerGroupTab", "Weld & Part File", 0, QApplication::UnicodeUTF8));
        LabelPartFileLoad->setText(QApplication::translate("DopplerGroupTab", "Load:", 0, QApplication::UnicodeUTF8));
        BtnLoadPartFile->setText(QApplication::translate("DopplerGroupTab", "Weld", 0, QApplication::UnicodeUTF8));
        CheckPartFileShow->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        BoxPart->setTitle(QApplication::translate("DopplerGroupTab", "Part", 0, QApplication::UnicodeUTF8));
        LabelGeometry->setText(QApplication::translate("DopplerGroupTab", "Geometry:", 0, QApplication::UnicodeUTF8));
        ComGeometry->clear();
        ComGeometry->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "PLATE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "OD", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "ID", 0, QApplication::UnicodeUTF8)
        );
        CheckUnifiedPartSetting->setText(QApplication::translate("DopplerGroupTab", "Unified Part setting", 0, QApplication::UnicodeUTF8));
        LabelPartSize1->setText(QApplication::translate("DopplerGroupTab", "Thickness: ", 0, QApplication::UnicodeUTF8));
        LabelPartSizeUnit1->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelPartSize2->setText(QApplication::translate("DopplerGroupTab", "Length:", 0, QApplication::UnicodeUTF8));
        LabelPartSizeUnit2->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelPartSize3->setText(QApplication::translate("DopplerGroupTab", "Width:", 0, QApplication::UnicodeUTF8));
        LabelPartSizeUnit3->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelMaterial->setText(QApplication::translate("DopplerGroupTab", "Material:", 0, QApplication::UnicodeUTF8));
        ComMaterial->clear();
        ComMaterial->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Steel 5920 3230", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Alumi 6000 3300", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "ID", 0, QApplication::UnicodeUTF8)
        );
        CheckShowThickness->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        BoxPartTofd->setTitle(QApplication::translate("DopplerGroupTab", "TOFD", 0, QApplication::UnicodeUTF8));
        LabelTofdScanMode->setText(QApplication::translate("DopplerGroupTab", "Scan Mode:", 0, QApplication::UnicodeUTF8));
        ComBoxScanMode->clear();
        ComBoxScanMode->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Parallel", 0, QApplication::UnicodeUTF8)
        );
        LabelTofdProMode->setText(QApplication::translate("DopplerGroupTab", "Process Mode:", 0, QApplication::UnicodeUTF8));
        ComBoxProMode->clear();
        ComBoxProMode->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Whole", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Aera", 0, QApplication::UnicodeUTF8)
        );
        LabelTofdWedgeSep->setText(QApplication::translate("DopplerGroupTab", "Wedge Seperation:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_8->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelTofdPcs->setText(QApplication::translate("DopplerGroupTab", "PCS:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_9->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelZeroOff->setText(QApplication::translate("DopplerGroupTab", "Wedge delay correction:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_6->setText(QApplication::translate("DopplerGroupTab", "us", 0, QApplication::UnicodeUTF8));
        LabelDepthStart->setText(QApplication::translate("DopplerGroupTab", "Depth start:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_5->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelDepthEnd->setText(QApplication::translate("DopplerGroupTab", "Depth end:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_7->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelTofdPcsCal->setText(QApplication::translate("DopplerGroupTab", "PCS:", 0, QApplication::UnicodeUTF8));
        LabelCalPCSUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelShowLwBw->setText(QApplication::translate("DopplerGroupTab", "LW / BW", 0, QApplication::UnicodeUTF8));
        CheckLwBwShow->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        BoxDepthCal->setTitle(QApplication::translate("DopplerGroupTab", "Depth Calibration", 0, QApplication::UnicodeUTF8));
        LabelDepthCal->setText(QApplication::translate("DopplerGroupTab", "Depth:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_19->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        BtnDepthCal->setText(QApplication::translate("DopplerGroupTab", "Calibration", 0, QApplication::UnicodeUTF8));
        BoxPartPosition->setTitle(QApplication::translate("DopplerGroupTab", "Position", 0, QApplication::UnicodeUTF8));
        LabelScanOffset->setText(QApplication::translate("DopplerGroupTab", "Scan Offset:  ", 0, QApplication::UnicodeUTF8));
        LabelScanOffsetUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelIndexOffset->setText(QApplication::translate("DopplerGroupTab", "Index Offset: ", 0, QApplication::UnicodeUTF8));
        LabelIndexOffsetUnit->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelSkewAngle->setText(QApplication::translate("DopplerGroupTab", "Skew Angle:", 0, QApplication::UnicodeUTF8));
        ComSkewAngle->clear();
        ComSkewAngle->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "  0degree", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", " 90degree", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "180degree", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "270degree", 0, QApplication::UnicodeUTF8)
        );
        toolBox->setItemText(toolBox->indexOf(Geometry), QApplication::translate("DopplerGroupTab", "Geometry", 0, QApplication::UnicodeUTF8));
        LabelMeasureValue->setText(QApplication::translate("DopplerGroupTab", "Measure Value", 0, QApplication::UnicodeUTF8));
        LabelCursor->setText(QApplication::translate("DopplerGroupTab", "Cursor", 0, QApplication::UnicodeUTF8));
        CheckMeasureShow->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        CheckCursorShow->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        LabelField1->setText(QApplication::translate("DopplerGroupTab", "Field 1 :", 0, QApplication::UnicodeUTF8));
        ComField1->clear();
        ComField1->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 9", 0, QApplication::UnicodeUTF8)
        );
        LabelField2->setText(QApplication::translate("DopplerGroupTab", "Field 2 :", 0, QApplication::UnicodeUTF8));
        ComField2->clear();
        ComField2->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 9", 0, QApplication::UnicodeUTF8)
        );
        LabelField3->setText(QApplication::translate("DopplerGroupTab", "Field 3 :", 0, QApplication::UnicodeUTF8));
        ComField3->clear();
        ComField3->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 9", 0, QApplication::UnicodeUTF8)
        );
        LabelField4->setText(QApplication::translate("DopplerGroupTab", "Field 4 :", 0, QApplication::UnicodeUTF8));
        ComField4->clear();
        ComField4->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 9", 0, QApplication::UnicodeUTF8)
        );
        LabelField5->setText(QApplication::translate("DopplerGroupTab", "Field 5 :", 0, QApplication::UnicodeUTF8));
        ComField5->clear();
        ComField5->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 9", 0, QApplication::UnicodeUTF8)
        );
        LabelCursorUnit1->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        label_199->setText(QApplication::translate("DopplerGroupTab", "%(m):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit2->setText(QApplication::translate("DopplerGroupTab", "%", 0, QApplication::UnicodeUTF8));
        label_201->setText(QApplication::translate("DopplerGroupTab", "U(r):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        label_203->setText(QApplication::translate("DopplerGroupTab", "U(m):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit4->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        label_205->setText(QApplication::translate("DopplerGroupTab", "S(r):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit5->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        label_207->setText(QApplication::translate("DopplerGroupTab", "S(m):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit6->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        label_209->setText(QApplication::translate("DopplerGroupTab", "I(r):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit7->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        label_211->setText(QApplication::translate("DopplerGroupTab", "I(m):", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit8->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        label_197->setText(QApplication::translate("DopplerGroupTab", "%(r):", 0, QApplication::UnicodeUTF8));
        LabelDefect->setText(QApplication::translate("DopplerGroupTab", "Defect", 0, QApplication::UnicodeUTF8));
        CheckDefectShow->setText(QApplication::translate("DopplerGroupTab", "Show", 0, QApplication::UnicodeUTF8));
        ComDefectIndex->clear();
        ComDefectIndex->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "NONE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Value 9", 0, QApplication::UnicodeUTF8)
        );
        LabelDefectIndex->setText(QApplication::translate("DopplerGroupTab", "Index :", 0, QApplication::UnicodeUTF8));
        labelDefectStart->setText(QApplication::translate("DopplerGroupTab", "Position:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_2->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        labelDefectLength->setText(QApplication::translate("DopplerGroupTab", "Length:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_3->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        labelDefectDepth->setText(QApplication::translate("DopplerGroupTab", "Depth:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_4->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        labelDefectHeight->setText(QApplication::translate("DopplerGroupTab", "Height:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_10->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_11->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        labelDefectOffset->setText(QApplication::translate("DopplerGroupTab", "Offset:", 0, QApplication::UnicodeUTF8));
        labelDefectWidth->setText(QApplication::translate("DopplerGroupTab", "Width:", 0, QApplication::UnicodeUTF8));
        LabelCursorUnit3_12->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        BtnDefectDelete->setText(QApplication::translate("DopplerGroupTab", "Delete", 0, QApplication::UnicodeUTF8));
        LabelReMark->setText(QApplication::translate("DopplerGroupTab", "Remark:", 0, QApplication::UnicodeUTF8));
        CheckBackShow->setText(QApplication::translate("DopplerGroupTab", "Background", 0, QApplication::UnicodeUTF8));
        CheckCursorSync->setText(QApplication::translate("DopplerGroupTab", "Background", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(Measurement), QApplication::translate("DopplerGroupTab", "Measurement", 0, QApplication::UnicodeUTF8));
        LabelLanguage->setText(QApplication::translate("DopplerGroupTab", "Language:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DopplerGroupTab", "ColorSetting", 0, QApplication::UnicodeUTF8));
        LabelCScanSource1->setText(QApplication::translate("DopplerGroupTab", "C Scan 1 Source:", 0, QApplication::UnicodeUTF8));
        ComCScanSource1->clear();
        ComCScanSource1->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Gate A  Amplitude", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B  Amplitude", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate  I  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate A  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate A-I  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B-I  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B-A  Position", 0, QApplication::UnicodeUTF8)
        );
        LabelCScanSource2->setText(QApplication::translate("DopplerGroupTab", "C Scan 2 Source:", 0, QApplication::UnicodeUTF8));
        ComCScanSource2->clear();
        ComCScanSource2->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Gate A  Amplitude", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B  Amplitude", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate  I  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate A  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate A-I  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B-I  Position", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Gate B-A  Position", 0, QApplication::UnicodeUTF8)
        );
        LabelCScanThickness->setText(QApplication::translate("DopplerGroupTab", "C Scan Thickness", 0, QApplication::UnicodeUTF8));
        LabelCScanThicknessMin->setText(QApplication::translate("DopplerGroupTab", "Min:", 0, QApplication::UnicodeUTF8));
        LabelCScanThicknessMax_3->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        LabelCScanThicknessMax->setText(QApplication::translate("DopplerGroupTab", "Max:", 0, QApplication::UnicodeUTF8));
        LabelCScanThicknessMax_2->setText(QApplication::translate("DopplerGroupTab", "mm", 0, QApplication::UnicodeUTF8));
        ComColorLineSelection->clear();
        ComColorLineSelection->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "A SCAN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "A SCAN MAX", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "A SCAN MIN", 0, QApplication::UnicodeUTF8)
        );
        ComColorLineColor->clear();
        ComColorLineColor->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "White", 0, QApplication::UnicodeUTF8)
        );
        LabelAmpColor->setText(QApplication::translate("DopplerGroupTab", "Amplitude:", 0, QApplication::UnicodeUTF8));
        BtnColorAmp->setText(QString());
        LabelColorRF->setText(QApplication::translate("DopplerGroupTab", "RF:", 0, QApplication::UnicodeUTF8));
        BtnColorRf->setText(QString());
        label_5->setText(QApplication::translate("DopplerGroupTab", "Thickness:", 0, QApplication::UnicodeUTF8));
        BtnColorThickness->setText(QString());
        groupBoxComDisp->setTitle(QApplication::translate("DopplerGroupTab", "Combination Display", 0, QApplication::UnicodeUTF8));
        ComComDisp1->clear();
        ComComDisp1->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Group1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group8", 0, QApplication::UnicodeUTF8)
        );
        ComComDisp2->clear();
        ComComDisp2->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Group1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group8", 0, QApplication::UnicodeUTF8)
        );
        ComComDisp3->clear();
        ComComDisp3->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Group1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group8", 0, QApplication::UnicodeUTF8)
        );
        ComComDisp4->clear();
        ComComDisp4->insertItems(0, QStringList()
         << QApplication::translate("DopplerGroupTab", "Group1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DopplerGroupTab", "Group8", 0, QApplication::UnicodeUTF8)
        );
        BtnRefurbishComDisp->setText(QApplication::translate("DopplerGroupTab", "Refurbish", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(Display), QApplication::translate("DopplerGroupTab", "Display", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DopplerGroupTab: public Ui_DopplerGroupTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOPPLERGROUPTAB_H
