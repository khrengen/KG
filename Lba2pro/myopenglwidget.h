#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H


#include <QOpenGLWidget>
#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QtMath>





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
    void setPrg(int prj);

signals:
    void paramChanged(int param);
    void xRotChanged(int xRot);
    void yRotChanged(int yRot);
    void zRotChanged(int zRot);
    void visionChanged(int vis);
    void prgChanged(int prg);
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
    int prg = 0;
    double cPr = 1;
};

#endif // MYOPENGLWIDGET_H
