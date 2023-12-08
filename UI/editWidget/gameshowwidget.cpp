#include "gameshowwidget.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <DATA/baseClass/gameobjectitem.h>

GameShowWidget::GameShowWidget(QWidget *parent)
    :UIWidget{parent}
{

    setFixedSize(1050,800);
    setVisible(true);
    m_gameShowView=new GameShowView(this);
    m_gameShowView->setVisible(true);


    dropWidget=new GameObjectDropWidget(this);
    dropWidget->setGeometry(0,0,1050,750);
    dropWidget->setLinkView(m_gameShowView);
    dropWidget->raise();

    setFocusPolicy(Qt::ClickFocus);


    connect(m_gameShowView,&GameShowView::getFocus,this,[this](){
        dropWidgetHide();
    });
    connect(m_gameShowView,&GameShowView::loseFocus,this,[this](){

        dropWidgetShow();
    });


}

void GameShowWidget::init()
{
    m_gameShowView->setScene(EditSystem::getInstance()->getManager()->getNowScene());
    m_gameShowView->centerOn(QPointF((m_gameShowView->width()-2)/2,(m_gameShowView->height()-2)/2));

    qDebug()<<"Scene:"<<m_gameShowView->sceneRect();
}

void GameShowWidget::dropWidgetShow()
{
    dropWidget->resize(1050,750);
    dropWidget->setEnabled(true);
    dropWidget->show();
    dropWidget->raise();
    //qDebug()<<"stylesheet"<<dropWidget->styleSheet();
    //qDebug()<<dropWidget->geometry();
    //qDebug()<<"dropWidget"<<dropWidget->isVisible()<<dropWidget->isActiveWindow();
    //qDebug()<<"show";
}

void GameShowWidget::dropWidgetHide()
{
    dropWidget->resize(0,0);
    dropWidget->setEnabled(false);
    dropWidget->hide();
    //qDebug()<<"stylesheet"<<dropWidget->styleSheet();
    //qDebug()<<dropWidget->geometry();
    //qDebug()<<"dropWidget"<<dropWidget->isVisible()<<dropWidget->isActiveWindow();
   // qDebug()<<"hide";
}

void GameShowWidget::mouseMoveEvent(QMouseEvent *e)
{
    m_mousePos=e->pos();
    //qDebug()<<"-------------";
    //qDebug()<<m_mousePos;
}

void GameShowWidget::focusInEvent(QFocusEvent *event)
{
    qDebug()<<"GameShowWidget focusInEvent";
    if(!m_gameShowView->hasFocus())
    {

    //dropWidget->setVisible(false);
     dropWidgetHide();
    //qDebug()<<"dropWidget"<<dropWidget->isVisible()<<dropWidget->isActiveWindow();
    }
}

void GameShowWidget::focusOutEvent(QFocusEvent *event)
{


    qDebug()<<"GameShowWidget focusOutEvent";
       //qDebug()<<focusWidget();
    if(focusWidget()!=m_gameShowView)
    {
        //dropWidget->setVisible(true);
        dropWidgetShow();
        //qDebug()<<"dropWidget"<<dropWidget->isVisible()<<dropWidget->isActiveWindow();
    }

}

void GameShowWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void GameShowWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(!m_gameShowView->scene()->selectedItems().empty())
    {
        QRect rect;

        rect.setRect(m_gameShowView->mapFromScene(m_gameShowView->scene()->selectedItems()[0]->pos()).x(),m_gameShowView->mapFromScene(m_gameShowView->scene()->selectedItems()[0]->pos()).y(),0,0);
        for(auto it:m_gameShowView->scene()->selectedItems())
        {
            rect.setX(qMin((int)rect.x(),(int)m_gameShowView->mapFromScene(it->pos()).x()));
            rect.setY(qMin((int)rect.y(),(int)m_gameShowView->mapFromScene(it->pos()).y()));
            rect.setWidth(qMax((int)rect.width(),(int)(it->x()+it->boundingRect().width()-rect.x())));
            rect.setHeight(qMax((int)rect.height(),(int)(it->y()+it->boundingRect().height()-rect.y())));
        }
        QPen pen(Qt::red,3,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawRect(rect);
        painter.end();
    }
}

