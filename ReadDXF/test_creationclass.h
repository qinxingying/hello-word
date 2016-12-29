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

    DRAW_LINE getLine() const;
    void setLine(const DRAW_LINE &line);

private:
    DRAW_LINE m_line;
  //  QList<DRAW_LINE> m_lineList;
};

#endif
