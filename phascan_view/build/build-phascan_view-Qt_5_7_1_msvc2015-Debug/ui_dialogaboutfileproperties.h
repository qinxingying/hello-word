/********************************************************************************
** Form generated from reading UI file 'dialogaboutfileproperties.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGABOUTFILEPROPERTIES_H
#define UI_DIALOGABOUTFILEPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogAboutFileProperties
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *labelFpgaCpuVersion;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *labelFpgaPaVersion;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *labelPhascanVersion;

    void setupUi(QDialog *DialogAboutFileProperties)
    {
        if (DialogAboutFileProperties->objectName().isEmpty())
            DialogAboutFileProperties->setObjectName(QStringLiteral("DialogAboutFileProperties"));
        DialogAboutFileProperties->resize(242, 146);
        verticalLayout = new QVBoxLayout(DialogAboutFileProperties);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(DialogAboutFileProperties);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        labelFpgaCpuVersion = new QLabel(DialogAboutFileProperties);
        labelFpgaCpuVersion->setObjectName(QStringLiteral("labelFpgaCpuVersion"));

        horizontalLayout->addWidget(labelFpgaCpuVersion);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(DialogAboutFileProperties);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        labelFpgaPaVersion = new QLabel(DialogAboutFileProperties);
        labelFpgaPaVersion->setObjectName(QStringLiteral("labelFpgaPaVersion"));

        horizontalLayout_2->addWidget(labelFpgaPaVersion);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(DialogAboutFileProperties);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        labelPhascanVersion = new QLabel(DialogAboutFileProperties);
        labelPhascanVersion->setObjectName(QStringLiteral("labelPhascanVersion"));

        horizontalLayout_3->addWidget(labelPhascanVersion);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DialogAboutFileProperties);

        QMetaObject::connectSlotsByName(DialogAboutFileProperties);
    } // setupUi

    void retranslateUi(QDialog *DialogAboutFileProperties)
    {
        DialogAboutFileProperties->setWindowTitle(QApplication::translate("DialogAboutFileProperties", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DialogAboutFileProperties", "FpgaCpuVersion :", Q_NULLPTR));
        labelFpgaCpuVersion->setText(QString());
        label_3->setText(QApplication::translate("DialogAboutFileProperties", "FpgaPaVersion  :", Q_NULLPTR));
        labelFpgaPaVersion->setText(QString());
        label_5->setText(QApplication::translate("DialogAboutFileProperties", "PhascanVersion :", Q_NULLPTR));
        labelPhascanVersion->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogAboutFileProperties: public Ui_DialogAboutFileProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGABOUTFILEPROPERTIES_H
