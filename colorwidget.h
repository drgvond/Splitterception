#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QtWidgets/qwidget.h>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

    static void resetCount() { widget_count = 0; }

private:
    QColor m_color;
    int m_size_hint;
    int m_widget_id;

    static int widget_count;
    static const Qt::GlobalColor colors[];
    static const int colors_count;
    static const int min_size = 20;
};

#endif // COLORWIDGET_H
