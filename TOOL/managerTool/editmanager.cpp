#include "editmanager.h"

#include <DATA/baseClass/dynamicitem.h>
#include <DATA/baseClass/map2ditem.h>
#include <DATA/baseClass/mapitem.h>

#include <TOOL/scriptTool/scriptsystem.h>


QVector<QGraphicsScene*>  EditManager::s_scenes={};
int                       EditManager::s_nowScenesIdx=0;
QGraphicsScene*           EditManager::s_nowScene=nullptr;
QVector<int>              EditManager::s_sceneLinkList={0};
QRect                     EditManager::s_sceneRect=QRect(0,0,512,512);

EditManager* EditManager::m_instance=nullptr;
QRect EditManager::getSceneRect()
{
    return s_sceneRect;
}

void EditManager::setSceneRect(const QRect &newSceneRect)
{
    s_sceneRect = newSceneRect;
    emit m_instance->sceneSizeChanged();
}

QRectF EditManager::getNowSceneRect()
{
    return s_nowScene->sceneRect();
}

int EditManager::getNowSceneIdx()
{
    return s_nowScenesIdx;
}

int EditManager::getScenesCount()
{
    return s_scenes.size();
}

void EditManager::addScene()
{
    QGraphicsScene* scene=new QGraphicsScene;
    scene->setBackgroundBrush(Qt::green);
    scene->setSceneRect(s_sceneRect);
    s_scenes.append(scene);

    //link 变化
    int linkTail=s_sceneLinkList[s_sceneLinkList.size()-1];
    s_sceneLinkList[s_sceneLinkList.size()-1]=s_sceneLinkList.size();
    s_sceneLinkList.append(linkTail);


    emit m_instance->sceneCountChanged();
}

void EditManager::addItemInScene(QGraphicsScene *scene, QGraphicsItem *item)
{
    scene->addItem(item);
}

