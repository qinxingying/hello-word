#ifndef DIALOGDXFFILELOAD_H
#define DIALOGDXFFILELOAD_H

#include "Instrument.h"

#include <QDialog>
#include <QModelIndex>

namespace Ui {
    class DialogDxfFileLoad;
}

class DialogDxfFileLoad : public QDialog
{
    Q_OBJECT

public:
    DialogDxfFileLoad(QWidget *parent = 0, int nGroupId_ = 0);
    ~DialogDxfFileLoad();

	PART_CONFIG* GetPart();

protected:
    enum DISPLAY_MODE
    {
        DISPLAY_WELD = 0,
        DISPLAY_PART
    };

    void SetWndName();
    void SetDisplayMode(DISPLAY_MODE eMode_);

	void ListPartFiles();
	void SetPart();

	void UpdateWeld();
    void UpdateDisplay();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_ComWeldType_currentIndexChanged(int index);
    void on_ComWeldSymetry_currentIndexChanged(int index);
    void on_SpinWHeight_valueChanged(double arg1);
    void on_SpinWoffset_valueChanged(double arg1);
    void on_SpinFHeight_valueChanged(double arg1);
    void on_SpinFRadius_valueChanged(double arg1);
    void on_SpinFAngle_valueChanged(double arg1);
    void on_SpinFHeight_2_valueChanged(double arg1);
    void on_SpinFAngle_2_valueChanged(double arg1);
	void on_PartFileListDbClicked(QModelIndex index);
	void on_BtnNccPathClicked();
	void on_BtnNccDefaultPathClicked();
    void slot_doubleSpinBox_zoom_setValue(double value);

private:
    Ui::DialogDxfFileLoad *ui;
    DISPLAY_MODE m_eDisplay;
	PART_CONFIG m_cPart;
    int m_nGroupId;
    int m_nWeldPartSel;
    QString m_path;
};

#endif // DIALOGDXFFILELOAD_H
