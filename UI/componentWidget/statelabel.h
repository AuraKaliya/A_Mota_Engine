#ifndef STATELABEL_H
#define STATELABEL_H

#include <QWidget>
#include <DATA/baseClass/clicklabel.h>
#include <DATA/enginestate.h>

class StateLabel : public ClickLabel
{
    Q_OBJECT

public:
    enum StateSwitchStritagies{
        Click=1,
        Function=2
    };
private:
    SourceManageLabelState m_nowState;
    QMap<SourceManageLabelState,QString> m_statePixmapPathDictionary;
    QMap<SourceManageLabelState,SourceManageLabelState> m_stateSwitchDictionary;
    QWidget* m_linkWidget=nullptr;
    StateSwitchStritagies m_stritagy=Click;
public:
    explicit StateLabel(QWidget *parent = nullptr);
    explicit StateLabel(const QString &text, QWidget *parent = nullptr);
    void addStatePixmapPath(SourceManageLabelState state, QString path);
    void setStateSwitch(SourceManageLabelState oldState,SourceManageLabelState newState);
    void stateSwitchNext();
    void setLinkWidget(QWidget*w);
    QWidget* getLinkWidget();
    SourceManageLabelState getNowState();
    StateLabel::StateSwitchStritagies getStritagy() const;
    void setStritagy(StateSwitchStritagies newStritagy);
    void setNowState(SourceManageLabelState state);
protected:
    void mouseReleaseEvent(QMouseEvent* e)override;
signals:
    void stateChanged(SourceManageLabelState);
    void labelStateChanged(StateLabel*,SourceManageLabelState);
};

#endif // STATELABEL_H
