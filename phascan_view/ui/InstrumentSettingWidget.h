#ifndef INSTRUMENTSETTINGWIDGET_H
#define INSTRUMENTSETTINGWIDGET_H
//##########################
//    �����������ô��� �� ���е�����������
//##########################
#include "FileStruct.h"

#include <QWidget>

class DopplerConfigure ;
namespace Ui {
    class InstrumentSettingWidget;
}

class InstrumentSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InstrumentSettingWidget(QWidget *parent = 0);
    ~InstrumentSettingWidget();
    void UpdateScanPos();
    void UpdateIndexPos();
    void UpdateIndexBox();
    void retranslateUi();

protected:
    //**************************
    void SetItemInvalide() ;
    //**************************
    void InitCommonConfig() ;
    DopplerConfigure* m_pConfig ;
    void showEvent(QShowEvent *) ;
    void UpdateEncoderInfo();
    void UpdateScanRange() ;
    void ResetEncoderSetting();

private slots:
    void on_ComScanType_currentIndexChanged(int index);
    void on_ComEncoderType_currentIndexChanged(int index);
    void on_ComEncoderTypeSetting_currentIndexChanged(int index);
    void on_ComEncoderPolarity_currentIndexChanged(int index);
    void on_ComEncoderDirection_currentIndexChanged(int index);
    void on_ComVoltagePa_currentIndexChanged(int index);
    void on_ComVoltageUt_currentIndexChanged(int index);
    //void on_ComTRPA_currentIndexChanged(int index);
    //void on_ComTRUT_currentIndexChanged(int index);
    void on_ValuePrf_editingFinished();
    void on_ValueScanStart_editingFinished();
    void on_ValueScanEnd_editingFinished();
    void on_ValueScanResolution_editingFinished();
    void on_ValueIndexStart_editingFinished();
    void on_ValueIndexStop_editingFinished();
    void on_ValueIndexResolution_editingFinished();
    void on_ValueEncoderResolution_editingFinished();
    void on_ValueEncoderOrg_editingFinished();
    void on_SpinBoxCurrentScanPos_valueChanged(double arg1);
    void on_SliderCurrentScanPos_valueChanged(int value);
    void on_SliderCurrentIndexPos_valueChanged(int value);
    void on_SpinBoxRasterOffset_valueChanged(double value);

    void on_SpinBoxCurrentScanend_valueChanged(double arg1);

    void on_SpinBoxCurrentIndexend_valueChanged(double arg1);

    void on_SpinBoxCurrentScanstart_valueChanged(double arg1);

    void on_SpinBoxCurrentIndexstart_valueChanged(double arg1);

    void on_BtnReset_clicked();

private:
    Ui::InstrumentSettingWidget *ui;
};

#endif // INSTRUMENTSETTINGWIDGET_H
