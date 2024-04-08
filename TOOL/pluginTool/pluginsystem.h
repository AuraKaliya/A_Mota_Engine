#ifndef PLUGINSYSTEM_H
#define PLUGINSYSTEM_H

#include "../../DATA/baseClass/systemobject.h"
#include <QObject>
#include "../managerTool/pluginmanager.h"



class PluginSystem : public SystemObject
{
    Q_OBJECT
public:
    static PluginSystem* getInstance(QObject *parent = nullptr);
    PluginManager* getManager();
    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;

private:
    static PluginSystem* m_instance;
    PluginManager * m_pluginManager=nullptr;
    explicit PluginSystem(QObject *parent = nullptr);
signals:

};

#endif // PLUGINSYSTEM_H
