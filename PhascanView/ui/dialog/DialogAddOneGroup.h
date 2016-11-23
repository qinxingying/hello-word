#ifndef DIALOGADDONEGROUP_H
#define DIALOGADDONEGROUP_H

#include <QDialog>

class QCloseEvent ;

namespace Ui {
    class DialogAddOneGroup;
}

class DialogAddOneGroup : public QDialog
{
    Q_OBJECT

public:
    ~DialogAddOneGroup();
    explicit DialogAddOneGroup(QWidget *parent = 0);

    int GetSelection() const ;
protected:
    void closeEvent (QCloseEvent *e) ;
private:

    int m_nComQty    ;
    int m_nSelection ;
    Ui::DialogAddOneGroup *ui;
protected slots:
    void slotComBoxSelectionChanged(int) ;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DIALOGADDONEGROUP_H
