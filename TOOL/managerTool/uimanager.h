#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>
#include <DATA/baseClass/uiwidget.h>
#include <DATA/enginestate.h>
#include <TOOL/sourceTool/sourcesystem.h>
#include <TOOL/editTool/editsystem.h>

#include <UI/editWidget/sourcemanagewidget.h>
#include <ui/editWidget/gameshowwidget.h>
#include <ui/editWidget/propertyeditwidget.h>
#include <ui/editWidget/eventeditwidget.h>


class UIManager : public QObject
{
    Q_OBJECT

public:

private:
    static UIManager* m_instance;
    EngineState m_engineState=EngineState::Editor;
    UIWidget* m_playerUI=nullptr;
    UIWidget* m_sourceManageUI=nullptr;
    UIWidget* m_gameShowUI=nullptr;
    UIWidget* m_propertyEditUI=nullptr;
    UIWidget* m_eventEditWidget=nullptr;
    QWidget * m_rootWidget=nullptr;



public:
    static UIManager* getInstance(QObject *parent = nullptr);




    void setRoot(QWidget *root);
    void loadUI();

private:
    explicit UIManager(QObject *parent = nullptr);

signals:

};

#endif // UIMANAGER_H
