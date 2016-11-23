/*******************
  Name:  DopplerColorBtn
  Copyright: Sheng Shen
  Date : 2013-08-26
  Description:   ����ɫ����ʾ�İ�ť
                 .............
**********************/

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
