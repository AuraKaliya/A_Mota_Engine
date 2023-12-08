#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H
#include "../../DATA/baseClass/systemobject.h"
#include"../managerTool/scriptmanager.h"
#include <QObject>

class ScriptSystem : public SystemObject
{
    Q_OBJECT
public:
    static ScriptSystem* getInstance(QObject* parent=nullptr);
    ScriptManager* getManager();

    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;
private:
    explicit ScriptSystem(QObject *parent = nullptr);
    static ScriptSystem* m_instance;
    ScriptManager* m_scriptManager=nullptr;
signals:

};

#endif // SCRIPTSYSTEM_H
