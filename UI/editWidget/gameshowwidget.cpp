#include "gameshowwidget.h"

#include <QDragEnterEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QMimeData>
#include <QPushButton>
#include <DATA/baseClass/gameobjectitem.h>

#pragma execution_character_set("utf-8")
GameShowWidget::GameShowWidget(QWidget *parent)
    :UIWidget{parent}
{

    setFixedSize(1050,800);
    setVisible(true);
    m_gameShowView=new GameShowView(this);
    m_gameShowView->setFixedSize(1050,750);
    m_gameShowView->setVisible(true);

    dropWidget=new GameObjectDropWidget(this);
    dropWidget->setGeometry(0,0,1050,750);
    dropWidget->setLinkView(m_gameShowView);
    dropWidget->raise();


    setFocusPolicy(Qt::ClickFocus);

    connect(m_gameShowView,&GameShowView::getFocus,this,[this](){
        dropWidgetHide();
    });
    connect(m_gameShowView,&GameShowView::loseFocus,this,[this](){
        dropWidgetShow();
    });

    connect(EditSystem::getInstance()->getManager(),&EditManager::nowSceneChanged,this,[this](int i){
       init();
    });

    setUIStyle();
}

void GameShowWidget::init()
{
    m_gameShowView->setScene(EditSystem::getInstance()->getManager()->getNowScene());
    //m_gameShowView->sceneRect()
    m_gameShowView->centerOn(QPointF((m_gameShowView->width()-2)/2,(m_gameShowView->height()-2)/2));
    //qDebug()<<"Scene:"<<

}

void GameShowWidget::demoInit()
{
    if(nowDemo()!=nullptr)
    {
        if(nowDemo()->objectName()=="Mota")
        {
            //mota 相关
            QVector<QWidget*> list;
            m_demoDataWidget=new QWidget(this);
            m_demoDataWidget->setGeometry(0,750,1050,50);

            QHBoxLayout * layout =new QHBoxLayout(m_demoDataWidget);

            QLabel * demoLabel=new QLabel(this);
            list.append(demoLabel);
            //demoLabel->setFixedHeight(50);
            demoLabel->setText("Demo:Mota");
            //layout->addWidget(demoLabel);

            QLabel * nowPageLabel=new QLabel(this);
            list.append(nowPageLabel);
            nowPageLabel->setText("当前:第"+QString::number(EditSystem::getInstance()->getManager()->getNowSceneIdx()+1)+"页");
            //pagesLabel->setFixedHeight(50);
            connect(EditSystem::getInstance()->getManager(),&EditManager::nowSceneChanged,this,[nowPageLabel](int i){
                nowPageLabel->setText("当前:第"+QString::number(EditSystem::getInstance()->getManager()->getNowSceneIdx()+1)+"页");
                //nowPageLabel->adjustSize();
            });

            QLabel * pagesLabel=new QLabel(this);
            list.append(pagesLabel);
            pagesLabel->setText("总计:"+QString::number(EditSystem::getInstance()->getManager()->getScenesCount())+"页");
            //pagesLabel->setFixedHeight(50);
            connect(EditSystem::getInstance()->getManager(),&EditManager::sceneCountChanged,this,[pagesLabel](){
                pagesLabel->setText("总计:"+QString::number(EditSystem::getInstance()->getManager()->getScenesCount())+"页");
                //pagesLabel->adjustSize();
            });


            QLabel * sceneSizeLabel=new QLabel(this);
            list.append(sceneSizeLabel);
            sceneSizeLabel->setText("预置大小:"+QString::number(EditSystem::getInstance()->getManager()->getSceneRect().width())+"X"+QString::number(EditSystem::getInstance()->getManager()->getSceneRect().height()));
            connect(EditSystem::getInstance()->getManager(),&EditManager::sceneSizeChanged,this,[sceneSizeLabel](){
                sceneSizeLabel->setText("预置大小:"+QString::number(EditSystem::getInstance()->getManager()->getSceneRect().width())+"X"+QString::number(EditSystem::getInstance()->getManager()->getSceneRect().height()));
                //pagesLabel->adjustSize();
            });

            QLabel * nowSceneSizeLabel=new QLabel(this);
            list.append(nowSceneSizeLabel);
            nowSceneSizeLabel->setText("当前大小:"+QString::number(EditSystem::getInstance()->getManager()->getNowSceneRect().width())+"X"+QString::number(EditSystem::getInstance()->getManager()->getNowSceneRect().height()));
            connect(EditSystem::getInstance()->getManager(),&EditManager::nowSceneChanged,this,[nowSceneSizeLabel](int i){
                nowSceneSizeLabel->setText("当前大小:"+QString::number(EditSystem::getInstance()->getManager()->getNowSceneRect().width())+"X"+QString::number(EditSystem::getInstance()->getManager()->getNowSceneRect().height()));
                //nowPageLabel->adjustSize();
            });

            QPushButton * addBtn=new QPushButton(this);
            list.append(addBtn);
            addBtn->setText("新建场景");
            connect(addBtn,&QPushButton::clicked,this,[](){
                EditSystem::getInstance()->getManager()->addScene();
            });

            for(auto it:list)
            {
                it->setFixedHeight(30);
                layout->addWidget(it);
            }

            m_demoDataWidget->setLayout(layout);
            m_demoDataWidget->setVisible(true);
        }
    }




}

