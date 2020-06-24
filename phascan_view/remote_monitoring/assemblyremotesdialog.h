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
    QPushButton *m_hide;
};

#endif // ASSEMBLYREMOTESDIALOG_H
