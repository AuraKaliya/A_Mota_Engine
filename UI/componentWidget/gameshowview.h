#ifndef GAMESHOWVIEW_H
#define GAMESHOWVIEW_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QVector2D>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QOpenGLTexture>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include <DATA/enginestyle.h>

class GameShowView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameShowView(QWidget *parent = nullptr);
protected:
    //
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mouseMoveEvent(QMouseEvent*e)override;
    void mouseReleaseEvent(QMouseEvent* e)override;
    void paintEvent(QPaintEvent* e)override;
private:
    QRect m_selectRect;
signals:
    void getFocus();
    void loseFocus();
};

#endif // GAMESHOWVIEW_H
