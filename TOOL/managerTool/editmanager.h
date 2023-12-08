#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

#include  <DATA/baseClass/gameobject.h>
#include <DATA/baseClass/gameobjectitem.h>
#include <TOOL/sourceTool/sourcesystem.h>

class EditManager : public QObject
{
    Q_OBJECT
private:
    static EditManager* m_instance;
    GameObject* m_nowGameObject=nullptr;
    GameObjectItem* m_nowGameObjectItem=nullptr;

    //关卡相关UI
    //关卡图数 -->地图数
    static QVector<QGraphicsScene*> s_scenes;
    static int s_nowScenesIdx;
    static QGraphicsScene*s_nowScene;

public:
    static EditManager* getInstance(QObject *parent = nullptr);
    void setNowGameObject(GameObject* gameObject=nullptr);
    void setNowGameObject(unsigned int id);
    void setNowGameObjectItem(GameObjectItem*item);

    void readSuperObject(GameObject* gameObject);
    void readMapItemData(QJsonObject obj);

    static void loadNextScene();
    static void loadNextScene(int sceneIdx);
    static QGraphicsScene* getNowScene();

private:
    explicit EditManager(QObject *parent = nullptr);
    static void updateNowSceneInfo();
signals:
    void nowGameObjectChanged(GameObject*);
    void nowGameObjectItemChanged(GameObjectItem*);
};

#endif // EDITMANAGER_H
