#include "motamap.h"

#include <QMetaProperty>

MotaMap::MotaMap(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::Environment);
    setClassName("MotaMap");
    setSuperEdit(true);
    //m_map=new Model2DMap;
    m_tower=new ModelTower;
    //m_myComponents.append(m_map);
    //m_myComponents.append(new ModelTower);
    m_myComponents.append(m_tower);
    //m_myComponents.append(std::declval<Model2DMap>());
    m_myComponents.append(new Model2DMap);
    m_myComponents.append(new Model2DObjectMap);

    if(!m_registFlag)
    {
        //将处理策略注册进map中。
        //每个类进行一次初始化策略
        m_soluteStratagies.insert("ChangeElement",changeElement);

        //已进行初始化策略
        m_registFlag=true;
    }
}

void MotaMap::init(const QJsonObject *data)
{
    qDebug()<<"---init MotaMap---";
    qDebug()<<"check0:"<<data->keys();
    //属性--统一读取
    unsigned int id=data->value("Id").toInt();
    setId(id);
    unsigned int type=data->value("Type").toInt();
    //qDebug()<<"type:"<<type;
    setType(static_cast<Type>(type));
    qDebug()<<"-------------Type Read: Environment"<<(getType()==Type::Environment);
    //qDebug()<<"-------------Type Read: Environment--"<<getType();
    //qDebug()<<"-------------Type Read: Environment--"<<Type::Environment;

    //数据解析
    unsigned int mapLayer=data->value("MapLayer").toInt();  //层数
    unsigned int mapWidth=data->value("MapSize").toArray().at(0).toInt();  //网格数
    unsigned int mapHeight=data->value("MapSize").toArray().at(1).toInt();
    unsigned int mapThreshold=data->value("Threshold").toInt();

    unsigned int objWidth=data->value("Size").toArray().at(0).toInt();
    unsigned int objHeight=data->value("Size").toArray().at(0).toInt();

    if(data->contains("Pos"))
    {
        double objPosX=data->value("Pos").toArray().at(0).toDouble();
        double objPosY=data->value("Pos").toArray().at(0).toDouble();
        //objPos
        setPosX(objPosX);
        setPosY(objPosY);
        setPosInit(true);
    }else
    {
        setPosInit(false);
    }


    QString pixIdList=data->value("PixIdList").toString();
    QString name=data->value("Name").toString();


    //初始化设置
        //objSize
    setWidth(objWidth);
    setHeight(objHeight);

        //objPixList- -- --map
    setPixIdList(pixIdList);
    setName(name);

    QVector<QVector<QVector <int> > > motaMap(mapLayer,QVector<QVector <int> >(mapHeight,QVector <int> (mapWidth,0)));

    QJsonArray motaLayerMapData=data->value("MapMatrix").toArray();
    for(int i=0;i<mapLayer;++i)
    {
        QJsonArray motaHeightMapData=motaLayerMapData[i].toArray();
        for(int j=0;j<mapHeight;++j)
        {
            QJsonArray motaWidthMapData=motaHeightMapData[j].toArray();
            for(int k=0;k<mapWidth;++k)
            {
                //qDebug()<<motaWidthMapData[k].toInt();
                motaMap[i][j][k]=motaWidthMapData[k].toInt();
            }
        }
    }


    QVector<QVector<QVector <bool> > > motaValiedMap(mapLayer,QVector<QVector <bool> >(mapHeight,QVector <bool> (mapWidth,0)));

    if(!data->value("ValiedErea").isNull())
    {
        QJsonArray motaValiedLayerMapData=data->value("ValiedErea").toArray();
        for(int i=0;i<mapLayer;++i)
        {
            QJsonArray motaValiedHeightMapData=motaValiedLayerMapData[i].toArray();
            for(int j=0;j<mapHeight;++j)
            {
                QJsonArray motaValiedWidthMapData=motaValiedHeightMapData[j].toArray();
                for(int k=0;k<mapWidth;++k)
                {
                    motaValiedMap[i][j][k]=(bool)motaValiedWidthMapData[k].toInt();

                }
            }
        }
    }else
    {
        qDebug()<<"ValiedErea Null!";
    }

    qDebug()<<motaValiedMap;

    QVector<int> maplinkedList(mapLayer,0);
    if(!data->value("MapLayerLinkedList").isNull())
    {
        QJsonArray mapLinkedListData=data->value("MapLayerLinkedList").toArray();
        for(int i=0;i<mapLayer;++i)
        {
            maplinkedList[i]=mapLinkedListData[i].toInt();
        }
    }

    QVector<QVector<QVector <int> > > motaObjectMap(mapLayer,QVector<QVector <int> >(mapHeight,QVector <int> (mapWidth,0)));

    QJsonArray motaObjectLayerMapData=data->value("MapObjectMatrix").toArray();
    for(int i=0;i<mapLayer;++i)
    {
        QJsonArray motaHeightMapData=motaObjectLayerMapData[i].toArray();
        for(int j=0;j<mapHeight;++j)
        {
            QJsonArray motaWidthMapData=motaHeightMapData[j].toArray();
            for(int k=0;k<mapWidth;++k)
            {
                //qDebug()<<motaWidthMapData[k].toInt();
                motaObjectMap[i][j][k]=motaWidthMapData[k].toInt();
            }
        }
    }


    int heroId=data->value("HeroId").toInt();




    //建立地图

    m_tower->setAllLayers(mapLayer);
    if(!data->value("MapLayerLinkedList").isNull())
    {
        m_tower->setLayerLinkedList(maplinkedList);
    }


    for(int i=0;i<mapLayer;++i)
    {
        Model2DMap* tmpMap=new Model2DMap;
        Model2DObjectMap* tmpObjectMap=new Model2DObjectMap;

        qDebug()<<"--check0--"<<motaValiedMap[i];
        tmpMap->initMap(mapWidth,mapHeight,objWidth,objHeight,motaMap[i],motaValiedMap[i]);

//        connect(tmpObjectMap,&Model2DObjectMap::hasHeroChanged,this,[this](bool flag){
//            if(flag)
//            {

//            }
//        });
        tmpObjectMap->initMap(mapWidth,mapHeight,motaObjectMap[i]);
        tmpObjectMap->initHero(heroId);

        m_map.append(tmpMap);
        m_objectMap.append(tmpObjectMap);
        qDebug()<<"m_objectMap"<<motaObjectMap;

    }

    qDebug()<<"--check--:";
    for(auto it:this->getMyComponents())
        {
            bool flag=true;
            int i=0;
            while(flag)
            {
                const QMetaObject * pNew=it->metaObject();
                QMetaProperty newProperty=pNew->property(i);
                //QMetaProperty oldProperty=pOld->property(i);
                i++;
                if(newProperty.isValid())
                {
                    qDebug()<<"check0.5:"<<it<<newProperty.read(it);
                }else
                {
                    flag=false;
                }
            }

        }

    qDebug()<<"check:"<<"heroPos"<<getHeroPos();
    qDebug()<<"---init MotaMap---end";
}

