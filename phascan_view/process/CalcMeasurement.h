/***************************
  Class Name :  CalcMeasurement
  Description:  calculate class for measures (%A, PA , SA , SB .....)
************************************/

#ifndef CALCMEASUREMENT_H
#define CALCMEASUREMENT_H

#include <QObject>
#include <QString>
#include <configure/const.h>


class CalcMeasurement : public QObject
{
    Q_OBJECT
public:
    explicit CalcMeasurement(QObject *parent = 0) ;
    static int Calc(int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ , float* pResult_);
    static QString GetZAValue(float _fValue);
    static QString GetMeasureValueString(int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ );
	static QString GetMeasureValueSimpleString (int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ );
    static QString GetMeasureValueWithUnit(int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ );
    static const char* GetMeasureNameString(int nGroupId_ , FEILD_VALUE_INDEX eIndex_) ;
    static const char* GetMeasureContentString(int nGroupId_ , FEILD_VALUE_INDEX eIndex_) ;
    static QString GetMeasureString(int nGroupId_ , FEILD_VALUE_INDEX eIndex_);
    static QString GetMeasureUnit(FEILD_VALUE_INDEX eIndex_ ) ;
    //static QString GetMeasureValue(int nGroupId_ , int nLaw_ , FEILD_VALUE_INDEX eIndex_ );
protected:
#if 0
    static int CalGateAmp(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGateAmp2Height(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGateAmp2Ref(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGateAmp(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGateAmp2Height(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGateAmp2Ref(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGatePos(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGatePos(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalGatePos(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalIEdgeInWater(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalcThicknessAPos(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
    static int CalcML(int nGroupId_ , int nLaw_ , int nGate_ , float* pResult_ );
#endif
signals:

public slots:

};






#endif // CALCMEASUREMENT_H
