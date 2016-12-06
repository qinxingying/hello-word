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
    ReportInfo* GetRePortInfo() ;


protected:

    void UpdateItems() ;
    ReportInfo m_cInfo ;

    void SetWndName(setup_LANG eLang);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogReportSetting *ui;
};

#endif // DIALOGREPORTSETTING_H
