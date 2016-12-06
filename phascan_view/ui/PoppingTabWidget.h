/*
*  TabWidget that auto-hides when mouse leaves or double-clicks on the tab
*  shows up when mouse enters or double-clicks on the tab
*/

#ifndef POPPINGTABWIDGET_H
#define POPPINGTABWIDGET_H

#include <QTabWidget>
class PoppingTabBar ;
class QResizeEvent  ;

class PoppingTabWidget : public QTabWidget
{
	Q_OBJECT
public:
	PoppingTabWidget(QWidget *parent);
        void SetHideAble(bool hide_);

protected:
	virtual void  showEvent (QShowEvent*);
        void	resizeEvent ( QResizeEvent * e )  ;

private slots:
	void slotExtend();
	void slotShrink();
        void slotLastTabButtonClicked(Qt::MouseButton btn_);
        void slotRightButtonDoubleClicked(int) ;

signals:
        void signalLastTabBottonCliecked(Qt::MouseButton);
        void signalRightButtonDoubleClicked(int) ;
private:
        bool m_bHideAble ;
        int  getMinShowWidth() const;
        PoppingTabBar* tb  ;


};

#endif // POPPINGTABWIDGET_H
