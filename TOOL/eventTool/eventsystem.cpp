#include "eventsystem.h"
EventSystem* EventSystem::m_instance=nullptr;
EventSystem *EventSystem::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new EventSystem(parent);
    }
    return  m_instance;
}
bool EventSystem::systemStart()
{
    return true;
}

bool EventSystem::systemInit()
{
    return true;
}

bool EventSystem::systemSolve()
{
    return true;
}

bool EventSystem::systemQuit()
{
    return true;
}

EventManager *EventSystem::getManager()
{
    return m_eventManager;
}
EventSystem::EventSystem(QObject *parent)
    : SystemObject{parent}
{
    m_eventManager=EventManager::getInstance();
}
