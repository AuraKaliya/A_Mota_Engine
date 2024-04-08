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
    static QVector<int> s_sceneLinkList;

    static QRect s_sceneRect;

    static QMap<QString,QGraphicsItem*> s_itemDictionary;


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
    static void initSceneLinkList(QVector<int> list);

    static QRect getSceneRect();
    static void setSceneRect(const QRect &newSceneRect);

    static QRectF getNowSceneRect();

    static int getNowSceneIdx();
    static int getScenesCount();

    static void addScene();
    static void addItemInScene(QGraphicsScene*scene,QGraphicsItem* item);

    void initFromDemo();

    static QVector<QGraphicsScene *> getScenes();

private:
    explicit EditManager(QObject *parent = nullptr);
    static void updateNowSceneInfo();
signals:
    void nowGameObjectChanged(GameObject*);
    void nowGameObjectItemChanged(GameObjectItem*);
    void nowSceneChanged(int);
    void sceneCountChanged();
    void sceneSizeChanged();
    void initFinished();
};

#endif // EDITMANAGER_H
