#include "motahero.h"

MotaHero::MotaHero(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::PlayerCharacter);
    setClassName("MotaHero");
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

void MotaHero::init(const QJsonObject *data)
{
    qDebug()<<"----MotaHero::init----";
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
        emit linkMap();
    }

    qDebug()<<"mapId"<<m_linkMapId;
    qDebug()<<"----MotaHero::init----end";
}

void MotaHero::tick()
{
    qDebug()<<"---Now Show the MotaHero's Information---";

    m_showCharacter->tick();

}

void MotaHero::solutePacketData(InsPacketData *data)
{

}

QJsonObject MotaHero::getItemData()
{
    QJsonObject obj;
    return obj;
}

QString MotaHero::getStateIndexList()
{
    return m_showCharacter->getPixIndexList();
}

QVector<QString> MotaHero::getStateStrList()
{
    QVector<QString> res;
    for(auto it:m_showCharacter->getStateList().split(","))
    {
        res.append(it);
    }
    return res;
}

QString MotaHero::getStateListStr()
{
     return m_showCharacter->getStateList();
}

void MotaHero::changeState(QString newState)
{
    m_showCharacter->setNowState(newState);
    emit stateChanged(newState);
}

void MotaHero::changeState(GameObject *me, QVariant v)
{
    MotaHero* Me=static_cast<MotaHero*>(me);

    QString newState=v.toString();
    Me->changeState(newState);

}

int MotaHero::linkMapId() const
{
    return m_linkMapId;
}
