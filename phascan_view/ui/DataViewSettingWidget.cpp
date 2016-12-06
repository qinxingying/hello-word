#include "DataViewSettingWidget.h"
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QDoubleSpinBox>

DataViewSettingWidget::DataViewSettingWidget(QWidget *parent) :
    QWidget(0)
{
    m_pView = (DopplerDataView*)parent ;

    //#############  set window property
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //setWindowOpacity(0.9);
    setAttribute(Qt::WA_TranslucentBackground, true);
    //############# set window size
    setFixedHeight( 30 );
    QPoint _pos = m_pView->mapToGlobal(QPoint(0 , 0)) ;
    setGeometry(_pos.x() + 25 ,  _pos.y() + m_pView->height() -  50  , m_pView->width()  -  60  ,   30 ) ;
    //############# create window layout
    QHBoxLayout* pLayout = new QHBoxLayout () ;
    pLayout->setContentsMargins(0,0,0,0) ;
    pLayout->setSpacing (1) ;
    //#############
    m_pBtnMinus = new QPushButton("-" , this) ;
    m_pBtnPlus  = new QPushButton("+" , this) ;
    m_pLabel    = new QLabel(this)  ;
    m_pLabel->setAlignment(Qt::AlignCenter);
    QPalette pal = m_pLabel->palette() ;
    pal.setColor(QPalette::Foreground , QColor(255 , 255 , 255 ));
    m_pLabel->setAutoFillBackground(true);
    m_pLabel->setPalette(pal);
    m_pLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    m_pBtnMinus->setFixedWidth(20);
    m_pBtnPlus->setFixedWidth(20);
    m_pLabel->setFixedWidth(30);
    m_pSlider = new QSlider(Qt::Horizontal, this) ;
    pLayout->addWidget(m_pLabel) ;
    pLayout->addWidget(m_pBtnMinus);
    pLayout->addWidget(m_pSlider);
    pLayout->addWidget(m_pBtnPlus);
    setLayout(pLayout);

    connect(m_pBtnMinus , SIGNAL(clicked()),  SLOT(slotButtonMinusClicked())) ;
    connect(m_pBtnPlus , SIGNAL(clicked()),  SLOT(slotButtonPlusClicked())) ;
    connect(m_pSlider  , SIGNAL(valueChanged(int)) , SLOT(slotSliderValueChanged(int))) ;
}

DataViewSettingWidget::~DataViewSettingWidget()
{

}


void DataViewSettingWidget::slotButtonMinusClicked()
{
    int _nStep  = m_pSlider->singleStep() ;
    m_pSlider->setValue(m_pSlider->value() - _nStep);
}

void DataViewSettingWidget::slotButtonPlusClicked()
{
    int _nStep  = m_pSlider->singleStep() ;
    m_pSlider->setValue(m_pSlider->value() + _nStep);
}

void DataViewSettingWidget::slotSliderValueChanged(int nValue_)
{
    QString _str = QString::number(nValue_) ;
    m_pLabel->setText(_str);
}
