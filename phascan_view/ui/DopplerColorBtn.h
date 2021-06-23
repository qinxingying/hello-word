/**********************************
  Description: 带颜色条显示的按钮
**********************************/

#ifndef DOPPLERCOLORBTN_H
#define DOPPLERCOLORBTN_H


#include <QPushButton>

class DopplerColorBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit DopplerColorBtn(QWidget *parent = 0);
    void SetColorIndex(void*);

protected:
    unsigned char m_aColorIndex[256][3]  ;
    void paintEvent (QPaintEvent* ) ;
signals:

public slots:

};

#endif // DOPPLERCOLORBTN_H
