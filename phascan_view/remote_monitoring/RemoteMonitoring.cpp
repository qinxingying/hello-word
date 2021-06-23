#include "RemoteMonitoring.h"
#include <QDebug>
#include "LoginDialog.h"
#include <QSettings>
#include <QMessageBox>

RemoteMonitoring::RemoteMonitoring(QObject *parent)
    : QProcess(parent),
      m_loginDialog(new LoginDialog),
      m_connected(false)
{
    connect(this, SIGNAL(finished(int)),
            SLOT(do_finished()));
}

RemoteMonitoring::~RemoteMonitoring()
{
    disconnect_remote_monitor();
    delete m_loginDialog;
}

void RemoteMonitoring::connect_remote_monitor()
{
    if(m_connected) {
        QMessageBox::warning(NULL, tr("Warning"), tr("remote monitor had connected!!"), QMessageBox::Ok);
        return;
    }

    if(m_loginDialog->exec() != QDialog::Accepted) {
        return;
    }

    QSettings tmp(".tmp", QSettings::IniFormat);
    QSettings settings("remoteviewer.ini", QSettings::IniFormat);
    QStringList keys = settings.allKeys();
    foreach (QString key, keys) {
        tmp.setValue(key, settings.value(key));
    }

    tmp.beginGroup("connection");
    tmp.setValue("host", m_loginDialog->ip());
    tmp.setValue("password", "43ab167de6805c6e");
    tmp.endGroup();
    tmp.sync();

    start("RemoteViewer.exe -optionsfile=.tmp");
    ::system("del .tmp ");

    m_connected = true;
}

void RemoteMonitoring::disconnect_remote_monitor()
{
    if(!m_connected) {
        return;
    }

    this->kill();
    this->terminate();
    m_connected = false;
}

void RemoteMonitoring::do_finished()
{
    m_connected = false;
}