void MotaMap::tick()
{
    //输出可达矩阵信息
    qDebug()<<"---Now Show the MotaMap's Information---";
    m_tower->tick();
    for(auto it :m_map) it->tick();
}

void MotaMap::solutePacketData(InsPacketData *data)
{
    //根据data中的insName选择相应的函数，根据value进行处理。
    //连锁等处理信息应该在InsManager中进行逻辑
    //这个应该放在GameObject基类中

    auto it=m_soluteStratagies.find(data->insName);
    if(it!=m_soluteStratagies.end())
    {
        //指令处理--数据包处理
        it.value()(this,data->value);
        //后续处理在manager中进行
    }
}

void MotaMap::changeElement(unsigned int layer, int x, int y, int index)
{
    //进行安全性检查：layer是否存在
    //进行处理
    m_map[layer]->setElement(x,y,index);

}

void MotaMap::changeElement(unsigned int layer, int x, int y, int index, bool valiedFlag)
{
    //进行安全性检查：layer是否存在

    //进行处理
    m_map[layer]->setElement(x,y,index);
    m_map[layer]->setElementValied(x,y,valiedFlag);

}

int MotaMap::getNowLayer()
{
    return m_tower->getNowLayer();
}

QVector<QVector<int> > MotaMap::getMap(int layer)
{
    qDebug()<<"-------MotaMap::getMap-----";
    if(layer<m_tower->getAllLayers());
    qDebug()<<"check0:"<<layer<<m_tower->getAllLayers()<<m_map;
    qDebug()<<"check1:"<<m_map[layer]->getMapMatrix();
    qDebug()<<"-------MotaMap::getMap-----end";
    return m_map[layer]->getMapMatrix();
}

