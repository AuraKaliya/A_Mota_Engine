#include "sourcecardviewwidget.h"

#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QPointF>

QMap<QString,doFunc> SourceCardViewWidget::m_eventSoluteDictionary={{"Default",doIgnore},{"SourceCardViewWidget",doAccept}};
void SourceCardViewWidget::registerToEventSolution(QString className)
{
    m_eventSoluteDictionary[className]=doAccept;
}

bool SourceCardViewWidget::findDragDictionary(QString className)
{
    auto it=m_eventSoluteDictionary.find(className);
    if(it!=m_eventSoluteDictionary.end())
    {
        return  true;
    }
    else
    {
        return false;
    }
    return false;
}

SourceCardViewWidget::SourceCardViewWidget(QWidget *parent)
    : QWidget{parent},m_dataText("")
{
    //setStyleSheet("background-color:blue;");


    if(parent!=nullptr)
    {
        setFixedWidth(parent->width());
    }



    m_mainLayout=new QGridLayout(this);
    reLayout();
   // m_mainLayout->set
    setLayout(m_mainLayout);
}

SourceCardViewWidget::SourceCardViewWidget(ViewClass cardType, QWidget *parent):SourceCardViewWidget(parent)
{
    qDebug()<<"hhhha";
    m_cardType=cardType;
}

void SourceCardViewWidget::addCardWidget(SourceCardWidget *w)
{
    //w->move((m_cardWidgetList.size()%3)*(w->width()+5)+10,(m_cardWidgetList.size()/3)*(w->height()+5)+10);
    w->setParent(this);
    m_mainLayout->addWidget(w,m_cardWidgetList.size()/3,m_cardWidgetList.size()%3);
    //m_mainLayout->addWidget(w);
    m_cardWidgetList.append(w);
#if 0
    qDebug()<<"*************";
    qDebug()<<"m_cardWidgetList.size()"<<m_cardWidgetList.size();
    qDebug()<<"this class"<<(int)m_cardType;
    qDebug()<<"*************";
#endif

    adjustSize();
    m_rect=this->rect();
}

void SourceCardViewWidget::delCardWidget(SourceCardWidget *w)
{
    //remove不改变parent和存在状态
    m_cardWidgetList.removeOne(w);
    m_mainLayout->removeWidget(w);
    w->setParent(nullptr);
    w->setVisible(false);
    adjustSize();
    m_rect=this->rect();
    emit widgetDeleted(w);
    reLayout();
}

void SourceCardViewWidget::reLayout()
{
    QGridLayout* layout=new QGridLayout(this);
    for(int i=0;i<m_cardWidgetList.size();++i)
    {
        m_mainLayout->removeWidget(m_cardWidgetList[i]);
        m_cardWidgetList[i]->setParent(this);
        layout->addWidget(m_cardWidgetList[i],i/3,i%3);
    }
    qDebug()<<(this->layout());
    if(this->layout()!=nullptr)
    {
        delete this->layout();
    }
    m_mainLayout=layout;
    m_mainLayout->setHorizontalSpacing(15);
    m_mainLayout->setVerticalSpacing(10);
    setLayout(m_mainLayout);

}

void SourceCardViewWidget::delCardWidget(int idx)
{

}

int SourceCardViewWidget::findWidget(SourceCardWidget *w)
{
    return 0;
}

void SourceCardViewWidget::initWidget()
{
    for(auto it:m_cardWidgetList)
    {
        m_cardWidgetList.removeOne(it);
        it->setParent(nullptr);
        it->setVisible(false);
        it->deleteLater();
    }
    m_selectWidgetList.clear();
    m_nowSelectWidget=nullptr;
}

void SourceCardViewWidget::setLinkLabel(QLabel *l)
{
    m_linkLabel=l;
}

void SourceCardViewWidget::updateSelectRect()
{
    if(!m_selectWidgetList.empty())
    {
        int maxWidth=0;
        int maxHeight=0;
        for(auto it:m_selectWidgetList)
        {
            maxWidth=qMax(maxWidth,it->x()+it->width()-m_selectWidgetList[0]->x());
            maxHeight=qMax(maxHeight,it->y()+it->height()-m_selectWidgetList[0]->y());
        }
        m_selectRect.setRect(m_selectWidgetList[0]->x(),
                             m_selectWidgetList[0]->y(),
                             maxWidth,
                             maxHeight);

    }else
    {
        m_selectRect.setRect(m_selectRect.x(),m_selectRect.y(),0,0);
    }

    update();
}

