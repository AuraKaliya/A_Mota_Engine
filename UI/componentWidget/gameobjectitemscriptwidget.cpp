#include "gameobjectitemscriptwidget.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

GameObjectItemScriptWidget::GameObjectItemScriptWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(420,100);
    initWidget();
}

void GameObjectItemScriptWidget::linkItem(GameObjectItem *item)
{
    m_linkItem=item;
    itemChanged();
}

void GameObjectItemScriptWidget::showHasScriptWidget()
{
    m_hasScriptWidget->setVisible(true);
    m_noScriptWidget->setVisible(false);

    m_fileNameBox->setText(ScriptSystem::getInstance()->getManager()->getScriptFileNameByItemId(m_linkItem->getId()));

}

void GameObjectItemScriptWidget::showNoScriptWidget()
{
    m_hasScriptWidget->setVisible(false);
    m_noScriptWidget->setVisible(true);

}

void GameObjectItemScriptWidget::initWidget()
{
    initHasScriptWidget();
    initNoScriptWidget();
}

void GameObjectItemScriptWidget::initHasScriptWidget()
{
    m_hasScriptWidget=new QWidget(this);
    m_hasScriptWidget->setGeometry(0,0,width(),height());

    m_fileNameBox=new QLineEdit(m_hasScriptWidget);
    m_fileNameBox->setGeometry(20,20,120,60);

    m_changeScriptBtn=new QPushButton(tr("C"),m_hasScriptWidget);
    m_changeScriptBtn->setGeometry(150,20,60,60);


    m_delScriptBtn=new QPushButton(tr("D"),m_hasScriptWidget);
    m_delScriptBtn->setGeometry(220,20,60,60);


    //删除脚本--逻辑绑定
    connect(m_delScriptBtn,&QPushButton::clicked,this,[this](){
        ScriptSystem::getInstance()->getManager()->delScriptFromItem(m_linkItem);
        m_linkItem->setScriptBindState(false);
        showNoScriptWidget();
    });



    m_hasScriptWidget->setVisible(false);
}

void GameObjectItemScriptWidget::initNoScriptWidget()
{
    m_noScriptWidget=new QWidget(this);
    m_noScriptWidget->setGeometry(0,0,width(),height());

    m_addScriptBtn=new QPushButton(tr("Add"),m_noScriptWidget);
    m_addScriptBtn->setGeometry(20,20,120,60);


    connect(m_addScriptBtn,&QPushButton::clicked,this,[this](bool flag){
        QDir dir(QApplication::applicationDirPath()+"/scripts");
        qDebug()<<dir.path();
        QString path=QFileDialog::getOpenFileName(nullptr,QString(),dir.path());

        if(path.isEmpty())
        {
            QMessageBox::warning(this,"打开文件","选择文件路径不能为空");
            return;
        }

        QString finalFilePath;
        QStringList tmpList=path.split("/");
        if(tmpList.size()>1)
        {
            finalFilePath=tmpList[tmpList.size()-1];
        }

        qDebug()<<"final:"<<finalFilePath;
        //ScriptSystem::getInstance()->getManager()->addScript(m_linkItem,"./"+finalFilePath);
        ScriptSystem::getInstance()->getManager()->addScript(m_linkItem,path);
        m_linkItem->setScriptBindState(true);

        //需要添加对GO的处理
        m_hasScriptWidget->setVisible(true);
        m_noScriptWidget->setVisible(false);
        m_fileNameBox->setText("./"+finalFilePath);

    });

    m_loadScriptBtn=new QPushButton(tr("Load"),m_noScriptWidget);
    m_loadScriptBtn->setGeometry(150,20,120,60);

    m_noScriptWidget->setVisible(true);
}

void GameObjectItemScriptWidget::itemChanged()
{
    if(m_linkItem==nullptr)
    {
        qDebug()<<"GameObjectItemScriptWidget:No have Item!";
        return;
    }

    if(m_linkItem->getScriptBindState())
    {
        showHasScriptWidget();
    }
    else
    {
        showNoScriptWidget();
    }



}
