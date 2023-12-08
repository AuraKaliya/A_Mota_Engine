#ifndef SOURCECARDVIEWWIDGET_H
#define SOURCECARDVIEWWIDGET_H

#include <QWidget>
#include <QRect>
#include <QSet>
#include <UI/componentWidget/sourcecardwidget.h>
#include <TOOL/sourceTool/sourcesystem.h>
#include <QGridLayout>

using doFunc=bool(*)();
inline bool doAccept(){return true;}
inline bool doIgnore(){return false;}

class SourceCardViewWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(ViewClass cardType READ getCardType WRITE setCardType NOTIFY cardTypeChanged)
public:
    enum SelectState
    {
        NoSelect=0,
        SingleSelect=1,
        MultipleSelect=2
    };
    enum class ViewClass
    {
        IMG=0,
        GO=1
    };
private:
    static QMap<QString,doFunc> m_eventSoluteDictionary;
    QVector<SourceCardWidget*> m_cardWidgetList;
    QVector<SourceCardWidget*> m_selectWidgetList;
    SourceCardWidget*m_nowSelectWidget=nullptr;
    QGridLayout* m_mainLayout=nullptr;
    QLabel* m_linkLabel=nullptr;

    bool m_mousePressedState=false;
    bool m_dragState=false;

    SelectState m_selectState=NoSelect;

    QPointF m_selectStartPoint;
    QPointF m_selectEndPoint;
    QRect m_selectRect;
    QString m_dataText;

    QRect m_rect;

    ViewClass m_cardType=SourceCardViewWidget::ViewClass::IMG;


public:
    static void registerToEventSolution(QString className);
    static bool findDragDictionary(QString className);
    explicit SourceCardViewWidget(QWidget *parent = nullptr);
    explicit SourceCardViewWidget(ViewClass cardType,QWidget *parent = nullptr);
    void addCardWidget(SourceCardWidget* w);
    void delCardWidget(SourceCardWidget* w);
    void reLayout();
    void delCardWidget(int idx);
    int findWidget(SourceCardWidget* w);
    void initWidget();
    void setLinkLabel(QLabel*l);
    void updateSelectRect();
    void resetSelectedState();
    ViewClass getCardType() const;
    void setCardType(ViewClass newCardType);
    void clearSelectWidget();
    QRect getShowRect();

protected:
    void dragEnterEvent(QDragEnterEvent*e)override;
    void dropEvent(QDropEvent*e)override;
    void mousePressEvent(QMouseEvent* e)override;
    void mouseMoveEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent* e)override;
    void dragMoveEvent(QDragMoveEvent* e)override;
    void paintEvent(QPaintEvent* e)override;
    void resizeEvent(QResizeEvent *e)override;
signals:
    void nowFocusWidget(SourceCardViewWidget* );
    void widgetDeleted(SourceCardWidget* );
    void cardTypeChanged();
    void dropDataSoluted();
    void dropStart(SourceCardViewWidget* );
    void widgetResized();
};

#endif // SOURCECARDVIEWWIDGET_H
