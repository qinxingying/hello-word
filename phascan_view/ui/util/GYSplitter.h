#ifndef GYSPLITTER_H
#define GYSPLITTER_H

#include <QSplitter>

class GYSplitter : public QSplitter
{
    Q_OBJECT

public:
	explicit GYSplitter(QWidget *parent = 0);

protected:
    void timerEvent(QTimerEvent *event);

private:
    int m_nTimerId;

};

#endif // GYSPLITTER_H
