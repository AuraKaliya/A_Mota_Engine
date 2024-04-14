#include "gameobjectdropwidget.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <DATA/baseClass/dynamicitem.h>
#include <DATA/baseClass/gameobjectitem.h>
#include <DATA/baseClass/map2ditem.h>
#include <TOOL/sourceTool/sourcesystem.h>
#include <TOOL/editTool/editsystem.h>

//test
#include <TOOL/scriptTool/scriptsystem.h>
//test

GameObjectDropWidget::GameObjectDropWidget(QWidget *parent)
    : QWidget{parent}
{
    setStyleSheet("background-color:black;");
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
        //qDebug()<<"GameObjectDropWidget";
        //qDebug()<<data->text();
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

    //  判断当前Demo

    GameDemo * demo=SourceSystem::getInstance()->getManager()->getNowDemo();

    //demo的初始化状态和加载的GO状态相关。
    // 魔塔
    if(demo->objectName()=="Mota")
    {
        //qDebug()<<"GameObjectDropWidget::dropEvent:  now demo is Mota!";
        //qDebug()<<"check <"<<data;
        if(data->hasFormat("Count"))
        {
            int count=data->data("Count").toInt();
            for(int i=0;i<count;++i)
            {
                if(data->data("Error_"+QString::number(i)).toInt()==0)
                {
                    if(QString::fromLocal8Bit(data->data("Class_"+QString::number(i))).split("_")[0]=="GameObject")
                    {
                        //qDebug()<<"solve ! dropevent~!!";
                        //GO
                        //创建具体GO，并交给SourceManager管理
                        QString name=QString::fromLocal8Bit(data->data("Name_"+QString::number(i)));
                        //GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(data->data("Gid_"+QString::number(i)).toInt());

                        //GameObject* sourceObj=SourceSystem::getInstance()->getManager()->getGameObjectSourceByName(name);
                        GameObject* obj=SourceSystem::getInstance()->getManager()->addGameObjectFromSource(name);
                        //qDebug()<<"obj"<<name<<obj;
                        //创建Item，设置初始值
                        GameObjectItem * item=nullptr;
                        QPointF point =QPointF(m_mousePos.x()-m_linkView->x()-m_linkView->sceneRect().x(),m_mousePos.y()-m_linkView->y()-m_linkView->sceneRect().y());

                        //获取当前释放位置对应的MotaLayer
                        int nowLayer=EditSystem::getInstance()->getManager()->getNowSceneIdx();
                        //判定添加的GO的类型
                        //可写成策略函数
                        switch(obj->getType())
                        {
                        case GameObject::Type::Environment:
                        {
                            /*
                                魔塔地图处理流程
                                1. 若未初始化，则新建地图-  新建窗体，连接Demo，设置初始参数、提交生成。
                                2. 若已初始化，则失败，需要先删除原有地图才能进行。
                            */
                            if(demo->envState())
                            {
                                qDebug()<<"Warnning: 需要先删除原有地图！";
                            }

                        }
                        break;
                        case GameObject::Type::PlayerCharacter:
                        {
                            qDebug()<<"GameObject::Type::PlayerCharacter！";
                            qDebug()<<static_cast<MotaDemo*>(demo)->posFromMap(QPoint(m_mousePos.x()-m_linkView->x()-m_linkView->sceneRect().x(),m_mousePos.y()-m_linkView->y()-m_linkView->sceneRect().y()));

                        }
                        break;
                        case GameObject::Type::NonPlayerCharacter:
                        {
                            qDebug()<<"drop--GameObject::Type::NonPlayerCharacter";
                            //qDebug()<<"obj::"<<obj<<obj->getId()<<obj->getClassName()<<obj->getName()<<obj->getPixId()<<obj->getPixIdList();
                            //qDebug()<<"check:drop Pos:";
                            //qDebug()<<"mousePos:"<<e->position();
                            //qDebug()<<"mousePos:"<<m_mousePos;
                            //qDebug()<<"mousePosToMap:"<<static_cast<MotaDemo*>(demo)->posFromMap(QPoint(m_mousePos.x(),m_mousePos.y()));
                            //qDebug()<<"mousePosToMap2:"<<static_cast<MotaDemo*>(demo)->posFromMap(QPoint(
                                //m_mousePos.x()-((m_linkView->width()-m_linkView->sceneRect().width())/2),
                                //m_mousePos.y()-((m_linkView->height()-m_linkView->sceneRect().height())/2)
                                 //                                                                       )
                                  //                                                                     );
                            //qDebug()<<"mousePosToMap2:"<<static_cast<MotaDemo*>(demo)->posFromMap(QPoint(m_mousePos.x()-m_linkView->x()-m_linkView->sceneRect().x(),m_mousePos.y()-m_linkView->y()-m_linkView->sceneRect().y()));

                            //QPoint itemPos=static_cast<MotaDemo*>(demo)->posFromMap(QPoint(m_mousePos.x()-m_linkView->x()-m_linkView->sceneRect().x(),m_mousePos.y()-m_linkView->y()-m_linkView->sceneRect().y()));
                                QPoint itemPos=static_cast<MotaDemo*>(demo)->posFromMap(QPoint(
                                m_mousePos.x()-((m_linkView->width()-m_linkView->sceneRect().width())/2),
                                m_mousePos.y()-((m_linkView->height()-m_linkView->sceneRect().height())/2)
                                )
                                                                                       );
                            item=new DynamicItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
                            DynamicItem* nonPlayerItem=static_cast<DynamicItem*>(item);

                            //由已注册的GameObject拖拽形成的具体Item
                            //item已存在id，进行反注册进Demo中-----待修正=========
                            auto pos=static_cast<MotaDemo*>(demo)->posFromMapMatrix(itemPos);
                            int itemX=pos.first;
                            int itemY=pos.second;
                            static_cast<MotaDemo*>(demo)->motaMap()->setItemPos(nowLayer,itemX,itemY,item->getId());

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
                                qDebug()<<" init object to item : pixFlag == false";
                                //nonPlayerItem->initPix(static_cast<MotaMonster*>(obj)->getStateStrList(),SourceSystem::getInstance()->getManager()->getIndexListByStr(static_cast<MotaMonster*>(obj)->getStateIndexList()));
                            }

                            //将item添加至场景
                            item->setVisible(true);
                            EditSystem::getInstance()->getManager()->getNowScene()->addItem(item);
                            //s_nowScene->addItem(item);

                            //后续处理---npc
                            //位置初始化   --1.获取点对应的坐标 2.对item进行设置setPos
                            //QPoint point=static_cast<MotaDemo*>(demo)->motaMap()->getElementPoint(nowLayer,itemPos.x(),itemPos.y());
                            item->setPos(itemPos);
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
                                //qDebug()<<"additem check:* "<<item->getId();
                                SourceSystem::getInstance()->getManager()->addGameObejctItemById(item,item->getId());

                                //绑定可见属性   ---- 这里表示的是当link的的obj设置为不可见时，其所绘制的所有图都不可见
                                item->setState(obj->drawState());
                                connect(obj,&GameObject::drawStateChanged,item,&GameObjectItem::setState);
                                //添加微操控制  ----当obj对应item消失时，进行检查是否是自己消失
                                //因为在item绘制时是以自己的state为判断标准，所以只用传递一个识别号，让item的逻辑自己判断即可
                                connect(obj,&GameObject::itemDrawStateChanged,item,&GameObjectItem::setItemState);
                            }
////////////////////////////////////////////////注册进Demo中////////////////////////////////////////////////
                            //从这里开始，判断是Monster还是NPC；
                            if(obj->getClassName()=="MotaNPC")
                            {
                                qDebug()<<"Is Mota NPC!";
                                static_cast<MotaDemo*>(demo)->addNPC(static_cast<MotaNPC*>(obj),itemPos.x(),itemPos.y());
                            }
                            else if(obj->getClassName()=="MotaMonster")
                            {
                                qDebug()<<"Is Mota Monster!";
                                static_cast<MotaDemo*>(demo)->addMonster(static_cast<MotaMonster*>(obj),itemPos.x(),itemPos.y());
                            }

                            //qDebug()<<"-check2-:";
                            //qDebug()<<item->isVisible();
                            //qDebug()<<item->pos();
                            //static_cast<MotaDemo*>(demo)->motaMap()->tick();

                            //static_cast<MotaDemo*>(demo)->addMonster(static_cast<MotaMonster*>(obj));

                            //qDebug()<<"check3:";
                           // static_cast<MotaDemo*>(demo)->motaMap()->tick();
                        }
                        break;
                        default :
                        {

                             qDebug()<<"GameObject::default!";
//                            item=new GameObjectItem(obj,*SourceSystem::getInstance()->getManager()->getPixmapByObject(obj));
//                            m_linkView->scene()->addItem(item);
                        }
                        break;
                        }

                        if(item!=nullptr)
                        {
                            item->setPixScale(QRect(0,0,obj->getWidth(),obj->getHeight()));

//                            if(obj->getPosInit())
//                            {
//                                item->setPos(obj->getPosX(),obj->getPosY());
//                            }
//                            else
//                            {
//                                item->setPos(m_mousePos);
//                                //同步obj的Pos属性
//                                obj->setPosX(point.rx());
//                                obj->setPosY(point.ry());
//                            }
//                            //将item注册进资源系统
//                            SourceSystem::getInstance()->getManager()->addGameObejctItemById(item,item->getId());

//                            //绑定可见属性
//                            item->setState(obj->drawState());
//                            connect(obj,&GameObject::drawStateChanged,item,&GameObjectItem::setState);

                        }
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
    else
    {
        qDebug()<<"error: drop error;";
    }

}

void GameObjectDropWidget::dragMoveEvent(QDragMoveEvent *e)
{
    m_mousePos=e->position();
}

void GameObjectDropWidget::mouseMoveEvent(QMouseEvent *e)
{

}


void GameObjectDropWidget::mousePressEvent(QMouseEvent*e)
{
}
