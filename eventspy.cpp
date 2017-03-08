#include "eventspy.h"
#include <QtCore/qdatetime.h>
#include <QtCore/qdebug.h>
#include <QtGui/qevent.h>

EventSpy::EventSpy(QObject *parent) : QObject(parent), m_paint_event_expected(false)
{
}

bool EventSpy::eventFilter(QObject *receiver, QEvent *event)
{
    bool expectation_changed = false;
    auto type = event->type();
    switch (type) {
    case QEvent::MouseMove:
        if (m_paint_event_expected && static_cast<QMouseEvent *>(event)->buttons()) {
            expectation_changed = true;
            m_paint_event_expected = false;
        }
        // fallthrough
    case QEvent::MouseButtonRelease:
    case QEvent::NonClientAreaMouseMove:
    case QEvent::NonClientAreaMouseButtonPress:
    case QEvent::NonClientAreaMouseButtonRelease:
    case QEvent::Enter:
    case QEvent::Leave:
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::Hide:
    case QEvent::CursorChange:
    case QEvent::WindowActivate:
    case QEvent::WindowDeactivate:
    case QEvent::ToolTip:
    case QEvent::FocusAboutToChange:
    case QEvent::FocusIn:
    case QEvent::FocusOut:
        break;
    default:
        qDebug() << QTime::currentTime().toString() << receiver << event;
        if (!m_paint_event_expected
                && (type == QEvent::Expose || type == QEvent::UpdateRequest)) {
            expectation_changed = true;
            m_paint_event_expected = true;
        } else if (m_paint_event_expected
                   && (type == QEvent::Move || type == QEvent::Resize || type == QEvent::LayoutRequest)) {
            expectation_changed = true;
            m_paint_event_expected = false;
        } else if (!m_paint_event_expected && type == QEvent::Paint) {
            qDebug() << "!!!! U *** N *** E *** X *** P *** E *** C *** T *** E *** D !!!!";
        }
    }

    if (expectation_changed)
        qDebug() << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~";

    return false;
}
