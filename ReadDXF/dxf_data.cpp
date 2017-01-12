#include "dxf_data.h"

#include <iostream>
#include <stdio.h>
#include <QDebug>

Dxf_Data::Dxf_Data() {

}

/**
 * Sample implementation of the method which handles layers.
 */
void Dxf_Data::addLayer(const DL_LayerData& data) {
    printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    printAttributes();
}

/**
 * Sample implementation of the method which handles point entities.
 */
void Dxf_Data::addPoint(const DL_PointData& data)
{
    printAttributes();
    m_pointList.append(data);
qDebug()<<"\n *****AddPoint(1)*****\n --- x,y,z = "<<data.x<<data.y<<data.z;
}

void Dxf_Data::addLine(const DL_LineData& data)
{
    printAttributes();
    m_lineList.append(data);
qDebug()<<"\n *****AddLine(2)*****\n --- x1,y1 = "<<data.x1<<data.y1<<"\n x2,y2 ="<<data.x2<<data.y2;
}

void Dxf_Data::addArc(const DL_ArcData& data)
{
    printAttributes();
    m_arcList.append(data);
qDebug()<<"\n *****AddArc(3)*****\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius,Angle1,Angle2 ="<<data.radius<<data.angle1<<data.angle2;
}

void Dxf_Data::addCircle(const DL_CircleData& data)
{
    printAttributes();
    m_circleList.append(data);
qDebug()<<"\n *******AddCircle(4)********\n --- cx,y,z = ("<<data.cx<<data.cy<<data.cz<<") \n radius ="<<data.radius;
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void Dxf_Data::addPolyline(const DL_PolylineData& data)
{
    printAttributes();
    m_polyLineList.append(data);
qDebug()<<"\n *******AddPolyline(5)********\n --- num,m,n ="<<data.number<<data.m<<data.n<<"\n flag ="<<data.flags;
}

/**
 * Sample implementation of the method which handles vertices.
 */
void Dxf_Data::addVertex(const DL_VertexData& data)
{
    printAttributes();
    m_vertexList.append(data);
qDebug()<<"\n *******AddVertex(6)********\n ---x, y, z, bulge="<<data.x<<data.y<<data.z<<data.bulge;
}

void Dxf_Data::addMText(const DL_MTextData &data)
{
    printAttributes();
    m_textList.append(data);
qDebug()<<"\n *******AddMText(7)********\n ---ipx, y ="<<data.ipx<<data.ipy;
qDebug()<<"width, height ="<<data.width<<data.height<<" \n TEXT ="<<data.text.c_str();
}

void Dxf_Data::addEllipse(const DL_EllipseData &data)
{
    m_ellipseList.append(data);
qDebug()<<"\n *******AddEllipse(8)********\n ---cx,y ="<<data.cx<<data.cy<<"\n mx,y ="<<data.mx<<data.my;
qDebug()<<"ratio ="<<data.ratio<<"angle1,2 ="<<data.angle1<<data.angle2;
}

void Dxf_Data::addText(const DL_TextData &data)
{
    m_textDataList.append(data);
qDebug()<<"\n *****AddText(9)****\n ---text ="<<data.text.c_str()<<"factor = "<<data.xScaleFactor;
qDebug()<<"ipx,y = "<<data.ipx<<data.ipy<<"apx,y ="<<data.apx<<data.apy;
qDebug()<<"angle, height, hJustification,v="<<data.angle<<data.height<<data.hJustification<<data.vJustification;
}

void Dxf_Data::addSpline(const DL_SplineData &data)
{
    m_splineList.append(data);
    qDebug()<<"\n *****addSpline(10)****\n ---degree,nfits,nknots ="<<data.degree<<data.nFit<<data.nKnots;
    qDebug()<<"tangentStartX,Y ="<<data.tangentStartX<<data.tangentStartY<<"\n tangentEndX,Y ="<<data.tangentEndX<<data.tangentEndY;
}

void Dxf_Data::addControlPoint(const DL_ControlPointData &data)
{
    m_controlPointList.append(data);
    qDebug()<<"\n *****AddControlPoint(11)****\n ---x,y,z,w ="<<data.x<<data.y<<data.z<<data.w;
}

void Dxf_Data::addInsert(const DL_InsertData &data)
{
qDebug()<<"\n *****TEST-1***\n ---name ="<<data.name.c_str();
}

void Dxf_Data::addComment(const std::string &data)
{
qDebug()<<"\n *****TEST-2****\n ---text ="<<data.c_str();
}

void Dxf_Data::addXLine(const DL_XLineData &data)
{
qDebug()<<"\n *****TEST-3****\n ---bx ="<<data.bx;
}

void Dxf_Data::addRay(const DL_RayData &data)
{
qDebug()<<"\n *****TEST-4****\n ---bx ="<<data.bx;
}

void Dxf_Data::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n",
            i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}

void Dxf_Data::printAttributes() {
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

QList<DL_LineData> Dxf_Data::getLineList() const
{
    return m_lineList;
}

void Dxf_Data::setLineList(const QList<DL_LineData> &lineList)
{
    m_lineList = lineList;
}

QList<DL_ArcData> Dxf_Data::getArcList() const
{
    return m_arcList;
}

void Dxf_Data::setArcList(const QList<DL_ArcData> &arcList)
{
    m_arcList = arcList;
}

QList<DL_MTextData> Dxf_Data::getTextList() const
{
    return m_textList;
}

void Dxf_Data::setTextList(const QList<DL_MTextData> &textList)
{
    m_textList = textList;
}

QList<DL_EllipseData> Dxf_Data::getEllipseList() const
{
    return m_ellipseList;
}

void Dxf_Data::setEllipseList(const QList<DL_EllipseData> &ellipseList)
{
    m_ellipseList = ellipseList;
}

QList<DL_CircleData> Dxf_Data::getCircleList() const
{
    return m_circleList;
}

void Dxf_Data::setCircleList(const QList<DL_CircleData> &circleList)
{
    m_circleList = circleList;
}

QList<DL_TextData> Dxf_Data::getTextDataList() const
{
    return m_textDataList;
}

void Dxf_Data::setTextDataList(const QList<DL_TextData> &textDataList)
{
    m_textDataList = textDataList;
}

QList<DL_VertexData> Dxf_Data::getVertexList() const
{
    return m_vertexList;
}

void Dxf_Data::setVertexList(const QList<DL_VertexData> &vertexList)
{
    m_vertexList = vertexList;
}

QList<DL_SplineData> Dxf_Data::getSplineList() const
{
    return m_splineList;
}

void Dxf_Data::setSplineList(const QList<DL_SplineData> &splineList)
{
    m_splineList = splineList;
}

QList<DL_ControlPointData> Dxf_Data::getControlPointList() const
{
    return m_controlPointList;
}

void Dxf_Data::setControlPointList(const QList<DL_ControlPointData> &controlPointList)
{
    m_controlPointList = controlPointList;
}

QList<DL_PointData> Dxf_Data::getPointList() const
{
    return m_pointList;
}

void Dxf_Data::setPointList(const QList<DL_PointData> &pointList)
{
    m_pointList = pointList;
}

QList<DL_PolylineData> Dxf_Data::getPolyLineList() const
{
    return m_polyLineList;
}

void Dxf_Data::setPolyLineList(const QList<DL_PolylineData> &polyLineList)
{
    m_polyLineList = polyLineList;
}

// EOF
