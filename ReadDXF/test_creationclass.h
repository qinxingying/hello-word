#ifndef TEST_CREATIONCLASS_H
#define TEST_CREATIONCLASS_H

#include "dl_creationadapter.h"
#include <QPainter>

class Test_CreationClass : public DL_CreationAdapter {

public:
    Test_CreationClass();

    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);//1
    virtual void addArc(const DL_ArcData& data);//2
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void add3dFace(const DL_3dFaceData& data);
    void printAttributes();

    virtual void addText(const DL_TextData& data);
    virtual void addMText(const DL_MTextData& data);//3
    virtual void addLeader(const DL_LeaderData& data);
    virtual void addLeaderVertex(const DL_LeaderVertexData& data);

    QList<DL_LineData> getLineList() const;
    void setLineList(const QList<DL_LineData> &lineList);

    QList<DL_ArcData> getArcList() const;
    void setArcList(const QList<DL_ArcData> &arcList);

    QList<DL_MTextData> getTextList() const;
    void setTextList(const QList<DL_MTextData> &textList);

private:
    QList<DL_LineData> m_lineList;
    QList<DL_ArcData> m_arcList;
    QList<DL_MTextData> m_textList;
};

#endif
