#include "gameobjectpropertiesshowwidget.h"

#include <QMetaProperty>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <QCoreApplication>

GameObject *GameObjectPropertiesShowWidget::getlinkObject() const
{
    return m_linkObject;
}

void GameObjectPropertiesShowWidget::setLinkObject(GameObject *newLinkObject)
{
    m_linkObject = newLinkObject;
}

GameObjectPropertiesShowWidget::GameObjectPropertiesShowWidget(QWidget *parent)
    : QWidget{parent}
{

    setObjectName("GameObjectPropertiesShowWidget");
}

void GameObjectPropertiesShowWidget::initShowArea()
{

    //先清除
    if(m_baseInfoWidget!=nullptr)
    {
        m_baseInfoWidget->setParent(nullptr);
       // m_baseInfoWidget->setVisible(false);
        //delete m_baseInfoWidget;
        m_baseInfoWidget->deleteLater();

    }

    if(m_componetInfoWidget!=nullptr)
    {
        m_componetInfoWidget->setParent(nullptr);
        // m_componetInfoWidget->setVisible(false);
        //delete m_componetInfoWidget;
        m_baseInfoWidget->deleteLater();

    }
    QCoreApplication::processEvents();
    m_componetInfoWidget=nullptr;
    m_baseInfoWidget=nullptr;

    m_showWidgetList.clear();
    m_propertyList.clear();
    m_optionLabelList.clear();
//    for(auto it=m_propertyList.begin();it!=m_propertyList.end();it++)
//    {
//        it->setParent(nullptr);
//        it->setVisible(false);
//        delete it;
//    }






    m_showRect.setRect(0,0,this->width(),this->height()*0.8);

    m_baseInfoWidget=new WheelSlideWidget(this);
    m_baseInfoWidget->setGeometry(m_showRect);
    m_baseInfoWidget->setVisible(true);

    m_componetInfoWidget=new WheelSlideWidget(this);
    m_componetInfoWidget->setGeometry(m_showRect);
    m_componetInfoWidget->setVisible(true);

    m_showWidgetList.append(m_baseInfoWidget);
    m_showWidgetList.append(m_componetInfoWidget);

    if(m_linkObject!=nullptr)
    {

        //GID GOClass Name Property?
        initBaseInfoWidget();
        initComponentInfoWidget();

//        //qDebug()<<"setVisible";
//        for(auto it:m_propertyList)
//        {
//            it->setVisible(true);
//            //qDebug()<<it->isVisible();
//        }

    }else
    {
        qDebug()<<"No LinkObject";
    }
    m_baseInfoWidget->raise();
}

void GameObjectPropertiesShowWidget::initBaseInfoWidget()
{

    QVector<QMetaProperty>* list=SourceSystem::getInstance()->getManager()->getGameObjectPropertyByObjectName(m_linkObject->getClassName());

    int spacing=5;
    for(int i=1,j=0;i<10;++i,++j)
    //for(int i=0;i<list->size();++i)
    {
        PropertyLabelWidget* w=new PropertyLabelWidget(m_baseInfoWidget);
        w->resize(180,50);
        w->setLink(m_linkObject,&(*list)[i]);
        w->setRatio(4,6,5,5);
        w->initWidget();
        w->setVisible(true);
        m_baseInfoWidget->addWidgetInArea(w,spacing+((j%2)*(w->width()+spacing)),spacing+((j/2)*(w->height()+spacing)));
        m_propertyList.append(w);
    }
    m_baseInfoWidget->setWheelDirection(WheelSlideWidget::VDirection);
    //qDebug()<<m_baseInfoWidget->children();

    //修改为property形式，在它中添加可编辑的判断，进行修改Name；
}

