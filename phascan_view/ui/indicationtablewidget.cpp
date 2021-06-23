#include "indicationtablewidget.h"
#include "ui_indicationtablewidget.h"
#include <QMessageBox>
#include "MainWindow.h"
#include "ProcessDisplay.h"

IndicationTableWidget::IndicationTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicationTableWidget)
{
    ui->setupUi(this);

    QTableWidgetItem    *headerItem;
    QStringList headerText;
    headerText << "ID" << "A%" << "Sr~Sm" << "Ur~Um" << "Ir~Im";  //表头标题用QStringList来表示
    ui->tableWidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
    for (int i = 0; i < ui->tableWidget->columnCount(); i++)//列编号从0开始
    {
        //cellItem=ui->tableInfo->horizontalHeaderItem(i);
        headerItem=new QTableWidgetItem(headerText.at(i)); //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font=headerItem->font();//获取原有字体设置
        font.setBold(true);
        font.setPointSize(8);//字体大小
        headerItem->setTextColor(Qt::red);
        headerItem->setFont(font);
        if (i == 0) {
            ui->tableWidget->setColumnWidth(i, 30);
        } else if (i == 1) {
            ui->tableWidget->setColumnWidth(i, 40);
        } else {
            ui->tableWidget->setColumnWidth(i, 82);
        }
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); /*设置 tablewidget 等高*/
    /*设置表格是否充满，即行末不留空*/
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setHidden(true);

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableWidget, &QAbstractItemView::customContextMenuRequested, this, &IndicationTableWidget::on_tableWidget_customContextMenuRequested);
    connect(ui->tableWidget, &QAbstractItemView::clicked, this, &IndicationTableWidget::on_tableWidget_Item_Clicked);

    m_nGroupId = 0;
    m_pConfig = DopplerConfigure::Instance();
    m_pGroup  = &m_pConfig->group[m_nGroupId];
}

IndicationTableWidget::~IndicationTableWidget()
{
    delete ui;
}

void IndicationTableWidget::setGroupId(int _groupId)
{
    m_nGroupId = _groupId;
    m_pGroup  = &m_pConfig->group[m_nGroupId];
    ui->groupComboBox->setCurrentIndex(m_nGroupId);
}

void IndicationTableWidget::updateConfig()
{
    int groupQty = m_pConfig->common.nGroupQty;
    ui->groupComboBox->clear();
    ui->tableWidget->clearContents();
    for (int i = 0; i < groupQty; ++i) {
        ui->groupComboBox->addItem(QString("Group %1").arg(i+1));
    }
    updateDefectTable();
}

void IndicationTableWidget::updateDefectTable()
{
    ui->tableWidget->clearContents();
    int cnt = m_pConfig->GetDefectCnt(m_nGroupId);
    ui->tableWidget->setRowCount(cnt);
    for(int i = 0 ; i < cnt ; i ++) {
        DEFECT_INFO* pDfInfo = m_pConfig->GetDefectPointer(m_nGroupId, i);
        QString amp = pDfInfo->m_strMeasure[0];
        QString Sr = QString::number(pDfInfo->fSStart + pDfInfo->dScanOffset, 'f', 1);
        QString Sm = QString::number(pDfInfo->fSStop + pDfInfo->dScanOffset, 'f', 1);
        QString Ur = QString::number(pDfInfo->fUStart, 'f', 1);
        QString Um = QString::number(pDfInfo->fUStop, 'f', 1);
        QString Ir = QString::number(pDfInfo->fIStart, 'f', 1);
        QString Im = QString::number(pDfInfo->fIStop, 'f', 1);
        QString lengthRange(QString("%1~%2").arg(Sr).arg(Sm));
        QString depthRange(QString("%1~%2").arg(Ur).arg(Um));
        QString horizontalRange(QString("%1~%2").arg(Ir).arg(Im));
        createItemsARow(i, pDfInfo->dIndex, amp, lengthRange, depthRange, horizontalRange);
    }
}

void IndicationTableWidget::createItemsARow(int _rowNo, int _id, QString _amp, QString _lengthRange, QString _depthRange, QString _horizontalRange)
{
    QTableWidgetItem    *item;

    QFont font = ui->tableWidget->font();
    font.setPointSize(8);

    item=new  QTableWidgetItem(QString::number(_id));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(font);
    ui->tableWidget->setItem(_rowNo, 0,item);

    item=new  QTableWidgetItem(_amp);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(font);
    ui->tableWidget->setItem(_rowNo, 1,item);

    item=new  QTableWidgetItem(_lengthRange);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(font);
    ui->tableWidget->setItem(_rowNo, 2,item);

    item=new  QTableWidgetItem(_depthRange);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(font);
    ui->tableWidget->setItem(_rowNo, 3, item);

    item=new  QTableWidgetItem(_horizontalRange);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(font);
    ui->tableWidget->setItem(_rowNo, 4, item);
}

void IndicationTableWidget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu *table_widget_menu;
    table_widget_menu = new QMenu(ui->tableWidget);
    QAction *action = new QAction(tr("Merge"), this);
    connect(action, &QAction::triggered, this, &IndicationTableWidget::on_merge_tableWidget_item);
    table_widget_menu->addAction(action);
    action = new QAction(tr("Delete"), this);
    connect(action, &QAction::triggered, this, &IndicationTableWidget::on_del_tableWidget_item);
    table_widget_menu->addAction(action);
    table_widget_menu->exec(QCursor::pos());
}

void IndicationTableWidget::on_tableWidget_Item_Clicked(const QModelIndex &index)
{
    g_pMainWnd->loadDefectPosition(m_nGroupId, index.row());
}

