/********************************************************************************
** Form generated from reading UI file 'dialogdefectselect.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDEFECTSELECT_H
#define UI_DIALOGDEFECTSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogDefectSelect
{
public:
    QLabel *LabelDefectSelect;
    QComboBox *ComboSelect;
    QPushButton *BtOk;
    QLabel *LabelNotice;

    void setupUi(QDialog *DialogDefectSelect)
    {
        if (DialogDefectSelect->objectName().isEmpty())
            DialogDefectSelect->setObjectName(QStringLiteral("DialogDefectSelect"));
        DialogDefectSelect->resize(526, 361);
        LabelDefectSelect = new QLabel(DialogDefectSelect);
        LabelDefectSelect->setObjectName(QStringLiteral("LabelDefectSelect"));
        LabelDefectSelect->setGeometry(QRect(10, 330, 91, 21));
        ComboSelect = new QComboBox(DialogDefectSelect);
        ComboSelect->setObjectName(QStringLiteral("ComboSelect"));
        ComboSelect->setGeometry(QRect(110, 330, 121, 22));
        BtOk = new QPushButton(DialogDefectSelect);
        BtOk->setObjectName(QStringLiteral("BtOk"));
        BtOk->setGeometry(QRect(389, 309, 111, 41));
        LabelNotice = new QLabel(DialogDefectSelect);
        LabelNotice->setObjectName(QStringLiteral("LabelNotice"));
        LabelNotice->setGeometry(QRect(10, 310, 371, 20));

        retranslateUi(DialogDefectSelect);

        QMetaObject::connectSlotsByName(DialogDefectSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogDefectSelect)
    {
        DialogDefectSelect->setWindowTitle(QApplication::translate("DialogDefectSelect", "Defect Select", Q_NULLPTR));
        LabelDefectSelect->setText(QApplication::translate("DialogDefectSelect", "Select Defect:", Q_NULLPTR));
        BtOk->setText(QApplication::translate("DialogDefectSelect", "OK", Q_NULLPTR));
        LabelNotice->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogDefectSelect: public Ui_DialogDefectSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDEFECTSELECT_H
