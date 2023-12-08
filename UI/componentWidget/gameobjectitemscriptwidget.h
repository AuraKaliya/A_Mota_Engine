#ifndef GAMEOBJECTITEMSCRIPTWIDGET_H
#define GAMEOBJECTITEMSCRIPTWIDGET_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLineEdit>


#include <DATA/baseClass/gameobjectitem.h>
#include <TOOL/scriptTool/scriptsystem.h>

class GameObjectItemScriptWidget : public QWidget
{
    Q_OBJECT
private:
    GameObjectItem* m_linkItem=nullptr;

    QWidget* m_hasScriptWidget;
    QWidget* m_noScriptWidget;

    QPushButton* m_addScriptBtn;
    QPushButton* m_loadScriptBtn;

    QLineEdit* m_fileNameBox;
    QPushButton* m_changeScriptBtn;
    QPushButton* m_delScriptBtn;

public:
    explicit GameObjectItemScriptWidget(QWidget *parent = nullptr);
    void linkItem(GameObjectItem*item);
    void showHasScriptWidget();
    void showNoScriptWidget();
private:
    void initWidget();
    void initHasScriptWidget();
    void initNoScriptWidget();
    void itemChanged();
signals:

};

#endif // GAMEOBJECTITEMSCRIPTWIDGET_H
