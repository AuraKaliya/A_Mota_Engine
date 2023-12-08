#include "sourcemanagewidget.h"

SourceManageWidget::SourceManageWidget(QWidget *parent)
    : UIWidget{parent}
{
    setFixedSize(420,1000);


    m_addSourceWidget=new AddSourceWidget(this);
    m_sourceTreeWidget=new SourceTreeWidget(this);

    m_mainLayout=new QVBoxLayout(this);
    m_mainLayout->addWidget(m_addSourceWidget);
    m_mainLayout->addWidget(m_sourceTreeWidget);

    m_addSourceWidget->setFixedHeight(150);
    m_addSourceWidget->setFixedWidth(420);
    m_sourceTreeWidget->setMinimumHeight(150);
    m_sourceTreeWidget->setFixedWidth(420);

    setLayout(m_mainLayout);
    adjustSize();

    //测试
    m_sourceTreeWidget->addFirstNode("Image",SourceCardViewWidget::ViewClass::IMG);
    m_sourceTreeWidget->addFirstNode("GameObject",SourceCardViewWidget::ViewClass::GO);
    m_sourceTreeWidget->adjustAreaSize();
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

#if 0
    qDebug()<<"hahaha";
    qDebug()<<"this Child："<<this->children();
    for(auto it:this->children())
        qDebug()<<it<<":"<<it->children();
    qDebug()<<"this parent: "<<this->parent();
#endif


    setFocusPolicy(Qt::ClickFocus);
}
