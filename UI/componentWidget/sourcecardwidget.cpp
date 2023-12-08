#include "sourcecardwidget.h"

#include <QDrag>
#include <QMimeData>
#include <QToolTip>

SourceCardWidget::SourceCardWidget(QWidget *parent)
    : QWidget{parent},m_dataText("")
{
    setFixedSize(90,160);
    m_iconLabel=new QLabel(this);
    m_nameLabel=new QLabel(this);


    m_iconLabel->setFixedSize(80,80);
    m_nameLabel->setFixedSize(80,40);
    m_iconLabel->move(5,10);
    m_nameLabel->move(5,105);


    m_nameLabel->setAlignment(Qt::AlignCenter);


    m_iconLabel->setVisible(true);
    m_nameLabel->setVisible(true);

    connect(this,&SourceCardWidget::selectStateChanged,this,[this](SourceCardWidget*w,bool b){
        if(b)
        {
            setStyleSheet("background-color:grey;");
        }else
        {
            setStyleSheet("background-color:white;");
        }
    });

}

bool SourceCardWidget::initCard(SourceMetaData *data)
{

    if(data==nullptr) return false;
    m_metaData=data;

    if(m_metaData->Icon!=nullptr)
        m_iconLabel->setPixmap(m_metaData->Icon->scaled(m_iconLabel->width(),m_iconLabel->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    if(m_metaData->Name!=nullptr)   
    {
        m_nameLabel->setText(m_metaData->Name);
    }

    if(m_metaData->Class.split("_")[0]=="GameObject")
        setDragable(true);

    return true;
}

void SourceCardWidget::enterEvent(QEnterEvent *e)
{
    QToolTip::showText(QCursor::pos(),m_metaData->Information);
}

void SourceCardWidget::setSelected(bool b)
{
    m_isSelected=b;
    emit selectStateChanged(this,m_isSelected);
}

bool SourceCardWidget::getSelected()
{
    return m_isSelected;
}

void SourceCardWidget::setDragable(bool able)
{
    m_dragable=able;
}

bool SourceCardWidget::getDragable()
{
    return m_dragable;
}

SourceMetaData *SourceCardWidget::getMetaData()
{
    if(m_initBySourceMetaData)
    return m_metaData;
    else
    return nullptr;
}


//void SourceCardWidget::mousePressEvent(QMouseEvent *e)
//{
//    if(e->button()==Qt::LeftButton)
//    {
//        //qDebug()<<"selected";
//        setSelected(!m_isSelected);
//    }

//}

//void SourceCardWidget::mouseMoveEvent(QMouseEvent *e)
//{

//}

//void SourceCardWidget::mouseReleaseEvent(QMouseEvent *e)
//{
//    if(m_isDraged) m_isDraged=false;

//    if(this->geometry().contains(e->pos()))
//    {
//        qDebug()<<"clicked!111";
//        emit thisClicked(this);
//    }
//}

//void SourceCardWidget::paintEvent(QPaintEvent *e)
//{

//}


