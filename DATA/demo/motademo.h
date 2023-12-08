#ifndef MOTADEMO_H
#define MOTADEMO_H

#include <QObject>
#include "../baseClass/gamedemo.h"
#include "../gameObject/motamap.h"
#include "../gameObject/motahero.h"
#include "../gameObject/motamonster.h"

#include <TOOL/template/Factory.hpp>

/*
    实际的Demo应该放在TOOL层，因为在Demo中并不只存有相关数据，还有进行处理的方案，有与UI交互的部分。
*/

class MotaDemo : public GameDemo
{
    Q_OBJECT

private:
    MotaMap * m_motaMap;
    MotaHero* m_motaHero;
    QVector<MotaMonster*> m_motaMonsterList;
    explicit MotaDemo(QObject *parent = nullptr);

    static MotaDemo* m_instance;

    static void heroMoveToNextElement(GameObject* hero,QVariant v);
    static void monsterMoveToNextElement(GameObject* monster,QVariant v);
    static void heroMoveToElement(GameObject* hero,QVariant v);



public:
    static MotaDemo* getInstance();
    void init(const QJsonObject* obj)override;
    void registToManager()override;

signals:

};

#endif // MOTADEMO_H
