#ifndef EVENTEDITWIDGET_H
#define EVENTEDITWIDGET_H

#include <QWidget>
#include <DATA/baseClass/instructionobject.h>
#include <DATA/baseClass/uiwidget.h>
#include <UI/componentWidget/wheelslidewidget.h>
#include <UI/componentWidget/toolwidget.h>

#include <TOOL/eventTool/eventsystem.h>
#include <TOOL/editTool/editsystem.h>

class EventEditWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit EventEditWidget(QWidget *parent = nullptr);

    ToolWidget *getShowWidget() const;

private:
    ToolWidget* m_showWidget=nullptr;

    QPushButton *m_addEventBtn=nullptr;
    QPushButton *m_delEventBtn=nullptr;



protected:
    void paintEvent(QPaintEvent* e)override;

signals:

};

#endif // EVENTEDITWIDGET_H
