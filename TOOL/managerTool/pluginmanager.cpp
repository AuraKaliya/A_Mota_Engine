#include "pluginmanager.h"

PluginManager* PluginManager::m_instance=nullptr;
PluginManager *PluginManager::getInstance(QObject *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new PluginManager(parent);
    }
    return m_instance;
}

void PluginManager::initPluginList()
{
    m_pluginFiles.clear();
    QStringList fileNames;
    fileNames<<"*.engine.dll";
    m_pluginFiles=m_pluginDir->entryList(fileNames,QDir::Files|QDir::Readable,QDir::Name);

    //==========test==========
    qDebug()<<"checkPlugin find :"<<m_pluginFiles;
    //
}

void PluginManager::loadPlugins()
{
    for(auto it:m_pluginFiles)
    {
        QPluginLoader loader;
        loader.setFileName(m_pluginDir->filePath(it));

        bool loadFlag=loader.load();
        if(!loadFlag)
        {
            qDebug()<<"error: "<<"load "<<it<<":"<<loader.errorString();
            continue;
        }

        EnginePlugin * p=qobject_cast<EnginePlugin*>(loader.instance());
        if(p)
        {
            p->initPlugin();
            p->initApp(m_rootWidget);

            if(true)
            {
                m_pluginWidgetList.append(p->getWidget());
                p->work();
            }

        }
        m_pluginDictionary.insert(p->getPluginName(),p);
    }
    emit pluginLoadFinished();
}

PluginManager::PluginManager(QObject *parent)
    : QObject{parent}
{
    m_pluginDir=new QDir(qApp->applicationDirPath()+"/plugins");

    //==========test==========
    qDebug()<<"checkPlugin:"<<m_pluginDir->path();
    //
}

QVector<QWidget *> PluginManager::pluginWidgetList() const
{
    return m_pluginWidgetList;
}
