#ifndef DIYBUTTON_H
#define DIYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QImage>
#include <QString>
#include <QPaintEvent>
#include <QEnterEvent>
#include <QEvent>
#include <QRgb>
#include <QMap>
class DIYButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DIYButton(QWidget *parent = nullptr);
    explicit DIYButton(QString str,QWidget *parent = nullptr);
    void setPix(QPixmap pix);
    void setPix(QString path);
    void initStyle(QString color);
protected:
    void paintEvent(QPaintEvent* e)override;
    void enterEvent(QEnterEvent* e)override;
    void leaveEvent(QEvent* e)override;
private:


    static QMap<QString,QRgb> s_colorDictionary;

    QPixmap m_diyPix;
    QPixmap m_hoverPix;
    QImage m_diyImg;
    bool m_initialized;
    bool m_hover;
    QRgb m_diyColor;
    QString m_colorStyle;

signals:

};

#endif // DIYBUTTON_H
