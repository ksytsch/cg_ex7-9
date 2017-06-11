#include "oglwidget.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <cmath>
#include <vector>
#include <QTimer>
#include <QVector>
#include "ball.h"
#include "gameobject.h"


using namespace std;

const QVector3D gravity (0, -2,0);
Ball *ball= new Ball(QVector3D(0.0,-05,1), QVector3D(1,0,0), 1 ,1, QVector3D(-7,13,0));


OGLWidget::OGLWidget(QWidget *parent): QOpenGLWidget(parent){
    light = 0;
    zoom  = 100;
    //set up timer to deal with periodic updates
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(30);//time interval 1000=1s
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::setZoom(int newzoom){
    zoom = newzoom;
    update();
}

void OGLWidget::setLight(int newlight){
    light = newlight;
    float dt = 0.1;

    ball->recalculatePosition(dt, gravity);
    update();
}

void OGLWidget::setRotX(int newrx){
    rotx = newrx;
    update();
}

void OGLWidget::setRotY(int newry){
    roty = newry;
    update();
}

void OGLWidget::setRotZ(int newrz){
    rotz = newrz;
    update();
}
//update scene dynamically
void OGLWidget::timerSlot(){
    //dt is constant due to the timer value set
    ball->recalculatePosition(0.1, gravity);
    if(ball->position.y()<-36){
        ball = new Ball (QVector3D(0.0,-15,1), QVector3D(1,0,0), 1 ,1, QVector3D(-7,13,0));
    }
    detectCollision();
    update();
}

void OGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    // Use depth testing and the depth buffer
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);
    // Calculate color for each pixel fragment
    glShadeModel(GL_SMOOTH);
    // Enable lighting in scene
    glEnable(GL_LIGHTING);
    // Set position of light source
    float light_pos[] = { 10.f, 5.f, 10.f, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos );
    // Set color for this light source
    // (We are only specifying a diffuse light source)
    float light_diffuse[] = { .8f, .8f, .8f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse );
    // Turn on this light
    glEnable(GL_LIGHT1);
    // Use the color of an object for light calculation
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

}

void OGLWidget::drawArena(){
    float length = 50;
    float width = 30;
    float centerPosX = 0;
    float centerPosY = 0;
    float centerPosZ = 0;

    glBegin(GL_QUADS);

    //surface
    glColor3f(1,1,0);//yellow
    glNormal3f(0, 1, 0); //Up
    glVertex3f(centerPosX-width/2, centerPosY-length/2-10, centerPosZ);
    glVertex3f(centerPosX+width/2, centerPosY-length/2-10, centerPosZ);
    glVertex3f(centerPosX+width/2, centerPosY+length/2, centerPosZ);
    glVertex3f(centerPosX-width/2, centerPosY+length/2, centerPosZ);
    glNormal3f( 0, 0, 1); //Towards
    glEnd();
}

