#include "pluginsystem.h"
PluginSystem* PluginSystem::m_instance=nullptr;
PluginSystem::PluginSystem(QObject *parent)
    : SystemObject{parent}
{
    m_pluginManager=PluginManager::getInstance();
}

PluginSystem *PluginSystem::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new PluginSystem(parent);
    }
    return m_instance;
}

PluginManager *PluginSystem::getManager()
{
    return m_pluginManager;
}

bool PluginSystem::systemStart()
{

 return true;
}

bool PluginSystem::systemInit()
{
 m_pluginManager->initPluginList();
 m_pluginManager->setRootWidget(static_cast<UIWidget*>(parent()));
 return true;
}

bool PluginSystem::systemSolve()
{
 return true;
}

bool PluginSystem::systemQuit()
{
 return true;
}
