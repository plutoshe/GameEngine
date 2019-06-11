#include "qtrendercontroller.h"
#include <QMouseEvent>

bool QTRenderController::event(QEvent *event)
{
	switch (event->type()) {
	case QEvent::UpdateRequest:
		frame++;
		qDebug() << frame;
		//renderNow();
		return true;
	case QEvent::MouseButtonPress:
	{
		QMouseEvent *me = static_cast<QMouseEvent *>(event);
		qDebug() << " aaa Mouse click" << me->pos();
		break;
	}
	default:
		return QWindow::event(event);
	}
}