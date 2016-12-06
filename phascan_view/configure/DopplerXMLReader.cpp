#include "DopplerXMLReader.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>

DopplerXMLReader::DopplerXMLReader(QObject *parent) :
    QObject(parent)
{
}


void DopplerXMLReader::LoadMaterial(QString* str_ , QList<MATERIAL*>* list_)
{
    if(str_->isEmpty())  return ;
    QFile _file(*str_);

    if(_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml (&_file) ;
        do
        {
            xml.readNext() ;
            if(xml.isStartElement() && (xml.name() == "Materials") )
                break  ;
        }while(!xml.atEnd()) ;

        do
        {
            xml.readNext() ;
            if(xml.isStartElement() && (xml.name() == "Material") )
            {
                MATERIAL* _pNew = new MATERIAL() ;
                float _value1 = xml.attributes().value("VelocityL").toString().toFloat() ;
                float _value2 = xml.attributes().value("VelocityT").toString().toFloat() ;
                float _value3 = xml.attributes().value("Density").toString().toFloat() ;

                _pNew->fVelocityLon = _value1 ;
                _pNew->fVelocityTran= _value2 ;
                _pNew->fDensity     = _value3 ;

                QString     _str0 = xml.attributes().value("EN").toString();
                std::string _str1 = _str0.toStdString();
                const char* _str2 = _str1.c_str();
                if(_str2) {
                    memcpy(_pNew->strName[0] , (char*)_str2 , strlen(_str2)< 63 ?strlen(_str2): 63)  ;
                }

                _str0 = xml.attributes().value("CHS").toString();
                _str1 = _str0.toStdString();
                _str2 = _str1.c_str();
                if(_str2) {
                    memcpy(_pNew->strName[1] , (char*)_str2 , strlen(_str2)< 63 ?strlen(_str2): 63)  ;
                }

                _str0 = xml.attributes().value("KOR").toString();
                _str1 = _str0.toStdString();
                _str2 = _str1.c_str();
                if(_str2) {
                    memcpy(_pNew->strName[2] , (char*)_str2 , strlen(_str2)< 63 ?strlen(_str2): 63)  ;
                }

                _str0 = xml.attributes().value("JP").toString();
                _str1 = _str0.toStdString();
                _str2 = _str1.c_str();
                if(_str2) {
                    memcpy(_pNew->strName[3] , (char*)_str2 , strlen(_str2)< 63 ?strlen(_str2): 63)  ;
                }
                list_->append(_pNew);
            }
        }while(!xml.atEnd()) ;
    }
}


void DopplerXMLReader::LoadWedgeFile(QString* str_ , WEDGE_CONFIG* wedge_)
{
    if(str_->isEmpty())  return ;
    QFile _file(*str_);
    if(_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml (&_file) ;
        do
        {
            xml.readNext() ;
            if(xml.isStartElement() && (xml.name() == "WEDGE") )
               break ;
        }while(!xml.atEnd()) ;

        memset((void*)wedge_ , 0 , sizeof(WEDGE_CONFIG)) ;
        do
        {
            xml.readNext() ;
            if(!xml.isStartElement()) continue ;
            if(xml.name() == "wedge")
            {
                char* str1 = xml.attributes().value("name").toString().toLatin1().data() ;
                if(str1) memcpy(wedge_->strName , (char*)str1 , strlen(str1)< 64 ?strlen(str1): 64 )  ;
                //qDebug("%s" , str1);
            }
            else if(xml.name() == "serial")
            {
                char * str1 = xml.attributes().value("value").toString().toLatin1().data() ;
                if(str1) memcpy(wedge_->strSerial , (char*)str1 , strlen(str1)< 64 ?strlen(str1): 64 )  ;
                //qDebug("%s" , str1);
            }
            else if(xml.name() == "type")
            {
                char * str1 = xml.attributes().value("value").toString().toLatin1().data() ;
                wedge_->eType = ((!strcmp(str1 , "PA"))||(!strcmp(str1 , "pa"))) ? setup_WEDGE_TYPE_PA: setup_WEDGE_TYPE_UT   ;
                //qDebug("%s %d" , str1 , wedge_->eType);
            }
            else if(xml.name() == "angle")
            {
                float _value1 = 0 , _value2 = 0 ;
                _value1 = xml.attributes().value("wedge").toString().toFloat() ;
                _value2 = xml.attributes().value("roof").toString().toFloat() ;
                wedge_->fWedgeAngle = _value1 ;
                wedge_->fRoofAngle  = _value2 ;
            }
            else if(xml.name() == "velocity")
            {
                float _value1 = 2330 , _value2 = 2330 ;
                _value1 = xml.attributes().value("lon").toString().toFloat() ;
                _value2 = xml.attributes().value("tra").toString().toFloat() ;
                wedge_->fVelocityLon = _value1 ;
                wedge_->fVelocityTra = _value2 ;
            }
            else if(xml.name() == "offset")
            {
                float _value1 = 0 , _value2 = 0 , _value3 = 0 ;
                _value1 = xml.attributes().value("fir").toString().toFloat() ;
                _value2 = xml.attributes().value("sec").toString().toFloat() ;
                _value3 = xml.attributes().value("firstheight").toString().toFloat() ;
                wedge_->fOffsetFir  = _value1 ;
                wedge_->fOffsetSec  = _value2 ;
                wedge_->fHeigtFirst = _value3 ;
            }
            else if(xml.name() == "size")
            {
                float _value1 = 0 , _value2 = 0 , _value3 = 0 ;
                _value1 = xml.attributes().value("length").toString().toFloat() ;
                _value2 = xml.attributes().value("width").toString().toFloat() ;
                _value3 = xml.attributes().value("height").toString().toFloat() ;
                wedge_->fLength  = _value1 ;
                wedge_->fWidth  = _value2 ;
                wedge_->fHeight = _value3 ;
            }
            else if(xml.name() == "size")
            {
                float _value1 = 0 , _value2 = 0 , _value3 = 0 ;
                _value1 = xml.attributes().value("length").toString().toFloat() ;
                _value2 = xml.attributes().value("width").toString().toFloat() ;
                _value3 = xml.attributes().value("height").toString().toFloat() ;
                wedge_->fLength  = _value1 ;
                wedge_->fWidth  = _value2 ;
                wedge_->fHeight = _value3 ;
            }
            else if(xml.name() == "UT")
            {
                float _value1 = 0 ; int _value2 = 0 ;
                _value1 = xml.attributes().value("length").toString().toFloat() ;
                _value2 = xml.attributes().value("width").toString().toInt() ;
                wedge_->fRefPoint    = _value1 ;
                wedge_->nWedgeDelay  = _value2 ;
            }
            else if(xml.name() == "direction")
            {
                wedge_->eDirection = xml.attributes().value("value").toString().toInt()?
                            setup_WEDGE_ORIENTATION_REVERSE : setup_WEDGE_ORIENTATION_NORMAL;

            }
        }while(!xml.atEnd()) ;
    }
}

