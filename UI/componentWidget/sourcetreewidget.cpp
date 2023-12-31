#include "sourcetreewidget.h"

#include <QGridLayout>
#include <QPropertyAnimation>
#include <QWheelEvent>

SourceTreeWidget::SourceTreeWidget(QWidget *parent)
    : QWidget{parent}
{
    m_area=new QWidget(this);
    m_area->move(0,0);
//
    //setStyleSheet("background-color:blue;");
//

}

QVector<QLabel *> SourceTreeWidget::getGOSecondNodesList()
{
    QVector<QLabel *> tmpList;
    for(auto it:m_secondNodesList[1])
        tmpList.append(it);

    return tmpList;
}

void SourceTreeWidget::addFirstNode(QString name)
{
    QLabel* firstNodeLabel=new QLabel(name,m_area);
    firstNodeLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    firstNodeLabel->setFixedHeight(50);
    firstNodeLabel->setFixedWidth(this->width());
    m_firstNodesList.append(firstNodeLabel);

    m_viewsList.append(*new QVector<SourceCardViewWidget*>);
    m_secondNodesList.append(*new QVector<StateLabel*>);
    addSecondNode(m_secondNodesList.size()-1,QString("未定义"));
    addSecondNode(m_secondNodesList.size()-1,QString("未定义2"));
}

void SourceTreeWidget::addFirstNode(QString name, SourceCardViewWidget::ViewClass cardClass)
{
    m_viewClassList.append(cardClass);
    addFirstNode(name);
}

void SourceTreeWidget::addSecondNode(int index, QString name)
{
    StateLabel* label=new StateLabel(name,m_area);
    SourceCardViewWidget* widget=new SourceCardViewWidget(m_viewClassList[index],m_area);
    label->setLinkWidget(widget);
    label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    label->setFixedHeight(50);
    label->setFixedWidth(this->width()-20);
    label->setStateSwitch(SourceManageLabelState::Show,SourceManageLabelState::Hide);
    label->setStateSwitch(SourceManageLabelState::Hide,SourceManageLabelState::Show);
    m_secondNodesList[index].append(label);

    //
    widget->setStyleSheet("background-color:white;");
    //

    widget->setFixedWidth(this->width());
    widget->setMinimumHeight(10);
    widget->setAcceptDrops(true);
    widget->setLinkLabel(label);
    m_viewsList[index].append(widget);

    connect(label,&StateLabel::labelStateChanged,this,[&](StateLabel*thisLabel,SourceManageLabelState state){
        switch (state) {
        case SourceManageLabelState::Show:
            showViewWidget(thisLabel->getLinkWidget());
            //test  在label中有添加自动转换的图片的功能
            thisLabel->setStyleSheet("background-color:blue");
            break;
        case SourceManageLabelState::Hide:
            static_cast<SourceCardViewWidget*>(thisLabel->getLinkWidget())->resetSelectedState();
            hideViewWidget(thisLabel->getLinkWidget());
            thisLabel->setStyleSheet("background-color:red");
            break;
        default:
            break;
        }
    });

    connect(widget,&SourceCardViewWidget::nowFocusWidget,this,[=](SourceCardViewWidget* w){
        qDebug()<<"nowFocusWidgetChanged";
        if(m_nowDropWidget!=nullptr&&m_nowDropWidget!=w) m_nowDropWidget->resetSelectedState();
            m_nowDropWidget=w;
    });
    connect(widget,&SourceCardViewWidget::dropStart,this,[=](SourceCardViewWidget* w){
        m_nowDropWidget=w;
    });
    connect(widget,&SourceCardViewWidget::dropDataSoluted,this,[=](){
        m_nowDropWidget->clearSelectWidget();
    });
    connect(widget,&SourceCardViewWidget::widgetResized,this,[=](){
        adjustAreaSize();
    });




}

