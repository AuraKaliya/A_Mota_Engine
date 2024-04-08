#ifndef ADDSOURCEWIDGET_H
#define ADDSOURCEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <TOOL/sourceTool/sourcesystem.h>
#include <DATA/baseClass/uiwidget.h>
#include <QVector>
#include <DATA/enginestyle.h>
class AddSourceWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit AddSourceWidget(QWidget *parent = nullptr);
    void setUIStyle()override;
private:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_addSourceByFileBtn;
    QPushButton* m_addSourceByPathBtn;
    QPushButton* m_addNewGameObjectBtn;
    QPushButton* m_outPortBtn;

    QVector<QPushButton*> m_buttonList;
signals:
    void addSource();
    void addGameObject();
    void outPort();

};

#endif // ADDSOURCEWIDGET_H
