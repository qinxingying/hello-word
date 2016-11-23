#include "DialogAddOneGroup.h"
#include "ui_DialogAddOneGroup.h"
#include <configure/DopplerConfigure.h>
#include <process/ParameterProcess.h>
#include <gHeader.h>


DialogAddOneGroup::DialogAddOneGroup(QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::DialogAddOneGroup)
{
    DopplerConfigure* _pConfig =  DopplerConfigure::Instance() ;
    m_nSelection = 0 ;
    m_nComQty    = _pConfig->common.nGroupQty + 1 ;

    ui->setupUi(this);
    setModal(true) ;

    ui->comboBox->clear();
    ui->comboBox->addItem(tr("Default Group Configure"));
    for(int i = 1; i < m_nComQty ; i++)
    {
        QString str1(tr("GROUP->"));
        QString str2 ;
        str2.sprintf("[%d]" , i) ;
        str1 += str2 ;
        ui->comboBox->addItem(str1);
    }

    connect(ui->comboBox , SIGNAL(currentIndexChanged(int)) , SLOT(slotComBoxSelectionChanged(int)))  ;

}

DialogAddOneGroup::~DialogAddOneGroup()
{
    delete ui;
}


void DialogAddOneGroup::slotComBoxSelectionChanged(int nId_)
{
    m_nSelection = nId_  ;
}

int DialogAddOneGroup::GetSelection() const
{
    return m_nSelection ;
}

void DialogAddOneGroup::on_pushButton_clicked()
{
    ParameterProcess* _process = ParameterProcess::Instance();
    QString _str = _process->AddOneGroup(m_nSelection - 1) ;
    if(_str.isEmpty())
    {
        accept () ;
    }
    else
    {
        QColor fgColor (0 , 0  , 0) ;
        QColor bgColor (255 , 0 , 0) ;
        g_pMainWnd->SetStatusBarMessageColor(2 , fgColor , bgColor);
        g_pMainWnd->SetStatusBarMessage(2 , _str);
    }
}

void DialogAddOneGroup::on_pushButton_2_clicked()
{
    reject() ;
    g_pMainWnd->UpdateStatusBarInfo();
}

void DialogAddOneGroup::closeEvent (QCloseEvent*)
{
    g_pMainWnd->UpdateStatusBarInfo();
}
