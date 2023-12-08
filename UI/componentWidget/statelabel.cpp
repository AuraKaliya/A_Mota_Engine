#include "statelabel.h"

StateLabel::StateSwitchStritagies StateLabel::getStritagy() const
{
    return m_stritagy;
}

void StateLabel::setStritagy(StateSwitchStritagies newStritagy)
{
    m_stritagy = newStritagy;
}

void StateLabel::setNowState(SourceManageLabelState state)
{
    m_nowState=state;
    emit stateChanged(m_nowState);
}

StateLabel::StateLabel(QWidget *parent)
    : ClickLabel{parent},m_nowState(SourceManageLabelState::Show)
{
    m_stateSwitchDictionary[SourceManageLabelState::Show]=SourceManageLabelState::Show;
    connect(this,&StateLabel::stateChanged,this,[=](SourceManageLabelState state){
        auto it=m_statePixmapPathDictionary.find(state);
        if(it!=m_statePixmapPathDictionary.end())
        setPixmap(m_statePixmapPathDictionary.find(state).value());
    });
}

StateLabel::StateLabel(const QString &text, QWidget *parent):StateLabel(parent)
{
    setText(text);
}

void StateLabel::addStatePixmapPath(SourceManageLabelState state, QString path)
{
    m_statePixmapPathDictionary[state]=path;
    m_stateSwitchDictionary[state]=state;
}

void StateLabel::setStateSwitch(SourceManageLabelState oldState, SourceManageLabelState newState)
{
    m_stateSwitchDictionary[oldState]=newState;
}

void StateLabel::stateSwitchNext()
{
    auto it =m_stateSwitchDictionary.find(m_nowState);
    if(it!=m_stateSwitchDictionary.end())
    {

        m_nowState=it.value();
        //qDebug()<<(int)m_nowState;
        auto it2=m_statePixmapPathDictionary.find(m_nowState);
        if(it2!=m_statePixmapPathDictionary.end())
        {
            setPixmap(it2.value());
        }
        else
        {
            qDebug()<<"No have this pixmap";
        }
        emit stateChanged(m_nowState);
        emit labelStateChanged(this,m_nowState);
    }
    else
    {
        qDebug()<<"NO this VALUE";
        for(auto it2=m_stateSwitchDictionary.begin();it2!=m_stateSwitchDictionary.end();++it2)
        {
            qDebug()<<(int)it.key()<<"  "<<(int)it.value();
        }

    }

}

void StateLabel::setLinkWidget(QWidget *w)
{
    m_linkWidget=w;
}

QWidget *StateLabel::getLinkWidget()
{
    return  m_linkWidget;
}

SourceManageLabelState StateLabel::getNowState()
{
    return m_nowState;
}

void StateLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        if(m_stritagy==StateSwitchStritagies::Click)
        stateSwitchNext();
    }
    ClickLabel::mouseReleaseEvent(e);
}
