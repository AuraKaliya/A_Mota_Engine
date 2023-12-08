#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include <QObject>
#include "../../DATA/baseClass/systemobject.h"
#include <TOOL/managerTool/eventmanager.h>

class EventSystem : public SystemObject
{
    Q_OBJECT

private:
    static EventSystem* m_instance;
    EventManager* m_eventManager=nullptr;
public:
    static EventSystem* getInstance(QObject * parent=nullptr);
    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;
    EventManager *getManager();
private:
    explicit EventSystem(QObject *parent = nullptr);

signals:

};

#endif // EVENTSYSTEM_H
