#include "showlabelwidget.h"

showLabelWidget::showLabelWidget(QWidget *parent)
    : QWidget{parent}
{
    m_titleLabel=new QLabel(this);
    m_valueLabel=new QLabel(this);

    setStyleSheet("background-color:grey;");
}

void showLabelWidget::setRatio(double x1, double x2,int vSpacing,int hHpacing)
{
    int width=this->width()-3*hHpacing;
    int height=this->height();

    //可能出现负数情况 ---
    m_titleLabel->setGeometry(hHpacing,vSpacing,width*(x1/(x1+x2)),height-2*vSpacing);
    m_valueLabel->setGeometry(hHpacing*2+m_titleLabel->width(),vSpacing,width*(x2/(x1+x2)),height-2*vSpacing);
    update();
}

void showLabelWidget::setPair(QString title, QString value)
{
    qDebug()<<title<<value;
    qDebug()<<m_titleLabel<<m_valueLabel;
    m_titleLabel->setText(title);
    m_valueLabel->setText(value);
}

void showLabelWidget::initWidget()
{
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_valueLabel->setAlignment(Qt::AlignCenter);

    m_titleLabel->setStyleSheet("background-color:white;");
    m_valueLabel->setStyleSheet("background-color:white;");
}
