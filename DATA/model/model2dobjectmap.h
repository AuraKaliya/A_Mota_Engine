#ifndef MODEL2DOBJECTMAP_H
#define MODEL2DOBJECTMAP_H

#include <QObject>
#include <QObject>
#include <QPoint>
#include <QVector>
#include <QEventLoop>
#include <QTimer>

#include "../baseClass/componentobject.h"

class Model2DObjectMap : public ComponentObject
{
    Q_OBJECT

    Q_PROPERTY(int mapWidth READ getMapWidth WRITE setMapWidth NOTIFY mapWidthChanged)
    Q_PROPERTY(int mapHeight READ getMapHeight WRITE setMapHeight NOTIFY mapHeightChanged)
    Q_PROPERTY(bool hasHero READ hasHero WRITE setHasHero NOTIFY hasHeroChanged)

public:

    explicit Model2DObjectMap(QObject *parent = nullptr);
    void tick()override;

    void initMap(int w,int h,QVector<QVector <int> >mapMatrix);
    void initHero(int heroId);
    QPair<int,int> getHeroPos();
    QPair<int,int>getObjectPos(int id);
    void objectMove(int oldX,int oldY,int newX,int newY);

    int getMapWidth() const;
    void setMapWidth(int newMapWidth);

    int getMapHeight() const;
    void setMapHeight(int newMapHeight);

    bool hasHero() const;
    void setHasHero(bool newHasHero);

    QVector<QVector<int> > mapMatrix() const;




signals:

    void mapWidthChanged();
    void mapHeightChanged();
    void hasHeroChanged(bool);
    void ObjectMove(int ,int ,int);
    void ObjectOverLap(int,int,int,int);

private:
    QVector<QVector <int> > m_mapMatrix;
    int m_heroPosX;
    int m_heroPosY;
    int m_heroId;
    int m_mapWidth;
    int m_mapHeight;
    bool m_hasHero;

    bool m_initFlag=false;

    QObject* m_signalLinkObj=nullptr;
};

REGISTER_OBJECT(Model2DObjectMap,ComponentObject)
#endif // MODEL2DOBJECTMAP_H
