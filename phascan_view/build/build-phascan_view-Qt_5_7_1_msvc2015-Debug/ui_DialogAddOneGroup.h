/********************************************************************************
** Form generated from reading UI file 'DialogAddOneGroup.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDONEGROUP_H
#define UI_DIALOGADDONEGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogAddOneGroup
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DialogAddOneGroup)
    {
        if (DialogAddOneGroup->objectName().isEmpty())
            DialogAddOneGroup->setObjectName(QStringLiteral("DialogAddOneGroup"));
        DialogAddOneGroup->resize(318, 119);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/Main/resource/Main/0-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogAddOneGroup->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(DialogAddOneGroup);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 6, -1, 6);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(9);
        label = new QLabel(DialogAddOneGroup);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 30));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 4);

        label_2 = new QLabel(DialogAddOneGroup);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        comboBox = new QComboBox(DialogAddOneGroup);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 2, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        pushButton = new QPushButton(DialogAddOneGroup);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 1, 1, 1);

        pushButton_2 = new QPushButton(DialogAddOneGroup);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DialogAddOneGroup);

        QMetaObject::connectSlotsByName(DialogAddOneGroup);
    } // setupUi

    void retranslateUi(QDialog *DialogAddOneGroup)
    {
        DialogAddOneGroup->setWindowTitle(QApplication::translate("DialogAddOneGroup", " Dialog : Add Group Configure", Q_NULLPTR));
        label->setText(QApplication::translate("DialogAddOneGroup", "Add One Group?", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogAddOneGroup", "Copy Configure of Group :", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogAddOneGroup", "Init Config", Q_NULLPTR)
         << QApplication::translate("DialogAddOneGroup", "Group 1", Q_NULLPTR)
         << QApplication::translate("DialogAddOneGroup", "Group 2", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("DialogAddOneGroup", "Ok", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("DialogAddOneGroup", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogAddOneGroup: public Ui_DialogAddOneGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDONEGROUP_H
