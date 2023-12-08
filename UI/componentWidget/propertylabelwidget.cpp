#include "propertylabelwidget.h"

PropertyLabelWidget::PropertyLabelWidget(QWidget *parent)
    : QWidget{parent}
{
    m_titleLabel=new QLabel(this);
    m_valueLabel=new QLineEdit(this);


    connect(m_valueLabel,&QLineEdit::editingFinished,this,[this](){
        qDebug()<<"edit End";
        if(m_hotUpdate)
        {
            qDebug()<<"submit!";
            m_linkProperty->write(m_linkObject,QVariant(m_valueLabel->text()));
        }
    });


}

void PropertyLabelWidget::setRatio(double x1, double x2, int vSpacing, int hHpacing)
{
    int width=this->width()-3*hHpacing;
    int height=this->height();
    //可能出现负数情况 ---
    m_titleLabel->setGeometry(hHpacing,vSpacing,width*(x1/(x1+x2)),height-2*vSpacing);
    m_valueLabel->setGeometry(hHpacing*2+m_titleLabel->width(),vSpacing,width*(x2/(x1+x2)),height-2*vSpacing);
    update();
}

void PropertyLabelWidget::submitValue()
{
    QVariant var=QVariant::fromValue(m_valueLabel->text());
    if(m_linkProperty!=nullptr&&m_linkObject!=nullptr)
    {
        if(m_linkProperty->write(m_linkObject,var))
        {
            qDebug()<<"*********";
            qDebug()<<"Success Write"<<m_linkProperty->name()<<var;
            qDebug()<<"*********";
        }
        else
        {
            qDebug()<<"Failed to Update";
        }
    }
}

void PropertyLabelWidget::setLink(QObject *obj, QMetaProperty *property)
{
    m_linkObject=obj;
    m_linkProperty=property;

    m_titleLabel->setText(property->name());
    m_valueLabel->setText(property->read(obj).toString());

}


void PropertyLabelWidget::setPair(QString title, QString value)
{

}

void PropertyLabelWidget::initWidget()
{
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_valueLabel->setAlignment(Qt::AlignCenter);

    m_titleLabel->setStyleSheet("background-color:white;");
    m_valueLabel->setStyleSheet("background-color:white;");
}

void PropertyLabelWidget::setHotUpdate(bool flag)
{
    m_hotUpdate=flag;
}
