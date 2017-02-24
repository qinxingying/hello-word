#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QString fileName = QFileDialog::getOpenFileName(this,
                            "Open File Dialog",
                            "",
                            "Part Files(*.dxf)");

    if(fileName.isEmpty())  return;


    ui->lineEdit_filePath->setText(fileName);

    ui->widget_dxfImage->getDxfData(fileName);

    ui->widget_dxfImage->paint_line();
    ui->widget_dxfImage->paint_vertexToLine();
    ui->widget_dxfImage->paint_circle();
    ui->widget_dxfImage->paint_arc();
    ui->widget_dxfImage->paint_ellipse();
   // ui->widget_dxfImage->paint_text();
   // ui->widget_dxfImage->paint_textData();
}

void MainWindow::slot_doubleSpinBox_setValue(double value)
{
    ui->doubleSpinBox_zoom->setValue(value);
}
