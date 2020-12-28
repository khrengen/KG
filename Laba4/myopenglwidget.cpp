#include "myopenglwidget.h"


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

void MyOpenGLWidget::setShine(int s)
{
    if (shine != s) {
        shine = s;
        emit prgChanged(s);
        update();
    }
}

void MyOpenGLWidget::setColorR(int c)
{
    if (rCol != c) {
        rCol = c;
        update();
    }
}

void MyOpenGLWidget::setColorG(int c)
{
    if (gCol != c) {
        gCol = c;
        update();
    }
}

void MyOpenGLWidget::setColorB(int c)
{
    if (bCol != c) {
        bCol = c;
        update();
    }
}

void MyOpenGLWidget::Light() {

    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat material_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat material_ambient[] = {0.3, 0.3, 0.3, 1.0};
    float shininess = 0.1 * shine * 128;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialf (GL_FRONT,GL_SHININESS, shininess);

    float r =rCol * 0.1;
    float g =gCol * 0.1;
    float b =bCol * 0.1;
    GLfloat light2_diffuse[] = {r, g, b};
    GLfloat light2_ambient[] = {r, g, b};
    GLfloat light3_specular[] = {r, g, b};
    GLfloat light1_ambient[] = {4, 4, 4};
    GLfloat light2_position[] = {-0.5, 0.8, 2.5, 1.0};

    GLfloat light3_position[] = {xPos, yPos, 2.5, 1.0};
    if (lght){
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);

        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);

        glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
        glLightfv(GL_LIGHT3, GL_POSITION, light3_position);

        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.3);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);

        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.4);
        glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.2);
     } else {
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
     }

}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    xPos += dx * 0.01;
    yPos -= dy * 0.01;
    update();

    lastPos = event->pos();
}


void MyOpenGLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glMatrixMode(GL_MODELVIEW);

    initializeGLFunctions();
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBOn);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)w / h;
    if (x > 1) {
        glFrustum(-x, x, -1.0, 1.0, 5.0, 15.0);
    } else {
        glFrustum(-1, 1, -1 / x, 1 / x, 5.0, 15.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);

    Light();
    glRotatef(15, 1.0, 0.0, 0.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    glRotatef(0, 0.0, 0.0, 1.0);

    glRotatef(xRotation, 1.0, 0.0, 0.0);
    glRotatef(yRotation, 0.0, 1.0, 0.0);
    glRotatef(zRotation, 0.0, 0.0, 1.0);

    glLineWidth(2);
    glColor4f(1.00f, 1.00f, 1.00f, 1.0f);

    double r = c;
    double n = M_PI/apro;
    std::vector<TVertex> coords(100);
    std::vector<TVertex> norm(100);
          for (double az = 0; az <= 2*M_PI; az += n) {
              for (double ze = 0; ze <= M_PI; ze += n) {
                TVertex vert1, normal;
                vert1.x = r*sin(ze)*cos(az); vert1.y = r*sin(ze)*sin(az); vert1.z = r*cos(ze);
                normal.x = sin(ze)*cos(az); normal.y = sin(ze)*sin(az); normal.z = cos(ze);
                norm.push_back(normal);
                coords.push_back(vert1);
                ze +=n;
                vert1.x = r*sin(ze)*cos(az); vert1.y = r*sin(ze)*sin(az); vert1.z = r*cos(ze);
                normal.x = sin(ze)*cos(az); normal.y = sin(ze)*sin(az); normal.z = cos(ze);
                norm.push_back(normal);
                coords.push_back(vert1);
                az += n;
                vert1.x = r*sin(ze)*cos(az); vert1.y = r*sin(ze)*sin(az); vert1.z = r*cos(ze);
                normal.x = sin(ze)*cos(az); normal.y = sin(ze)*sin(az); normal.z = cos(ze);
                norm.push_back(normal);
                coords.push_back(vert1);
                ze -= n;
                vert1.x = r*sin(ze)*cos(az); vert1.y = r*sin(ze)*sin(az); vert1.z = r*cos(ze);
                normal.x = sin(ze)*cos(az); normal.y = sin(ze)*sin(az); normal.z = cos(ze);
                norm.push_back(normal);
                coords.push_back(vert1);
                az -= n;
              }
          }

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*coords.size(), &coords[0], GL_DYNAMIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, VBOn);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*norm.size(), &norm[0], GL_DYNAMIC_DRAW);
    glNormalPointer(GL_FLOAT, 0, NULL);
    if (vision){
        glDrawArrays(GL_QUADS, 0, coords.size());
    } else{
        glDrawArrays(GL_LINE_STRIP, 0, coords.size());
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

