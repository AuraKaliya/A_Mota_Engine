#include "instructionmanager.h"
QMap<QString,GameDemo*> InstructionManager::m_demoDictionary={};
QMap<QString,QVector<QPair<QString,SoluteFunc> > > InstructionManager::m_insFunctionDictionary{};
InstructionManager * InstructionManager::m_instance=nullptr;
InstructionManager *InstructionManager::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new InstructionManager(parent);
    }
    return m_instance;

}

GameDemo *InstructionManager::findDemoByName(QString name)
{
    auto it = m_demoDictionary.find(name);
    if(it != m_demoDictionary.end())
    {
        return it.value();
    }
    else
    {
        return nullptr;
    }
    return nullptr;
}

bool InstructionManager::soluteInstruction(InstructionObject*insObj)
{
    InstructionContext* insContext=insObj->getInsContext();
    //处理权限

//    auto demo=m_demoDictionary.find(insContext->insDemo);
//    if(demo==m_demoDictionary.end())
//    {
//        return false;
//    }

    //处理模式--Demo      //转发数据包
    //--------------------------优化-策略模式
    auto list=insContext->insModel.split("_");
    if(list[0]=="Data")
    {
         qDebug()<<"Solute Data";
    }
    else if(list[0]=="Ins")
    {
        if(list[1]=="Demo")
        {
            qDebug()<<"Solute Demo Ins";
            for(auto it:insContext->insPacket)
            {
                GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(it.ObjectIndex);
                findInsFuncFromDictionary("Demo",it.insName)(obj,it.value);
                it.soluteState=true;
            }
        }
        else if(list[1]=="Object")
        {
             qDebug()<<"Solute Object Ins";
            for(auto it:insContext->insPacket)
            {
                qDebug()<<"insId"<<it.insIndex;
                qDebug()<<"insObj"<<it.ObjectIndex;
                qDebug()<<"insName"<<it.insName;

                if(!it.soluteState)
                {
                    GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(it.ObjectIndex);
                    qDebug()<<"=====";
                    if(obj!=nullptr)qDebug()<<obj->getId();
                    qDebug()<<"=====";
                    if(obj!=nullptr)
                    {
                        //指令处理--前置处理（delay、soluteState）
                        //指令处理--数据包处理
                        obj->solutePacketData(&it);
                        //指令处理 --处理完成
                        it.soluteState=true;
                        //指令处理--后续处理 （link ）
                    }
                }
            }
        }
    }




//    if(insContext->insModel.contains("Data"))
//    {
//        qDebug()<<"Solute Data";

//    }else if(insContext->insModel.contains("Ins"))
//    {
//        qDebug()<<"Solute Ins";
//        //demo.value()->insRecv(insContext);

//        for(auto it:insContext->insPacket)
//        {
//            qDebug()<<"insId"<<it.insIndex;
//            qDebug()<<"insObj"<<it.ObjectIndex;
//            qDebug()<<"insName"<<it.insName;

//            if(!it.soluteState)
//            {
//                GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(it.ObjectIndex);
//                qDebug()<<"=====";
//                if(obj!=nullptr)qDebug()<<obj->getId();
//                qDebug()<<"=====";
//                if(obj!=nullptr)
//                {
//                    //指令处理--前置处理（delay、soluteState）

//                    //指令处理--数据包处理
//                    obj->solutePacketData(&it);

//                    //指令处理 --处理完成
//                    it.soluteState=true;

//                    //指令处理--后续处理 （link ）

//                }
//            }

//        }

//        //维护一个延时指令的队列，在处理完正常指令后进行处理延时指令
//    }
    return true;
}

SoluteFunc InstructionManager::findInsFuncFromDictionary(QString catalog, QString funcName)
{
    auto it=m_insFunctionDictionary.find(catalog);
    if(it!=m_insFunctionDictionary.end())
    {
        for(auto it2:it.value())
        {
            if(it2.first==funcName)
            {
                return it2.second;
            }
        }
        qDebug()<<"ERROR:InstructionManager::findInsFuncFromDictionary"<<it.key()<<" No have this function!";
        return m_insFunctionDictionary["Default"][0].second;
    }
    else
    {
        qDebug()<<"ERROR:InstructionManager::findInsFuncFromDictionary :"<<catalog<<" No have this Catalog!";
        return m_insFunctionDictionary["Default"][0].second;
    }
}

void InstructionManager::defaultSolution(GameObject *, QVariant)
{
    qDebug()<<"This Is A Default Ins Func Solution!";
}


InstructionManager::InstructionManager(QObject *parent)
    : QObject{parent}
{

    m_insFunctionDictionary.insert("Demo", QVector<QPair<QString,SoluteFunc> >());

    m_insFunctionDictionary.insert("Default", QVector<QPair<QString,SoluteFunc> >());
    m_insFunctionDictionary["Default"].append(QPair<QString,SoluteFunc>("Default",defaultSolution));

    connect(SourceSystem::getInstance()->getManager(),&SourceManager::newGameObjectRegisted,this,[=](GameObject*obj,QString objName){
        //qDebug()<<"---------++++++++-----------";
        //获取GO的处理策略以及对应的insName，进行注册--相当于汇总
        QVector<QPair<QString,SoluteFunc> > soluteList;
        QMap<QString,SoluteFunc> *tmpList=obj->getSoluteStratagies();
        for(auto it=tmpList->begin();it!=tmpList->end();++it)
        {
            soluteList.append(QPair<QString,SoluteFunc>(it.key(),it.value()) );
        }
        //qDebug()<<soluteList;
        m_insFunctionDictionary[objName]=soluteList;
    });


    connect(SourceSystem::getInstance()->getManager(),&SourceManager::newFuncRegisted,this,[=](SoluteFunc func,QString funcName){
        m_insFunctionDictionary["Demo"].append(QPair<QString,SoluteFunc>(funcName,func));
    });

}
