#ifndef SHOWLABELWIDGET_H
#define SHOWLABELWIDGET_H

#include <QWidget>
#include <QLabel>

class showLabelWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel* m_titleLabel=nullptr;
    QLabel* m_valueLabel=nullptr;
public:
    explicit showLabelWidget(QWidget *parent = nullptr);
    void setRatio(double x1=4.0,double x2= 6.0,int vSpacing=10,int hHpacing=10);
    void setPair(QString title,QString value);
    void initWidget();
signals:

};

#endif // SHOWLABELWIDGET_H
