#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <QObject>
#include "lua.hpp"
#include <DATA/constvalue.h>
#include <DATA/baseClass/script.h>
#include <TOOL/sourceTool/sourcesystem.h>
#include <TOOL/instructionTool/instructionsystem.h>
#include <QTimer>

/*
    1.每个item绑定的script都是一个lua虚拟机
    2.在生成时进行统一的初始化--注册函数
    3.在tick时直接调用
*/




class ScriptManager : public QObject
{
    Q_OBJECT
public:
    enum class Type{
        String,Int,UInt,Double,Error
    };
private:
    static  ScriptManager* m_instance;
    static  lua_State* m_luaState;  //整体的总state
    static  QVector<Script*> m_scriptList;
    static QMap<unsigned int,QString> m_itemToScriptFileNameDictionary;
    static QMap<unsigned int,Script*> m_itemToScriptDictionary;
    QTimer * m_updater=nullptr;
public:
    static int readKeyState(lua_State* state);
    static int setItemState(lua_State* state);
    static int setObjectState(lua_State* state);
    static int getObjectState(lua_State*state);
    static int soluteInstruction(lua_State*state);

    static ScriptManager::Type getPropertyType(QMetaProperty p);
public:
    static ScriptManager*getInstance(QObject*parent=nullptr);
    static void addScript(GameObjectItem* item, QString fileName);
    static void addScript(Script* script);
    static void delScriptFromItem(GameObjectItem* item);
    static void registerFunc(lua_State* lua);
    static void registerItemToScriptFile(unsigned int ,QString);
    static void registerItemToScript(unsigned int,Script*);
    static QString getScriptFileNameByItemId(unsigned int);
    static Script* getScirptByItemId(unsigned int);
    void initEnvironment();

private:
    explicit ScriptManager(QObject *parent = nullptr);

    void initEngineToLua();
signals:

};

#endif // SCRIPTMANAGER_H
