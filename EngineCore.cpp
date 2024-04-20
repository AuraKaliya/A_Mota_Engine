#include "EngineCore.h"
#include "ui_EngineCore.h"

#include <QFinalState>
#include<QThread>
#include<QTimer>
#include<QFileDialog>
#include <QMessageBox>

#include "./DATA/systemstate.h"

#include <UI/componentWidget/sourcecardviewwidget.h>
#include <UI/componentWidget/addgameobjectinfowidget.h>
#include <UI/componentWidget/wheelslidewidget.h>
#include <UI/componentWidget/showlabelwidget.h>


//test
#include <UI/editWidget/testwidget.h>
//test


EngineCore::EngineCore(QWidget *parent)
    : UIWidget(parent)
    , ui(new Ui::EngineCore)
{
    ui->setupUi(this);
    setFixedSize(1920,1080);
    move(0,0);
    setStyleSheet("EngineCore{background-color:white;}"
                 );
    // "SourceManageWidget{background-color:black;}"

//构建全局变量

    m_jsonParser=JsonParser::getInstance();
    //构建状态机
    m_stateManager=new StateManger(this);
    //初始化状态机
    QState* engineStartState=new QState(QState::ParallelStates);
    QFinalState* engineStopState=new QFinalState ;
    engineStartState->addTransition(this,SIGNAL(closeEngine()),engineStopState);
    m_stateManager->addState(engineStartState);
    m_stateManager->addState(engineStopState);
    m_stateManager->setInitialState(engineStartState);

    //构建资源系统
    m_sourceSystem=SourceSystem::getInstance(this);
    //绑定状态---注册进状态机
    SystemState*stateToSourceSystem=new SystemState(engineStartState);
    stateToSourceSystem->connectToSystem(m_sourceSystem);
    stateToSourceSystem->connectToStartingBySignal(m_stateManager,SIGNAL(startAllSystem()));

    //构建指令系统
    m_instructionSyStem=InstructionSystem::getInstance(this);
    //绑定状态--注册进状态机
    SystemState*stateToInstructioSystem=new SystemState(engineStartState);
    stateToInstructioSystem->connectToSystem(m_instructionSyStem);
    stateToInstructioSystem->connectToStartingBySignal(m_stateManager,SIGNAL(startAllSystem()));

    //构建编辑系统
    m_editSystem=EditSystem::getInstance(this);
    //绑定状态--注册进状态机
    SystemState*stateToEditSystem=new SystemState(engineStartState);
    stateToEditSystem->connectToSystem(m_editSystem);
    stateToEditSystem->connectToStartingBySignal(m_stateManager,SIGNAL(startAllSystem()));

    //构建UI系统
    m_uiSystem=UISystem::getInstance(this);
    //绑定状态--注册进状态机
    SystemState*stateToUISystem=new SystemState(engineStartState);
    stateToUISystem->connectToSystem(m_uiSystem);
    stateToUISystem->connectToStartingBySignal(m_stateManager,SIGNAL(startAllSystem()));

    //==================================后启动
    //构建脚本系统
    m_scriptSystem=ScriptSystem::getInstance(this);
    //绑定状态--注册进状态机
    SystemState*stateToScriptSystem=new SystemState(engineStartState);
    stateToScriptSystem->connectToSystem(m_scriptSystem);
    stateToScriptSystem->connectToStartingBySignal(m_stateManager,SIGNAL(startAllSystem()));

    //构建插件系统
    m_pluginSystem=PluginSystem::getInstance(this);
    //绑定状态--注册进状态机
    SystemState* stateToPluginSystem=new SystemState(engineStartState);
    stateToPluginSystem->connectToSystem(m_pluginSystem);
    stateToPluginSystem->connectToStartingBySignal(m_stateManager,SIGNAL(startAllSystem()));



    //-------系统构建完成，进入统一管理启动----------//

    //由于状态机的处理需要事件循环来进行分派，事件循环需要通过QApplication的exce进行阻塞启动，所以采用连接方式，通过timer进行自动化启动，通过信号进行各阶段关联。
    //构造函数里只能是状态的设置和前置的配置。
    QTimer *startTimer=new QTimer;
    startTimer->setInterval(20);
    connect(startTimer,&QTimer::timeout,this,[=](){
        qDebug()<<"Timer timeOut";
        startTimer->stop();
        startTimer->deleteLater();
        startSystem();
    });

    m_stateManager->start();
    startTimer->start();


    //-------系统启动完成，进入工作状态----------//

//后续处理

/*TEST*/

//    SourceCardViewWidget *w=new SourceCardViewWidget();
//    w->setWindowFlags(Qt::FramelessWindowHint);
//    w->setFixedSize(500,500);
//    w->show();



//    AddGameObjectInfoWidget* w=new AddGameObjectInfoWidget();
//    w->show();



//    showLabelWidget * w3=new showLabelWidget();
//    w3->resize(200,50);
//    w3->setPair("GOClass","MotaMap");
//    w3->setRatio(3,7,5,5);
//    w3->initWidget();
//    w3->show();

/*TEST*/


}

