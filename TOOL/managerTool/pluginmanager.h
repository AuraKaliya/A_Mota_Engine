#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <DATA/baseClass/basicdata.h>
#include <QDir>
#include <QPluginLoader>
#include <QString>
#include <QVector>
#include "QApplication"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager* getInstance(QObject *parent = nullptr);

    void initPluginList();
    void loadPlugins();
    void setRootWidget(UIWidget* rootWidget);
    QVector<QWidget *> pluginWidgetList() const;

    QStringList pluginFiles() const;

private:
    static PluginManager* m_instance;
    explicit PluginManager(QObject *parent = nullptr);

    UIWidget* m_rootWidget;
    QDir * m_pluginDir;
    QStringList m_pluginFiles;
    QMap<QString,EnginePlugin*> m_pluginDictionary;
    QVector<QWidget*> m_pluginWidgetList;

signals:
    void pluginLoadFinished();
};

#endif // PLUGINMANAGER_H
