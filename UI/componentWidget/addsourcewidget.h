#ifndef ADDSOURCEWIDGET_H
#define ADDSOURCEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <TOOL/sourceTool/sourcesystem.h>


class AddSourceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddSourceWidget(QWidget *parent = nullptr);
private:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_addSourceByFileBtn;
    QPushButton* m_addSourceByPathBtn;
    QPushButton* m_addNewGameObjectBtn;
signals:
    void addSource();
    void addGameObject();
};

#endif // ADDSOURCEWIDGET_H
