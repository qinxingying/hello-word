/*
 *	TabBar working with auto-hide TabWidget
 */

#ifndef POPPINGTABBAR_H
#define POPPINGTABBAR_H

#include <QTabBar>

class QMouseEvent;
class QEvent;

class PoppingTabBar : public QTabBar
{
	Q_OBJECT

public:
	PoppingTabBar(QWidget *parent);

protected:

	virtual void mousePressEvent      (QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
        virtual void wheelEvent(QWheelEvent* event) ;

signals:
	void extend();
	void shrink();
        void signalLastTabButton(Qt::MouseButton);
        void signalRightButtonDoubleClicked(int);
};

#endif // POPPINGTABBAR_H
