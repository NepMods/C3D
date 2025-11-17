//
// Created by arjun on 10/23/25.
//
#include "mesh.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_dynamic_array/cda.h"
#include "engine/helper/helper.h"
#include "engine/triangle/Triangle.h"

void mesh_update(void *mesh_o, double time) {
    Mesh *mesh = (Mesh *)mesh_o;
    // for (int i = 0; i < mesh->num_objects; i++) {
    //     Object *object = (mesh->objects[i]);
    //     object->update(object, time);
    // }

    transform_update(&mesh->transform);

    if (mesh->customUpdate) {
        mesh->customUpdate(mesh, time);
    }
}
Mesh from_raw(float *vertices, int num_vertices, int *indices, int num_indices) {
    Mesh mesh = initialize_mesh();
    // mesh->vertices = vertices;


    return mesh;
}

void upload_mesh(Mesh *mesh) {
    if (mesh && !mesh->uploaded) {

        /*
         * BIND THE BUFFERS TO ITS TYPE
         */
        glBindVertexArray(mesh->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

        /*
         * Copy the vertices and indices to GPU memory
         */
        glBufferData(GL_ARRAY_BUFFER, mesh->vertices.vertex_count * sizeof(struct Vertex),  array_get_data(&mesh->vertices.vertices), mesh->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->vertices.index_count * sizeof(int), array_get_data(&mesh->vertices.indices), mesh->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        /*
         * Shader Layout
         */
        glBindVertexArray(mesh->VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, color));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, normal));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
        mesh->uploaded = 1;
    }
}
void mesh_customUpdate(void *mesh, double time) {

}

Mesh initialize_mesh() {

    Mesh mesh;
    mesh.update = mesh_update;
    mesh.customUpdate = mesh_customUpdate;
    mesh.transform = init_transform();
    mesh.dynamic = 0;
    mesh.VAO = -1;
    mesh.VBO = -1;
    mesh.EBO = -1;
    mesh.uploaded = 0;
    mesh.vertices = initialize_vertices();

    /*
     * CREATE THE BUFFER IN GPU MEMORY
     */
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    /*
     * BIND THE BUFFERS TO ITS TYPE
     */
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);


    return mesh;
}

void on_update_mesh(Mesh *mesh ,update_function function) {
    mesh->customUpdate = function;
}
Mesh load_from_file(char *filename) {
    Mesh mesh = initialize_mesh();
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Failed to open file");
        return mesh;
    }
    int total_vertices = 0;
    d_array vertices = array_init(0, sizeof(struct vec3));

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\0' || line[0] == '\n')
            continue;

        if (line[0] == 'v') {
            if (line[0] == 'v') {
                float x, y, z;
                if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
                    struct vec3 tmp = init_vec3(x, y, z);
                    __array_append(&vertices, &tmp);
                    total_vertices++;
                }
            }
        }

        if (line[0] == 'f') {
            int f0, f1, f2;
            if (sscanf(line, "f %d %d %d", &f0, &f1, &f2) == 3) {
                if (f0-1 < total_vertices && f1-1 < total_vertices && f2-1 < total_vertices) {
                    struct Triangle tri = init_triangle_3(array_get(vertices, f0 -1 , struct vec3), array_get(vertices, f1 - 1, struct vec3), array_get(vertices, f2 - 1 , struct vec3));
                    calculate_triangle_vertices(tri, &mesh.vertices);
                }
            }
        }
    }

    fclose(f);
    return mesh; // true
}
