#include "eventmanager.h"

EventManager *EventManager::m_instance=nullptr;
QMap<QString,QVector<InstructionObject*> > EventManager::m_eventToInsDictionary{};
EventManager *EventManager::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new EventManager(parent);
    }
    return m_instance;
}

QVector<QString> EventManager::getEventList()
{
    QVector<QString> tmp;
    for(auto it=m_eventToInsDictionary.begin();it!=m_eventToInsDictionary.end();++it)
    {
        tmp.append(it.key());
    }
    return tmp;
}

QVector<InstructionObject *> EventManager::getInsByEvent(QString event)
{
    auto it=m_eventToInsDictionary.find(event);
    if(it!=m_eventToInsDictionary.end())
        return it.value();
    else
    {
        qDebug()<<"EventManager::getInsByEvent: no have this event!";
        return QVector<InstructionObject *>();
    }
}

bool EventManager::addEvent(QString event)
{
    auto it=m_eventToInsDictionary.find(event);
    if(it!=m_eventToInsDictionary.end())
    {
        qDebug()<<"EventManager::addEvent : have a same event!";
        return false;
    }
    else
    {
        m_eventToInsDictionary.insert(event,* new QVector<InstructionObject *>());
    }
    return true;
}

bool EventManager::delEvent(QString event)
{

    auto it=m_eventToInsDictionary.find(event);
    if(it!=m_eventToInsDictionary.end())
    {
        //需要先把value清理了，再remove key；
        m_eventToInsDictionary.remove(event);
        return true;
    }
    else
    {
        qDebug()<<"EventManager::delEvent : no have this event!";
        return false;
    }
}

bool EventManager::addInsToEvent(QString event, InstructionObject *ins )
{
    auto it=m_eventToInsDictionary.find(event);
    if(it!=m_eventToInsDictionary.end())
    {
        m_eventToInsDictionary[event].append(ins);
        return true;
    }
    else
    {
        qDebug()<<"EventManager::addInsToEvent : no have this event!";
    }
    return false;
}

void EventManager::eventTrigger(QString event)
{
    auto it=m_eventToInsDictionary.find(event);
    if(it!=m_eventToInsDictionary.end())
    {
        for(auto it2:it.value())
        {
            //我觉得还是需要配置一套副本来执行，同时还需要给ins添加对List的处理
            InstructionSystem::getInstance()->getManager()->soluteInstruction(it2);
        }
    }
    else
    {
        qDebug()<<"EventManager::eventTrigger : no have this event!";
    }

}

EventManager::EventManager(QObject *parent)
    : QObject{parent}
{
    m_eventToInsDictionary.insert("Test_Event",QVector<InstructionObject*>());
    InstructionObject* testObj1=new InstructionObject();
    testObj1->setInsName("Test_Instruction1");
    m_eventToInsDictionary["Test_Event"].append(testObj1);
    InstructionObject* testObj2=new InstructionObject();
    testObj2->setInsName("Test_Instruction2");
    m_eventToInsDictionary["Test_Event"].append(testObj2);

}
