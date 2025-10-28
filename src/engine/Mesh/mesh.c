//
// Created by arjun on 10/23/25.
//
#include "mesh.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine/helper/helper.h"
#include "engine/triangle/Triangle.h"

void mesh_update(void *mesh_o, double time) {
    Mesh *mesh = (Mesh *)mesh_o;
    // for (int i = 0; i < mesh->num_objects; i++) {
    //     Object *object = (mesh->objects[i]);
    //     object->update(object, time);
    // }
    if (mesh->transform) {
        transform_update(mesh->transform);
    }
    if (mesh->customUpdate) {
        mesh->customUpdate(mesh, time);
    }
}
Mesh* from_raw(float *vertices, int num_vertices, int *indices, int num_indices) {
    Mesh *mesh = initialize_mesh();
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
        glBufferData(GL_ARRAY_BUFFER, mesh->vertices->vertex_count * sizeof(Vertex), mesh->vertices->vertex, mesh->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->vertices->index_count * sizeof(int), mesh->vertices->indices, mesh->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        /*
         * Shader Layout
         */
        glBindVertexArray(mesh->VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    }
}
void mesh_customUpdate(void *mesh, double time) {

}

Mesh *initialize_mesh() {

    Mesh *mesh = malloc(sizeof(Mesh));
    mesh->update = mesh_update;
    mesh->customUpdate = mesh_customUpdate;
    mesh->transform = init_transform();
    mesh->dynamic = 0;
    mesh->VAO = -1;
    mesh->VBO = -1;
    mesh->EBO = -1;
    mesh->uploaded = 0;
    mesh->vertices = initialize_vertices();

    /*
     * CREATE THE BUFFER IN GPU MEMORY
     */
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    /*
     * BIND THE BUFFERS TO ITS TYPE
     */
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);


    return mesh;
}

//
// void add_object(Mesh *mesh, Object *object){
//      mesh->objects = realloc(mesh->objects, sizeof(Object) * (mesh->num_objects + 1));
//     if (!mesh->objects) {
//         mesh->num_objects = 0;
//         return;
//     }
//     // Copy the new Object into the array
//     mesh->objects[mesh->num_objects] = object;
//     mesh->num_objects++;
// }
//
// void add_objects(Mesh *scene, Object **objects, int num_objects) {
//     for (int i = 0; i < num_objects; i++) {
//         add_object(scene, objects[i]);
//     }
// }
// void remove_object(Mesh *mesh, Object *object) {
//     if (!object ||mesh->num_objects == 0) return;
//
//     int found_index = -1;
//     for (int i = 0; i <mesh->num_objects; i++) {
//         if (memcmp(&mesh->objects[i], object, sizeof(Object)) == 0) {
//             found_index = i;
//             break;
//         }
//     }
//     if (found_index == -1) return;
//     for (int i = found_index; i <mesh->num_objects - 1; i++) {
//         mesh->objects[i] = mesh->objects[i + 1];
//     }
//
//     mesh->num_objects--;
//     if (object->total_vertices > 0) {
//         mesh->objects = realloc(mesh->objects, sizeof(Object) *mesh->num_objects);
//     } else {
//         free(mesh->objects);
//         mesh->objects = NULL;
//     }
// }

void on_update_mesh(Mesh *mesh ,update_function function) {
    mesh->customUpdate = function;
}
Mesh *load_from_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Failed to open file");
        return 0;
    }
    Mesh *mesh = initialize_mesh();
    int total_vertices = 0;
    vec3 *vertices = (vec3 *)malloc(sizeof(vec3) * 1);
    Color color = getColor();

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\0' || line[0] == '\n')
            continue;

        if (line[0] == 'v') {
            if (line[0] == 'v') {
                float x, y, z;
                if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
                    vec3 *tmp = realloc(vertices, sizeof(vec3) * (total_vertices + 1));
                    if (!tmp) { free(vertices); return NULL; }
                    vertices = tmp;
                    vertices[total_vertices++] = Vec3(x, y, z);
                }
            }
        }

        if (line[0] == 'f') {
            int f0, f1, f2;
            if (sscanf(line, "f %d %d %d", &f0, &f1, &f2) == 3) {
                if (f0-1 < total_vertices && f1-1 < total_vertices && f2-1 < total_vertices) {
                    Triangle tri = init_triangle_3(vertices[f0-1], vertices[f1-1], vertices[f2-1]);
                    calculate_triangle_vertices(tri, mesh->vertices);
                }
            }
        }
    }

    fclose(f);
    return mesh; // true
}
