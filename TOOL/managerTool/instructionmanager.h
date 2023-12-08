#ifndef INSTRUCTIONMANAGER_H
#define INSTRUCTIONMANAGER_H

#include <QObject>
#include <DATA/baseClass/gameobject.h>
#include <DATA/baseClass/gamedemo.h>
#include <QMap>
#include <DATA/baseClass/instructionobject.h>
#include <TOOL/sourceTool/sourcesystem.h>
/*
    指令管理者，存在于指令系统中。
    1.解析指令上下文，找到指令文本对应的对象，解析指令文本中命令对应的指令对象。
    2.生成指令，由对象和指令对象获取生成的指令文本。
    3.
*/


using soluteInsFunc=void(*)(InsPacketData*);
class InstructionManager : public QObject
{
    Q_OBJECT
private:
    static QMap<QString,QVector<QPair<QString,SoluteFunc> > > m_insFunctionDictionary;
public:
    static InstructionManager* getInstance(QObject *parent=nullptr);
    GameDemo* findDemoByName(QString name);
    bool soluteInstruction(InstructionObject* insObj);
    SoluteFunc findInsFuncFromDictionary(QString catalog,QString funcName);
    static void defaultSolution(GameObject*,QVariant);
private:
    static InstructionManager* m_instance;
    explicit InstructionManager(QObject *parent = nullptr);
    static QMap<QString,GameDemo*>m_demoDictionary;

signals:

};

#endif // INSTRUCTIONMANAGER_H
