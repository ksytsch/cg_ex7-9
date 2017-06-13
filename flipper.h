#ifndef FLIPPER_H
#define FLIPPER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include <QTimer>


class Flipper
{
public:
    std::vector<QVector2D> points;   
    QVector3D colour;
    float height;

    float curAngle = 0;
    float maxAngle = 60;
    QVector3D rotationPoint;
    std::vector<QVector2D> maxAcceleration;
    boolean enabled = false;

    Flipper();
    Flipper(std::vector <QVector2D> p,  QVector3D c, float h);
    void drawPseudo3d();

    void activateFlipper();
    QVector2D checkCollisionArea();
    float calculateCollisionAngle();
    void rotate(float angle);

};

#endif // FLIPPER_H
