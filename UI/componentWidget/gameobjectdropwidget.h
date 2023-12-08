#ifndef GAMEOBJECTDROPWIDGET_H
#define GAMEOBJECTDROPWIDGET_H

#include <QWidget>
#include <UI/componentWidget/gameshowview.h>
class GameObjectDropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameObjectDropWidget(QWidget *parent = nullptr);
    void setLinkView(QGraphicsView* view);

protected:
    void dragEnterEvent(QDragEnterEvent*e)override;
    void dropEvent(QDropEvent*e)override;
    void dragMoveEvent(QDragMoveEvent *e)override;
    void mouseMoveEvent(QMouseEvent*e)override;
    void mousePressEvent(QMouseEvent*e)override;

private:
    QGraphicsView* m_linkView=nullptr;
    QPointF m_mousePos;
signals:

};

#endif // GAMEOBJECTDROPWIDGET_H
