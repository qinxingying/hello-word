#ifndef ASSEMBLYREMOTESDIALOG_H
#define ASSEMBLYREMOTESDIALOG_H

#include <QDialog>
class singleRemoteWidget;
class assemblyRemotesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit assemblyRemotesDialog(QWidget *parent = NULL);
    ~assemblyRemotesDialog();
private:
    void initRemotes();
    void saveRemotes();
    singleRemoteWidget* m_singleRemote1;
    singleRemoteWidget* m_singleRemote2;
    singleRemoteWidget* m_singleRemote3;
    singleRemoteWidget* m_singleRemote4;
    singleRemoteWidget* m_singleRemote5;
    singleRemoteWidget* m_singleRemote6;
    singleRemoteWidget* m_singleRemote7;
    singleRemoteWidget* m_singleRemote8;
    QPushButton *m_hide;
};

#endif // ASSEMBLYREMOTESDIALOG_H
