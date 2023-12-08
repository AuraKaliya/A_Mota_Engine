#ifndef PROPERTYEDITWIDGET_H
#define PROPERTYEDITWIDGET_H

#include <QWidget>
#include <DATA/baseClass/gameobject.h>
#include <DATA/baseClass/gameobjectitem.h>
#include <DATA/baseClass/instructionobject.h>
#include <DATA/baseClass/uiwidget.h>

#include <UI/componentWidget/gameobjectiteminfowidget.h>
#include <UI/componentWidget/gameobjectpropertiesshowwidget.h>
#include <UI/componentWidget/wheelslidewidget.h>
#include <UI/componentWidget/gameobjectitemscriptwidget.h>

#include <TOOL/editTool/editsystem.h>

class PropertyEditWidget :public UIWidget
//public WheelSlideWidget,
{
    Q_OBJECT
public:
    explicit PropertyEditWidget(QWidget *parent = nullptr);

    void updateWidget();


    WheelSlideWidget *getShowWidget() const;
    void setShowWidget(WheelSlideWidget *newShowWidget);

    GameObject *getNowGameObject() const;
    void setNowGameObject(GameObject *newNowGameObject);

    GameObjectItem *getNowGameObjectItem() const;
    void setNowGameObjectItem(GameObjectItem *newNowGameObjectItem);


private:
    WheelSlideWidget* m_showWidget=nullptr;
    GameObjectPropertiesShowWidget* m_gameObjectPropertiewShowWidget=nullptr;
    GameObjectItemInfoWidget* m_gameObjectItemInfoWidget=nullptr;
    GameObjectItemScriptWidget* m_gameObjectItemScriptWidget=nullptr;



    GameObject* m_nowGameObject;
    GameObjectItem* m_nowGameObjectItem;
    QVector<InstructionObject> m_insList;


    bool m_updateFlagObj=false;
    bool m_updateFlagItem=false;

signals:

    void linkObjectChanged(GameObject*);


};

#endif // PROPERTYEDITWIDGET_H
