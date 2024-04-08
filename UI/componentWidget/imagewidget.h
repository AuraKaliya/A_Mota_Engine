#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* e)override;
    void setImagePath(QString imgPath);
private:
    QString m_imgPath;
signals:

};

#endif // IMAGEWIDGET_H
