//
// Created by arjun on 10/22/25.
//

#include "vertex.h"

#include <stdio.h>
#include <stdlib.h>

#include "engine/helper/helper.h"


struct Vertices initialize_vertices() {
    struct Vertices vertices;
    vertices.index_count = 0;
    vertices.vertex_count = 0;
    vertices.per_object_index = -1;
    vertices.indices =  array_init(10, sizeof(int));
    vertices.vertices = array_init(10, sizeof(struct Vertex));
    return vertices;
}
int add_vertex(struct Vertices *vertices, struct  Vertex vertex) {
    __array_append(&vertices->vertices, &vertex);
    vertices->vertex_count++;
    return vertices->vertex_count-1;
}
void add_indices(struct  Vertices *vertices, int *indices, int count, int index_per_instance) {
    if (vertices->per_object_index == -1) {
        vertices->per_object_index = index_per_instance;
    }
    __array_append_multiple(&vertices->indices, indices, count);
    vertices->index_count += count;
}

struct Vertex initialize_vertex(struct vec3 pos, struct vec3 color) {
    struct Vertex vertex;
    vertex.position = pos;
    vertex.color = color;
    vertex.normal =  Vec3(0.0f, 0.0f, 0.0f);
    return vertex;
}

struct Vertex initialize_vertex_with_normal(struct vec3 pos, struct vec3 color, struct vec3 normal) {
    struct Vertex vert= initialize_vertex(pos, color);
    vert.normal = normal;
    return vert;
}

void calculate_normals(struct Vertices *vertices) {
    if (!vertices) return;

    for (int i = 0; i < vertices->vertex_count; i++) {
        struct Vertex *vertext = array_at(&vertices->vertices, i).data;
        vertext->normal = Vec3(0.0f, 0.0f, 0.0f);
    }

    int faceCount = vertices->index_count / vertices->per_object_index;

    for (int f = 0; f < faceCount; f++) {

        int start = f * vertices->per_object_index;

        if (vertices->per_object_index < 3) continue;

        int i0 = array_get(vertices->indices, start, int);
        int i1 = array_get(vertices->indices, start + 1, int);
        int i2 = array_get(vertices->indices, start + 2, int);

        struct Vertex *vertex1 = array_at(&vertices->vertices, i0).data;
        struct Vertex *vertex2 = array_at(&vertices->vertices, i1).data;
        struct Vertex *vertex3 = array_at(&vertices->vertices, i2).data;

        struct vec3 edge1 = vec3_sub(vertex2->position,  vertex1->position);
        struct vec3 edge2 = vec3_sub(vertex3->position, vertex1->position);
        struct vec3 faceNormal = vec3_normalize(vec3_cross(edge1, edge2));

        for (int j = 0; j < vertices->per_object_index; j++) {
            int vi = array_get(vertices->indices, start + j, int);
            struct Vertex *vertex_set_normal = array_at(&vertices->vertices, vi).data;
            vertex_set_normal->normal = vec3_add(vertex_set_normal->normal, faceNormal);
        }
    }

    for (int i = 0; i < vertices->vertex_count; i++) {

        struct Vertex *vertex = array_at(&vertices->vertices, i).data;
        vertex->normal =  vec3_normalize(vertex->normal);
    }
}
void print_vertices(struct Vertices *vertices) {
    if (!vertices) return;

    printf("Vertices Struct Debug:\n");
    printf("Vertex Count: %d\n", vertices->vertex_count);
    printf("Index Count: %d\n", vertices->index_count);
    printf("Indices per Face (per_object_index): %d\n\n", vertices->per_object_index);

    // if (vertices->vertices.length > 0) {
    //     for (int i = 0; i < vertices->vertex_count; i++) {
    //         struct Vertex *v = array_at(&vertices->vertices, i).data;
    //         printf("Vertex [%d]:\n", i);
    //         printf("  Position: (%.3f, %.3f, %.3f)\n", v->position.x, v->position.y, v->position.z);
    //         printf("  Color:    (%.3f, %.3f, %.3f)\n", v->color.x, v->color.y, v->color.z);
    //         printf("  Normal:   (%.3f, %.3f, %.3f)\n\n", v->normal.x, v->normal.y, v->normal.z);
    //     }
    // } else {
    //     printf("No vertex data.\n");
    // }
    //
    // if (vertices->indices.length > 0) {
    //     printf("Indices:\n");
    //     for (int i = 0; i < vertices->index_count; i++) {
    //         printf("  [%d] %d\n", i, array_get(vertices->indices, i, int));
    //     }
    //     printf("\n");
    // } else {
    //     printf("No index data.\n");
    // }
}
