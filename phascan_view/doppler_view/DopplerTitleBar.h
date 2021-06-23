#ifndef DOPPLERTITLEBAR_H
#define DOPPLERTITLEBAR_H

#include <QWidget>

#define DOPPLER_TITLE_BAR_HEIGHT    15

class DopplerTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit DopplerTitleBar(QWidget *parent = 0);
    void SetBackgroudColor(QColor& cColor_);
    void SetTextColor(QColor& cColor_)   ;
    void SetTitle(QString& strTitle_) ;

protected:
    QColor         m_cBgColor ;
    QColor         m_cFgColor ;
    QString        m_strTitle ;
    void paintEvent(QPaintEvent* cEvent_);
signals:

public slots:

};

#endif // DOPPLERTITLEBAR_H
