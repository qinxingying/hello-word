/********************************************************************************
** Form generated from reading UI file 'DialogAboutVersion.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGABOUTVERSION_H
#define UI_DIALOGABOUTVERSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogAboutVersion
{
public:
    QLabel *label;
    QLabel *label_Version;

    void setupUi(QDialog *DialogAboutVersion)
    {
        if (DialogAboutVersion->objectName().isEmpty())
            DialogAboutVersion->setObjectName(QStringLiteral("DialogAboutVersion"));
        DialogAboutVersion->resize(400, 300);
        label = new QLabel(DialogAboutVersion);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 60, 121, 20));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label_Version = new QLabel(DialogAboutVersion);
        label_Version->setObjectName(QStringLiteral("label_Version"));
        label_Version->setGeometry(QRect(230, 60, 140, 20));
        label_Version->setFont(font);

        retranslateUi(DialogAboutVersion);

        QMetaObject::connectSlotsByName(DialogAboutVersion);
    } // setupUi

    void retranslateUi(QDialog *DialogAboutVersion)
    {
        DialogAboutVersion->setWindowTitle(QApplication::translate("DialogAboutVersion", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DialogAboutVersion", "Version:", Q_NULLPTR));
        label_Version->setText(QApplication::translate("DialogAboutVersion", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogAboutVersion: public Ui_DialogAboutVersion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGABOUTVERSION_H
