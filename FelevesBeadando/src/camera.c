#include "camera.h"
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>


#define size 10


//Creating the camera and its starting position
void CreateCamera(Camera* camera)
{
    camera->pos.x = 0.0;
    camera->pos.y = 0.0;
    camera->pos.z = 2.5;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

//Update camera movements in real time
void UpdateCamera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);


    camera->pos.x += cos(angle) * camera->speed.y * time;
    camera->pos.y += sin(angle) * camera->speed.y * time;

    camera->pos.x += cos(side_angle) * camera->speed.x * time;
    camera->pos.y += sin(side_angle) * camera->speed.x * time;

    camera->pos.z += camera->speed.z * time;

    if(camera->pos.z > 4.7){
        CreateCamera(camera);
    }

    if(camera->pos.z < 0.1){
        CreateCamera(camera);
    }

    if(camera->pos.x < -6.5 || camera->pos.x > 6.5 || camera->pos.y < -6.5 || camera->pos.y > 6.5){

        CreateCamera(camera);
    }
}


void SetView(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->pos.x, -camera->pos.y, -camera->pos.z);
}

void RotateCamera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void SetCameraSpeed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void SetCameraSideSpeed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}
void SetCameraLiftSpeed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}


