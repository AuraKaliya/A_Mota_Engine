#include "modeltower.h"


ModelTower::ModelTower(QObject *parent)
    : ComponentObject{parent}
{
    setObjectName("ModelTower");
}

void ModelTower::tick()
{
    qDebug()<<"---Tower Information---";
    qDebug()<<"AllLayer: "<<QString::number(m_allLayers);
    qDebug()<<"m_nowLayer: "<<QString::number(m_nowLayer);
    qDebug()<<"LinkList: " <<m_layerLinkedList;
}



unsigned int ModelTower::getNextLayerId()
{
    return m_layerLinkedList[m_nowLayer];
}

void ModelTower::setLayers(const unsigned int &layers)
{
    if(layers>=0)
    {
        m_allLayers=layers;

        m_layerLinkedList.resize(layers);
        for(int i=0;i<layers;++i)
        {
            m_layerLinkedList[i]=i+1;
        }
        m_layerLinkedList[layers-1]=0;

        m_nowLayer=0;
    }
}

void ModelTower::setNowLayer(const unsigned int &nowLayer)
{
    m_nowLayer=nowLayer;
}

void ModelTower::setLinkList(const QVector<int> &layerLinkedList)
{
    m_layerLinkedList=layerLinkedList;

}

void ModelTower::nextLayer()
{
    m_nowLayer=m_layerLinkedList[m_nowLayer];
}


unsigned int ModelTower::getAllLayers() const
{
    return m_allLayers;
}

void ModelTower::setAllLayers(unsigned int newAllLayers)
{
    qDebug()<<"---ModelTower::setAllLayers---";
    qDebug()<<"check0:"<<newAllLayers;

    if (m_allLayers == newAllLayers||newAllLayers<0)
        return;

    m_allLayers=newAllLayers;

    m_layerLinkedList.resize(newAllLayers);
    for(int i=0;i<newAllLayers;++i)
    {
        m_layerLinkedList[i]=i+1;
    }
    m_layerLinkedList[newAllLayers-1]=0;

    m_nowLayer=0;
    qDebug()<<"---ModelTower::setAllLayers---end";
    emit allLayersChanged();
}

QVector<int> ModelTower::getLayerLinkedList() const
{
    return m_layerLinkedList;
}

void ModelTower::setLayerLinkedList(const QVector<int> &newLayerLinkedList)
{
    if (m_layerLinkedList == newLayerLinkedList)
        return;
    m_layerLinkedList = newLayerLinkedList;
    emit layerLinkedListChanged();
}

unsigned int ModelTower::getNowLayer() const
{
    return m_nowLayer;
}

void ModelTower::setLinked(int layer, int linkLayer)
{
    m_layerLinkedList[layer]=linkLayer;
    emit layerLinkedListChanged();
}
