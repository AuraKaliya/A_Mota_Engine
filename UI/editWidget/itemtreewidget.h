#ifndef ITEMTREEWIDGET_H
#define ITEMTREEWIDGET_H

#include <QWidget>
#include <DATA/baseClass/uiwidget.h>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVector>
#include <QMap>
#include <TOOL/editTool/editsystem.h>

class ItemTreeWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit ItemTreeWidget(QWidget *parent = nullptr);

    void addScene(QString scene);
    void addItemToScene(QString scene,QString itemName);
public slots:
    void updateTree();
    void resetTree();
protected:
    void paintEvent(QPaintEvent* e)override;
private:
    QTreeView * m_view;
    QStandardItemModel *m_model;
    QMap<QString,int> m_SceneToIndexDictionary;
    QVector<QVector <QStandardItem*> > m_itemList;

signals:

};

#endif // ITEMTREEWIDGET_H
