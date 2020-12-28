#include "spline.h"
#include <QDebug>


spline::spline()
{

}

spline::spline(QVector<myPoint>& pnts)
{
    points = pnts;
    segments.resize(points.size() - 1);
    for (int i =0; i < segments.size(); i++) {
        segments[i].xPolynom.resize(4);
        segments[i].yPolynom.resize(4);
        segments[i].zPolynom.resize(4);
    }
}

GLfloat spline::getF(GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat t)
{
    return qPow(t, 3) * a + qPow(t, 2) * b + t * c + d;
}

void spline::calculate(){

     preCalculation();
        for(int i = 0; i < (int)segments.size() - 1; ++i){
            calculatePolynom(segments[i].xPolynom, segments[i+1].xPolynom);
            calculatePolynom(segments[i].yPolynom, segments[i+1].yPolynom);
            calculatePolynom(segments[i].zPolynom, segments[i+1].zPolynom);
        }
        postCalculation();
       // qDebug() << segments[1].xPolynom << '\n' ;

}

void spline::calculatePolynom(QVector<GLfloat>& fP, QVector<GLfloat>& sP){
    GLfloat m = sP[3] - fP[3] - fP[2];
    GLfloat q = sP[2] - fP[2];
    fP[0] = q - 2 * m;
    fP[1] = 3 * m - q;
}

void spline::preCalculation(){
    segments[0].xPolynom[2] = k*(points[1].x-points[0].x)/2;
    segments[0].yPolynom[2] = k*(points[1].y-points[0].y)/2;
    segments[0].zPolynom[2] = k*(points[1].z-points[0].z)/2;

    for(int i = 1; i < (int)segments.size(); ++i){
        segments[i].xPolynom[2] = k * (points[i+1].x-points[i-1].x);
        segments[i].yPolynom[2] = k * (points[i+1].y-points[i-1].y);
        segments[i].zPolynom[2] = k * (points[i+1].z-points[i-1].z);
    }
    for(int i = 0; i < (int)segments.size();++i){
        segments[i].xPolynom[3] = points[i].x;
        segments[i].yPolynom[3] = points[i].y;
        segments[i].zPolynom[3] = points[i].z;
    }
}
void spline::postCalculation(){
    calculateLastPolynom(segments.back().xPolynom, points.back().x, points[points.size()-2].x);
    calculateLastPolynom(segments.back().yPolynom, points.back().y, points[points.size()-2].y);
    calculateLastPolynom(segments.back().zPolynom, points.back().z, points[points.size()-2].z);
}

void spline::calculateLastPolynom(QVector<GLfloat>& pol, float pl, float pr){
    float t = k*(pl - pr)/2;
    float m = t - pol[2];
    float q = pl - pol[2] - pol[3];
    pol[1] = 3*q-m;
    pol[0] = m-2*q;

}

void spline::draw() {
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    GLfloat dx, dy, dz;
    for (int i = 0; i < (int)segments.size(); i++) {
        //qDebug() << dx << ' '<< dy<< ' '<< dz<< "\n";
        glVertex3f(points[i].x, points[i].y, points[i].z);

        for (GLfloat t = 0; t < 1; t += 0.1) {
            dx = getF(segments[i].xPolynom[0], segments[i].xPolynom[1], segments[i].xPolynom[2], segments[i].xPolynom[3], t);
            dy = getF(segments[i].yPolynom[0], segments[i].yPolynom[1], segments[i].yPolynom[2], segments[i].yPolynom[3], t);
            dz = getF(segments[i].zPolynom[0], segments[i].zPolynom[1], segments[i].zPolynom[2], segments[i].zPolynom[3], t);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(dx, dy, dz);
        }
        glVertex3f(points[i+1].x, points[i+1].y, points[i+1].z);

    }
    glEnd();

}








