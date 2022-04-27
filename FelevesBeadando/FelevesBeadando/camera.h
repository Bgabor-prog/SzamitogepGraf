#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "utilities.h"
#include <stdbool.h>


typedef struct Camera
{
    vec3 pos;
    vec3 rotation;
    vec3 speed;
} Camera;


void CreateCamera(Camera* camera);

void UpdateCamera(Camera* camera, double time);

void SetView(const Camera* camera);

void RotateCamera(Camera* camera, double horizontal, double vertical);

void SetCameraSpeed(Camera* camera, double speed);

void SetCameraSideSpeed(Camera* camera, double speed);

void SetCameraLiftSpeed(Camera* camera, double speed);


#endif // CAMERA_H_INCLUDED
