#include "scriptmanager.h"
#include "qmetaobject.h"

ScriptManager* ScriptManager::m_instance=nullptr;
lua_State* ScriptManager::m_luaState=nullptr;
QVector<Script*> ScriptManager::m_scriptList={};
QMap<unsigned int,QString> ScriptManager::m_itemToScriptFileNameDictionary{};
QMap<unsigned int,Script*>ScriptManager::m_itemToScriptDictionary{};
int ScriptManager::readKeyState(lua_State *state)
{
    //Key状态获取函数

    GlobalKeyValue keyValue;
    const char* key=lua_tostring(state,-1);
    bool flag=keyValue.getKeyPressedState(key);
    lua_pushboolean(state,flag);
    return 1;
}

int ScriptManager::setItemState(lua_State *state)
{
    //Item状态设置函数
    /*
     * 1.获取希望操作的函数--item属性
     * 2.获取传入的参数值
     * 3.进行操作
    */

    QString propertyName=lua_tostring(state,-1);
    return 0;
}

int ScriptManager::setObjectState(lua_State *state)
{
    //参数： id  proname
    qDebug()<<"--ScriptManager::setObjectState--";
    unsigned int objectId=lua_tonumber(state,-3);
    const char* propertyName=lua_tostring(state,-2);
    qDebug()<<"check0:"<<objectId<<propertyName;
    GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(objectId);

    if(obj!=nullptr)
    {

        qDebug()<<"check1:"<<obj->getScript()<<obj->getNowState();
        const QMetaObject* metaObj=obj->metaObject();
        int index= metaObj->indexOfProperty(propertyName);
        //根据index获取对应属性，并返回属性的类型

        if(index!=-1)
        {
            //QVariant var;
            QMetaProperty property=metaObj->property(index);

            switch (getPropertyType(property)) {
            case Type::Int:
                property.write(obj,QVariant(lua_tonumber(state,-1)));
                break;
            case Type::String:
                property.write(obj,QVariant(lua_tostring(state,-1)));
                break;
            case Type::UInt:
                property.write(obj,QVariant(lua_tonumber(state,-1)));
                break;
            case Type::Double:
                //qDebug()<<"Double!~~~~~~~~~~~~~~~~~~~~~~~2222222222~~~~~~~~~~~~~";
                property.write(obj,QVariant(lua_tonumber(state,-1)));
                break;
            case Type::Error:
            default:
                qDebug()<<"No have this propertyType!";
                break;
            }
        }
        else
        {
          qDebug()<<"No have this property!";
        }
    }
    return 0;
}

int ScriptManager::getObjectState(lua_State *state)
{
    //参数： id  proname
    unsigned int objectId=lua_tonumber(state,-2);
    const char* propertyName=lua_tostring(state,-1);

    //qDebug()<<"getObjectState!!!!!!!!---c++-----  objID:"<<objectId<<" propertyname:"<<propertyName;

    GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(objectId);
    if(obj!=nullptr)
    {
        const QMetaObject* metaObj=obj->metaObject();
        int index= metaObj->indexOfProperty(propertyName);
        //根据index获取对应属性，并返回属性的类型
        if(index!=-1)
        {
          //QVariant var;
          QMetaProperty property=metaObj->property(index);
          switch (getPropertyType(property)) {
          case Type::Int:
                lua_pushinteger(state,property.read(obj).toInt());

                break;
          case Type::String:
                lua_pushstring(state,property.read(obj).toString().toStdString().c_str());
                break;
          case Type::UInt:
                lua_pushinteger(state,property.read(obj).toUInt());
                break;
          case Type::Double:
                //qDebug()<<"Double!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                lua_pushinteger(state,property.read(obj).toDouble());
                break;
          case Type::Error:
          default:
                qDebug()<<"No have this propertyType!";
                break;
          }
        }
        else
        {
          qDebug()<<"No have this property!";
        }
    }
    return 1;
}

int ScriptManager::soluteInstruction(lua_State *state)
{
    //获取参数  --
    /*
        1-id
        2-insName
        3-insType ---Object/Demo
        ...具体的参数
        -1：具体参数个数(一个参数填1) （从4开始计算  for int i=4;i<n+4;i++）
        这是为tick服务的，tick是与GO绑定的，所以需要有ObjectId；（哪怕是Demo和System指令）
    */
    qDebug()<<"---ScriptManager::soluteInstruction---";
    unsigned int objectId=lua_tonumber(state,1);
    const char* insName=lua_tostring(state,2);
    const char* insType=lua_tostring(state,3);
    int n=lua_tonumber(state,-1);



    QVector<QVariant> list;
    for(int i=4;i<n+4;++i)
    {
        list.append(QVariant(lua_tostring(state,i)));
    }

    qDebug()<<"Check:"<<objectId<<insName<<insType<<list<<n;


    GameObject* obj=SourceSystem::getInstance()->getManager()->getObjectById(objectId);
    if(obj!=nullptr)
    {
        InstructionObject* insObj=new InstructionObject;
        InstructionContext insContext;
        insContext.insModel="Ins_";
        insContext.insModel+=insType;
        InsPacketData data;
        data.insName=insName;
        data.ObjectIndex=objectId;
        data.value=QVariant(list);
        data.insIndex=insContext.insPacket.size();
        insContext.insPacket.append(data);
        insObj->setInsContext(insContext);
        InstructionSystem::getInstance()->getManager()->soluteInstruction(insObj);
    }else
    {
        qDebug()<<"ScriptManager::soluteInstruction:NO HAVE THIS OBJECT";
    }

    return 0;
}


