#ifndef MODELTOWER_H
#define MODELTOWER_H

#include <QObject>
#include "../baseClass/componentobject.h"

class ModelTower : public ComponentObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int allLayers READ getAllLayers WRITE setAllLayers NOTIFY allLayersChanged)
    Q_PROPERTY(unsigned int nowLayer READ getNowLayer WRITE setNowLayer NOTIFY nowLayerChanged)

private:
    unsigned int m_allLayers;
    unsigned int m_nowLayer;
    QVector<int> m_layerLinkedList;

public:
    explicit ModelTower(QObject *parent = nullptr);

    void tick() override;

    unsigned int getNextLayerId();

    void setLayers( const unsigned int& layers);
    void setNowLayer(const unsigned int& nowLayer);
    void setLinkList(const QVector<int>& layerLinkedList);
    void nextLayer();


    unsigned int getAllLayers() const;
    void setAllLayers(unsigned int newAllLayers);

    QVector<int> getLayerLinkedList() const;
    void setLayerLinkedList(const QVector<int> &newLayerLinkedList);

    unsigned int getNowLayer() const;

    void setLinked(int layer,int linkLayer);

signals:

    void allLayersChanged();
    void layerLinkedListChanged();
    void nowLayerChanged();
};
REGISTER_OBJECT(ModelTower,ComponentObject)
#endif // MODELTOWER_H
