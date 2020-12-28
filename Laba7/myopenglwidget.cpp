#include "myopenglwidget.h"
#include <QDebug>


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    :QOpenGLWidget{parent}
{

}

void MyOpenGLWidget::initializeGL()
{
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    qreal aspectratio = qreal (w) / qreal(h);
    if (aspectratio > 1) {
        glOrtho(-1 * aspectratio, 1 * aspectratio, -1, 1, 1, -1);
    } else {
        glOrtho(-1, 1, -1 / aspectratio, 1 / aspectratio, 1, -1);
    }

}

GLfloat F( GLfloat t, GLfloat A, GLfloat B, GLfloat C, GLfloat D) {
    return A * qPow(t, 3) + B * qPow(t, 2) + C * (t) + D;
}

void setConst(std::vector<GLfloat> &spline1, std::vector<GLfloat> &spline2, GLfloat df0, GLfloat df2, GLfloat p0, GLfloat p1, GLfloat p2) {

        GLfloat& a1 = spline1[0];
        GLfloat& a2 = spline2[0];
        GLfloat& b1 = spline1[1];
        GLfloat& b2 = spline2[1];
        GLfloat& c1 = spline1[2];
        GLfloat& c2 = spline2[2];
        GLfloat& d1 = spline1[3];
        GLfloat& d2 = spline2[3];

        d1 = p0;
        d2 = p1;
        c1 = df0;

        GLfloat n = -c1;
        GLfloat h = d2-d1-c1;
        GLfloat q = p2 - d2;
        GLfloat z = df2;
        GLfloat x = 3*q + 2*n - z;

        a1 = (x-5*h)/4;
        b1 = (9*h - x)/4;

        b2 = 3*a1 + b1;
        c2 = 3*a1 + 2*b1 - n;
        a2 = q - b2 - c2;

}

void MyOpenGLWidget::buildSpline() {

    GLfloat mydfx0 = (df0x - x1) * 5;
    GLfloat mydfx2 = (x3 - df2x) * 5;

    GLfloat mydfy0 = (df0y - y1) * 5;
    GLfloat mydfy2 = (y3 - df2y) * 5;

    std::vector<GLfloat> coefX0(4);
    std::vector<GLfloat> coefX1(4);
    std::vector<GLfloat> coefY0(4);
    std::vector<GLfloat> coefY1(4);

    setConst(coefX0, coefX1, mydfx0, mydfx2, x1, x2, x3);
    setConst(coefY0, coefY1, mydfy0, mydfy2, y1, y2, y3);
    drawSpline(coefX0, coefY0, coefX1, coefY1);
}

void MyOpenGLWidget:: drawSpline (std::vector<GLfloat> &splineX0, std::vector<GLfloat> &splineY0, std::vector<GLfloat> &splineX1, std::vector<GLfloat> &splineY1) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::blue, 2));
    QPoint prev(x1, y1);

    GLfloat px, py;

    for (GLfloat t = 0; t < 1; t += 0.01) {
        px = F(t, splineX0[0], splineX0[1], splineX0[2], splineX0[3]);
        py = F(t, splineY0[0], splineY0[1], splineY0[2], splineY0[3]);
        painter.drawLine(prev, QPoint(px,py));
        prev = QPoint(px,py);
    }
    prev = QPoint(x2,y2);

    for (GLfloat t = 0; t < 1; t += 0.01) {
        px = F(t, splineX1[0], splineX1[1], splineX1[2], splineX1[3]);
        py = F(t, splineY1[0], splineY1[1], splineY1[2], splineY1[3]);
        painter.drawLine(prev, QPoint(px,py));
        prev = QPoint(px,py);
    }

    QPointF p[3];
    p[0] = QPoint(x1,y1);
    p[1] = QPoint(x2,y2);
    p[2] = QPoint(x3,y3);
    painter.setPen(QPen(Qt::red, 8));
    painter.drawPoints(p,3);
    QPoint df0(df0x, df0y), df2(df2x, df2y);
    painter.setPen(QPen(Qt::green, 3));
    painter.drawLine(QPoint(x1,y1), df0);
    painter.drawLine(QPoint(x3,y3), df2);
    painter.setPen(QPen(Qt::red, 3));
    painter.drawPoint(df0);
    painter.drawPoint(df2);

}

void MyOpenGLWidget::paintGL()
{
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      buildSpline();
}



void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    lastPos = event->pos();

}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (abs(lastPos.x() - x1) < 5 && abs(lastPos.y() - y1) < 5) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        x1 += dx;
        y1 += dy;
        df0x += dx;
        df0y += dy;

    } else if (abs(lastPos.x() - x2) < 5 && abs(lastPos.y() - y2) < 5) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        x2 += dx;
        y2 += dy;

    } else if (abs(lastPos.x() - x3) < 5 && abs(lastPos.y() - y3) < 5) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        x3 += dx;
        y3 += dy;
        df2x += dx;
        df2y += dy;

    } else if (abs(lastPos.x() - df0x) < 5 && abs(lastPos.y() - df0y) < 5) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        df0x += dx;
        df0y += dy;
    } else if (abs(lastPos.x() - df2x) < 5 && abs(lastPos.y() - df2y) < 5) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        df2x += dx;
        df2y += dy;
 }

    update();
    lastPos = event->pos();
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    lastPos = event->pos();
}
