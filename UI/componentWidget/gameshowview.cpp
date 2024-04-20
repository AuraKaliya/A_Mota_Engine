#include "gameshowview.h"

#include <TOOL/editTool/editsystem.h>

GameShowView::GameShowView(QWidget *parent)
    : QGraphicsView(parent)
{



    //setFixedSize(1050,750);
    //setBackgroundBrush(Qt::white);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
        //+((width()-scene()->width())/2)
        //+((height()-scene()->height())/2)
        rect.setRect(this->mapFromScene(this->scene()->selectedItems()[0]->pos()).x(),
                     this->mapFromScene(this->scene()->selectedItems()[0]->pos()).y(),
                     0,0);
        for(auto it:this->scene()->selectedItems())
        {
            //+((width()-scene()->width())/2)
            //+((height()-scene()->height())/2)
            rect.setX(qMin((int)rect.x(),(int)(this->mapFromScene(it->pos()).x())));
            rect.setY(qMin((int)rect.y(),(int)(this->mapFromScene(it->pos()).y())));
            rect.setWidth(qMax((int)rect.width(),(int)(it->x()+it->boundingRect().width()-rect.x()+((width()-scene()->width())/2))));
            rect.setHeight(qMax((int)rect.height(),(int)(it->y()+it->boundingRect().height()-rect.y()+((height()-scene()->height())/2))));

            qDebug()<<"now Pos!= :"<<it->pos().rx()<<it->pos().ry();
            static_cast<GameObjectItem*>(it)->getLinkObj()->setPosX(it->pos().rx());
            static_cast<GameObjectItem*>(it)->getLinkObj()->setPosY(it->pos().ry());
        }
        m_selectRect=rect;
        qDebug()<<"GameShowView::mouseReleaseEvent  rect"<<m_selectRect;
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
    QPainter painterBackground(this->viewport());

    if(EngineStyle::getInstance()->styleName()=="Night")
    {
        painterBackground.fillRect(this->rect(), Qt::darkGray); // 深灰色背景
    }
    else
    {
        painterBackground.fillRect(this->rect(), Qt::white);// 纯白色背景
    }
    painterBackground.end();

    QGraphicsView::paintEvent(e);
    QPainter painterSelect(this->viewport());
    //painterSelect.begin(this->viewport());
    if(!this->scene()->selectedItems().empty())
    {
        QPen pen(Qt::red,2,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);
        painterSelect.setPen(pen);
        painterSelect.drawRect(m_selectRect);
    }
    painterSelect.end();
}
