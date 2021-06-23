#include "DialogColorSelect.h"
#include "ui_DialogColorSelect.h"
#include <configure/DopplerColorIndex.h>

#include <QDir>
#include <QPainter>
#include <QListWidget>
#include <QDebug>

DialogColorSelect::DialogColorSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColorSelect)
{
    ui->setupUi(this);
    setFixedSize(size());
    InitListWidget();
}

DialogColorSelect::~DialogColorSelect()
{
    delete ui;
}

void DialogColorSelect::InitListWidget()
{
    QListWidget* m_pSubList  = ui->ListName;
    QString strPaletePath = QCoreApplication::applicationDirPath() + "/init/palette";

    QDir _dir(strPaletePath);
    _dir.setFilter(QDir::Files | QDir::Readable);

    QFileInfoList _list = _dir.entryInfoList();
    QFileInfo _fileInfo;
    m_pSubList->clear();
    QListWidgetItem* _p;

    for (int i = 0; i < _list.size(); ++i)
    {
        _fileInfo = _list.at(i);
        _p =  new QListWidgetItem(_fileInfo.fileName(), m_pSubList);
    }
    Q_UNUSED(_p);

    QObject::connect(m_pSubList, SIGNAL(currentTextChanged(QString)),  SLOT(slotSelectChanged(QString)));
    if (m_pSubList->count() > 0)
    {
        m_pSubList->setCurrentRow(0);
    }
}

void DialogColorSelect::slotSelectChanged(QString str_)
{
    if(str_.isEmpty())  return ;

    QString strPaletePath = QCoreApplication::applicationDirPath() + "/init/palette/";
    QListWidget* m_pSubList  = ui->ListName;
    QListWidgetItem* _pFile   = m_pSubList->currentItem();

    QString _str = strPaletePath + _pFile->text();

    DopplerColorIndex _color;
    _color.LoadPallete(_str);
    memcpy((void*)m_aColor , _color.GetColorIndex() , 256 * 3);
    update();
}

void DialogColorSelect::paintEvent (QPaintEvent*)
{
    QPainter _painter(this);
    QRect _rect = ui->ListName->geometry();
    int _nXStart = _rect.right() + 10 ;
    int _nXStop  = _nXStart + 90  ;
    int _nYStart = _rect.top() ;
    int _nHeight = _rect.height() ;
    int _nIndex ;
    QPen _pen = _painter.pen();
    _pen.setWidth(1);

    for(int i = 0 ; i < _nHeight ; i++)
    {
        _nIndex = 255 - i * 255 / _nHeight ;
        _pen.setColor(QColor(m_aColor[_nIndex][0] , m_aColor[_nIndex][1] , m_aColor[_nIndex][2]));
        _painter.setPen(_pen);
        _painter.drawLine(_nXStart ,_nYStart + i , _nXStop , _nYStart + i);
    }
}

void DialogColorSelect::on_pushButton_clicked()
{
    accept ();
}

void DialogColorSelect::on_pushButton_2_clicked()
{
    reject();
}

void* DialogColorSelect::GetColorIndex() const
{
    return (void*)m_aColor;
}
