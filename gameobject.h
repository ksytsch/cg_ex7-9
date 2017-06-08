#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <vector>


class GameObject
{
public:
    std::vector<QVector2D> points;
    QVector3D colour;
    float height;

    GameObject();
    GameObject(std::vector <QVector2D> p,  QVector3D c, float h);
    void drawPseudo3d();
};

#endif // GAMEOBJECT_H
