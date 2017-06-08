#include "ball.h"
#define _USE_MATH_DEFINES


using namespace std;

Ball::Ball(){

}
//constructor for the ball with all relevant parameters
Ball::Ball(const QVector3D pos, QVector3D col, float rad, float m, QVector3D s){
//    position.setX(pos.x());
//    position.setY(pos.y());
//    position.setZ(pos.z());

//    colour.setX(col.x());
//    colour.setY(col.y());
//    colour.setZ(col.z());
    position = pos;
    colour =col;

    radius=rad;
    mass = m;
    speed = s;
}

//function to draw a ball with given params - taken from MForm
void Ball::drawBall(int nr_lat, int nr_lon){
    // Angle delta in both directions
    const float lat_delta = M_PI / float( nr_lat );
    const float lon_delta = M_PI / float( nr_lon );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*M_PI; lon += lon_delta )
    {
        glColor3f(colour.x(),colour.y(),colour.z());
        glBegin( GL_QUAD_STRIP ) ;
        for( float lat = 0.0f; lat <= 2.0f*M_PI; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            float xn1 = cosf( lat ) * sinf( lon );
            float yn1 = sinf( lat ) * sinf( lon );
            float zn1 = cosf( lon );

            // Set normal vector (important for lighting!)
            glNormal3f( xn1, yn1, zn1 );
            glVertex3f( position.x()+radius*xn1, position.y()+radius*yn1, position.z()+radius*zn1 );

            float xn2 = cosf( lat ) * sinf( lon + lon_delta );
            float yn2 = sinf( lat ) * sinf( lon + lon_delta );
            float zn2 = cosf( lon + lon_delta );

            glNormal3f( xn2, yn2, zn2 );
            glVertex3f( position.x()+radius*xn2, position.y()+radius*yn2, position.z()+radius*zn2 );
        }
        glEnd() ;
    }
}

void Ball::recalculatePosition(float dt, QVector3D force){
    speed += dt*force;
    position += dt*speed;
}

void Ball::deleteBall(){
    delete[]this;
}
