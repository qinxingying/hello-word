#include "dialogkeyboardhelp.h"
#include "ui_dialogkeyboardhelp.h"

DialogKeyboardHelp::DialogKeyboardHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogKeyboardHelp)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/file/resource/Main/keyboardInstruction.jpg"));
}

DialogKeyboardHelp::~DialogKeyboardHelp()
{
    delete ui;
}
