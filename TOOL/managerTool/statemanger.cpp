#include "statemanger.h"

StateManger::StateManger(QObject *parent)
    : QStateMachine{parent}
{

}

void StateManger::startSystem()
{
#if 0
    qDebug()<<"emit starAllSystem";
#endif
    emit startAllSystem();
}
