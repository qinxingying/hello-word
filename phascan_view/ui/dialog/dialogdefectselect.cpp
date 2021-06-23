#include "dialogdefectselect.h"
#include "ui_dialogdefectselect.h"
#include <QPainter>
#include <QMouseEvent>

DialogDefectSelect::DialogDefectSelect(int defectNum, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDefectSelect)
{
    ui->setupUi(this);
    int x = size().width() - 20;
    int y = size().height() - 70;

    m_Image = new QImage( x, y, QImage::Format_RGB888);

    ui->ComboSelect->clear();
    for(int i = 1; i <= defectNum; i++){
        ui->ComboSelect->addItem(QString::number(i));
    }
    ui->LabelNotice->setText(tr("these has %1 defects found. please select one.").arg(defectNum));
    ui->ComboSelect->setCurrentIndex(0);
    m_selectDefect = 0;
    connect(ui->ComboSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(defectSelect(int)));
    connect(ui->BtOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

DialogDefectSelect::~DialogDefectSelect()
{
    delete m_Image;
    delete ui;    
}

void DialogDefectSelect::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage( QPoint(10,10), *m_Image);
    painter.setPen(Qt::black);
    int p = 1;
    for( int i = 0; i < m_defectCentre.size(); i++){
        if( m_selectDefect == i){
            painter.setPen(Qt::white);
        }else{
            painter.setPen(Qt::black);
        }
        painter.drawText(m_defectCentre[i], QString::number(p));
        p++;
    }
}

void DialogDefectSelect::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button()){
        QPoint buff = event->pos();
        for(int i = 0; i < m_defectCentre.size(); i++){
            if(m_defectRect[i].contains(buff)){
                ui->ComboSelect->setCurrentIndex(i);
                update();
                return;
            }
        }
    }
}

void DialogDefectSelect::defectSelect(int index)
{
    m_selectDefect = index;
}
