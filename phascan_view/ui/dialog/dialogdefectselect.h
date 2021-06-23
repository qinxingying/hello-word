#ifndef DIALOGDEFECTSELECT_H
#define DIALOGDEFECTSELECT_H

#include <QDialog>

namespace Ui {
class DialogDefectSelect;
}

class DialogDefectSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDefectSelect(int defectNum, QWidget *parent = 0);
    ~DialogDefectSelect();
    QImage* getDefectImage(){return m_Image;}
    void setDefectCentre(QVector<QPoint> defectCentre, QVector<QRect> defectRect){m_defectCentre = defectCentre;m_defectRect = defectRect;}
    int  getSelectDefect(){return m_selectDefect;}
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void defectSelect(int index);
private:
    Ui::DialogDefectSelect *ui;
    QImage* m_Image;
    QVector<QPoint> m_defectCentre;
    QVector<QRect>  m_defectRect;
    int m_selectDefect;
};

#endif // DIALOGDEFECTSELECT_H
