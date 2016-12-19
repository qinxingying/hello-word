#ifndef DIALOGWELDPARTLOAD_H
#define DIALOGWELDPARTLOAD_H

#include "Instrument.h"
#include "DopplerConfigure.h"

#include <QDialog>
#include <QModelIndex>

namespace Ui {
    class DialogWeldPartLoad;
}

class DialogWeldPartLoad : public QDialog
{
    Q_OBJECT

public:
    DialogWeldPartLoad(QWidget *parent = 0 , int nGroupId_ = 0);
    ~DialogWeldPartLoad();

	PART_CONFIG* GetPart();

protected:
    enum DISPLAY_MODE
    {
        DISPLAY_WELD  = 0,
        DISPLAY_PART
    };

    void SetWndName();
    void SetDisplayMode(DISPLAY_MODE eMode_)   ;

	void ListPartFiles();
	void SetPart();

	void UpdateWeld();
    void UpdateDisplay() ;

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_ComWeldType_currentIndexChanged(int index);
    void on_ComWeldSymetry_currentIndexChanged(int index);
    void on_SpinWHeight_valueChanged(double arg1);
    void on_SpinWoffset_valueChanged(double arg1);
    void on_SpinFHeight_valueChanged(double arg1);
    void on_SpinFRadius_valueChanged(double arg1);
    void on_SpinFAngle_valueChanged(double arg1);
	void on_PartFileListDbClicked(QModelIndex index);
	void on_BtnNccPathClicked();
	void on_BtnNccDefaultPathClicked();

private:
	DopplerConfigure* m_pConfig;
	Ui::DialogWeldPartLoad *ui;
    DISPLAY_MODE m_eDisplay;
	PART_CONFIG m_cPart;
    int    m_nGroupId;
    int    m_nWeldPartSel;
};

#endif // DIALOGWELDPARTLOAD_H
