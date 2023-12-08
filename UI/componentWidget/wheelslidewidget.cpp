#include "wheelslidewidget.h"

#include <QWheelEvent>

QWidget *WheelSlideWidget::getArea() const
{
    return m_area;
}

void WheelSlideWidget::setArea(QWidget *newArea)
{
    m_area = newArea;
}

void WheelSlideWidget::setArea(int width, int height)
{
    if(m_area!=nullptr)
    {
        m_area->setMinimumSize(width,height);
    }
}

void WheelSlideWidget::addWidgetInArea(QWidget *w, int x, int y)
{
    w->setParent(m_area);
    w->move(x,y);
    m_area->adjustSize();

}

int WheelSlideWidget::getBorder() const
{
    return m_border;
}

void WheelSlideWidget::setBorder(int newBorder)
{
    m_border = newBorder;
    redoMove();
}

void WheelSlideWidget::updateArea()
{
    m_area->adjustSize();
}

WheelSlideWidget::WheelSlideWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(400,400);
    setStyleSheet("background-color:grey;");

    m_area=new QWidget(this);
    m_area->move(0,0);
    m_area->setStyleSheet("background-color:white;");
    setArea(width(),height());
}

void WheelSlideWidget::setWheelDirection(wheelDirection direction)
{
    m_wheelDirection=direction;
    if(m_wheelDirection&NoDirection)
    {
        m_area->setMinimumSize(0,0);
    }
    else if(m_wheelDirection&VDirection)
    {
        m_area->setMinimumWidth(this->width());
    }
    else if(m_wheelDirection&HDirection)
    {
        m_area->setMinimumHeight(this->height());
    }
}

void WheelSlideWidget::wheelEvent(QWheelEvent *e)
{
   // qDebug()<<"m_wheelDirection&NoDirection "<<(m_wheelDirection&NoDirection);
    //qDebug()<<"m_wheelDirection&VDirection "<<(m_wheelDirection&VDirection);
   // qDebug()<<"m_wheelDirection&HDirection "<<(m_wheelDirection&HDirection);

    //qDebug()<<
    if(m_wheelDirection&NoDirection)
    {
        qDebug()<<"NoDirection";
    }
    else if(m_wheelDirection&VDirection)
    {
        int delta=e->angleDelta().y();
        m_area->move(m_area->x(),m_area->y()+delta);
    }
    else if(m_wheelDirection&HDirection)
    {
       // qDebug()<<"ha";

        int delta=e->angleDelta().y();
       // qDebug()<<delta;
       // qDebug()<<"geo"<<m_area->geometry();
        m_area->move(m_area->x()+delta,m_area->y());
       // qDebug()<<"geo"<<m_area->geometry();
    }
    redoMove();
}

void WheelSlideWidget::resizeEvent(QResizeEvent *e)
{

    if(m_wheelDirection&NoDirection)
    {
        m_area->setMinimumSize(0,0);
    }
    else if(m_wheelDirection&VDirection)
    {
        m_area->setMinimumWidth(this->width());
    }
    else if(m_wheelDirection&HDirection)
    {
        m_area->setMinimumHeight(this->height());
    }
}

void WheelSlideWidget::redoMove()
{
   // qDebug()<<"area: x"<<m_area->x()<<" y"<<m_area->y();
    int nowY=m_area->y();
    int heightLimit=this->height();
    if(nowY+m_area->height()<heightLimit)
    {
        m_area->move(m_area->x(),heightLimit-m_area->height()-m_border);
    }
    else if(nowY>m_border)
    {
        m_area->move(m_area->x(),m_border);
    }

    int nowX=m_area->x();
    int widthLimit=this->width();
    if(nowX+m_area->width()<widthLimit)
    {
        m_area->move(widthLimit-m_area->width()-m_border,m_area->y());
    }
    else if(nowX>m_border)
    {
        m_area->move(m_border,m_area->y());
    }
   // qDebug()<<"area: x"<<m_area->x()<<" y"<<m_area->y();
}
