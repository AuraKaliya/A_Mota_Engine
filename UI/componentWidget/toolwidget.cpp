#include "toolwidget.h"

ToolWidget::ToolWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(500,210);

    m_headWidget=new WheelSlideWidget(this);
    m_headWidget->setWheelDirection(WheelSlideWidget::HDirection);
    m_headWidget->setGeometry(0,0,500,60);
    m_headWidget->setArea(500,60);
    m_headWidget->setVisible(true);


    m_bodyWidget=new WheelSlideWidget(this);
    m_bodyWidget->setWheelDirection(WheelSlideWidget::VDirection);
    m_bodyWidget->setGeometry(0,65,500,145);
    m_bodyWidget->setVisible(true);

    //setRatio(2,8);
}

void ToolWidget::setRatio(int headHeight, int bodyHeight)
{

}

QPushButton *ToolWidget::addBtnToHead(QPushButton *btn)
{
    if(btn!=nullptr)
    {
        btn->setFixedSize(m_headBtnSize,m_headBtnSize);
        m_headWidget->addWidgetInArea(btn,m_headSpacing+(m_headBtnList.size())*(m_headSpacing+m_headBtnSize),(m_headWidget->height()-m_headBtnSize)/2);
        //btn->setParent(m_headWidget);
        m_headBtnList.append(btn);
    }
    updateWidget();
    return btn;
}

QWidget *ToolWidget::addWidgetToBody(QWidget *widget)
{
    if(widget!=nullptr)
    {
        widget->setFixedWidth(this->width());
        m_bodyWidget->addWidgetInArea(widget,0,m_bodyWidgetSpacing+m_bodyWidgetList.size()*(m_bodyWidgetSpacing+widget->height()));
        //widget->setParent(m_bodyWidget);
        m_bodyWidgetList.append(widget);
    }
    updateWidget();
    return widget;
}

void ToolWidget::updateWidget()
{
    update();
//    //head
//    for(int i=0;i<m_headBtnList.size();++i)
//    {
//        m_headBtnList[i]->setGeometry(m_headSpacing+i*(m_headSpacing+m_headBtnSize),(m_headWidget->height()-m_headBtnSize)/2,m_headBtnSize,m_headBtnSize);
//    }

//    for(int i=0;i<m_bodyWidgetList.size();++i)
//    {
//        m_bodyWidgetList[i]->setGeometry(0,m_bodyWidgetSpacing+i*(m_bodyWidgetSpacing+m_bodyWidgetList[i]->height()),this->width(),m_bodyWidgetList[i]->height());
//    }

    //test---
    //m_bodyWidget->adjustSize();
}

int ToolWidget::headSpacing() const
{
    return m_headSpacing;
}

void ToolWidget::setHeadSpacing(int newHeadSpacing)
{
    m_headSpacing = newHeadSpacing;
}

int ToolWidget::bodyWidgetSpacing() const
{
    return m_bodyWidgetSpacing;
}

void ToolWidget::setBodyWidgetSpacing(int newBodyWidgetSpacing)
{
    m_bodyWidgetSpacing = newBodyWidgetSpacing;
}

int ToolWidget::headBtnSize() const
{
    return m_headBtnSize;
}

void ToolWidget::setHeadBtnSize(int newHeadBtnSize)
{
    m_headBtnSize = newHeadBtnSize;
}

void ToolWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    //m_headWidget->resize()


}
