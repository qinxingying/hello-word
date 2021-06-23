/********************************************************************************
** Form generated from reading UI file 'DialogColorSelect.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCOLORSELECT_H
#define UI_DIALOGCOLORSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogColorSelect
{
public:
    QListWidget *ListName;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DialogColorSelect)
    {
        if (DialogColorSelect->objectName().isEmpty())
            DialogColorSelect->setObjectName(QStringLiteral("DialogColorSelect"));
        DialogColorSelect->resize(400, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogColorSelect->sizePolicy().hasHeightForWidth());
        DialogColorSelect->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/file/resource/Main/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogColorSelect->setWindowIcon(icon);
        ListName = new QListWidget(DialogColorSelect);
        ListName->setObjectName(QStringLiteral("ListName"));
        ListName->setGeometry(QRect(10, 10, 281, 341));
        pushButton = new QPushButton(DialogColorSelect);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(36, 360, 161, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton_2 = new QPushButton(DialogColorSelect);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(210, 360, 161, 31));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        retranslateUi(DialogColorSelect);

        QMetaObject::connectSlotsByName(DialogColorSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogColorSelect)
    {
        DialogColorSelect->setWindowTitle(QApplication::translate("DialogColorSelect", "Pallette", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogColorSelect", "Select", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("DialogColorSelect", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogColorSelect: public Ui_DialogColorSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCOLORSELECT_H
