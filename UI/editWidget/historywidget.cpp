#include "historywidget.h"

#include <QTextCursor>

HistoryWidget::HistoryWidget(QWidget *parent)
    : UIWidget{parent}
{
    setFixedSize(545,210);
    setVisible(true);


    m_historyShowView=new QTextEdit(this);
    m_historyShowView->setVisible(true);
    m_historyShowView->setWordWrapMode(QTextOption::WrapAnywhere);
    m_historyShowView->setReadOnly(true);

    m_historyShowView->setGeometry(0,0,width(),height());
    //m_historyShowView
    setUIStyle();
}

void HistoryWidget::setUIStyle()
{
    setStyleSheet("background-color:white");
}

void HistoryWidget::addAction(QString str)
{
    QString header="[Act] ";
    QTextCursor cursor(m_historyShowView->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat fmt;
    fmt.setForeground(QBrush(Qt::red));
    cursor.setCharFormat(fmt);
    cursor.insertText(header);
    fmt.setForeground(QBrush(Qt::black));
    cursor.setCharFormat(fmt);
    cursor.insertText(str);
    cursor.insertText("\n");
    m_historyShowView->setTextCursor(cursor);

}

void HistoryWidget::addInstruction(QString str)
{
    QString header="[Ins] ";
    QTextCursor cursor(m_historyShowView->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat fmt;

    fmt.setForeground(QBrush(Qt::blue));

    cursor.setCharFormat(fmt);
    cursor.insertText(header);
    fmt.setForeground(QBrush(Qt::black));
    cursor.setCharFormat(fmt);
    cursor.insertText(str);
    cursor.insertText("\n");
    m_historyShowView->setTextCursor(cursor);
}

void HistoryWidget::addEvent(QString str)
{
    QString header="[Evn] ";
    QTextCursor cursor(m_historyShowView->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat fmt;

    fmt.setForeground(QBrush(Qt::green));

    cursor.setCharFormat(fmt);
    cursor.insertText(header);
    fmt.setForeground(QBrush(Qt::black));
    cursor.setCharFormat(fmt);
    cursor.insertText(str);
    cursor.insertText("\n");
    m_historyShowView->setTextCursor(cursor);
}

void HistoryWidget::addError(QString str)
{

}
