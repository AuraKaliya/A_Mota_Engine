#ifndef COMPONENTOBJECT_H
#define COMPONENTOBJECT_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <TOOL/template/Registor.hpp>

class GameObject;
class ComponentObject : public QObject
{
    Q_OBJECT

public:
    explicit ComponentObject(QObject *parent = nullptr);
    //virtual void initProperty(QJsonObject jsonObj);
    //virtual QJsonObject getProperty();
    virtual void tick();
    virtual void bindToGameObject(GameObject* go);

    virtual bool waitForSignal(QObject* obj,const char * signal,const unsigned int ms=3000);


signals:

};

#endif // COMPONENTOBJECT_H
