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

    DIYButton *b1=new DIYButton("SkyBlue");
    DIYButton *b2=new DIYButton("DeepPink");
    DIYButton *b3=new DIYButton("DarkOrchid");

    b1->setPix(":/RESOURCE/default/newInstruction.png");
    b2->setPix(":/RESOURCE/default/deleteInstruction.png");
    b3->setPix(":/RESOURCE/default/editInstruction.png");

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
    setUIStyle();
}

ToolWidget *EventEditWidget::getShowWidget() const
{
    return m_showWidget;
}

void EventEditWidget::setUIStyle()
{
    QString style;
    if(EngineStyle::getInstance()->styleName()=="Night")
    {
        style=
            "EventShowWidget{border-radius:10px;background-color:rgba(157,162,160,0.5);}";
    }
    else
    {
        style=
            "EventShowWidget{border-radius:10px;background-color:rgba(248,249,250,0.2);}";
    }

    setStyleSheet(style);
}

void EventEditWidget::paintEvent(QPaintEvent *e)
{
//    QPainter painter(this);
//    painter.setBrush(QBrush(Qt::red));
//    painter.drawRect(this->rect());

    UIWidget::paintEvent(e);
    QPainter painter(this);

    if(EngineStyle::getInstance()->styleName()=="Night")
    {
        painter.fillRect(this->rect(),QBrush(Qt::darkGray));
    }
    else
    {
        QImage  img(":/RESOURCE/default/Background1.png");
        painter.drawImage(this->rect(),img);
    }

    painter.end();

}
