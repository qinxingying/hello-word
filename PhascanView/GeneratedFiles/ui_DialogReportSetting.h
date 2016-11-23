/********************************************************************************
** Form generated from reading UI file 'DialogReportSetting.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREPORTSETTING_H
#define UI_DIALOGREPORTSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogReportSetting
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLineEdit *StrPartName;
    QLabel *label;
    QLineEdit *StrPartNo;
    QLabel *label_2;
    QLineEdit *StrPartPostion;
    QLabel *label_6;
    QLineEdit *StrReportName;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QComboBox *ComModeSelection;

    void setupUi(QDialog *DialogReportSetting)
    {
        if (DialogReportSetting->objectName().isEmpty())
            DialogReportSetting->setObjectName(QString::fromUtf8("DialogReportSetting"));
        DialogReportSetting->resize(314, 225);
        pushButton = new QPushButton(DialogReportSetting);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 185, 131, 31));
        layoutWidget = new QWidget(DialogReportSetting);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 22, 291, 152));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        StrPartName = new QLineEdit(layoutWidget);
        StrPartName->setObjectName(QString::fromUtf8("StrPartName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, StrPartName);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        StrPartNo = new QLineEdit(layoutWidget);
        StrPartNo->setObjectName(QString::fromUtf8("StrPartNo"));

        formLayout->setWidget(1, QFormLayout::FieldRole, StrPartNo);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        StrPartPostion = new QLineEdit(layoutWidget);
        StrPartPostion->setObjectName(QString::fromUtf8("StrPartPostion"));

        formLayout->setWidget(2, QFormLayout::FieldRole, StrPartPostion);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        StrReportName = new QLineEdit(layoutWidget);
        StrReportName->setObjectName(QString::fromUtf8("StrReportName"));

        formLayout->setWidget(3, QFormLayout::FieldRole, StrReportName);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        dateEdit = new QDateEdit(layoutWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, dateEdit);

        ComModeSelection = new QComboBox(layoutWidget);
        ComModeSelection->setObjectName(QString::fromUtf8("ComModeSelection"));

        formLayout->setWidget(5, QFormLayout::SpanningRole, ComModeSelection);


        retranslateUi(DialogReportSetting);

        QMetaObject::connectSlotsByName(DialogReportSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogReportSetting)
    {
        DialogReportSetting->setWindowTitle(QApplication::translate("DialogReportSetting", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DialogReportSetting", "OK", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DialogReportSetting", "Part Name:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogReportSetting", "Part No.:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogReportSetting", "Part Position", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DialogReportSetting", "Report Name:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DialogReportSetting", "Date & Time:", 0, QApplication::UnicodeUTF8));
        ComModeSelection->clear();
        ComModeSelection->insertItems(0, QStringList()
         << QApplication::translate("DialogReportSetting", "Without  Group Parameters", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogReportSetting", "With Group Parameters", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class DialogReportSetting: public Ui_DialogReportSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREPORTSETTING_H