QVector<QVector<bool> > MotaMap::getValiedMap(int layer)
{
    if(layer<m_tower->getAllLayers());
    return m_map[layer]->getValiedMatrix();
}

bool MotaMap::elementIsValied(int layer, int x, int y)
{
    if(layer<m_tower->getAllLayers())
    {
        return m_map[layer]->elementIsValied(x,y);
    }else
    {
        qDebug()<<"MotaMap::elementIsValied : no have a layer;(layer=0)";
    }
    return false;
}

QJsonObject MotaMap::getItemData()
{

    QJsonObject obj;

    obj.insert("Type","Map");

    QJsonObject dataObj;

    QJsonArray mapArray;
    for(int i=0;i<m_map.size();++i)
    {
        QJsonArray preLayerMap;
        QVector<QVector<int>> mapMatrix=m_map[i]->getMapMatrix();
        for(auto it:mapMatrix)
        {
            QJsonArray preRow;
            for(auto it2:it)
            {
                preRow.append(it2);
            }
            preLayerMap.append(preRow);
        }
        mapArray.append(preLayerMap);
    }
    dataObj.insert("Matrix",mapArray);

    QJsonArray pixIndex;
    QJsonArray pixSourceIndex;
    for(auto it=m_tilePixDictionary.begin();it!=m_tilePixDictionary.end();it++)
    {
        pixIndex.append(it.key());
        pixSourceIndex.append(it.value());
    }
    dataObj.insert("PixIndex",pixIndex);
    dataObj.insert("PixSourceIndex",pixSourceIndex);

    obj.insert("Data",dataObj);

    return obj;
}

void MotaMap::changeElement(GameObject *me, QVariant v)
{
    //Variant
    /*
        Vecotr[layer(int),x(int),y(int),newIndex(int)]
    */


    MotaMap* Me=static_cast<MotaMap*>(me);
    //处理数据
    QVector<QVariant> tmpList=v.toList();
    int layer=tmpList[0].toInt();
    int x=tmpList[1].toInt();
    int y=tmpList[2].toInt();
    int newIndex=tmpList[3].toInt();
    if(tmpList.size()>4)
    {
        bool valiedFlag=tmpList[4].toBool();
        Me->changeElement(layer,x,y,newIndex,valiedFlag);
    }else
    {
        Me->changeElement(layer,x,y,newIndex);
    }

}

void MotaMap::operator <<(GameObject &obj)
{
    GameObject::operator<<(obj);
    MotaMap* mObj=static_cast<MotaMap*>(&obj);

    this->m_map=mObj->m_map;
    this->m_tower=mObj->m_tower;
    this->m_tilePixDictionary=mObj->m_tilePixDictionary;
}

QPoint MotaMap::getElementPoint(int layer, int x, int y)
{
    return m_map[layer]->getElementPoint(x,y);
}

QPair<int, QPair<int, int> > MotaMap::getHeroPos()
{
    qDebug()<<"MotaMap::getHeroPos()"<<m_tower->getNowLayer()<<" --- "<<m_objectMap[m_tower->getNowLayer()]->mapMatrix();

    return QPair<int, QPair<int, int> >(m_tower->getNowLayer(),m_objectMap[m_tower->getNowLayer()]->getHeroPos());
}

QPair<int, QPair<int, int> > MotaMap::findObjectPos(int id)
{
    qDebug()<<"--- MotaMap::findObjectPos---";
    bool flag=false;
    for(int i=0;i<m_tower->getAllLayers();++i)
    {

        QPair<int, int> tmp=m_objectMap[i]->getObjectPos(id);
        if(tmp.first!=-1)
        {
            flag=true;
            qDebug()<<"--- MotaMap::findObjectPos---end--true";
            return QPair<int, QPair<int, int> >(i,tmp);
        }

    }

    if(!flag)
    {
         qDebug()<<"--- MotaMap::findObjectPos---end--false";
    }

    return QPair<int, QPair<int, int> >(-1,QPair<int, int> ());
}

void MotaMap::objectMove(int layer, int oldX, int oldY, int newX, int newY)
{
    m_objectMap[layer]->objectMove(oldX,oldY,newX,newY);
}





