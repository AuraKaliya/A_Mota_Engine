#include "motademo.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
MotaDemo* MotaDemo::m_instance=nullptr;
MotaDemo::MotaDemo(QObject *parent)
    : GameDemo{parent}
{

    //固有/静态/唯一性的GameObject的初始化
    /*
        1. 初始化
        2. 将GO注册进SourceManager中
    */
    //1. 初始化
    m_motaMap=new MotaMap;
    m_motaHero=new MotaHero;


    //2. 注册  --在统一注册中，根据init的结果进行处理（通过文件创建/进行新建）
    m_element.insert("MotaMap",QPair<QString,GameObject*>("MotaMap",m_motaMap));
    m_element.insert("MotaHero",QPair<QString,GameObject*>("MotaHero",m_motaHero));
    //m_element.insert("MotaMonster",QPair<QString,GameObject*>("MotaMonster",m_motaMonster));
    m_elementList.insert("MotaMonster",*new QVector<GameObject*>());

    //异步初始化处理
    //link--绑定Hero和Map
    connect(m_motaHero,&MotaHero::linkMap,this,[this](){

        QPair<int,QPair<int,int>> heroPos=m_motaMap->getHeroPos();

        QPoint p=m_motaMap->getElementPoint(heroPos.first,heroPos.second.first,heroPos.second.second);
        int posX=p.x();
        int posY=p.y();
        m_motaHero->setPosX(posX);
        m_motaHero->setPosY(posY);
        m_motaHero->setPosInit(true);
    });




}

void MotaDemo::heroMoveToNextElement(GameObject *hero, QVariant v)
{
    //Variant
    /*
        vector[direction(int)]
    */
    //MotaHero* Hero=static_cast<MotaHero*>(hero);
    qDebug()<<"---MotaDemo::heroMoveToNextElement---";
    MotaHero* Hero=m_instance->m_motaHero;

    //获取当前的地图坐标
    QPair<int,QPair<int,int>> heroPos=m_instance->m_motaMap->getHeroPos();
    qDebug()<<"heroPos:"<<heroPos;

    int nowLayer=heroPos.first;
    qDebug()<<"ValiedMap"<<m_instance->m_motaMap->getValiedMap(nowLayer);
    int nowX=heroPos.second.first;
    int nowY=heroPos.second.second;
    int nextX=nowX;
    int nextY=nowY;
    QVector<QVariant> tmpList=v.toList();

    //获取方向
    int direction=tmpList[0].toInt();
    //  0: 不动 1右 2上 3左 4下
    //处理
    switch (direction) {
    case 1:
    {
        nextX+=1;
    }
        break;
    case 2:
        nextY-=1;
        break;
    case 3:
        nextX-=1;
        break;
    case 4:
        nextY+=1;
        break;
    case 0:
    default:
        qDebug()<<"No Active!";
        return;
    }

    qDebug()<<"NextPos:"<<nextX<<nextY <<m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY);
    //判断是否可行
    if(m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY))
    {
        // 可行，item移动 -- obj的属性改变；
        QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
        QPropertyAnimation * animationX=new QPropertyAnimation(Hero,"posX");
        QPropertyAnimation * animationY=new QPropertyAnimation(Hero,"posY");

        animationGroup->addAnimation(animationX);
        animationGroup->addAnimation(animationY);

        animationX->setDuration(200);
        animationY->setDuration(200);

        animationX->setStartValue(Hero->getPosX());
        animationY->setStartValue(Hero->getPosY());

        QPoint p=m_instance->m_motaMap->getElementPoint(nowLayer,nextX,nextY);
        animationX->setEndValue((double)p.x());
        animationY->setEndValue((double)p.y());

        connect(animationGroup,&QParallelAnimationGroup::finished,m_instance,[=](){
            qDebug()<<"QParallelAnimationGroup::finished";
            qDebug()<<nowLayer<<nowX<<nowY<<nextX<<nextY;
            m_instance->m_motaMap->objectMove(nowLayer,nowX,nowY,nextX,nextY);
             qDebug()<<"QParallelAnimationGroup::finished   ---end";
        });
        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
    }









//    //QVector<QVariant> tmpList=v.toList();
//    int x=tmpList[0].toInt();
//    int y=tmpList[1].toInt();
//    int layer=m_instance->m_motaMap->getNowLayer();
//    if(m_instance->m_motaMap->elementIsValied(layer,x,y))
//    {
//        // 可行，item移动 -- obj的属性改变；
//        QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
//        QPropertyAnimation * animationX=new QPropertyAnimation(Hero,"posX");
//        QPropertyAnimation * animationY=new QPropertyAnimation(Hero,"posY");

