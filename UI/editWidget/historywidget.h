#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include<DATA/baseClass/uiwidget.h>
#include <QTextEdit>
#include <QTextCharFormat>

#pragma execution_character_set("utf-8")
class HistoryWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit HistoryWidget(QWidget *parent = nullptr);
    void setUIStyle()override;
public slots:
  void addAction(QString str);
  void addInstruction(QString str);
  void addEvent(QString str);
  void addError(QString str);
private:
    QTextEdit * m_historyShowView=nullptr;
signals:

};

#endif // HISTORYWIDGET_H
