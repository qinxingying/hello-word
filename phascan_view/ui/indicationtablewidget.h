﻿#ifndef INDICATIONTABLEWIDGET_H
#define INDICATIONTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "ParameterProcess.h"
#include "Instrument.h"
#include "DopplerConfigure.h"
#include <QStack>

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
    void retranslateUi();
    void setSelectedDefect(int _index);
    void deleteDefect(int _index);
    void clearStack();
protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void merged();
    void save();
private slots:
    void on_groupComboBox_currentIndexChanged(int index);

    void on_modifyBtn_clicked();

    void on_restoreBtn_clicked();

    void on_saveBtn_clicked();

    void on_undoBtn_clicked();

private:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void on_tableWidget_Item_Clicked(const QModelIndex &index);
    void on_del_tableWidget_item();
    void on_merge_tableWidget_item();
    void on_tableWidget_current_cell_changed(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::IndicationTableWidget *ui;

    DopplerConfigure* m_pConfig;
    GROUP_CONFIG* m_pGroup;
    int  m_nGroupId;

    enum Command {
        Delete,
        Merge,
        Modify
    };
    QStack<Command> m_commandStack;
    QStack<QVector<DEFECT_INFO>> m_undoStack;
};

#endif // INDICATIONTABLEWIDGET_H