//        animationGroup->addAnimation(animationX);
//        animationGroup->addAnimation(animationY);

//        animationX->setDuration(200);
//        animationY->setDuration(200);

//        animationX->setStartValue(Hero->getPosX());
//        animationY->setStartValue(Hero->getPosY());

//        QPoint p=m_instance->m_motaMap->getElementPoint(layer,x,y);
//        animationX->setEndValue((double)p.x());
//        animationY->setEndValue((double)p.y());

//        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
//    }

}

void MotaDemo::monsterMoveToNextElement(GameObject *monster, QVariant v)
{
    //Variant
    /*
        vector[direction(int)]
    */
    //MotaHero* Hero=static_cast<MotaHero*>(hero);
    qDebug()<<"---MotaDemo::heroMoveToNextElement---";
    MotaMonster* Monster=static_cast<MotaMonster*>(monster);

    //获取当前的地图坐标
    QPair<int,QPair<int,int>> monsterPos=m_instance->m_motaMap->findObjectPos(Monster->getId());
    qDebug()<<"heroPos:"<<monsterPos;

    int nowLayer=monsterPos.first;
    qDebug()<<"ValiedMap"<<m_instance->m_motaMap->getValiedMap(nowLayer);
    int nowX=monsterPos.second.first;
    int nowY=monsterPos.second.second;
    int nextX=nowX;
    int nextY=nowY;
    QVector<QVariant> tmpList=v.toList();

    //获取方向
    int direction=tmpList[0].toInt();
    //  0: 不动 1右 2上 3左 4下
    //处理
    switch (direction) {
    case 1:
    {
        nextX+=1;
    }
    break;
    case 2:
        nextY-=1;
        break;
    case 3:
        nextX-=1;
        break;
    case 4:
        nextY+=1;
        break;
    case 0:
    default:
        qDebug()<<"No Active!";
        return;
    }

    qDebug()<<"NextPos:"<<nextX<<nextY <<m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY);
    //判断是否可行
    if(m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY))
    {
        // 可行，item移动 -- obj的属性改变；
        QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
        QPropertyAnimation * animationX=new QPropertyAnimation(Monster,"posX");
        QPropertyAnimation * animationY=new QPropertyAnimation(Monster,"posY");

        animationGroup->addAnimation(animationX);
        animationGroup->addAnimation(animationY);

        animationX->setDuration(200);
        animationY->setDuration(200);

        animationX->setStartValue(Monster->getPosX());
        animationY->setStartValue(Monster->getPosY());

        QPoint p=m_instance->m_motaMap->getElementPoint(nowLayer,nextX,nextY);
        animationX->setEndValue((double)p.x());
        animationY->setEndValue((double)p.y());

        connect(animationGroup,&QParallelAnimationGroup::finished,m_instance,[=](){
            qDebug()<<"QParallelAnimationGroup::finished";
            qDebug()<<nowLayer<<nowX<<nowY<<nextX<<nextY;
            m_instance->m_motaMap->objectMove(nowLayer,nowX,nowY,nextX,nextY);
            qDebug()<<"QParallelAnimationGroup::finished   ---end";
        });
        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MotaDemo::heroMoveToElement(GameObject *hero, QVariant v)
{
    //Variant
    /*
        vector[x(int),y(int)]
    */
    MotaHero* Hero=m_instance->m_motaHero;
    QVector<QVariant> tmpList=v.toList();
    int x=tmpList[0].toInt();
    int y=tmpList[1].toInt();
    int layer=m_instance->m_motaMap->getNowLayer();
    if(m_instance->m_motaMap->elementIsValied(layer,x,y))
    {
        // 可行，item移动 -- obj的属性改变；
        QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
        QPropertyAnimation * animationX=new QPropertyAnimation(Hero,"posX");
        QPropertyAnimation * animationY=new QPropertyAnimation(Hero,"posY");

        animationGroup->addAnimation(animationX);
        animationGroup->addAnimation(animationY);

        animationX->setDuration(200);
        animationY->setDuration(200);

        animationX->setStartValue(Hero->getPosX());
        animationY->setStartValue(Hero->getPosY());

        QPoint p=m_instance->m_motaMap->getElementPoint(layer,x,y);
        animationX->setEndValue((double)p.x());
        animationY->setEndValue((double)p.y());

        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
    }



}

MotaDemo *MotaDemo::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance=new MotaDemo;
    }
    return m_instance;
}

