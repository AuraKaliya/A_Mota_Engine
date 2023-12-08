#include "instructionsystem.h"

InstructionSystem * InstructionSystem::m_instance=nullptr;
InstructionSystem *InstructionSystem::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new InstructionSystem(parent);
    }
    return m_instance;
}

bool InstructionSystem::systemStart()
{
    return true;
}

bool InstructionSystem::systemInit()
{
return true;
}

bool InstructionSystem::systemSolve()
{
return true;
}

bool InstructionSystem::systemQuit()
{
return true;
}

InstructionManager *InstructionSystem::getManager()
{
return  m_instructionManager;
}

InstructionSystem::InstructionSystem(QObject *parent)
    : SystemObject{parent}
{
m_instructionManager=InstructionManager::getInstance();
}
