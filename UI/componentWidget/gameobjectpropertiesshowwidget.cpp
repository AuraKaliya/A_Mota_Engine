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
        m_baseInfoWidget->clearWidgetList();
        m_baseInfoWidget->deleteLater();
    }

    if(m_componetInfoWidget!=nullptr)
    {
        m_componetInfoWidget->setParent(nullptr);
        m_componetInfoWidget->clearWidgetList();
        m_componetInfoWidget->deleteLater();
    }

    QCoreApplication::processEvents();

    m_componetInfoWidget=nullptr;
    m_baseInfoWidget=nullptr;

    m_showWidgetList.clear();
    m_propertyList.clear();
    m_optionLabelList.clear();

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
    }else
    {
        qDebug()<<"No LinkObject";
    }
    m_baseInfoWidget->raise();
}

void GameObjectPropertiesShowWidget::initBaseInfoWidget()
{
    QVector<QMetaProperty>* list=SourceSystem::getInstance()->getManager()->getGameObjectPropertyByObjectName(m_linkObject->getClassName());

    int spacing=0;

    //固定设置----九个-----基础属性
    //原先： 180*50   一行两个--
    // 现在： 390 * 50  一行一个

    for(int i=1,j=0;i<10;++i,++j)
    {
        PropertyLabelWidget* w=new PropertyLabelWidget(m_baseInfoWidget);
        w->resize(400,50);
        w->setLink(m_linkObject,&(*list)[i]);
        w->setRatio(4,6,5,0);
        w->initWidget();
        w->setVisible(true);
        //原先
        //m_baseInfoWidget->addWidgetInArea(w,spacing+((j%2)*(w->width()+spacing)),spacing+((j/2)*(w->height()+spacing)));
        //现在
        m_baseInfoWidget->addWidgetInArea(w,spacing,spacing+((j)*(w->height()+spacing)));

        m_propertyList.append(w);
    }
    m_baseInfoWidget->setWheelDirection(WheelSlideWidget::VDirection);

    //修改为property形式，在它中添加可编辑的判断，进行修改Name；
}

void GameObjectPropertiesShowWidget::initComponentInfoWidget()
{
    //qDebug()<<"==================void GameObjectPropertiesShowWidget::initComponentInfoWidget()================";
    //获取GO的Component列表
    QVector<QString>* component=SourceSystem::getInstance()->getManager()->getComponentByGameObjectName(m_linkObject->getClassName());
    //对每个Component生成一个Widget，获取component的属性
   int widgetSpacing=10;
    for(int i=0;i<component->size();++i)
    {
        QVector<QMetaProperty>* vector=SourceSystem::getInstance()->getManager()->getComponentPropertyByComponentName((*component)[i]);

        QWidget * widget=new QWidget(m_componetInfoWidget);

        QLabel * titleLabel=new QLabel(widget);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setText((*component)[i]);

        titleLabel->setFont(EngineStyle::getInstance()->thirdTitleFont());

        titleLabel->setMinimumHeight(30);
        titleLabel->adjustSize();
        titleLabel->move(0,0);

        int headHeight=titleLabel->height();
        int spacing=0;
        qDebug()<<vector->size();
        for(int j=0;j<vector->size();++j)
        {
            PropertyLabelWidget* w=new PropertyLabelWidget(widget);
            w->setFixedSize(400,50);
            w->setLink(m_linkObject->getMyComponents()[i],&(*vector)[j]);
            w->setRatio(4,6,5,0);
            w->initWidget();
            //原先
            //w->move(spacing+((j%2)*(w->width()+spacing)),headHeight+spacing+((j/2)*(w->height()+spacing)));
            //现在
            w->move(spacing,spacing+headHeight+((j)*(w->height()+spacing)));
            w->setVisible(true);
            if(m_hotUpdate)
            {
                w->setHotUpdate(true);
            }

            m_propertyList.append(w);
        }

        widget->setFixedHeight(headHeight+spacing+(((vector->size()))*(50+spacing))+50);
        widget->setVisible(true);

        QWidget* lastWidget=m_componetInfoWidget->getLastWidget();
        if(lastWidget==nullptr)
        {
            m_componetInfoWidget->addWidgetInArea(widget,0,0);
        }
        else
        {
            m_componetInfoWidget->addWidgetInArea(widget,0,lastWidget->y()+lastWidget->height()+widgetSpacing);
        }

        //qDebug()<<"Check:componet widget"<<widget->geometry()<<"====="<<((i/1)*(widget->height()+widgetSpacing));
    }

   m_componetInfoWidget->setWheelDirection(WheelSlideWidget::VDirection);
    //对属性进行可视化，作为初始编辑。
   //qDebug()<<"==================void GameObjectPropertiesShowWidget::initComponentInfoWidget()================end";
}

