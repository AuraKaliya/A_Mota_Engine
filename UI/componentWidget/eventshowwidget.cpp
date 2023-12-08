#include "eventshowwidget.h"

#include <QPainter>
#include <QPainterPath>

EventShowWidget::EventShowWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedWidth(500);
    setStyleSheet("border-radius:10;background-color:grey;");

    //test
    //QPainterPath PainterPath;	//绘制一个QPainter路径对象
    //PainterPath.addRoundedRect(this->rect(), 15, 15);	//对它设置路径为四周圆角。10即圆角的深度，可以修改
    //QRegion mask = QRegion(PainterPath.toFillPolygon().toPolygon());	//创建遮罩对象，内容即该QPainter路径
    //this->setMask(mask);

    //test

    m_eventBox=new QLineEdit(this);
    m_eventBox->setGeometry(10,10,200,40);

    m_addWidget=new QWidget(this);
    m_addWidget->resize(200,40);
    m_addWidget->setStyleSheet("background-color:green");
    m_addWidget->move(290,spacing);
    m_insWidget.append(m_addWidget);
    m_insLayer<<-1;

    //--Need--
    // 需要有一个connect   绑定添加按钮被按下时与system交互添加Ins的行为。


}

void EventShowWidget::initWidget(QString eventName)
{
    //从系统中获取event对应的指令列表
    auto list=EventSystem::getInstance()->getManager()->getInsByEvent(eventName);
    //获取每个指令的指令名，构建相应的指令窗体
    if(list.size()>0)
    {
        m_eventBox->setText(eventName);
        //qDebug()<<"hhaha"<<eventName;
        for(auto it:list)
        {
            QString insName=it->getInsName();
            if(insName!="")
            {
                addIns(insName);
            }
        }
    }
    //其他细节的连接

    // 点击窗体弹出修改Ins的界面

}

void EventShowWidget::updateWidget()
{

    for(int i=1,j=0;i!=-1;i=m_insLayer[i],++j)
    {
        m_insWidget[i]->move(290,spacing+j*(spacing+m_insWidget[i]->height()));
        m_insWidget[i]->setVisible(true);
    }
    adjustSize();
    update();
}

QWidget *EventShowWidget::addIns()
{
    //Test function
    //出现一个消息框，根据消息框内容JSON添加Ins

    QWidget* w=new QWidget(this);

    if(m_insWidget.size()%2==0)
    {
        w->setStyleSheet("background-color:red");
    }else
    {
        w->setStyleSheet("background-color:blue");
    }
    qDebug()<<"addIns";
    w->resize(200,40);
    w->setVisible(true);
    m_insWidget.append(w);

    if(!(m_insWidget.size()>2))
    {
        m_insLayer<<0;
    }
    else
    {
        m_insLayer[m_insLayer.size()-1]=m_insWidget.size()-1;
        m_insLayer<<0;
    }
    updateWidget();
    return w;
}

QWidget *EventShowWidget::addIns(QString insName)
{
    qDebug()<<"EventShowWidget::addIns(str) "<<insName;

    //出现一个消息框，根据消息框内容JSON添加Ins
    QLabel* w=new QLabel(this);

    if(m_insWidget.size()%2==0)
    {
        w->setStyleSheet("background-color:red");
    }else
    {
        w->setStyleSheet("background-color:blue");
    }
    //qDebug()<<"addIns";
    w->resize(200,40);
    w->setVisible(true);
    w->setText(insName);

    m_insWidget.append(w);

    if(!(m_insWidget.size()>2))
    {
        m_insLayer<<0;
    }
    else
    {
        m_insLayer[m_insLayer.size()-1]=m_insWidget.size()-1;
        m_insLayer<<0;
    }
    updateWidget();
    return w;
}

void EventShowWidget::paintEvent(QPaintEvent *e)
{
    //qDebug()<<"hahahaha``";
//    qDebug()<<"this"<<this->geometry();
      QPainter painter(this);
    //painter.setBrush(QBrush(Qt::black));
    //painter.drawRect(0,0,width()-1,height()-1);
    //painter.setBrush(QBrush());

    //test

    //QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    painter.setClipping(true);
    QPainterPath canDrawingPathArea; // 能画上的区域
    canDrawingPathArea.addRoundedRect(rect(), 10, 10);
    canDrawingPathArea.setFillRule(Qt::WindingFill); // 多块区域组合填充模式
    painter.setClipPath(canDrawingPathArea);

    QColor color(Qt::darkRed);
    color.setAlpha(200);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawRect(rect());
    painter.setBrush(QBrush());
    //test



    QPen pen;

    // step1;
    QPoint start(m_eventBox->x()+m_eventBox->width(),m_eventBox->y()+m_eventBox->height()/2);
    QPoint end(290,spacing+m_addWidget->height()/2);

    qDebug()<<start<<end;

    pen.setWidth(2);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(start,end);

    //draw point
    pen.setWidth(8);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(start);
    painter.drawPoint(end);



    //setp2;
    QPoint start2(250,spacing+m_addWidget->height()/2);
    QPoint end2(250,spacing+(m_insWidget.size()-1)*(m_addWidget->height()+spacing)+m_addWidget->height()/2);
    pen.setWidth(2);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(start2,end2);



    //setp3;
    for(int i=1;i<m_insWidget.size();++i)
    {
        QPoint start3(250,spacing+(i)*(m_addWidget->height()+spacing)+m_addWidget->height()/2);
        QPoint end3(290,spacing+(i)*(m_addWidget->height()+spacing)+m_addWidget->height()/2);
        pen.setWidth(2);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawLine(start3,end3);

        pen.setWidth(8);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.drawPoint(end3);
    }

}
