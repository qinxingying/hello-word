#ifndef DIALOGREPORTSETTING_H
#define DIALOGREPORTSETTING_H

#include <QDialog>
#include <report/DopplerHtmlReport.h>

namespace Ui {
    class DialogReportSetting;
}

class DialogReportSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReportSetting(QWidget *parent = 0);
    ~DialogReportSetting();
    void SetReportInfo(ReportInfo*) ;
    void SetRepotName(QString);
    ReportInfo* GetRePortInfo() ;

protected:
    void UpdateItems() ;
    ReportInfo m_cInfo ;

private slots:
    void on_pushButton_clicked();

    void on_logoToolButton_clicked();

private:
    Ui::DialogReportSetting *ui;
};

#endif // DIALOGREPORTSETTING_H
