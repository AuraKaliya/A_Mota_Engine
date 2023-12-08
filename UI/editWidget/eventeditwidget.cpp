#include "eventeditwidget.h"

#include <QBrush>
#include <ui/componentWidget/eventshowwidget.h>

EventEditWidget::EventEditWidget(QWidget *parent)
    : UIWidget{parent}
{
    resize(500,210);
    setVisible(true);
    //setStyleSheet("background-color:white;");
    //qDebug()<<"hello~~~";
    m_showWidget=new ToolWidget(this);
    m_showWidget->setGeometry(0,0,this->width(),this->height());
    m_showWidget->setVisible(true);



    //test

    QPushButton *b1=new QPushButton("Add");
    QPushButton *b2=new QPushButton("Del");
    QPushButton *b3=new QPushButton("Mod");

    m_showWidget->addBtnToHead(b1);
    m_showWidget->addBtnToHead(b2);
    m_showWidget->addBtnToHead(b3);

    b1->setVisible(true);
    b2->setVisible(true);
    b3->setVisible(true);


    for(auto it:EventSystem::getInstance()->getManager()->getEventList())
    {
        //qDebug()<<"&&&&"<<it;
        EventShowWidget *w1=new EventShowWidget();

         w1->initWidget(it);
//        for(auto it2:EventSystem::getInstance()->getManager()->getInsByEvent(it))
//        {
//        }
        m_showWidget->addWidgetToBody(w1);
        w1->setVisible(true);
        //qDebug()<<"&&&&Check"<<w1<<w1->geometry()<<w1->isVisible();
    }


    //w1->setStyleSheet("background-color:grey;");
    //    w1->setFixedWidth(500);
//    w1->addIns();
//    w1->addIns();
//    w1->addIns();
//    w1->show();
    //w1->setVisible(true);
    //test

}

ToolWidget *EventEditWidget::getShowWidget() const
{
    return m_showWidget;
}

void EventEditWidget::paintEvent(QPaintEvent *e)
{
//    QPainter painter(this);
//    painter.setBrush(QBrush(Qt::red));
//    painter.drawRect(this->rect());
}
