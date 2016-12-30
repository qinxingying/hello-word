#include "test_creationclass.h"

#include <iostream>
#include <stdio.h>
#include <QDebug>

Test_CreationClass::Test_CreationClass() {
//    m_line.x1 = 0;
//    m_line.y1 = 0;
//    m_line.x2 = 0;
//    m_line.y2 = 0;
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

/**
 * Sample implementation of the method which handles line entities.
 */
void Test_CreationClass::addLine(const DL_LineData& data) {
    printf("LINE(---)     (%6.3f, %6.3f, %6.3f) (%6.3f, %6.3f, %6.3f)\n",
           data.x1, data.y1, data.z1, data.x2, data.y2, data.z2);
    printAttributes();

    DRAW_LINE line = {0.0, 0.0, 0.0, 0.0};
    line.x1 = data.x1;
    line.y1 = data.y1;
    line.x2 = data.x2;
    line.y2 = data.y2;

    m_lineList.append(line);
}

/**
 * Sample implementation of the method which handles arc entities.
 */
void Test_CreationClass::addArc(const DL_ArcData& data) {
    printf("ARC ( )     (%6.3f, %6.3f, %6.3f) %6.3f, %6.3f, %6.3f\n",
           data.cx, data.cy, data.cz,
           data.radius, data.angle1, data.angle2);
    printAttributes();

    DRAW_ARC arc = {0.0, 0.0, 0.0, 0.0, 0.0};
    arc.cx = data.cx;
    arc.cy = data.cy;
    arc.radius = data.radius;
    arc.angle1 = data.angle1;
    arc.angle2 = data.angle2;
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void Test_CreationClass::addCircle(const DL_CircleData& data) {
    printf("CIRCLE   (%6.3f, %6.3f, %6.3f) %6.3f\n",
           data.cx, data.cy, data.cz,
           data.radius);
    printAttributes();
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void Test_CreationClass::addPolyline(const DL_PolylineData& data) {
    printf("POLYLINE \n");
    printf("flags: %d\n", (int)data.flags);
    printAttributes();
}

/**
 * Sample implementation of the method which handles vertices.
 */
void Test_CreationClass::addVertex(const DL_VertexData& data) {
    printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f\n",
           data.x, data.y, data.z,
           data.bulge);
    printAttributes();
}


void Test_CreationClass::add3dFace(const DL_3dFaceData& data) {
    printf("3DFACE\n");
    for (int i=0; i<4; i++) {
        printf("   corner %d: %6.3f %6.3f %6.3f\n", 
            i, data.x[i], data.y[i], data.z[i]);
    }
    printAttributes();
}

void Test_CreationClass::addText(const DL_TextData &data)
{
    qDebug()<<"**************TEXT*************\n text ="<<data.text.c_str()<<"  \n style= "<<data.style.c_str();
}

void Test_CreationClass::addMText(const DL_MTextData &data)
{
    qDebug()<<"**************MTEXT*************\n"<<data.angle<<"  height "<<data.height<<"\n style:"<<data.style.c_str()<<"text:"<<data.text.c_str();

    DRAW_MTEXT text = {0, 0, 0, 0, 0, 0, ""};
    text.x = data.ipx;
    text.y = data.ipy;
    text.dirx = data.dirx;
    text.diry = data.diry;
    text.width = data.width;
    text.height = data.height;
    text.text = data.text.c_str();
}

void Test_CreationClass::addLeader(const DL_LeaderData &data)
{
    qDebug()<<"**************Arrow*************\n"<<data.arrowHeadFlag<<"  numer = "<<data.number<<data.textAnnotationWidth;
    printAttributes();
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

QList<DRAW_LINE> Test_CreationClass::getLineList() const
{
    return m_lineList;
}

void Test_CreationClass::setLineList(const QList<DRAW_LINE> &lineList)
{
    m_lineList = lineList;
}

QList<DRAW_ARC> Test_CreationClass::getArcList() const
{
    return m_arcList;
}

void Test_CreationClass::setArcList(const QList<DRAW_ARC> &arcList)
{
    m_arcList = arcList;
}

QList<DRAW_MTEXT> Test_CreationClass::getTextList() const
{
    return m_textList;
}

void Test_CreationClass::setTextList(const QList<DRAW_MTEXT> &textList)
{
    m_textList = textList;
}

// EOF
