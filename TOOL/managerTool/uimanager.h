#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>
#include <DATA/baseClass/uiwidget.h>
#include <DATA/enginestate.h>
#include <TOOL/sourceTool/sourcesystem.h>
#include <TOOL/editTool/editsystem.h>
#include <TOOL/pluginTool/pluginsystem.h>

#include <UI/editWidget/sourcemanagewidget.h>
#include <ui/editWidget/gameshowwidget.h>
#include <ui/editWidget/propertyeditwidget.h>
#include <ui/editWidget/eventeditwidget.h>
#include <ui/editWidget/historywidget.h>
#include <ui/editWidget/itemtreewidget.h>

#pragma execution_character_set("utf-8")
class UIManager : public QObject
{
    Q_OBJECT

public:

    void updateUIStyle();
private:
    static UIManager* m_instance;
    EngineState m_engineState=EngineState::Editor;
    UIWidget* m_playerUI=nullptr;
    UIWidget* m_sourceManageUI=nullptr;
    UIWidget* m_gameShowUI=nullptr;
    UIWidget* m_propertyEditUI=nullptr;
    UIWidget* m_eventEditWidget=nullptr;
    UIWidget* m_historyWidget=nullptr;
    UIWidget* m_itemTreeUI=nullptr;
    QWidget * m_rootWidget=nullptr;

    QVector<UIWidget* > m_widgetList={};

public:
    static UIManager* getInstance(QObject *parent = nullptr);




    void setRoot(QWidget *root);
    void loadUI();

private:
    explicit UIManager(QObject *parent = nullptr);

signals:

};

#endif // UIMANAGER_H
