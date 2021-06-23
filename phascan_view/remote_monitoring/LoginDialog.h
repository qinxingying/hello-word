#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSpinBox>

class QPushButton;
class QSpinBox;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = NULL);

    QString ip();

private:
    QSpinBox *m_ip1;
    QSpinBox *m_ip2;
    QSpinBox *m_ip3;
    QSpinBox *m_ip4;
    QPushButton *m_ok;
    QPushButton *m_cancel;
};

#endif // LOGINDIALOG_H
