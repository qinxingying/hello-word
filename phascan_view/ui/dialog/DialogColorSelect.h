#ifndef DIALOGCOLORSELECT_H
#define DIALOGCOLORSELECT_H

#include "const.h"

#include <QDialog>

namespace Ui {
    class DialogColorSelect;
}

class DialogColorSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogColorSelect(QWidget *parent = 0);
    ~DialogColorSelect();

    void* GetColorIndex() const;

protected:
    void paintEvent (QPaintEvent*);

private:
    void InitListWidget() ;

    Ui::DialogColorSelect *ui;
    unsigned char m_aColor[256][3];

protected slots:
    void slotSelectChanged(QString str_);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DIALOGCOLORSELECT_H
