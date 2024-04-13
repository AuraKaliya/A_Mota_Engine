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
        //m_sourceManageUI->setVisible(true);
        //m_sourceManageUI->setNowUIState(UIWidget::Editor);
        m_widgetList.append(m_sourceManageUI);

        m_gameShowUI=new GameShowWidget(m_rootWidget);
        //m_gameShowUI->setVisible(true);
        //m_gameShowUI->setNowUIState(UIWidget::Editor);
        m_gameShowUI->init();
        m_widgetList.append(m_gameShowUI);

        m_propertyEditUI=new PropertyEditWidget(m_rootWidget);
        //m_propertyEditUI->setVisible(true);
        //m_propertyEditUI->setNowUIState(UIWidget::Editor);
        //m_propertyEditUI->show();
        m_widgetList.append(m_propertyEditUI);

        m_eventEditWidget=new EventEditWidget(m_rootWidget);
        //m_eventEditWidget->setVisible(true);
        //m_eventEditWidget->setNowUIState(UIWidget::Editor);
        m_widgetList.append(m_eventEditWidget);


        m_historyWidget=new HistoryWidget(m_rootWidget);
        m_widgetList.append(m_historyWidget);

        m_itemTreeUI=new ItemTreeWidget(m_rootWidget);
        m_widgetList.append(m_itemTreeUI);


        //临时布局
        //setFixedSize(420,1000);
        m_sourceManageUI->move(10,10);
        //setFixedSize(1050,800);
        m_gameShowUI->move(450,10);
        //setFixedSize(450,600)
        m_propertyEditUI->move(1510,420);
        //resize(500,210);
        m_eventEditWidget->move(1000,810);
        //setFixedSize(550,200);
        m_historyWidget->move(450,810);
        //setFixedSize(400,400);
        m_itemTreeUI->move(1510,10);

        connect(m_rootWidget,SIGNAL(actionSend(QString)),m_historyWidget,SLOT(addAction(QString)));

        connect(InstructionSystem::getInstance()->getManager(),SIGNAL(instructionSend(QString)),m_historyWidget,SLOT(addInstruction(QString)));

        connect(MotaDemo::getInstance(),SIGNAL(eventSend(QString)),m_historyWidget,SLOT(addEvent(QString)));

        connect(EditSystem::getInstance()->getManager(),SIGNAL(initFinished()),m_itemTreeUI,SLOT(updateTree()));

        //不越层调用 ---使用edit而非ui中的
        connect(EditSystem::getInstance()->getManager(),SIGNAL(actionSend(QString)),m_historyWidget,SLOT(addAction(QString)));


        connect(PluginSystem::getInstance()->getManager(),&PluginManager::pluginLoadFinished,this,[this](){
            for(auto it:PluginSystem::getInstance()->getManager()->pluginWidgetList())
            {
                UIWidget* w=static_cast<UIWidget*>(it);
                connect(w,SIGNAL(eventSend(QString)),m_historyWidget,SLOT(addEvent(QString)));
                connect(w,SIGNAL(actionSend(QString)),m_historyWidget,SLOT(addAction(QString)));
                connect(w,SIGNAL(instructionSend(QString)),m_historyWidget,SLOT(addInstruction(QString)));
            }
        });






        //统一设置--Editor
        for(auto it:m_widgetList)
        {
            it->setVisible(true);
            it->setNowUIState(Editor);

            //预设Demo
            GameDemo* demo=SourceSystem::getInstance()->getManager()->getNowDemo();

            if(demo!=nullptr)
            {
                it->setNowDemo(demo);
                qDebug()<<"Now Set the demo"<<demo <<demo->objectName();
                it->demoInit();
            }
            else
            {
                qDebug()<<" WARNNING : NO HAVE NOWDEMO!";
            }


            //连接信息传递至historywidget

            connect(it,SIGNAL(actionSend(QString)),     m_historyWidget,SLOT(addAction(QString))        );
            connect(it,SIGNAL(eventSend(QString)),      m_historyWidget,SLOT(addEvent(QString))         );
            connect(it,SIGNAL(instructionSend(QString)),m_historyWidget,SLOT(addInstruction(QString))   );





        }
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