void OGLWidget::createGameObjects(){
    vector<QVector2D> leftS;
    leftS.push_back(QVector2D(-18,-25));
    leftS.push_back(QVector2D(-15,-25));

    leftS.push_back(QVector2D(-15,25));
    leftS.push_back(QVector2D(-18,25));
    GameObject *leftSide = new GameObject(leftS, QVector3D(1,0,0), 5);

    vector<QVector2D> rightS;
    rightS.push_back(QVector2D(18,-25));
    rightS.push_back(QVector2D(15,-25));
    rightS.push_back(QVector2D(15,25));
    rightS.push_back(QVector2D(18,25));
    GameObject *rightSide = new GameObject(rightS, QVector3D(1,0,0), 5);

    vector<QVector2D> topS;
    topS.push_back(QVector2D(-15,25));
    topS.push_back(QVector2D(15,25));
    topS.push_back(QVector2D(15,28));
    topS.push_back(QVector2D(-15,28));
    GameObject *topSide = new GameObject(topS, QVector3D(1,0,0), 5);

    vector<QVector2D> botLeftTri;
    botLeftTri.push_back(QVector2D(-15, -20));
    botLeftTri.push_back(QVector2D(-10,-22));
    botLeftTri.push_back(QVector2D(-10,-25));
    botLeftTri.push_back(QVector2D(-15,-25));
    GameObject *botLeftTriangle = new GameObject(botLeftTri, QVector3D(1,0,0), 5);

    vector<QVector2D> botRightTri;
    botRightTri.push_back(QVector2D(15, -20));
    botRightTri.push_back(QVector2D(10,-22));
    botRightTri.push_back(QVector2D(10,-25));
    botRightTri.push_back(QVector2D(15,-25));
    GameObject *botRightTriangle = new GameObject(botRightTri, QVector3D(1,0,0), 5);

    vector<QVector2D> leftFlip;
    leftFlip.push_back(QVector2D(-10,-22));
    leftFlip.push_back(QVector2D(-10,-25));
    leftFlip.push_back(QVector2D(-3,-25));
    leftFlip.push_back(QVector2D(-2.5,-24));
    GameObject *lFlipper = new GameObject(leftFlip, QVector3D(0,0,1), 2);

    vector<QVector2D> rightFlip;
    rightFlip.push_back(QVector2D(10,-22));
    rightFlip.push_back(QVector2D(10,-25));
    rightFlip.push_back(QVector2D(3, -25));
    rightFlip.push_back(QVector2D(2.5,-24));
    GameObject *rFlipper = new GameObject(rightFlip, QVector3D(0,0,1), 2);



    vector<QVector2D> quad;
    quad.push_back(QVector2D(1,1));
    quad.push_back(QVector2D(1,3));
    quad.push_back(QVector2D(3,3));
    quad.push_back(QVector2D(3,1));
    GameObject *quadObj = new GameObject(quad, QVector3D(0,1,0), 3);

    //sides + flippers
    gameObjects.push_back(*leftSide);
    gameObjects.push_back(*rightSide);
    gameObjects.push_back(*topSide);
    gameObjects.push_back(*botLeftTriangle);
    gameObjects.push_back(*botRightTriangle);
    gameObjects.push_back(*lFlipper);
    gameObjects.push_back(*rFlipper);



    //game objects
    gameObjects.push_back(*quadObj);

}

void OGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Prepare projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
                     // Parallel projection with
    glOrtho(-10, 10, // clipping planes: left,   right
            -10, 10, //                  bottom, top
            -50, 50);//                  near,   far

    // Prepare model matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply rotation angles
    glRotatef(rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // Apply scaling
    float scale = zoom/350.0;
    glScalef( scale, scale, scale ); // Scale along all axis
    // Change light position
    float light_pos[] = { 10.f * cosf(light*M_PI/180.f),
                           5.f,
                          10.f * sinf(light*M_PI/180.f), 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION,  light_pos);
    drawArena();
    createGameObjects();
    //drawBall(QVector3D( ballX, ballY, 1), 1);
    for(int i =0;i<gameObjects.size();i++){
        GameObject o = gameObjects.at(i);
        o.drawPseudo3d();
    }
    ball->drawBall();
}

void OGLWidget::detectCollision(){
    //sides collision
    if(ball->position.x()<-14){
       //vb = 2(-va*n)n+va
       ball->position.setX(-13.5);
       QVector3D va = ball->speed;
       QVector3D vb = 2*(-va * QVector3D(1,0,0))*QVector3D(1,0,0)+va;
       ball->speed =vb;
    }
    if(ball->position.x()>14){
        ball->position.setX(13.5);
        QVector3D va = ball->speed;
        QVector3D vb = 2*(-va * QVector3D(-1,0,0))*QVector3D(-1,0,0)+va;
        ball->speed =vb;
    }
    if(ball->position.y()>24){
        ball->position.setY(23.5);
        QVector3D va = ball->speed;
        QVector3D vb = 2*(-va * QVector3D(1,-1,0))*QVector3D(1,-1,0)+va;
        ball->speed =vb;
    }
}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::mousePressEvent(QMouseEvent *event){
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // ... and while moving, we calculate the dragging deltas
    // Left button: Rotating around x and y axis
    int dx = (event->buttons() & Qt::LeftButton) ? lastpos.y() - event->y() : 0;
    int dy = lastpos.x() - event->x();

    // Right button: Rotating around z and y axis
    int dz = (event->buttons() & Qt::RightButton) ? lastpos.y() - event->y() : 0;

    // Now let the world know that we want to rotate
    emit changeRotation( dx, dy, dz );

    // Make the current position the starting point for the next dragging step
    lastpos = event->pos();
}




