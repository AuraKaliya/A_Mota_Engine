#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <Data/baseClass/uiwidget.h>
#include <QResizeEvent>
#include <QStackedWidget>
#include <UI/componentWidget/gameshowview.h>
#include <UI/componentWidget/gameobjectdropwidget.h>
#include <TOOL/editTool/editsystem.h>
class TestWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit TestWidget(QWidget *parent = nullptr);
    void init();
protected:
    void resizeEvent(QResizeEvent *e)override;
    void closeEvent(QCloseEvent *e)override;
private:
    QStackedWidget * m_viewList;
    GameShowView* m_gameShowView=nullptr;
    QVector<QGraphicsScene *> m_scenes;
signals:
    void closed();
};

#endif // TESTWIDGET_H
