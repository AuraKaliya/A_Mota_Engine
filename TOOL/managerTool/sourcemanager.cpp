#include "sourcemanager.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QMetaProperty>


QMap<QString, readFunc> SourceManager::m_importStrategise{};
QMap<unsigned int , QPixmap* > SourceManager::m_pixmapDictionary{};
QMap<unsigned int ,QVector<QPixmap> > SourceManager::m_multiplePixDictionary{};
QMap<unsigned int , QString >  SourceManager::m_sourcePathDictionary{};
QMap<unsigned int,GameObject*> SourceManager::m_gameObjectDictionary{};
QMap<unsigned int,GameObjectItem*>SourceManager::m_gameObjectItemDictionary{};
QMap<QString,readJsonFunc> SourceManager::m_readJsonStrategise{};
QMap<QString,GameDemo*> SourceManager::m_gameDemoDictionary{};
QMap<QString,GameObject*> SourceManager::m_gameObjectSampleDictionary{};
QMap<QString,GameObject*> SourceManager::m_gameObjectSourceDictionary{};
QMap<unsigned int,SourceMetaData*>SourceManager::m_sourceMetaDataDictionary{};
QMap<QString,QVector<QString>> SourceManager::m_gameObjectComponentList{};
QMap<QString,QVector<QPair<QString,QString> > > SourceManager::m_gameObjectBasePropertyList{};
QMap<QString,QVector<QMetaProperty> > SourceManager::m_gameObjectPropertyList{};
QMap<QString,QVector<QMetaProperty>> SourceManager::m_gameObjectComponentPropertyList{};
SourceManager* SourceManager::m_instance=nullptr;

unsigned int SourceManager::m_maxSourceId=1000001;
unsigned int SourceManager::m_maxGameObjectId=9000001;
unsigned int SourceManager::m_maxGameObjectItemId=8000001;

QPixmap* SourceManager::m_defaultPix=nullptr;

SourceManager::SourceManager(QObject *parent)
    : QObject{parent}
{
    m_importStrategise.insert("jpg",readImage);
    m_importStrategise.insert("jpeg",readImage);
    m_importStrategise.insert("gif",readImage);
    m_importStrategise.insert("png",readImage);
    m_importStrategise.insert("bpm",readImage);
    m_importStrategise.insert("json",readJson);

    m_readJsonStrategise.insert("Demo",readJsonFileToDemo);
    m_readJsonStrategise.insert("Source",readJsonFileToSource);

    //设置Default
    m_defaultPix=new QPixmap(":/RESOURCE/default/GameObjectDefaultPix.png");


    //注册Demo  ---固有Demo
    /*
        1. 注册进Map
        2. 绑定处理逻辑--绑定信号-槽：Demo中创建GO时，需要添加进SourceManager中进行管理

    */
    // 1. 注册进Map
    m_gameDemoDictionary.insert("Mota",MotaDemo::getInstance());

    // 2. 绑定处理逻辑
        //绑定GO注册事件
    connect(MotaDemo::getInstance(),&MotaDemo::objectRegistToManager,this,[=](GameObject* newGO,QString GOName){
        //注册GO  -- 这里传入的newGO是一个单独的对象实体。
        const QMetaObject *p=newGO->metaObject();
        //将GO的BaseProperty注册
        QVector<QPair<QString,QString> > basepropertyList;
        QVector<QMetaProperty> propertyList;
        bool flag=true;
        int i=0;
        while(flag)
        {
            QMetaProperty property=p->property(i++);
            if(property.isValid())
            {
                QPair<QString,QString> tmp(property.name(),property.read(newGO).toString());
                basepropertyList.append(tmp);
                propertyList.append(property);
            }
            else
            {
                flag=false;
                continue;
            }
        }
        //注册GO的属性
        m_gameObjectBasePropertyList[GOName]=basepropertyList;
        m_gameObjectPropertyList[GOName]=propertyList;
        //
        //qDebug()<<GOName;
        qDebug()<<basepropertyList;
        //
        //将GO的ComponentObject注册
        QVector<QString> componentList;
        for(auto it:newGO->getMyComponents())
        {
            QVector<QMetaProperty> componentPropertyList;
            const QMetaObject *p=it->metaObject();
            QMetaProperty property=p->property(0);
            //
            //qDebug()<<property.name();
            //
            componentList.append(property.read(it).toString());
            bool flag2=true;
            int i=1;
            while(flag2)
            {
                QMetaProperty componentProperty=p->property(i++);
                if(componentProperty.isValid())
                {
                    componentPropertyList.append(componentProperty);
                    qDebug()<<"component: "<<property.read(it).toString()<<
                        "  componentProperty: "<<componentProperty.name()<<
                        "  componentPropertyValue: "<<componentProperty.read(it).toString();
                }
                else
                {
                    flag2=false;
                    continue;
                }
            }
            //注册GO组件的属性
            m_gameObjectComponentPropertyList[property.read(it).toString()]=componentPropertyList;
        }
        //
        qDebug()<<componentList;
        //
        //注册GO的组件
        m_gameObjectComponentList[GOName]=componentList;

        //注册GO的样本
        registerGameObjectSample(newGO,GOName);

        //发送“新GO注册”的信号，该信号由InstructionManager捕获，并进行指令集的更新
        emit newGameObjectRegisted(newGO,GOName);
    });

    connect(MotaDemo::getInstance(),&MotaDemo::demoFuncRegistToManager,this,[=](SoluteFunc func,QString funcName){
        emit newFuncRegisted(func,funcName);
    });

        //绑定GO创立事件

    connect(MotaDemo::getInstance(),&MotaDemo::objectCreated,this,[=](GameObject* newGO){
        //判断是否注册成功并进行处理。
        registerGameObjectById(m_maxGameObjectId,newGO);

        //无论如何 id都会增加
        m_maxGameObjectId++;
        qDebug()<<"register GameObject "<<m_maxGameObjectId;
    });
    connect(MotaDemo::getInstance(),&MotaDemo::objectCreatedFromFile,this,[=](GameObject* newGO,unsigned int id){
         //判断是否注册成功并进行处理。
        registerGameObjectById(id,newGO);
        m_maxGameObjectId=qMax(id+1,m_maxGameObjectId);
        qDebug()<<"register GameObject "<<id;
    });


    setNowDemo(MotaDemo::getInstance());

}

