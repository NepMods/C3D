//
// Created by arjun on 10/27/25.
//

#include "Camera.h"

#include <math.h>
#include <stdlib.h>

#include "engine/core/renderer/renderer.h"
#include "engine/core/transform/transform.h"
#include "engine/helper/helper.h"

Camera *main_camera;
Camera *get_main() {
    if (main_camera) {
        return main_camera;
    }
    float fov = 90.0f;
    float near = 0.1f;
    float far = 1000.0f;
    Renderer *renderer = get_main_renderer();
    main_camera = init_camera(fov, (float)renderer->width/(float)renderer->height, near, far);
    return main_camera;
}

Camera * init_camera(float fov, float aspect, float near_plane, float far_plane) {
    Camera * camera = (Camera *)malloc(sizeof(Camera));
    camera->fov = fov;
    camera->aspect = aspect;
    camera->near_plane = near_plane;
    camera->far_plane = far_plane;
    camera->camera_transform = init_transform();
    camera->camera_transform.position.z += 2;

    camera_update(camera);
    return camera;
}
void camera_update(Camera * camera) {

    float fov = deg2rad(camera->fov);
    float aspect = (float)camera->aspect;
    float near = camera->near_plane;
    float far = camera->far_plane;

    float f = 1.0f / tan(fov / 2.0f);

    matrix4x4 proj = {0};
    proj.a[0][0] = f / aspect;
    proj.a[1][1] = f;
    proj.a[2][2] = (far + near) / (near - far);
    proj.a[2][3] = (2 * far * near) / (near - far);
    proj.a[3][2] = -1.0f;
    proj.a[3][3] = 0.0f;

    camera->projection = proj;

    transform_update(&camera->camera_transform);
    camera->view = Inverse(camera->camera_transform.model);
}