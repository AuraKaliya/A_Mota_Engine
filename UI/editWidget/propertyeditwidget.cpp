#include "propertyeditwidget.h"

PropertyEditWidget::PropertyEditWidget(QWidget *parent)
    : UIWidget{parent}
{
    int spacing=10;
    resize(400,600);
    //setFixedSize(400,600);
    m_showWidget=new WheelSlideWidget(this);
    //
    setStyleSheet("background-color:blue;");
    //
    m_showWidget->setGeometry(10,10,width(),height());
    m_showWidget->setWheelDirection(WheelSlideWidget::VDirection);
    m_showWidget->setArea(this->width(),this->height());

    m_gameObjectPropertiewShowWidget=new GameObjectPropertiesShowWidget(m_showWidget);
    m_gameObjectPropertiewShowWidget->setFixedSize(400,300);
    m_gameObjectPropertiewShowWidget->initWidget();
    m_gameObjectPropertiewShowWidget->setHotUpdate(true);

    //可迁移到updateWidget中   ---已迁移
//    connect(this,&PropertyEditWidget::linkObjectChanged,m_gameObjectPropertiewShowWidget,[this](GameObject* obj){
//        m_gameObjectPropertiewShowWidget->setLinkObject(obj);
//        m_gameObjectPropertiewShowWidget->initWidget();
//    });

    m_gameObjectItemInfoWidget=new GameObjectItemInfoWidget(m_showWidget);


    m_gameObjectItemScriptWidget=new GameObjectItemScriptWidget(m_showWidget);

    //
//    m_gameObjectPropertiewShowWidget->setParent(nullptr);
//    m_gameObjectPropertiewShowWidget->show();
//    m_gameObjectItemInfoWidget->setParent(nullptr);
//    m_gameObjectItemInfoWidget->show();


    //

    m_showWidget->addWidgetInArea(m_gameObjectPropertiewShowWidget,0,0);
    m_showWidget->addWidgetInArea(m_gameObjectItemScriptWidget,0,spacing+m_gameObjectPropertiewShowWidget->height());
    m_showWidget->addWidgetInArea(m_gameObjectItemInfoWidget,0,2*spacing+m_gameObjectPropertiewShowWidget->height()+m_gameObjectItemScriptWidget->height());


    connect(EditSystem::getInstance()->getManager(),&EditManager::nowGameObjectChanged,this,[this](GameObject* obj){
        qDebug()<<"objectSelectChanged"<<obj<<obj->getClassName()<<obj->getName();
        //m_nowGameObject=obj;
        setNowGameObject(obj);
        m_updateFlagObj=true;
        updateWidget();
    });

    connect(EditSystem::getInstance()->getManager(),&EditManager::nowGameObjectItemChanged,this,[this](GameObjectItem* item){
        qDebug()<<"itemSelectChanged"<<item->getLinkObj()->getName();
        m_nowGameObjectItem=item;
        m_updateFlagItem=true;
        updateWidget();
    });
    m_gameObjectPropertiewShowWidget->show();
}

void PropertyEditWidget::updateWidget()
{

    if(m_updateFlagObj&&m_updateFlagItem)
    {
        qDebug()<<"updateWidget";
        m_gameObjectItemScriptWidget->linkItem(m_nowGameObjectItem);

m_gameObjectPropertiewShowWidget->setLinkObject(m_nowGameObject);
m_gameObjectPropertiewShowWidget->initWidget();
//        //m_gameObjectPropertiewShowWidget->setVisible(true);

//        qDebug()<<"m_gameObjectPropertiewShowWidget:"<<m_gameObjectPropertiewShowWidget->getlinkObject()<<
//            m_gameObjectPropertiewShowWidget->getlinkObject()->getName()<<"****\n" <<
//            m_gameObjectPropertiewShowWidget->geometry()<<
//            m_gameObjectPropertiewShowWidget->isVisible();

//        //qDebug()<<this->children()[0]->children()[0]->children()[0]->children();

//        qDebug()<<"------";
//        auto it2=static_cast<QWidget*>(this->children()[0]->children()[0]->children()[0]);
//        //qDebug()<<it2->isVisible()<<it2->geometry();
//        //qDebug()<<"------";

//        for(auto it:this->children()[0]->children()[0]->children())
//        {
//            qDebug()<<it->objectName();
//            //qDebug()<<static_cast<QWidget*>(it)->isVisible()<<static_cast<QWidget*>(it)->geometry();

//        }

        m_gameObjectItemInfoWidget->setLinkItem(m_nowGameObjectItem);
        m_gameObjectItemInfoWidget->initWidget();


        m_updateFlagObj=false;
        m_updateFlagItem=false;

        m_showWidget->updateArea();

   }

}

WheelSlideWidget *PropertyEditWidget::getShowWidget() const
{
    return m_showWidget;
}

void PropertyEditWidget::setShowWidget(WheelSlideWidget *newShowWidget)
{
    m_showWidget = newShowWidget;
}

GameObject *PropertyEditWidget::getNowGameObject() const
{
    return m_nowGameObject;
}

void PropertyEditWidget::setNowGameObject(GameObject *newNowGameObject)
{
    m_nowGameObject = newNowGameObject;
    emit linkObjectChanged(m_nowGameObject);
}

GameObjectItem *PropertyEditWidget::getNowGameObjectItem() const
{
    return m_nowGameObjectItem;
}

void PropertyEditWidget::setNowGameObjectItem(GameObjectItem *newNowGameObjectItem)
{
    m_nowGameObjectItem = newNowGameObjectItem;
}
