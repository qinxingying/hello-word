#ifndef SINGLEREMOTEWIDGET_H
#define SINGLEREMOTEWIDGET_H

#include <QWidget>
class QSpinBox;
class QPushButton;
class QProcess;
class QLabel;
class singleRemoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit singleRemoteWidget(QWidget *parent = NULL);
    void setIP(QString &src);
    void setLabel(const char *src);
    QString getIP();

private slots:
    void okClicked();
    void cancelClicked();
    void remoteExit();
private:
    QLabel *m_label;
    QSpinBox *m_ip1;
    QSpinBox *m_ip2;
    QSpinBox *m_ip3;
    QSpinBox *m_ip4;
    QPushButton *m_ok;
    QPushButton *m_cancel;
    QProcess *m_process;
    bool m_connected;
};

#endif // SINGLEREMOTEWIDGET_H
