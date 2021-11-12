#ifndef DIALOGREPORTINFOSETTING_H
#define DIALOGREPORTINFOSETTING_H

#include <QDialog>
#include <report/DopplerHtmlReport.h>
#include <QFileSystemModel>

namespace Ui {
class DialogReportInfoSetting;
}

class DialogReportInfoSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReportInfoSetting(QWidget *parent = 0);
    ~DialogReportInfoSetting();
    void SetReportInfo2(ReportInfo2 &info2, bool flush = true);
    ReportInfo2& GetRePortInfo2();

private slots:
    void on_buttonBox_accepted();
    void on_saveBtn_clicked();
    void on_deleteBtn_clicked();
    void on_newBtn_clicked();
    void on_clearBtn_clicked();
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::DialogReportInfoSetting *ui;

    ReportInfo2 m_cInfo;

    QFileSystemModel    *m_model;
    QString              m_infoFilePath;
    QString              m_infoFileName;
};

#endif // DIALOGREPORTINFOSETTING_H