void MotaDemo::init(const QJsonObject *obj)
{

    QJsonObject data =obj->value("Data").toObject();

    for(auto it:data.value("PacketList").toArray())
    {
        QString packetName=it.toString();
        qDebug()<<"MotaDemo::init"<<packetName;
        QJsonObject tmp=data.value(packetName).toObject();
        if(m_element.find(packetName)!=m_element.end())
        {
            m_element[packetName].second->init(&tmp);
        }
        else if(tmp.contains("List"))
        {
            for(auto item:tmp.value("List").toArray())
            {
                GameObject* obj=Factory<GameObject>::GetInstance()->CreateObject(packetName);
                qDebug()<<"item"<<item.toVariant()<<"\n\n"<<item.isObject()<<item.toObject();
                QJsonObject tmp2=item.toObject();

                //得想办法把obj给加入到List中
                if(obj->getClassName()=="MotaMonster")
                {
                    MotaMonster* monster=static_cast<MotaMonster*>(obj);
                    m_motaMonsterList.append(monster);

                    connect(monster,&MotaMonster::linkMap,this,[this](GameObject* obj){
                        qDebug()<<"MotaMonster::linkMap--"<<obj->getId()<<obj->getClassName();
                        QPair<int,QPair<int,int>> objPos=m_motaMap->findObjectPos(obj->getId());
                        if(objPos.first!=-1)
                        {
                            QPoint p=m_motaMap->getElementPoint(objPos.first,objPos.second.first,objPos.second.second);
                            int posX=p.x();
                            int posY=p.y();
                            obj->setPosX(posX);
                            obj->setPosY(posY);
                            obj->setPosInit(true);
                        }
                    });
                }

                obj->init(&tmp2);
                m_elementList[packetName].append(obj);

            }
        }

    }


//    for(auto it=m_element.begin();it!=m_element.end();++it)
//    {
//        if(data.contains(it.key()))
//        {
//            //qDebug()<<"!!!!MotaDemo::init!!!!"<<it.key();
//            QJsonObject tmp=data.value(it.key()).toObject();
//            it.value().second->init(&tmp);
//        }
//    }
    registToManager();
}

void MotaDemo::registToManager()
{
    qDebug()<<"---MotaDemo::registToManager---";
    /*
     *  将Demo的指令进行注册
        将该Demo中的所有GO向SourceManager进行注册
        1.从文件中读取的资产应该具有已标准化的ID
        2.对新建的ID进行依靠Source自己处理。
        3.在source生成Demo配置文件时再进行统一的标准化处理。
        4.注册GameObject类、所含组件和属性。
    */

    //将demo的func--指令处理进行建立。
    emit demoFuncRegistToManager(heroMoveToNextElement,"heroMoveToNextElement");

    emit demoFuncRegistToManager(monsterMoveToNextElement,"monsterMoveToNextElement");
    //将demo的func--指令处理进行建立。


    //将demo中含有的所有GameObject种类进行注册
    emit objectRegistToManager(new MotaMap(m_motaMap),"MotaMap");
    emit objectRegistToManager(new MotaHero(m_motaHero),"MotaHero");

    for(auto it:m_motaMonsterList)
    {
        emit objectRegistToManager(new MotaMonster(it),"MotaMonster");
    }




    //将demo中含有的所有GameObject进行建立

    qDebug()<<"---check0:"<<m_motaMap->getId()<<m_motaMap->getPixIdList();


    if(m_motaMap->getId()!=0)
    {
        emit objectCreatedFromFile(m_motaMap,m_motaMap->getId());
    }
    else
    {
        emit objectCreated(m_motaMap);
    }


    qDebug()<<"---check1:"<<m_motaHero->getId()<<m_motaHero->getPixIdList();
    if(m_motaHero->getId()!=0)
    {
        emit objectCreatedFromFile(m_motaHero,m_motaHero->getId());
    }
    else
    {
        emit objectCreated(m_motaHero);
    }


    for(auto it:m_motaMonsterList)
    {
        if(it->getId()!=0)
        {
            emit objectCreatedFromFile(it,it->getId());
        }
        else
        {
            emit objectCreated(it);
        }
    }


    qDebug()<<"---MotaDemo::registToManager---end";
}


