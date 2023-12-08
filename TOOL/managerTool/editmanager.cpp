#include "editmanager.h"


QVector<QGraphicsScene*>  EditManager::s_scenes={};
int                       EditManager::s_nowScenesIdx=0;
QGraphicsScene*           EditManager::s_nowScene=nullptr;



EditManager* EditManager::m_instance=nullptr;
EditManager *EditManager::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new EditManager(parent);
    }
    return m_instance;
}

void EditManager::loadNextScene()
{

}

void EditManager::loadNextScene(int sceneIdx)
{

}

QGraphicsScene *EditManager::getNowScene()
{
    return s_nowScene;
}

void EditManager::setNowGameObject(GameObject *gameObject)
{
    m_nowGameObject=gameObject;
    qDebug()<<"EditManager::nowGameObjectChanged";
    emit nowGameObjectChanged(m_nowGameObject);
}

void EditManager::setNowGameObject(unsigned int id)
{
    GameObject *gameObject=SourceSystem::getInstance()->getManager()->getObjectById(id);
    if(gameObject!=nullptr)
    {
        m_nowGameObject=gameObject;
        emit nowGameObjectChanged(m_nowGameObject);
    }
    else
    {

    }

}

void EditManager::setNowGameObjectItem(GameObjectItem *item)
{
    m_nowGameObjectItem=item;
    qDebug()<<"EditManager::nowGameObjectItemChanged";
    emit nowGameObjectItemChanged(m_nowGameObjectItem);
}

void EditManager::readSuperObject(GameObject *gameObject)
{
    QJsonObject obj=gameObject->getItemData();



}

EditManager::EditManager(QObject *parent)
    : QObject{parent}
{
    QGraphicsScene* scene=new QGraphicsScene;
    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(QRectF(0,0,1050,750));
    s_scenes.append(scene);
    s_nowScene=scene;

}
void EditManager::updateNowSceneInfo()
{

}
