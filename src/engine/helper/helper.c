//
// Created by arjun on 10/22/25.
//

#include "helper.h"

#include <math.h>
#include <stdio.h>


struct vec3 vec2ToVec3(struct vec2 vector2) {
    return (struct vec3){vector2.x, vector2.y, 0.0f};
}
Color getColor() {
    Color c;
    c.red        = (struct vec3){1.0f, 0.0f, 0.0f};
    c.green      = (struct vec3){0.0f, 1.0f, 0.0f};
    c.blue       = (struct vec3){0.0f, 0.0f, 1.0f};
    c.yellow     = (struct vec3){1.0f, 1.0f, 0.0f};
    c.cyan       = (struct vec3){0.0f, 1.0f, 1.0f};
    c.magenta    = (struct vec3){1.0f, 0.0f, 1.0f};
    c.orange     = (struct vec3){1.0f, 0.5f, 0.0f};
    c.purple     = (struct vec3){0.5f, 0.0f, 0.5f};
    c.pink       = (struct vec3){1.0f, 0.2f, 0.6f};
    c.white      = (struct vec3){1.0f, 1.0f, 1.0f};
    c.black      = (struct vec3){0.0f, 0.0f, 0.0f};
    c.gray       = (struct vec3){0.5f, 0.5f, 0.5f};
    c.lightGray  = (struct vec3){0.75f, 0.75f, 0.75f};
    c.darkGray   = (struct vec3){0.25f, 0.25f, 0.25f};
    c.brown      = (struct vec3){0.55f, 0.27f, 0.07f};
    return c;
}



float deg2rad(float deg)  {
    return deg * (PI / 180.0f);
}

struct vec3 color_with_luminance(struct vec3 base_color, float lum) {
    struct vec3 col;
    col.x = base_color.x * lum;
    col.y = base_color.y * lum;
    col.z = base_color.z * lum;

    // clamp to [0,1] to avoid overflow
    if (col.x > 1.0f) col.x = 1.0f;
    if (col.y > 1.0f) col.y = 1.0f;
    if (col.z > 1.0f) col.z = 1.0f;

    if (col.x < 0.0f) col.x = 0.0f;
    if (col.y < 0.0f) col.y = 0.0f;
    if (col.z < 0.0f) col.z = 0.0f;

    return col;
}
// void apply_luminance(Object *obj, float lum) {
//     if (!obj || obj->total_vertices <= 0) return;
//
//     for (int i = 0; i < obj->total_vertices; i++) {
//         Vertex *v = &obj->vertices[i];
//
//         // modulate each component by luminance
//         v->color.x *= lum;
//         v->color.y *= lum;
//         v->color.z *= lum;
//
//         // clamp to [0,1]
//         if (v->color.x > 1.0f) v->color.x = 1.0f;
//         if (v->color.y > 1.0f) v->color.y = 1.0f;
//         if (v->color.z > 1.0f) v->color.z = 1.0f;
//
//         if (v->color.x < 0.0f) v->color.x = 0.0f;
//         if (v->color.y < 0.0f) v->color.y = 0.0f;
//         if (v->color.z < 0.0f) v->color.z = 0.0f;
//     }
// }


matrix4x4 get_projection_matrix(int height, int width, float fov, float far, float near) {
    matrix4x4 projection = {0};

    float aspect = (float)width / (float)height;

    // float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
    float fovRad = 1.0f / tanf((fov * 0.5f) * (3.14159f / 180.0f));


    projection.a[0][0] = aspect * fovRad;
    projection.a[1][1] = fovRad;
    projection.a[2][2] = far / (far - near);
    projection.a[3][2] =( -far*near )/ (far - near);
    projection.a[2][3] = 1.0f;
    projection.a[3][3] = 0.0f;
    return projection;
}

struct vec3 reverse_vec3(struct vec3 vector3) {
    return (struct vec3){-vector3.x, -vector3.y, -vector3.z};
}
struct vec2 screen_to_ndc(float x, float y, float width, float height) {
    return (struct vec2){
        (x / width) * 2.0f - 1.0f,    // x in [-1,1]
        (y / height) * 2.0f - 1.0f    // y in [-1,1]
    };
}

// struct vec3 fromVertex(Vertex v) {
//     return v.position;
// }

struct vec3 fromVec3d(vec3d v) {
    return (struct vec3){v.x, v.y, v.z};
}

struct vec3 Vec3(float x, float y, float z) {
    return (struct vec3){x, y, z};
}


struct vec3 vec3_add(struct vec3 p1, struct vec3 p2) {
    return Vec3(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}
struct vec3 vec3_sub(struct vec3 p1, struct vec3 p2) {
    struct vec3 vec = {0, 0, 0};
    vec.x = p1.x - p2.x;
    vec.y = p1.y - p2.y;
    vec.z = p1.z - p2.z;
    return vec;
}
struct vec3 vec3_mul(struct vec3 p1, float k) {
    return Vec3(p1.x * k, p1.y * k, p1.z * k);
}
struct vec3 vec3_div(struct vec3 p1, float k) {
    if (k == 0) {
        return Vec3(0.0f, 0.0f, 0.0f);
    }
    return Vec3(p1.x / k, p1.y / k, p1.z / k);
}
float vec3_dot(struct vec3 p1, struct vec3 p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}
float vec3_len(struct vec3 p1) {
    return sqrtf(vec3_dot(p1, p1));
}
struct vec3 vec3_normalize(struct vec3 p1) {
    float len = vec3_len(p1);
    return vec3_div(p1, len);
}

struct vec3 vec3_cross(struct vec3 p1, struct vec3 p2) {
    struct vec3 cross = {0, 0, 0};
    cross.x = p1.y * p2.z - p1.z * p2.y;
    cross.y = p1.z * p2.x - p1.x * p2.z;
    cross.z = p1.x * p2.y - p1.y * p2.x;
    return cross;
}