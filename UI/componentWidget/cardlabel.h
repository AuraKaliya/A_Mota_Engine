#ifndef CARDLABEL_H
#define CARDLABEL_H

#include <QWidget>
#include <DATA/baseClass/clicklabel.h>
class CardLabel : public ClickLabel
{
    Q_OBJECT
public:
    explicit CardLabel(QWidget *parent = nullptr);

    int cardId() const;
    void setCardId(int newCardId);
protected:
    void mousePressEvent(QMouseEvent*e)override;
private:
    int m_cardId;
signals:
    void cardIdSignal(int);
};

#endif // CARDLABEL_H
