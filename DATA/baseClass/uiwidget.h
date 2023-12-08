#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>

/*
    引擎的页面的抽象基类，提供构建页面的基础处理方法。

--  Init
--  SetxxX
*/


class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    virtual void init();
signals:

};

#endif // UIWIDGET_H
