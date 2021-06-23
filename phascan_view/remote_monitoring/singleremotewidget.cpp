#include "singleremotewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>

singleRemoteWidget::singleRemoteWidget(QWidget *parent)
    : QWidget(parent),
      m_label(new QLabel(this)),
      m_ip1(new QSpinBox(this)),
      m_ip2(new QSpinBox(this)),
      m_ip3(new QSpinBox(this)),
      m_ip4(new QSpinBox(this)),
      m_ok(new QPushButton(tr("Ok"), this)),
      m_cancel(new QPushButton(tr("Cancel"), this)),
      m_process(nullptr),
      m_connected(false)
{
    QHBoxLayout *ipVLayout = new QHBoxLayout(this);
    ipVLayout->addWidget(m_label);
    ipVLayout->addWidget(m_ip1);
    ipVLayout->addWidget(new QLabel("."));
    ipVLayout->addWidget(m_ip2);
    ipVLayout->addWidget(new QLabel("."));
    ipVLayout->addWidget(m_ip3);
    ipVLayout->addWidget(new QLabel("."));
    ipVLayout->addWidget(m_ip4);
    ipVLayout->addWidget(new QLabel);
    ipVLayout->addWidget(m_ok);
    ipVLayout->addWidget(m_cancel);

    m_ip1->setMinimum(0);
    m_ip1->setMaximum(255);
    m_ip2->setMinimum(0);
    m_ip1->setButtonSymbols(QSpinBox::NoButtons);
    m_ip2->setMaximum(255);
    m_ip2->setButtonSymbols(QSpinBox::NoButtons);
    m_ip3->setMinimum(0);
    m_ip3->setMaximum(255);
    m_ip3->setButtonSymbols(QSpinBox::NoButtons);
    m_ip4->setMinimum(0);
    m_ip4->setMaximum(255);
    m_ip4->setButtonSymbols(QSpinBox::NoButtons);

    setLayout(ipVLayout);
    m_cancel->setEnabled(false);
    connect(m_ok, SIGNAL(clicked(bool)), this, SLOT(okClicked()));
    connect(m_cancel, SIGNAL(clicked(bool)), this, SLOT(cancelClicked()));
}

void singleRemoteWidget::okClicked()
{
    if(m_connected) {
        QMessageBox::warning(NULL, tr("Warning"), tr("remote monitor had connected!!"), QMessageBox::Ok);
        return;
    }

    QSettings tmp(".tmp", QSettings::IniFormat);
    QSettings settings("remoteviewer.ini", QSettings::IniFormat);
    settings.beginGroup("connection");
    tmp.beginGroup("connection");
    QStringList keys = settings.childKeys();
    foreach (QString key, keys) {
        tmp.setValue(key, settings.value(key));
    }
    settings.endGroup();
    tmp.endGroup();

    settings.beginGroup("options");
    tmp.beginGroup("options");
    keys = settings.childKeys();
    foreach (QString key, keys) {
        tmp.setValue(key, settings.value(key));
    }
    settings.endGroup();
    tmp.endGroup();

    tmp.beginGroup("connection");
    tmp.setValue("host", getIP());
    tmp.setValue("password", "43ab167de6805c6e");
    tmp.endGroup();
    tmp.sync();

    if(m_process == nullptr){
        m_process = new QProcess(this);
        connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(remoteExit()));
    }
    m_process->start("RemoteViewer.exe -optionsfile=.tmp");
    ::system("del .tmp ");
    m_cancel->setEnabled(true);
    m_ok->setEnabled(false);
    m_connected = true;
}

void singleRemoteWidget::cancelClicked()
{
    if(!m_connected) {
        return;
    }
    m_process->kill();
    m_process->terminate();
    m_connected = false;
    m_cancel->setEnabled(false);
    m_ok->setEnabled(true);
}

void singleRemoteWidget::remoteExit()
{
    m_connected = false;
    m_cancel->setEnabled(false);
    m_ok->setEnabled(true);
}

void singleRemoteWidget::setIP(QString &src)
{
    QStringList list1 = src.split('.', QString::SkipEmptyParts);
    m_ip1->setValue(list1.at(0).toInt());
    m_ip2->setValue(list1.at(1).toInt());
    m_ip3->setValue(list1.at(2).toInt());
    m_ip4->setValue(list1.at(3).toInt());
}

void singleRemoteWidget::setLabel(const char *src)
{
    m_label->setText(src);
}

QString singleRemoteWidget::getIP()
{
    QString ip = QString("%1.%2.%3.%4")
                    .arg(m_ip1->value())
                    .arg(m_ip2->value())
                    .arg(m_ip3->value())
                    .arg(m_ip4->value());
    return ip;
}
