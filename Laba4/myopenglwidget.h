#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H


#include <QOpenGLWidget>
#include <QGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QtMath>
#include <QGLFunctions>


class MyOpenGLWidget : public QOpenGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);

    struct TVertex {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

public slots:
    void setParam(int param);
    void setXRot(int xRot);
    void setYRot(int yRot);
    void setZRot(int zRot);
    void setVision(int vis);
    void setApro(int n);
    void setPrg(int l);
    void setShine(int s);
    void setColorR(int c);
    void setColorG(int c);
    void setColorB(int c);

signals:
    void paramChanged(int param);
    void xRotChanged(int xRot);
    void yRotChanged(int yRot);
    void zRotChanged(int zRot);
    void visionChanged(int vis);
    void AproChanged(int n);
    void prgChanged(int l);
    void shineChanged(int s);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void Light();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    GLfloat c = 1;
    int xRotation = 0;
    int yRotation = 0;
    int zRotation = 0;
    int vision = 0;
    int lght = 1;
    int apro = 10;
    int shine = 7;
    int rCol = 4;
    int gCol = 7;
    int bCol = 2;
    float xPos = -0.5;
    float yPos = 0.8;

    QPoint lastPos;
    unsigned int VBO;
    unsigned int VBOn;
};

#endif // MYOPENGLWIDGET_H
