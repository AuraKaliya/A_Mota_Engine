#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QSet>
#include <QPixmap>
#include <DATA/baseClass/sourcemetadata.h>
#include <DATA/baseClass/gameobject.h>
#include <DATA/baseClass/gamedemo.h>
#include <DATA/baseClass/gameobjectitem.h>
#include <DATA/baseClass/pixsource.h>
#include <TOOL/translateTool/valuetranslator.h>
#include <TOOL/template/Factory.hpp>
#include <TOOL/template/Registor.hpp>

/*
    资源管理者，存在于资源系统中；
    1. 导入资源  获取文件路径，判定合法性，导入建立基础类型。
    2. 初始化资产  需要在基础资源导入之后进行，建立GameObject对象并进行注册和管理。 --需要用到注册器，可提到资源系统中
    3. 修改资源 QFILE
    4. 获取基础资源ID，获取GO的ID。
    5. 对资源和资产的区分：是否可编辑/可进行游戏性编辑建立。资源自导入就为全局唯一，通过资源建立资产是从资源处取得后设置
    6. 通过Map对资源进行分类管理。
*/


//teset
#include "DATA/demo/motademo.h"
//test

using  readFunc=bool(*)(QString);
using  readJsonFunc=void(*)(QJsonObject);
class SourceManager : public QObject
{
    Q_OBJECT

public:
    enum SourceSystemError
    {
      ImportSource=1000,
      GameObjectRegist=1001
    };
    enum DefaultSource
    {
        Image,
        Text
    };
protected:
    static QMap<QString, readFunc> m_importStrategise;
    static QMap<QString,readJsonFunc> m_readJsonStrategise;
private:
    static QPixmap* m_defaultPix;
    GameDemo* m_nowDemo=nullptr;
    static unsigned int m_maxSourceId;
    static unsigned int m_maxGameObjectId;
    static unsigned int m_maxGameObjectItemId;
    static QMap<unsigned int , QPixmap* > m_pixmapDictionary;
    static QMap<unsigned int ,QVector<QPixmap> > m_multiplePixDictionary;
    static QMap<unsigned int , QString >  m_sourcePathDictionary;
    static QMap<unsigned int,GameObject*> m_gameObjectDictionary;
    static QMap<unsigned int,GameObjectItem*>m_gameObjectItemDictionary;
    static QMap<QString,GameObject*> m_gameObjectSampleDictionary;
    static QMap<QString,GameObject*> m_gameObjectSourceDictionary;
    static QMap<QString,GameDemo*> m_gameDemoDictionary;
    static SourceManager* m_instance;
    static QMap<unsigned int,SourceMetaData*>m_sourceMetaDataDictionary;
    //可以考虑改为存放QMetaProperty
    static QMap<QString,QVector<QPair<QString,QString> > > m_gameObjectBasePropertyList;
    static QMap<QString,QVector<QMetaProperty> > m_gameObjectPropertyList;
    static QMap<QString,QVector<QString>> m_gameObjectComponentList;
    static QMap<QString,QVector<QMetaProperty>> m_gameObjectComponentPropertyList;
    static QMap<QString,QVector<QPixmap>> m_DynamicPixmapDictionary;
    static QMap<unsigned int,PixSource*>m_pixSourceDictionary;
    static QString m_outPortPath;

public:
    static SourceManager* getInstance();

    void importSource(QString path);
    void addGameObject(GameObject* gameObject);
    void addGameObjectFromSample(QString objClass);
    void addGameObjectSourceFromSample(QString objClass);
    GameObject* addGameObjectFromSource(QString objName);
    void addGameObjectById(GameObject* obj,unsigned int id);
    void addGameObjectItem(GameObjectItem* item);
    void addGameObejctItemById(GameObjectItem* item,unsigned int id);
    GameObjectItem* getGameObjectItemById(unsigned int id);
    void registerGameObjectSample(GameObject* obj,QString objClass);
    void registerGameObjectSource(GameObject* obj,QString objName);

    void modifySource(QByteArray data,QString path);

    QString getSourcePathById(unsigned int id);
    QPixmap* getPixmapById(unsigned int id);
    QPixmap* getPixmapById(unsigned int id,bool defaultPix);
    QPixmap* getPixmapByObject(GameObject*obj);
    PixSource* getPixSourceById(unsigned int id);
    QVector<PixSource* > getPixSourceList();
    GameObject* getObjectById(unsigned int id);
    QVector<QPair<int,QPixmap*> > getPixmapList();
    QVector<QPair<unsigned int,GameObject* > > getGameObjectList();
    QVector<GameObject*> getGameObjectSourceList();
    GameObject* getGameObjectSourceByName(QString name);
    QVector<QPair<QString,GameObject* > > getGameObjectSampleList();
    QVector<QString>* getComponentByGameObjectName(QString name);
    QVector<QMetaProperty>* getComponentPropertyByComponentName(QString name);
    QVector<QMetaProperty>* getGameObjectPropertyByObjectName(QString name);
    SourceMetaData*  getSourceMetaDataFromPixById(unsigned int id);
    SourceMetaData*  getSourceMetaDataFromGOById(unsigned int id);
    SourceMetaData*  getSourceMetaDataFromGOSourceByName(QString objName);
    QVector<QPixmap> cutPixFromId(unsigned int id,int startX,int startY,int perWidth,int perHeight,int xInterval,int yInterval);
    QVector<QVector<QPixmap* >> getMultiplePixByControlList(unsigned int,QString);
    QVector<QVector<int>> getIndexListByStr(QString indexStrList);

    GameDemo* getNowDemo();
    void outPortDemo();

protected:
    static void addPixmap(unsigned int id,QString path,QPixmap* pix);
    static void addPixSource(unsigned int id,PixSource* pixSource);
    static bool readImage(QString path);
    static bool readDynamicImage(QString path);
    static bool readPixSource(QString path);
    static bool readJson(QString path);
    static bool registerSourcePathById(unsigned int id,QString path);
    static bool registerGameObjectById(unsigned int id,GameObject* gameObject);
    static bool registerPixmapById(unsigned int id,QPixmap* pix);
    static void readJsonFileToDemo(QJsonObject obj);
    static void readJsonFileToSource(QJsonObject obj);
    static SourceMetaData* findSourceMetaData(unsigned int id);
    void setNowDemo(GameDemo* demo);
    void solveError(SourceSystemError error);
private:
    explicit SourceManager(QObject *parent = nullptr);

signals:
    void addSource();
    void newGameObjectRegisted(GameObject*,QString);
    void newFuncRegisted(SoluteFunc,QString);
};

#endif // SOURCEMANAGER_H