SourceManager *SourceManager::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance=new SourceManager;
    }
    return  m_instance;
}

void SourceManager::importSource(QString path)
{

    //判断path的合法性
    QString tail=path.split(".")[1];
    //分类--策略模式 -- 调用相应的载入函数
    auto it =m_importStrategise.find(tail);
    if(it!=m_importStrategise.end())
    {
        bool flag=it.value()(path);

        if(!flag)
        {
            //添加失败
            qDebug()<<"path:"<<path;
            qDebug()<<"添加失败";
        }
        else
        {
            //添加成功
            qDebug()<<"path:"<<path;
            qDebug()<<"添加成功";
            emit addSource();
        }
    }

    //无论结果如何，idx都会增加。
    m_maxSourceId++;

}

void SourceManager::addGameObject(GameObject *gameObject)
{

   // m_gameObjectDictionary.insert(gameObject->getId(),gameObject);
    m_gameObjectDictionary[gameObject->getId()]=gameObject;

    for(auto it=m_gameObjectDictionary.begin();it!=m_gameObjectDictionary.end();++it)
    {
        qDebug()<<it.key()<<it.value();
    }
    emit addSource();
}

void SourceManager::addGameObjectFromSample(QString objClass)
{
    // 1.从static中获取当前的id，对objName中的id进行修改
    //需要获取的是子类对象的内存，用基类指针对象GameObject*进行存储。   ---用工厂
    //qDebug()<<"SourceManager::addGameObjectFromSample";
    //qDebug()<<objName;

    GameObject* newObj=Factory<GameObject>::GetInstance()->CreateObject(objClass);
    //qDebug()<<newObj->getClassName();
    *newObj<<(*m_gameObjectSampleDictionary[objClass]);
    // 2.addGameObject
    registerGameObjectById(m_maxGameObjectId,newObj);
     // 3.更新全局id
    m_maxGameObjectId++;
    //qDebug()<<"register GameObject "<<m_maxGameObjectId;
}

