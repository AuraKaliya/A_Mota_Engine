#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <QObject>
#include "../../DATA/baseClass/systemobject.h"
#include <TOOL/managerTool/uimanager.h>
class UISystem : public SystemObject
{
    Q_OBJECT

private:
    static UISystem* m_instance;
    UIManager* m_uiManager=nullptr;
public:
    static UISystem*getInstance(QObject *parent = nullptr);
    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;
private:
    explicit UISystem(QObject *parent = nullptr);

signals:

};

#endif // UISYSTEM_H
