#ifndef DOPPLERCOUPLEBAR_H
#define DOPPLERCOUPLEBAR_H

#include <QWidget>

#define DOPPLER_COUPLE_BAR_WIDTH   10

class DopplerConfigure;
class DopplerCoupleSScanBar : public QWidget
{
    Q_OBJECT
public:
    explicit DopplerCoupleSScanBar( QWidget *parent = 0);
    void setColorIndex( void* color_);
    void setGroupId( int groupId);

private:
    void paintEvent(QPaintEvent *);

    unsigned char (*color)[3];
    int       nGroupId;
    DopplerConfigure* m_pConfig;
};

enum BarOrientation{
    Horizontal,
    Vertical
};

class DopplerCoupleCScanBar : public QWidget
{
    Q_OBJECT
public:
    explicit DopplerCoupleCScanBar( BarOrientation direction, QWidget *parent = 0);
    void setColorIndex( void* color_);
    void setGroupId( int groupId);
    void setDisplayRange( double _start, double _end){start = _start; end = _end;update();}
    void setCoupleRange( double _start, double _end){ startRange = _start; endRange = _end;update();}
    BarOrientation getOrientation(){return m_dirction;}

private:
    void paintEvent(QPaintEvent *);
    unsigned char (*color)[3];
    int       nGroupId;
    double start;
    double end;
    double startRange;
    double endRange;
    BarOrientation m_dirction;
};

#endif // DOPPLERCOUPLEBAR_H
