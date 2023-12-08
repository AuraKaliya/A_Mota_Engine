#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <ui/componentWidget/wheelslidewidget.h>
#include <QPushButton>
#include <QVector>

class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidget(QWidget *parent = nullptr);

    void setRatio(int headHeight,int bodyHeight);


   QPushButton* addBtnToHead(QPushButton* btn);
   QWidget* addWidgetToBody(QWidget* widget);


   void updateWidget();

   int headSpacing() const;
   void setHeadSpacing(int newHeadSpacing);

   int bodyWidgetSpacing() const;
   void setBodyWidgetSpacing(int newBodyWidgetSpacing);

   int headBtnSize() const;
   void setHeadBtnSize(int newHeadBtnSize);
   protected:
   void resizeEvent(QResizeEvent* e);
private:
    WheelSlideWidget* m_headWidget=nullptr;
    WheelSlideWidget* m_bodyWidget=nullptr;

    int m_headSpacing=5;
    int m_headBtnSize=50;


    int m_bodyWidgetSpacing=5;

    QVector<QPushButton*> m_headBtnList{};
    QVector<QWidget*> m_bodyWidgetList{};





signals:

};

#endif // TOOLWIDGET_H
