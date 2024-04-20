#include "uisystem.h"
UISystem*UISystem::m_instance=nullptr;
UISystem *UISystem::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new UISystem(parent);
    }
    return  m_instance;
}

UIManager *UISystem::getManager()
{
    return m_uiManager;
}

bool UISystem::systemStart()
{
    return true;
}

bool UISystem::systemInit()
{
    qDebug()<<"UISystem :systemInit";
    m_uiManager->setRoot(static_cast<QWidget*>(this->parent()));
    m_uiManager->loadUI();
    return true;
}

bool UISystem::systemSolve()
{
     return true;
}

bool UISystem::systemQuit()
{
     return true;
}

UISystem::UISystem(QObject *parent)
    : SystemObject{parent}
{
    m_uiManager=UIManager::getInstance();
}
