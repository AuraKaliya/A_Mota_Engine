#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
protected:
    //void dragEneterEvent(QDragEnterEvent*e)override;
signals:

};

#endif // GAMESCENE_H
