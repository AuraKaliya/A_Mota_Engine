#include "sourcesystem.h"

SourceSystem::SourceSystem(QObject *parent)
    : SystemObject{parent}
{
    m_sourceManager=SourceManager::getInstance();
}

SourceSystem* SourceSystem::m_instance=nullptr;
SourceSystem *SourceSystem::getInstance(QObject *parent )
{
    if(m_instance==nullptr)
    {
        m_instance=new SourceSystem(parent);
    }
    return m_instance;
}

SourceManager *SourceSystem::getManager()
{
    return m_sourceManager;
}

bool SourceSystem::systemStart()
{
    return true;
}

bool SourceSystem::systemInit()
{
return true;
}

bool SourceSystem::systemSolve()
{
return true;
}

bool SourceSystem::systemQuit()
{
return true;
}
