/********************************************************************************
** Form generated from reading UI file 'DialogRegister.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREGISTER_H
#define UI_DIALOGREGISTER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogRegister
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditSN1;
    QPushButton *RegBtn;

    void setupUi(QDialog *DialogRegister)
    {
        if (DialogRegister->objectName().isEmpty())
            DialogRegister->setObjectName(QString::fromUtf8("DialogRegister"));
        DialogRegister->resize(398, 82);
        horizontalLayoutWidget = new QWidget(DialogRegister);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 11, 381, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEditSN1 = new QLineEdit(horizontalLayoutWidget);
        lineEditSN1->setObjectName(QString::fromUtf8("lineEditSN1"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        lineEditSN1->setFont(font);
        lineEditSN1->setInputMethodHints(Qt::ImhUppercaseOnly);
        lineEditSN1->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEditSN1);

        RegBtn = new QPushButton(DialogRegister);
        RegBtn->setObjectName(QString::fromUtf8("RegBtn"));
        RegBtn->setGeometry(QRect(139, 43, 121, 31));

        retranslateUi(DialogRegister);

        QMetaObject::connectSlotsByName(DialogRegister);
    } // setupUi

    void retranslateUi(QDialog *DialogRegister)
    {
        DialogRegister->setWindowTitle(QApplication::translate("DialogRegister", "Dialog", 0, QApplication::UnicodeUTF8));
        RegBtn->setText(QApplication::translate("DialogRegister", "Register", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogRegister: public Ui_DialogRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREGISTER_H
