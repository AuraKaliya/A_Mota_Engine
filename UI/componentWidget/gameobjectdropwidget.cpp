#include "gameobjectdropwidget.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <DATA/baseClass/dynamicitem.h>
#include <DATA/baseClass/gameobjectitem.h>
#include <DATA/baseClass/map2ditem.h>
#include <TOOL/sourceTool/sourcesystem.h>

//test
#include <TOOL/scriptTool/scriptsystem.h>
//test

GameObjectDropWidget::GameObjectDropWidget(QWidget *parent)
    : QWidget{parent}
{
    //透明
    //setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    //setPalette(pal);

    //qDebug()<<"*********************2*";
    setStyleSheet("background-color:black;");
    //setWindowOpacity(0.7);
    setMouseTracking(true);
    setVisible(true);

}

void GameObjectDropWidget::setLinkView(QGraphicsView *view)
{
    m_linkView=view;
    setAcceptDrops(true);
}

void GameObjectDropWidget::dragEnterEvent(QDragEnterEvent *e)
{
    //处理从souce区域拖入的资源----创建新GO和Item，然后进行绑定；
    const QMimeData * data=e->mimeData();
    if(data->hasText())
    {
        qDebug()<<"GameObjectDropWidget";
        qDebug()<<data->text();
        if(data->text()=="SourceCardViewWidget")
        {
            setMouseTracking(true);
            e->accept();
        }
        else
        {
            e->ignore();
        }
    }
}

