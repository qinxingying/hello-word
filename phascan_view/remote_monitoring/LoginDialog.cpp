#include "LoginDialog.h"
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent),
      m_ip1(new QSpinBox(this)),
      m_ip2(new QSpinBox(this)),
      m_ip3(new QSpinBox(this)),
      m_ip4(new QSpinBox(this)),
      m_ok(new QPushButton(tr("Ok"), this)),
      m_cancel(new QPushButton(tr("Cancel"), this))
{
    resize(300, 200);
    setWindowTitle(tr("Remote IP"));

    QVBoxLayout *dialogVLayout = new QVBoxLayout(this);
    QHBoxLayout *ipVLayout = new QHBoxLayout;
    ipVLayout->addWidget(new QLabel);
    ipVLayout->addWidget(m_ip1);
    ipVLayout->addWidget(new QLabel("."));
    ipVLayout->addWidget(m_ip2);
    ipVLayout->addWidget(new QLabel("."));
    ipVLayout->addWidget(m_ip3);
    ipVLayout->addWidget(new QLabel("."));
    ipVLayout->addWidget(m_ip4);
    ipVLayout->addWidget(new QLabel);

    m_ip1->setMinimum(0);
    m_ip1->setMaximum(255);
    m_ip1->setValue(192);
    m_ip2->setMinimum(0);
    m_ip1->setButtonSymbols(QSpinBox::NoButtons);
    m_ip2->setMaximum(255);
    m_ip2->setValue(168);
    m_ip2->setButtonSymbols(QSpinBox::NoButtons);
    m_ip3->setMinimum(0);
    m_ip3->setMaximum(255);
    m_ip3->setValue(1);
    m_ip3->setButtonSymbols(QSpinBox::NoButtons);
    m_ip4->setMinimum(0);
    m_ip4->setMaximum(255);
    m_ip4->setValue(215);
    m_ip4->setButtonSymbols(QSpinBox::NoButtons);

    QHBoxLayout *buttonHLayout = new QHBoxLayout;
    buttonHLayout->addWidget(m_cancel);
    buttonHLayout->addWidget(m_ok);

    dialogVLayout->addLayout(ipVLayout);
    dialogVLayout->addLayout(buttonHLayout);

    connect(m_cancel, SIGNAL(clicked(bool)),
            this, SLOT(reject()));
    connect(m_ok, SIGNAL(clicked(bool)),
            this, SLOT(accept()));
}

QString LoginDialog::ip()
{
    QString ip = QString("%1.%2.%3.%4")
                    .arg(m_ip1->value())
                    .arg(m_ip2->value())
                    .arg(m_ip3->value())
                    .arg(m_ip4->value());
    return ip;
}
