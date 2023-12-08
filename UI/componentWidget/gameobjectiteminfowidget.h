#ifndef GAMEOBJECTITEMINFOWIDGET_H
#define GAMEOBJECTITEMINFOWIDGET_H

#include <QWidget>
#include <DATA/baseClass/gameobjectitem.h>
#include "UI/componentWidget/propertylabelwidget.h"
class GameObjectItemInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameObjectItemInfoWidget(QWidget *parent = nullptr);
    void initWidget();
    void setLinkItem( GameObjectItem*item);
private:
    GameObjectItem* m_linkItem=nullptr;
    QVector<QMetaProperty*> m_itemPropertyList;
    QVector<PropertyLabelWidget*> m_propertyLabelWidgetList;
signals:

};

#endif // GAMEOBJECTITEMINFOWIDGET_H
