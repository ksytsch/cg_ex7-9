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

    boolean activated;
    std::vector<QVector2D> minAcceleration;
    std::vector<QVector2D> maxAcceleration;



    Flipper();
};

#endif // FLIPPER_H
