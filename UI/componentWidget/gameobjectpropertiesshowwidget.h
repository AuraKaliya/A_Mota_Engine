#ifndef GAMEOBJECTPROPERTIESSHOWWIDGET_H
#define GAMEOBJECTPROPERTIESSHOWWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QGridLayout>
#include <QVector>

#include <UI/componentWidget/wheelslidewidget.h>
#include <UI/componentWidget/showlabelwidget.h>
#include <UI/componentWidget/propertylabelwidget.h>
#include <UI/componentWidget/statelabel.h>
#include <TOOL/sourceTool/sourcesystem.h>
class GameObjectPropertiesShowWidget : public QWidget
{
    Q_OBJECT

private:
    GameObject* m_linkObject=nullptr;

    QRect m_showRect;
    //WheelSlideWidget* m_showArea=nullptr;
    WheelSlideWidget* m_baseInfoWidget=nullptr;
    WheelSlideWidget* m_componetInfoWidget=nullptr;
    QVector<WheelSlideWidget*> m_showWidgetList={};

    WheelSlideWidget* m_optionArea=nullptr;
    StateLabel * m_optionInfoLabel=nullptr;
    StateLabel * m_optionPropertyLabel=nullptr;
    QVector<StateLabel*> m_optionLabelList{};


    QVector<PropertyLabelWidget*> m_propertyList{};


    int m_nowShowWidgetIndex=0;
    bool m_hotUpdate=false;
public:
    explicit GameObjectPropertiesShowWidget(QWidget *parent = nullptr);
    GameObject *getlinkObject() const;
    void setLinkObject(GameObject *newLinkObject);
    void initBaseInfoWidget();
    void initComponentInfoWidget();
    void initWidget();
    void initProperty();
    QVector<PropertyLabelWidget*>* getPropertyList();
    void showWidgetSwitch(StateLabel* label);
    void setHotUpdate(bool flag);
protected:
    void mousePressEvent(QMouseEvent*e)override;
    void paintEvent(QPaintEvent* e)override;

private:
    void initShowArea();

    void initOptionArea();
    void updateShow();
signals:

};

#endif // GAMEOBJECTPROPERTIESSHOWWIDGET_H
