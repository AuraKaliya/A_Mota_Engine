#include "gameshowview.h"

#include <TOOL/editTool/editsystem.h>

GameShowView::GameShowView(QWidget *parent)
    : QGraphicsView(parent)
{
    setFixedSize(1052,752);
    //setBackgroundBrush(Qt::white);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void GameShowView::focusInEvent(QFocusEvent *event)
{
    emit getFocus();
}

void GameShowView::focusOutEvent(QFocusEvent *event)
{
    emit loseFocus();
}

void GameShowView::mouseMoveEvent(QMouseEvent *e)
{

    if(!this->scene()->selectedItems().empty())
    {
        QRect rect;
        rect.setRect(this->mapFromScene(this->scene()->selectedItems()[0]->pos()).x(),this->mapFromScene(this->scene()->selectedItems()[0]->pos()).y(),0,0);
        for(auto it:this->scene()->selectedItems())
        {
            rect.setX(qMin((int)rect.x(),(int)this->mapFromScene(it->pos()).x()));
            rect.setY(qMin((int)rect.y(),(int)this->mapFromScene(it->pos()).y()));
            rect.setWidth(qMax((int)rect.width(),(int)(it->x()+it->boundingRect().width()-rect.x())));
            rect.setHeight(qMax((int)rect.height(),(int)(it->y()+it->boundingRect().height()-rect.y())));
        }
        m_selectRect=rect;
    }
   QGraphicsView::mouseMoveEvent(e);
   viewport()->update();
}

void GameShowView::mouseReleaseEvent(QMouseEvent *e)
{

    QGraphicsView::mouseReleaseEvent(e);
    if(!this->scene()->selectedItems().empty())
    {
        QRect rect;
        rect.setRect(this->mapFromScene(this->scene()->selectedItems()[0]->pos()).x(),this->mapFromScene(this->scene()->selectedItems()[0]->pos()).y(),0,0);
        for(auto it:this->scene()->selectedItems())
        {
            rect.setX(qMin((int)rect.x(),(int)this->mapFromScene(it->pos()).x()));
            rect.setY(qMin((int)rect.y(),(int)this->mapFromScene(it->pos()).y()));
            rect.setWidth(qMax((int)rect.width(),(int)(it->x()+it->boundingRect().width()-rect.x())));
            rect.setHeight(qMax((int)rect.height(),(int)(it->y()+it->boundingRect().height()-rect.y())));

            qDebug()<<"now Pos!= :"<<it->pos().rx()<<it->pos().ry();
            static_cast<GameObjectItem*>(it)->getLinkObj()->setPosX(it->pos().rx());
            static_cast<GameObjectItem*>(it)->getLinkObj()->setPosY(it->pos().ry());
        }
        m_selectRect=rect;

        //qDebug()<<"***********";
        //qDebug()<<static_cast<GameObjectItem*>(this->scene()->selectedItems()[0])->getLinkObj();
        //qDebug()<<"***********";
        EditSystem::getInstance()->getManager()->setNowGameObjectItem(static_cast<GameObjectItem*>(this->scene()->selectedItems()[0]));
        EditSystem::getInstance()->getManager()->setNowGameObject(static_cast<GameObjectItem*>(this->scene()->selectedItems()[0])->getLinkObj());

    }

   viewport()->update();
}

void GameShowView::paintEvent(QPaintEvent *e)
{
    QGraphicsView::paintEvent(e);
    QPainter painters(this->viewport());
    if(!this->scene()->selectedItems().empty())
    {
        QPen pen(Qt::red,2,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);
        painters.setPen(pen);
        painters.drawRect(m_selectRect);
    }
}
