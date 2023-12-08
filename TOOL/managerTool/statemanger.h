#ifndef STATEMANGER_H
#define STATEMANGER_H

#include <QStateMachine>
#include <QObject>


class StateManger : public QStateMachine
{
    Q_OBJECT
public:
    explicit StateManger(QObject *parent = nullptr);
    void startSystem();
signals:
    void startAllSystem();
};

#endif // STATEMANGER_H
