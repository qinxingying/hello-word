/********************************************************************************
** Form generated from reading UI file 'dialogdefectmethodselect.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDEFECTMETHODSELECT_H
#define UI_DIALOGDEFECTMETHODSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogDefectMethodSelect
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *halfWaveRadioL;
    QRadioButton *endHalfWaveRadioL;
    QRadioButton *sensitivityRadioL;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *halfWaveRadioH;
    QRadioButton *endHalfWaveRadioH;
    QRadioButton *sensitivityRadioH;
    QRadioButton *tipDiffractionH;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QDoubleSpinBox *scaleDoubleSpinBox;
    QCheckBox *autoMerge;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogDefectMethodSelect)
    {
        if (DialogDefectMethodSelect->objectName().isEmpty())
            DialogDefectMethodSelect->setObjectName(QStringLiteral("DialogDefectMethodSelect"));
        DialogDefectMethodSelect->resize(617, 190);
        verticalLayout_3 = new QVBoxLayout(DialogDefectMethodSelect);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(DialogDefectMethodSelect);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        halfWaveRadioL = new QRadioButton(groupBox);
        halfWaveRadioL->setObjectName(QStringLiteral("halfWaveRadioL"));

        verticalLayout->addWidget(halfWaveRadioL);

        endHalfWaveRadioL = new QRadioButton(groupBox);
        endHalfWaveRadioL->setObjectName(QStringLiteral("endHalfWaveRadioL"));

        verticalLayout->addWidget(endHalfWaveRadioL);

        sensitivityRadioL = new QRadioButton(groupBox);
        sensitivityRadioL->setObjectName(QStringLiteral("sensitivityRadioL"));

        verticalLayout->addWidget(sensitivityRadioL);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DialogDefectMethodSelect);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        halfWaveRadioH = new QRadioButton(groupBox_2);
        halfWaveRadioH->setObjectName(QStringLiteral("halfWaveRadioH"));

        verticalLayout_2->addWidget(halfWaveRadioH);

        endHalfWaveRadioH = new QRadioButton(groupBox_2);
        endHalfWaveRadioH->setObjectName(QStringLiteral("endHalfWaveRadioH"));

        verticalLayout_2->addWidget(endHalfWaveRadioH);

        sensitivityRadioH = new QRadioButton(groupBox_2);
        sensitivityRadioH->setObjectName(QStringLiteral("sensitivityRadioH"));

        verticalLayout_2->addWidget(sensitivityRadioH);

        tipDiffractionH = new QRadioButton(groupBox_2);
        tipDiffractionH->setObjectName(QStringLiteral("tipDiffractionH"));

        verticalLayout_2->addWidget(tipDiffractionH);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(DialogDefectMethodSelect);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        scaleDoubleSpinBox = new QDoubleSpinBox(DialogDefectMethodSelect);
        scaleDoubleSpinBox->setObjectName(QStringLiteral("scaleDoubleSpinBox"));
        scaleDoubleSpinBox->setValue(50);

        horizontalLayout_4->addWidget(scaleDoubleSpinBox);


        horizontalLayout_2->addLayout(horizontalLayout_4);

        autoMerge = new QCheckBox(DialogDefectMethodSelect);
        autoMerge->setObjectName(QStringLiteral("autoMerge"));
        autoMerge->setChecked(true);

        horizontalLayout_2->addWidget(autoMerge);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(DialogDefectMethodSelect);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(true);
        pushButton->setMinimumSize(QSize(0, 31));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(DialogDefectMethodSelect);

        QMetaObject::connectSlotsByName(DialogDefectMethodSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogDefectMethodSelect)
    {
        DialogDefectMethodSelect->setWindowTitle(QApplication::translate("DialogDefectMethodSelect", "Defect Method Select", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogDefectMethodSelect", "Length measuring methods", Q_NULLPTR));
        halfWaveRadioL->setText(QApplication::translate("DialogDefectMethodSelect", "Half Wave Height Method", Q_NULLPTR));
        endHalfWaveRadioL->setText(QApplication::translate("DialogDefectMethodSelect", "End point Half Wave Height Method", Q_NULLPTR));
        sensitivityRadioL->setText(QApplication::translate("DialogDefectMethodSelect", "Absolute Sensitivity Method", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DialogDefectMethodSelect", "Height measuring methods", Q_NULLPTR));
        halfWaveRadioH->setText(QApplication::translate("DialogDefectMethodSelect", "Half Wave Height Method", Q_NULLPTR));
        endHalfWaveRadioH->setText(QApplication::translate("DialogDefectMethodSelect", "End point Half Wave Height Method", Q_NULLPTR));
        sensitivityRadioH->setText(QApplication::translate("DialogDefectMethodSelect", "Absolute Sensitivity Method", Q_NULLPTR));
        tipDiffractionH->setText(QApplication::translate("DialogDefectMethodSelect", "TipDiffraction Method", Q_NULLPTR));
        label->setText(QApplication::translate("DialogDefectMethodSelect", "Scale: ", Q_NULLPTR));
        autoMerge->setText(QApplication::translate("DialogDefectMethodSelect", "AutoMerge", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogDefectMethodSelect", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogDefectMethodSelect: public Ui_DialogDefectMethodSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDEFECTMETHODSELECT_H
