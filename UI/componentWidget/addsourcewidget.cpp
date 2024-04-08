#include "addsourcewidget.h"

#include <QFileDialog>
#include <QMessageBox>

AddSourceWidget::AddSourceWidget(QWidget *parent)
    : UIWidget{parent}
{


    //构建
    m_addSourceByFileBtn=new QPushButton(this);
    //m_addSourceByPathBtn=new QPushButton(this);
    m_addNewGameObjectBtn=new QPushButton(this);
    m_outPortBtn=new QPushButton(this);

    m_buttonList<<m_addSourceByFileBtn<<m_addNewGameObjectBtn<<m_outPortBtn;


    m_mainLayout=new QHBoxLayout(this);
    m_mainLayout->addWidget(m_addSourceByFileBtn);
    //m_mainLayout->addWidget(m_addSourceByPathBtn);
    m_mainLayout->addWidget(m_addNewGameObjectBtn);
    m_mainLayout->addWidget(m_outPortBtn);

    //初始化参数
    //m_addSourceByFileBtn
    m_addSourceByFileBtn->setText(QString("导入文件"));
    m_addSourceByFileBtn->setMinimumWidth(50);
    m_addSourceByFileBtn->setMaximumWidth(80);
    m_addSourceByFileBtn->setMinimumHeight(50);

    //m_addSourceByPathBtn
//    m_addSourceByPathBtn->setText(QString("导入文件夹"));
//    m_addSourceByPathBtn->setMinimumWidth(50);
//    m_addSourceByPathBtn->setMinimumHeight(50);

    //m_addNewGameObjectBtn
    m_addNewGameObjectBtn->setText(QString("新建GO"));
    m_addNewGameObjectBtn->setMinimumWidth(50);
    m_addNewGameObjectBtn->setMaximumWidth(80);
    m_addNewGameObjectBtn->setMinimumHeight(50);

    //m_outPortBtn
    m_outPortBtn->setText(QString("导出Demo"));
    m_outPortBtn->setMinimumWidth(50);
    m_outPortBtn->setMaximumWidth(80);
    m_outPortBtn->setMinimumHeight(50);



    //m_mainLayout
    m_mainLayout->setSpacing(5);


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
//    connect(m_addSourceByPathBtn,&QPushButton::clicked,this,[&](){
//        qDebug()<<"loading...";
//    });
    connect(m_addNewGameObjectBtn,&QPushButton::clicked,this,[&](){
        qDebug()<<"loading...";
        emit addGameObject();
    });


    connect(m_outPortBtn,&QPushButton::clicked,this,[&](){
        qDebug()<<"loading...";
        emit outPort();
    });



    setLayout(m_mainLayout);
    adjustSize();
    setUIStyle();
}

void AddSourceWidget::setUIStyle()
{
    for(auto it:m_buttonList)
    {
        it->setStyleSheet(EngineStyle::getInstance()->firstButtonStyle());
    }

}