void GameObjectDropWidget::dropEvent(QDropEvent *e)
{
    //接受事件后，进行的处理逻辑
    //行为判断，目前只提供一个移动行为
    e->dropAction();
    const QMimeData* data=e->mimeData();
    if(data->hasFormat("Count"))
    {
        //qDebug()<<"m_cardType"<<(int)m_cardType;
        //qDebug()<<"ViewClass"<<data->data("ViewClass").toInt();
        int count=data->data("Count").toInt();
        for(int i=0;i<count;++i)
        {
            if(data->data("Error_"+QString::number(i)).toInt()==0)
            {
                if(QString::fromLocal8Bit(data->data("Class_"+QString::number(i))).split("_")[0]=="GameObject")
                {
                    //GO
                    //创建具体GO，并交给SourceManager管理
                    QString name=QString::fromLocal8Bit(data->data("Name_"+QString::number(i)));
                    //qDebug()<<name;
                    qDebug()<<"-----------=====----------"<<data->data("Gid_"+QString::number(i)).toInt();
                    //GameObject* obj=SourceSystem::getInstance()->getManager()->addGameObjectFromSource(name);
                    GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(data->data("Gid_"+QString::number(i)).toInt());
                    qDebug()<<"Drop obj!"<<obj;
                    qDebug()<<obj->getName()<<obj->getPixIdList();
                    //创建Item，设置初始值
                    GameObjectItem * item;
                    //判定添加的GO的类型
                    //可写成策略函数
                    switch(obj->getType())
                    {
                    case GameObject::Type::Environment:
                    {
                        //进行Map2DItem处理
                        //qDebug()<<"GameObject::Type::Environment:";
                        item=new Map2DItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                        Map2DItem* mapItem=static_cast<Map2DItem*>(item);
                        QMap<int ,QPixmap*> map{};
                        for(auto it:obj->getPixIdList().split(","))
                        {
                            QPixmap* pix=SourceSystem::getInstance()->getManager()->getPixmapById(it.toUInt());
                            if(pix!=nullptr)
                            {
                                map[it.toUInt()]=pix;
                            }
                        }
                        //初始化
                        mapItem->initMap(5,5,map,map.begin().key());
                        mapItem->resetMap(static_cast<MotaMap*>(mapItem->getLinkObj())->getMap(0));
                        //test
                        //qDebug()<<"$$$$$"<<mapItem->getLinkObj()<<obj;
                        //qDebug()<<static_cast<MotaMap*>(mapItem->getLinkObj())->getMap(0);
                        //test
                    }
                        break;
                    case GameObject::Type::PlayerCharacter:
                    {
                        //进行DynamicItem处理
                        qDebug()<<"GameObject::Type::PlayerCharacter";
                        item=new DynamicItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                        DynamicItem* playerItem=static_cast<DynamicItem*>(item);
//                        SourceSystem::getInstance()->getManager()->cutPixFromId(obj->getPixIdList().split(",")[0].toUInt(),
//                                                                                0,0,32,32,
//                                                                                0,1);
                        //初始化
                       // playerItem->initPix(static_cast<MotaHero*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getMultiplePixByControlList(obj->getPixId(),static_cast<MotaHero*>(obj)->getStateIndexList()));
                        playerItem->initPix(static_cast<MotaHero*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getIndexListByStr(static_cast<MotaHero*>(obj)->getStateIndexList()));

                        //test
                        //playerItem->changeState("Normal");
                        //qDebug()<<"$$$$$"<<mapItem->getLinkObj()<<obj;
                        //qDebug()<<static_cast<MotaMap*>(mapItem->getLinkObj())->getMap(0);
                        //Script * script=new Script(":/RESOURCE/setting/test.lua",obj,item);
                        if(obj->getScript()!="")
                        {
                            ScriptSystem::getInstance()->getManager()->addScript(item,"./"+obj->getScript());
                            item->setScriptBindState(true);
                        }
                        //test
                    }
                    break;
                    case GameObject::Type::NonPlayerCharacter:
                    {
                        //进行DynamicItem处理
                        qDebug()<<"GameObject::Type::PlayerCharacter";
                        item=new DynamicItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                        DynamicItem* playerItem=static_cast<DynamicItem*>(item);
                        //                        SourceSystem::getInstance()->getManager()->cutPixFromId(obj->getPixIdList().split(",")[0].toUInt(),
                        //                                                                                0,0,32,32,
                        //                                                                                0,1);
                        //初始化
                        // playerItem->initPix(static_cast<MotaHero*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getMultiplePixByControlList(obj->getPixId(),static_cast<MotaHero*>(obj)->getStateIndexList()));
                        playerItem->initPix(static_cast<MotaMonster*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getIndexListByStr(static_cast<MotaMonster*>(obj)->getStateIndexList()));
                        //test
                        //playerItem->changeState("Normal");
                        //qDebug()<<"$$$$$"<<mapItem->getLinkObj()<<obj;
                        //qDebug()<<static_cast<MotaMap*>(mapItem->getLinkObj())->getMap(0);
                        //Script * script=new Script(":/RESOURCE/setting/test.lua",obj,item);
                         //ScriptSystem::getInstance()->getManager()->addScript(item,"./test.lua");
                         //item->setScriptBindState(true);
                        //test
                        if(obj->getScript()!="")
                        {
                            ScriptSystem::getInstance()->getManager()->addScript(item,"./"+obj->getScript());
                            item->setScriptBindState(true);
                        }
                    }
                    break;
                    default :
                    {
                        item=new GameObjectItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                    }
                        break;
                    }

                    item->setPixScale(QRect(0,0,obj->getWidth(),obj->getHeight()));
                    //获取当前Scene，将Item加入到Scene中
                    QPointF point =QPointF(m_mousePos.x()-m_linkView->x()-m_linkView->sceneRect().x(),m_mousePos.y()-m_linkView->y()-m_linkView->sceneRect().y());
                    m_linkView->scene()->addItem(item);
                    if(obj->getPosInit())
                    {
                        item->setPos(obj->getPosX(),obj->getPosY());
                    }
                    else
                    {
                        item->setPos(m_mousePos);
                        //同步obj的Pos属性
                        obj->setPosX(point.rx());
                        obj->setPosY(point.ry());
                    }
                    //将item注册进资源系统

                    SourceSystem::getInstance()->getManager()->addGameObejctItemById(item,item->getId());

                    //test
                    //test--绑定脚本
                    //Script * script=new Script(":/RESOURCE/setting/test.lua",obj,item);
                    //ScriptSystem::getInstance()->getManager()->addScript(item,"./test.lua");
                    //item->setScriptBindState(true);

                    //test
                    //qDe
                    //qDebug()<<"mousePos:"<<m_mousePos<<" itemPos"<<item->pos();
                    //m_linkView ->setFocus();

                }
            }
            else
            {
                //该部分出错，进入错误处理逻辑
                //目前忽略
            }

        }
    }
    else
    {
        qDebug()<<"无效数据";
    }
}

void GameObjectDropWidget::dragMoveEvent(QDragMoveEvent *e)
{
    //qDebug()<<"dragPos"<<e->position();
    m_mousePos=e->position();

}

void GameObjectDropWidget::mouseMoveEvent(QMouseEvent *e)
{
    //m_mousePos=e->pos();
    //qDebug()<<"-------------";
    //qDebug()<<m_mousePos;
    //if(m_linkView!=nullptr)
    //qDebug()<<m_linkView->sceneRect();
}


void GameObjectDropWidget::mousePressEvent(QMouseEvent*e)
{
    //qDebug()<<e->pos();
}
