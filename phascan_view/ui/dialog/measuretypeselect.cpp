#include "measuretypeselect.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
MeasureTypeSelect::MeasureTypeSelect(QWidget *parent, int type) :
    QDialog(parent),
    m_tabWidget(new QTabWidget(this)),
    m_tableWidgets(TABLE_COUNT),
    m_chooseBtn(new QPushButton(tr("Choose"), this)),
    m_cancelBtn(new QPushButton(tr("Cancel"), this))
{
    setWindowFlags((windowFlags() & ~Qt::WindowContextHelpButtonHint)
                       | Qt::FramelessWindowHint);
    setMinimumWidth(630);
    setMinimumHeight(500);
    move(100, 50);

    m_tabWidget->setTabPosition(QTabWidget::West);

//    m_tabWidget->addTab(create_gate_widget(), tr("Gate"));
//    m_tabWidget->addTab(create_cursor_widget(), tr("Cursor"));
//    m_tabWidget->addTab(create_position_widget(), tr("Position"));
//    m_tabWidget->addTab(create_sizing_widget(), tr("Sizing"));
//    m_tabWidget->addTab(create_aws_widget(), "AWS");
//    m_tabWidget->addTab(create_tofd_widget(), "TOFD");

    QHBoxLayout *btmLayout = new QHBoxLayout;
    btmLayout->addSpacerItem(new QSpacerItem(450, 0,
                                             QSizePolicy::Expanding,
                                             QSizePolicy::Ignored));
    btmLayout->addWidget(m_cancelBtn);
    btmLayout->addWidget(m_chooseBtn);

    connect(m_chooseBtn, SIGNAL(clicked(bool)), SLOT(accept()));
    connect(m_cancelBtn, SIGNAL(clicked(bool)), SLOT(reject()));

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    mainLayout->addWidget(new QLabel(tr("Measurement"), this), 2);
    mainLayout->addWidget(line);
    mainLayout->addWidget(m_tabWidget, 16);
    mainLayout->addLayout(btmLayout, 1);

    //set_type(type);
}

MeasureTypeSelect::~MeasureTypeSelect()
{

}

//QWidget *MeasureTypeSelect::create_gate_widget()
//{

//}

//QWidget *MeasureTypeSelect::create_cursor_widget()
//{

//}

//QWidget *MeasureTypeSelect::create_position_widget()
//{

//}

//QWidget *MeasureTypeSelect::create_sizing_widget()
//{

//}

//QWidget *MeasureTypeSelect::create_aws_widget()
//{

//}

//QWidget *MeasureTypeSelect::create_tofd_widget()
//{

//}
