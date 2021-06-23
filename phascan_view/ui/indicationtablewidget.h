﻿#ifndef INDICATIONTABLEWIDGET_H
#define INDICATIONTABLEWIDGET_H

#include <QWidget>
#include "ParameterProcess.h"
#include "Instrument.h"
#include "DopplerConfigure.h"

namespace Ui {
class IndicationTableWidget;
}

class IndicationTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndicationTableWidget(QWidget *parent = 0);
    ~IndicationTableWidget();
    void setGroupId(int _groupId);
    void updateConfig();
    void updateDefectTable();
    void createItemsARow(int _rowNo, int _id, QString _amp, QString _lengthRange, QString _depthRange, QString _horizontalRange);

signals:
    void merged();
private slots:
    void on_groupComboBox_currentIndexChanged(int index);

private:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void on_tableWidget_Item_Clicked(const QModelIndex &index);
    void on_del_tableWidget_item();
    void on_merge_tableWidget_item();

private:
    Ui::IndicationTableWidget *ui;

    DopplerConfigure* m_pConfig;
    GROUP_CONFIG* m_pGroup;
    int  m_nGroupId;
};

#endif // INDICATIONTABLEWIDGET_H
