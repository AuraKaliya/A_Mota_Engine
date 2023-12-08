#include "scriptsystem.h"
ScriptSystem* ScriptSystem::m_instance=nullptr;

ScriptSystem *ScriptSystem::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new ScriptSystem(parent);
    }
    return m_instance;
}

ScriptManager *ScriptSystem::getManager()
{
    return m_scriptManager;
}

bool ScriptSystem::systemStart()
{
    return true;
}

bool ScriptSystem::systemInit()
{
  return true;
}

bool ScriptSystem::systemSolve()
{
  return true;
}

bool ScriptSystem::systemQuit()
{
  return true;
}

ScriptSystem::ScriptSystem(QObject *parent)
    : SystemObject{parent}
{
    m_scriptManager=ScriptManager::getInstance();
}
