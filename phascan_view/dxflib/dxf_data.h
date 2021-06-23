#ifndef DXF_DATA_H
#define DXF_DATA_H

#include "dl_creationadapter.h"
#include <QList>

class Dxf_Data : public DL_CreationAdapter {

public:
    Dxf_Data();

    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);//2
    virtual void addArc(const DL_ArcData& data);//3
    virtual void addCircle(const DL_CircleData& data); //4
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data); //6
    virtual void addMText(const DL_MTextData& data);//7
    virtual void addEllipse(const DL_EllipseData& data);
    virtual void addText(const DL_TextData& data); //9

    virtual void addSpline(const DL_SplineData& data);
    virtual void addControlPoint(const DL_ControlPointData& data);//11

    virtual void addInsert(const DL_InsertData& data);
    virtual void addComment(const std::string& data);
    virtual void addXLine(const DL_XLineData& data);
    virtual void addRay(const DL_RayData& data);

    virtual void add3dFace(const DL_3dFaceData& data);
    void printAttributes();

    const QList<DL_LineData> &getLineList() const;
    const QList<DL_ArcData> &getArcList() const;
    const QList<DL_MTextData> &getTextList() const;
    const QList<DL_EllipseData> &getEllipseList() const;
    const QList<DL_CircleData> &getCircleList() const;
    const QList<DL_TextData> &getTextDataList() const;
    const QList<DL_VertexData> &getVertexList() const;
    const QList<DL_SplineData> &getSplineList() const;
    const QList<DL_ControlPointData> &getControlPointList() const;
    const QList<DL_PointData> &getPointList() const;
    const QList<DL_PolylineData> &getPolyLineList() const;

private:
    QList<DL_PointData> m_pointList;
    QList<DL_LineData> m_lineList;
    QList<DL_ArcData> m_arcList;
    QList<DL_TextData> m_textDataList;
    QList<DL_MTextData> m_textList;
    QList<DL_EllipseData> m_ellipseList;
    QList<DL_CircleData> m_circleList;
    QList<DL_VertexData> m_vertexList;
    QList<DL_PolylineData> m_polyLineList;
    QList<DL_SplineData> m_splineList;
    QList<DL_ControlPointData> m_controlPointList;
};

#endif
