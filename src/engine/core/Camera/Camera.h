//
// Created by arjun on 10/27/25.
//

#ifndef C_3D_RENDERING_ENGINE_CAMERA_H
#define C_3D_RENDERING_ENGINE_CAMERA_H

#include "engine/core/transform/transform.h"
#include "engine/core/matrix4x4/matrix4x4.h"

typedef struct  {
    Transform camera_transform;
    float fov;
    float aspect;
    float near_plane;
    float far_plane;

    matrix4x4 view;
    matrix4x4 projection;
} Camera;

Camera *get_main();
Camera * init_camera(float fov, float aspect, float near_plane, float far_plane);
void camera_update(Camera * camera);

#endif //C_3D_RENDERING_ENGINE_CAMERA_H