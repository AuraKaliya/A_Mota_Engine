#include "cardhubwidget.h"
bool CardHubWidget::s_initFlag=false;
CardHubWidget::CardHubWidget(QWidget *parent)
    : WheelSlideWidget{parent}
{
    setFixedSize(300,600);
    setWheelDirection(VDirection);
}

void CardHubWidget::initWidget()
{

    //从资源系统中获取所有图片资源 形成卡牌 加入到area中
    m_cardLabelList.clear();

    for(auto it:SourceSystem::getInstance()->getManager()->getPixSourceList())
    {
        int cardId=it->id();
        CardLabel* cardLabel=new CardLabel();

        cardLabel->setFixedSize(90,160);
        cardLabel->setCardId(cardId);
        cardLabel->setPixmap(QPixmap(*it->pix()).scaled(cardLabel->width(),cardLabel->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

        addWidgetInArea(cardLabel,(m_cardLabelList.size()%3)*cardLabel->width(),(m_cardLabelList.size()/3)*(cardLabel->height()+10));
        cardLabel->setVisible(true);

        m_cardLabelList.append(cardLabel);
        connect(cardLabel,&CardLabel::cardIdSignal,this,[this](int id){
            emit cardSelectById(id);
            hideByPix();
        });
    }

    qDebug()<<"CardHubWidget::initWidget()==="<<m_cardLabelList.size();
    s_initFlag=true;
}

void CardHubWidget::showByPix()
{
    this->show();
    qDebug()<<"CardHubWidget::showByPix()===========";
    qDebug()<<"geo:"<<this->geometry()<<" vis"<<isVisible();
    for(auto it:m_cardLabelList)
    {
        qDebug()<<it->geometry()<<it->isVisible();

    }
    qDebug()<<"CardHubWidget::showByPix()===========";
}

void CardHubWidget::hideByPix()
{
    this->hide();
}

bool CardHubWidget::getInitFlag()
{
    return s_initFlag;
}
