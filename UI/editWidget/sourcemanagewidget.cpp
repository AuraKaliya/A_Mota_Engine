#include "sourcemanagewidget.h"

SourceManageWidget::SourceManageWidget(QWidget *parent)
    : UIWidget{parent}
{
    setFixedSize(420,1010);


    m_addSourceWidget=new AddSourceWidget(this);
    m_sourceTreeWidget=new SourceTreeWidget(this);

    //m_mainLayout=new QVBoxLayout(this);
    //m_mainLayout->addWidget(m_addSourceWidget);
    //m_mainLayout->addWidget(m_sourceTreeWidget);

    m_addSourceWidget->setFixedHeight(150);
    m_addSourceWidget->setFixedWidth(420);
    m_addSourceWidget->move(0,0);

    //m_sourceTreeWidget->setMinimumHeight(150);
    m_sourceTreeWidget->setFixedHeight(845);
    m_sourceTreeWidget->setFixedWidth(420);
    //setLayout(m_mainLayout);
    //adjustSize();

    //测试
    m_sourceTreeWidget->addFirstNode("Image",SourceCardViewWidget::ViewClass::IMG);
    m_sourceTreeWidget->addFirstNode("GameObject",SourceCardViewWidget::ViewClass::GO);
    m_sourceTreeWidget->adjustAreaSize();
    m_sourceTreeWidget->move(0,155);
    //

    //测试
    connect(m_addSourceWidget,&AddSourceWidget::addSource,this,[=](){
        qDebug()<<"AddSource";
        m_sourceTreeWidget->initSource();
    });
    //


    //顺序
    m_addGameObjectInfoWidget=new AddGameObjectInfoWidget();
    m_addGameObjectInfoWidget->setLinkSourceTreeWidget(m_sourceTreeWidget);

    connect(m_addSourceWidget,&AddSourceWidget::addGameObject,this,[this](){
        qDebug()<<"addGameObject start";
        m_addGameObjectInfoWidget->updateList();
        m_addGameObjectInfoWidget->show();
        qDebug()<<"addGameObject end";
    });

    connect(m_addSourceWidget,&AddSourceWidget::outPort,this,[this](){
        qDebug()<<"outPort start";
        SourceSystem::getInstance()->getManager()->outPortDemo();
        qDebug()<<"outPort end";
    });



#if 0
    qDebug()<<"hahaha";
    qDebug()<<"this Child："<<this->children();
    for(auto it:this->children())
        qDebug()<<it<<":"<<it->children();
    qDebug()<<"this parent: "<<this->parent();
#endif


    //setUIStyle();
    setFocusPolicy(Qt::ClickFocus);
}

void SourceManageWidget::setUIStyle()
{
    qDebug()<<"check  SourceManageWidget";
    QString style=
        ""
        "QPushButton:hover { border-radius:10px;color: white;background-color:rgba(52,58,64,0.2); }"
        "QPushButton:!hover { border-radius:10px;color: white;background-color:rgba(52,58,64,0.6); }";




    setStyleSheet(style);
    qDebug()<<"check  SourceManageWidget  end";
}

void SourceManageWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QImage  img(":/RESOURCE/default/Background1.png");
    painter.drawImage(this->rect(),img);

}
