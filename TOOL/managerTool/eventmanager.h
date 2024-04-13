#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>

#include <TOOL/instructionTool/instructionsystem.h>


/*
    1.事件管理者提供对事件的统一管理。
    一个Map-->事件名String-触发的指令集Vector<Ins*>;
    触发时根据该Ins复制一份传递给指令处理系统进行处理。
    2.删除事件、添加事件、查询事件、事件发生、返回事件列表。
    3.连通各系统，获取系统提供的可调函数--已注册可反射的函数，生成数据包和相应的控制信息，传递给指令系统，指令系统进行处理。
    4.获取资源系统中，GameObject注册过的指令。
    5.对输入的值进行转换为统一数据格式，Varint
    6.添加事件触发绑定的指令后，提供给Script系统一个接口，可在脚本中进行事件触发。EventTrigger(String);
    事件是预定义好的触发指令的集合，在需要动态触发的情况使用指令系统进行描述。
*/

class EventManager : public QObject
{
    Q_OBJECT

private:
    static EventManager* m_instance;
    static QMap<QString,QVector<InstructionObject*> > m_eventToInsDictionary;

public:
    static EventManager* getInstance(QObject *parent = nullptr);

    QVector<QString> getEventList();
    QVector<InstructionObject*> getInsByEvent(QString event);
    bool addEvent(QString event);
    bool delEvent(QString event);
    bool addInsToEvent(QString event,InstructionObject*ins);
    static void eventTrigger(QString event);

private:
    explicit EventManager(QObject *parent = nullptr);

signals:

};

#endif // EVENTMANAGER_H
