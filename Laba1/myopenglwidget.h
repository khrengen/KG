#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
 #include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QtMath>
#include <QPainter>
#include <QTextStream>




class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);

public slots:
    void setParam(int param);

signals:
    void paramChanged(int param);


protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    int c = 100;
};

#endif // MYOPENGLWIDGET_H
