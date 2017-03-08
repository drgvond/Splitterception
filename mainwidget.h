#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/qwidget.h>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(bool use_splitters, QWidget *parent = 0);
    ~MainWidget();

private:
    QWidget *makeSplitters(int children, int depth) const;
    QLayout *makeLayouts(int children, int depth, QLayout *parent = nullptr) const;

    static int objects_count;
    static bool call_winId;
};

#endif // MAINWIDGET_H
