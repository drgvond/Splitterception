#ifndef EVENTSPY_H
#define EVENTSPY_H

#include <QtCore/qobject.h>

class EventSpy : public QObject
{
    Q_OBJECT
public:
    explicit EventSpy(QObject *parent = 0);

    bool eventFilter(QObject *receiver, QEvent *event) override;

private:
    bool m_paint_event_expected;
};

#endif // EVENTSPY_H
