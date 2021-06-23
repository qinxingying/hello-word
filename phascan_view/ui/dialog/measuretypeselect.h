#ifndef MEASURETYPESELECT_H
#define MEASURETYPESELECT_H

#include <QDialog>

class QTableWidget;
class QTabWidget;
class MeasureTypeSelect : public QDialog
{
    Q_OBJECT
public:
    explicit MeasureTypeSelect(QWidget *parent = 0, int type=0);
    ~MeasureTypeSelect();
    int type() const;
    QString type_string();
    //void set_type(int type);
protected:
//    QWidget *create_gate_widget();
//    QWidget *create_cursor_widget();
//    QWidget *create_position_widget();
//    QWidget *create_sizing_widget();
//    QWidget *create_aws_widget();
//    QWidget *create_tofd_widget();
private:
    QTabWidget *m_tabWidget;
    enum {
        GATE,
        CURSOR,
        POSITION,
        SIZING,
        AWS,
        TOFD,
        TABLE_COUNT
    };
    QVector<QTableWidget *> m_tableWidgets;
    QPushButton *m_chooseBtn;
    QPushButton *m_cancelBtn;
};

#endif // MEASURETYPESELECT_H
