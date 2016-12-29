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

    ui->lineEdit_filePath->setText(fileName);

    Test_CreationClass* creationClass = new Test_CreationClass();
    DL_Dxf* dxf = new DL_Dxf();

    if (!dxf->in(fileName.toLatin1().data(), creationClass)) {
        ui->lineEdit_filePath->setText("could not be opened");
        return;
    }

    DRAW_LINE line = creationClass->getLine();
    qDebug() << "line x1:" << line.x1 << "x2:" << line.x2;
    ui->widget_dxfImage->setLine(line);
}
