//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_OBJECT_H
#define C_3D_RENDERING_ENGINE_OBJECT_H
#include "engine/core/matrix4x4/matrix4x4.h"
#include "engine/vertex/vertex.h"
#include "glad/glad.h"


typedef void (*update_function)(void *, double);

typedef struct {
    GLenum mode;
    int total_vertices;
    Vertex *vertices;

    update_function update;
} Object;

Object *initialize_object();
void add_vertex(Object *object, Vertex *vertex);
void remove_vertex(Object *object, Vertex *vertex);
void on_update(Object *obj, update_function update);
VertexArray get_vertex_screen(Object *obj, matrix4x4 projection, int height, int width);

#endif //C_3D_RENDERING_ENGINE_OBJECT_H