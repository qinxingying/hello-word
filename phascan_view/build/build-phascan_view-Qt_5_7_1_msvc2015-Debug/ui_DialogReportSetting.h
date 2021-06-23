/********************************************************************************
** Form generated from reading UI file 'DialogReportSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREPORTSETTING_H
#define UI_DIALOGREPORTSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogReportSetting
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLineEdit *StrPartName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *StrPartNo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *StrPartPostion;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *StrReportName;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *logoLineEdit;
    QToolButton *logoToolButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QComboBox *ComModeSelection;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogReportSetting)
    {
        if (DialogReportSetting->objectName().isEmpty())
            DialogReportSetting->setObjectName(QStringLiteral("DialogReportSetting"));
        DialogReportSetting->resize(321, 257);
        QIcon icon;
        icon.addFile(QStringLiteral(":/file/resource/toolbar/0-06.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogReportSetting->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DialogReportSetting);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(DialogReportSetting);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        StrPartName = new QLineEdit(DialogReportSetting);
        StrPartName->setObjectName(QStringLiteral("StrPartName"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StrPartName->sizePolicy().hasHeightForWidth());
        StrPartName->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(StrPartName);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(DialogReportSetting);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        StrPartNo = new QLineEdit(DialogReportSetting);
        StrPartNo->setObjectName(QStringLiteral("StrPartNo"));

        horizontalLayout_2->addWidget(StrPartNo);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(DialogReportSetting);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        StrPartPostion = new QLineEdit(DialogReportSetting);
        StrPartPostion->setObjectName(QStringLiteral("StrPartPostion"));

        horizontalLayout_3->addWidget(StrPartPostion);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(DialogReportSetting);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        StrReportName = new QLineEdit(DialogReportSetting);
        StrReportName->setObjectName(QStringLiteral("StrReportName"));

        horizontalLayout_4->addWidget(StrReportName);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(DialogReportSetting);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        logoLineEdit = new QLineEdit(DialogReportSetting);
        logoLineEdit->setObjectName(QStringLiteral("logoLineEdit"));
        logoLineEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(logoLineEdit);

        logoToolButton = new QToolButton(DialogReportSetting);
        logoToolButton->setObjectName(QStringLiteral("logoToolButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logoToolButton->sizePolicy().hasHeightForWidth());
        logoToolButton->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(logoToolButton);

        horizontalLayout_5->setStretch(0, 10);
        horizontalLayout_5->setStretch(1, 14);
        horizontalLayout_5->setStretch(2, 6);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(DialogReportSetting);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        dateEdit = new QDateEdit(DialogReportSetting);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        horizontalLayout_6->addWidget(dateEdit);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_6);

        ComModeSelection = new QComboBox(DialogReportSetting);
        ComModeSelection->setObjectName(QStringLiteral("ComModeSelection"));

        verticalLayout->addWidget(ComModeSelection);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(DialogReportSetting);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_7->addWidget(pushButton_2);

        pushButton = new QPushButton(DialogReportSetting);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_7->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(DialogReportSetting);
        QObject::connect(pushButton_2, SIGNAL(clicked()), DialogReportSetting, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogReportSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogReportSetting)
    {
        DialogReportSetting->setWindowTitle(QApplication::translate("DialogReportSetting", "Report Setting", Q_NULLPTR));
        label_5->setText(QApplication::translate("DialogReportSetting", "Part Name:", Q_NULLPTR));
        label->setText(QApplication::translate("DialogReportSetting", "Part No.:", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogReportSetting", "Part Position", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogReportSetting", "Report Name:", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogReportSetting", "Logo", Q_NULLPTR));
        logoToolButton->setText(QApplication::translate("DialogReportSetting", "...", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogReportSetting", "Date & Time:", Q_NULLPTR));
        ComModeSelection->clear();
        ComModeSelection->insertItems(0, QStringList()
         << QApplication::translate("DialogReportSetting", "Without  Group Parameters", Q_NULLPTR)
         << QApplication::translate("DialogReportSetting", "With Group Parameters", Q_NULLPTR)
        );
        pushButton_2->setText(QApplication::translate("DialogReportSetting", "&Cancel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogReportSetting", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogReportSetting: public Ui_DialogReportSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREPORTSETTING_H
