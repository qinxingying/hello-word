#include "DopplerColorIndex.h"
#include <QXmlStreamReader>
#include <QFile>

DopplerColorIndex::DopplerColorIndex(QObject *parent) :
    QObject(parent)
{
    for(int i = 0 ; i < COLOR_INDEX_LENGTH ; i++)
    {
        m_aColorIndex[i][0] =  i    ;
        m_aColorIndex[i][1] =     0 ;
        m_aColorIndex[i][2] = 255 - i ;
    }
}

DopplerColorIndex::DopplerColorIndex(QString* str_ , QObject* parent):QObject(parent)
{
    LoadPallete(*str_);
}

void DopplerColorIndex::SetColorIndex(unsigned char*  color[3] , int nQty_)
{
    if(!color)  return ;

    if(nQty_ > COLOR_INDEX_LENGTH)
         nQty_ = COLOR_INDEX_LENGTH  ;

    for(int i = 0 ; i < nQty_ ; i++)
    {
        m_aColorIndex[i][0] = color[i][0] ;
        m_aColorIndex[i][1] = color[i][0] ;
        m_aColorIndex[i][2] = color[i][0] ;
    }
}


void DopplerColorIndex::GetColorValue(int* r , int* g , int* b , int index_) const
{
    *r = m_aColorIndex[index_][0] ;
    *g = m_aColorIndex[index_][1] ;
    *b = m_aColorIndex[index_][2] ;
}


void* DopplerColorIndex::GetColorIndex() const
{
    return (void*)m_aColorIndex ;
}

void DopplerColorIndex::LoadPallete(QString str_)
{
    if(str_.isEmpty())  return ;
    QFile _file(str_);
    if(_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml (&_file)  ;
        int _nIndex = 0 ;
        do
        {
            xml.readNext() ;
            if(xml.isStartElement() && (xml.name() == "MainColors"))
            {
                do
                {
                    xml.readNext() ;
                    if(xml.isStartElement() && (xml.name() == "Color") )
                    {
                        if(_nIndex < COLOR_INDEX_LENGTH)
                        {
                            m_aColorIndex[_nIndex][0]   = xml.attributes().value("R").toString().toInt() ;
                            m_aColorIndex[_nIndex][1]   = xml.attributes().value("G").toString().toInt() ;
                            m_aColorIndex[_nIndex][2]   = xml.attributes().value("B").toString().toInt() ;
                        }
                        _nIndex ++  ;
                    }
                }while(!xml.atEnd()) ;
            }

        }while(!xml.atEnd());

    }
}
