//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_HELPER_H
#define C_3D_RENDERING_ENGINE_HELPER_H

#include "engine/vec3/vec3.h"
#include "engine/vec2/vec2.h"
#include "engine/core/matrix4x4/matrix4x4.h"
#include "engine/object/object.h"
#include "engine/vertex/vertex.h"
#define PI 3.14159265359f
float deg2rad(float deg);
vec3d multiplyMatrix4x4AndVec3(vec3 in, matrix4x4 matrix);
matrix4x4 get_projection_matrix(int height, int width, float fov, float far, float near) ;

vec3 vec2ToVec3(vec2 vector2);
vec3 reverse_vec3(vec3 vector3);
vec2 screen_to_ndc(float x, float y, float width, float height);
vec3 color_with_luminance(vec3 base_color, float lum);
void apply_luminance(Object *obj, float lum);

vec3 vec3_add(vec3 p1, vec3 p2);
vec3 vec3_sub(vec3 p1, vec3 p2);
vec3 vec3_mul(vec3 p1, float k);
vec3 vec3_div(vec3 p1, float k);
float vec3_dot(vec3 p1, vec3 p2);
float vec3_len(vec3 p1);
vec3 vec3_normalize(vec3 p1);
vec3 vec3_cross(vec3 p1, vec3 p2);

typedef struct {
    vec3 red;
    vec3 green;
    vec3 blue;
    vec3 yellow;
    vec3 cyan;
    vec3 magenta;
    vec3 orange;
    vec3 purple;
    vec3 pink;
    vec3 white;
    vec3 black;
    vec3 gray;
    vec3 lightGray;
    vec3 darkGray;
    vec3 brown;
} Color;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

vec3 fromVertex(Vertex v);
vec3 fromVec3d(vec3d v);
Color getColor();
vec3 Vec3(float x, float y, float z);

#endif //C_3D_RENDERING_ENGINE_HELPER_H