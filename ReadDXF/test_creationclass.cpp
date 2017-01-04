#include "test_creationclass.h"

#include <iostream>
#include <stdio.h>
#include <QDebug>

Test_CreationClass::Test_CreationClass() {

}

/**
 * Sample implementation of the method which handles layers.
 */
void Test_CreationClass::addLayer(const DL_LayerData& data) {
    printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    printAttributes();
}

/**
 * Sample implementation of the method which handles point entities.
 */
void Test_CreationClass::addPoint(const DL_PointData& data) {
    printf("POINT(...)    (%6.3f, %6.3f, %6.3f)\n",
           data.x, data.y, data.z);
    printAttributes();
}

void Test_CreationClass::addLine(const DL_LineData& data)
{
    printAttributes();
    m_lineList.append(data);
}

void Test_CreationClass::addArc(const DL_ArcData& data)
{
    printAttributes();
    m_arcList.append(data);
qDebug()<<"\n *****Arc*****\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius,Angle1,Angle2 ="<<data.radius<<data.angle1<<data.angle2;
}

void Test_CreationClass::addCircle(const DL_CircleData& data)
{
    printAttributes();
    m_circleList.append(data);

qDebug()<<"\n *******Circle********\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius ="<<data.radius;
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void Test_CreationClass::addPolyline(const DL_PolylineData& data)
{
    printAttributes();
qDebug()<<"\n *******Polyline********\n --- num,m,n ="<<data.number<<data.m<<data.n<<"\n flag ="<<data.flags;
}

/**
 * Sample implementation of the method which handles vertices.
 */
void Test_CreationClass::addVertex(const DL_VertexData& data)
{
    printAttributes();
    m_vertexList.append(data);
qDebug()<<"\n *******addVertex********\n ---x, y, z, bulge="<<data.x<<data.y<<data.z<<data.bulge;
}


void Test_CreationClass::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n", 
            i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}

void Test_CreationClass::addMText(const DL_MTextData &data)
{
    printAttributes();
    m_textList.append(data);
qDebug()<<"\n *******MTEXT********\n ---ipx, y ="<<data.ipx<<data.ipy<<"\n width, height ="<<data.width<<data.height<<" \n TEXT ="<<data.text.c_str();
}

void Test_CreationClass::addEllipse(const DL_EllipseData &data)
{
    m_ellipseList.append(data);
qDebug()<<"\n *******Ellipse********\n ---cx,y ="<<data.cx<<data.cy<<"\n mx,y ="<<data.mx<<data.my<<"\n ratio ="<<data.ratio;
qDebug()<<"angle1,2 ="<<data.angle1<<data.angle2;
}

void Test_CreationClass::addText(const DL_TextData &data)
{
    m_textDataList.append(data);
qDebug()<<"\n *****addText****\n ---text ="<<data.text.c_str()<<"\n factor = "<<data.xScaleFactor;
qDebug()<<"\n angle, height, hJustification,v="<<data.angle<<data.height<<data.hJustification<<data.vJustification;
}

void Test_CreationClass::addInsert(const DL_InsertData &data)
{
qDebug()<<"\n *****TEST-1***\n ---name ="<<data.name.c_str();
}

void Test_CreationClass::addComment(const std::string &data)
{
qDebug()<<"\n *****TEST-2****\n ---text ="<<data.c_str();
}

void Test_CreationClass::addXLine(const DL_XLineData &data)
{
qDebug()<<"\n *****TEST-3****\n ---bx ="<<data.bx;
}

void Test_CreationClass::addRay(const DL_RayData &data)
{
qDebug()<<"\n *****TEST-4****\n ---bx ="<<data.bx;
}

void Test_CreationClass::printAttributes() {
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)	{
        printf("BYLAYER");
    } else if (attributes.getColor()==0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1) {
        printf("BYLAYER");
    } else if (attributes.getWidth()==-2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth()==-3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLinetype().c_str());
}

QList<DL_LineData> Test_CreationClass::getLineList() const
{
    return m_lineList;
}

void Test_CreationClass::setLineList(const QList<DL_LineData> &lineList)
{
    m_lineList = lineList;
}

QList<DL_ArcData> Test_CreationClass::getArcList() const
{
    return m_arcList;
}

void Test_CreationClass::setArcList(const QList<DL_ArcData> &arcList)
{
    m_arcList = arcList;
}

QList<DL_MTextData> Test_CreationClass::getTextList() const
{
    return m_textList;
}

void Test_CreationClass::setTextList(const QList<DL_MTextData> &textList)
{
    m_textList = textList;
}

QList<DL_EllipseData> Test_CreationClass::getEllipseList() const
{
    return m_ellipseList;
}

void Test_CreationClass::setEllipseList(const QList<DL_EllipseData> &ellipseList)
{
    m_ellipseList = ellipseList;
}

QList<DL_CircleData> Test_CreationClass::getCircleList() const
{
    return m_circleList;
}

void Test_CreationClass::setCircleList(const QList<DL_CircleData> &circleList)
{
    m_circleList = circleList;
}

QList<DL_TextData> Test_CreationClass::getTextDataList() const
{
    return m_textDataList;
}

void Test_CreationClass::setTextDataList(const QList<DL_TextData> &textDataList)
{
    m_textDataList = textDataList;
}

QList<DL_VertexData> Test_CreationClass::getVertexList() const
{
    return m_vertexList;
}

void Test_CreationClass::setVertexList(const QList<DL_VertexData> &vertexList)
{
    m_vertexList = vertexList;
}

// EOF
