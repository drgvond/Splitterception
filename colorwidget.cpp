#include "colorwidget.h"
#include <QtGui>
#include <qdebug.h>

int ColorWidget::widget_count = 0;
const Qt::GlobalColor ColorWidget::colors[] = { Qt::red, Qt::green, Qt::magenta, Qt::cyan, /*Qt::blue,*/ Qt::yellow };
const int ColorWidget::colors_count = sizeof(colors) / sizeof(colors[0]);

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget(parent), m_size_hint(2 * min_size), m_widget_id(widget_count++)
{
    m_color = colors[m_widget_id % colors_count];
    setObjectName(QString::number(m_widget_id));
}

QSize ColorWidget::sizeHint() const
{
    return QSize(m_size_hint, m_size_hint);
}

QSize ColorWidget::minimumSizeHint() const
{
    return QSize(m_size_hint, m_size_hint);
//    return QSize(min_size, min_size);
}

void ColorWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(e->rect(), QBrush(m_color));

    p.drawText(QRect(5, 5, 50, 20), objectName());
}

void ColorWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_size_hint += 10;
    } else if (e->button() == Qt::RightButton) {
        m_size_hint -= 10;
        if (m_size_hint < min_size)
            m_size_hint = min_size;
    }

    updateGeometry();
}
