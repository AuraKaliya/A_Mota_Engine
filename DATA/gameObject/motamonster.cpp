#include "motamonster.h"

MotaMonster::MotaMonster(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::NonPlayerCharacter);
    setClassName("MotaMonster");
    setSuperEdit(true);

    m_showCharacter=new ModelShowCharacter;
    m_myComponents.append(m_showCharacter);

    if(!m_registFlag)
    {
        //将处理策略注册进map中。
        //每个类进行一次初始化策略
        //m_soluteStratagies.insert("ChangeElement",changeElement);
        //已进行初始化策略
        m_registFlag=true;
    }
}

void MotaMonster::init(const QJsonObject *data)
{
    qDebug()<<"----MotaMonster::init----";
    //属性--统一读取
    unsigned int id=data->value("Id").toInt();
    setId(id);

    unsigned int type=data->value("Type").toInt();
    setType(static_cast<Type>(type));

    if(data->contains("Pos"))
    {
        double objPosX=data->value("Pos").toArray().at(0).toDouble();
        double objPosY=data->value("Pos").toArray().at(0).toDouble();
        setPosX(objPosX);
        setPosY(objPosY);
        setPosInit(true);
    }else
    {
        setPosInit(false);
    }

    unsigned int objWidth=data->value("Size").toArray().at(0).toInt();
    unsigned int objHeight=data->value("Size").toArray().at(0).toInt();
    setWidth(objWidth);
    setHeight(objHeight);

    QString pixIdList=data->value("PixIdList").toString();
    setPixIdList(pixIdList);

    QString name=data->value("Name").toString();
    setName(name);


    QString multiplePix=data->value("MultiplePix").toString();
    setPixId(multiplePix.toUInt());


    QString stateList=data->value("StateList").toString();
    QString stateIndexList=data->value("StateIndexList").toString();

    m_showCharacter->setStateList(stateList);
    m_showCharacter->setPixIndexList(stateIndexList);

    QString script=data->value("Script").toString();
    setScript(script);

    unsigned int mapId=data->value("LinkMapId").toInt();
    if(mapId)
    {
        m_linkMapId=mapId;

        emit linkMap(this);
    }
    qDebug()<<"mapId"<<m_linkMapId;
    qDebug()<<"----MotaMonster::init----end";
}

void MotaMonster::tick()
{
    qDebug()<<"---Now Show the MotaMonster's Information---";
}

void MotaMonster::solutePacketData(InsPacketData *data)
{

}

QString MotaMonster::getStateIndexList()
{
    return m_showCharacter->getPixIndexList();
}

QVector<QString> MotaMonster::getStateStrList()
{
    QVector<QString> res;
    for(auto it:m_showCharacter->getStateList().split(","))
    {
        res.append(it);
    }
    return res;
}

QString MotaMonster::getStateListStr()
{
    return m_showCharacter->getStateList();
}

void MotaMonster::changeState(QString newState)
{
    m_showCharacter->setNowState(newState);
    emit stateChanged(newState);
}

void MotaMonster::changeState(GameObject *me, QVariant v)
{
    MotaMonster* Me=static_cast<MotaMonster*>(me);

    QString newState=v.toString();
    Me->changeState(newState);
}

int MotaMonster::linkMapId() const
{
    return m_linkMapId;
}

QJsonObject MotaMonster::getItemData()
{
    QJsonObject obj;
    return obj;
}
