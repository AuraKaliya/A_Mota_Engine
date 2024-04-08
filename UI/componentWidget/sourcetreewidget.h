#ifndef SOURCETREEWIDGET_H
#define SOURCETREEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPair>
#include <QMap>
#include <TOOL/sourceTool/sourcesystem.h>
#include <UI/componentWidget/sourcecardwidget.h>
#include <UI/componentWidget/statelabel.h>
#include <UI/componentWidget/sourcecardviewwidget.h>
#include <UI/componentWidget/imagewidget.h>

class SourceTreeWidget : public QWidget
{
    Q_OBJECT

private:
    QWidget* m_area=nullptr;
    SourceCardViewWidget* m_nowDropWidget=nullptr;
    SourceCardViewWidget* m_nowFocusWidget=nullptr;
    bool m_init=false;
    QVector <QWidget*> m_firstNodesList;
    QVector<QVector <StateLabel* > > m_secondNodesList{};
    QVector<QVector<SourceCardViewWidget*> > m_viewsList{};
    QVector<SourceCardViewWidget::ViewClass> m_viewClassList{};

    //QMap<int,QString> m_FirstNodesName{};

public:
    explicit SourceTreeWidget(QWidget *parent = nullptr);

    QVector<QLabel*> getGOSecondNodesList();


    void addFirstNode(QString name);
    void addFirstNode(QString name,SourceCardViewWidget::ViewClass cardClass);
    void addSecondNode(int index,QString name);
    void initSource();
    void adjustAreaSize();
    void redoMove();

    void hideViewWidget(QWidget *w);
    void showViewWidget(QWidget *w);

    void updateSourceWidget();
protected:
    void wheelEvent(QWheelEvent* e)override;

signals:

};

#endif // SOURCETREEWIDGET_H
