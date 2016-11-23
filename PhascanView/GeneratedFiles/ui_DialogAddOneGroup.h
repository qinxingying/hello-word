/********************************************************************************
** Form generated from reading UI file 'DialogAddOneGroup.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDONEGROUP_H
#define UI_DIALOGADDONEGROUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAddOneGroup
{
public:
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DialogAddOneGroup)
    {
        if (DialogAddOneGroup->objectName().isEmpty())
            DialogAddOneGroup->setObjectName(QString::fromUtf8("DialogAddOneGroup"));
        DialogAddOneGroup->resize(383, 159);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/Main/resource/Main/0-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogAddOneGroup->setWindowIcon(icon);
        label = new QLabel(DialogAddOneGroup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 151, 41));
        label_2 = new QLabel(DialogAddOneGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 50, 151, 41));
        comboBox = new QComboBox(DialogAddOneGroup);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(190, 60, 151, 22));
        pushButton = new QPushButton(DialogAddOneGroup);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 100, 101, 31));
        pushButton_2 = new QPushButton(DialogAddOneGroup);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 100, 101, 31));

        retranslateUi(DialogAddOneGroup);

        QMetaObject::connectSlotsByName(DialogAddOneGroup);
    } // setupUi

    void retranslateUi(QDialog *DialogAddOneGroup)
    {
        DialogAddOneGroup->setWindowTitle(QApplication::translate("DialogAddOneGroup", " Dialog : Add Group Configure", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogAddOneGroup", "Add One Group?", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogAddOneGroup", "Copy Configure of Group :", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogAddOneGroup", "Init Config", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogAddOneGroup", "Group 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogAddOneGroup", "Group 2", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("DialogAddOneGroup", "Ok", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("DialogAddOneGroup", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogAddOneGroup: public Ui_DialogAddOneGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDONEGROUP_H
