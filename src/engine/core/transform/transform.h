//
// Created by arjun on 10/27/25.
//

#ifndef C_3D_RENDERING_ENGINE_TRANSFORM_H
#define C_3D_RENDERING_ENGINE_TRANSFORM_H
#include "engine/core/matrix4x4/matrix4x4.h"
#include "engine/vec3/vec3.h"

struct Transform_t {
    struct vec3 position;
    struct vec3 scale;
    struct vec3 rotation;
    matrix4x4 model;
};
#define Transform struct Transform_t

Transform init_transform();
matrix4x4 Rotate(Transform *transform);
matrix4x4 Scale(Transform *transform);
matrix4x4 Translate(Transform *transform);
void transform_update(Transform *transform);

#endif //C_3D_RENDERING_ENGINE_TRANSFORM_H