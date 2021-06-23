/********************************************************************************
** Form generated from reading UI file 'DialogDxfFileLoad.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDXFFILELOAD_H
#define UI_DIALOGDXFFILELOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "painter/QWeldShowWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogDxfFileLoad
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_zoom;
    QDoubleSpinBox *doubleSpinBox_zoom;
    QLabel *LabelPartFilePath;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *WeldGroupShow;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLabel *LabelType;
    QComboBox *ComWeldType;
    QLabel *LabelSymetry;
    QComboBox *ComWeldSymetry;
    QFrame *frame_value;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *LabelWHeight;
    QDoubleSpinBox *SpinWHeight;
    QLabel *LabelUnitWHeight;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *LabelWOffset;
    QDoubleSpinBox *SpinWoffset;
    QLabel *LabelUnitWOffset;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *LabelFHeight;
    QDoubleSpinBox *SpinFHeight;
    QLabel *LabelUnitFHeight;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *LabelFHeight_2;
    QDoubleSpinBox *SpinFHeight_2;
    QLabel *LabelUnitFHeight_2;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *LabelFRadius;
    QDoubleSpinBox *SpinFRadius;
    QLabel *LabelUnitFRadius;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *LabelFAngle;
    QDoubleSpinBox *SpinFAngle;
    QLabel *LabelUnitFAngle;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_11;
    QLabel *LabelFAngle_2;
    QDoubleSpinBox *SpinFAngle_2;
    QLabel *LabelUnitFAngle_2;
    QGroupBox *PartGroupShow;
    QGridLayout *gridLayout_2;
    QPushButton *BtnNccDefaultPath;
    QPushButton *BtnNccPath;
    QLabel *LabelPartFileName;
    QListView *ListPartFile;
    QWeldShowWidget *ExpoView;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DialogDxfFileLoad)
    {
        if (DialogDxfFileLoad->objectName().isEmpty())
            DialogDxfFileLoad->setObjectName(QStringLiteral("DialogDxfFileLoad"));
        DialogDxfFileLoad->setWindowModality(Qt::NonModal);
        DialogDxfFileLoad->resize(802, 453);
        QIcon icon;
        icon.addFile(QStringLiteral(":/file/resource/main_menu/0-05.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogDxfFileLoad->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(DialogDxfFileLoad);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBox = new QComboBox(DialogDxfFileLoad);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(217, 0));
        comboBox->setMaximumSize(QSize(217, 16777215));
        comboBox->setLayoutDirection(Qt::LeftToRight);
        comboBox->setMaxVisibleItems(5);

        horizontalLayout_3->addWidget(comboBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_zoom = new QLabel(DialogDxfFileLoad);
        label_zoom->setObjectName(QStringLiteral("label_zoom"));

        horizontalLayout->addWidget(label_zoom);

        doubleSpinBox_zoom = new QDoubleSpinBox(DialogDxfFileLoad);
        doubleSpinBox_zoom->setObjectName(QStringLiteral("doubleSpinBox_zoom"));
        doubleSpinBox_zoom->setAlignment(Qt::AlignCenter);
        doubleSpinBox_zoom->setMinimum(0.01);
        doubleSpinBox_zoom->setValue(1);

        horizontalLayout->addWidget(doubleSpinBox_zoom);

        LabelPartFilePath = new QLabel(DialogDxfFileLoad);
        LabelPartFilePath->setObjectName(QStringLiteral("LabelPartFilePath"));
        LabelPartFilePath->setMinimumSize(QSize(0, 18));
        LabelPartFilePath->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(LabelPartFilePath);

        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 10);

        horizontalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        frame = new QFrame(DialogDxfFileLoad);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        WeldGroupShow = new QGroupBox(frame);
        WeldGroupShow->setObjectName(QStringLiteral("WeldGroupShow"));
        sizePolicy.setHeightForWidth(WeldGroupShow->sizePolicy().hasHeightForWidth());
        WeldGroupShow->setSizePolicy(sizePolicy);
        WeldGroupShow->setMinimumSize(QSize(180, 0));
        WeldGroupShow->setMaximumSize(QSize(217, 16777215));
        verticalLayout = new QVBoxLayout(WeldGroupShow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 6, -1, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        LabelType = new QLabel(WeldGroupShow);
        LabelType->setObjectName(QStringLiteral("LabelType"));

        gridLayout_3->addWidget(LabelType, 0, 0, 1, 1);

        ComWeldType = new QComboBox(WeldGroupShow);
        ComWeldType->setObjectName(QStringLiteral("ComWeldType"));

        gridLayout_3->addWidget(ComWeldType, 0, 1, 1, 1);

        LabelSymetry = new QLabel(WeldGroupShow);
        LabelSymetry->setObjectName(QStringLiteral("LabelSymetry"));

        gridLayout_3->addWidget(LabelSymetry, 1, 0, 1, 1);

        ComWeldSymetry = new QComboBox(WeldGroupShow);
        ComWeldSymetry->setObjectName(QStringLiteral("ComWeldSymetry"));

        gridLayout_3->addWidget(ComWeldSymetry, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        frame_value = new QFrame(WeldGroupShow);
        frame_value->setObjectName(QStringLiteral("frame_value"));
        verticalLayout_3 = new QVBoxLayout(frame_value);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_1 = new QFrame(frame_value);
        frame_1->setObjectName(QStringLiteral("frame_1"));
        frame_1->setFrameShape(QFrame::StyledPanel);
        frame_1->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_1);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        LabelWHeight = new QLabel(frame_1);
        LabelWHeight->setObjectName(QStringLiteral("LabelWHeight"));
        LabelWHeight->setMinimumSize(QSize(96, 20));
        LabelWHeight->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_5->addWidget(LabelWHeight);

        SpinWHeight = new QDoubleSpinBox(frame_1);
        SpinWHeight->setObjectName(QStringLiteral("SpinWHeight"));
        SpinWHeight->setMaximumSize(QSize(58, 16777215));
        SpinWHeight->setAlignment(Qt::AlignCenter);
        SpinWHeight->setDecimals(1);

        horizontalLayout_5->addWidget(SpinWHeight);

        LabelUnitWHeight = new QLabel(frame_1);
        LabelUnitWHeight->setObjectName(QStringLiteral("LabelUnitWHeight"));
        LabelUnitWHeight->setMinimumSize(QSize(30, 20));
        LabelUnitWHeight->setMaximumSize(QSize(30, 20));

        horizontalLayout_5->addWidget(LabelUnitWHeight);


        verticalLayout_3->addWidget(frame_1);

        frame_2 = new QFrame(frame_value);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        LabelWOffset = new QLabel(frame_2);
        LabelWOffset->setObjectName(QStringLiteral("LabelWOffset"));
        LabelWOffset->setMinimumSize(QSize(96, 0));
        LabelWOffset->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_6->addWidget(LabelWOffset);

        SpinWoffset = new QDoubleSpinBox(frame_2);
        SpinWoffset->setObjectName(QStringLiteral("SpinWoffset"));
        SpinWoffset->setMaximumSize(QSize(58, 20));
        SpinWoffset->setAlignment(Qt::AlignCenter);
        SpinWoffset->setDecimals(1);

        horizontalLayout_6->addWidget(SpinWoffset);

        LabelUnitWOffset = new QLabel(frame_2);
        LabelUnitWOffset->setObjectName(QStringLiteral("LabelUnitWOffset"));
        LabelUnitWOffset->setMaximumSize(QSize(30, 20));

        horizontalLayout_6->addWidget(LabelUnitWOffset);


        verticalLayout_3->addWidget(frame_2);

        frame_3 = new QFrame(frame_value);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_10 = new QHBoxLayout(frame_3);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        LabelFHeight = new QLabel(frame_3);
        LabelFHeight->setObjectName(QStringLiteral("LabelFHeight"));
        LabelFHeight->setMinimumSize(QSize(96, 0));
        LabelFHeight->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_10->addWidget(LabelFHeight);

        SpinFHeight = new QDoubleSpinBox(frame_3);
        SpinFHeight->setObjectName(QStringLiteral("SpinFHeight"));
        SpinFHeight->setMaximumSize(QSize(58, 20));
        SpinFHeight->setAlignment(Qt::AlignCenter);
        SpinFHeight->setDecimals(1);

        horizontalLayout_10->addWidget(SpinFHeight);

        LabelUnitFHeight = new QLabel(frame_3);
        LabelUnitFHeight->setObjectName(QStringLiteral("LabelUnitFHeight"));
        LabelUnitFHeight->setMaximumSize(QSize(30, 20));

        horizontalLayout_10->addWidget(LabelUnitFHeight);


        verticalLayout_3->addWidget(frame_3);

        frame_4 = new QFrame(frame_value);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_4);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        LabelFHeight_2 = new QLabel(frame_4);
        LabelFHeight_2->setObjectName(QStringLiteral("LabelFHeight_2"));
        LabelFHeight_2->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_9->addWidget(LabelFHeight_2);

        SpinFHeight_2 = new QDoubleSpinBox(frame_4);
        SpinFHeight_2->setObjectName(QStringLiteral("SpinFHeight_2"));
        SpinFHeight_2->setMaximumSize(QSize(58, 20));
        SpinFHeight_2->setAlignment(Qt::AlignCenter);
        SpinFHeight_2->setDecimals(1);

        horizontalLayout_9->addWidget(SpinFHeight_2);

        LabelUnitFHeight_2 = new QLabel(frame_4);
        LabelUnitFHeight_2->setObjectName(QStringLiteral("LabelUnitFHeight_2"));
        LabelUnitFHeight_2->setMaximumSize(QSize(30, 20));

        horizontalLayout_9->addWidget(LabelUnitFHeight_2);


        verticalLayout_3->addWidget(frame_4);

        frame_5 = new QFrame(frame_value);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_5);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        LabelFRadius = new QLabel(frame_5);
        LabelFRadius->setObjectName(QStringLiteral("LabelFRadius"));
        LabelFRadius->setMinimumSize(QSize(96, 0));
        LabelFRadius->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_8->addWidget(LabelFRadius);

        SpinFRadius = new QDoubleSpinBox(frame_5);
        SpinFRadius->setObjectName(QStringLiteral("SpinFRadius"));
        SpinFRadius->setMaximumSize(QSize(58, 20));
        SpinFRadius->setAlignment(Qt::AlignCenter);
        SpinFRadius->setDecimals(1);

        horizontalLayout_8->addWidget(SpinFRadius);

        LabelUnitFRadius = new QLabel(frame_5);
        LabelUnitFRadius->setObjectName(QStringLiteral("LabelUnitFRadius"));
        LabelUnitFRadius->setMaximumSize(QSize(30, 20));

        horizontalLayout_8->addWidget(LabelUnitFRadius);


        verticalLayout_3->addWidget(frame_5);

        frame_6 = new QFrame(frame_value);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        LabelFAngle = new QLabel(frame_6);
        LabelFAngle->setObjectName(QStringLiteral("LabelFAngle"));
        LabelFAngle->setMinimumSize(QSize(96, 0));
        LabelFAngle->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_7->addWidget(LabelFAngle);

        SpinFAngle = new QDoubleSpinBox(frame_6);
        SpinFAngle->setObjectName(QStringLiteral("SpinFAngle"));
        SpinFAngle->setMaximumSize(QSize(58, 20));
        SpinFAngle->setAlignment(Qt::AlignCenter);
        SpinFAngle->setDecimals(1);

        horizontalLayout_7->addWidget(SpinFAngle);

        LabelUnitFAngle = new QLabel(frame_6);
        LabelUnitFAngle->setObjectName(QStringLiteral("LabelUnitFAngle"));
        LabelUnitFAngle->setMaximumSize(QSize(30, 20));

        horizontalLayout_7->addWidget(LabelUnitFAngle);


        verticalLayout_3->addWidget(frame_6);

        frame_7 = new QFrame(frame_value);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        horizontalLayout_11 = new QHBoxLayout(frame_7);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        LabelFAngle_2 = new QLabel(frame_7);
        LabelFAngle_2->setObjectName(QStringLiteral("LabelFAngle_2"));
        LabelFAngle_2->setMinimumSize(QSize(96, 0));
        LabelFAngle_2->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_11->addWidget(LabelFAngle_2);

        SpinFAngle_2 = new QDoubleSpinBox(frame_7);
        SpinFAngle_2->setObjectName(QStringLiteral("SpinFAngle_2"));
        SpinFAngle_2->setMinimumSize(QSize(58, 20));
        SpinFAngle_2->setMaximumSize(QSize(58, 20));
        SpinFAngle_2->setAlignment(Qt::AlignCenter);
        SpinFAngle_2->setDecimals(1);
        SpinFAngle_2->setMaximum(180);

        horizontalLayout_11->addWidget(SpinFAngle_2);

        LabelUnitFAngle_2 = new QLabel(frame_7);
        LabelUnitFAngle_2->setObjectName(QStringLiteral("LabelUnitFAngle_2"));
        LabelUnitFAngle_2->setMaximumSize(QSize(30, 20));

        horizontalLayout_11->addWidget(LabelUnitFAngle_2);


        verticalLayout_3->addWidget(frame_7);


        verticalLayout->addWidget(frame_value);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 7);

        horizontalLayout_2->addWidget(WeldGroupShow);

        PartGroupShow = new QGroupBox(frame);
        PartGroupShow->setObjectName(QStringLiteral("PartGroupShow"));
        sizePolicy.setHeightForWidth(PartGroupShow->sizePolicy().hasHeightForWidth());
        PartGroupShow->setSizePolicy(sizePolicy);
        PartGroupShow->setMinimumSize(QSize(180, 0));
        PartGroupShow->setMaximumSize(QSize(185, 16777215));
        gridLayout_2 = new QGridLayout(PartGroupShow);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(-1, 6, -1, 0);
        BtnNccDefaultPath = new QPushButton(PartGroupShow);
        BtnNccDefaultPath->setObjectName(QStringLiteral("BtnNccDefaultPath"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(BtnNccDefaultPath->sizePolicy().hasHeightForWidth());
        BtnNccDefaultPath->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(BtnNccDefaultPath, 0, 0, 1, 1);

        BtnNccPath = new QPushButton(PartGroupShow);
        BtnNccPath->setObjectName(QStringLiteral("BtnNccPath"));
        sizePolicy1.setHeightForWidth(BtnNccPath->sizePolicy().hasHeightForWidth());
        BtnNccPath->setSizePolicy(sizePolicy1);
        BtnNccPath->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(BtnNccPath, 0, 1, 1, 1);

        LabelPartFileName = new QLabel(PartGroupShow);
        LabelPartFileName->setObjectName(QStringLiteral("LabelPartFileName"));
        LabelPartFileName->setMinimumSize(QSize(0, 18));
        LabelPartFileName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(LabelPartFileName, 1, 0, 1, 2);

        ListPartFile = new QListView(PartGroupShow);
        ListPartFile->setObjectName(QStringLiteral("ListPartFile"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ListPartFile->sizePolicy().hasHeightForWidth());
        ListPartFile->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(ListPartFile, 2, 0, 1, 2);

        gridLayout_2->setRowStretch(2, 10);

        horizontalLayout_2->addWidget(PartGroupShow);

        ExpoView = new QWeldShowWidget(frame);
        ExpoView->setObjectName(QStringLiteral("ExpoView"));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(226, 240, 153, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        ExpoView->setPalette(palette);
        ExpoView->setContextMenuPolicy(Qt::NoContextMenu);
        ExpoView->setAutoFillBackground(true);

        horizontalLayout_2->addWidget(ExpoView);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout_2->addWidget(frame);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(DialogDxfFileLoad);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_4->addWidget(buttonBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_4);


        retranslateUi(DialogDxfFileLoad);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDxfFileLoad, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDxfFileLoad, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogDxfFileLoad);
    } // setupUi

    void retranslateUi(QDialog *DialogDxfFileLoad)
    {
        DialogDxfFileLoad->setWindowTitle(QApplication::translate("DialogDxfFileLoad", "Weld", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogDxfFileLoad", "Weld", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "Load Part File", Q_NULLPTR)
        );
        label_zoom->setText(QApplication::translate("DialogDxfFileLoad", "Zoom:", Q_NULLPTR));
        LabelPartFilePath->setText(QString());
        WeldGroupShow->setTitle(QApplication::translate("DialogDxfFileLoad", "Weld Parameter", Q_NULLPTR));
        LabelType->setText(QApplication::translate("DialogDxfFileLoad", "Type:", Q_NULLPTR));
        ComWeldType->clear();
        ComWeldType->insertItems(0, QStringList()
         << QApplication::translate("DialogDxfFileLoad", "I shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "V shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "double_V shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "U shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "diff_V shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "J shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "VY shape", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "TKY shape", Q_NULLPTR)
        );
        LabelSymetry->setText(QApplication::translate("DialogDxfFileLoad", "Symmetry:", Q_NULLPTR));
        ComWeldSymetry->clear();
        ComWeldSymetry->insertItems(0, QStringList()
         << QApplication::translate("DialogDxfFileLoad", "Symmetry", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "Right", Q_NULLPTR)
         << QApplication::translate("DialogDxfFileLoad", "Left", Q_NULLPTR)
        );
        LabelWHeight->setText(QApplication::translate("DialogDxfFileLoad", "Weland Height:", Q_NULLPTR));
        LabelUnitWHeight->setText(QApplication::translate("DialogDxfFileLoad", "mm", Q_NULLPTR));
        LabelWOffset->setText(QApplication::translate("DialogDxfFileLoad", "Weland Offset:", Q_NULLPTR));
        LabelUnitWOffset->setText(QApplication::translate("DialogDxfFileLoad", "mm", Q_NULLPTR));
        LabelFHeight->setText(QApplication::translate("DialogDxfFileLoad", "Fizone Height:", Q_NULLPTR));
        LabelUnitFHeight->setText(QApplication::translate("DialogDxfFileLoad", "mm", Q_NULLPTR));
        LabelFHeight_2->setText(QApplication::translate("DialogDxfFileLoad", "Fiz_down Height:", Q_NULLPTR));
        LabelUnitFHeight_2->setText(QApplication::translate("DialogDxfFileLoad", "mm", Q_NULLPTR));
        LabelFRadius->setText(QApplication::translate("DialogDxfFileLoad", "Fizone Radius:", Q_NULLPTR));
        LabelUnitFRadius->setText(QApplication::translate("DialogDxfFileLoad", "mm", Q_NULLPTR));
        LabelFAngle->setText(QApplication::translate("DialogDxfFileLoad", "Fizone Angle:", Q_NULLPTR));
        LabelUnitFAngle->setText(QApplication::translate("DialogDxfFileLoad", "deg", Q_NULLPTR));
        LabelFAngle_2->setText(QApplication::translate("DialogDxfFileLoad", "Fiz_down Angle:", Q_NULLPTR));
        LabelUnitFAngle_2->setText(QApplication::translate("DialogDxfFileLoad", "deg", Q_NULLPTR));
        PartGroupShow->setTitle(QApplication::translate("DialogDxfFileLoad", "Part File", Q_NULLPTR));
        BtnNccDefaultPath->setText(QApplication::translate("DialogDxfFileLoad", "Default path", Q_NULLPTR));
        BtnNccPath->setText(QApplication::translate("DialogDxfFileLoad", "Path Setting", Q_NULLPTR));
        LabelPartFileName->setText(QApplication::translate("DialogDxfFileLoad", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogDxfFileLoad: public Ui_DialogDxfFileLoad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDXFFILELOAD_H
