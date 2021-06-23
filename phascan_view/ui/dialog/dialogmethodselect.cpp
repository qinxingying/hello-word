#include "dialogmethodselect.h"
#include "ui_dialogmethodselect.h"
#include <QButtonGroup>

DialogMethodSelect::DialogMethodSelect( int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMethodSelect)
{
    ui->setupUi(this);
    m_GroupBt = new QButtonGroup(this);
    m_GroupBt->addButton(ui->RBtHalfWave, 0);
    m_GroupBt->addButton(ui->RBtAbsoluteSensitivity, 1);
    m_method = id;
    if(id == 0){
        ui->RBtHalfWave->setChecked(true);
    }else{
        ui->RBtAbsoluteSensitivity->setChecked(true);
    }

    connect(ui->RBtHalfWave, SIGNAL(clicked(bool)), this, SLOT(methodSelect()));
    connect(ui->RBtAbsoluteSensitivity, SIGNAL(clicked(bool)), this, SLOT(methodSelect()));
    connect(ui->BtOK, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

DialogMethodSelect::~DialogMethodSelect()
{
    delete ui;
}

void DialogMethodSelect::methodSelect()
{
    switch (m_GroupBt->checkedId()) {
    case 0:
        m_method = 0;
        break;
    case 1:
        m_method = 1;
        break;
    default:
        break;
    }
}