void SourceManager::addGameObjectSourceFromSample(QString objClass)
{
    // 1.从static中获取当前的id，对objName中的id进行修改
    //需要获取的是子类对象的内存，用基类指针对象GameObject*进行存储。   ---用工厂
    GameObject* newObj=Factory<GameObject>::GetInstance()->CreateObject(objClass);
    //qDebug()<<newObj->getClassName();
    *newObj<<(*m_gameObjectSampleDictionary[objClass]);
    // 2.addGameObjectToSource
    registerGameObjectSource(newObj,newObj->getName());
    //qDebug()<<"register GameObject "<<newObj->getName();
    emit addSource();
}

GameObject* SourceManager::addGameObjectFromSource(QString objName)
{

    GameObject* newObj=Factory<GameObject>::GetInstance()->CreateObject(m_gameObjectSourceDictionary[objName]->getClassName());

    *newObj<<(*m_gameObjectSourceDictionary[objName]);

    addGameObjectById(newObj,m_maxGameObjectId);
    m_maxGameObjectId++;
    return newObj;
}

void SourceManager::addGameObjectById(GameObject *obj, unsigned int id)
{
    obj->setId(id);
    //m_gameObjectDictionary.insert(id,gameObject);
    addGameObject(obj);
}

void SourceManager::addGameObjectItem(GameObjectItem *item)
{
    qDebug()<<"now show Item id:"<<item->getId();
    m_gameObjectItemDictionary[item->getId()]=item;
}

void SourceManager::addGameObejctItemById(GameObjectItem *item, unsigned int id)
{
    m_gameObjectItemDictionary[id]=item;
}

GameObjectItem *SourceManager::getGameObjectItemById(unsigned int id)
{
    auto it=m_gameObjectItemDictionary.find(id);
    if(it!=m_gameObjectItemDictionary.end())
    {
        return it.value();
    }
    return nullptr;
}

void SourceManager::registerGameObjectSample(GameObject *obj, QString objClass)
{
    m_gameObjectSampleDictionary[objClass]=obj;
}

void SourceManager::registerGameObjectSource(GameObject *obj, QString objName)
{
    //尝试进行资产注册
    if(objName!="")
    {
        if(getInstance()->getGameObjectSourceByName(objName)==nullptr)
        {

            m_gameObjectSourceDictionary[objName]=obj;
        }
        else
        {
            qDebug()<<"ERROR:已有同名GO："<<objName;
        }
    }else
    {
        qDebug()<<"ERROR:object name is null";
    }
    qDebug()<<"***************";
    for(auto it:m_gameObjectSourceDictionary)
    {
        qDebug()<<it;
    }
    qDebug()<<m_gameObjectSourceDictionary;
    qDebug()<<"***************";

}

void SourceManager::modifySource(QByteArray data, QString path)
{

}

QString SourceManager::getSourcePathById(unsigned int id)
{
    auto it=m_sourcePathDictionary.find(id);
    if(it != m_sourcePathDictionary.end())
    {
        return it.value();
    }
    else
    {
        return QString("");
    }

}

QPixmap *SourceManager::getPixmapById(unsigned int id)
{
    auto it=m_pixmapDictionary.find(id);
    if(it!=m_pixmapDictionary.end())
    {
        return  it.value();
    }
    else
    {
        //返回默认值
        qDebug()<<"Error:pixID"<<id;
        qDebug()<<"return default pix";
        return m_defaultPix;
    }

}

QPixmap *SourceManager::getPixmapById(unsigned int id, bool defaultPix)
{
    if(defaultPix)
    {
        return getPixmapById(id);

    }
    else
    {
        auto it=m_pixmapDictionary.find(id);
        if(it!=m_pixmapDictionary.end())
        {
            return  it.value();
        }
        else
        {
            //返回默认值
            qDebug()<<"Error:pixID"<<id;
            return nullptr;
        }
    }
}

QPixmap *SourceManager::getPixmapByObject(GameObject *obj)
{
    //获取GO的PixID;
    int id=obj->getPixId();
    //查找对应Image并返回
    return getPixmapById(id);
}

GameObject *SourceManager::getObjectById(unsigned int id)
{
    auto it=m_gameObjectDictionary.find(id);
    if(it!=m_gameObjectDictionary.end())
    {
        return it.value();
    }
    return nullptr;
}

