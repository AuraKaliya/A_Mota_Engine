#ifndef GAMESHOWWIDGET_H
#define GAMESHOWWIDGET_H


#include<DATA/baseClass/uiwidget.h>
#include<UI/componentWidget/gameshowview.h>
#include <UI/componentWidget/gameobjectdropwidget.h>
#include <TOOL/editTool/editsystem.h>

/*
 * 在GameShowView中显示渲染
    1.对GameObject在窗体内的显示和渲染，不参与逻辑控制，只负责渲染
    2.每次渲染（帧）获取GameObject实例的数据，进行图形的渲染

*/
class GameShowWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit GameShowWidget(QWidget *parent = nullptr);
    void init()override;
    void dropWidgetShow();
    void dropWidgetHide();
protected:

    void mouseMoveEvent(QMouseEvent*e)override;
    void focusInEvent(QFocusEvent *event)override;
    void focusOutEvent(QFocusEvent *event)override;
    void mouseReleaseEvent(QMouseEvent* e)override;
    void paintEvent(QPaintEvent* e)override;
private:
    GameShowView* m_gameShowView=nullptr;
    GameObjectDropWidget* dropWidget=nullptr;
    QPoint m_mousePos;
signals:

};

#endif // GAMESHOWWIDGET_H
