#include "gameobjectiteminfowidget.h"


#include <QMetaProperty>

GameObjectItemInfoWidget::GameObjectItemInfoWidget(QWidget *parent)
    : QWidget{parent}
{
    setObjectName("GameObjectItemInfoWidget");
    setFixedWidth(400);
}

void GameObjectItemInfoWidget::initWidget()
{
    //clear
    for(auto it:m_itemPropertyList)
    {
        delete it;
        it=nullptr;
    }
    m_itemPropertyList.clear();

    for(auto it:m_propertyLabelWidgetList)
    {
        it->setEnabled(false);
        it->setVisible(false);
        it->setParent(nullptr);
        it->deleteLater();
    }
    m_propertyLabelWidgetList.clear();


    if(m_linkItem!=nullptr)
    {
        qDebug()<<"initItemProperty";
        const QMetaObject * p=m_linkItem->metaObject();
        bool flag=true;
        int i=1;
        int spacing=10;
        while(flag)
        {
            QMetaProperty *property= new QMetaProperty(p->property(i));
            if(property->isValid())
            {
                qDebug()<<property->name();
                m_itemPropertyList.append(property);
                PropertyLabelWidget* w=new PropertyLabelWidget(this);

                w->resize(380,50);
                w->setLink(static_cast<QObject*>(m_linkItem),property);
                w->setRatio(4,6,5,5);
                w->setHotUpdate(true);
                w->initWidget();
                w->move(0,spacing+((i-1)*(w->height()+spacing)));
                w->setVisible(true);
                w->setHotUpdate(true);
                m_propertyLabelWidgetList.append(w);
                i++;
            }
            else
            {
                flag=false;
                continue;
            }
        }
    }
    adjustSize();

}

void GameObjectItemInfoWidget::setLinkItem(GameObjectItem *item)
{
    m_linkItem=item;
    //initWidget();
}
