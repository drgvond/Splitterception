#include "mainwidget.h"
#include "eventspy.h"
#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget splittersWidget(true);
    splittersWidget.setWindowTitle("Splitters");
    splittersWidget.show();

    MainWidget layoutsWidget(false);
    layoutsWidget.setWindowTitle("Layouts");
    layoutsWidget.show();

    EventSpy spy;
    a.installEventFilter(&spy);

    return a.exec();
}
