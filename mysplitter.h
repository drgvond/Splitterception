#ifndef MYSPLITTER_H
#define MYSPLITTER_H

#include <QtWidgets>

class MySplitter : public QSplitter
{
    Q_OBJECT
public:
    MySplitter(Qt::Orientation orientation, QWidget *parent = 0);

    QSplitterHandle *createHandle() override;
};

class MySplitterHandle : public QSplitterHandle
{
    Q_OBJECT
public:
    MySplitterHandle(Qt::Orientation o, QSplitter *parent);

    void mouseDoubleClickEvent(QMouseEvent *e) override;
};

class MyLayoutHandle : public QWidget
{
    Q_OBJECT
public:
    MyLayoutHandle(QBoxLayout *layout);

    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

private:
    Qt::Orientation m_orientation;
    QBoxLayout *m_layout;
};

#endif // MYSPLITTER_H
