#include "cardlabel.h"

CardLabel::CardLabel(QWidget *parent)
    : ClickLabel{parent}
{
    m_cardId=-1;
}

int CardLabel::cardId() const
{
    return m_cardId;
}

void CardLabel::setCardId(int newCardId)
{
    m_cardId = newCardId;
}

void CardLabel::mousePressEvent(QMouseEvent *e)
{
    ClickLabel::mousePressEvent(e);
    emit cardIdSignal(m_cardId);
}
