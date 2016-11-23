/********************************************************************************
** Form generated from reading UI file 'InstrumentSettingWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTRUMENTSETTINGWIDGET_H
#define UI_INSTRUMENTSETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InstrumentSettingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *LabelPaValtage;
    QLabel *LabelUtVolatage;
    QWidget *layoutWidget_5;
    QGridLayout *gridLayout_10;
    QLabel *LabelScanType;
    QComboBox *ComScanType;
    QLabel *LabelEncoderType;
    QComboBox *ComEncoderType;
    QLabel *LabelPrf;
    QDoubleSpinBox *ValuePrf;
    QGroupBox *BoxScanArea;
    QLabel *LabelPaValtage_2;
    QLabel *LabelPaValtage_3;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *LabelScanStart;
    QDoubleSpinBox *ValueScanStart;
    QDoubleSpinBox *ValueIndexStart;
    QLabel *LabelScanStartUnit;
    QLabel *LabelScanEnd;
    QDoubleSpinBox *ValueScanEnd;
    QDoubleSpinBox *ValueIndexStop;
    QLabel *LabelScanEndUnit;
    QLabel *LabelScanResolution;
    QDoubleSpinBox *ValueScanResolution;
    QDoubleSpinBox *ValueIndexResolution;
    QLabel *LabelScanResolutionUnit;
    QGroupBox *BoxEncoderMode;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *LabelEncoderType_2;
    QComboBox *ComEncoderTypeSetting;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *LabelResolution;
    QDoubleSpinBox *ValueEncoderResolution;
    QLabel *LabelEncoderResolutionUnit;
    QWidget *layoutWidget_3;
    QGridLayout *gridLayout_12;
    QLabel *LabelEncoderPolarity;
    QComboBox *ComEncoderPolarity;
    QLabel *LabelEncoderDirection;
    QComboBox *ComEncoderDirection;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *LabelEncoderOrg;
    QDoubleSpinBox *ValueEncoderOrg;
    QLabel *LabeEncoderOrgUnit;
    QComboBox *ComVoltageUt;
    QComboBox *ComVoltagePa;
    QLabel *LabelScanPos;
    QSlider *SliderCurrentScanPos;
    QDoubleSpinBox *SpinBoxCurrentScanPos;
    QLabel *LabelIndexPos;
    QDoubleSpinBox *SpinBoxCurrentIndexPos;
    QSlider *SliderCurrentIndexPos;
    QLabel *LabelScanPosUnit;
    QLabel *LabelIndexPosUnit;

    void setupUi(QWidget *InstrumentSettingWidget)
    {
        if (InstrumentSettingWidget->objectName().isEmpty())
            InstrumentSettingWidget->setObjectName(QString::fromUtf8("InstrumentSettingWidget"));
        InstrumentSettingWidget->resize(308, 688);
        verticalLayout = new QVBoxLayout(InstrumentSettingWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(InstrumentSettingWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 287, 686));
        LabelPaValtage = new QLabel(scrollAreaWidgetContents);
        LabelPaValtage->setObjectName(QString::fromUtf8("LabelPaValtage"));
        LabelPaValtage->setGeometry(QRect(30, 440, 75, 25));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LabelPaValtage->sizePolicy().hasHeightForWidth());
        LabelPaValtage->setSizePolicy(sizePolicy);
        LabelPaValtage->setMinimumSize(QSize(75, 25));
        LabelUtVolatage = new QLabel(scrollAreaWidgetContents);
        LabelUtVolatage->setObjectName(QString::fromUtf8("LabelUtVolatage"));
        LabelUtVolatage->setGeometry(QRect(30, 470, 75, 25));
        sizePolicy.setHeightForWidth(LabelUtVolatage->sizePolicy().hasHeightForWidth());
        LabelUtVolatage->setSizePolicy(sizePolicy);
        LabelUtVolatage->setMinimumSize(QSize(75, 25));
        layoutWidget_5 = new QWidget(scrollAreaWidgetContents);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 20, 207, 93));
        gridLayout_10 = new QGridLayout(layoutWidget_5);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        LabelScanType = new QLabel(layoutWidget_5);
        LabelScanType->setObjectName(QString::fromUtf8("LabelScanType"));
        sizePolicy.setHeightForWidth(LabelScanType->sizePolicy().hasHeightForWidth());
        LabelScanType->setSizePolicy(sizePolicy);
        LabelScanType->setMinimumSize(QSize(75, 25));

        gridLayout_10->addWidget(LabelScanType, 0, 0, 1, 1);

        ComScanType = new QComboBox(layoutWidget_5);
        ComScanType->setObjectName(QString::fromUtf8("ComScanType"));

        gridLayout_10->addWidget(ComScanType, 0, 1, 1, 2);

        LabelEncoderType = new QLabel(layoutWidget_5);
        LabelEncoderType->setObjectName(QString::fromUtf8("LabelEncoderType"));
        sizePolicy.setHeightForWidth(LabelEncoderType->sizePolicy().hasHeightForWidth());
        LabelEncoderType->setSizePolicy(sizePolicy);
        LabelEncoderType->setMinimumSize(QSize(75, 25));

        gridLayout_10->addWidget(LabelEncoderType, 1, 0, 1, 2);

        ComEncoderType = new QComboBox(layoutWidget_5);
        ComEncoderType->setObjectName(QString::fromUtf8("ComEncoderType"));

        gridLayout_10->addWidget(ComEncoderType, 1, 2, 1, 1);

        LabelPrf = new QLabel(layoutWidget_5);
        LabelPrf->setObjectName(QString::fromUtf8("LabelPrf"));
        sizePolicy.setHeightForWidth(LabelPrf->sizePolicy().hasHeightForWidth());
        LabelPrf->setSizePolicy(sizePolicy);
        LabelPrf->setMinimumSize(QSize(70, 25));
        LabelPrf->setMaximumSize(QSize(70, 20));

        gridLayout_10->addWidget(LabelPrf, 2, 0, 1, 1);

        ValuePrf = new QDoubleSpinBox(layoutWidget_5);
        ValuePrf->setObjectName(QString::fromUtf8("ValuePrf"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ValuePrf->sizePolicy().hasHeightForWidth());
        ValuePrf->setSizePolicy(sizePolicy1);
        ValuePrf->setMinimumSize(QSize(50, 20));
        ValuePrf->setMaximumSize(QSize(16777215, 20));
        ValuePrf->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValuePrf->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePrf->setDecimals(1);
        ValuePrf->setMinimum(1);
        ValuePrf->setMaximum(6000);

        gridLayout_10->addWidget(ValuePrf, 2, 2, 1, 1);

        BoxScanArea = new QGroupBox(scrollAreaWidgetContents);
        BoxScanArea->setObjectName(QString::fromUtf8("BoxScanArea"));
        BoxScanArea->setGeometry(QRect(20, 110, 261, 131));
        LabelPaValtage_2 = new QLabel(BoxScanArea);
        LabelPaValtage_2->setObjectName(QString::fromUtf8("LabelPaValtage_2"));
        LabelPaValtage_2->setGeometry(QRect(94, 9, 61, 20));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(111);
        sizePolicy2.setVerticalStretch(25);
        sizePolicy2.setHeightForWidth(LabelPaValtage_2->sizePolicy().hasHeightForWidth());
        LabelPaValtage_2->setSizePolicy(sizePolicy2);
        LabelPaValtage_2->setMinimumSize(QSize(0, 0));
        LabelPaValtage_3 = new QLabel(BoxScanArea);
        LabelPaValtage_3->setObjectName(QString::fromUtf8("LabelPaValtage_3"));
        LabelPaValtage_3->setGeometry(QRect(160, 9, 61, 20));
        sizePolicy2.setHeightForWidth(LabelPaValtage_3->sizePolicy().hasHeightForWidth());
        LabelPaValtage_3->setSizePolicy(sizePolicy2);
        LabelPaValtage_3->setMinimumSize(QSize(0, 0));
        layoutWidget2 = new QWidget(BoxScanArea);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 30, 241, 89));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        LabelScanStart = new QLabel(layoutWidget2);
        LabelScanStart->setObjectName(QString::fromUtf8("LabelScanStart"));
        sizePolicy.setHeightForWidth(LabelScanStart->sizePolicy().hasHeightForWidth());
        LabelScanStart->setSizePolicy(sizePolicy);
        LabelScanStart->setMinimumSize(QSize(75, 25));

        gridLayout->addWidget(LabelScanStart, 0, 0, 1, 1);

        ValueScanStart = new QDoubleSpinBox(layoutWidget2);
        ValueScanStart->setObjectName(QString::fromUtf8("ValueScanStart"));
        sizePolicy.setHeightForWidth(ValueScanStart->sizePolicy().hasHeightForWidth());
        ValueScanStart->setSizePolicy(sizePolicy);
        ValueScanStart->setMinimumSize(QSize(60, 20));
        ValueScanStart->setMaximumSize(QSize(60, 20));
        ValueScanStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueScanStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanStart->setDecimals(1);
        ValueScanStart->setMinimum(-10000);
        ValueScanStart->setMaximum(10000);

        gridLayout->addWidget(ValueScanStart, 0, 1, 1, 1);

        ValueIndexStart = new QDoubleSpinBox(layoutWidget2);
        ValueIndexStart->setObjectName(QString::fromUtf8("ValueIndexStart"));
        sizePolicy.setHeightForWidth(ValueIndexStart->sizePolicy().hasHeightForWidth());
        ValueIndexStart->setSizePolicy(sizePolicy);
        ValueIndexStart->setMinimumSize(QSize(60, 20));
        ValueIndexStart->setMaximumSize(QSize(60, 20));
        ValueIndexStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueIndexStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexStart->setDecimals(1);
        ValueIndexStart->setMinimum(-10000);
        ValueIndexStart->setMaximum(10000);

        gridLayout->addWidget(ValueIndexStart, 0, 2, 1, 1);

        LabelScanStartUnit = new QLabel(layoutWidget2);
        LabelScanStartUnit->setObjectName(QString::fromUtf8("LabelScanStartUnit"));

        gridLayout->addWidget(LabelScanStartUnit, 0, 3, 1, 1);

        LabelScanEnd = new QLabel(layoutWidget2);
        LabelScanEnd->setObjectName(QString::fromUtf8("LabelScanEnd"));
        sizePolicy.setHeightForWidth(LabelScanEnd->sizePolicy().hasHeightForWidth());
        LabelScanEnd->setSizePolicy(sizePolicy);
        LabelScanEnd->setMinimumSize(QSize(75, 25));

        gridLayout->addWidget(LabelScanEnd, 1, 0, 1, 1);

        ValueScanEnd = new QDoubleSpinBox(layoutWidget2);
        ValueScanEnd->setObjectName(QString::fromUtf8("ValueScanEnd"));
        sizePolicy.setHeightForWidth(ValueScanEnd->sizePolicy().hasHeightForWidth());
        ValueScanEnd->setSizePolicy(sizePolicy);
        ValueScanEnd->setMinimumSize(QSize(60, 20));
        ValueScanEnd->setMaximumSize(QSize(60, 20));
        ValueScanEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueScanEnd->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanEnd->setDecimals(1);
        ValueScanEnd->setMinimum(-10000);
        ValueScanEnd->setMaximum(10000);

        gridLayout->addWidget(ValueScanEnd, 1, 1, 1, 1);

        ValueIndexStop = new QDoubleSpinBox(layoutWidget2);
        ValueIndexStop->setObjectName(QString::fromUtf8("ValueIndexStop"));
        sizePolicy.setHeightForWidth(ValueIndexStop->sizePolicy().hasHeightForWidth());
        ValueIndexStop->setSizePolicy(sizePolicy);
        ValueIndexStop->setMinimumSize(QSize(60, 20));
        ValueIndexStop->setMaximumSize(QSize(60, 20));
        ValueIndexStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueIndexStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexStop->setDecimals(1);
        ValueIndexStop->setMinimum(-10000);
        ValueIndexStop->setMaximum(10000);

        gridLayout->addWidget(ValueIndexStop, 1, 2, 1, 1);

        LabelScanEndUnit = new QLabel(layoutWidget2);
        LabelScanEndUnit->setObjectName(QString::fromUtf8("LabelScanEndUnit"));

        gridLayout->addWidget(LabelScanEndUnit, 1, 3, 1, 1);

        LabelScanResolution = new QLabel(layoutWidget2);
        LabelScanResolution->setObjectName(QString::fromUtf8("LabelScanResolution"));
        sizePolicy.setHeightForWidth(LabelScanResolution->sizePolicy().hasHeightForWidth());
        LabelScanResolution->setSizePolicy(sizePolicy);
        LabelScanResolution->setMinimumSize(QSize(75, 25));

        gridLayout->addWidget(LabelScanResolution, 2, 0, 1, 1);

        ValueScanResolution = new QDoubleSpinBox(layoutWidget2);
        ValueScanResolution->setObjectName(QString::fromUtf8("ValueScanResolution"));
        sizePolicy.setHeightForWidth(ValueScanResolution->sizePolicy().hasHeightForWidth());
        ValueScanResolution->setSizePolicy(sizePolicy);
        ValueScanResolution->setMinimumSize(QSize(60, 20));
        ValueScanResolution->setMaximumSize(QSize(60, 20));
        ValueScanResolution->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueScanResolution->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanResolution->setDecimals(1);
        ValueScanResolution->setMinimum(-10000);
        ValueScanResolution->setMaximum(10000);

        gridLayout->addWidget(ValueScanResolution, 2, 1, 1, 1);

        ValueIndexResolution = new QDoubleSpinBox(layoutWidget2);
        ValueIndexResolution->setObjectName(QString::fromUtf8("ValueIndexResolution"));
        sizePolicy.setHeightForWidth(ValueIndexResolution->sizePolicy().hasHeightForWidth());
        ValueIndexResolution->setSizePolicy(sizePolicy);
        ValueIndexResolution->setMinimumSize(QSize(60, 20));
        ValueIndexResolution->setMaximumSize(QSize(60, 20));
        ValueIndexResolution->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueIndexResolution->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexResolution->setDecimals(1);
        ValueIndexResolution->setMinimum(-10000);
        ValueIndexResolution->setMaximum(10000);

        gridLayout->addWidget(ValueIndexResolution, 2, 2, 1, 1);

        LabelScanResolutionUnit = new QLabel(layoutWidget2);
        LabelScanResolutionUnit->setObjectName(QString::fromUtf8("LabelScanResolutionUnit"));

        gridLayout->addWidget(LabelScanResolutionUnit, 2, 3, 1, 1);

        BoxEncoderMode = new QGroupBox(scrollAreaWidgetContents);
        BoxEncoderMode->setObjectName(QString::fromUtf8("BoxEncoderMode"));
        BoxEncoderMode->setGeometry(QRect(20, 250, 261, 181));
        layoutWidget1 = new QWidget(BoxEncoderMode);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(24, 20, 221, 29));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        LabelEncoderType_2 = new QLabel(layoutWidget1);
        LabelEncoderType_2->setObjectName(QString::fromUtf8("LabelEncoderType_2"));
        sizePolicy.setHeightForWidth(LabelEncoderType_2->sizePolicy().hasHeightForWidth());
        LabelEncoderType_2->setSizePolicy(sizePolicy);
        LabelEncoderType_2->setMinimumSize(QSize(75, 25));

        horizontalLayout_5->addWidget(LabelEncoderType_2);

        ComEncoderTypeSetting = new QComboBox(layoutWidget1);
        ComEncoderTypeSetting->setObjectName(QString::fromUtf8("ComEncoderTypeSetting"));

        horizontalLayout_5->addWidget(ComEncoderTypeSetting);

        layoutWidget_2 = new QWidget(BoxEncoderMode);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(25, 48, 221, 27));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        LabelResolution = new QLabel(layoutWidget_2);
        LabelResolution->setObjectName(QString::fromUtf8("LabelResolution"));
        sizePolicy.setHeightForWidth(LabelResolution->sizePolicy().hasHeightForWidth());
        LabelResolution->setSizePolicy(sizePolicy);
        LabelResolution->setMinimumSize(QSize(75, 25));

        horizontalLayout_6->addWidget(LabelResolution);

        ValueEncoderResolution = new QDoubleSpinBox(layoutWidget_2);
        ValueEncoderResolution->setObjectName(QString::fromUtf8("ValueEncoderResolution"));
        sizePolicy.setHeightForWidth(ValueEncoderResolution->sizePolicy().hasHeightForWidth());
        ValueEncoderResolution->setSizePolicy(sizePolicy);
        ValueEncoderResolution->setMinimumSize(QSize(60, 20));
        ValueEncoderResolution->setMaximumSize(QSize(60, 20));
        ValueEncoderResolution->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueEncoderResolution->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueEncoderResolution->setDecimals(1);
        ValueEncoderResolution->setMinimum(1);
        ValueEncoderResolution->setMaximum(10000);

        horizontalLayout_6->addWidget(ValueEncoderResolution);

        LabelEncoderResolutionUnit = new QLabel(layoutWidget_2);
        LabelEncoderResolutionUnit->setObjectName(QString::fromUtf8("LabelEncoderResolutionUnit"));

        horizontalLayout_6->addWidget(LabelEncoderResolutionUnit);

        layoutWidget_3 = new QWidget(BoxEncoderMode);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(25, 78, 164, 62));
        gridLayout_12 = new QGridLayout(layoutWidget_3);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        LabelEncoderPolarity = new QLabel(layoutWidget_3);
        LabelEncoderPolarity->setObjectName(QString::fromUtf8("LabelEncoderPolarity"));
        sizePolicy.setHeightForWidth(LabelEncoderPolarity->sizePolicy().hasHeightForWidth());
        LabelEncoderPolarity->setSizePolicy(sizePolicy);
        LabelEncoderPolarity->setMinimumSize(QSize(75, 25));

        gridLayout_12->addWidget(LabelEncoderPolarity, 0, 0, 1, 1);

        ComEncoderPolarity = new QComboBox(layoutWidget_3);
        ComEncoderPolarity->setObjectName(QString::fromUtf8("ComEncoderPolarity"));

        gridLayout_12->addWidget(ComEncoderPolarity, 0, 1, 1, 1);

        LabelEncoderDirection = new QLabel(layoutWidget_3);
        LabelEncoderDirection->setObjectName(QString::fromUtf8("LabelEncoderDirection"));
        sizePolicy.setHeightForWidth(LabelEncoderDirection->sizePolicy().hasHeightForWidth());
        LabelEncoderDirection->setSizePolicy(sizePolicy);
        LabelEncoderDirection->setMinimumSize(QSize(75, 25));

        gridLayout_12->addWidget(LabelEncoderDirection, 1, 0, 1, 1);

        ComEncoderDirection = new QComboBox(layoutWidget_3);
        ComEncoderDirection->setObjectName(QString::fromUtf8("ComEncoderDirection"));

        gridLayout_12->addWidget(ComEncoderDirection, 1, 1, 1, 1);

        layoutWidget = new QWidget(BoxEncoderMode);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(25, 138, 201, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LabelEncoderOrg = new QLabel(layoutWidget);
        LabelEncoderOrg->setObjectName(QString::fromUtf8("LabelEncoderOrg"));
        sizePolicy.setHeightForWidth(LabelEncoderOrg->sizePolicy().hasHeightForWidth());
        LabelEncoderOrg->setSizePolicy(sizePolicy);
        LabelEncoderOrg->setMinimumSize(QSize(75, 25));

        horizontalLayout->addWidget(LabelEncoderOrg);

        ValueEncoderOrg = new QDoubleSpinBox(layoutWidget);
        ValueEncoderOrg->setObjectName(QString::fromUtf8("ValueEncoderOrg"));
        sizePolicy.setHeightForWidth(ValueEncoderOrg->sizePolicy().hasHeightForWidth());
        ValueEncoderOrg->setSizePolicy(sizePolicy);
        ValueEncoderOrg->setMinimumSize(QSize(60, 20));
        ValueEncoderOrg->setMaximumSize(QSize(60, 20));
        ValueEncoderOrg->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ValueEncoderOrg->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueEncoderOrg->setDecimals(1);
        ValueEncoderOrg->setMinimum(-10000);
        ValueEncoderOrg->setMaximum(10000);

        horizontalLayout->addWidget(ValueEncoderOrg);

        LabeEncoderOrgUnit = new QLabel(layoutWidget);
        LabeEncoderOrgUnit->setObjectName(QString::fromUtf8("LabeEncoderOrgUnit"));

        horizontalLayout->addWidget(LabeEncoderOrgUnit);

        ComVoltageUt = new QComboBox(scrollAreaWidgetContents);
        ComVoltageUt->setObjectName(QString::fromUtf8("ComVoltageUt"));
        ComVoltageUt->setGeometry(QRect(110, 470, 78, 20));
        ComVoltagePa = new QComboBox(scrollAreaWidgetContents);
        ComVoltagePa->setObjectName(QString::fromUtf8("ComVoltagePa"));
        ComVoltagePa->setGeometry(QRect(110, 440, 78, 20));
        LabelScanPos = new QLabel(scrollAreaWidgetContents);
        LabelScanPos->setObjectName(QString::fromUtf8("LabelScanPos"));
        LabelScanPos->setGeometry(QRect(13, 500, 131, 28));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        LabelScanPos->setFont(font);
        SliderCurrentScanPos = new QSlider(scrollAreaWidgetContents);
        SliderCurrentScanPos->setObjectName(QString::fromUtf8("SliderCurrentScanPos"));
        SliderCurrentScanPos->setGeometry(QRect(20, 525, 231, 21));
        SliderCurrentScanPos->setMinimum(1);
        SliderCurrentScanPos->setMaximum(256);
        SliderCurrentScanPos->setPageStep(1);
        SliderCurrentScanPos->setOrientation(Qt::Horizontal);
        SpinBoxCurrentScanPos = new QDoubleSpinBox(scrollAreaWidgetContents);
        SpinBoxCurrentScanPos->setObjectName(QString::fromUtf8("SpinBoxCurrentScanPos"));
        SpinBoxCurrentScanPos->setGeometry(QRect(140, 503, 91, 20));
        SpinBoxCurrentScanPos->setAlignment(Qt::AlignCenter);
        SpinBoxCurrentScanPos->setButtonSymbols(QAbstractSpinBox::NoButtons);
        SpinBoxCurrentScanPos->setMinimum(-10000);
        SpinBoxCurrentScanPos->setMaximum(10000);
        LabelIndexPos = new QLabel(scrollAreaWidgetContents);
        LabelIndexPos->setObjectName(QString::fromUtf8("LabelIndexPos"));
        LabelIndexPos->setGeometry(QRect(13, 544, 131, 28));
        LabelIndexPos->setFont(font);
        SpinBoxCurrentIndexPos = new QDoubleSpinBox(scrollAreaWidgetContents);
        SpinBoxCurrentIndexPos->setObjectName(QString::fromUtf8("SpinBoxCurrentIndexPos"));
        SpinBoxCurrentIndexPos->setGeometry(QRect(140, 547, 91, 20));
        SpinBoxCurrentIndexPos->setAlignment(Qt::AlignCenter);
        SpinBoxCurrentIndexPos->setButtonSymbols(QAbstractSpinBox::NoButtons);
        SliderCurrentIndexPos = new QSlider(scrollAreaWidgetContents);
        SliderCurrentIndexPos->setObjectName(QString::fromUtf8("SliderCurrentIndexPos"));
        SliderCurrentIndexPos->setGeometry(QRect(20, 569, 231, 21));
        SliderCurrentIndexPos->setMinimum(1);
        SliderCurrentIndexPos->setMaximum(256);
        SliderCurrentIndexPos->setPageStep(1);
        SliderCurrentIndexPos->setOrientation(Qt::Horizontal);
        LabelScanPosUnit = new QLabel(scrollAreaWidgetContents);
        LabelScanPosUnit->setObjectName(QString::fromUtf8("LabelScanPosUnit"));
        LabelScanPosUnit->setGeometry(QRect(240, 505, 41, 20));
        LabelIndexPosUnit = new QLabel(scrollAreaWidgetContents);
        LabelIndexPosUnit->setObjectName(QString::fromUtf8("LabelIndexPosUnit"));
        LabelIndexPosUnit->setGeometry(QRect(240, 549, 41, 20));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(InstrumentSettingWidget);

        QMetaObject::connectSlotsByName(InstrumentSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *InstrumentSettingWidget)
    {
        InstrumentSettingWidget->setWindowTitle(QApplication::translate("InstrumentSettingWidget", "Form", 0, QApplication::UnicodeUTF8));
        LabelPaValtage->setText(QApplication::translate("InstrumentSettingWidget", "PA Voltage:", 0, QApplication::UnicodeUTF8));
        LabelUtVolatage->setText(QApplication::translate("InstrumentSettingWidget", "UT Voltage:", 0, QApplication::UnicodeUTF8));
        LabelScanType->setText(QApplication::translate("InstrumentSettingWidget", "Scan Type:", 0, QApplication::UnicodeUTF8));
        ComScanType->clear();
        ComScanType->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "One Line Scan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Two Line Scan", 0, QApplication::UnicodeUTF8)
        );
        LabelEncoderType->setText(QApplication::translate("InstrumentSettingWidget", "Encoder Type:", 0, QApplication::UnicodeUTF8));
        ComEncoderType->clear();
        ComEncoderType->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Time", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Encoder X", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Encoder Y", 0, QApplication::UnicodeUTF8)
        );
        LabelPrf->setText(QApplication::translate("InstrumentSettingWidget", "PRF:", 0, QApplication::UnicodeUTF8));
        BoxScanArea->setTitle(QApplication::translate("InstrumentSettingWidget", "Area", 0, QApplication::UnicodeUTF8));
        LabelPaValtage_2->setText(QApplication::translate("InstrumentSettingWidget", "Scan Axis", 0, QApplication::UnicodeUTF8));
        LabelPaValtage_3->setText(QApplication::translate("InstrumentSettingWidget", "Index Axis", 0, QApplication::UnicodeUTF8));
        LabelScanStart->setText(QApplication::translate("InstrumentSettingWidget", "Start:", 0, QApplication::UnicodeUTF8));
        LabelScanStartUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", 0, QApplication::UnicodeUTF8));
        LabelScanEnd->setText(QApplication::translate("InstrumentSettingWidget", "End :", 0, QApplication::UnicodeUTF8));
        LabelScanEndUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", 0, QApplication::UnicodeUTF8));
        LabelScanResolution->setText(QApplication::translate("InstrumentSettingWidget", "Resolution:", 0, QApplication::UnicodeUTF8));
        LabelScanResolutionUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", 0, QApplication::UnicodeUTF8));
        BoxEncoderMode->setTitle(QApplication::translate("InstrumentSettingWidget", "Encoder Mode", 0, QApplication::UnicodeUTF8));
        LabelEncoderType_2->setText(QApplication::translate("InstrumentSettingWidget", "Encoder Type:", 0, QApplication::UnicodeUTF8));
        ComEncoderTypeSetting->clear();
        ComEncoderTypeSetting->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Encoder X", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Encoder Y", 0, QApplication::UnicodeUTF8)
        );
        LabelResolution->setText(QApplication::translate("InstrumentSettingWidget", "Resolution:", 0, QApplication::UnicodeUTF8));
        LabelEncoderResolutionUnit->setText(QApplication::translate("InstrumentSettingWidget", "Steps/mm", 0, QApplication::UnicodeUTF8));
        LabelEncoderPolarity->setText(QApplication::translate("InstrumentSettingWidget", "Polarity:", 0, QApplication::UnicodeUTF8));
        ComEncoderPolarity->clear();
        ComEncoderPolarity->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Inverse", 0, QApplication::UnicodeUTF8)
        );
        LabelEncoderDirection->setText(QApplication::translate("InstrumentSettingWidget", "Direction:", 0, QApplication::UnicodeUTF8));
        ComEncoderDirection->clear();
        ComEncoderDirection->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Quad", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Up", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "Down", 0, QApplication::UnicodeUTF8)
        );
        LabelEncoderOrg->setText(QApplication::translate("InstrumentSettingWidget", "Origin:", 0, QApplication::UnicodeUTF8));
        LabeEncoderOrgUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", 0, QApplication::UnicodeUTF8));
        ComVoltageUt->clear();
        ComVoltageUt->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "  50V", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "100V ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "200V", 0, QApplication::UnicodeUTF8)
        );
        ComVoltagePa->clear();
        ComVoltagePa->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "  50V", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InstrumentSettingWidget", "100V ", 0, QApplication::UnicodeUTF8)
        );
        LabelScanPos->setText(QApplication::translate("InstrumentSettingWidget", "Current Scan Pos:", 0, QApplication::UnicodeUTF8));
        LabelIndexPos->setText(QApplication::translate("InstrumentSettingWidget", "Current Index Pos:", 0, QApplication::UnicodeUTF8));
        LabelScanPosUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", 0, QApplication::UnicodeUTF8));
        LabelIndexPosUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InstrumentSettingWidget: public Ui_InstrumentSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTRUMENTSETTINGWIDGET_H
