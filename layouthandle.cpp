#include "layouthandle.h"
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>
#include <QtWidgets/qboxlayout.h>

LayoutHandle::LayoutHandle(QBoxLayout *layout)
    : QWidget(), m_layout(layout)
{
    m_orientation = layout->direction() == QBoxLayout::LeftToRight
            ? Qt::Horizontal : Qt::Vertical;

    if (m_orientation == Qt::Horizontal) {
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        setCursor(Qt::SplitHCursor);
    } else {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        setCursor(Qt::SplitVCursor);
    }
}

QSize LayoutHandle::sizeHint() const
{
#ifdef EMULATE_SPLITTER_HANDLE
    // Same as QSplitterHandle
    auto *pw = parentWidget();
    QStyleOption opt(0);
    opt.init(pw);
    opt.state = QStyle::State_None;
    // Handle width 1
    return pw->style()->sizeFromContents(QStyle::CT_Splitter, &opt, QSize(1, 1), pw)
            .expandedTo(QApplication::globalStrut());
#else
    return QSize(3, 3);
#endif
}

void LayoutHandle::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
#ifdef EMULATE_SPLITTER_HANDLE
    // Same as QSplitterHandle
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
#else
    p.fillRect(e->rect(), Qt::gray);
#endif
}

void LayoutHandle::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        m_mouseOffset = pick(e->pos());
}

void LayoutHandle::mouseMoveEvent(QMouseEvent *e)
{
    if (!(e->buttons() & Qt::LeftButton))
        return;

    const int delta = pick(e->pos()) - m_mouseOffset;
    moveSplitter(delta);
}

void LayoutHandle::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
}

void LayoutHandle::mouseDoubleClickEvent(QMouseEvent *e)
{
    moveSplitter(e->button() == Qt::LeftButton ? 10 : -10);
}

void LayoutHandle::moveSplitter(int delta)
{
    if (m_cached_index == -1 || m_layout->itemAt(m_cached_index)->widget() != this) {
        m_cached_index = 0;
        while (m_layout->itemAt(m_cached_index)->widget() != this)
            m_cached_index++;
    }

    auto *handleItem = m_layout->itemAt(m_cached_index);
    auto *preItem = m_layout->itemAt(m_cached_index - 1);
    auto *postItem = m_layout->itemAt(m_cached_index + 1);

    auto handleRect = handleItem->geometry();
    auto preRect = preItem->geometry();
    auto postRect = postItem->geometry();

    if (m_orientation == Qt::Horizontal) {
        preRect.setWidth(preRect.width() + delta);
        handleRect.translate(delta, 0);
        postRect.setLeft(postRect.left() + delta);
    } else {
        preRect.setHeight(preRect.height() + delta);
        handleRect.translate(0, delta);
        postRect.setTop(postRect.top() + delta);
    }

    preItem->setGeometry(preRect);
    handleItem->setGeometry(handleRect);
    postItem->setGeometry(postRect);
}