void GameObjectPropertiesShowWidget::initWidget()
{
    initShowArea();
    initOptionArea();

    for(auto it:m_optionLabelList)
    {
        it->setVisible(true);
    }
    for(auto it:m_propertyList)
    {
        it->setVisible(true);
    }

    for(auto it: m_optionLabelList)
    {
        it->setNowState(SourceManageLabelState::Hide);
    }
    for(auto it: m_showWidgetList)
    {
        it->hide();
    }

    //m_showWidgetList[0]->show();
    m_nowShowWidgetIndex=0;
    m_showWidgetList[m_nowShowWidgetIndex]->raise();
    m_showWidgetList[m_nowShowWidgetIndex]->show();

    m_optionLabelList[0]->setNowState(SourceManageLabelState::Show);
    m_optionLabelList[0]->setStyleSheet("border-radius:10px;color: white;background-color:rgba(52,58,64,0.6);");

    update();
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
            for(auto it:m_showWidgetList[m_nowShowWidgetIndex]->children()[0]->children())
            {
                QWidget*w= static_cast<QWidget*>(it);
                w->setVisible(true);
            }
           // qDebug()<<"finished";
            //updateShow();
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
        //qDebug()<<"This Child"<<children();
        for(auto it:children())
        {
            QWidget* widget=static_cast<QWidget*>(it);
            //qDebug()<<"Visible:"<<widget->isVisible();
            //qDebug()<<"geo:"<<widget->frameGeometry();
        }

        //qDebug()<<"m_propertyList"<<m_propertyList;
        for(auto it:m_propertyList)
        {
            //qDebug()<<it->isVisible();
        }

        //qDebug()<<"m_showWidgetList"<<m_showWidgetList;
        for(auto it:m_showWidgetList)
        {
           // qDebug()<<it->isVisible();
        }
    }
}

void GameObjectPropertiesShowWidget::paintEvent(QPaintEvent *e)
{

}

void GameObjectPropertiesShowWidget::initOptionArea()
{

    if(m_optionArea!=nullptr)
    {
        m_optionArea->setParent(nullptr);
        delete m_optionArea;
        m_optionArea=nullptr;
        m_optionLabelList.clear();
    }

    m_optionArea=new WheelSlideWidget(this);
    m_optionArea->setMinimumHeight(60);
    m_optionArea->setGeometry(0,this->height()*0.8,this->width(),this->height()*0.2);
    m_optionArea->setBorder(5);
    m_optionArea->setWheelDirection(WheelSlideWidget::HDirection);
    m_optionArea->setArea(m_optionArea->width(),m_optionArea->height());
    m_optionArea->setVisible(true);

    //两个基本页面选项
    m_optionInfoLabel=new StateLabel("Base");
    m_optionPropertyLabel=new StateLabel("Property");

    m_optionLabelList.append(m_optionInfoLabel);
    m_optionLabelList.append(m_optionPropertyLabel);

    //用于点击切换的label的初始化
    // 1.设置大小  2， 放入area中  3， 设置切换样式
    int spacing=10;
    for(int i=0;i<m_optionLabelList.size();++i)
    {
        //初始设置
        m_optionLabelList[i]->setStritagy(StateLabel::Function);
        m_optionLabelList[i]->setLinkWidget(m_componetInfoWidget);
        m_optionLabelList[i]->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        m_optionLabelList[i]->setStateSwitch(SourceManageLabelState::Show,SourceManageLabelState::Hide);
        m_optionLabelList[i]->setStateSwitch(SourceManageLabelState::Hide,SourceManageLabelState::Show);
        m_optionLabelList[i]->setVisible(true);

        //位置
        m_optionLabelList[i]->setMinimumHeight(50);
        m_optionLabelList[i]->setMinimumWidth(80);
        m_optionArea->addWidgetInArea(m_optionLabelList[i],spacing+i*(m_optionInfoLabel->width()+spacing),0);
        //字体
        m_optionLabelList[i]->setFont(EngineStyle::getInstance()->thirdTitleFont());

        m_optionLabelList[i]->setAlignment(Qt::AlignCenter);

        //添加切换逻辑和动画
        connect(m_optionLabelList[i],&StateLabel::me,this,[this](ClickLabel* label){
            StateLabel* tmpLabel=static_cast<StateLabel*>(label);
            showWidgetSwitch(tmpLabel);
        });
        connect(m_optionLabelList[i],&StateLabel::labelStateChanged,this,[](StateLabel* thisLabel,SourceManageLabelState state){
            switch (state) {
            case SourceManageLabelState::Show:
                //thisLabel->setStyleSheet("background-color:blue");
                thisLabel->setStyleSheet("border-radius:10px;color: white;background-color:rgba(52,58,64,0.6);");
                break;
            case SourceManageLabelState::Hide:
                //thisLabel->setStyleSheet("background-color:red");
                thisLabel->setStyleSheet("border-radius:10px;color: white;background-color:rgba(52,58,64,0.2);");
                break;
            default:
                break;
            }
        });
        m_optionLabelList[i]->setNowState(SourceManageLabelState::Hide);
    }
    update();
    //m_optionLabelList[0]->setNowState(SourceManageLabelState::Hide);

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
