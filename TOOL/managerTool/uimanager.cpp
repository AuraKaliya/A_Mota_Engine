#include "uimanager.h"



UIManager* UIManager::m_instance=nullptr;
UIManager *UIManager::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new UIManager;
    }
    return  m_instance;
}

void UIManager::setRoot(QWidget *root)
{
    m_rootWidget=root;
}

void UIManager::loadUI()
{
    if(m_rootWidget==nullptr)
    {
        qDebug()<<"No have root! UIManager";
        return;
    }
    if(m_engineState==EngineState::Editor)
    {
        m_sourceManageUI=new SourceManageWidget(m_rootWidget);
        m_sourceManageUI->setVisible(true);

        m_gameShowUI=new GameShowWidget(m_rootWidget);
        m_gameShowUI->setVisible(true);
        m_gameShowUI->init();

        m_propertyEditUI=new PropertyEditWidget(m_rootWidget);
        m_propertyEditUI->setVisible(true);
        //m_propertyEditUI->show();

        m_eventEditWidget=new EventEditWidget(m_rootWidget);
        m_eventEditWidget->setVisible(true);

        //临时布局
        //setFixedSize(420,1000);
        m_sourceManageUI->move(10,10);
        //setFixedSize(1050,800);
        m_gameShowUI->move(450,10);
        //setFixedSize(450,600)
        m_propertyEditUI->move(1510,420);
        //resize(500,210);
        m_eventEditWidget->move(1000,810);



    }
    else if(m_engineState==EngineState::Player)
    {

    }else
    {

    }

}

UIManager::UIManager(QObject *parent)
    : QObject{parent}
{


    //updateNowSceneInfo();
}


