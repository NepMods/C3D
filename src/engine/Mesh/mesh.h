//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_MESH_H
#define C_3D_RENDERING_ENGINE_MESH_H
#include "engine/core/transform/transform.h"
#include "engine/core/vertex/vertex.h"
#include "glad/glad.h"

typedef void (*update_function)(void *, double);




typedef struct {
    Transform transform;

    struct Vertices vertices;

    GLuint VAO, VBO, EBO;
    int dynamic;
    int uploaded;

    update_function update;
    update_function customUpdate;
} Mesh;

Mesh initialize_mesh();
Mesh from_raw(float *vertices, int num_vertices, int *indices, int num_indices);
void upload_mesh(Mesh *mesh);

void on_update_mesh(Mesh *mesh, update_function function);
Mesh load_from_file(char *filename);

#endif //C_3D_RENDERING_ENGINE_MESH_H