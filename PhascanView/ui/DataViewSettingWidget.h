#ifndef DATAVIEWSETTINGWIDGET_H
#define DATAVIEWSETTINGWIDGET_H

#include <QWidget>
#include <DopplerView/DopplerDataView.h>

class QPushButton ;
class QSlider     ;
class QLabel      ;


class DataViewSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataViewSettingWidget(QWidget *parent = 0);
    ~DataViewSettingWidget();
protected:
    DopplerDataView*    m_pView      ;
    QPushButton*        m_pBtnMinus  ;
    QPushButton*        m_pBtnPlus   ;
    QSlider*            m_pSlider    ;
    QLabel*             m_pLabel     ;

signals:
    
public slots:
    void slotButtonMinusClicked() ;
    void slotButtonPlusClicked()  ;
    void slotSliderValueChanged(int) ;

};

#endif // DATAVIEWSETTINGWIDGET_H
