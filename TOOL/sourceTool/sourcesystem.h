#ifndef SOURCESYSTEM_H
#define SOURCESYSTEM_H
#include "../../DATA/baseClass/systemobject.h"
#include "../managerTool/sourcemanager.h"
#include <QObject>

class SourceSystem : public SystemObject
{
    Q_OBJECT
public:

    static SourceSystem *getInstance(QObject *parent = nullptr);

    SourceManager* getManager();

    bool systemStart()override;
    bool systemInit() override;
    bool systemSolve() override;
    bool systemQuit() override;


private:
    explicit SourceSystem(QObject *parent = nullptr);

    static SourceSystem* m_instance;
    SourceManager* m_sourceManager=nullptr;
signals:

};

#endif // SOURCESYSTEM_H
