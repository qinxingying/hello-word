/********************************************************************************
** Form generated from reading UI file 'dialogkeyboardhelp.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGKEYBOARDHELP_H
#define UI_DIALOGKEYBOARDHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogKeyboardHelp
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *labelLogo;
    QLabel *labelKeyboard;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelWimage;
    QLabel *labelWtext;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelSimage;
    QLabel *labelStext;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelAimage;
    QLabel *labelAtext;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelDimage;
    QLabel *labelDtext;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelZimage;
    QLabel *labelZtext;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelCimage;
    QLabel *labelCtext;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *label0image;
    QLabel *label0text;
    QLabel *labelUpimage;
    QLabel *labelUptext;
    QLabel *labelLeftimage;
    QLabel *labelLefttext;
    QLabel *labelShift;
    QLabel *label_2;
    QLabel *labelShiftimage;
    QLabel *labelShifttext;

    void setupUi(QDialog *DialogKeyboardHelp)
    {
        if (DialogKeyboardHelp->objectName().isEmpty())
            DialogKeyboardHelp->setObjectName(QStringLiteral("DialogKeyboardHelp"));
        DialogKeyboardHelp->resize(507, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/file/resource/Main/keyboardLogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogKeyboardHelp->setWindowIcon(icon);
#ifndef QT_NO_WHATSTHIS
        DialogKeyboardHelp->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS
        verticalLayout_3 = new QVBoxLayout(DialogKeyboardHelp);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelLogo = new QLabel(DialogKeyboardHelp);
        labelLogo->setObjectName(QStringLiteral("labelLogo"));

        verticalLayout_3->addWidget(labelLogo);

        labelKeyboard = new QLabel(DialogKeyboardHelp);
        labelKeyboard->setObjectName(QStringLiteral("labelKeyboard"));

        verticalLayout_3->addWidget(labelKeyboard);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelWimage = new QLabel(DialogKeyboardHelp);
        labelWimage->setObjectName(QStringLiteral("labelWimage"));

        horizontalLayout->addWidget(labelWimage);

        labelWtext = new QLabel(DialogKeyboardHelp);
        labelWtext->setObjectName(QStringLiteral("labelWtext"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelWtext->setFont(font);

        horizontalLayout->addWidget(labelWtext);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelSimage = new QLabel(DialogKeyboardHelp);
        labelSimage->setObjectName(QStringLiteral("labelSimage"));

        horizontalLayout_2->addWidget(labelSimage);

        labelStext = new QLabel(DialogKeyboardHelp);
        labelStext->setObjectName(QStringLiteral("labelStext"));
        labelStext->setFont(font);

        horizontalLayout_2->addWidget(labelStext);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelAimage = new QLabel(DialogKeyboardHelp);
        labelAimage->setObjectName(QStringLiteral("labelAimage"));

        horizontalLayout_3->addWidget(labelAimage);

        labelAtext = new QLabel(DialogKeyboardHelp);
        labelAtext->setObjectName(QStringLiteral("labelAtext"));
        labelAtext->setFont(font);

        horizontalLayout_3->addWidget(labelAtext);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelDimage = new QLabel(DialogKeyboardHelp);
        labelDimage->setObjectName(QStringLiteral("labelDimage"));

        horizontalLayout_4->addWidget(labelDimage);

        labelDtext = new QLabel(DialogKeyboardHelp);
        labelDtext->setObjectName(QStringLiteral("labelDtext"));
        labelDtext->setFont(font);

        horizontalLayout_4->addWidget(labelDtext);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelZimage = new QLabel(DialogKeyboardHelp);
        labelZimage->setObjectName(QStringLiteral("labelZimage"));

        horizontalLayout_5->addWidget(labelZimage);

        labelZtext = new QLabel(DialogKeyboardHelp);
        labelZtext->setObjectName(QStringLiteral("labelZtext"));
        labelZtext->setFont(font);

        horizontalLayout_5->addWidget(labelZtext);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelCimage = new QLabel(DialogKeyboardHelp);
        labelCimage->setObjectName(QStringLiteral("labelCimage"));

        horizontalLayout_6->addWidget(labelCimage);

        labelCtext = new QLabel(DialogKeyboardHelp);
        labelCtext->setObjectName(QStringLiteral("labelCtext"));
        labelCtext->setFont(font);

        horizontalLayout_6->addWidget(labelCtext);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_7->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label0image = new QLabel(DialogKeyboardHelp);
        label0image->setObjectName(QStringLiteral("label0image"));

        gridLayout->addWidget(label0image, 0, 2, 1, 1);

        label0text = new QLabel(DialogKeyboardHelp);
        label0text->setObjectName(QStringLiteral("label0text"));
        label0text->setFont(font);

        gridLayout->addWidget(label0text, 0, 3, 1, 1);

        labelUpimage = new QLabel(DialogKeyboardHelp);
        labelUpimage->setObjectName(QStringLiteral("labelUpimage"));

        gridLayout->addWidget(labelUpimage, 1, 2, 1, 1);

        labelUptext = new QLabel(DialogKeyboardHelp);
        labelUptext->setObjectName(QStringLiteral("labelUptext"));
        labelUptext->setFont(font);

        gridLayout->addWidget(labelUptext, 1, 3, 1, 1);

        labelLeftimage = new QLabel(DialogKeyboardHelp);
        labelLeftimage->setObjectName(QStringLiteral("labelLeftimage"));

        gridLayout->addWidget(labelLeftimage, 2, 2, 1, 1);

        labelLefttext = new QLabel(DialogKeyboardHelp);
        labelLefttext->setObjectName(QStringLiteral("labelLefttext"));
        labelLefttext->setFont(font);

        gridLayout->addWidget(labelLefttext, 2, 3, 1, 1);

        labelShift = new QLabel(DialogKeyboardHelp);
        labelShift->setObjectName(QStringLiteral("labelShift"));

        gridLayout->addWidget(labelShift, 3, 0, 1, 1);

        label_2 = new QLabel(DialogKeyboardHelp);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 1, 1, 1);

        labelShiftimage = new QLabel(DialogKeyboardHelp);
        labelShiftimage->setObjectName(QStringLiteral("labelShiftimage"));

        gridLayout->addWidget(labelShiftimage, 3, 2, 1, 1);

        labelShifttext = new QLabel(DialogKeyboardHelp);
        labelShifttext->setObjectName(QStringLiteral("labelShifttext"));
        labelShifttext->setFont(font);

        gridLayout->addWidget(labelShifttext, 3, 3, 1, 1);


        horizontalLayout_7->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout_7);


        retranslateUi(DialogKeyboardHelp);

        QMetaObject::connectSlotsByName(DialogKeyboardHelp);
    } // setupUi

    void retranslateUi(QDialog *DialogKeyboardHelp)
    {
        DialogKeyboardHelp->setWindowTitle(QApplication::translate("DialogKeyboardHelp", "Keyboard Instruction", Q_NULLPTR));
        labelLogo->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelKeyboard->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelWimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelWtext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelSimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelStext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelAimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelAtext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelDimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelDtext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelZimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelZtext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelCimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelCtext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        label0image->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        label0text->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelUpimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelUptext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelLeftimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelLefttext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelShift->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogKeyboardHelp", "+", Q_NULLPTR));
        labelShiftimage->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
        labelShifttext->setText(QApplication::translate("DialogKeyboardHelp", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogKeyboardHelp: public Ui_DialogKeyboardHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGKEYBOARDHELP_H
