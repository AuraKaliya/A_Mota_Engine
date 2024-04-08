#include "testwidget.h"

TestWidget::TestWidget(QWidget *parent)
    : QMainWindow{parent}
{
//    m_viewList=new QStackedWidget(this);
//    m_viewList->move(0,0);
    m_gameShowView=new GameShowView(this);
    m_gameShowView->setVisible(true);
    setCentralWidget(m_gameShowView);


    connect(EditSystem::getInstance()->getManager(),&EditManager::nowSceneChanged,this,[this](int i){
        init();
    });


}

void TestWidget::init()
{
    //m_scenes=EditSystem::getInstance()->getManager()->getScenes();
    m_gameShowView->setScene(EditSystem::getInstance()->getManager()->getNowScene());
    m_gameShowView->centerOn(QPointF((m_gameShowView->width()-2)/2,(m_gameShowView->height()-2)/2));
    resize(m_gameShowView->sceneRect().size().width(),m_gameShowView->sceneRect().size().height());
    qDebug()<<"Check================-----"<<m_gameShowView->sceneRect();
}

void TestWidget::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
    //    m_viewList->resize(this->size());
}

void TestWidget::closeEvent(QCloseEvent *e)
{
    emit closed();
    QMainWindow::closeEvent(e);
}
