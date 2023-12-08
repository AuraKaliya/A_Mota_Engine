#ifndef ADDGAMEOBJECTINFOWIDGET_H
#define ADDGAMEOBJECTINFOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>


#include <UI/componentWidget/gameobjectpropertiesshowwidget.h>
#include <UI/componentWidget/sourcetreewidget.h>


#include <DATA/baseClass/gameobject.h>
#include <TOOL/sourceTool/sourcesystem.h>


/*
    这是一个“独立”的顶层widget，能够引入其他的组件进行逻辑处理，然后通过与系统进行直接交互达到数据更新的功能。
    它会被放到editWidget中进行存放，并由editWidget进行调用显示。
*/

class AddGameObjectInfoWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel* m_pixLabel=nullptr;

    QWidget* m_nodesWidget=nullptr;
    QLabel* m_firstNodeLabel=nullptr;
    QComboBox* m_secondNodeLabel=nullptr;
    QComboBox* m_GameObjectClassBox=nullptr;

    GameObjectPropertiesShowWidget* m_propertyWidget=nullptr;
    QTextEdit* m_informationBox=nullptr;
    QPushButton* m_yesBtn=nullptr;
    QPushButton* m_noBtn=nullptr;

    QVBoxLayout* m_nodesLayout=nullptr;
    QHBoxLayout* m_headLayout=nullptr;
    QVBoxLayout* m_mainLayout=nullptr;
    QHBoxLayout* m_tailLayout=nullptr;


    GameObject* m_linkObject=nullptr;
    QVector<QLabel*> m_linkLabelList;
    QVector<GameObject*> m_linkObjectList;
    SourceTreeWidget* m_linkSourceTreeWidget=nullptr;

public:
    explicit AddGameObjectInfoWidget(QWidget *parent = nullptr);
    explicit AddGameObjectInfoWidget(GameObject*obj,QWidget *parent = nullptr);
    GameObject *getLinkObject() const;
    void setLinkObject(GameObject *newLinkObject);
    void setLinkSourceTreeWidget(SourceTreeWidget*);
    void updateList();

private:
    void initPixLabel();
    void initNodesWidget();
    void initPropertyWidget();
    void initLayouts();
    void initControBtn();
    void initSecondNodeLabelList();
    void initGameObjectClassBoxList();

signals:
    void linkObjectChanged(GameObject*);
    void addObject(GameObject*);
};

#endif // ADDGAMEOBJECTINFOWIDGET_H
