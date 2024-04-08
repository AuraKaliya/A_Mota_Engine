#ifndef ENGINECORE_H
#define ENGINECORE_H

#include <QWidget>
#include <QState>
#include <QStateMachine>
#include <QMap>


#include "./DATA/baseClass/systemobject.h"
#include "./TOOL/sourceTool/jsonparser.h"

#include "./TOOL/sourceTool/sourcesystem.h"
#include <TOOL/instructionTool/instructionsystem.h>
#include <TOOL/editTool/editsystem.h>
#include <TOOL/uiTool/uisystem.h>
#include <TOOL/scriptTool/scriptsystem.h>
#include <TOOL/pluginTool/pluginsystem.h>
#include "TOOL/managerTool/statemanger.h"

#include <DATA/constvalue.h>



QT_BEGIN_NAMESPACE
namespace Ui { class EngineCore; }
QT_END_NAMESPACE

class EngineCore : public QWidget
{
    Q_OBJECT

public:
    EngineCore(QWidget *parent = nullptr);
    ~EngineCore();

    void test();
    void startSystem();
protected:

    bool eventFilter(QObject* obj, QEvent*e)override;
    void keyPressEvent(QKeyEvent* e)override;
    void keyReleaseEvent(QKeyEvent* e)override;

private:
    Ui::EngineCore *ui;

    StateManger * m_stateManager=nullptr;

    QMap<QString,SystemObject*> m_systemDictionary;

    JsonParser* m_jsonParser=nullptr;

    SourceSystem* m_sourceSystem=nullptr;
    InstructionSystem* m_instructionSyStem=nullptr;
    EditSystem* m_editSystem=nullptr;
    UISystem* m_uiSystem=nullptr;
    ScriptSystem* m_scriptSystem=nullptr;
    PluginSystem* m_pluginSystem=nullptr;


    //**test****//
    int testx=0;

    //**test****//


signals:
    void closeEngine();
    void actionSend(QString str);
private slots:

    //**test****//
    void on_testBtn_clicked();
    void on_pushButton_clicked();
    void on_insButton_clicked();
    //**test****//
    void on_pushButton_2_clicked();
};
#endif // ENGINECORE_H