void SourceCardViewWidget::resetSelectedState()
{
    m_selectState=NoSelect;
    for(auto it:m_selectWidgetList)
    {
        it->setSelected(false);
    }
    m_selectWidgetList.clear();
    m_nowSelectWidget=nullptr;
    update();
}

void SourceCardViewWidget::dragEnterEvent(QDragEnterEvent *e)
{
    //当拖放事件进入时，选择性处理事件。（主动过滤）
    const QMimeData* data=e->mimeData();
    if(data->hasText())
    {
        qDebug()<<data->text();
        if(findDragDictionary(data->text()))
        {
            e->accept();
        }
        else
        {
            e->ignore();
        }
    }
}

void SourceCardViewWidget::dropEvent(QDropEvent *e)
{
    //接受事件后，进行的处理逻辑
    //行为判断，目前只提供一个移动行为
    e->dropAction();
    const QMimeData* data=e->mimeData();
    if(data->hasFormat("Count"))
    {
        int count=data->data("Count").toInt();
        if(data->hasFormat("ViewClass"))
        if(data->data("ViewClass").toInt()!=(int)m_cardType)
        {
            qDebug()<<"只能同类型拖拽";
            return;
        }

        if(data->hasFormat("Link"))
        if(QString::fromLocal8Bit(data->data("Link"))==QString(m_linkLabel->text()))
        {
            qDebug()<<"忽略自己拖自己";
            qDebug()<<"this:"<<m_linkLabel<<m_linkLabel->text();
            qDebug()<<"data:"<<QString::fromLocal8Bit(data->data("Link"));
            return;
        }

        for(int i=0;i<count;++i)
        {
            if(data->data("Error_"+QString::number(i)).toInt()==0)
            {
                SourceCardWidget *card=new SourceCardWidget(this);
                    //开始添加指定内容
                if(QString::fromLocal8Bit(data->data("Class_"+QString::number(i))).split("_")[0]=="GameObject")
                {   //GO
                    qDebug()<<"######"<<data->data("Gid_"+QString::number(i)).toInt();
                    if(data->data("Gid_"+QString::number(i)).toInt()>0)
                    {
                        card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromGOById(data->data("Gid_"+QString::number(i)).toInt()));
                    }else
                    {
                        card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromGOSourceByName(data->data("Name_"+QString::number(i))));
                    }

                }
                else
                {
                    card->initCard(SourceSystem::getInstance()->getManager()->getSourceMetaDataFromPixById(data->data("Gid_"+QString::number(i)).toInt()));
                }

                card->setVisible(true);
                addCardWidget(card);
            }
            else
            {
                //该部分出错，进入错误处理逻辑
                //目前忽略
            }

        }
        emit dropDataSoluted();
    }
    else
    {
        qDebug()<<"无效数据";
    }

}

void SourceCardViewWidget::mousePressEvent(QMouseEvent *e)
{

    if(e->button()==Qt::LeftButton)
    {
        emit nowFocusWidget(this);

        if(m_selectState!=NoSelect&&m_selectRect.contains(e->pos())&&!m_selectWidgetList.empty())
        {
            //已选中，且鼠标在选中框内开始拖拽
            m_dragState=true;
            QDrag *drag=new QDrag(this);
            QMimeData * data=new QMimeData;

            //标记widget的类型，表示从该widget中拖出的数据

            data->setText("SourceCardViewWidget");

            for(int i=0;i<m_selectWidgetList.size();++i)
            {
                SourceMetaData* metaData=m_selectWidgetList[i]->getMetaData();
                QString IdxStr=QString::number(i);
                if(metaData!=nullptr)
                {
                    data->setData("Gid_"+IdxStr,QByteArray::number(metaData->Gid));
                    data->setData("Name_"+IdxStr,metaData->Name.toLocal8Bit());
                    data->setData("Class_"+IdxStr,metaData->Class.toLocal8Bit());
                }
                else
                {
                    data->setData("Error_"+IdxStr,QByteArray::number(-1));
                }
            }
            data->setData("Count",QByteArray::number(m_selectWidgetList.size()));
            data->setData("ViewClass",QByteArray::number((int)m_cardType));
            if(m_linkLabel!=nullptr)
            {
                data->setData("Link",m_linkLabel->text().toLocal8Bit());
            }
            else
            {
                data->setData("Link",QString("NoLink").toLocal8Bit());
            }
            drag->setMimeData(data);
            emit dropStart(this);
            drag->exec();
        }else
        {
            m_mousePressedState=true;
            QPointF startPoint=e->globalPosition();
            m_selectStartPoint.setX(startPoint.x()-mapToGlobal(this->pos()).x()+this->x());
            m_selectStartPoint.setY(startPoint.y()-mapToGlobal(this->pos()).y()+this->y());
            m_selectRect.setRect(m_selectStartPoint.x(),m_selectStartPoint.y(),1,1);
        }
    }
}

void SourceCardViewWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_mousePressedState&&!m_dragState)
    {
        m_selectState=MultipleSelect;
        QPointF desPoint=e->globalPosition();
        m_selectEndPoint.setX(desPoint.x()-mapToGlobal(this->pos()).x()+this->x());
        m_selectEndPoint.setY(desPoint.y()-mapToGlobal(this->pos()).y()+this->y());
        m_selectRect.setRect(
            qMin(m_selectEndPoint.x(),m_selectStartPoint.x()),qMin(m_selectEndPoint.y(),m_selectStartPoint.y()),
            qAbs(m_selectEndPoint.x()-m_selectStartPoint.x()),qAbs(m_selectEndPoint.y()-m_selectStartPoint.y())
            );
        update();
    }

}

void SourceCardViewWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_dragState)
    {
        m_dragState=false;
        //代表已经将选中的内容拖动过去了
    }
    m_mousePressedState=false;
    //鼠标停下时，将区域内的CardWidget加入选择队列中。
    QRect posRect(e->pos().x(),e->pos().y(),1,1);
    if(this->rect().contains(posRect)||m_selectState)
    {
        //有一个更优的算法：预测GridLayout的逻辑，直接通过Rect将对应的widget加入容器中  ---GridLayout可变排列
        //这里采用暴力选取，因为没多少个（大概
        for(int i=0;i<m_cardWidgetList.size();++i)
        {
            if(m_selectRect.contains(m_cardWidgetList[i]->geometry()))
            {
                resetSelectedState();
                m_selectState=MultipleSelect;
                int j=i;
                while(j<m_cardWidgetList.size())
                {
                    if(m_selectRect.contains(m_cardWidgetList[j]->geometry()))
                    {
                        m_cardWidgetList[j]->setSelected(true);
                        m_selectWidgetList.append(m_cardWidgetList[j]);
                    }
                    j++;
                }
                updateSelectRect();
                break;
            }
            else if(m_cardWidgetList[i]->geometry().contains(m_selectRect))
            {
                if(m_cardWidgetList[i]->getSelected())
                {
                    m_selectState=NoSelect;
                    m_cardWidgetList[i]->setSelected(false);
                    resetSelectedState();
                }else
                {
                    resetSelectedState();
                    m_selectState=SingleSelect;
                    m_cardWidgetList[i]->setSelected(true);
                    m_selectWidgetList.append(m_cardWidgetList[i]);
                }
                break;
            }else
            {
                resetSelectedState();
            }
        }
    }
    updateSelectRect();
    update();
}

void SourceCardViewWidget::dragMoveEvent(QDragMoveEvent *e)
{

}

void SourceCardViewWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    if(m_selectState!=NoSelect)
    //if(1)
    {
        QPen pen(Qt::red,3,Qt::DashDotLine,Qt::RoundCap,Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawRect(m_selectRect);
        painter.end();
    }

}

void SourceCardViewWidget::resizeEvent(QResizeEvent *e)
{
    emit widgetResized();
    QWidget::resizeEvent(e);
}

SourceCardViewWidget::ViewClass SourceCardViewWidget::getCardType() const
{
    return m_cardType;
}

void SourceCardViewWidget::setCardType(ViewClass newCardType)
{
    if (m_cardType == newCardType)
        return;
    m_cardType = newCardType;
    emit cardTypeChanged();
}

void SourceCardViewWidget::clearSelectWidget()
{
    for(auto it:m_selectWidgetList)
    {
        delCardWidget(it);
    }
    m_selectWidgetList.clear();
    updateSelectRect();
}

QRect SourceCardViewWidget::getShowRect()
{
    return m_rect;
}
