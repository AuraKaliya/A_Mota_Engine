#include "diybutton.h"
#include "qpainter.h"


QMap<QString,QRgb> DIYButton::s_colorDictionary={
    {"SkyBlue",qRgb(135, 206, 235)},
    {"LawnGreen",qRgb(124, 252, 0)},
    {"ScarletRed",qRgb(255, 36, 0)},
    {"DeepPink",qRgb(238, 57, 0)},
    {"Coral",qRgb(152, 135, 220)},
    {"DarkOrchid",qRgb(81, 2, 214)},
    {"DarkSalmon",qRgb(255, 255, 255)}
                                                    };


DIYButton::DIYButton(QWidget *parent)
    : QPushButton{parent}
{
    m_initialized=false;
    m_hover=false;
    //m_diyPix.setScaledContents(true);
    //setToolTip("Tip！~");

}

DIYButton::DIYButton(QString str, QWidget *parent):DIYButton{parent}
{
    m_colorStyle=str;
//    m_initialized=false;
//    m_hover=false;

}

void DIYButton::setPix(QPixmap pix)
{
    if(pix.isNull())
    {
        return;
    }
    m_diyPix=pix;
    m_initialized=true;
}

void DIYButton::setPix(QString path)
{
    m_diyPix.load(path);

    if(m_diyPix.isNull())
        return;

    m_initialized=true;
    initStyle(m_colorStyle);
}

void DIYButton::initStyle(QString color)
{

    auto res=s_colorDictionary.find(color);
    if(res!=s_colorDictionary.end())
    {
        m_diyColor=res.value();
    }
    else
    {
        m_diyColor=qRgb(0, 0, 0);
    }

    m_diyImg=m_diyPix.toImage();
    for(int y=0;y<m_diyImg.height();y++)
    {
        for(int x=0;x<m_diyImg.width();x++)
        {
            QRgb pixel=m_diyImg.pixel(x,y);
            if(qAlpha(pixel)>0)
            {
                m_diyImg.setPixel(x,y,m_diyColor);
            }
        }
    }
    m_hoverPix=QPixmap::fromImage(QImage(m_diyImg));
}

void DIYButton::paintEvent(QPaintEvent *e)
{
    //QPushButton::paintEvent(e);
    QPainter painter(this);
    int scale=qMin(width(),height());
    int x=(width()-scale)/2;
    int y=(height()-scale)/2;
    if(m_initialized)
    {
    if(m_hover)
    {
         painter.drawPixmap(QRect(x,y,scale,scale),m_hoverPix);
    }
    else
    {
         painter.drawPixmap(QRect(x,y,scale,scale),m_diyPix);
    }

    }


}

void DIYButton::enterEvent(QEnterEvent *e)
{
    m_hover=true;
}

void DIYButton::leaveEvent(QEvent *e)
{
    m_hover=false;
}
