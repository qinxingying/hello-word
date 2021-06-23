/********************************************************************************
** Form generated from reading UI file 'dialogmethodselect.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMETHODSELECT_H
#define UI_DIALOGMETHODSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogMethodSelect
{
public:
    QPushButton *BtOK;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *RBtHalfWave;
    QRadioButton *RBtAbsoluteSensitivity;

    void setupUi(QDialog *DialogMethodSelect)
    {
        if (DialogMethodSelect->objectName().isEmpty())
            DialogMethodSelect->setObjectName(QStringLiteral("DialogMethodSelect"));
        DialogMethodSelect->resize(318, 166);
        BtOK = new QPushButton(DialogMethodSelect);
        BtOK->setObjectName(QStringLiteral("BtOK"));
        BtOK->setGeometry(QRect(210, 110, 80, 31));
        widget = new QWidget(DialogMethodSelect);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 221, 61));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        RBtHalfWave = new QRadioButton(widget);
        RBtHalfWave->setObjectName(QStringLiteral("RBtHalfWave"));

        verticalLayout->addWidget(RBtHalfWave);

        RBtAbsoluteSensitivity = new QRadioButton(widget);
        RBtAbsoluteSensitivity->setObjectName(QStringLiteral("RBtAbsoluteSensitivity"));

        verticalLayout->addWidget(RBtAbsoluteSensitivity);


        retranslateUi(DialogMethodSelect);

        QMetaObject::connectSlotsByName(DialogMethodSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogMethodSelect)
    {
        DialogMethodSelect->setWindowTitle(QApplication::translate("DialogMethodSelect", "Method Select", Q_NULLPTR));
        BtOK->setText(QApplication::translate("DialogMethodSelect", "OK", Q_NULLPTR));
        RBtHalfWave->setText(QApplication::translate("DialogMethodSelect", "Half Wave Height Method", Q_NULLPTR));
        RBtAbsoluteSensitivity->setText(QApplication::translate("DialogMethodSelect", "Absolute Sensitivity Method", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogMethodSelect: public Ui_DialogMethodSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMETHODSELECT_H
