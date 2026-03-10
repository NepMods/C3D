//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_VERTEX_H
#define C_3D_RENDERING_ENGINE_VERTEX_H

#include "c_dynamic_array/cda.h"
#include "engine/vec3/vec3.h"

struct Vertex {
    struct vec3 position;
    struct vec3 color;
    struct vec3 normal;
} ;

struct Vertices {
    d_array vertices;
    d_array indices;
    int vertex_count;
    int index_count;
    int per_object_index;
};

struct Vertex initialize_vertex(struct vec3 pos,struct vec3 color);
struct Vertex initialize_vertex_with_normal(struct vec3 pos,struct  vec3 color, struct vec3 normal);
struct Vertices initialize_vertices();
int add_vertex(struct Vertices *vertices, struct Vertex vertex);
void add_indices(struct Vertices *vertices,  int *indices, int count, int index_per_instance);
void calculate_normals(struct Vertices *vertices);
void print_vertices(struct Vertices *vertices);
#endif //C_3D_RENDERING_ENGINE_VERTEX_H