QVector<QPair<int, QPixmap *> > SourceManager::getPixmapList()
{
    QVector<QPair<int, QPixmap *> > vector;
    for(auto it=m_pixmapDictionary.begin();it!=m_pixmapDictionary.end();++it)
    {
        vector.append(QPair<int, QPixmap *>(it.key(),it.value()) );
    }
    return vector;
}

QVector<QPair<unsigned int, GameObject *> > SourceManager::getGameObjectList()
{

    QVector<QPair<unsigned int, GameObject *> > vector;
    for(auto it=m_gameObjectDictionary.begin();it!=m_gameObjectDictionary.end();++it)
    {
        vector.append(QPair<unsigned int, GameObject *> (it.key(),it.value()) );
    }
    return vector;
}

QVector<GameObject *> SourceManager::getGameObjectSourceList()
{
    QVector< GameObject *> vector;
    for(auto it=m_gameObjectSourceDictionary.begin();it!=m_gameObjectSourceDictionary.end();++it)
    {
        vector.append(it.value());
    }
    return vector;
}

GameObject *SourceManager::getGameObjectSourceByName(QString name)
{
    auto it=m_gameObjectSourceDictionary.find(name);
    if(it!=m_gameObjectSourceDictionary.end())
    {
        return it.value();
    }else
    {
        return nullptr;
    }
}

QVector<QPair<QString, GameObject *> > SourceManager::getGameObjectSampleList()
{
    QVector<QPair<QString, GameObject *> > vector;
    for(auto it=m_gameObjectSampleDictionary.begin();it!=m_gameObjectSampleDictionary.end();++it)
    {
        vector.append(QPair<QString, GameObject *> (it.key(),it.value()) );
    }
    return vector;
}

QVector<QString> *SourceManager::getComponentByGameObjectName(QString name)
{
    auto it=m_gameObjectComponentList.find(name);
    if(it!=m_gameObjectComponentList.end())
    {
        return &it.value();
    }else
    {
        return nullptr;
    }
}

QVector<QMetaProperty> *SourceManager::getComponentPropertyByComponentName(QString name)
{
    auto it=m_gameObjectComponentPropertyList.find(name);
    if(it!=m_gameObjectComponentPropertyList.end())
    {
        return &it.value();
    }else
    {
        return nullptr;
    }
}

QVector<QMetaProperty> *SourceManager::getGameObjectPropertyByObjectName(QString name)
{
    auto it=m_gameObjectPropertyList.find(name);
    if(it!=m_gameObjectPropertyList.end())
    {
        return &it.value();
    }else
    {
        return nullptr;
    }
}

SourceMetaData *SourceManager::getSourceMetaDataFromPixById(unsigned int id)
{

    SourceMetaData* data=findSourceMetaData(id);
    if(data==nullptr)
    {
        data=new SourceMetaData;
        QPixmap* pix=getPixmapById(id);
        if(pix!=nullptr)
        {
            data->Class+="Image_";
            data->Gid=id;
            data->Name=QString("[IMG]"+QString::number(id));
            data->Icon=pix;
            data->Information=QString("图片："+QString::number(id));
        }
    }


    return data;
}

SourceMetaData* SourceManager::getSourceMetaDataFromGOById(unsigned int id)
{
    qDebug()<<"SourceManager::getSourceMetaDataFromGOById";
    SourceMetaData* data=findSourceMetaData(id);
    if(data==nullptr)
    {
        qDebug()<<"data=null";

        data=new SourceMetaData;
        GameObject* obj=getObjectById(id);
        if(obj!=nullptr)
        {
            data->Class+="GameObject_";
            data->Class+=obj->getClassName();
            data->Gid=id;
            data->Name=QString(obj->getName());
            data->Icon=getPixmapByObject(obj);
            //information
            data->Information=QString("对象："+QString::number(id));
            //
        }
    }
    return data;
}

