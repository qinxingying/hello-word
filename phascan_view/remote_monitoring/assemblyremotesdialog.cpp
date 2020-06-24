#include "assemblyremotesdialog.h"
#include "singleremotewidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSettings>

assemblyRemotesDialog::assemblyRemotesDialog(QWidget *parent)
    : QDialog(parent),
      m_singleRemote1(new singleRemoteWidget(this)),
      m_singleRemote2(new singleRemoteWidget(this)),
      m_hide(new QPushButton(tr("Hide"), this))
{
    resize(300, 150);
    setWindowTitle(tr("Remote Monitor"));
    QVBoxLayout *dialogVLayout = new QVBoxLayout(this);
    dialogVLayout->addWidget(m_singleRemote1);
    dialogVLayout->addWidget(m_singleRemote2);
    dialogVLayout->addWidget(m_hide);
    setLayout(dialogVLayout);
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowCloseButtonHint);
    connect(this, SIGNAL(rejected()), this, SLOT(hide()));
    connect(m_hide, SIGNAL(clicked(bool)), this, SLOT(hide()));
    initRemotes();
}

assemblyRemotesDialog::~assemblyRemotesDialog()
{
    saveRemotes();
}

void assemblyRemotesDialog::initRemotes()
{
    QVariant remote1("192.168.1.170");
    QVariant remote2("192.168.1.171");
    QSettings settings("remoteviewer.ini", QSettings::IniFormat);
    settings.beginGroup("remotesIP");
    QString temp = settings.value("remote1", remote1).toString();
    m_singleRemote1->setIP(temp);
    m_singleRemote1->setLabel("IP 1");
    temp = settings.value("remote2", remote2).toString();
    m_singleRemote2->setIP(temp);
    m_singleRemote2->setLabel("IP 2");
    settings.endGroup();
}

void assemblyRemotesDialog::saveRemotes()
{
    QSettings settings("remoteviewer.ini", QSettings::IniFormat);
    settings.beginGroup("remotesIP");
    QString temp = m_singleRemote1->getIP();
    settings.setValue("remote1", temp);
    temp = m_singleRemote2->getIP();
    settings.setValue("remote2", temp);
    settings.sync();
}
