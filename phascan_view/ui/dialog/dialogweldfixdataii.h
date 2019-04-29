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

private slots:
    void weldTypeChanged(int index);
private:
    Ui::DialogWeldFixDataII *ui;
    int m_nGroupId;
    PART_CONFIG m_cPart;
};

#endif // DIALOGWELDFIXDATAII_H
