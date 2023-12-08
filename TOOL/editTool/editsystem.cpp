#include "editsystem.h"
EditSystem* EditSystem::m_instance=nullptr;
EditSystem *EditSystem::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new EditSystem(parent);
    }
    return  m_instance;
}

bool EditSystem::systemStart()
{
    return true;
}

bool EditSystem::systemInit()
{
return true;
}

bool EditSystem::systemSolve()
{
return true;
}

bool EditSystem::systemQuit()
{
return true;
}

EditManager *EditSystem::getManager()
{
return m_editManager;
}

EditSystem::EditSystem(QObject *parent)
    : SystemObject{parent}
{
    m_editManager=EditManager::getInstance();
}
