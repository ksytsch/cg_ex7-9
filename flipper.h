#ifndef FLIPPER_H
#define FLIPPER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <vector>

class Flipper
{
public:
    std::vector<QVector2D> points;
    QVector3D colour;
    float height;

    std::vector<QVector2D> maxAcceleration;


    Flipper();
    Flipper(std::vector <QVector2D> p,  QVector3D c, float h);
    void drawPseudo3d();
};

#endif // FLIPPER_H
