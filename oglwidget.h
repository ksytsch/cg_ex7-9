#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <vector>
#include <QMouseEvent>
#include <ball.h>
#include <gameobject.h>



class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    QTimer *timer;
    std::vector<GameObject> gameObjects;

    // Used to rotate object by mouse
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void drawArena();
    void drawPseudo3d(std::vector<QVector2D> p, float height);
    void createGameObjects();
    void detectCollision();
signals:
    // Emitted whenever a change of rotation angles is requested (e.g. by mouse or key)
    void changeRotation( int dx, int dy, int dz );

public slots:   
    // Set zoom factor
    void setZoom( int newzoom );
    // Set light position
    void setLight(int newlight );
    // Set the rotation angles
    void setRotX( int newrx );
    void setRotY( int newry );
    void setRotZ( int newrz );
    void timerSlot();

protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    int zoom;       // Zoom factor (0..200, 100 for 1:1)
    int light;      // Light position (0..360, around y axis)

    QPoint lastpos; // Last position of mouse pressed, used for dragging
    int rotx;       // Rotation angles (0..360)
    int roty;
    int rotz;


};

#endif // OGLWIDGET_H
