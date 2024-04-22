#ifndef CARDHUBWIDGET_H
#define CARDHUBWIDGET_H

#include <QWidget>
#include <TOOL/sourceTool/sourcesystem.h>
#include <UI/componentWidget/cardlabel.h>
#include <UI/componentWidget/wheelslidewidget.h>
#include <QGridLayout>

class CardHubWidget : public WheelSlideWidget
{
    Q_OBJECT
public:
    explicit CardHubWidget(QWidget *parent = nullptr);
    void initWidget();
    void showByPix();
    void hideByPix();

    static bool getInitFlag();

private:
    static bool s_initFlag;
    QGridLayout * m_mainLayout;
    QVector<CardLabel*> m_cardLabelList;
signals:
    void cardSelectById(int );
};

#endif // CARDHUBWIDGET_H
