/********************************************************************************
** Form generated from reading UI file 'DialogWeldPartLoad.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWELDPARTLOAD_H
#define UI_DIALOGWELDPARTLOAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <ui/QWeldShowWidget.h>

QT_BEGIN_NAMESPACE

class Ui_DialogWeldPartLoad
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QGroupBox *WeldGroupShow;
    QComboBox *ComWeldType;
    QLabel *LabelType;
    QComboBox *ComWeldSymetry;
    QLabel *LabelSymetry;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *LabelWHeight;
    QLabel *LabelUnitWHeight;
    QLabel *LabelWOffset;
    QLabel *LabelUnitWOffset;
    QLabel *LabelFHeight;
    QLabel *LabelUnitFHeight;
    QLabel *LabelFRadius;
    QLabel *LabelUnitFRadius;
    QLabel *LabelFAngle;
    QLabel *LabelUnitFAngle;
    QDoubleSpinBox *SpinWHeight;
    QDoubleSpinBox *SpinWoffset;
    QDoubleSpinBox *SpinFHeight;
    QDoubleSpinBox *SpinFRadius;
    QDoubleSpinBox *SpinFAngle;
    QGroupBox *PartGroupShow;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *LabelPartFileName;
    QListView *ListPartFile;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *BtnNccDefaultPath;
    QPushButton *BtnNccPath;
    QWeldShowWidget *ExpoView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *LabelPartFilePath;

    void setupUi(QDialog *DialogWeldPartLoad)
    {
        if (DialogWeldPartLoad->objectName().isEmpty())
            DialogWeldPartLoad->setObjectName(QString::fromUtf8("DialogWeldPartLoad"));
        DialogWeldPartLoad->resize(610, 395);
        buttonBox = new QDialogButtonBox(DialogWeldPartLoad);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(230, 360, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(DialogWeldPartLoad);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 10, 191, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setLayoutDirection(Qt::LeftToRight);
        comboBox->setMaxVisibleItems(5);
        layoutWidget1 = new QWidget(DialogWeldPartLoad);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 40, 591, 311));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        WeldGroupShow = new QGroupBox(layoutWidget1);
        WeldGroupShow->setObjectName(QString::fromUtf8("WeldGroupShow"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(WeldGroupShow->sizePolicy().hasHeightForWidth());
        WeldGroupShow->setSizePolicy(sizePolicy1);
        WeldGroupShow->setMinimumSize(QSize(200, 0));
        ComWeldType = new QComboBox(WeldGroupShow);
        ComWeldType->setObjectName(QString::fromUtf8("ComWeldType"));
        ComWeldType->setGeometry(QRect(80, 40, 111, 22));
        LabelType = new QLabel(WeldGroupShow);
        LabelType->setObjectName(QString::fromUtf8("LabelType"));
        LabelType->setGeometry(QRect(10, 40, 51, 21));
        ComWeldSymetry = new QComboBox(WeldGroupShow);
        ComWeldSymetry->setObjectName(QString::fromUtf8("ComWeldSymetry"));
        ComWeldSymetry->setGeometry(QRect(80, 70, 111, 22));
        LabelSymetry = new QLabel(WeldGroupShow);
        LabelSymetry->setObjectName(QString::fromUtf8("LabelSymetry"));
        LabelSymetry->setGeometry(QRect(10, 70, 51, 21));
        layoutWidget2 = new QWidget(WeldGroupShow);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 110, 181, 151));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        LabelWHeight = new QLabel(layoutWidget2);
        LabelWHeight->setObjectName(QString::fromUtf8("LabelWHeight"));

        gridLayout->addWidget(LabelWHeight, 0, 0, 1, 2);

        LabelUnitWHeight = new QLabel(layoutWidget2);
        LabelUnitWHeight->setObjectName(QString::fromUtf8("LabelUnitWHeight"));

        gridLayout->addWidget(LabelUnitWHeight, 0, 3, 1, 1);

        LabelWOffset = new QLabel(layoutWidget2);
        LabelWOffset->setObjectName(QString::fromUtf8("LabelWOffset"));

        gridLayout->addWidget(LabelWOffset, 1, 0, 1, 2);

        LabelUnitWOffset = new QLabel(layoutWidget2);
        LabelUnitWOffset->setObjectName(QString::fromUtf8("LabelUnitWOffset"));

        gridLayout->addWidget(LabelUnitWOffset, 1, 3, 1, 1);

        LabelFHeight = new QLabel(layoutWidget2);
        LabelFHeight->setObjectName(QString::fromUtf8("LabelFHeight"));

        gridLayout->addWidget(LabelFHeight, 2, 0, 1, 2);

        LabelUnitFHeight = new QLabel(layoutWidget2);
        LabelUnitFHeight->setObjectName(QString::fromUtf8("LabelUnitFHeight"));

        gridLayout->addWidget(LabelUnitFHeight, 2, 3, 1, 1);

        LabelFRadius = new QLabel(layoutWidget2);
        LabelFRadius->setObjectName(QString::fromUtf8("LabelFRadius"));

        gridLayout->addWidget(LabelFRadius, 3, 0, 1, 2);

        LabelUnitFRadius = new QLabel(layoutWidget2);
        LabelUnitFRadius->setObjectName(QString::fromUtf8("LabelUnitFRadius"));

        gridLayout->addWidget(LabelUnitFRadius, 3, 3, 1, 1);

        LabelFAngle = new QLabel(layoutWidget2);
        LabelFAngle->setObjectName(QString::fromUtf8("LabelFAngle"));

        gridLayout->addWidget(LabelFAngle, 4, 0, 1, 2);

        LabelUnitFAngle = new QLabel(layoutWidget2);
        LabelUnitFAngle->setObjectName(QString::fromUtf8("LabelUnitFAngle"));

        gridLayout->addWidget(LabelUnitFAngle, 4, 3, 1, 1);

        SpinWHeight = new QDoubleSpinBox(layoutWidget2);
        SpinWHeight->setObjectName(QString::fromUtf8("SpinWHeight"));
        SpinWHeight->setDecimals(1);

        gridLayout->addWidget(SpinWHeight, 0, 2, 1, 1);

        SpinWoffset = new QDoubleSpinBox(layoutWidget2);
        SpinWoffset->setObjectName(QString::fromUtf8("SpinWoffset"));
        SpinWoffset->setDecimals(1);

        gridLayout->addWidget(SpinWoffset, 1, 2, 1, 1);

        SpinFHeight = new QDoubleSpinBox(layoutWidget2);
        SpinFHeight->setObjectName(QString::fromUtf8("SpinFHeight"));
        SpinFHeight->setDecimals(1);

        gridLayout->addWidget(SpinFHeight, 2, 2, 1, 1);

        SpinFRadius = new QDoubleSpinBox(layoutWidget2);
        SpinFRadius->setObjectName(QString::fromUtf8("SpinFRadius"));
        SpinFRadius->setDecimals(1);

        gridLayout->addWidget(SpinFRadius, 3, 2, 1, 1);

        SpinFAngle = new QDoubleSpinBox(layoutWidget2);
        SpinFAngle->setObjectName(QString::fromUtf8("SpinFAngle"));
        SpinFAngle->setDecimals(1);

        gridLayout->addWidget(SpinFAngle, 4, 2, 1, 1);


        horizontalLayout->addWidget(WeldGroupShow);

        PartGroupShow = new QGroupBox(layoutWidget1);
        PartGroupShow->setObjectName(QString::fromUtf8("PartGroupShow"));
        sizePolicy1.setHeightForWidth(PartGroupShow->sizePolicy().hasHeightForWidth());
        PartGroupShow->setSizePolicy(sizePolicy1);
        PartGroupShow->setMinimumSize(QSize(200, 0));
        verticalLayoutWidget = new QWidget(PartGroupShow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(3, 44, 191, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        LabelPartFileName = new QLabel(verticalLayoutWidget);
        LabelPartFileName->setObjectName(QString::fromUtf8("LabelPartFileName"));
        LabelPartFileName->setMinimumSize(QSize(0, 18));

        verticalLayout->addWidget(LabelPartFileName);

        ListPartFile = new QListView(verticalLayoutWidget);
        ListPartFile->setObjectName(QString::fromUtf8("ListPartFile"));

        verticalLayout->addWidget(ListPartFile);

        verticalLayout->setStretch(1, 20);
        horizontalLayoutWidget_2 = new QWidget(PartGroupShow);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(3, 13, 191, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        BtnNccDefaultPath = new QPushButton(horizontalLayoutWidget_2);
        BtnNccDefaultPath->setObjectName(QString::fromUtf8("BtnNccDefaultPath"));

        horizontalLayout_2->addWidget(BtnNccDefaultPath);

        BtnNccPath = new QPushButton(horizontalLayoutWidget_2);
        BtnNccPath->setObjectName(QString::fromUtf8("BtnNccPath"));
        BtnNccPath->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(BtnNccPath);


        horizontalLayout->addWidget(PartGroupShow);

        ExpoView = new QWeldShowWidget(layoutWidget1);
        ExpoView->setObjectName(QString::fromUtf8("ExpoView"));
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

        horizontalLayout->addWidget(ExpoView);

        horizontalLayoutWidget = new QWidget(DialogWeldPartLoad);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(216, 4, 381, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        LabelPartFilePath = new QLabel(horizontalLayoutWidget);
        LabelPartFilePath->setObjectName(QString::fromUtf8("LabelPartFilePath"));
        LabelPartFilePath->setMinimumSize(QSize(0, 18));

        horizontalLayout_4->addWidget(LabelPartFilePath);


        retranslateUi(DialogWeldPartLoad);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogWeldPartLoad, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogWeldPartLoad, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogWeldPartLoad);
    } // setupUi

    void retranslateUi(QDialog *DialogWeldPartLoad)
    {
        DialogWeldPartLoad->setWindowTitle(QApplication::translate("DialogWeldPartLoad", "Dialog", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldPartLoad", "Weld", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogWeldPartLoad", "Load Part File", 0, QApplication::UnicodeUTF8)
        );
        WeldGroupShow->setTitle(QApplication::translate("DialogWeldPartLoad", "Weld Parameter", 0, QApplication::UnicodeUTF8));
        ComWeldType->clear();
        ComWeldType->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldPartLoad", "I shape", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogWeldPartLoad", "V shape", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogWeldPartLoad", "double V shpe", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogWeldPartLoad", "U shape", 0, QApplication::UnicodeUTF8)
        );
        LabelType->setText(QApplication::translate("DialogWeldPartLoad", "Type:", 0, QApplication::UnicodeUTF8));
        ComWeldSymetry->clear();
        ComWeldSymetry->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldPartLoad", "Symmetry", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogWeldPartLoad", "Left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogWeldPartLoad", "Right", 0, QApplication::UnicodeUTF8)
        );
        LabelSymetry->setText(QApplication::translate("DialogWeldPartLoad", "Symmetry:", 0, QApplication::UnicodeUTF8));
        LabelWHeight->setText(QApplication::translate("DialogWeldPartLoad", "Weland Height:", 0, QApplication::UnicodeUTF8));
        LabelUnitWHeight->setText(QApplication::translate("DialogWeldPartLoad", "mm", 0, QApplication::UnicodeUTF8));
        LabelWOffset->setText(QApplication::translate("DialogWeldPartLoad", "Weland Offset:", 0, QApplication::UnicodeUTF8));
        LabelUnitWOffset->setText(QApplication::translate("DialogWeldPartLoad", "mm", 0, QApplication::UnicodeUTF8));
        LabelFHeight->setText(QApplication::translate("DialogWeldPartLoad", "Fizone Height:", 0, QApplication::UnicodeUTF8));
        LabelUnitFHeight->setText(QApplication::translate("DialogWeldPartLoad", "mm", 0, QApplication::UnicodeUTF8));
        LabelFRadius->setText(QApplication::translate("DialogWeldPartLoad", "Fizone Radius", 0, QApplication::UnicodeUTF8));
        LabelUnitFRadius->setText(QApplication::translate("DialogWeldPartLoad", "mm", 0, QApplication::UnicodeUTF8));
        LabelFAngle->setText(QApplication::translate("DialogWeldPartLoad", "Fizone Angle:", 0, QApplication::UnicodeUTF8));
        LabelUnitFAngle->setText(QApplication::translate("DialogWeldPartLoad", "deg", 0, QApplication::UnicodeUTF8));
        PartGroupShow->setTitle(QApplication::translate("DialogWeldPartLoad", "Part File", 0, QApplication::UnicodeUTF8));
        LabelPartFileName->setText(QApplication::translate("DialogWeldPartLoad", "TextLabel", 0, QApplication::UnicodeUTF8));
        BtnNccDefaultPath->setText(QApplication::translate("DialogWeldPartLoad", "Default path", 0, QApplication::UnicodeUTF8));
        BtnNccPath->setText(QApplication::translate("DialogWeldPartLoad", "Path Setting", 0, QApplication::UnicodeUTF8));
        LabelPartFilePath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogWeldPartLoad: public Ui_DialogWeldPartLoad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWELDPARTLOAD_H
