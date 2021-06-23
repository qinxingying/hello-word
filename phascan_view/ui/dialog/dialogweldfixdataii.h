/**********************************
  Description: 二代数据焊缝图示调整界面
**********************************/

#ifndef DIALOGWELDFIXDATAII_H
#define DIALOGWELDFIXDATAII_H

#include <QDialog>
#include "Instrument.h"

namespace Ui {
class DialogWeldFixDataII;
}

class DialogWeldFixDataII : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWeldFixDataII(QWidget *parent = 0, int nGroupId = 0);
    ~DialogWeldFixDataII();
    PART_CONFIG* GetPart();

protected:
    enum DISPLAY_MODE
    {
        DISPLAY_WELD = 0,
        DISPLAY_PART
    };
    void SetDisplayMode(DISPLAY_MODE eMode_);
    void SetWndName();
    void ListPartFiles();
private slots:
    void weldTypeChanged( int index);
    void symmetryChanged( int index);
    void probePosChanged( int index);
    void weldFormChanged(int index);
    void HAZValueChanged(double value);
    void w1ValueChanged( double value);
    void w2ValueChanged( double value);
    void w3ValueChanged( double value);
    void h1ValueChanged( double value);
    void h2ValueChanged( double value);
    void r1ValueChanged( double value);
    void r2ValueChanged( double value);    
    void PartFileListClicked(QModelIndex index);
    void zoomValueChanged(double value);
    void on_nccDefaultPathBt_clicked();
    void on_nccPathBt_clicked();

private:
    Ui::DialogWeldFixDataII *ui;
    int m_nGroupId;
    PART_CONFIG m_cPart;
    DISPLAY_MODE m_eDisplay;
    QString m_path;
};

#endif // DIALOGWELDFIXDATAII_H