void EditManager::initFromDemo()
{
    // 这里需要清空所有Scene  -----------

    ////////////////////////////////////

    GameDemo * demo=SourceSystem::getInstance()->getManager()->getNowDemo();

    if(demo!=nullptr&&demo->initState())
    {
        //可以改为策略模式
        if(demo->objectName()=="Mota")
        {

            //qDebug()<<"EditManager::initFromDemo: Mota!";
            //进行初始化处理



            //重新设计的初始化方案
            /*
                1. 先加载map，hero，monster，npc，drop
                2. 加载mapItem。
                3. 从map中获取objectMap，加载obj
            */


            //进行注册的映射
            for(auto it:demo->getElement())
            {
                demo->registerElement(it->getId(),it);
            }

            //加载map
            if(true)
            {
                auto it=static_cast<MotaDemo*>(demo)->motaMap();

                GameObjectItem * item=nullptr;

                //添加link 塔
                initSceneLinkList(it->getTowerLink());

                for(int i=0;i<it->getTowerLink().size();++i)
                {
                   loadNextScene(i);

//                    item=new Map2DItem(it,*SourceSystem::getInstance()->getManager()->getPixmapByObject(it));
//                    Map2DItem* mapItem=static_cast<Map2DItem*>(item);
//                    QMap<int ,QPixmap*> map{};
//                    for(auto it:it->getPixIdList().split(","))
//                    {
//                        QPixmap* pix=SourceSystem::getInstance()->getManager()->getPixmapById(it.toUInt());
//                        if(pix!=nullptr)
//                        {
//                            map[it.toUInt()]=pix;
//                        }
//                    }

//                    //初始化
//                    mapItem->initMap(5,5,map,map.begin().key());
//                    mapItem->resetMap(static_cast<MotaMap*>(mapItem->getLinkObj())->getMap(i));

                   item=new MapItem(it,*SourceSystem::getInstance()->getManager()->getPixmapByObject(it));

                   MapItem* mapItem=static_cast<MapItem*>(item);
                   //qDebug()<<"checkMapItem0: --end";
                   QMap<int,PixSource*> map{};
                   for(auto it:it->getPixIdList().split(","))
                   {
                       PixSource* pixSource=SourceSystem::getInstance()->getManager()->getPixSourceById(it.toInt());
                       if(pixSource!=nullptr)
                       {
                           map[it.toUInt()]=pixSource;
                       }
                   }
                   //qDebug()<<"checkMapItem1: "<<map<<"--end";
                    //初始化
                   mapItem->initMap(it->mapNetWidth(),it->mapNetHeight(),map,map.begin().key());
                   //qDebug()<<"checkMapItem1.2: "<<"--end";
                   auto elementList=static_cast<MotaMap*>(mapItem->getLinkObj())->getMap(i);
                   //qDebug()<<"checkMapItem1.3: "<<elementList;
                   for(int y=0;y<elementList.size();++y)
                   {
                       for(int x=0;x<elementList[y].size();++x)
                       {
                           qDebug()<<"checkMapItem1.5 y x element"<<y<<x<<elementList[y][x];
                           mapItem->setPix(x,y,elementList[y][x]);

                       }
                   }
                    //qDebug()<<"checkMapItem2: --end";


                    //获取当前Scene，将Item加入到Scene中
                    s_nowScene->addItem(item);
                    item->setPixScale(QRect(0,0,it->getWidth(),it->getHeight()));
                    if(it->getPosInit())
                    {
                        item->setPos(it->getPosX(),it->getPosY());
                    }
                    else
                    {
                        item->setPos(0,0);
                        //同步obj的Pos属性
                        it->setPosX(0);
                        it->setPosY(0);

                        qDebug()<<"WARNNING : NO POS INIT";
                    }

                    connect(this,&EditManager::nowSceneChanged,static_cast<MotaMap*>(it),[it](int i){
                        MotaMap* map=static_cast<MotaMap*>(it);
                        map->nextLayer(i);
                    });

                    if(item !=nullptr)
                    {
                        item->setPixScale(QRect(0,0,it->getWidth(),it->getHeight()));
                        if(it->getPosInit())
                        {
                            item->setPos(it->getPosX(),it->getPosY());
                        }
                        else
                        {
                            item->setPos(0,0);
                            //同步obj的Pos属性
                            it->setPosX(0);
                            it->setPosY(0);
                        }
                        //将item注册进资源系统
                        SourceSystem::getInstance()->getManager()->addGameObejctItemById(item,item->getId());

                        //绑定可见属性
                        item->setState(it->drawState());
                        connect(it,&GameObject::drawStateChanged,item,&GameObjectItem::setState);
                        s_nowScene->setSceneRect(0,0,it->getWidth(),it->getHeight());

                    }
                }
            }

            if(true)
            {
                auto posMap=static_cast<MotaDemo*>(demo)->objPosDictionary();

                for(auto it=posMap.begin();it!=posMap.end();++it)
                {
                    auto obj=static_cast<MotaDemo*>(demo)->getElement(it.key());
                    if(obj!=nullptr)
                    {
                        GameObjectItem * item=nullptr;

                        //根据link的obj的类型进行初始化设置
                        switch(obj->getType())
                        {
                        case GameObject::Type::PlayerCharacter:
                        {
                            //切换当前编辑场景
                            //Player 在Mota中只存在一个，所以做特殊化处理
                            loadNextScene(it.value()[0].layer);

                            //构建DynamicItem
                            item=new DynamicItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                            DynamicItem* playerItem=static_cast<DynamicItem*>(item);

                            //设置控制位
                            //obj同步位置改变
                            playerItem->setSyncPos(true);
                            //obj同步pix状态改变（角色动态）
                            playerItem->setSyncPixState(true);

                            //绘制图案初始化
                            if(obj->pixSourceFlag()==true)
                            {
                                qDebug()<<" init object to item : pixFlag == true======Player";
                                PixSource* pixSource=SourceSystem::getInstance()->getManager()->getPixSourceById(obj->getPixId());
                                if(pixSource!=nullptr)
                                {
                                    playerItem->setObjPix(* pixSource->pix());
                                    playerItem->initPix(pixSource->stateList(),pixSource->stateIndexList(),0,0,pixSource->getPerW(),pixSource->getPerH(),pixSource->XInterval(),pixSource->YInterval());

                                }
                                else
                                {
                                    qDebug()<<"ERROR : init object to item  :NO HAVE THIS PIXSOURCE!";
                                }
                            }
                            else
                            {
                                playerItem->initPix(static_cast<MotaHero*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getIndexListByStr(static_cast<MotaHero*>(obj)->getStateIndexList()));
                            }

                            //将item添加到Scene中    ---因为不同类型有不同的scene选择，而scene变化是在处理类型的区域内的，所以应该把代码放这里面
                            s_nowScene->addItem(item);


                            //后续处理-------player

                            //item 绘制大小
                            item->setPixScale(QRect(0,0,obj->getWidth(),obj->getHeight()));

                            //位置的初始化
                            if(obj->getPosInit())
                            {
                                item->setPos(obj->getPosX(),obj->getPosY());
                            }
                            else
                            {
                                item->setPos(0,0);
                                //同步obj的Pos属性
                                obj->setPosX(0);
                                obj->setPosY(0);
                            }


                            if(item!=nullptr)
                            {
                                //添加脚本   --新修正： script应该与item绑定
                                if(obj->getScript()!="")
                                {
                                    ScriptSystem::getInstance()->getManager()->addScript(item,"./"+obj->getScript());
                                    item->setScriptBindState(true);
                                }

                                //将item注册进资源系统
                                SourceSystem::getInstance()->getManager()->addGameObejctItemById(item,item->getId());

                                //绑定可见属性   ---- 这里表示的是当link的的obj设置为不可见时，其所绘制的所有图都不可见
                                item->setState(obj->drawState());
                                connect(obj,&GameObject::drawStateChanged,item,&GameObjectItem::setState);
                            }
                        }
                        break;
                        case GameObject::Type::NonPlayerCharacter:
                        {
                            //读取该obj对应的所有位置进行添加
                            for(auto objPos:it.value())
                            {
                                //切换当前编辑场景
                                loadNextScene(objPos.layer);

                                item=new DynamicItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                                DynamicItem* nonPlayerItem=static_cast<DynamicItem*>(item);

                                //item已存在id，进行反注册进Demo中
                                static_cast<MotaDemo*>(demo)->motaMap()->setItemPos(objPos.layer,objPos.x,objPos.y,item->getId());

                                //绘制图案初始化
                                if(obj->pixSourceFlag()==true)
                                {
                                    qDebug()<<" init object to item : pixFlag == true";
                                    PixSource* pixSource=SourceSystem::getInstance()->getManager()->getPixSourceById(obj->getPixId());
                                    if(pixSource!=nullptr)
                                    {
                                        nonPlayerItem->setObjPix(* pixSource->pix());
                                        nonPlayerItem->initPix(pixSource->stateList(),pixSource->stateIndexList(),0,0,pixSource->getPerW(),pixSource->getPerH(),pixSource->XInterval(),pixSource->YInterval());
                                    }
                                    else
                                    {
                                        qDebug()<<"ERROR : init object to item  :NO HAVE THIS PIXSOURCE!";
                                    }
                                }else
                                {
                                    //qDebug()<<" init object to item : pixFlag == false";
                                    //nonPlayerItem->initPix(static_cast<MotaMonster*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getIndexListByStr(static_cast<MotaMonster*>(obj)->getStateIndexList()));
                                }

                                //将item添加至场景
                                s_nowScene->addItem(item);


                                //后续处理---npc

                                //位置初始化   --1.获取点对应的坐标 2.对item进行设置setPos
                                QPoint point=static_cast<MotaDemo*>(demo)->motaMap()->getElementPoint(objPos.layer,objPos.x,objPos.y);


                                item->setPos(point);

                                if(item!=nullptr)
                                {
                                    //item 绘制大小
                                    item->setPixScale(QRect(0,0,obj->getWidth(),obj->getHeight()));

                                    //添加脚本   --新修正： script应该与item绑定   --这是统一的处理，用于在外部代码中进行控制obj的特性（如 检测敌意范围等）
                                    if(obj->getScript()!="")
                                    {
                                        ScriptSystem::getInstance()->getManager()->addScript(item,"./"+obj->getScript());
                                        item->setScriptBindState(true);
                                    }

                                    //将item注册进资源系统
                                    SourceSystem::getInstance()->getManager()->addGameObejctItemById(item,item->getId());

                                    //绑定可见属性   ---- 这里表示的是当link的的obj设置为不可见时，其所绘制的所有图都不可见
                                    item->setState(obj->drawState());
                                    connect(obj,&GameObject::drawStateChanged,item,&GameObjectItem::setState);
                                    //添加微操控制  ----当obj对应item消失时，进行检查是否是自己消失
                                    //因为在item绘制时是以自己的state为判断标准，所以只用传递一个识别号，让item的逻辑自己判断即可
                                    connect(obj,&GameObject::itemDrawStateChanged,item,&GameObjectItem::setItemState);
                                }
                            }
                        }
                        break;
                        default:
                        {

                        }
                        break;    
                        }

                        item;



                    }
                }
            }

            connect(static_cast<MotaDemo*>(demo),&MotaDemo::layerChanged,this,[this](int layer){

                QGraphicsScene* oldScene=s_nowScene;
                loadNextScene(layer);
                QGraphicsScene* newScene=s_nowScene;
                GameObject* obj=SourceSystem::getInstance()->getManager()->getNowDemo()->getElement("MotaHero");
                if(obj!=nullptr)
                {
                    QGraphicsItem* heroItem=SourceSystem::getInstance()->getManager()->getGameObjectItemById(obj->itemId());

                    //qDebug()<<"^^^^check0:"<<oldScene<<heroItem<<obj->getPosX()<<obj->getPosY();
                    oldScene->removeItem(heroItem);
                    newScene->addItem(heroItem);
                    heroItem->setPos(obj->getPosX(),obj->getPosY());
                    //qDebug()<<"^^^^check1:"<<newScene<<heroItem<<obj->getPosX()<<obj->getPosY();
                }
                else
                {
                    qDebug()<<"error no have this obj!";
                }

            });

            //加载默认场景-------------id----可设置为外置控制
            loadNextScene(0);
        }


        emit initFinished();
    }else
    {
        qDebug()<<"ERROR: EditManager::initFromDemo;";
    }


}

