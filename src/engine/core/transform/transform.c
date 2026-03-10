//
// Created by arjun on 10/27/25.
//

#include "transform.h"

#include <stdlib.h>

#include "engine/helper/helper.h"


Transform init_transform() {
    Transform transform;
    transform.scale = Vec3(1.0f, 1.0f, 1.0f);
    transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
    transform.position = Vec3(0.0f, 0.0f, 0.0f);
    transform_update(&transform);
    return transform;
}

matrix4x4 Rotate(Transform *transform) {
    matrix4x4 m = multiplyMatrix4x4(
        rotX(transform->rotation.x),
        multiplyMatrix4x4(
            rotY(transform->rotation.y),
            rotZ(transform->rotation.z)
        )
    );
    return m;
}

matrix4x4 Scale(Transform *transform) {
    matrix4x4 m = mat4_identity();
    m.a[0][0] = transform->scale.x;
    m.a[1][1] = transform->scale.y;
    m.a[2][2] = transform->scale.z;
    return m;
}
matrix4x4 Translate(Transform *transform) {
    matrix4x4 m = mat4_identity();
    m.a[0][3] = transform->position.x;
    m.a[1][3] = transform->position.y;
    m.a[2][3] = transform->position.z;
    return m;
}
void transform_update(Transform *transform) {
    matrix4x4 translated = Translate(transform);
    matrix4x4 scaled = Scale(transform);
    matrix4x4 rotated = Rotate(transform);
    transform->model = multiplyMatrix4x4(rotated, multiplyMatrix4x4(scaled, translated));
}