void GameObjectPropertiesShowWidget::initComponentInfoWidget()
{




    //获取GO的Component列表
    QVector<QString>* component=SourceSystem::getInstance()->getManager()->getComponentByGameObjectName(m_linkObject->getClassName());

    //qDebug()<<m_linkObject->getClassName()<<"   QVector<QMetaProperty>* vector:   "<<vector->size();
    //对每个Component生成一个Widget，获取component的属性

    qDebug()<<"component"<<*component;
   int widgetSpacing=10;
    for(int i=0;i<component->size();++i)
    {
        qDebug()<<"Now Component: "<<((*component)[i]);
        QVector<QMetaProperty>* vector=SourceSystem::getInstance()->getManager()->getComponentPropertyByComponentName((*component)[i]);

        QWidget * widget=new QWidget(m_componetInfoWidget);

        QLabel * titleLabel=new QLabel(widget);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setText((*component)[i]);
        titleLabel->setMinimumHeight(50);
        titleLabel->adjustSize();

        int headHeight=50;
        int spacing=5;
        qDebug()<<vector->size();
        for(int j=0;j<vector->size();++j)
        {
            //QPair<QString,QString> pair((*vector)[j].name(),(*vector)[j].read(m_linkObject->getMyComponents()[i]).toString());
            //qDebug()<<"Now Vector:"<<j<<pair;
            PropertyLabelWidget* w=new PropertyLabelWidget(widget);
            w->resize(180,50);
            //qDebug()<<pair;
            //w->setPair(pair.first,pair.second);
            w->setLink(m_linkObject->getMyComponents()[i],&(*vector)[j]);
            w->setRatio(3,7,5,5);
            w->initWidget();
            //qDebug()<<"end";
            w->move(spacing+((j%2)*(w->width()+spacing)),headHeight+spacing+((j/2)*(w->height()+spacing)));

            w->setVisible(true);
            //m_componetInfoWidget->addWidgetInArea(w,spacing+((i%2)*(w->width()+spacing)),spacing+((i/2)*(w->height()+spacing)));
            qDebug()<<"w:"<<w->geometry();

            if(m_hotUpdate)
            {
                w->setHotUpdate(true);
            }

            m_propertyList.append(w);
        }
        widget->setStyleSheet("background-color:blue");
        widget->adjustSize();
        widget->setVisible(true);

//        qDebug()<<"m_componetInfoWidget";
        m_componetInfoWidget->addWidgetInArea(widget,widgetSpacing+((i%1)*(widget->width()+widgetSpacing)),widgetSpacing+((i/1)*(widget->height()+widgetSpacing)));
//        qDebug()<<"m_componetInfoWidget end";
    }
//    qDebug()<<"hahaha4";
   m_componetInfoWidget->setWheelDirection(WheelSlideWidget::VDirection);
    //对属性进行可视化，作为初始编辑。
}

void GameObjectPropertiesShowWidget::initWidget()
{
    initShowArea();
    initOptionArea();
    for(auto it:m_optionLabelList)
    {
        it->setVisible(true);
        //qDebug()<<it->geometry();
    }
    //qDebug()<<"setVisible";
    for(auto it:m_propertyList)
    {
        it->setVisible(true);
        //qDebug()<<it->isVisible();
    }


    //qDebug()<<"initWidget end!";
    //qDebug()<<this->children();

}

void GameObjectPropertiesShowWidget::initProperty()
{
    if(m_linkObject==nullptr)
    {
        return ;
    }

}

QVector<PropertyLabelWidget *>* GameObjectPropertiesShowWidget::getPropertyList()
{
    if(m_propertyList.empty())
        return nullptr;
    return &m_propertyList;
}

