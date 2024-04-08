#ifndef EVENTSHOWWIDGET_H
#define EVENTSHOWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QLineEdit>

#include <TOOL/eventTool/eventsystem.h>
#include <DATA/enginestyle.h>
class EventShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EventShowWidget(QWidget *parent = nullptr);

    void initWidget(QString eventName);
    void updateWidget();
    QWidget* addIns();
    QWidget* addIns(QString insName);
protected:
    void paintEvent(QPaintEvent*e)override;
private:
    QVector<QWidget* > m_insWidget{};
    QVector<int> m_insLayer{};
    QLineEdit * m_eventBox=nullptr;
    QPushButton * m_addWidget=nullptr;

    QString m_nowEvent;
    int spacing=10;
signals:

};

#endif // EVENTSHOWWIDGET_H
