#ifndef SOURCEMANAGEWIDGET_H
#define SOURCEMANAGEWIDGET_H

#include <QWidget>
#include <DATA/baseClass/uiwidget.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <UI/componentWidget/addsourcewidget.h>
#include <UI/componentWidget/sourcetreewidget.h>
#include <UI/componentWidget/addgameobjectinfowidget.h>


class SourceManageWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit SourceManageWidget(QWidget *parent = nullptr);
    void setUIStyle()override;
    void paintEvent(QPaintEvent* e)override;
protected:

private:
    //QHBoxLayout* m_addSourceWidgetMainLayout;
    QVBoxLayout* m_mainLayout;
    AddSourceWidget* m_addSourceWidget=nullptr;
    SourceTreeWidget* m_sourceTreeWidget=nullptr;
    AddGameObjectInfoWidget* m_addGameObjectInfoWidget=nullptr;

signals:

};

#endif // SOURCEMANAGEWIDGET_H
