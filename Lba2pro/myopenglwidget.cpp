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

void MyOpenGLWidget::setPrg(int prj)
{
    if (prg != prj) {
        prg = prj;
        emit prgChanged(prj);
        update();
    }
}

void MyOpenGLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

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
}

void MyOpenGLWidget::paintGL()
{

    static const GLfloat coords[6][4][3] = {
          { { +2.0, -1.0, +1.0 }, { +2.0, -1.0, -1.0 },
            { +2.0, +1.0, -1.0 }, { +2.0, +1.0, +1.0 } },
          { { -2.0, -1.0, -1.0 }, { -2.0, -1.0, +1.0 },
            { -2.0, +1.0, +1.0 }, { -2.0, +1.0, -1.0 } },
          { { +2.0, -1.0, -1.0 }, { -2.0, -1.0, -1.0 },
            { -2.0, +1.0, -1.0 }, { +2.0, +1.0, -1.0 } },
          { { -2.0, -1.0, +1.0 }, { +2.0, -1.0, +1.0 },
            { +2.0, +1.0, +1.0 }, { -2.0, +1.0, +1.0 } },
          { { -2.0, -1.0, -1.0 }, { +2.0, -1.0, -1.0 },
            { +2.0, -1.0, +1.0 }, { -2.0, -1.0, +1.0 } },
          { { -2.0, +1.0, +1.0 }, { +2.0, +1.0, +1.0 },
            { +2.0, +1.0, -1.0 }, { -2.0, +1.0, -1.0 } }

      };

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

          glEnable(GL_DEPTH_TEST);
          glEnable(GL_CULL_FACE);
          if(prg){
              glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              qreal aspectratio = qreal (width()) / qreal(height());
              if (aspectratio > 1) {
                  glOrtho(-1 * aspectratio, 1 * aspectratio, -1, 1, 1, -1);
              } else {
                  glOrtho(-1, 1, -1 / aspectratio, 1 / aspectratio, 1, -1);
              }
              cPr = 0.4;
          } else {
              resizeGL(width(), height());
              glTranslatef(0.0, 0.0, -10.0);
              cPr = 1;

         }

      glRotatef(15, 1.0, 0.0, 0.0);
      glRotatef(30, 0.0, 1.0, 0.0);
      glRotatef(0, 0.0, 0.0, 1.0);
      glBegin(GL_LINES);
          glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
          glVertex3f(0, 0 , 0);
          glVertex3f(1*cPr, 0 , 0);

          glColor4f(0.00f, 1.00f, 0.00f, 1.0f);
          glVertex3f(0, 0 , 0);
          glVertex3f(0, 1*cPr , 0);

          glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
          glVertex3f(0, 0 , 0);
          glVertex3f(0, 0 , 1*cPr);
      glEnd();

      glScalef(c * cPr, c * cPr, c * cPr);
      glRotatef(xRotation, 1.0, 0.0, 0.0);
      glRotatef(yRotation, 0.0, 1.0, 0.0);
      glRotatef(zRotation, 0.0, 0.0, 1.0);

      glLineWidth(2);

      glColor4f(1.00f, 1.00f, 1.00f, 1.0f);
      for (int i = 0; i < 6; ++i) {
        glLoadName(i);
        if (vision){
            glPolygonMode (GL_FRONT, GL_LINE);
            glBegin(GL_QUADS);
        } else {
            glBegin(GL_LINE_STRIP);
        }
        for (int j = 0; j < 4; ++j) {
          glVertex3f(coords[i][j][0], coords[i][j][1], coords[i][j][2]);
        }
        glEnd();
      }


}
