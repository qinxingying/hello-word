/***************************
  Name:  DopplerColorIndex
  Description:    用于加载XML格式的颜色文件
************************************/

#ifndef DOPPLERCOLORINDEX_H
#define DOPPLERCOLORINDEX_H

#include <QObject>
#define  COLOR_INDEX_LENGTH    256

class DopplerColorIndex : public QObject
{
    Q_OBJECT
public:
    explicit DopplerColorIndex(QObject *parent = 0);
    DopplerColorIndex(QString* str , QObject* parent = 0) ;
    void SetColorIndex(unsigned char*  color[3] , int nQty_) ;
    void GetColorValue(int* r , int* g , int* b , int index_) const;
    void* GetColorIndex()  const;

    void LoadPallete(QString str_) ;


protected:
    unsigned char m_aColorIndex[COLOR_INDEX_LENGTH][3]  ;

signals:

public slots:


};

#endif // DOPPLERCOLORINDEX_H
