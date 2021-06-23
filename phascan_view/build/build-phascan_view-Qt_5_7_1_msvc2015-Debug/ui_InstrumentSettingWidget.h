/********************************************************************************
** Form generated from reading UI file 'InstrumentSettingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTRUMENTSETTINGWIDGET_H
#define UI_INSTRUMENTSETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InstrumentSettingWidget
{
public:
    QHBoxLayout *horizontalLayout_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *LabelScanType;
    QComboBox *ComEncoderType;
    QDoubleSpinBox *ValuePrf;
    QLabel *LabelPrf;
    QLabel *LabelEncoderType;
    QComboBox *ComScanType;
    QLabel *LabelTopcMergeCompareView;
    QComboBox *ComTopcMergeCompareView;
    QGroupBox *BoxScanArea;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QLabel *LabelPaValtage_2;
    QLabel *LabelPaValtage_3;
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
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *LabelEncoderType_2;
    QComboBox *ComEncoderTypeSetting;
    QLabel *LabelResolution;
    QDoubleSpinBox *ValueEncoderResolution;
    QLabel *LabelEncoderResolutionUnit;
    QLabel *LabelEncoderPolarity;
    QComboBox *ComEncoderPolarity;
    QLabel *LabelEncoderDirection;
    QComboBox *ComEncoderDirection;
    QLabel *LabelEncoderOrg;
    QDoubleSpinBox *ValueEncoderOrg;
    QLabel *LabeEncoderOrgUnit;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBoxVoltage;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QLabel *LabelPaValtage;
    QComboBox *ComVoltagePa;
    QComboBox *ComVoltageUt;
    QLabel *LabelUtVolatage;
    QPushButton *BtnReset;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *LabelScanPos;
    QDoubleSpinBox *SpinBoxCurrentScanPos;
    QLabel *LabelScanPosUnit;
    QSlider *SliderCurrentScanPos;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LabelIndexPos;
    QDoubleSpinBox *SpinBoxCurrentIndexPos;
    QLabel *LabelIndexPosUnit;
    QSlider *SliderCurrentIndexPos;
    QHBoxLayout *horizontalLayout_7;
    QLabel *rasterOffsetLabel;
    QDoubleSpinBox *SpinBoxRasterOffset;
    QLabel *rasterOffsetUnitLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *SpinBoxCurrentScanstart;
    QLabel *LabelScanStartUnit_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QDoubleSpinBox *SpinBoxCurrentScanend;
    QLabel *LabelScanStopUnit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QDoubleSpinBox *SpinBoxCurrentIndexstart;
    QLabel *LabelIndexStartUnit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QDoubleSpinBox *SpinBoxCurrentIndexend;
    QLabel *LabelIndexStopUnit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *InstrumentSettingWidget)
    {
        if (InstrumentSettingWidget->objectName().isEmpty())
            InstrumentSettingWidget->setObjectName(QStringLiteral("InstrumentSettingWidget"));
        InstrumentSettingWidget->resize(357, 570);
        horizontalLayout_8 = new QHBoxLayout(InstrumentSettingWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        scrollArea = new QScrollArea(InstrumentSettingWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -288, 320, 840));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(9, 4, 9, -1);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        LabelScanType = new QLabel(groupBox);
        LabelScanType->setObjectName(QStringLiteral("LabelScanType"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LabelScanType->sizePolicy().hasHeightForWidth());
        LabelScanType->setSizePolicy(sizePolicy);
        LabelScanType->setMinimumSize(QSize(70, 20));
        LabelScanType->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(LabelScanType, 0, 0, 1, 1);

        ComEncoderType = new QComboBox(groupBox);
        ComEncoderType->setObjectName(QStringLiteral("ComEncoderType"));

        gridLayout_2->addWidget(ComEncoderType, 1, 1, 1, 1);

        ValuePrf = new QDoubleSpinBox(groupBox);
        ValuePrf->setObjectName(QStringLiteral("ValuePrf"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ValuePrf->sizePolicy().hasHeightForWidth());
        ValuePrf->setSizePolicy(sizePolicy1);
        ValuePrf->setMinimumSize(QSize(50, 20));
        ValuePrf->setMaximumSize(QSize(16777215, 20));
        ValuePrf->setAlignment(Qt::AlignCenter);
        ValuePrf->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValuePrf->setDecimals(1);
        ValuePrf->setMinimum(1);
        ValuePrf->setMaximum(6000);

        gridLayout_2->addWidget(ValuePrf, 2, 1, 1, 1);

        LabelPrf = new QLabel(groupBox);
        LabelPrf->setObjectName(QStringLiteral("LabelPrf"));
        sizePolicy.setHeightForWidth(LabelPrf->sizePolicy().hasHeightForWidth());
        LabelPrf->setSizePolicy(sizePolicy);
        LabelPrf->setMinimumSize(QSize(70, 20));
        LabelPrf->setMaximumSize(QSize(70, 25));

        gridLayout_2->addWidget(LabelPrf, 2, 0, 1, 1);

        LabelEncoderType = new QLabel(groupBox);
        LabelEncoderType->setObjectName(QStringLiteral("LabelEncoderType"));
        sizePolicy.setHeightForWidth(LabelEncoderType->sizePolicy().hasHeightForWidth());
        LabelEncoderType->setSizePolicy(sizePolicy);
        LabelEncoderType->setMinimumSize(QSize(70, 20));
        LabelEncoderType->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(LabelEncoderType, 1, 0, 1, 1);

        ComScanType = new QComboBox(groupBox);
        ComScanType->setObjectName(QStringLiteral("ComScanType"));

        gridLayout_2->addWidget(ComScanType, 0, 1, 1, 1);

        LabelTopcMergeCompareView = new QLabel(groupBox);
        LabelTopcMergeCompareView->setObjectName(QStringLiteral("LabelTopcMergeCompareView"));

        gridLayout_2->addWidget(LabelTopcMergeCompareView, 3, 0, 1, 1);

        ComTopcMergeCompareView = new QComboBox(groupBox);
        ComTopcMergeCompareView->setObjectName(QStringLiteral("ComTopcMergeCompareView"));

        gridLayout_2->addWidget(ComTopcMergeCompareView, 3, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        BoxScanArea = new QGroupBox(scrollAreaWidgetContents);
        BoxScanArea->setObjectName(QStringLiteral("BoxScanArea"));
        gridLayout_4 = new QGridLayout(BoxScanArea);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        LabelPaValtage_2 = new QLabel(BoxScanArea);
        LabelPaValtage_2->setObjectName(QStringLiteral("LabelPaValtage_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(111);
        sizePolicy2.setVerticalStretch(25);
        sizePolicy2.setHeightForWidth(LabelPaValtage_2->sizePolicy().hasHeightForWidth());
        LabelPaValtage_2->setSizePolicy(sizePolicy2);
        LabelPaValtage_2->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(LabelPaValtage_2, 0, 1, 1, 1);

        LabelPaValtage_3 = new QLabel(BoxScanArea);
        LabelPaValtage_3->setObjectName(QStringLiteral("LabelPaValtage_3"));
        sizePolicy2.setHeightForWidth(LabelPaValtage_3->sizePolicy().hasHeightForWidth());
        LabelPaValtage_3->setSizePolicy(sizePolicy2);
        LabelPaValtage_3->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(LabelPaValtage_3, 0, 2, 1, 1);

        LabelScanStart = new QLabel(BoxScanArea);
        LabelScanStart->setObjectName(QStringLiteral("LabelScanStart"));
        sizePolicy.setHeightForWidth(LabelScanStart->sizePolicy().hasHeightForWidth());
        LabelScanStart->setSizePolicy(sizePolicy);
        LabelScanStart->setMinimumSize(QSize(70, 20));
        LabelScanStart->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(LabelScanStart, 1, 0, 1, 1);

        ValueScanStart = new QDoubleSpinBox(BoxScanArea);
        ValueScanStart->setObjectName(QStringLiteral("ValueScanStart"));
        sizePolicy.setHeightForWidth(ValueScanStart->sizePolicy().hasHeightForWidth());
        ValueScanStart->setSizePolicy(sizePolicy);
        ValueScanStart->setMinimumSize(QSize(60, 20));
        ValueScanStart->setMaximumSize(QSize(60, 20));
        ValueScanStart->setAlignment(Qt::AlignCenter);
        ValueScanStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanStart->setDecimals(1);
        ValueScanStart->setMinimum(-10000);
        ValueScanStart->setMaximum(10000);

        gridLayout->addWidget(ValueScanStart, 1, 1, 1, 1);

        ValueIndexStart = new QDoubleSpinBox(BoxScanArea);
        ValueIndexStart->setObjectName(QStringLiteral("ValueIndexStart"));
        sizePolicy.setHeightForWidth(ValueIndexStart->sizePolicy().hasHeightForWidth());
        ValueIndexStart->setSizePolicy(sizePolicy);
        ValueIndexStart->setMinimumSize(QSize(60, 20));
        ValueIndexStart->setMaximumSize(QSize(60, 20));
        ValueIndexStart->setAlignment(Qt::AlignCenter);
        ValueIndexStart->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexStart->setDecimals(1);
        ValueIndexStart->setMinimum(-10000);
        ValueIndexStart->setMaximum(10000);

        gridLayout->addWidget(ValueIndexStart, 1, 2, 1, 1);

        LabelScanStartUnit = new QLabel(BoxScanArea);
        LabelScanStartUnit->setObjectName(QStringLiteral("LabelScanStartUnit"));
        LabelScanStartUnit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LabelScanStartUnit, 1, 3, 1, 1);

        LabelScanEnd = new QLabel(BoxScanArea);
        LabelScanEnd->setObjectName(QStringLiteral("LabelScanEnd"));
        sizePolicy.setHeightForWidth(LabelScanEnd->sizePolicy().hasHeightForWidth());
        LabelScanEnd->setSizePolicy(sizePolicy);
        LabelScanEnd->setMinimumSize(QSize(70, 20));
        LabelScanEnd->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(LabelScanEnd, 2, 0, 1, 1);

        ValueScanEnd = new QDoubleSpinBox(BoxScanArea);
        ValueScanEnd->setObjectName(QStringLiteral("ValueScanEnd"));
        sizePolicy.setHeightForWidth(ValueScanEnd->sizePolicy().hasHeightForWidth());
        ValueScanEnd->setSizePolicy(sizePolicy);
        ValueScanEnd->setMinimumSize(QSize(60, 20));
        ValueScanEnd->setMaximumSize(QSize(60, 20));
        ValueScanEnd->setAlignment(Qt::AlignCenter);
        ValueScanEnd->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanEnd->setDecimals(1);
        ValueScanEnd->setMinimum(-10000);
        ValueScanEnd->setMaximum(10000);

        gridLayout->addWidget(ValueScanEnd, 2, 1, 1, 1);

        ValueIndexStop = new QDoubleSpinBox(BoxScanArea);
        ValueIndexStop->setObjectName(QStringLiteral("ValueIndexStop"));
        sizePolicy.setHeightForWidth(ValueIndexStop->sizePolicy().hasHeightForWidth());
        ValueIndexStop->setSizePolicy(sizePolicy);
        ValueIndexStop->setMinimumSize(QSize(60, 20));
        ValueIndexStop->setMaximumSize(QSize(60, 20));
        ValueIndexStop->setAlignment(Qt::AlignCenter);
        ValueIndexStop->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexStop->setDecimals(1);
        ValueIndexStop->setMinimum(-10000);
        ValueIndexStop->setMaximum(10000);

        gridLayout->addWidget(ValueIndexStop, 2, 2, 1, 1);

        LabelScanEndUnit = new QLabel(BoxScanArea);
        LabelScanEndUnit->setObjectName(QStringLiteral("LabelScanEndUnit"));
        LabelScanEndUnit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LabelScanEndUnit, 2, 3, 1, 1);

        LabelScanResolution = new QLabel(BoxScanArea);
        LabelScanResolution->setObjectName(QStringLiteral("LabelScanResolution"));
        sizePolicy.setHeightForWidth(LabelScanResolution->sizePolicy().hasHeightForWidth());
        LabelScanResolution->setSizePolicy(sizePolicy);
        LabelScanResolution->setMinimumSize(QSize(70, 20));
        LabelScanResolution->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(LabelScanResolution, 3, 0, 1, 1);

        ValueScanResolution = new QDoubleSpinBox(BoxScanArea);
        ValueScanResolution->setObjectName(QStringLiteral("ValueScanResolution"));
        sizePolicy.setHeightForWidth(ValueScanResolution->sizePolicy().hasHeightForWidth());
        ValueScanResolution->setSizePolicy(sizePolicy);
        ValueScanResolution->setMinimumSize(QSize(60, 20));
        ValueScanResolution->setMaximumSize(QSize(60, 20));
        ValueScanResolution->setAlignment(Qt::AlignCenter);
        ValueScanResolution->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueScanResolution->setDecimals(1);
        ValueScanResolution->setMinimum(-10000);
        ValueScanResolution->setMaximum(10000);

        gridLayout->addWidget(ValueScanResolution, 3, 1, 1, 1);

        ValueIndexResolution = new QDoubleSpinBox(BoxScanArea);
        ValueIndexResolution->setObjectName(QStringLiteral("ValueIndexResolution"));
        sizePolicy.setHeightForWidth(ValueIndexResolution->sizePolicy().hasHeightForWidth());
        ValueIndexResolution->setSizePolicy(sizePolicy);
        ValueIndexResolution->setMinimumSize(QSize(60, 20));
        ValueIndexResolution->setMaximumSize(QSize(60, 20));
        ValueIndexResolution->setAlignment(Qt::AlignCenter);
        ValueIndexResolution->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueIndexResolution->setDecimals(1);
        ValueIndexResolution->setMinimum(-10000);
        ValueIndexResolution->setMaximum(10000);

        gridLayout->addWidget(ValueIndexResolution, 3, 2, 1, 1);

        LabelScanResolutionUnit = new QLabel(BoxScanArea);
        LabelScanResolutionUnit->setObjectName(QStringLiteral("LabelScanResolutionUnit"));
        LabelScanResolutionUnit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LabelScanResolutionUnit, 3, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(BoxScanArea);

        BoxEncoderMode = new QGroupBox(scrollAreaWidgetContents);
        BoxEncoderMode->setObjectName(QStringLiteral("BoxEncoderMode"));
        gridLayout_6 = new QGridLayout(BoxEncoderMode);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        LabelEncoderType_2 = new QLabel(BoxEncoderMode);
        LabelEncoderType_2->setObjectName(QStringLiteral("LabelEncoderType_2"));
        sizePolicy.setHeightForWidth(LabelEncoderType_2->sizePolicy().hasHeightForWidth());
        LabelEncoderType_2->setSizePolicy(sizePolicy);
        LabelEncoderType_2->setMinimumSize(QSize(70, 20));

        gridLayout_5->addWidget(LabelEncoderType_2, 0, 0, 1, 1);

        ComEncoderTypeSetting = new QComboBox(BoxEncoderMode);
        ComEncoderTypeSetting->setObjectName(QStringLiteral("ComEncoderTypeSetting"));

        gridLayout_5->addWidget(ComEncoderTypeSetting, 0, 1, 1, 1);

        LabelResolution = new QLabel(BoxEncoderMode);
        LabelResolution->setObjectName(QStringLiteral("LabelResolution"));
        sizePolicy.setHeightForWidth(LabelResolution->sizePolicy().hasHeightForWidth());
        LabelResolution->setSizePolicy(sizePolicy);
        LabelResolution->setMinimumSize(QSize(70, 20));
        LabelResolution->setMaximumSize(QSize(90, 16777215));

        gridLayout_5->addWidget(LabelResolution, 1, 0, 1, 1);

        ValueEncoderResolution = new QDoubleSpinBox(BoxEncoderMode);
        ValueEncoderResolution->setObjectName(QStringLiteral("ValueEncoderResolution"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ValueEncoderResolution->sizePolicy().hasHeightForWidth());
        ValueEncoderResolution->setSizePolicy(sizePolicy3);
        ValueEncoderResolution->setMinimumSize(QSize(0, 20));
        ValueEncoderResolution->setMaximumSize(QSize(1777125, 20));
        ValueEncoderResolution->setAlignment(Qt::AlignCenter);
        ValueEncoderResolution->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueEncoderResolution->setDecimals(2);
        ValueEncoderResolution->setMinimum(1);
        ValueEncoderResolution->setMaximum(10000);

        gridLayout_5->addWidget(ValueEncoderResolution, 1, 1, 1, 1);

        LabelEncoderResolutionUnit = new QLabel(BoxEncoderMode);
        LabelEncoderResolutionUnit->setObjectName(QStringLiteral("LabelEncoderResolutionUnit"));
        LabelEncoderResolutionUnit->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(LabelEncoderResolutionUnit, 1, 2, 1, 1);

        LabelEncoderPolarity = new QLabel(BoxEncoderMode);
        LabelEncoderPolarity->setObjectName(QStringLiteral("LabelEncoderPolarity"));
        sizePolicy.setHeightForWidth(LabelEncoderPolarity->sizePolicy().hasHeightForWidth());
        LabelEncoderPolarity->setSizePolicy(sizePolicy);
        LabelEncoderPolarity->setMinimumSize(QSize(70, 20));
        LabelEncoderPolarity->setMaximumSize(QSize(90, 16777215));

        gridLayout_5->addWidget(LabelEncoderPolarity, 2, 0, 1, 1);

        ComEncoderPolarity = new QComboBox(BoxEncoderMode);
        ComEncoderPolarity->setObjectName(QStringLiteral("ComEncoderPolarity"));

        gridLayout_5->addWidget(ComEncoderPolarity, 2, 1, 1, 1);

        LabelEncoderDirection = new QLabel(BoxEncoderMode);
        LabelEncoderDirection->setObjectName(QStringLiteral("LabelEncoderDirection"));
        sizePolicy.setHeightForWidth(LabelEncoderDirection->sizePolicy().hasHeightForWidth());
        LabelEncoderDirection->setSizePolicy(sizePolicy);
        LabelEncoderDirection->setMinimumSize(QSize(70, 20));
        LabelEncoderDirection->setMaximumSize(QSize(90, 16777215));

        gridLayout_5->addWidget(LabelEncoderDirection, 3, 0, 1, 1);

        ComEncoderDirection = new QComboBox(BoxEncoderMode);
        ComEncoderDirection->setObjectName(QStringLiteral("ComEncoderDirection"));

        gridLayout_5->addWidget(ComEncoderDirection, 3, 1, 1, 1);

        LabelEncoderOrg = new QLabel(BoxEncoderMode);
        LabelEncoderOrg->setObjectName(QStringLiteral("LabelEncoderOrg"));
        sizePolicy.setHeightForWidth(LabelEncoderOrg->sizePolicy().hasHeightForWidth());
        LabelEncoderOrg->setSizePolicy(sizePolicy);
        LabelEncoderOrg->setMinimumSize(QSize(70, 20));
        LabelEncoderOrg->setMaximumSize(QSize(90, 16777215));

        gridLayout_5->addWidget(LabelEncoderOrg, 4, 0, 1, 1);

        ValueEncoderOrg = new QDoubleSpinBox(BoxEncoderMode);
        ValueEncoderOrg->setObjectName(QStringLiteral("ValueEncoderOrg"));
        sizePolicy3.setHeightForWidth(ValueEncoderOrg->sizePolicy().hasHeightForWidth());
        ValueEncoderOrg->setSizePolicy(sizePolicy3);
        ValueEncoderOrg->setMinimumSize(QSize(0, 0));
        ValueEncoderOrg->setMaximumSize(QSize(1777125, 20));
        ValueEncoderOrg->setAlignment(Qt::AlignCenter);
        ValueEncoderOrg->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ValueEncoderOrg->setDecimals(1);
        ValueEncoderOrg->setMinimum(-10000);
        ValueEncoderOrg->setMaximum(10000);

        gridLayout_5->addWidget(ValueEncoderOrg, 4, 1, 1, 1);

        LabeEncoderOrgUnit = new QLabel(BoxEncoderMode);
        LabeEncoderOrgUnit->setObjectName(QStringLiteral("LabeEncoderOrgUnit"));
        LabeEncoderOrgUnit->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(LabeEncoderOrgUnit, 4, 2, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);


        verticalLayout_2->addWidget(BoxEncoderMode);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        groupBoxVoltage = new QGroupBox(scrollAreaWidgetContents);
        groupBoxVoltage->setObjectName(QStringLiteral("groupBoxVoltage"));
        groupBoxVoltage->setFlat(false);
        gridLayout_8 = new QGridLayout(groupBoxVoltage);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        LabelPaValtage = new QLabel(groupBoxVoltage);
        LabelPaValtage->setObjectName(QStringLiteral("LabelPaValtage"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(LabelPaValtage->sizePolicy().hasHeightForWidth());
        LabelPaValtage->setSizePolicy(sizePolicy4);
        LabelPaValtage->setMinimumSize(QSize(70, 20));
        LabelPaValtage->setMaximumSize(QSize(100, 16777215));

        gridLayout_7->addWidget(LabelPaValtage, 0, 0, 1, 1);

        ComVoltagePa = new QComboBox(groupBoxVoltage);
        ComVoltagePa->setObjectName(QStringLiteral("ComVoltagePa"));

        gridLayout_7->addWidget(ComVoltagePa, 0, 1, 1, 1);

        ComVoltageUt = new QComboBox(groupBoxVoltage);
        ComVoltageUt->setObjectName(QStringLiteral("ComVoltageUt"));

        gridLayout_7->addWidget(ComVoltageUt, 1, 1, 1, 1);

        LabelUtVolatage = new QLabel(groupBoxVoltage);
        LabelUtVolatage->setObjectName(QStringLiteral("LabelUtVolatage"));
        sizePolicy4.setHeightForWidth(LabelUtVolatage->sizePolicy().hasHeightForWidth());
        LabelUtVolatage->setSizePolicy(sizePolicy4);
        LabelUtVolatage->setMinimumSize(QSize(70, 20));
        LabelUtVolatage->setMaximumSize(QSize(100, 16777215));

        gridLayout_7->addWidget(LabelUtVolatage, 1, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);


        horizontalLayout_9->addWidget(groupBoxVoltage);

        BtnReset = new QPushButton(scrollAreaWidgetContents);
        BtnReset->setObjectName(QStringLiteral("BtnReset"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(BtnReset->sizePolicy().hasHeightForWidth());
        BtnReset->setSizePolicy(sizePolicy5);
        BtnReset->setMinimumSize(QSize(0, 40));
        BtnReset->setMaximumSize(QSize(16777215, 80));

        horizontalLayout_9->addWidget(BtnReset);


        verticalLayout_2->addLayout(horizontalLayout_9);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        LabelScanPos = new QLabel(groupBox_3);
        LabelScanPos->setObjectName(QStringLiteral("LabelScanPos"));
        LabelScanPos->setMinimumSize(QSize(120, 0));
        LabelScanPos->setMaximumSize(QSize(150, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        LabelScanPos->setFont(font);

        horizontalLayout->addWidget(LabelScanPos);

        SpinBoxCurrentScanPos = new QDoubleSpinBox(groupBox_3);
        SpinBoxCurrentScanPos->setObjectName(QStringLiteral("SpinBoxCurrentScanPos"));
        sizePolicy4.setHeightForWidth(SpinBoxCurrentScanPos->sizePolicy().hasHeightForWidth());
        SpinBoxCurrentScanPos->setSizePolicy(sizePolicy4);
        SpinBoxCurrentScanPos->setMinimumSize(QSize(80, 20));
        SpinBoxCurrentScanPos->setMaximumSize(QSize(80, 20));
        SpinBoxCurrentScanPos->setAlignment(Qt::AlignCenter);
        SpinBoxCurrentScanPos->setButtonSymbols(QAbstractSpinBox::NoButtons);
        SpinBoxCurrentScanPos->setMinimum(-10000);
        SpinBoxCurrentScanPos->setMaximum(10000);

        horizontalLayout->addWidget(SpinBoxCurrentScanPos);

        LabelScanPosUnit = new QLabel(groupBox_3);
        LabelScanPosUnit->setObjectName(QStringLiteral("LabelScanPosUnit"));
        LabelScanPosUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(LabelScanPosUnit);


        verticalLayout->addLayout(horizontalLayout);

        SliderCurrentScanPos = new QSlider(groupBox_3);
        SliderCurrentScanPos->setObjectName(QStringLiteral("SliderCurrentScanPos"));
        SliderCurrentScanPos->setMinimum(1);
        SliderCurrentScanPos->setMaximum(256);
        SliderCurrentScanPos->setPageStep(1);
        SliderCurrentScanPos->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(SliderCurrentScanPos);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        LabelIndexPos = new QLabel(groupBox_3);
        LabelIndexPos->setObjectName(QStringLiteral("LabelIndexPos"));
        LabelIndexPos->setMinimumSize(QSize(120, 0));
        LabelIndexPos->setMaximumSize(QSize(150, 16777215));
        LabelIndexPos->setFont(font);

        horizontalLayout_2->addWidget(LabelIndexPos);

        SpinBoxCurrentIndexPos = new QDoubleSpinBox(groupBox_3);
        SpinBoxCurrentIndexPos->setObjectName(QStringLiteral("SpinBoxCurrentIndexPos"));
        sizePolicy4.setHeightForWidth(SpinBoxCurrentIndexPos->sizePolicy().hasHeightForWidth());
        SpinBoxCurrentIndexPos->setSizePolicy(sizePolicy4);
        SpinBoxCurrentIndexPos->setMinimumSize(QSize(80, 20));
        SpinBoxCurrentIndexPos->setMaximumSize(QSize(80, 20));
        SpinBoxCurrentIndexPos->setAlignment(Qt::AlignCenter);
        SpinBoxCurrentIndexPos->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_2->addWidget(SpinBoxCurrentIndexPos);

        LabelIndexPosUnit = new QLabel(groupBox_3);
        LabelIndexPosUnit->setObjectName(QStringLiteral("LabelIndexPosUnit"));
        LabelIndexPosUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(LabelIndexPosUnit);


        verticalLayout->addLayout(horizontalLayout_2);

        SliderCurrentIndexPos = new QSlider(groupBox_3);
        SliderCurrentIndexPos->setObjectName(QStringLiteral("SliderCurrentIndexPos"));
        SliderCurrentIndexPos->setMinimum(1);
        SliderCurrentIndexPos->setMaximum(256);
        SliderCurrentIndexPos->setPageStep(1);
        SliderCurrentIndexPos->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(SliderCurrentIndexPos);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        rasterOffsetLabel = new QLabel(groupBox_3);
        rasterOffsetLabel->setObjectName(QStringLiteral("rasterOffsetLabel"));
        rasterOffsetLabel->setMinimumSize(QSize(110, 0));
        rasterOffsetLabel->setFont(font);

        horizontalLayout_7->addWidget(rasterOffsetLabel);

        SpinBoxRasterOffset = new QDoubleSpinBox(groupBox_3);
        SpinBoxRasterOffset->setObjectName(QStringLiteral("SpinBoxRasterOffset"));
        sizePolicy4.setHeightForWidth(SpinBoxRasterOffset->sizePolicy().hasHeightForWidth());
        SpinBoxRasterOffset->setSizePolicy(sizePolicy4);
        SpinBoxRasterOffset->setMinimumSize(QSize(80, 20));
        SpinBoxRasterOffset->setMaximumSize(QSize(80, 20));
        SpinBoxRasterOffset->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        SpinBoxRasterOffset->setButtonSymbols(QAbstractSpinBox::NoButtons);
        SpinBoxRasterOffset->setKeyboardTracking(false);
        SpinBoxRasterOffset->setDecimals(1);
        SpinBoxRasterOffset->setMinimum(-100);
        SpinBoxRasterOffset->setMaximum(100);

        horizontalLayout_7->addWidget(SpinBoxRasterOffset);

        rasterOffsetUnitLabel = new QLabel(groupBox_3);
        rasterOffsetUnitLabel->setObjectName(QStringLiteral("rasterOffsetUnitLabel"));

        horizontalLayout_7->addWidget(rasterOffsetUnitLabel);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(110, 0));
        label_4->setMaximumSize(QSize(150, 16777215));
        label_4->setFont(font);

        horizontalLayout_3->addWidget(label_4);

        SpinBoxCurrentScanstart = new QDoubleSpinBox(groupBox_3);
        SpinBoxCurrentScanstart->setObjectName(QStringLiteral("SpinBoxCurrentScanstart"));
        SpinBoxCurrentScanstart->setMinimumSize(QSize(80, 20));
        SpinBoxCurrentScanstart->setMaximumSize(QSize(80, 20));
        SpinBoxCurrentScanstart->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_3->addWidget(SpinBoxCurrentScanstart);

        LabelScanStartUnit_2 = new QLabel(groupBox_3);
        LabelScanStartUnit_2->setObjectName(QStringLiteral("LabelScanStartUnit_2"));

        horizontalLayout_3->addWidget(LabelScanStartUnit_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(110, 0));
        label_2->setMaximumSize(QSize(150, 16777215));
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        SpinBoxCurrentScanend = new QDoubleSpinBox(groupBox_3);
        SpinBoxCurrentScanend->setObjectName(QStringLiteral("SpinBoxCurrentScanend"));
        SpinBoxCurrentScanend->setMinimumSize(QSize(80, 20));
        SpinBoxCurrentScanend->setMaximumSize(QSize(80, 20));
        SpinBoxCurrentScanend->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_4->addWidget(SpinBoxCurrentScanend);

        LabelScanStopUnit = new QLabel(groupBox_3);
        LabelScanStopUnit->setObjectName(QStringLiteral("LabelScanStopUnit"));

        horizontalLayout_4->addWidget(LabelScanStopUnit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(110, 0));
        label_7->setMaximumSize(QSize(150, 16777215));
        label_7->setFont(font);

        horizontalLayout_5->addWidget(label_7);

        SpinBoxCurrentIndexstart = new QDoubleSpinBox(groupBox_3);
        SpinBoxCurrentIndexstart->setObjectName(QStringLiteral("SpinBoxCurrentIndexstart"));
        SpinBoxCurrentIndexstart->setMinimumSize(QSize(80, 20));
        SpinBoxCurrentIndexstart->setMaximumSize(QSize(80, 20));
        SpinBoxCurrentIndexstart->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_5->addWidget(SpinBoxCurrentIndexstart);

        LabelIndexStartUnit = new QLabel(groupBox_3);
        LabelIndexStartUnit->setObjectName(QStringLiteral("LabelIndexStartUnit"));

        horizontalLayout_5->addWidget(LabelIndexStartUnit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(110, 0));
        label->setMaximumSize(QSize(150, 16777215));
        label->setFont(font);

        horizontalLayout_6->addWidget(label);

        SpinBoxCurrentIndexend = new QDoubleSpinBox(groupBox_3);
        SpinBoxCurrentIndexend->setObjectName(QStringLiteral("SpinBoxCurrentIndexend"));
        SpinBoxCurrentIndexend->setMinimumSize(QSize(80, 20));
        SpinBoxCurrentIndexend->setMaximumSize(QSize(80, 20));
        SpinBoxCurrentIndexend->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_6->addWidget(SpinBoxCurrentIndexend);

        LabelIndexStopUnit = new QLabel(groupBox_3);
        LabelIndexStopUnit->setObjectName(QStringLiteral("LabelIndexStopUnit"));

        horizontalLayout_6->addWidget(LabelIndexStopUnit);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_8->addWidget(scrollArea);


        retranslateUi(InstrumentSettingWidget);

        QMetaObject::connectSlotsByName(InstrumentSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *InstrumentSettingWidget)
    {
        InstrumentSettingWidget->setWindowTitle(QApplication::translate("InstrumentSettingWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QString());
        LabelScanType->setText(QApplication::translate("InstrumentSettingWidget", "Scan Type:", Q_NULLPTR));
        ComEncoderType->clear();
        ComEncoderType->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Time", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Encoder X", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Encoder Y", Q_NULLPTR)
        );
        LabelPrf->setText(QApplication::translate("InstrumentSettingWidget", "PRF:", Q_NULLPTR));
        LabelEncoderType->setText(QApplication::translate("InstrumentSettingWidget", "Encoder Type:", Q_NULLPTR));
        ComScanType->clear();
        ComScanType->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "One Line Scan", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Two Line Scan", Q_NULLPTR)
        );
        LabelTopcMergeCompareView->setText(QApplication::translate("InstrumentSettingWidget", "Topc Merge Compare View:", Q_NULLPTR));
        ComTopcMergeCompareView->clear();
        ComTopcMergeCompareView->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "OFF", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "ON", Q_NULLPTR)
        );
        BoxScanArea->setTitle(QApplication::translate("InstrumentSettingWidget", "Area", Q_NULLPTR));
        LabelPaValtage_2->setText(QApplication::translate("InstrumentSettingWidget", "Scan Axis", Q_NULLPTR));
        LabelPaValtage_3->setText(QApplication::translate("InstrumentSettingWidget", "Index Axis", Q_NULLPTR));
        LabelScanStart->setText(QApplication::translate("InstrumentSettingWidget", "Start:", Q_NULLPTR));
        LabelScanStartUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", Q_NULLPTR));
        LabelScanEnd->setText(QApplication::translate("InstrumentSettingWidget", "End :", Q_NULLPTR));
        LabelScanEndUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", Q_NULLPTR));
        LabelScanResolution->setText(QApplication::translate("InstrumentSettingWidget", "Resolution:", Q_NULLPTR));
        LabelScanResolutionUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", Q_NULLPTR));
        BoxEncoderMode->setTitle(QApplication::translate("InstrumentSettingWidget", "Encoder Mode", Q_NULLPTR));
        LabelEncoderType_2->setText(QApplication::translate("InstrumentSettingWidget", "Encoder Type:", Q_NULLPTR));
        ComEncoderTypeSetting->clear();
        ComEncoderTypeSetting->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Encoder X", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Encoder Y", Q_NULLPTR)
        );
        LabelResolution->setText(QApplication::translate("InstrumentSettingWidget", "Resolution:", Q_NULLPTR));
        LabelEncoderResolutionUnit->setText(QApplication::translate("InstrumentSettingWidget", "Steps/mm", Q_NULLPTR));
        LabelEncoderPolarity->setText(QApplication::translate("InstrumentSettingWidget", "Polarity:", Q_NULLPTR));
        ComEncoderPolarity->clear();
        ComEncoderPolarity->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Normal", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Inverse", Q_NULLPTR)
        );
        LabelEncoderDirection->setText(QApplication::translate("InstrumentSettingWidget", "Direction:", Q_NULLPTR));
        ComEncoderDirection->clear();
        ComEncoderDirection->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "Quad", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Up", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "Down", Q_NULLPTR)
        );
        LabelEncoderOrg->setText(QApplication::translate("InstrumentSettingWidget", "Origin:", Q_NULLPTR));
        LabeEncoderOrgUnit->setText(QApplication::translate("InstrumentSettingWidget", "mm", Q_NULLPTR));
        groupBoxVoltage->setTitle(QString());
        LabelPaValtage->setText(QApplication::translate("InstrumentSettingWidget", "PA Voltage:", Q_NULLPTR));
        ComVoltagePa->clear();
        ComVoltagePa->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "  50V", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "100V ", Q_NULLPTR)
        );
        ComVoltageUt->clear();
        ComVoltageUt->insertItems(0, QStringList()
         << QApplication::translate("InstrumentSettingWidget", "  50V", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "100V ", Q_NULLPTR)
         << QApplication::translate("InstrumentSettingWidget", "200V", Q_NULLPTR)
        );
        LabelUtVolatage->setText(QApplication::translate("InstrumentSettingWidget", "UT Voltage:", Q_NULLPTR));
        BtnReset->setText(QApplication::translate("InstrumentSettingWidget", "Reset", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        LabelScanPos->setText(QApplication::translate("InstrumentSettingWidget", "Current Scan Pos:", Q_NULLPTR));
        LabelScanPosUnit->setText(QString());
        LabelIndexPos->setText(QApplication::translate("InstrumentSettingWidget", "Current Index Pos:", Q_NULLPTR));
        LabelIndexPosUnit->setText(QString());
        rasterOffsetLabel->setText(QApplication::translate("InstrumentSettingWidget", "Raster Offset:", Q_NULLPTR));
        rasterOffsetUnitLabel->setText(QString());
        label_4->setText(QApplication::translate("InstrumentSettingWidget", "Scan Start:", Q_NULLPTR));
        LabelScanStartUnit_2->setText(QString());
        label_2->setText(QApplication::translate("InstrumentSettingWidget", "Scan Stop:  ", Q_NULLPTR));
        LabelScanStopUnit->setText(QString());
        label_7->setText(QApplication::translate("InstrumentSettingWidget", "Index Start:", Q_NULLPTR));
        LabelIndexStartUnit->setText(QString());
        label->setText(QApplication::translate("InstrumentSettingWidget", "Index Stop:", Q_NULLPTR));
        LabelIndexStopUnit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InstrumentSettingWidget: public Ui_InstrumentSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTRUMENTSETTINGWIDGET_H
