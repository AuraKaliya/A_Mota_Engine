#ifndef EDITSYSTEM_H
#define EDITSYSTEM_H

#include <QObject>
#include "../../DATA/baseClass/systemobject.h"
#include <TOOL/managerTool/editmanager.h>
class EditSystem : public SystemObject
{
    Q_OBJECT

private:
    static EditSystem* m_instance;
    EditManager * m_editManager=nullptr;
public:
    static EditSystem* getInstance(QObject * parent=nullptr);
    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;
    EditManager *getManager();

private:
    explicit EditSystem(QObject *parent = nullptr);

signals:

};

#endif // EDITSYSTEM_H
