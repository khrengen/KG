#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    :QOpenGLWidget{parent}
{

}

void MyOpenGLWidget::setParam(int param)
{
    if (param != c) {
        c = param;
        emit paramChanged(param);
        update();
    }
}

void MyOpenGLWidget::initializeGL()
{

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

void MyOpenGLWidget::paintGL()
{
    glClearColor(255, 255, 255, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawLine(0, height() / 2, width(), height() / 2);
    painter.drawLine(width() / 2, 0, width() / 2, height());
    QPointF points[3];
    points[0] = QPoint(width(), height() / 2);
    points[1] = QPoint(width() - 20, height() / 2 - 5);
    points[2] = QPoint(width() - 20, height() / 2 + 5);
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawPolygon(points, 3);
    points[0] = QPoint(width() / 2, 0);
    points[1] = QPoint(width() / 2 - 5, 20);
    points[2] = QPoint(width() / 2 + 5, 20);
    painter.drawPolygon(points, 3);

    qreal a = 0;
    qreal b = qRadiansToDegrees(2 * M_PI);
    qreal h = 0.005;
    painter.save();
    QPoint OO(width() / 2, height() / 2);
    painter.translate(OO);
    for(int i = -100; i <= 100; i ++) {
        painter.drawLine(i * 10, -2, i * 10, 2);
        painter.drawLine(-2, i * 10, 2, i * 10);

    }
    for(int i = -10; i < 10; i++) {
        painter.drawText(i * 100, 12, QString::number(i));
        if (i != 0) {
            painter.drawText(12, i * 100, QString::number(-i));
        }
    }
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine));
    for (qreal angle = a; angle <= b; angle += h)
    {
        QPointF p(c * qPow(qCos(angle),3), c * qPow(qSin(angle),3));
        painter.drawPoint(p);

    }
    painter.restore();



}

