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

private slots:
    void weldTypeChanged( int index);
    void symmetryChanged( int index);
    void w1ValueChanged( double value);
    void w2ValueChanged( double value);
    void w3ValueChanged( double value);
    void h1ValueChanged( double value);
    void h2ValueChanged( double value);
    void r1ValueChanged( double value);
    void r2ValueChanged( double value);
private:
    Ui::DialogWeldFixDataII *ui;
    int m_nGroupId;
    PART_CONFIG m_cPart;
};

#endif // DIALOGWELDFIXDATAII_H