EngineCore::~EngineCore()
{
    delete ui;
}

void EngineCore::test()
{


//    QTimer *startTimer=new QTimer;
//    startTimer->setInterval(20);
//    connect(startTimer,&QTimer::timeout,this,[=](){
//        GlobalKeyValue keyValue;
//        if(keyValue.getKeyPressedState("d"))
//            testx++;
//        if(keyValue.getKeyPressedState("a"))
//            testx--;
//        qDebug()<<"NowX:"<<testx;
//    });
//    startTimer->start();

}

void EngineCore::startSystem()
{
    m_stateManager->startSystem();
}

bool EngineCore::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type()==QEvent::KeyPress)
    {
        QKeyEvent*keyEvent=static_cast<QKeyEvent* >(e);
        keyPressEvent(keyEvent);

        //是否会和本身的处理冲突--调用两次
        return false;
    }else
    {
        return QWidget::eventFilter(obj,e);
    }
}

void EngineCore::mousePressEvent(QMouseEvent *e)
{
    emit clickedHere(QPoint(e->globalPosition().x(),e->globalPosition().y()));
    UIWidget::mousePressEvent(e);
}

void EngineCore::keyPressEvent(QKeyEvent *e)
{
    qDebug()<<e->key() << "Key Pressed";
    char keyChar=e->key();
    emit actionSend(QString(keyChar)+" Pressed.");
    //qDebug()<<Qt::Key_Up;
    //if(e->key()==)

    //================================test=================================
    if(e->key() == Qt::Key_P && (e->modifiers() & Qt::ControlModifier))
    {
        emit actionSend(QString("init Source."));
        on_testBtn_clicked();
    }

    if(e->key() == Qt::Key_O && (e->modifiers() & Qt::ControlModifier))
    {
        emit actionSend(QString("init Demo."));
        on_insButton_clicked();
    }

    if(e->key() == Qt::Key_I && (e->modifiers() & Qt::ControlModifier))
    {
        emit actionSend(QString("load plugin."));
        on_pushButton_2_clicked();
    }

    if(e->key() == Qt::Key_U && (e->modifiers() & Qt::ControlModifier))
    {
       emit actionSend(QString("switch style."));
       on_styleButton_clicked();
    }
    //================================test=================================
    GlobalKeyValue keyValue;
    //目前支持定义0-9：48~57  a-z:65~90
    if(e->key()>=65&&e->key()<=90)
    {
        *(keyValue.keyDictionaryByChar.find(e->key()-65).value())=true;
    }

    if(e->key()>=48&&e->key()<=57)
    {
        *(keyValue.keyDictionaryByNum.find(e->key()-48).value())=true;
    }

#if 0
qDebug()<<"*****************";
    for(auto it=keyValue.keyPressedDictionary.begin();it!=keyValue.keyPressedDictionary.end();++it)
    {
        qDebug()<<it.key()<<" "<<*it.value();
    }
qDebug()<<"*****************";
#endif
}

void EngineCore::keyReleaseEvent(QKeyEvent *e)
{
    //qDebug()<<"==============================";
    qDebug()<<e->key() << "Key Release";
    //qDebug()<<Qt::Key_Up;
    GlobalKeyValue keyValue;
    //目前支持定义0-9：48~57  a-z:65~90
    if(e->key()>=65&&e->key()<=90)
    {
        *(keyValue.keyDictionaryByChar.find(e->key()-65).value())=false;
    }

    if(e->key()>=48&&e->key()<=57)
    {
        *(keyValue.keyDictionaryByNum.find(e->key()-48).value())=false;
    }
#if 0
    qDebug()<<"*****************";
    for(auto it=keyValue.keyPressedDictionary.begin();it!=keyValue.keyPressedDictionary.end();++it)
    {
        qDebug()<<it.key()<<" "<<*it.value();
    }
    qDebug()<<"*****************";
#endif
}


