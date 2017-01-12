#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "dxf_data.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_dxfImage->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    ui->widget_dxfImage->setPalette(palette);

    connect(ui->widget_dxfImage, SIGNAL(zoom(double)), this, SLOT(slot_doubleSpinBox_setValue(double)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_openFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
                            "Open File Dialog",
                            "",
                            "Part Files(*.dxf)");

    if(fileName.isEmpty())  return;

    Dxf_Data* dxfData = new Dxf_Data();
    DL_Dxf* dxf = new DL_Dxf();

    if (!dxf->in(fileName.toLatin1().data(), dxfData)) {
        ui->lineEdit_filePath->setText("could not be opened");
        return;
    }

    QList<DL_PointData> pointList = dxfData->getPointList();
    ui->widget_dxfImage->setPointList(pointList);

    QList<DL_LineData> lineList = dxfData->getLineList();
    ui->widget_dxfImage->setLineList(lineList);

    QList<DL_MTextData> textList = dxfData->getTextList();
    ui->widget_dxfImage->setTextList(textList);

    QList<DL_ArcData> arcList = dxfData->getArcList();
    ui->widget_dxfImage->setArcList(arcList);

    QList<DL_CircleData> circleList = dxfData->getCircleList();
    ui->widget_dxfImage->setCircleList(circleList);

    QList<DL_TextData> textDataList = dxfData->getTextDataList();
    ui->widget_dxfImage->setTextDataList(textDataList);

    QList<DL_VertexData> vertexList = dxfData->getVertexList();
    ui->widget_dxfImage->setVertexList(vertexList);

    QList<DL_ControlPointData> controlPointList = dxfData->getControlPointList();
    ui->widget_dxfImage->setControlPointList(controlPointList);

    QList<DL_PolylineData> polyLineList = dxfData->getPolyLineList();
    ui->widget_dxfImage->setPolyLineList(polyLineList);

    QList<DL_EllipseData> ellipseList = dxfData->getEllipseList();
    ui->widget_dxfImage->setEllipseList(ellipseList);

    ui->lineEdit_filePath->setText(fileName);
    ui->doubleSpinBox_zoom->setValue(ui->widget_dxfImage->m_zoom);

    delete dxf;
    delete dxfData;

}

void MainWindow::slot_doubleSpinBox_setValue(double value)
{
    ui->doubleSpinBox_zoom->setValue(value);
}
