#ifndef SOURCECARDWIDGET_H
#define SOURCECARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <DATA/baseClass/sourcemetadata.h>
#include <QMap>
#include <QMouseEvent>
#include <DATA/baseClass/gameobject.h>

/*
cardwidget
可将数据拖出，接收函数要放在上一层的窗体上
*/
class SourceCardWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel* m_linkWidget=nullptr;
    QString m_dataText;
    SourceMetaData* m_metaData=nullptr;
    bool m_dragable=false;
    bool m_isSelected=false;
    bool m_isDraged=false;
    bool m_initBySourceMetaData=true;
    QLabel* m_iconLabel=nullptr;
    QLabel* m_nameLabel=nullptr;

public:
    explicit SourceCardWidget(QWidget *parent = nullptr);
    bool initCard(SourceMetaData* data);
    void enterEvent(QEnterEvent*e)override;
    void setSelected(bool b);
    bool getSelected();
    void setDragable(bool able);
    bool getDragable();
    SourceMetaData* getMetaData();

protected:
    //void dragEnterEvent(QDragEnterEvent*e)override;
    //void dropEvent(QDropEvent*e)override;
    //void mousePressEvent(QMouseEvent* e)override;
    //void mouseMoveEvent(QMouseEvent* e)override;
    //void mouseReleaseEvent(QMouseEvent* e)override;
    //void paintEvent(QPaintEvent* e)override;
    //void dragMoveEvent(QDragMoveEvent* e)override;

signals:
    void selectStateChanged(SourceCardWidget*,bool);
    void thisClicked(SourceCardWidget* );
};

#endif // SOURCECARDWIDGET_H
