/********************************************************************************
** Form generated from reading UI file 'dialogweldfixdataii.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWELDFIXDATAII_H
#define UI_DIALOGWELDFIXDATAII_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <painter/weldshowdataiiwidget.h>

QT_BEGIN_NAMESPACE

class Ui_DialogWeldFixDataII
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *weldFormComboBox;
    QLabel *zoomLabel;
    QDoubleSpinBox *zoomDoubleSpinBox;
    QLabel *pathLabel;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *weldImageLabel;
    QGroupBox *weldParameterGroupBox;
    QGridLayout *gridLayout;
    QLabel *r1Label;
    QLabel *r2Label;
    QLabel *w1UnitLabel;
    QLabel *h2Label;
    QDoubleSpinBox *h2DoubleSpinBox;
    QDoubleSpinBox *r1DoubleSpinBox;
    QLabel *w2UnitLabel;
    QLabel *h2UnitLabel;
    QLabel *h1Label;
    QLabel *w1Label;
    QLabel *w2Label;
    QDoubleSpinBox *w3DoubleSpinBox;
    QLabel *r2UnitLabel;
    QDoubleSpinBox *w1DoubleSpinBox;
    QComboBox *weldTypeComboBox;
    QLabel *w3UnitLabel;
    QDoubleSpinBox *h1DoubleSpinBox;
    QLabel *weldTypeLabel;
    QDoubleSpinBox *r2DoubleSpinBox;
    QLabel *h1UnitLabel;
    QDoubleSpinBox *w2DoubleSpinBox;
    QLabel *r1UnitLabel;
    QLabel *w3Label;
    QLabel *symmetryLabel;
    QComboBox *symmetryComboBox;
    QLabel *probePosLabel;
    QComboBox *ProbePosComboBox;
    QLabel *HAZLabel;
    QDoubleSpinBox *HAZDoubleSpinBox;
    QLabel *HAZUnitLabel;
    QSpacerItem *verticalSpacer;
    QGroupBox *partFileGroupBox;
    QGridLayout *gridLayout_2;
    QPushButton *nccDefaultPathBt;
    QPushButton *nccPathBt;
    QLabel *partFileNameLabel;
    QListView *partFileListView;
    QVBoxLayout *verticalLayout_2;
    WeldShowDataIIWidget *showWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogWeldFixDataII)
    {
        if (DialogWeldFixDataII->objectName().isEmpty())
            DialogWeldFixDataII->setObjectName(QStringLiteral("DialogWeldFixDataII"));
        DialogWeldFixDataII->resize(750, 500);
        DialogWeldFixDataII->setMinimumSize(QSize(750, 500));
        DialogWeldFixDataII->setMaximumSize(QSize(750, 500));
        QIcon icon;
        icon.addFile(QStringLiteral(":/file/resource/main_menu/0-05.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogWeldFixDataII->setWindowIcon(icon);
        verticalLayout_3 = new QVBoxLayout(DialogWeldFixDataII);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        weldFormComboBox = new QComboBox(DialogWeldFixDataII);
        weldFormComboBox->setObjectName(QStringLiteral("weldFormComboBox"));

        horizontalLayout->addWidget(weldFormComboBox);

        zoomLabel = new QLabel(DialogWeldFixDataII);
        zoomLabel->setObjectName(QStringLiteral("zoomLabel"));
        zoomLabel->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(zoomLabel);

        zoomDoubleSpinBox = new QDoubleSpinBox(DialogWeldFixDataII);
        zoomDoubleSpinBox->setObjectName(QStringLiteral("zoomDoubleSpinBox"));
        zoomDoubleSpinBox->setMinimum(0.01);
        zoomDoubleSpinBox->setValue(1);

        horizontalLayout->addWidget(zoomDoubleSpinBox);

        pathLabel = new QLabel(DialogWeldFixDataII);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));

        horizontalLayout->addWidget(pathLabel);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        weldImageLabel = new QLabel(DialogWeldFixDataII);
        weldImageLabel->setObjectName(QStringLiteral("weldImageLabel"));

        verticalLayout->addWidget(weldImageLabel);

        weldParameterGroupBox = new QGroupBox(DialogWeldFixDataII);
        weldParameterGroupBox->setObjectName(QStringLiteral("weldParameterGroupBox"));
        gridLayout = new QGridLayout(weldParameterGroupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        r1Label = new QLabel(weldParameterGroupBox);
        r1Label->setObjectName(QStringLiteral("r1Label"));

        gridLayout->addWidget(r1Label, 6, 0, 1, 1);

        r2Label = new QLabel(weldParameterGroupBox);
        r2Label->setObjectName(QStringLiteral("r2Label"));

        gridLayout->addWidget(r2Label, 9, 0, 1, 1);

        w1UnitLabel = new QLabel(weldParameterGroupBox);
        w1UnitLabel->setObjectName(QStringLiteral("w1UnitLabel"));

        gridLayout->addWidget(w1UnitLabel, 4, 2, 1, 1);

        h2Label = new QLabel(weldParameterGroupBox);
        h2Label->setObjectName(QStringLiteral("h2Label"));

        gridLayout->addWidget(h2Label, 8, 0, 1, 1);

        h2DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        h2DoubleSpinBox->setObjectName(QStringLiteral("h2DoubleSpinBox"));
        h2DoubleSpinBox->setKeyboardTracking(false);
        h2DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(h2DoubleSpinBox, 8, 1, 1, 1);

        r1DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        r1DoubleSpinBox->setObjectName(QStringLiteral("r1DoubleSpinBox"));
        r1DoubleSpinBox->setKeyboardTracking(false);
        r1DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(r1DoubleSpinBox, 6, 1, 1, 1);

        w2UnitLabel = new QLabel(weldParameterGroupBox);
        w2UnitLabel->setObjectName(QStringLiteral("w2UnitLabel"));

        gridLayout->addWidget(w2UnitLabel, 7, 2, 1, 1);

        h2UnitLabel = new QLabel(weldParameterGroupBox);
        h2UnitLabel->setObjectName(QStringLiteral("h2UnitLabel"));

        gridLayout->addWidget(h2UnitLabel, 8, 2, 1, 1);

        h1Label = new QLabel(weldParameterGroupBox);
        h1Label->setObjectName(QStringLiteral("h1Label"));

        gridLayout->addWidget(h1Label, 5, 0, 1, 1);

        w1Label = new QLabel(weldParameterGroupBox);
        w1Label->setObjectName(QStringLiteral("w1Label"));

        gridLayout->addWidget(w1Label, 4, 0, 1, 1);

        w2Label = new QLabel(weldParameterGroupBox);
        w2Label->setObjectName(QStringLiteral("w2Label"));

        gridLayout->addWidget(w2Label, 7, 0, 1, 1);

        w3DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        w3DoubleSpinBox->setObjectName(QStringLiteral("w3DoubleSpinBox"));
        w3DoubleSpinBox->setKeyboardTracking(false);
        w3DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(w3DoubleSpinBox, 10, 1, 1, 1);

        r2UnitLabel = new QLabel(weldParameterGroupBox);
        r2UnitLabel->setObjectName(QStringLiteral("r2UnitLabel"));

        gridLayout->addWidget(r2UnitLabel, 9, 2, 1, 1);

        w1DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        w1DoubleSpinBox->setObjectName(QStringLiteral("w1DoubleSpinBox"));
        w1DoubleSpinBox->setKeyboardTracking(false);
        w1DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(w1DoubleSpinBox, 4, 1, 1, 1);

        weldTypeComboBox = new QComboBox(weldParameterGroupBox);
        weldTypeComboBox->setObjectName(QStringLiteral("weldTypeComboBox"));

        gridLayout->addWidget(weldTypeComboBox, 0, 1, 1, 2);

        w3UnitLabel = new QLabel(weldParameterGroupBox);
        w3UnitLabel->setObjectName(QStringLiteral("w3UnitLabel"));

        gridLayout->addWidget(w3UnitLabel, 10, 2, 1, 1);

        h1DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        h1DoubleSpinBox->setObjectName(QStringLiteral("h1DoubleSpinBox"));
        h1DoubleSpinBox->setKeyboardTracking(false);
        h1DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(h1DoubleSpinBox, 5, 1, 1, 1);

        weldTypeLabel = new QLabel(weldParameterGroupBox);
        weldTypeLabel->setObjectName(QStringLiteral("weldTypeLabel"));

        gridLayout->addWidget(weldTypeLabel, 0, 0, 1, 1);

        r2DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        r2DoubleSpinBox->setObjectName(QStringLiteral("r2DoubleSpinBox"));
        r2DoubleSpinBox->setKeyboardTracking(false);
        r2DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(r2DoubleSpinBox, 9, 1, 1, 1);

        h1UnitLabel = new QLabel(weldParameterGroupBox);
        h1UnitLabel->setObjectName(QStringLiteral("h1UnitLabel"));

        gridLayout->addWidget(h1UnitLabel, 5, 2, 1, 1);

        w2DoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        w2DoubleSpinBox->setObjectName(QStringLiteral("w2DoubleSpinBox"));
        w2DoubleSpinBox->setKeyboardTracking(false);
        w2DoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(w2DoubleSpinBox, 7, 1, 1, 1);

        r1UnitLabel = new QLabel(weldParameterGroupBox);
        r1UnitLabel->setObjectName(QStringLiteral("r1UnitLabel"));

        gridLayout->addWidget(r1UnitLabel, 6, 2, 1, 1);

        w3Label = new QLabel(weldParameterGroupBox);
        w3Label->setObjectName(QStringLiteral("w3Label"));

        gridLayout->addWidget(w3Label, 10, 0, 1, 1);

        symmetryLabel = new QLabel(weldParameterGroupBox);
        symmetryLabel->setObjectName(QStringLiteral("symmetryLabel"));

        gridLayout->addWidget(symmetryLabel, 1, 0, 1, 1);

        symmetryComboBox = new QComboBox(weldParameterGroupBox);
        symmetryComboBox->setObjectName(QStringLiteral("symmetryComboBox"));

        gridLayout->addWidget(symmetryComboBox, 1, 1, 1, 2);

        probePosLabel = new QLabel(weldParameterGroupBox);
        probePosLabel->setObjectName(QStringLiteral("probePosLabel"));

        gridLayout->addWidget(probePosLabel, 2, 0, 1, 1);

        ProbePosComboBox = new QComboBox(weldParameterGroupBox);
        ProbePosComboBox->setObjectName(QStringLiteral("ProbePosComboBox"));

        gridLayout->addWidget(ProbePosComboBox, 2, 1, 1, 2);

        HAZLabel = new QLabel(weldParameterGroupBox);
        HAZLabel->setObjectName(QStringLiteral("HAZLabel"));

        gridLayout->addWidget(HAZLabel, 3, 0, 1, 1);

        HAZDoubleSpinBox = new QDoubleSpinBox(weldParameterGroupBox);
        HAZDoubleSpinBox->setObjectName(QStringLiteral("HAZDoubleSpinBox"));
        HAZDoubleSpinBox->setDecimals(1);

        gridLayout->addWidget(HAZDoubleSpinBox, 3, 1, 1, 1);

        HAZUnitLabel = new QLabel(weldParameterGroupBox);
        HAZUnitLabel->setObjectName(QStringLiteral("HAZUnitLabel"));

        gridLayout->addWidget(HAZUnitLabel, 3, 2, 1, 1);


        verticalLayout->addWidget(weldParameterGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        partFileGroupBox = new QGroupBox(DialogWeldFixDataII);
        partFileGroupBox->setObjectName(QStringLiteral("partFileGroupBox"));
        gridLayout_2 = new QGridLayout(partFileGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        nccDefaultPathBt = new QPushButton(partFileGroupBox);
        nccDefaultPathBt->setObjectName(QStringLiteral("nccDefaultPathBt"));

        gridLayout_2->addWidget(nccDefaultPathBt, 0, 0, 1, 1);

        nccPathBt = new QPushButton(partFileGroupBox);
        nccPathBt->setObjectName(QStringLiteral("nccPathBt"));

        gridLayout_2->addWidget(nccPathBt, 0, 1, 1, 1);

        partFileNameLabel = new QLabel(partFileGroupBox);
        partFileNameLabel->setObjectName(QStringLiteral("partFileNameLabel"));

        gridLayout_2->addWidget(partFileNameLabel, 1, 0, 1, 2);

        partFileListView = new QListView(partFileGroupBox);
        partFileListView->setObjectName(QStringLiteral("partFileListView"));

        gridLayout_2->addWidget(partFileListView, 2, 0, 1, 2);


        horizontalLayout_2->addWidget(partFileGroupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        showWidget = new WeldShowDataIIWidget(DialogWeldFixDataII);
        showWidget->setObjectName(QStringLiteral("showWidget"));

        verticalLayout_2->addWidget(showWidget);

        buttonBox = new QDialogButtonBox(DialogWeldFixDataII);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(DialogWeldFixDataII);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogWeldFixDataII, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogWeldFixDataII, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogWeldFixDataII);
    } // setupUi

    void retranslateUi(QDialog *DialogWeldFixDataII)
    {
        DialogWeldFixDataII->setWindowTitle(QApplication::translate("DialogWeldFixDataII", "Weld", Q_NULLPTR));
        weldFormComboBox->clear();
        weldFormComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldFixDataII", "Weld", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Load Part File", Q_NULLPTR)
        );
        zoomLabel->setText(QApplication::translate("DialogWeldFixDataII", "Zoom:", Q_NULLPTR));
        pathLabel->setText(QString());
        weldImageLabel->setText(QApplication::translate("DialogWeldFixDataII", "TextLabel", Q_NULLPTR));
        weldParameterGroupBox->setTitle(QApplication::translate("DialogWeldFixDataII", "Weld Parameter", Q_NULLPTR));
        r1Label->setText(QApplication::translate("DialogWeldFixDataII", "R1:", Q_NULLPTR));
        r2Label->setText(QApplication::translate("DialogWeldFixDataII", "R2:", Q_NULLPTR));
        w1UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        h2Label->setText(QApplication::translate("DialogWeldFixDataII", "H2:", Q_NULLPTR));
        w2UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        h2UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        h1Label->setText(QApplication::translate("DialogWeldFixDataII", "H1:", Q_NULLPTR));
        w1Label->setText(QApplication::translate("DialogWeldFixDataII", "W1:", Q_NULLPTR));
        w2Label->setText(QApplication::translate("DialogWeldFixDataII", "W2:", Q_NULLPTR));
        r2UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        weldTypeComboBox->clear();
        weldTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldFixDataII", "NONE", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "I", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "V", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "U", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "VY", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "VV", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "UU", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "UV", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "TKY", Q_NULLPTR)
        );
        w3UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        weldTypeLabel->setText(QApplication::translate("DialogWeldFixDataII", "Weld Type:", Q_NULLPTR));
        h1UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        r1UnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        w3Label->setText(QApplication::translate("DialogWeldFixDataII", "W3:", Q_NULLPTR));
        symmetryLabel->setText(QApplication::translate("DialogWeldFixDataII", "Symmetry:", Q_NULLPTR));
        symmetryComboBox->clear();
        symmetryComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldFixDataII", "Symmetry", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Right", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Left", Q_NULLPTR)
        );
        probePosLabel->setText(QApplication::translate("DialogWeldFixDataII", "Probe Position:", Q_NULLPTR));
        ProbePosComboBox->clear();
        ProbePosComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogWeldFixDataII", "Web1", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Web2", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Wing1", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Wing2", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Wing3", Q_NULLPTR)
         << QApplication::translate("DialogWeldFixDataII", "Wing4", Q_NULLPTR)
        );
        HAZLabel->setText(QApplication::translate("DialogWeldFixDataII", "HAZ:", Q_NULLPTR));
        HAZUnitLabel->setText(QApplication::translate("DialogWeldFixDataII", "mm", Q_NULLPTR));
        partFileGroupBox->setTitle(QApplication::translate("DialogWeldFixDataII", "Part File", Q_NULLPTR));
        nccDefaultPathBt->setText(QApplication::translate("DialogWeldFixDataII", "Default Path", Q_NULLPTR));
        nccPathBt->setText(QApplication::translate("DialogWeldFixDataII", "Path Setting", Q_NULLPTR));
        partFileNameLabel->setText(QApplication::translate("DialogWeldFixDataII", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogWeldFixDataII: public Ui_DialogWeldFixDataII {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWELDFIXDATAII_H
