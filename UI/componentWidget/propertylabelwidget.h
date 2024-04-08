#ifndef PROPERTYLABELWIDGET_H
#define PROPERTYLABELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMetaProperty>
#include <DATA/baseClass/gameobject.h>
#include <DATA/baseClass/uiwidget.h>
#include <QVariant>

class PropertyLabelWidget : public UIWidget
{
    Q_OBJECT

private:
    QLabel* m_titleLabel=nullptr;
    QLineEdit* m_valueLabel=nullptr;
    QMetaProperty* m_linkProperty=nullptr;
    QObject* m_linkObject=nullptr;

    bool m_hotUpdate=false;

public:
    explicit PropertyLabelWidget(QWidget *parent = nullptr);
    void setRatio(double x1=4.0,double x2= 6.0,int vSpacing=10,int hHpacing=10);
    void submitValue();
    void setLink(QObject* obj,QMetaProperty* property);
    void setPair(QString title,QString value);
    void initWidget();
    void setHotUpdate(bool flag);
    void setUIStyle()override;
    void paintEvent(QPaintEvent* e)override;
signals:

};

#endif // PROPERTYLABELWIDGET_H