void GameShowWidget::dropWidgetShow()
{
    dropWidget->resize(1050,750);
    dropWidget->setEnabled(true);
    dropWidget->show();
    dropWidget->raise();
}

void GameShowWidget::dropWidgetHide()
{
    dropWidget->resize(0,0);
    dropWidget->setEnabled(false);
    dropWidget->hide();
}

void GameShowWidget::setUIStyle()
{

    if(EngineStyle::getInstance()->styleName()=="Night")
    {
        m_gameShowView->setBackgroundBrush(QBrush(Qt::darkGray));
    }
    else
    {
        m_gameShowView->setBackgroundBrush(QBrush(Qt::white));
    }

}

void GameShowWidget::mouseMoveEvent(QMouseEvent *e)
{
    m_mousePos=e->pos();
}

void GameShowWidget::focusInEvent(QFocusEvent *event)
{
    if(!m_gameShowView->hasFocus())
    {
        dropWidgetHide();
    }
}

void GameShowWidget::focusOutEvent(QFocusEvent *event)
{
    if(focusWidget()!=m_gameShowView)
    {
        dropWidgetShow();
    }
}

void GameShowWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void GameShowWidget::paintEvent(QPaintEvent *e)
{
//    qDebug()<<"GameShowWidget::paintEvent";
//    QPainter painter(this);
//    if(!m_gameShowView->scene()->selectedItems().empty())
//    {
//        QRect rect;
//        //绘制item选中
//        rect.setRect(m_gameShowView->mapFromScene(m_gameShowView->scene()->selectedItems()[0]->pos()).x()-(m_gameShowView->width()-m_gameShowView->scene()->width())/2,
//                     m_gameShowView->mapFromScene(m_gameShowView->scene()->selectedItems()[0]->pos()).y()-(m_gameShowView->height()-m_gameShowView->scene()->height())/2,
//                     0,0);

//        for(auto it:m_gameShowView->scene()->selectedItems())
//        {
//            //rect.setY(qMin((int)rect.y(),(int)m_gameShowView->mapFromScene(it->pos()).y()));
//            rect.setX(qMin((int)rect.x(),(int)(m_gameShowView->mapFromScene(it->pos()).x()-(m_gameShowView->width()-m_gameShowView->scene()->width())/2)));
//            //rect.setY(qMin((int)rect.y(),(int)m_gameShowView->mapFromScene(it->pos()).y()));
//            rect.setY(qMin((int)rect.y(),(int)(m_gameShowView->mapFromScene(it->pos()).y()-(m_gameShowView->height()-m_gameShowView->scene()->height())/2)));
//            rect.setWidth(qMax((int)rect.width(),(int)(it->x()+it->boundingRect().width()-rect.x())));
//            rect.setHeight(qMax((int)rect.height(),(int)(it->y()+it->boundingRect().height()-rect.y())));
//        }
//        qDebug()<<"GameShowWidget::rect:"   <<rect;

//        QRect drawRect(rect.x()+(m_gameShowView->width()-m_gameShowView->scene()->width())/2,
//                       rect.y()+(m_gameShowView->height()-m_gameShowView->scene()->height())/2,
//                       rect.width(),
//                       rect.height()
//                       );
////        rect.setX(rect.x()+(m_gameShowView->width()-m_gameShowView->scene()->width())/2);
////        rect.setY(rect.y()+(m_gameShowView->height()-m_gameShowView->scene()->height())/2);
//        qDebug()<<"GameShowWidget::rect2 :" <<drawRect;
//        QPen pen(Qt::red,3,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);
//        painter.setPen(pen);
//        painter.drawRect(rect);
//    }
////    painter.setPen(QPen(Qt::red));
////    painter.drawRect(0,750,100,49);
//    painter.end();
   UIWidget::paintEvent(e);

//    QPainter painterBackground(this);

//    if(EngineStyle::getInstance()->styleName()=="Night")
//    {
//        painterBackground.fillRect(this->rect(), Qt::darkGray); // 深灰色背景
//    }
//    else
//    {
//        painterBackground.fillRect(this->rect(), Qt::white);// 纯白色背景
//    }
//    painterBackground.end();
}

