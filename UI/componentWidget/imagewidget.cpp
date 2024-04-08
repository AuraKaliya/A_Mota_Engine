#include "imagewidget.h"
#include<QPainter>
ImageWidget::ImageWidget(QWidget *parent)
    : QWidget{parent}
{
    m_imgPath="";
}

void ImageWidget::paintEvent(QPaintEvent *e)
{


    if(m_imgPath!="")
    {
        QPainter painter(this);
        painter.drawImage(this->rect(),QImage(m_imgPath));
    }

}

void ImageWidget::setImagePath(QString imgPath)
{
    m_imgPath=imgPath;
}
