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
#include <GL/GLU.h>






class MyOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);

public slots:
    void setParam(int param);
    void setXRot(int xRot);
    void setYRot(int yRot);
    void setZRot(int zRot);
    void setVision(int vis);
    void setApro(int n);
    void setPrg(int l);

signals:
    void paramChanged(int param);
    void xRotChanged(int xRot);
    void yRotChanged(int yRot);
    void zRotChanged(int zRot);
    void visionChanged(int vis);
    void AproChanged(int n);
    void prgChanged(int l);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    GLfloat c = 1;
    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;
    int vision = 0;
    int lght = 0;
    int apro = 10;
};

#endif // MYOPENGLWIDGET_H