void IndicationTableWidget::on_del_tableWidget_item()
{
    /*获取选中的列表里的所有条目*/
        QList<QTableWidgetItem*> list = ui->tableWidget->selectedItems();
        int cnt = list.count() / 5;
        if(cnt <= 0)
        {
            QMessageBox::warning(this, tr("Delete Defect"),
            tr("Please Select Defect"),
            QMessageBox::Ok);
            return;
        }

        int id = 0;
        for(int i = 0; i < cnt; i++)
        {
            //int id = list.at(i * 5)->data(0).toInt() - 1;
            int row = ui->tableWidget->row(list.at(i * 5));
            if(row!=-1)
            {
                ui->tableWidget->removeRow(row);
                m_pConfig->DeleteDefect(m_nGroupId, row);
                id = row;
            }
        }
        g_pMainWnd->updateAllDefectBox();
        g_pMainWnd->loadDefectPosition(m_nGroupId, id);
        ProcessDisplay _display ;
        _display.ResetDefectInfo(m_nGroupId);
        _display.UpdateAllViewOverlay();

        updateDefectTable();
        ui->tableWidget->setCurrentItem(nullptr);
}

void IndicationTableWidget::on_merge_tableWidget_item()
{
    QList<QTableWidgetItem*> list = ui->tableWidget->selectedItems();
    int cnt = list.count() / 5;
    if (cnt <= 1) return;

    QVector<int> ids;
    for(int i = 0; i < cnt; i++)
    {
        int id = list.at(i * 5)->data(0).toInt() - 1;
        ids << id;
    }
    qSort(ids.begin(), ids.end());
    float max = 0.0;
    float fSStart   = 0.0;
    float fSStop    = 0.0;
    float fVPAStart = 0.0;
    float fVPAStop  = 0.0;

    for (auto i : ids) {
        DEFECT_INFO* pDfInfo = m_pConfig->GetDefectPointer(m_nGroupId, i);
        max = pDfInfo->reserve[0] > max ? pDfInfo->reserve[0] : max;
        if (i == ids[0]) {
            fSStart     = pDfInfo->fSStart;
            fSStop      = pDfInfo->fSStop;
            fVPAStart   = pDfInfo->fVPAStart;
            fVPAStop    = pDfInfo->fVPAStop;
        } else {
            fSStart     = pDfInfo->fSStart < fSStart ? pDfInfo->fSStart : fSStart;
            fSStop      = pDfInfo->fSStop > fSStop ? pDfInfo->fSStop : fSStop;
            fVPAStart   = pDfInfo->fVPAStart < fVPAStart ? pDfInfo->fVPAStart : fVPAStart;
            fVPAStop    = pDfInfo->fVPAStop > fVPAStop ? pDfInfo->fVPAStop : fVPAStop;
        }
    }
    QVector<DEFECT_INFO *> tmp;
    for (auto i : ids) {
        DEFECT_INFO* pDfInfo = m_pConfig->GetDefectPointer(m_nGroupId, i);
        if (pDfInfo->reserve[0] == max) {
            tmp.append(pDfInfo);
        }
    }
    if (tmp.count() == 0) return;
    int specialId = tmp[0]->dIndex - 1;
    float len = tmp[0]->fSStop - tmp[0]->fSStart;
    for (int i = 1; i < tmp.count(); ++i) {
        float lenTmp = tmp[i]->fSStop - tmp[i]->fSStart;
        if (lenTmp > len) {
            specialId = tmp[i]->dIndex - 1;
        }
    }

    DEFECT_INFO* pDfInfo = m_pConfig->GetDefectPointer(m_nGroupId, specialId);
//    pDfInfo->fSStart   = fSStart;
//    pDfInfo->fSStop    = fSStop;
//    pDfInfo->fVPAStart = fVPAStart;
//    pDfInfo->fVPAStop  = fVPAStop;

//    int c = m_pConfig->GetDefectCnt(m_nGroupId);
//    DEFECT_INFO* pDfInfo2 = m_pConfig->GetDefectPointer(m_nGroupId, ids.first());
//    DEFECT_INFO* prev = pDfInfo2->pPrev;
//    DEFECT_INFO* next = pDfInfo2->pNext;
//    memcpy(pDfInfo2, pDfInfo, sizeof(DEFECT_INFO));
//    pDfInfo2->pNext = next;
//    pDfInfo2->pPrev = prev;

//    c = m_pConfig->GetDefectCnt(m_nGroupId);
//    g_pMainWnd->loadDefectPosition(m_nGroupId, specialId);

    for(int i = 0; i < cnt; i++)
    {
        int row = ui->tableWidget->row(list.at(i * 5));
        if (list.at(i * 5)->data(0).toInt() - 1 == specialId) {
            continue;
        }
        if(row!=-1)
        {
            ui->tableWidget->removeRow(row);
            m_pConfig->DeleteDefect(m_nGroupId, row);
        }
    }

    pDfInfo->fSStart   = fSStart;
    pDfInfo->fSStop    = fSStop;
    pDfInfo->fVPAStart = fVPAStart;
    pDfInfo->fVPAStop  = fVPAStop;

    m_pConfig->ReorderDefect();
    g_pMainWnd->loadDefectPosition(m_nGroupId, pDfInfo->dIndex - 1);
    m_pConfig->DeleteDefect(m_nGroupId, pDfInfo->dIndex - 1);

    g_pMainWnd->updateAllDefectBox();
    ProcessDisplay _display ;
    _display.ResetDefectInfo(m_nGroupId);
    _display.UpdateAllViewOverlay();

    emit merged();
    ui->tableWidget->setCurrentItem(nullptr);
}

void IndicationTableWidget::on_groupComboBox_currentIndexChanged(int index)
{
    m_nGroupId = index;
    updateDefectTable();
    g_pMainWnd->SetCurGroup(index);
}
