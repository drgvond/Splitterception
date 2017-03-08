#ifndef MYSPLITTER_H
#define MYSPLITTER_H

#include <QtWidgets/qsplitter.h>

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

#endif // MYSPLITTER_H
