#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H


#include <QOpenGLWidget>
#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QtMath>
#include <QPainter>
#include <QPainterPath>


class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);

public slots:

signals:

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void drawSpline(std::vector<GLfloat> &cf1, std::vector<GLfloat> &cf2, std::vector<GLfloat> &cf3, std::vector<GLfloat> &cf4);
    void buildSpline();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    GLfloat x1 = 80; GLfloat y1 = 320;
    GLfloat x2 = 600; GLfloat y2 = 320;
    GLfloat x3 = 1200; GLfloat y3 = 320;
    QPoint lastPos;
    GLfloat df0x = 80; GLfloat df0y = 400;
    GLfloat df2x = 1200; GLfloat df2y = 240;

};

#endif // MYOPENGLWIDGET_H
