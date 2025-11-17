//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_TRIANGLE_H
#define C_3D_RENDERING_ENGINE_TRIANGLE_H

#include "engine/Mesh/mesh.h"
// #include "engine/object/object.h"
#include "engine/vec2/vec2.h"
#include "engine/vec3/vec3.h"
// #include "engine/vertex/vertex.h"


struct Triangle {
    struct vec3 a, b, c;
};

struct Triangle init_triangle(struct vec2 a, struct vec2 b, struct vec2 c) ;
struct  Triangle init_triangle_3(struct vec3 a, struct vec3 b, struct vec3 c) ;
struct vec3 getNormalVector(struct  Triangle t);
void calculate_triangle_vertices(struct  Triangle t, struct Vertices *vertices);
void print_triangle(const struct Triangle *t);
#endif //C_3D_RENDERING_ENGINE_TRIANGLE_H