void GameObjectPropertiesShowWidget::showWidgetSwitch(StateLabel *label)
{
    //新旧widget和它们的label
    int newIndex=m_optionLabelList.indexOf(label);
    qDebug()<<"newIndex "<<newIndex;
    WheelSlideWidget* newWidget=m_showWidgetList[newIndex];

    StateLabel *newLabel=label;
    if(newIndex!=m_nowShowWidgetIndex)
    {

        int oldIndex=m_nowShowWidgetIndex;
        StateLabel* oldLabel=m_optionLabelList[oldIndex];
        WheelSlideWidget* oldWidget=m_showWidgetList[oldIndex];
        //qDebug()<<"hahahahahaha";
        qDebug()<<oldWidget;
        QPropertyAnimation * oldWidgetAnimation=new QPropertyAnimation(oldWidget,"geometry");
        oldWidgetAnimation->setDuration(100);
        oldWidgetAnimation->setStartValue(oldWidget->geometry());
        //qDebug()<<"hahahahahaha2";
        QPropertyAnimation * newWidgetAnimation=new QPropertyAnimation(newWidget,"geometry");
        newWidgetAnimation->setDuration(100);
        newWidgetAnimation->setEndValue(QRect(oldWidget->x(),oldWidget->y(),newWidget->width(),newWidget->height()));
        //qDebug()<<"hahahahahaha3";
        QParallelAnimationGroup *group =new QParallelAnimationGroup();
        group->addAnimation(oldWidgetAnimation);
        group->addAnimation(newWidgetAnimation);

        //判定方向
        if(newIndex>oldIndex)
        {
            //new>old --向左移动
            oldWidgetAnimation->setEndValue(QRect(-oldWidget->width(),oldWidget->y(),oldWidget->width(),oldWidget->height()));
            newWidgetAnimation->setStartValue(QRect(oldWidget->x()+oldWidget->width(),oldWidget->y(),newWidget->width(),newWidget->height()));
        }else
        {
            //new<old --向右移动
            oldWidgetAnimation->setEndValue(QRect(oldWidget->x()+oldWidget->width(),oldWidget->y(),oldWidget->width(),oldWidget->height()));
            newWidgetAnimation->setStartValue(QRect(-oldWidget->width(),oldWidget->y(),newWidget->width(),newWidget->height()));
        }

        connect(group,&QParallelAnimationGroup::finished,this,[this](){
            m_showWidgetList[m_nowShowWidgetIndex]->raise();
            m_showWidgetList[m_nowShowWidgetIndex]->show();
            //qDebug()<<m_showWidgetList[m_nowShowWidgetIndex]->geometry();
            //qDebug()<<m_showWidgetList[m_nowShowWidgetIndex]->isVisible();
            //qDebug()<<m_showWidgetList[m_nowShowWidgetIndex]->children()[0];
            //QWidget*w2= static_cast<QWidget*>(m_showWidgetList[m_nowShowWidgetIndex]->children()[0]);
             //qDebug()<<w2->isVisible();
            //qDebug()<<m_showWidgetList[m_nowShowWidgetIndex]->children()[0]->children();
            for(auto it:m_showWidgetList[m_nowShowWidgetIndex]->children()[0]->children())
            {
                QWidget*w= static_cast<QWidget*>(it);
                w->setVisible(true);
                //qDebug()<<w->isVisible();
            }
           // qDebug()<<"finished";
            updateShow();
        });

        group->start(QAbstractAnimation::DeleteWhenStopped);
        newLabel->stateSwitchNext();
        oldLabel->stateSwitchNext();
        m_nowShowWidgetIndex=newIndex;
    }
}

void GameObjectPropertiesShowWidget::setHotUpdate(bool flag)
{
    m_hotUpdate=flag;
}

void GameObjectPropertiesShowWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        qDebug()<<"This Child"<<children();
        for(auto it:children())
        {
            QWidget* widget=static_cast<QWidget*>(it);
            qDebug()<<"Visible:"<<widget->isVisible();
            qDebug()<<"geo:"<<widget->frameGeometry();
        }

        qDebug()<<"m_propertyList"<<m_propertyList;



        for(auto it:m_propertyList)
        {
            qDebug()<<it->isVisible();
        }

        qDebug()<<"m_showWidgetList"<<m_showWidgetList;
        for(auto it:m_showWidgetList)
        {
            qDebug()<<it->isVisible();
        }

    }

}