void DopplerXMLReader::LoadProbeFile(QString* str_ , PROBE_CONFIG* probe_)
{
    if(str_->isEmpty())  return ;
    QFile _file(*str_);
    if(_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml (&_file) ;
        do
        {
            xml.readNext() ;
            if(xml.isStartElement() && (xml.name() == "PROBE") )
               break ;
        }while(!xml.atEnd()) ;

        memset((void*)probe_ , 0 , sizeof(PROBE_CONFIG)) ;
        do
        {
            xml.readNext() ;
            if(!xml.isStartElement()) continue ;
            if(xml.name() == "probe")
            {
                char* str1 = xml.attributes().value("name").toString().toLatin1().data() ;
                if(str1) memcpy(probe_->strName , (char*)str1 , strlen(str1)< 64 ?strlen(str1): 64 )  ;
            }
            else if(xml.name() == "serial")
            {
                char * str1 = xml.attributes().value("value").toString().toLatin1().data() ;
                if(str1) memcpy(probe_->strSerial , (char*)str1 , strlen(str1)< 64 ?strlen(str1): 64 )  ;

            }
            else if(xml.name() == "element")
            {
                int _value1 = 0 , _value2 = 0 ;
                _value1 = xml.attributes().value("fir").toString().toInt() ;
                _value2 = xml.attributes().value("sec").toString().toInt() ;
                probe_->nElementPri  = _value1 ;
                probe_->nElementSec  = _value2 ;
            }
            else if(xml.name() == "pitch")
            {
                float _value1 = 0 , _value2 = 0 ;
                _value1 = xml.attributes().value("fir").toString().toFloat() ;
                _value2 = xml.attributes().value("sec").toString().toFloat() ;
                probe_->fPitchPri  = _value1 ;
                probe_->fPitchSec  = _value2 ;
            }
            else if(xml.name() == "size")
            {
                float _value1 = 0 , _value2 = 0 ;
                _value1 = xml.attributes().value("fir").toString().toFloat() ;
                _value2 = xml.attributes().value("sec").toString().toFloat() ;
                probe_->fSizePri  = _value1 ;
                probe_->fSizeSec  = _value2 ;
            }
            else if(xml.name() == "frequency")
            {
                float _value1 = 0 ;
                _value1 = xml.attributes().value("value").toString().toFloat() ;
                probe_->fFrequency  = _value1 ;
            }
            else if(xml.name() == "location")
            {
                int _value1 = xml.attributes().value("value").toString().toFloat() ;
                probe_->nLocationPolicy = _value1   ;
            }
        }while(!xml.atEnd()) ;
    }
}

void DopplerXMLReader::SaveWedgeFile(QString*, WEDGE_CONFIG*) //(QString* str_ , WEDGE_CONFIG* wedge_)
{

}

void DopplerXMLReader::SaveProbeFile(QString*, PROBE_CONFIG*)//(QString* str_ , PROBE_CONFIG* probe_)
{

}
