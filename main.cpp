#include "mainwidget.h"
#include "colorwidget.h"
#include "eventspy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget splittersWidget(true);
    splittersWidget.setWindowTitle("Splitters");
    splittersWidget.show();

    ColorWidget::resetCount();

    MainWidget layoutsWidget(false);
    layoutsWidget.setWindowTitle("Layouts");
    layoutsWidget.show();

    EventSpy spy;
    a.installEventFilter(&spy);

    return a.exec();
}
