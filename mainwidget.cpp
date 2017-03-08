#include "mainwidget.h"
#include "colorwidget.h"
#include "mysplitter.h"
#include "layouthandle.h"
#include <QtWidgets>

int MainWidget::objects_count = 0;
bool MainWidget::call_winId = false;

MainWidget::MainWidget(bool use_splitters, QWidget *parent)
    : QWidget(parent)
{
    objects_count = 0;
    ColorWidget::resetCount();

    if (use_splitters) {
        auto *layout = new QVBoxLayout;
        layout->setMargin(0);
        layout->addWidget(makeSplitters(3, 5));
        setLayout(layout);
    } else {
        setLayout(makeLayouts(3, 5));
    }
}

MainWidget::~MainWidget()
{

}

QWidget *MainWidget::makeSplitters(int children, int depth) const
{
    if (depth == 0) {
        auto *w = new ColorWidget();
        if (call_winId)
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
        if (call_winId)
            w->winId();
        parent->addWidget(w);
        return nullptr;
    }

    auto *layout = new QBoxLayout((depth & 1) ? QBoxLayout::LeftToRight : QBoxLayout::TopToBottom);
    layout->setMargin(1);
    layout->setSpacing(0);
    layout->setObjectName(QLatin1Char('l') + QString::number(objects_count++));
    for (int i = 0; i < children; i++) {
        auto *child = makeLayouts(children, depth - 1, layout);
        if (child)
            layout->addLayout(child);
        if (i < children - 1) {
            auto *handle = new LayoutHandle(layout);
            const QLatin1String prefix("layout_handle_");
            const QString &siblingName = child ? child->objectName()
                                         : layout->itemAt(layout->count() - 1)->widget()->objectName();
            handle->setObjectName(prefix + siblingName);
            layout->addWidget(handle);
        }
    }

    return layout;
}
