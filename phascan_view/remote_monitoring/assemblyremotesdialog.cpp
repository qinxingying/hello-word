#include "assemblyremotesdialog.h"
#include "singleremotewidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSettings>

assemblyRemotesDialog::assemblyRemotesDialog(QWidget *parent)
    : QDialog(parent),
      m_singleRemote1(new singleRemoteWidget(this)),
      m_singleRemote2(new singleRemoteWidget(this)),
      m_singleRemote3(new singleRemoteWidget(this)),
      m_singleRemote4(new singleRemoteWidget(this)),
      m_singleRemote5(new singleRemoteWidget(this)),
      m_singleRemote6(new singleRemoteWidget(this)),
      m_singleRemote7(new singleRemoteWidget(this)),
      m_singleRemote8(new singleRemoteWidget(this)),
      m_hide(new QPushButton(tr("Hide"), this))
{
    resize(300, 200);
    setWindowTitle(tr("Remote Monitor"));
    QVBoxLayout *dialogVLayout = new QVBoxLayout(this);
    dialogVLayout->addWidget(m_singleRemote1);
    dialogVLayout->addWidget(m_singleRemote2);
    dialogVLayout->addWidget(m_singleRemote3);
    dialogVLayout->addWidget(m_singleRemote4);
    dialogVLayout->addWidget(m_singleRemote5);
    dialogVLayout->addWidget(m_singleRemote6);
    dialogVLayout->addWidget(m_singleRemote7);
    dialogVLayout->addWidget(m_singleRemote8);
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
    QVariant remote3("192.168.1.172");
    QVariant remote4("192.168.1.173");
    QVariant remote5("192.168.1.174");
    QVariant remote6("192.168.1.175");
    QVariant remote7("192.168.1.176");
    QVariant remote8("192.168.1.177");
    QSettings settings("remoteviewer.ini", QSettings::IniFormat);
    settings.beginGroup("remotesIP");

    QString temp = settings.value("remote1", remote1).toString();
    m_singleRemote1->setIP(temp);
    m_singleRemote1->setLabel("IP 1");

    temp = settings.value("remote2", remote2).toString();
    m_singleRemote2->setIP(temp);
    m_singleRemote2->setLabel("IP 2");

    temp = settings.value("remote3", remote3).toString();
    m_singleRemote3->setIP(temp);
    m_singleRemote3->setLabel("IP 3");

    temp = settings.value("remote4", remote4).toString();
    m_singleRemote4->setIP(temp);
    m_singleRemote4->setLabel("IP 4");

    temp = settings.value("remote5", remote5).toString();
    m_singleRemote5->setIP(temp);
    m_singleRemote5->setLabel("IP 5");

    temp = settings.value("remote6", remote6).toString();
    m_singleRemote6->setIP(temp);
    m_singleRemote6->setLabel("IP 6");

    temp = settings.value("remote7", remote7).toString();
    m_singleRemote7->setIP(temp);
    m_singleRemote7->setLabel("IP 7");

    temp = settings.value("remote8", remote8).toString();
    m_singleRemote8->setIP(temp);
    m_singleRemote8->setLabel("IP 8");
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

    temp = m_singleRemote3->getIP();
    settings.setValue("remote3", temp);

    temp = m_singleRemote4->getIP();
    settings.setValue("remote4", temp);

    temp = m_singleRemote5->getIP();
    settings.setValue("remote5", temp);

    temp = m_singleRemote6->getIP();
    settings.setValue("remote6", temp);

    temp = m_singleRemote7->getIP();
    settings.setValue("remote7", temp);

    temp = m_singleRemote8->getIP();
    settings.setValue("remote8", temp);
    settings.sync();
}
