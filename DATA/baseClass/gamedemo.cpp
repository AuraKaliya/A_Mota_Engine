#include "gamedemo.h"

GameDemo::GameDemo(QObject *parent)
    : QObject{parent}
{

}

QVector<GameObject *> GameDemo::getElement()
{
    QVector<GameObject * >tmp;
    for(auto it:qAsConst(m_element))
    {
        tmp.append(it.second);
    }

    for(auto it:qAsConst(m_elementList))
    {
        for(auto it2:it)
        {
            tmp.append(it2);
        }
    }
    return tmp;
}
