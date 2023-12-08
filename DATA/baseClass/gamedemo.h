#ifndef GAMEDEMO_H
#define GAMEDEMO_H

#include <QObject>
#include <QMap>
#include "gameobject.h"

class GameDemo : public QObject
{
    Q_OBJECT
public:
    explicit GameDemo(QObject *parent = nullptr);
    virtual void init(const QJsonObject* obj)=0;
    virtual QVector<GameObject*> getElement();
    virtual void registToManager()=0;
    //virtual void insRecv(InstructionContext* insContext)=0;
    //virtual void dataSend()=0;

protected:
    QMap<QString,QPair<QString,GameObject*> > m_element;
    QMap<QString,QVector<GameObject*> > m_elementList;
signals:
    void objectCreated(GameObject*);
    void objectCreatedFromFile(GameObject*,unsigned int id);
    void objectRegistToManager(GameObject*,QString);
    void demoFuncRegistToManager(SoluteFunc,QString);
};


//#define REGISTERTODEMO()

#endif // GAMEDEMO_H