QVector<QGraphicsScene *> EditManager::getScenes()
{
    return s_scenes;
}

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
    //安全性检查


    //转换
    int nextSceneIdx=s_sceneLinkList[s_nowScenesIdx];

    if(s_scenes.size()>nextSceneIdx)
    {
        qDebug()<<"nowScene:"<<s_nowScenesIdx<<s_nowScene;
        s_nowScenesIdx=nextSceneIdx;
        s_nowScene=s_scenes[s_nowScenesIdx];
        qDebug()<<"nextScene:"<<s_nowScenesIdx<<s_nowScene;
    }
    emit m_instance->nowSceneChanged(s_nowScenesIdx);
}

void EditManager::loadNextScene(int sceneIdx)
{
    if(s_scenes.size()>sceneIdx)
    {
        s_nowScenesIdx=sceneIdx;
        s_nowScene=s_scenes[s_nowScenesIdx];
    }
    emit m_instance->nowSceneChanged(s_nowScenesIdx);
}

QGraphicsScene *EditManager::getNowScene()
{
    return s_nowScene;
}

void EditManager::initSceneLinkList(QVector<int> list)
{
    s_sceneLinkList=list;
    int needCount=list.size();
    int nowCount=s_scenes.size();

    for(int i=0;i<needCount-nowCount;++i)
    {
        QGraphicsScene* scene=new QGraphicsScene;
        scene->setBackgroundBrush(Qt::white);
        scene->setSceneRect(QRectF(0,0,1050,750));
        s_scenes.append(scene);
        emit m_instance->sceneCountChanged();
    }

}

void EditManager::setNowGameObject(GameObject *gameObject)
{
    m_nowGameObject=gameObject;
    qDebug()<<"EditManager::nowGameObjectChanged";
    QString actionStr="GameObject select:"+gameObject->getClassName()+" "+gameObject->getName();
    emit nowGameObjectChanged(m_nowGameObject);
    emit actionSend(actionStr);
}

void EditManager::setNowGameObject(unsigned int id)
{
    GameObject *gameObject=SourceSystem::getInstance()->getManager()->getObjectById(id);
    if(gameObject!=nullptr)
    {
        m_nowGameObject=gameObject;
        QString actionStr="GameObject select:"+gameObject->getClassName()+" "+gameObject->getName();
        emit nowGameObjectChanged(m_nowGameObject);
        emit actionSend(actionStr);
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
