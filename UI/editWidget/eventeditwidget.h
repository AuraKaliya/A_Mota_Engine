#ifndef EVENTEDITWIDGET_H
#define EVENTEDITWIDGET_H

#include <QWidget>
#include <DATA/baseClass/instructionobject.h>
#include <DATA/baseClass/uiwidget.h>
#include <UI/componentWidget/wheelslidewidget.h>
#include <UI/componentWidget/toolwidget.h>

#include <TOOL/eventTool/eventsystem.h>
#include <TOOL/editTool/editsystem.h>
#include <DATA/enginestyle.h>
#include <UI/componentWidget/diybutton.h>
class EventEditWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit EventEditWidget(QWidget *parent = nullptr);

    ToolWidget *getShowWidget() const;
    void setUIStyle()override;
private:
    ToolWidget* m_showWidget=nullptr;

    QPushButton *m_addEventBtn=nullptr;
    QPushButton *m_delEventBtn=nullptr;



protected:
    void paintEvent(QPaintEvent* e)override;

signals:

};

#endif // EVENTEDITWIDGET_H
