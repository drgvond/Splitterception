#ifndef LAYOUTHANDLE_H
#define LAYOUTHANDLE_H

#include <QtWidgets/qwidget.h>

class QBoxLayout;

class LayoutHandle : public QWidget
{
    Q_OBJECT
public:
    LayoutHandle(QBoxLayout *layout);

    QSize sizeHint() const override;

    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

private:
    void moveSplitter(int pos);

    inline int pick(const QPoint &pos) const
    { return m_orientation == Qt::Horizontal ? pos.x() : pos.y(); }

    Qt::Orientation m_orientation;
    QBoxLayout *m_layout;
    int m_mouseOffset;
    int m_cached_index = -1;
};

#endif // LAYOUTHANDLE_H
