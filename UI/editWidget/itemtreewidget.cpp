#include "itemtreewidget.h"

#include <qpainter.h>

ItemTreeWidget::ItemTreeWidget(QWidget *parent)
    : UIWidget{parent}
{
    setFixedSize(400,400);
   // setStyleSheet("background-color:red");
    setVisible(true);
    m_view=new QTreeView(this);
    m_view->setGeometry(0,0,this->width(),this->height());
    //qDebug()<<"check----------------------------------"<< m_view->isVisible();
    m_model=new QStandardItemModel(m_view);

    m_view->setModel(m_model);
    m_model->setHorizontalHeaderLabels(QStringList()<<"ObjectName"<<"Type");


    m_view->setVisible(true);
    m_view->setHeaderHidden(false);
    m_view->expandAll();
    //qDebug()<<"check----------------------------------"<< m_view->isVisible();

//    addScene("scene1");
//    addScene("scene2");
//    addScene("scene3");

//    addItemToScene("scene1","object1.1");
//    addItemToScene("scene1","object1.2");
//    addItemToScene("scene1","object1.3");

//    addItemToScene("scene2","object2.1");
//    addItemToScene("scene2","object2.2");
//    addItemToScene("scene2","object2.3");

//    addItemToScene("scene3","object3.1");
//    addItemToScene("scene3","object3.2");
//    addItemToScene("scene3","object3.3");




    qDebug()<<"check----------------------------------"<<m_SceneToIndexDictionary;
}

void ItemTreeWidget::addScene(QString scene)
{
    QStandardItem * item=new QStandardItem(scene);
    int index=m_itemList.size();
    m_model->setItem(index,0,item);
    m_SceneToIndexDictionary.insert(scene,index);
    m_itemList.append(QVector<QStandardItem*>());

}

void ItemTreeWidget::addItemToScene(QString scene, QString itemName)
{
    QStandardItem * nameItem=new QStandardItem(itemName);
    QStandardItem * typeItem=new QStandardItem("Object");
    int sceneIndex=-1;
    auto it=m_SceneToIndexDictionary.find(scene);
    if(it != m_SceneToIndexDictionary.end())
    {
        sceneIndex=it.value();
    }
    else
    {

    }

    if(sceneIndex==-1) return;

    int itemIndex=m_itemList[sceneIndex].size();
    m_model->item(sceneIndex,0)->setChild(itemIndex,0,nameItem);
    m_model->item(sceneIndex,0)->setChild(itemIndex,1,typeItem);

    m_itemList[sceneIndex].append(nameItem);


}

void ItemTreeWidget::updateTree()
{
    resetTree();

    int sceneIdx=0;
    for(auto it:EditSystem::getInstance()->getManager()->getScenes())
    {
        QString sceneName="Scene"+QString::number(sceneIdx);
        addScene(sceneName);
        for(auto it2:it->items())
        {
            if(static_cast<GameObjectItem*>(it2)->getLinkObj()!=nullptr)
            {
                QString objName=static_cast<GameObjectItem*>(it2)->getLinkObj()->getName();
                addItemToScene(sceneName,objName);
            }
        }
        sceneIdx++;
    }
}

void ItemTreeWidget::resetTree()
{
    //！！！！update！！！！
    //未做内存释放
    m_model->clear();
    m_model->setHorizontalHeaderLabels(QStringList()<<"ObjectName"<<"Type");
    m_SceneToIndexDictionary.clear();
    m_itemList.clear();

}

void ItemTreeWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));
    //painter.drawRect(this->rect());
    //qDebug()<<"check----------------------------------"<< m_view->isVisible();
    //qDebug()<<"check----------------------------------"<< m_view->geometry();
    //qDebug()<<"check----------------------------------"<< m_view->;
}

