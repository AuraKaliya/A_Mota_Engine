#ifndef INSTRUCTIONSYSTEM_H
#define INSTRUCTIONSYSTEM_H

#include <QObject>
#include "../../DATA/baseClass/systemobject.h"
#include <TOOL/managerTool/instructionmanager.h>

class InstructionSystem : public SystemObject
{
    Q_OBJECT

private:
    static InstructionSystem * m_instance;
    InstructionManager* m_instructionManager=nullptr;

public:
    static InstructionSystem* getInstance(QObject *parent = nullptr);
    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;
    InstructionManager*getManager();

private:
     explicit InstructionSystem(QObject *parent = nullptr);
signals:

};

#endif // INSTRUCTIONSYSTEM_H
