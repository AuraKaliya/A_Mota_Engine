#include "addsourcewidget.h"

#include <QFileDialog>
#include <QMessageBox>

AddSourceWidget::AddSourceWidget(QWidget *parent)
    : QWidget{parent}
{


    //构建
    m_addSourceByFileBtn=new QPushButton(this);
    m_addSourceByPathBtn=new QPushButton(this);
    m_addNewGameObjectBtn=new QPushButton(this);

    m_mainLayout=new QHBoxLayout(this);
    m_mainLayout->addWidget(m_addSourceByFileBtn);
    m_mainLayout->addWidget(m_addSourceByPathBtn);
    m_mainLayout->addWidget(m_addNewGameObjectBtn);

    //初始化参数
    //m_addSourceByFileBtn
    m_addSourceByFileBtn->setText(QString("导入文件"));
    m_addSourceByFileBtn->setMinimumWidth(100);
    m_addSourceByFileBtn->setMinimumHeight(100);

    //m_addSourceByPathBtn
    m_addSourceByPathBtn->setText(QString("导入文件夹"));
    m_addSourceByPathBtn->setMinimumWidth(100);
    m_addSourceByPathBtn->setMinimumHeight(100);

    //m_addNewGameObjectBtn
    m_addNewGameObjectBtn->setText(QString("新建GO"));
    m_addNewGameObjectBtn->setMinimumWidth(100);
    m_addNewGameObjectBtn->setMinimumHeight(100);

    //m_mainLayout
    m_mainLayout->setSpacing(20);


    //逻辑建立
    connect(m_addSourceByFileBtn,&QPushButton::clicked,this,[&](){
        QString path=QFileDialog::getOpenFileName();
        //qDebug()<<path;
        if(path.isEmpty())
        {
            QMessageBox::warning(this,"打开文件","选择文件路径不能为空");
            return;
        }
        SourceSystem::getInstance()->getManager()->importSource(path);
    });
    connect(SourceSystem::getInstance()->getManager(),&SourceManager::addSource,this,[=](){
        qDebug()<<"addSource";
        emit addSource();
    });
    connect(m_addSourceByPathBtn,&QPushButton::clicked,this,[&](){
        qDebug()<<"loading...";
    });
    connect(m_addNewGameObjectBtn,&QPushButton::clicked,this,[&](){
        qDebug()<<"loading...";
        emit addGameObject();
    });



    setLayout(m_mainLayout);
    adjustSize();
}
