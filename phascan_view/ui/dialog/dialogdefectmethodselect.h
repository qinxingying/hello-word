#ifndef DIALOGDEFECTMETHODSELECT_H
#define DIALOGDEFECTMETHODSELECT_H

#include <QDialog>

namespace Ui {
class DialogDefectMethodSelect;
}

class DialogDefectMethodSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDefectMethodSelect(QWidget *parent = 0);
    ~DialogDefectMethodSelect();

    int getLengthMeasureMethodId() {return m_lengthMeasureMethod;}

    int getHeightMeasureMethodId() {return m_heightMeasureMethod;}

    double getScale() {return m_scale;}

private slots:
    void on_halfWaveRadioL_clicked();

    void on_endHalfWaveRadioL_clicked();

    void on_sensitivityRadioL_clicked();

    void on_halfWaveRadioH_clicked();

    void on_endHalfWaveRadioH_clicked();

    void on_sensitivityRadioH_clicked();

    void on_pushButton_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::DialogDefectMethodSelect *ui;

    int m_lengthMeasureMethod {0};
    int m_heightMeasureMethod {0};
    double m_scale {50.0};
};

#endif // DIALOGDEFECTMETHODSELECT_H
