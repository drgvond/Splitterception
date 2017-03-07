#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(bool use_splitters, QWidget *parent = 0);
    ~MainWidget();

    QWidget *makeSplitters(int children, int depth) const;
    QLayout *makeLayouts(int children, int depth, QLayout *parent = nullptr) const;

    void mouseDoubleClickEvent(QMouseEvent *e) override;

private:
    static int objects_count;
};

#endif // MAINWIDGET_H