SourceMetaData *SourceManager::getSourceMetaDataFromGOSourceByName(QString objName)
{

    SourceMetaData* data=new SourceMetaData;
    GameObject* obj=m_gameObjectSourceDictionary[objName];
    //qDebug()<<"if object"<<(obj==nullptr);
    if(obj!=nullptr)
    {
        data->Class+="GameObject_";
        data->Class+=obj->getClassName();
        data->Name=QString(obj->getName());
        data->Icon=getPixmapByObject(obj);
        //information
        data->Information=QString("对象："+obj->getName());
    }

    return data;
}

QVector<QPixmap> SourceManager::cutPixFromId(unsigned int id, int startX, int startY, int perWidth, int perHeight, int xInterval, int yInterval)
{
    // ---优化---
    // 可以将参数缩减，用一个结构体来描述切割的属性
    // ---优化---

    QPixmap* sourcePix=getPixmapById(id,false);
    if(sourcePix==nullptr)
    {
        qDebug()<<"SourceManager::cutPixFromId : no have this pix!";
        return QVector<QPixmap> ();
    }
    else
    {
        int sourceWidth=sourcePix->width();
        int sourceHeight=sourcePix->height();
        qDebug()<<"$$$"<<sourceWidth<<sourceHeight;
        QVector<QPixmap> pixList;
        //进行切割。
        int nowY=startY;
        //暂时用不上--用于控制切割碎片的
        int pixHeight=qMin(sourceHeight-nowY,perHeight);
        while((nowY+perHeight+yInterval)<=sourceHeight)
        {
            int nowX=startX;
            int pixWidth=qMin(sourceWidth-nowX,perWidth);
            while((nowX+perWidth+xInterval)<=sourceWidth)
            {
                pixList.append(*new QPixmap(sourcePix->copy(nowX,nowY,perWidth,perHeight)));
                nowX+=(xInterval+perWidth);
            }
            nowY+=(yInterval+perHeight);
        }
        qDebug()<<"$$$$"<<pixList.size()<<"$$$$"<<id;
        m_multiplePixDictionary[id]=pixList;
        return pixList;
    }
}

QVector<QVector<QPixmap *> > SourceManager::getMultiplePixByControlList(unsigned int id,QString indexStrList)
{
    qDebug()<<"---SourceManager::getMultiplePixByControlList---";
    QVector<QVector<QPixmap *> >   res;

    QVector<QVector<int> > indexList;

    for(auto it:indexStrList.split("|"))
    {
        QVector<int> tmp;
        for(auto it2:it.split(","))
        {
            tmp.append(it2.toInt());
        }
        indexList.append(tmp);
    }

    //需要添加错误控制

    auto sourceList=m_multiplePixDictionary[id];

    qDebug()<<"check0:"<<id<<sourceList.size();
    for(auto it:indexList)
    {
        QVector<QPixmap *>  tmp;
        for(auto it2:it)
        {
            tmp.append(&(sourceList[it2]));
        }
        res.append(tmp);
    }
    qDebug()<<"---SourceManager::getMultiplePixByControlList---end";
    return res;
}

QVector<QVector<int> > SourceManager::getIndexListByStr(QString indexStrList)
{
    QVector<QVector<int> > indexList;

    for(auto it:indexStrList.split("|"))
    {
        QVector<int> tmp;
        for(auto it2:it.split(","))
        {
            tmp.append(it2.toInt());
        }
        indexList.append(tmp);
    }
    return indexList;
}

GameDemo *SourceManager::getNowDemo()
{
    return m_nowDemo;
}

void SourceManager::addPixmap(unsigned int id, QString path, QPixmap *pix)
{
    //需要动态更新maxSourceId --后续进行重构
    m_maxSourceId=qMax(id,m_maxSourceId);

    bool flag=true;
    flag= registerSourcePathById(id,path);
    //如果注册失败，则进行错误处理，同时释放资源
    if(!flag)
    {
        ;
    }

    flag=registerPixmapById(id,pix);
    if(!flag)
    {
        ;
    }


}

bool SourceManager::readImage(QString path)
{
    QPixmap* pix=new QPixmap(path);

    if(pix == nullptr) return false;

    addPixmap(m_maxSourceId,path,pix);

    return true;
}

