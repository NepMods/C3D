//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_RECT_H
#define C_3D_RENDERING_ENGINE_RECT_H
#include "engine/triangle/Triangle.h"

typedef struct {
    struct Triangle s1;
    struct Triangle s2;
} Rect;

Rect* init_rect(struct vec3 p1,struct  vec3 p2, struct vec3 p3, struct vec3 p4);
void calculate_rect_vertices(Rect* r, struct  Vertices *vertices);
#endif //C_3D_RENDERING_ENGINE_RECT_H