void GameObjectPropertiesShowWidget::paintEvent(QPaintEvent *e)
{

//    QPainter painter(this);
//    painter.setPen(QPen(Qt::red));
//    for(auto it:m_showWidgetList)
//    {
//        qDebug()<<it->geometry();
//        painter.drawRect(it->geometry());
//    }


}

void GameObjectPropertiesShowWidget::initOptionArea()
{

    if(m_optionArea!=nullptr)
    {
        m_optionArea->setParent(nullptr);
        //m_optionArea->setVisible(false);
        delete m_optionArea;
        m_optionArea=nullptr;
        m_optionLabelList.clear();
    }

    m_optionArea=new WheelSlideWidget(this);
    m_optionArea->setGeometry(0,this->height()*0.8,this->width(),this->height()*0.2);
    m_optionArea->setBorder(5);
    m_optionArea->setWheelDirection(WheelSlideWidget::HDirection);
    m_optionArea->setArea(m_optionArea->width(),m_optionArea->height());
    m_optionArea->setVisible(true);

    //两个基本页面选项
    m_optionInfoLabel=new StateLabel("BaseInformation");
    m_optionInfoLabel->setStritagy(StateLabel::Function);
    m_optionInfoLabel->adjustSize();
    m_optionInfoLabel->setLinkWidget(m_baseInfoWidget);
    m_optionInfoLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_optionInfoLabel->setStateSwitch(SourceManageLabelState::Show,SourceManageLabelState::Hide);
    m_optionInfoLabel->setStateSwitch(SourceManageLabelState::Hide,SourceManageLabelState::Show);
    m_optionInfoLabel->setVisible(true);

    m_optionPropertyLabel=new StateLabel("Property");
    m_optionPropertyLabel->setStritagy(StateLabel::Function);
    m_optionPropertyLabel->adjustSize();
    m_optionPropertyLabel->setLinkWidget(m_componetInfoWidget);
    m_optionPropertyLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    m_optionPropertyLabel->setStateSwitch(SourceManageLabelState::Show,SourceManageLabelState::Hide);
    m_optionPropertyLabel->setStateSwitch(SourceManageLabelState::Hide,SourceManageLabelState::Show);
    m_optionPropertyLabel->setVisible(true);

    m_optionLabelList.append(m_optionInfoLabel);
    m_optionLabelList.append(m_optionPropertyLabel);

    int spacing=10;
    for(int i=0;i<m_optionLabelList.size();++i)
    {
        m_optionArea->addWidgetInArea(m_optionLabelList[i],spacing+i*(m_optionInfoLabel->width()+spacing),0);
        //添加切换逻辑和动画
        connect(m_optionLabelList[i],&StateLabel::me,this,[this](ClickLabel* label){
            StateLabel* tmpLabel=static_cast<StateLabel*>(label);
            showWidgetSwitch(tmpLabel);
        });
        connect(m_optionLabelList[i],&StateLabel::labelStateChanged,this,[](StateLabel* thisLabel,SourceManageLabelState state){
            switch (state) {
            case SourceManageLabelState::Show:
                thisLabel->setStyleSheet("background-color:blue");
                break;
            case SourceManageLabelState::Hide:
                thisLabel->setStyleSheet("background-color:red");
                break;
            default:
                break;
            }
        });
        m_optionLabelList[i]->setNowState(SourceManageLabelState::Hide);
    }
    m_optionLabelList[m_nowShowWidgetIndex]->setNowState(SourceManageLabelState::Show);

//    m_optionArea->addWidgetInArea(m_optionInfoLabel,0,0);
//    m_optionArea->addWidgetInArea(m_optionPropertyLabel,10+m_optionInfoLabel->width(),0);


}

void GameObjectPropertiesShowWidget::updateShow()
{
    for(auto it:m_showWidgetList)
    {
        it->setVisible(true);
    }
    for(auto it:m_optionLabelList)
    {
        it->setVisible(true);
    }
    for(auto it:m_propertyList)
    {
        it->setVisible(true);
    }
}
