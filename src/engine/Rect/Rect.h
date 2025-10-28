//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_RECT_H
#define C_3D_RENDERING_ENGINE_RECT_H
#include "engine/triangle/Triangle.h"

typedef struct {
    Triangle s1;
    Triangle s2;
} Rect;

Rect* init_rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
void calculate_rect_vertices(Rect* r, Vertices *vertices);
#endif //C_3D_RENDERING_ENGINE_RECT_H