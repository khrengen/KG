#include "myopenglwidget.h"
#include <QTextStream>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    :QOpenGLWidget{parent}
{

}

void MyOpenGLWidget::setParam(int param)
{
    if ((GLfloat)param != c * 100) {
        c = (GLfloat)param / 100;
        emit paramChanged(param);
        update();
    }
}

void MyOpenGLWidget::setXRot(int xRot)
{
    if (xRot != xRotation) {
        xRotation = xRot;
        emit xRotChanged(xRot);
        update();
    }
}

void MyOpenGLWidget::setYRot(int yRot)
{
    if (yRot != yRotation) {
        yRotation = yRot;
        emit xRotChanged(yRot);
        update();
    }
}

void MyOpenGLWidget::setZRot(int zRot)
{
    if (zRot != zRotation) {
        zRotation = zRot;
        emit xRotChanged(zRot);
        update();
    }
}

void MyOpenGLWidget::setVision(int vis)
{
    if (vision != vis) {
        vision = vis;
        emit visionChanged(vis);
        update();
    }
}

void MyOpenGLWidget::setApro(int n)
{
    if (n != apro) {
        apro = n;
        emit AproChanged(apro);
        update();
    }
}

void MyOpenGLWidget::setPrg(int l)
{
    if (lght != l) {
        lght = l;
        emit prgChanged(l);
        update();
    }
}

void Light(int lght) {


    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

          GLfloat light2_diffuse[] = {0.4, 0.7, 0.2};
          GLfloat light1_ambient[] = {5, 5, 5};
          GLfloat light2_position[] = {-0.7, 0.8, 1.5, 1.0};

          if (lght){
              glDisable(GL_LIGHT1);
              glEnable(GL_LIGHT2);
              glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
              glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
              glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
              glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
              glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4);

          } else {
              glDisable(GL_LIGHT2);
              glEnable(GL_LIGHT1);

              glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
          }

}

void MyOpenGLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);


}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)w / h;
    if (x > 1) {
        glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    } else {
        glFrustum(-1, 1, -1 / x, 1 / x, 4.0, 15.0);
    }
    glMatrixMode(GL_MODELVIEW);
    //Light(lght);
}

void MyOpenGLWidget::paintGL()
{


      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();
      glTranslatef(0.0, 0.0, -10.0);

      glRotatef(15, 1.0, 0.0, 0.0);
      glRotatef(30, 0.0, 1.0, 0.0);
      glRotatef(0, 0.0, 0.0, 1.0);

      glRotatef(xRotation, 1.0, 0.0, 0.0);
      glRotatef(yRotation, 0.0, 1.0, 0.0);
      glRotatef(zRotation, 0.0, 0.0, 1.0);
      Light(lght);
      glLineWidth(2);
      glColor4f(1.00f, 1.00f, 1.00f, 1.0f);

      double r = c;
      double n = M_PI/apro;

      for (double az = 0; az < 2*M_PI; az += n) {
          for (double ze = 0; ze < M_PI; ze += n) {
              glLineWidth(2);
              if (vision){
                  glBegin(GL_QUADS);
              } else {
                  glBegin(GL_LINE_STRIP);
              }
              glVertex3f(r*sin(ze)*cos(az), r*sin(ze)*sin(az), r*cos(ze));
              ze +=n;
              glVertex3f(r*sin(ze)*cos(az), r*sin(ze)*sin(az), r*cos(ze));
              az += n;
              glVertex3f(r*sin(ze)*cos(az), r*sin(ze)*sin(az), r*cos(ze));
              ze -= n;
              glVertex3f(r*sin(ze)*cos(az), r*sin(ze)*sin(az), r*cos(ze));
              az -= n;
              glVertex3f(r*sin(ze)*cos(az), r*sin(ze)*sin(az), r*cos(ze));
              glEnd();

          }

      }



}

