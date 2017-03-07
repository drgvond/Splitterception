#include "mysplitter.h"

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

MyLayoutHandle::MyLayoutHandle(QBoxLayout *layout)
    : QWidget(), m_layout(layout)
{
    m_orientation = layout->direction() == QBoxLayout::LeftToRight
            ? Qt::Horizontal : Qt::Vertical;

    // Emulate QSplitterHandle in a QSplitter
    if (m_orientation == Qt::Horizontal)
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    else
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

QSize MyLayoutHandle::sizeHint() const
{
    // Same as QSplitterHandle
    auto *pw = parentWidget();
    QStyleOption opt(0);
    opt.init(pw);
    opt.state = QStyle::State_None;
    // Handle width 1
    return pw->style()->sizeFromContents(QStyle::CT_Splitter, &opt, QSize(1, 1), pw)
            .expandedTo(QApplication::globalStrut());
}

void MyLayoutHandle::paintEvent(QPaintEvent *e)
{
    // Same as QSplitterHandle
    QPainter p(this);
    QStyleOption opt(0);
    opt.rect = contentsRect();
    opt.palette = palette();
    if (m_orientation == Qt::Horizontal)
        opt.state = QStyle::State_Horizontal;
    else
        opt.state = QStyle::State_None;
#if 0
    if (d->hover)
        opt.state |= QStyle::State_MouseOver;
    if (d->pressed)
        opt.state |= QStyle::State_Sunken;
#endif
    auto *pw = parentWidget();
    if (isEnabled())
        opt.state |= QStyle::State_Enabled;
    pw->style()->drawControl(QStyle::CE_Splitter, &opt, &p, pw);
}

void MyLayoutHandle::mouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug() << layout();
}
