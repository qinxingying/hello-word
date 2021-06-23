#ifndef DIALOGMETHODSELECT_H
#define DIALOGMETHODSELECT_H

#include <QDialog>

namespace Ui {
class DialogMethodSelect;
}

class QButtonGroup;
class DialogMethodSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMethodSelect( int id, QWidget *parent = 0);
    ~DialogMethodSelect();
    int getMethodId(){return m_method;}

private slots:
    void methodSelect();

private:
    Ui::DialogMethodSelect *ui;
    QButtonGroup *m_GroupBt;
    int m_method;
};

#endif // DIALOGMETHODSELECT_H
