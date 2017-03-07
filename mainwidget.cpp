#include "mainwidget.h"
#include "colorwidget.h"
#include "mysplitter.h"
#include <QtWidgets>

int MainWidget::objects_count = 0;

MainWidget::MainWidget(bool use_splitters, QWidget *parent)
    : QWidget(parent)
{
    if (use_splitters) {
        auto *layout = new QVBoxLayout;
        layout->setMargin(0);
        layout->addWidget(makeSplitters(3, 5));
        setLayout(layout);
    } else {
        setLayout(makeLayouts(3, 5));
    }
    objects_count = 0;
}

MainWidget::~MainWidget()
{

}

QWidget *MainWidget::makeSplitters(int children, int depth) const
{
    if (depth == 0) {
        auto *w = new ColorWidget();
        w->winId();
        return w;
    }

    auto *splitter = new MySplitter(depth & 1 ? Qt::Horizontal : Qt::Vertical);
    splitter->setObjectName(QLatin1Char('s') + QString::number(objects_count++));
    for (int i = 0; i < children; i++)
        splitter->addWidget(makeSplitters(children, depth - 1));

    return splitter;
}

QLayout *MainWidget::makeLayouts(int children, int depth, QLayout *parent) const
{
    if (depth == 0) {
        auto *w = new ColorWidget();
        w->winId();
        parent->addWidget(w);
        return nullptr;
    }

    auto *layout = new QBoxLayout((depth & 1) ? QBoxLayout::LeftToRight : QBoxLayout::TopToBottom);
    layout->setMargin(1);
    layout->setSpacing(0);
    layout->setObjectName(QString::number(objects_count++));
    for (int i = 0; i < children; i++)
        if (auto *child = makeLayouts(children, depth - 1, layout)) {
            if (i > 0) {
                auto *handle = new MyLayoutHandle(layout);
                layout->addWidget(handle);
            }
            layout->addLayout(child);
        }

    return layout;
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    auto *l0 = layout()->itemAt(0)->layout();
    if (!l0)
        return;
    auto g0 = l0->geometry();
    auto *l1 = layout()->itemAt(1)->layout();
    if (!l1)
        l1 = layout()->itemAt(2)->layout();
    auto g1 = l1->geometry();
    if (e->button() == Qt::LeftButton) {
        g0.setWidth(g0.width() + 10);
        g1.setLeft(g1.left() + 10);
    } else if (e->button() == Qt::RightButton) {
        g0.setWidth(g0.width() - 10);
        g1.setLeft(g1.left() - 10);
    }

    l0->setGeometry(g0);
    l1->setGeometry(g1);
}
