#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include <QPainter>

typedef struct ADD_LINE
{
    double x1;
    double y1;
    double x2;
    double y2;
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

typedef struct ADD_MTEXT
{
    double x;
    double y;
    double dirx;
    double diry;
    double height;
    double width;
    QString text;
}DRAW_MTEXT;

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

    virtual void addText(const DL_TextData& data);
    virtual void addMText(const DL_MTextData& data);
    virtual void addLeader(const DL_LeaderData& data);
    virtual void addLeaderVertex(const DL_LeaderVertexData& data);

    QList<DRAW_LINE> getLineList() const;
    void setLineList(const QList<DRAW_LINE> &lineList);

    QList<DRAW_ARC> getArcList() const;
    void setArcList(const QList<DRAW_ARC> &arcList);

    QList<DRAW_MTEXT> getTextList() const;
    void setTextList(const QList<DRAW_MTEXT> &textList);

private:
    QList<DRAW_LINE> m_lineList;
    QList<DRAW_ARC> m_arcList;
    QList<DRAW_MTEXT> m_textList;
};

#endif
