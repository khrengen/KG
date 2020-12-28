#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H


#include <QOpenGLWidget>
#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QtMath>
#include "spline.h"





class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);

public slots:
    void setXRot(int xRot);
    void setYRot(int yRot);
    void setZRot(int zRot);
    void setParam(int param);
    void setApro(int apro);
    void setxa1(int x);
    void setya1(int x);
    void setza1(int x);
    void setxa2(int x);
    void setya2(int x);
    void setza2(int x);
    void setxa3(int x);
    void setya3(int x);
    void setza3(int x);
    void setxa4(int x);
    void setya4(int x);
    void setza4(int x);

    void setxb1(int x);
    void setyb1(int x);
    void setzb1(int x);
    void setxb2(int x);
    void setyb2(int x);
    void setzb2(int x);
    void setxb3(int x);
    void setyb3(int x);
    void setzb3(int x);
    void setxb4(int x);
    void setyb4(int x);
    void setzb4(int x);


signals:
    void xRotChanged(int xRot);
    void yRotChanged(int yRot);
    void zRotChanged(int zRot);
    void paramChanged(int param);
    

protected:
    void calcInit();
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    void drawSurface(spline& s1, spline& s2);
    virtual void paintGL();
private:   
    GLfloat c = 0.65;
    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;
    int p = 10;
    spline spl;
    spline spl2;
    GLfloat xa1=-2, xa2=0, xa3=1, xa4=2, xb1=-2, xb2=-1, xb3=2, xb4=3;
    GLfloat ya1=-3, ya2=-1, ya3=3, ya4=1, yb1=0, yb2=1, yb3=-3, yb4=-1;
    GLfloat za1=-2, za2=-2, za3=-2, za4=-2, zb1=2, zb2=2, zb3=2, zb4=2;

};

#endif // MYOPENGLWIDGET_H
