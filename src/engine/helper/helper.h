//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_HELPER_H
#define C_3D_RENDERING_ENGINE_HELPER_H

#include "engine/vec3/vec3.h"
#include "engine/vec2/vec2.h"
#include "engine/core/matrix4x4/matrix4x4.h"
#define PI 3.14159265359f
float deg2rad(float deg);
vec3d multiplyMatrix4x4AndVec3(struct vec3 in, matrix4x4 matrix);
matrix4x4 get_projection_matrix(int height, int width, float fov, float far, float near) ;

struct vec3 vec2ToVec3(struct vec2 vector2);
struct vec3 reverse_vec3(struct vec3 vector3);
struct vec2 screen_to_ndc(float x, float y, float width, float height);
struct vec3 color_with_luminance(struct vec3 base_color, float lum);
// void apply_luminance(Object *obj, float lum);

struct vec3 vec3_add(struct vec3 p1, struct vec3 p2);
struct vec3 vec3_sub(struct vec3 p1, struct vec3 p2);
struct vec3 vec3_mul(struct vec3 p1, float k);
struct vec3 vec3_div(struct vec3 p1, float k);
float vec3_dot(struct vec3 p1, struct vec3 p2);
float vec3_len(struct vec3 p1);
struct vec3 vec3_normalize(struct vec3 p1);
struct vec3 vec3_cross(struct vec3 p1, struct vec3 p2);

typedef struct {
    struct vec3 red;
    struct vec3 green;
    struct vec3 blue;
    struct vec3 yellow;
    struct vec3 cyan;
    struct vec3 magenta;
    struct vec3 orange;
    struct vec3 purple;
    struct vec3 pink;
    struct vec3 white;
    struct vec3 black;
    struct vec3 gray;
    struct vec3 lightGray;
    struct vec3 darkGray;
    struct vec3 brown;
} Color;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// struct vec3 fromVertex(Vertex v);
struct vec3 fromVec3d(vec3d v);
Color getColor();
struct vec3 Vec3(float x, float y, float z);

#endif //C_3D_RENDERING_ENGINE_HELPER_H