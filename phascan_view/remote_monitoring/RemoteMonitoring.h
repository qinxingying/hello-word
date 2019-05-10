#ifndef REMOTEMONITORING_H
#define REMOTEMONITORING_H

#include <QProcess>

class LoginDialog;

class RemoteMonitoring : public QProcess
{
    Q_OBJECT
public:
    explicit RemoteMonitoring(QObject *parent = Q_NULLPTR);
    ~RemoteMonitoring();

signals:
    void remote_connected();
    void remote_disconnected();

protected slots:
    void connect_remote_monitor();
    void disconnect_remote_monitor();

    void do_finished();

private:
    LoginDialog *m_loginDialog;
    bool m_connected;
};

#endif // REMOTEMONITORING_H