void EngineCore::on_testBtn_clicked()
{
#if 0
    //ScriptManager::getInstance();
    QString path="C:/Users/Aura/Desktop/22333.png";
    //qDebug()<<path;
    if(path.isEmpty())
    {
        QMessageBox::warning(this,"打开文件","选择路径不能为空");
        return;
    }
    for(int i=0;i<10;++i)
        m_sourceSystem->getManager()->importSource(path);

    path="D:/QTF/A_Mota_Engine/RESOURCE/demoSetting/MotaTest1.json";
    m_sourceSystem->getManager()->importSource(path);
    qDebug()<<m_sourceSystem->getManager()->getPixmapList();
#endif

    QString path="D:/QTF/A_Mota_Engine/RESOURCE/demoSetting/MotaTest1.json";
    //m_sourceSystem->getManager()->importSource(path);

    path="D:/QTF/A_Mota_Engine/RESOURCE/setting/defaultSource.json";
    m_sourceSystem->getManager()->importSource(path);
    qDebug()<<"on_testBtn_clicked"<<m_sourceSystem->getManager()->getPixmapList();
#if 0
    qDebug()<<"Test--------------遍历文件----------------";
    QDir dir("D:/QTF/A_Mota_Engine/RESOURCE/default/MotaPix");
    if(!dir.exists())
    {
        qDebug()<<" No have this dir!";
    }
    else
    {
        dir.setFilter(QDir::Files|QDir::NoSymLinks);
        QStringList filters;
        filters<<"*.png"<<"*.jpg";
        dir.setNameFilters(filters);
        QStringList list =dir.entryList();
        for(auto it:list)
        {
            m_sourceSystem->getManager()->importSource(QString(dir.path()+"/"+it));
        }
    }
    qDebug()<<"Test--------------遍历文件----------------end";
#endif


    //m_editSystem->getManager()->initFromDemo();
}


void EngineCore::on_pushButton_clicked()
{
    qDebug()<<"on_pushButton_clicked";
//    for(auto it:m_sourceSystem->getManager()->getNowDemo()->getElement())
//    {
//        it->tick();
//        //AddGameObjectInfoWidget* w=new AddGameObjectInfoWidget(it);
//        //w->show();
//    }

    //m_editSystem->getManager()->loadNextScene();

    TestWidget* w=new TestWidget();
    setFixedSize(0,0);
    setParent(w);
    setVisible(true);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    w->init();
    w->show();
    //w->setFocus();
    connect(w,&TestWidget::closed,this,[this](){
        this->setParent(nullptr);
        this->show();
        setFixedSize(1920,1080);
        setVisible(true);
        move(0,0);
                                         });
    //this->hide();




    qDebug()<<"on_pushButton_clicked end";
}


void EngineCore::on_insButton_clicked()
{
    //测试指令
    /*
        1.建立一个指令：
        2.传到InsSys->InsManager中进行处理
        3.通过tick看是否真执行了
    */
//    InstructionObject* insObj=new InstructionObject;
//    InstructionContext insContext;
//    insContext.insModel="DemoIns";
//    InsPacketData data1;
//    data1.insName="ChangeElement";
//    data1.ObjectIndex=9000001;
//    //Value
//    QVariant var;
//    QList <QVariant> pvarList;
//    pvarList.append(QVariant(0));
//    pvarList.append(QVariant(2));
//    pvarList.append(QVariant(0));
//    pvarList.append(QVariant(33));
//    var.setValue(pvarList);
//    data1.value=var;
//    //Value
//    data1.insIndex=insContext.insPacket.size();
//    insContext.insPacket.append(data1);

//    insObj->setInsContext(insContext);

//    m_instructionSyStem->getInstance()->getManager()->soluteInstruction(insObj);


   // qDebug()<<m_sourceSystem->getManager()->getGameObjectSampleList()[0].first;
    //qDebug()<<* m_sourceSystem->getManager()->getComponentByGameObjectName(m_sourceSystem->getManager()->getGameObjectSampleList()[0].first);
   m_editSystem->getManager()->initFromDemo();

   //检查pixSource

//   for(auto it:m_sourceSystem->getManager()->getPixSourceList())
//   {
//        qDebug()<<it->pix()<<it->id()<<it->pix()->isNull()<<it->stateIndexList()<<it->stateList();
//   }


}


void EngineCore::on_pushButton_2_clicked()
{
   qDebug()<<"==================load Plugin==============";
   m_pluginSystem->getInstance()->getManager()->loadPlugins();
    qDebug()<<"==================load Plugin==============end";
}


void EngineCore::on_styleButton_clicked()
{
    if(EngineStyle::getInstance()->styleName()=="Default")
    {
        EngineStyle::getInstance()->setStyleName("Night");
    }
    else
    {
        EngineStyle::getInstance()->setStyleName("Default");
    }

    m_uiSystem->getInstance()->getManager()->updateUIStyle();
}

