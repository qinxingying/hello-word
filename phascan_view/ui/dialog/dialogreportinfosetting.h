#ifndef DIALOGREPORTINFOSETTING_H
#define DIALOGREPORTINFOSETTING_H

#include <QDialog>
#include <report/DopplerHtmlReport.h>

namespace Ui {
class DialogReportInfoSetting;
}

class DialogReportInfoSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReportInfoSetting(QWidget *parent = 0);
    ~DialogReportInfoSetting();
    void SetReportInfo2(ReportInfo2 &info2);
    ReportInfo2& GetRePortInfo2();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogReportInfoSetting *ui;

    ReportInfo2 m_cInfo;
};

#endif // DIALOGREPORTINFOSETTING_H
