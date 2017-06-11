#include "flipper.h"
#define _USE_MATH_DEFINES
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <math.h>
#include <cmath>
#include <vector>
#include <QVector>

using namespace std;
Flipper::Flipper(){}

Flipper::Flipper(std::vector <QVector2D> p, QVector3D c, float h){
    points = p;
    colour = c;
    height = h;
}

void Flipper::drawPseudo3d(){
    //paint figure at the given height
    glBegin(GL_POLYGON);
    glColor3f(colour.x(),colour.y(),colour.z());
    glNormal3f(0, 1, 0); //Up
    for(int i=0; i<points.size();i++){
        glVertex3f(points.at(i).x(), points.at(i).y(), height);
    }
    glEnd();
    //paint the sides
    glBegin(GL_QUADS);
    for(int i=0; i<points.size()-1;i++){
        //TODO - normal vector calc
        //normalX = points.at(i).y()-points.at(i+1).y(), -points.at(i).x()+points.at(i+1).x();
        glNormal3f(points.at(i).y()-points.at(i+1).y(), 0, -points.at(i).x()+points.at(i+1).x());

        glVertex3f(points.at(i).x(), points.at(i).y(), height);
        glVertex3f(points.at(i+1).x(), points.at(i+1).y(), height);
        glVertex3f(points.at(i+1).x(), points.at(i+1).y(), 0);
        glVertex3f(points.at(i).x(), points.at(i).y(), 0);
    }
    //last and first point side - cant be drawn in the loop
    //TODO - normal vector
    glVertex3f(points.at(points.size()-1).x(), points.at(points.size()-1).y(), height);
    glVertex3f(points.at(0).x(), points.at(0).y(), height);
    glVertex3f(points.at(0).x(), points.at(0).y(), 0);
    glVertex3f(points.at(points.size()-1).x(), points.at(points.size()-1).y(), 0);
    glEnd();
}
