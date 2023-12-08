#include "addgameobjectinfowidget.h"

GameObject *AddGameObjectInfoWidget::getLinkObject() const
{
    return m_linkObject;
}

void AddGameObjectInfoWidget::setLinkObject(GameObject *newLinkObject)
{
    if (m_linkObject == newLinkObject)
        return;
    m_linkObject = newLinkObject;
    //qDebug()<<"objChanged";
    emit linkObjectChanged(m_linkObject);
}

void AddGameObjectInfoWidget::setLinkSourceTreeWidget(SourceTreeWidget *w)
{
    m_linkSourceTreeWidget=w;
    updateList();
}

void AddGameObjectInfoWidget::updateList()
{
    initSecondNodeLabelList();
    initGameObjectClassBoxList();
}

AddGameObjectInfoWidget::AddGameObjectInfoWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(400,800);

    initPixLabel();
    initNodesWidget();
    initPropertyWidget();
    initControBtn();
    initLayouts();

      //qDebug()<<"new";
}

AddGameObjectInfoWidget::AddGameObjectInfoWidget(GameObject *obj, QWidget *parent):AddGameObjectInfoWidget(parent)
{
    //qDebug()<<"obj--new";
    setLinkObject(obj);
}

void AddGameObjectInfoWidget::initPixLabel()
{
    m_pixLabel = new QLabel(this); // 创建一个QLabel对象，将其父对象设为当前类的对象
        // 设置m_pixLabel的其他属性，如文本、字体、对齐方式等
    m_pixLabel->setFixedSize(90,160);

    m_pixLabel->setPixmap(QPixmap(":/RESOURCE/default/GameObjectDefaultPix.png").scaled(m_pixLabel->width(),m_pixLabel->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

void AddGameObjectInfoWidget::initNodesWidget()
{
    m_nodesWidget = new QWidget(this); // 创建一个QWidget对象，将其父对象设为当前类的对象
    m_firstNodeLabel = new QLabel(m_nodesWidget); // 创建一个QLabel对象，将其父对象设为m_nodesWidget
    m_secondNodeLabel = new QComboBox(m_nodesWidget); // 创建一个QLabel对象，将其父对象设为m_nodesWidget
    m_GameObjectClassBox=new QComboBox(m_nodesWidget);
    // 设置m_firstNodeLabel和m_secondNodeLabel的其他属性，如文本、字体、对齐方式等

    m_nodesWidget->setFixedSize(250,160);


    m_firstNodeLabel->setFixedSize(200,40);
    m_firstNodeLabel->setText("GameObject");



    m_secondNodeLabel->setFixedSize(200,40);
    initSecondNodeLabelList();

    m_GameObjectClassBox->setFixedSize(200,40);
    initGameObjectClassBoxList();


    connect(m_GameObjectClassBox,&QComboBox::currentIndexChanged,this,[this](){
        if(m_GameObjectClassBox->isEnabled())
            setLinkObject(m_linkObjectList[m_GameObjectClassBox->currentIndex()]);
    });
    //m_secondNodeLabel->setText("未定义");

}

void AddGameObjectInfoWidget::initPropertyWidget()
{
    m_propertyWidget = new GameObjectPropertiesShowWidget(this); // 创建一个GameObjectPropertiesShowWidget对象，将其父对象设为当前类的对象
    m_informationBox = new QTextEdit(this); // 创建一个QTextEdit对象,将其父对象设为当前类的对象
    // 设置m_informationBox的其他属性，如文本、字体、对齐方式等

    m_propertyWidget->setFixedSize(400,300);
    m_propertyWidget->setStyleSheet("background-color:white;");
    m_propertyWidget->initWidget();

    m_informationBox->setFixedSize(400,250);


    connect(this,&AddGameObjectInfoWidget::linkObjectChanged,m_propertyWidget,[this](GameObject* obj){
        m_propertyWidget->setLinkObject(obj);
        m_propertyWidget->initWidget();
    });

}

void AddGameObjectInfoWidget::initLayouts()
{
    m_nodesLayout = new QVBoxLayout(m_nodesWidget); // 创建一个垂直布局对象，将其父对象设为m_nodesWidget
    m_nodesLayout->addWidget(m_firstNodeLabel); // 将m_firstNodeLabel添加到m_nodesLayout中
    m_nodesLayout->addWidget(m_secondNodeLabel); // 将m_secondNodeLabel添加到m_nodesLayout中
    m_nodesLayout->addWidget(m_GameObjectClassBox);
    m_nodesLayout->setSpacing(20);
    m_nodesLayout->setAlignment(Qt::AlignCenter);


    m_headLayout = new QHBoxLayout(); // 创建一个水平布局对象
    m_headLayout->addWidget(m_pixLabel); // 将m_pixLabel添加到m_headLayout中
    m_headLayout->addWidget(m_nodesWidget); // 将m_nodesWidget添加到m_headLayout中

    m_headLayout->setSpacing(20);


    m_tailLayout= new QHBoxLayout();
    m_tailLayout->addWidget(m_yesBtn);
    m_tailLayout->addWidget(m_noBtn);
    m_tailLayout->setSpacing(20);
    m_tailLayout->setAlignment(Qt::AlignCenter);

    m_mainLayout = new QVBoxLayout(this); // 创建一个垂直布局对象，将其父对象设为当前类的对象
    m_mainLayout->addLayout(m_headLayout); // 将m_headLayout添加到m_mainLayout中
    m_mainLayout->addWidget(m_propertyWidget); // 将m_propertyWidget添加到m_mainLayout中
    m_mainLayout->addWidget(m_informationBox);
    m_mainLayout->addLayout(m_tailLayout);
    m_mainLayout->setSpacing(10);

}

void AddGameObjectInfoWidget::initControBtn()
{

    m_yesBtn=new QPushButton(tr("确定"),this);
    m_noBtn=new QPushButton(tr("取消"),this);

    m_yesBtn->adjustSize();
    m_yesBtn->setVisible(true);

    m_noBtn->adjustSize();
    m_noBtn->setVisible(true);

//    connect(this,&AddGameObjectInfoWidget::linkObjectChanged,this,[this](GameObject* obj){
//        //1. 取消以前绑定的内容
//        //m_yesBtn->disconnect();
//        //2.进行新的绑定
//    });
    connect(m_yesBtn,&QPushButton::clicked,this,[this](){

        for(auto it:*(m_propertyWidget->getPropertyList()))
        {
            it->submitValue();
        }
        qDebug()<<"this!";
        //emit addObject(m_linkObject);
        //SourceSystem::getInstance()->getManager()->addGameObjectFromSample(m_linkObject->getClassName());
        SourceSystem::getInstance()->getManager()->addGameObjectSourceFromSample(m_linkObject->getClassName());
        qDebug()<<"this!2";
        this->close();
    });
}

void AddGameObjectInfoWidget::initSecondNodeLabelList()
{
   //qDebug()<<" AddGameObjectInfoWidget::initSecondNodeLabelList() start";
    //获取当前的GO一栏的二级节点
    if(m_linkSourceTreeWidget!=nullptr)
    {
        m_linkLabelList=m_linkSourceTreeWidget->getGOSecondNodesList();
        //qDebug()<<m_linkLabelList[0]->text();
        //这地方可能会出现内存泄漏
        m_secondNodeLabel->clear();
        for(auto it:m_linkLabelList)
            m_secondNodeLabel->addItem(it->text());
    }

    if(m_secondNodeLabel->maxCount()!=0)
    {
        m_secondNodeLabel->setCurrentIndex(0);
    }

    //qDebug()<<" AddGameObjectInfoWidget::initSecondNodeLabelList() end";
}

void AddGameObjectInfoWidget::initGameObjectClassBoxList()
{
    //qDebug()<<" AddGameObjectInfoWidget::initGameObjectClassBoxList() start";
    QVector<QPair<QString,GameObject*>> list=SourceSystem::getInstance()->getManager()->getGameObjectSampleList();

    //m_GameObjectClassBox在clear时会变动currentIndex
    m_linkObjectList.clear();
    m_GameObjectClassBox->setEnabled(false);
    m_GameObjectClassBox->clear();

    for(auto it:list)
    {
        m_GameObjectClassBox->setEnabled(true);
        m_linkObjectList.append(it.second);
        m_GameObjectClassBox->addItem(it.first);
    }

    if(m_GameObjectClassBox->maxCount()!=0)
    {
        m_GameObjectClassBox->setCurrentIndex(0);
    }
    //qDebug()<<" AddGameObjectInfoWidget::initGameObjectClassBoxList() end";
}
