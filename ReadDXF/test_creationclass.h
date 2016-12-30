#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include <QPainter>

typedef struct ADD_LINE
{
    float x1;
    float y1;
    float x2;
    float y2;
}DRAW_LINE;

typedef struct ADD_ARC
{
    double cx;
    double cy;

    double radius;
    /*! Startangle of arc in degrees. */
    double angle1;
    /*! Endangle of arc in degrees. */
    double angle2;
}DRAW_ARC;

class Test_CreationClass : public DL_CreationAdapter {

public:
    Test_CreationClass();

    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void add3dFace(const DL_3dFaceData& data);
    void printAttributes();

    QList<DRAW_LINE> getLineList() const;
    void setLineList(const QList<DRAW_LINE> &lineList);

    QList<DRAW_ARC> getArcList() const;
    void setArcList(const QList<DRAW_ARC> &arcList);

private:
    QList<DRAW_LINE> m_lineList;
    QList<DRAW_ARC> m_arcList;
};

#endif