bool SourceManager::readJson(QString path)
{
    //Type -> Demo Setting Widget
    //需要引入相应的Demo模块，默认为MotaDemo
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning()<<"Error:Cannot open file "<<path;
        return false;
    }
    QByteArray data=file.readAll();
    QJsonParseError parseError;
    QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error!=QJsonParseError::NoError||doc.isNull()||!doc.isObject())
    {
        qDebug()<<"Error:faild to ex"<<path;
        return false;
    }
    QJsonObject root=doc.object();


    auto it=m_readJsonStrategise.find(root.value("Type").toString());
    if (it!=m_readJsonStrategise.end())
    {
        it.value()(root.value("Data").toObject());
        return true;
    }
    else
    {
        qDebug()<<"Error:Faild to find this Type"<<root.value("Type").toString();
        return false;
    }
    return true;
}

bool SourceManager::registerSourcePathById(unsigned int id, QString path)
{
    qDebug()<<"---SourceManager::registerSourcePathById---";
    //qDebug()<<id<<path;
    m_sourcePathDictionary.insert(id,path);
    qDebug()<<"---SourceManager::registerSourcePathById---end";
    return true;
}

bool SourceManager::registerGameObjectById(unsigned int id, GameObject *gameObject)
{
    qDebug()<<"---SourceManager::registerGameObjectById---";
    qDebug()<<"check0:"<<gameObject->getId()<< id<<gameObject->getPixIdList();
    gameObject->setId(id);
    getInstance()->registerGameObjectSource(gameObject,gameObject->getName());
    //m_gameObjectDictionary.insert(id,gameObject);
    getInstance()->addGameObject(gameObject);

    qDebug()<<"---SourceManager::registerGameObjectById---end";
    return true;
}

bool SourceManager::registerPixmapById(unsigned int id, QPixmap *pix)
{
    qDebug()<<"---SourceManager::registerPixmapById---";
   // qDebug()<<id<<pix;
   m_pixmapDictionary.insert(id,pix);
   qDebug()<<"---SourceManager::registerPixmapById---end";
    return true;
}

void SourceManager::readJsonFileToDemo(QJsonObject obj)
{
    auto it=m_gameDemoDictionary.find(obj.value("Demo").toString());

    if(it!=m_gameDemoDictionary.end())
    {

        getInstance()->setNowDemo(it.value());
        it.value()->init(&obj);
    }
}

void SourceManager::readJsonFileToSource(QJsonObject obj)
{
    qDebug()<<"---SourceManager::readJsonFileToSource---";
    qDebug()<<"check-1:"<<obj.keys();
    QJsonObject dataObj=obj.value("Image").toObject();
    qDebug()<<"check0:"<<dataObj.keys();
    if(obj.contains("Image"))
    {
        //添加Image
            //----读取数据
        QJsonObject imageObj=obj.value("Image").toObject();

        QString imageDirPath=imageObj.value("ImgPath").toString();

        QVector<unsigned int> idxList{};
        for(auto it:imageObj.value("ImgIdx").toArray())
        {
            idxList.append(it.toInt());
        }

        QVector<QString> imagePath{};
        for(auto it:imageObj.value("ImgList").toArray())
        {
            imagePath.append(it.toString());
        }

        qDebug()<<"check1 :"<<idxList;
        qDebug()<<"check2 :"<<imagePath;
            //----读进SourceSystem
        if(idxList.size()!=imagePath.size()) qDebug()<<"Size no same!";

        for(int i=0;i<imagePath.size();++i)
        {
            QString path=imageDirPath+"/"+imagePath[i];
            qDebug()<<"check3:"<<path;
            QPixmap* pix= new QPixmap(path);
            if(!pix->isNull())
            {
                addPixmap(idxList[i],path,pix);
            }else
            {
                qDebug()<<"ERROR: PIX isNull;";
            }
        }
    }else
    {
        qDebug()<<"ERROR:No have Image";
    }
    qDebug()<<"---SourceManager::readJsonFileToSource---end";
}

SourceMetaData *SourceManager::findSourceMetaData(unsigned int id)
{
    auto it=m_sourceMetaDataDictionary.find(id);
    if(it!=m_sourceMetaDataDictionary.end())
        return it.value();
    else
        return nullptr;
}

void SourceManager::setNowDemo(GameDemo *demo)
{
    m_nowDemo=demo;
}
