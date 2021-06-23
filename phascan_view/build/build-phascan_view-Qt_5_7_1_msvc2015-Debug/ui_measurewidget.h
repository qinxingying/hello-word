/********************************************************************************
** Form generated from reading UI file 'measurewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASUREWIDGET_H
#define UI_MEASUREWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeasureWidget
{
public:
    QVBoxLayout *verticalLayout;
    QListView *measureListView;
    QHBoxLayout *horizontalLayout;
    QPushButton *itemAddBt;
    QPushButton *itemDelBt;
    QPushButton *measurePatternBt;

    void setupUi(QWidget *MeasureWidget)
    {
        if (MeasureWidget->objectName().isEmpty())
            MeasureWidget->setObjectName(QStringLiteral("MeasureWidget"));
        MeasureWidget->resize(211, 523);
        verticalLayout = new QVBoxLayout(MeasureWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        measureListView = new QListView(MeasureWidget);
        measureListView->setObjectName(QStringLiteral("measureListView"));

        verticalLayout->addWidget(measureListView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        itemAddBt = new QPushButton(MeasureWidget);
        itemAddBt->setObjectName(QStringLiteral("itemAddBt"));

        horizontalLayout->addWidget(itemAddBt);

        itemDelBt = new QPushButton(MeasureWidget);
        itemDelBt->setObjectName(QStringLiteral("itemDelBt"));

        horizontalLayout->addWidget(itemDelBt);


        verticalLayout->addLayout(horizontalLayout);

        measurePatternBt = new QPushButton(MeasureWidget);
        measurePatternBt->setObjectName(QStringLiteral("measurePatternBt"));

        verticalLayout->addWidget(measurePatternBt);


        retranslateUi(MeasureWidget);

        QMetaObject::connectSlotsByName(MeasureWidget);
    } // setupUi

    void retranslateUi(QWidget *MeasureWidget)
    {
        MeasureWidget->setWindowTitle(QApplication::translate("MeasureWidget", "Form", Q_NULLPTR));
        itemAddBt->setText(QApplication::translate("MeasureWidget", "+", Q_NULLPTR));
        itemDelBt->setText(QApplication::translate("MeasureWidget", "-", Q_NULLPTR));
        measurePatternBt->setText(QApplication::translate("MeasureWidget", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MeasureWidget: public Ui_MeasureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREWIDGET_H
