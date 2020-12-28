#ifndef SPLINE_H
#define SPLINE_H

#include <QOpenGLWidget>
#include <QtWidgets>
#include <QtOpenGL>
#include <QtMath>


struct segment {
    QVector<GLfloat> xPolynom;
    QVector<GLfloat> yPolynom;
    QVector<GLfloat> zPolynom;

};

struct myPoint {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

class spline
{
public:
    spline();
    spline(QVector<myPoint>& pnts);
    GLfloat getF(GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat t);
    void  preCalculation();
    void  calculate();
    void  postCalculation();
    void calculatePolynom(QVector<GLfloat>& fP, QVector<GLfloat>& sP);
    void calculateLastPolynom(QVector<GLfloat>& pol, float pl, float pr);
    void draw();
    QVector<segment> segments;

private:
    QVector<myPoint> points;
    int k = 1;

};

#endif // SPLINE_H
