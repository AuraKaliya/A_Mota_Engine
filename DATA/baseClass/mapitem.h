#ifndef MAPITEM_H
#define MAPITEM_H

#include <QObject>
#include <DATA/baseClass/gameobjectitem.h>


/*
1. 地图类型的Item
    额外拥有地图容量X*Y
    拥有基本图Pix（即空容量时显示的内容）
    拥有子图数count=X*Y
    拥有子图Vector<Pix*>  size=count
    初始化后生成子Item，根据容量进行填充。
    子Item不可选中，仅通过mapItem提供的方法进行定位和修改。
    子item的参数由MapItem进行规划确定
*/

class MapItem : public GameObjectItem
{
    Q_OBJECT
public:
    explicit MapItem(GameObject *obj, QPixmap pix,QObject *parent=nullptr);

signals:

};

#endif // MAPITEM_H
