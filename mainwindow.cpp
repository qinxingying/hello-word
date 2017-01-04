#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"

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

    Test_CreationClass* creationClass = new Test_CreationClass();
    DL_Dxf* dxf = new DL_Dxf();

    if (!dxf->in(fileName.toLatin1().data(), creationClass)) {
        ui->lineEdit_filePath->setText("could not be opened");
        return;
    }

    QList<DL_LineData> lineList = creationClass->getLineList();
    ui->widget_dxfImage->setLineList(lineList);

    QList<DL_MTextData> textList = creationClass->getTextList();
    ui->widget_dxfImage->setTextList(textList);

    QList<DL_ArcData> arcList = creationClass->getArcList();
    ui->widget_dxfImage->setArcList(arcList);

    QList<DL_CircleData> circleList = creationClass->getCircleList();
    ui->widget_dxfImage->setCircleList(circleList);

    QList<DL_TextData> textDataList = creationClass->getTextDataList();
    ui->widget_dxfImage->setTextDataList(textDataList);

    QList<DL_VertexData> vertexList = creationClass->getVertexList();
    ui->widget_dxfImage->setVertexList(vertexList);

    ui->lineEdit_filePath->setText(fileName);
    ui->doubleSpinBox_zoom->setValue(ui->widget_dxfImage->m_zoom);

    delete dxf;
    delete creationClass;

}

void MainWindow::slot_doubleSpinBox_setValue(double value)
{
    ui->doubleSpinBox_zoom->setValue(value);
}
