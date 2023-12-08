#include "model2dobjectmap.h"

Model2DObjectMap::Model2DObjectMap(QObject *parent)
    : ComponentObject{parent}
{
    setObjectName("Model2DObjectMap");
}

void Model2DObjectMap::tick()
{

}

void Model2DObjectMap::initMap(int w, int h, QVector<QVector<int> > mapMatrix)
{
    setMapWidth(w);
    setMapHeight(h);
    m_mapMatrix=mapMatrix;

    m_initFlag=true;
}

void Model2DObjectMap::initHero(int heroId)
{
    m_heroId=heroId;

    auto it=getHeroPos();
    if(it.first!=-1)
    {
        setHasHero(true);
    }
    else
    {
        setHasHero(false);
    }
}

QPair<int, int> Model2DObjectMap::getHeroPos()
{
    m_heroPosX=-1;
    m_heroPosY=-1;
    bool flag=false;
    for(int i=0;i<m_mapMatrix.size();++i)
    {

        for(int j=0;j<m_mapMatrix[i].size();++j)
        {
            if(m_mapMatrix[i][j]==m_heroId)
            {
                m_heroPosX=j;
                m_heroPosY=i;
                flag=true;
                break;
            }
        }
        if(flag)
        {

            break;
        }
    }

    if(!flag)
    {
        qDebug() << "No Find Hero";
    }


    return QPair<int,int>(m_heroPosX,m_heroPosY);
}

QPair<int, int> Model2DObjectMap::getObjectPos(int id)
{
    bool flag=false;
    for(int i=0;i<m_mapMatrix.size();++i)
    {
        for(int j=0;j<m_mapMatrix[i].size();++j)
        {
            if(m_mapMatrix[i][j]==id)
            {
                flag=true;
                return QPair<int, int>(j,i);
            }
        }
    }

    if(!flag)
    {
        qDebug()<<"Model2DObjectMap::getObjectPos: no find this id";
    }
     return QPair<int, int>(-1,-1);
}

void Model2DObjectMap::objectMove(int oldX, int oldY, int newX, int newY)
{
    //！warning！
    //缺少安全性检查
    int obj1Id=m_mapMatrix[oldY][oldX];
    if(obj1Id!=0)
    {
        m_mapMatrix[oldY][oldX]=0;
    }else
    {
        qDebug()<<"Model2DObjectMap::objectMove : NO HAVE OBJECT";
        qDebug()<<"m_mapMatrix"<<m_mapMatrix;
        qDebug()<<"xy:"<<oldX<<oldY;
        return;
    }

    int obj2Id=m_mapMatrix[newY][newX];
    if(obj2Id==0){
        m_mapMatrix[newY][newX]=obj1Id;
        emit ObjectMove(obj1Id,newX,newY);
    }
    else
    {
        emit ObjectOverLap(obj1Id,obj2Id,newX,newY);
        if(m_signalLinkObj!=nullptr)
        {
            //等待处理完成的信号
            waitForSignal(m_signalLinkObj,SIGNAL(overLapSolved()),1000);
        }
        else
        {
            qDebug()<<"ObjectOverLap! but no have link solve Object!";
        }
    }

}

int Model2DObjectMap::getMapWidth() const
{
    return m_mapWidth;
}

void Model2DObjectMap::setMapWidth(int newMapWidth)
{
    if (m_mapWidth == newMapWidth)
        return;
    m_mapWidth = newMapWidth;
    emit mapWidthChanged();
}

int Model2DObjectMap::getMapHeight() const
{
    return m_mapHeight;
}

void Model2DObjectMap::setMapHeight(int newMapHeight)
{
    if (m_mapHeight == newMapHeight)
        return;
    m_mapHeight = newMapHeight;
    emit mapHeightChanged();
}

bool Model2DObjectMap::hasHero() const
{
    return m_hasHero;
}

void Model2DObjectMap::setHasHero(bool newHasHero)
{
    if (m_hasHero == newHasHero)
        return;
    m_hasHero = newHasHero;
    emit hasHeroChanged(m_hasHero);
}

QVector<QVector<int> > Model2DObjectMap::mapMatrix() const
{
    return m_mapMatrix;
}