ScriptManager::Type ScriptManager::getPropertyType(QMetaProperty p)
{
    if(!p.isValid()) return Type::Error;

    //可以写成Dictionary的形式
    if(strcmp(p.typeName(),"QString")==0) return Type::String;
    if(strcmp(p.typeName(),"int")==0) return Type::Int;
    if(strcmp(p.typeName(),"uint")==0) return Type::UInt;
    if(strcmp(p.typeName(),"double")==0) return Type::Double;

    return Type::Error;
}

ScriptManager *ScriptManager::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new ScriptManager(parent);
    }
    return m_instance;
}

void ScriptManager::addScript(GameObjectItem *item, QString fileName)
{
    Script *script=new Script(fileName,item->getLinkObj(),item);
    addScript(script);

    //注册绑定item和script
    registerItemToScriptFile(item->getId(),fileName);
    registerItemToScript(item->getId(),script);
}

void ScriptManager::addScript(Script *script)
{
    lua_State* lua=luaL_newstate();
    script->m_lua=lua;
    luaL_openlibs(lua);
    qDebug()<<"filename: "<<script->m_fileName.toStdString().c_str();
    luaL_dofile(lua,script->m_fileName.toStdString().c_str());

    qDebug()<<"addScript!";
    lua_getglobal(lua,"testname");
    qDebug()<<"testName: "<<lua_tostring(lua,-1);


    //注册函数
    registerFunc(lua);
    //初始化脚本参数
    lua_getglobal(lua,"init");
    lua_pushnumber(lua,script->m_item->getId());
    lua_pushnumber(lua,script->m_obj->getId());
    lua_pcall(lua, 2, 0, 0);

    m_scriptList.append(script);


}

void ScriptManager::delScriptFromItem(GameObjectItem *item)
{
    Script* script=getScirptByItemId(item->getId());
    //qDebug()<<"###############################"<<script;
    //qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<m_scriptList;

    if(script!=nullptr)
    {
        qDebug()<<"ScriptManager::delScriptFromItem!~~~~~~~~~~~~~~~";
        bool flag=m_scriptList.removeOne(script);
        qDebug()<<"flag:"<<flag;

        //！！！！！！！！！！！！！！
        //此处需要去实现script的析构函数
        //！！！！！！！！！！！！！！

        delete script;
        script=nullptr;
    }
    else
    {
        qDebug()<<"ScriptManager::delScriptFromItem : no have this items script!";
    }



}

void ScriptManager::registerFunc(lua_State *lua)
{
    //注册Key状态获取函数   --这个可以每个都注册一个
    lua_register(lua,"readKeyState",readKeyState);

    //注册object管理函数
    lua_register(lua,"setObjectState",setObjectState);
    lua_register(lua,"getObjectState",getObjectState);

    //注册item管理函数
    lua_register(lua,"soluteInstruction",soluteInstruction);
    //注册指令函数


}

void ScriptManager::registerItemToScriptFile(unsigned int id, QString fileName)
{
    m_itemToScriptFileNameDictionary[id]=fileName;
    qDebug()<<"registerItemToScriptFile"<<id<< "  "<<fileName;
}

void ScriptManager::registerItemToScript(unsigned int id, Script *script)
{
    m_itemToScriptDictionary[id]=script;
    qDebug()<<"registerItemToScript";
}

QString ScriptManager::getScriptFileNameByItemId(unsigned int id)
{
    auto it=m_itemToScriptFileNameDictionary.find(id);
    if (it!=m_itemToScriptFileNameDictionary.end())
    {
        return it.value();
    }
    else
    {
        qDebug()<<"ScriptManager::getScriptFileNameByItemId: No have this id-File";
        return "";
    }
}

Script *ScriptManager::getScirptByItemId(unsigned int id )
{
    auto it=m_itemToScriptDictionary.find(id);
    if (it!=m_itemToScriptDictionary.end())
    {
        return it.value();
    }
    else
    {
        qDebug()<<"id:"<<id;
        qDebug()<<"ScriptManager::getScirptByItemId: No have this id-File";
        return nullptr;
    }

}

void ScriptManager::initEnvironment()
{

}

ScriptManager::ScriptManager(QObject *parent)
    : QObject{parent}
{
    m_luaState=luaL_newstate();
    luaL_openlibs(m_luaState);

    m_updater=new QTimer(this);

    m_updater->setInterval(30);
    connect(m_updater,&QTimer::timeout,this,[this](){
        for(auto it:m_scriptList)
        {
            lua_State * lua=it->m_lua;
            lua_getglobal(lua,"tick");
            lua_pcall(lua,0,0,0);
            //qDebug()<<"tick! by timeOut";
        }
        //qDebug()<<"tick!!!!!!!!";
    });

    m_updater->start();



    //test
    QVariant var1("1");
    QVariant var2("1.5");
    QVariant var3("s");
    qDebug()<<"test var1:  "<<var1.toString()<<var1.toInt()<<var1.toUInt()<<var1.toDouble();
    qDebug()<<"test var2:  "<<var2.toString()<<var2.toInt()<<var2.toUInt()<<var2.toDouble();
    qDebug()<<"test var3:  "<<var3.toString()<<var3.toInt()<<var3.toUInt()<<var3.toDouble();
    //test



}

void ScriptManager::initEngineToLua()
{
    luaL_dofile(m_luaState,":/RESOURCE/setting/engine.lua");
//基于程序中的变量对该lua文件进行初始化

//将程序中的函数向该lua文件进行注册
    registerFunc(m_luaState);

}
