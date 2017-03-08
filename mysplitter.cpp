#include "mysplitter.h"
#include <QtGui/qevent.h>

MySplitter::MySplitter(Qt::Orientation o, QWidget *parent)
    : QSplitter(o, parent)
{
    setContentsMargins(1, 1, 1, 1);
    setHandleWidth(1);
}

QSplitterHandle *MySplitter::createHandle()
{
    return new MySplitterHandle(orientation(), this);
}

MySplitterHandle::MySplitterHandle(Qt::Orientation o, QSplitter *parent)
    : QSplitterHandle(o, parent)
{ }

void MySplitterHandle::mouseDoubleClickEvent(QMouseEvent *e)
{
    int position = orientation() == Qt::Horizontal ? pos().x() : pos().y();
    if (e->button() == Qt::LeftButton)
        moveSplitter(position + 10);
    else if (e->button() == Qt::RightButton)
        moveSplitter(position - 10);
}