void SourceTreeWidget::initSource()
{
    //从资源系统中获取所有资源的列表，进行更新
    //删除已有的
//    for(const auto &it:m_viewsList)
//    {
//        for(auto it2:it)
//        {
//            [=](){
//                if(!it2->children().empty())
//                delete it2->children()[0];
//            }();
//            for(auto item:it2->children())
//            {
//                delete item;
//            }
//        }
//    }

    for(const auto & it: m_viewsList)
    {
        for(auto it2:it)
        it2->initWidget();
    }

    //初始化ImageNode
#if 0
  //
    QGridLayout * layout=new QGridLayout(m_viewsList[0][0]);
    layout->setSpacing(10);
    int index=0;

    qDebug()<<SourceSystem::getInstance()->getManager()->getPixmapList();

    for(auto it:SourceSystem::getInstance()->getManager()->getPixmapList())
    {
        SourceCardWidget* card=new SourceCardWidget(m_viewsList[0][0]);
        card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromPixById(it.first));
        card->setVisible(true);
        layout->addWidget(card,index/3,index%3);
        ++index;
    }
    m_viewsList[0][0]->setLayout(layout);
    m_viewsList[0][0]->resize(m_viewsList[0][0]->width(),210*((index+2)/3)+20);

    qDebug()<<m_viewsList[0][0]->children();
#endif

    for(auto it:SourceSystem::getInstance()->getManager()->getPixmapList())
    {
        //[0][0]:Image-未定义
        SourceCardWidget* card=new SourceCardWidget(m_viewsList[0][0]);
        card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromPixById(it.first));
        card->setVisible(true);
        m_viewsList[0][0]->addCardWidget(card);
    }

    for(auto it:SourceSystem::getInstance()->getManager()->getGameObjectSourceList())
    {
        //[0][0]:Image-未定义
        SourceCardWidget* card=new SourceCardWidget(m_viewsList[1][0]);

        //card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromGOSourceByName(it->getName()));
        qDebug()<<"%%%%%%%%%"<<it->getId();
        card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromGOById(it->getId()));
        card->setVisible(true);
        m_viewsList[1][0]->addCardWidget(card);
    }

    //更新GameObjectNode

    adjustAreaSize();
}


void SourceTreeWidget::adjustAreaSize()
{
    int height=0;
    for(int i=0;i<m_firstNodesList.size();++i)
    {
        m_firstNodesList[i]->move(0,height);
        height+=m_firstNodesList[i]->height();
        for(int j=0;j<m_secondNodesList[i].size();++j)
        {
            m_secondNodesList[i][j]->move(20,height);
            height+=m_secondNodesList[i][j]->height();

            m_viewsList[i][j]->move(0,height);
            height+=m_viewsList[i][j]->height();
        }
    }

    m_area->resize(this->width(),height);

}

void SourceTreeWidget::redoMove()
{
    int nowY=m_area->y();
    int heightLimit=this->height();
    if(nowY+m_area->height()<heightLimit)
    {
        m_area->move(m_area->x(),heightLimit-m_area->height());
    }
    else if(nowY>0)
    {
        m_area->move(m_area->x(),0);
    }
}

void SourceTreeWidget::hideViewWidget(QWidget *w)
{

    QPropertyAnimation * animation=new QPropertyAnimation(w,"geometry");
    animation->setDuration(100);
    animation->setStartValue(w->rect());
    animation->setEndValue(QRect(w->x(),w->y(),w->width(),10));
    //animation->setEasingCurve(QEasingCurve::InOutBounce);
    connect(animation,&QPropertyAnimation::finished,[](){
    });


    connect(animation,&QPropertyAnimation::valueChanged,[this](){
        adjustAreaSize();
    });
    w->setVisible(false);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SourceTreeWidget::showViewWidget(QWidget *w)
{
    QPropertyAnimation * animation=new QPropertyAnimation(w,"geometry");
    animation->setDuration(100);
    animation->setStartValue(w->rect());
    //animation->setEndValue(QRect(w->x(),w->y(),w->width(),210*((w->children().size()+1)/3)+20));
    animation->setEndValue(static_cast<SourceCardViewWidget*>(w)->getShowRect());
    //animation->setEasingCurve(QEasingCurve::InOutBounce);
    connect(animation,&QPropertyAnimation::finished,[](){
    });
    connect(animation,&QPropertyAnimation::valueChanged,[this](){
        adjustAreaSize();
    });
    w->setVisible(true);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SourceTreeWidget::updateSourceWidget()
{


}

void SourceTreeWidget::wheelEvent(QWheelEvent *e)
{
    int delta=e->angleDelta().y();
    m_area->move(m_area->x(),m_area->y()+delta);
    redoMove();

}
