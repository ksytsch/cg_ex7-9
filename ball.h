#ifndef BALL_H
#define BALL_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector>

class Ball{
public:
    QVector3D position;
    QVector3D colour;
    float radius;
    float mass;
    QVector3D speed;

    Ball();
    Ball(const QVector3D pos, QVector3D col, float rad, float m, QVector3D s);
    void drawBall(int nr_lat = 90, int nr_lon = 90);
    void recalculatePosition(float dt, QVector3D force);
    void deleteBall();
};

#endif // BALL_H
