//
// Created by arjun on 10/22/25.
//

#include "object.h"

#include <math.h>

#include "engine/helper/helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine/triangle/Triangle.h"
vec3 Camera  = {0, 0, 0};
vec3 Light = {0, 0, -1};
void noUpdate(void *k,double d) {
    // printf("NoUpdate\n");
}
Object *initialize_object() {
    Object *object = malloc(sizeof(Object));
    object->total_vertices = 0;
    object->vertices = NULL;
    object->update = noUpdate;
    return object;
}
void add_vertex(Object *object, Vertex *vertex) {
    object->vertices = realloc(object->vertices, sizeof(Vertex) * (object->total_vertices + 1));
    if (!object->vertices) {
        object->total_vertices = 0;
        return;
    }
    object->vertices[object->total_vertices] = *vertex;
    object->total_vertices++;
}

void remove_vertex(Object *object, Vertex *vertex) {
    if (!object || object->total_vertices == 0) return;

    int found_index = -1;
    for (int i = 0; i < object->total_vertices; i++) {
        if (memcmp(&object->vertices[i], vertex, sizeof(Vertex)) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) return;
    for (int i = found_index; i < object->total_vertices - 1; i++) {
        object->vertices[i] = object->vertices[i + 1];
    }

    object->total_vertices--;
    if (object->total_vertices > 0) {
        object->vertices = realloc(object->vertices, sizeof(Vertex) * object->total_vertices);
    } else {
        free(object->vertices);
        object->vertices = NULL;
    }
}

void on_update(Object *object, update_function update) {
    object->update = update;
}

int printed = 3;
VertexArray get_vertex_screen(Object *obj, matrix4x4 projection, int height, int width) {
    Vertex *new_vertices = malloc(sizeof(Vertex) * obj->total_vertices);
    for (int i = 0; i < obj->total_vertices; i++) {
        Vertex *vertex = &obj->vertices[i];
        new_vertices[i] = *vertex;
        new_vertices[i].position.z += 15.0f;
    }
    Triangle triangle = from_vertices(new_vertices, obj->total_vertices);

    vec3 normal = getNormalVector(triangle);
    vec3 CamToTri = vec3_sub(triangle.a, Camera);
    float projected_visibility = vec3_dot(normal, CamToTri);

    if (projected_visibility > 0) {
        return (VertexArray){new_vertices, 0};
    }
    float l = vec3_len(Light);
    Light = vec3_div(Light, l);

    float dp_light = vec3_dot(normal, Light);
    for (int i = 0; i < obj->total_vertices; i++) {
        Vertex *vertex = &obj->vertices[i];
        new_vertices[i] = *vertex;
        new_vertices[i].position.z += 5.0f;

        vec3 color = color_with_luminance(vertex->color, dp_light);

        vec3d current_pos = multiplyMatrix4x4AndVec3(new_vertices[i].position, projection);

        new_vertices[i].position = (vec3){current_pos.x, current_pos.y, current_pos.z};
        new_vertices[i].color = color;
    }
    return (VertexArray){new_vertices, 1};
}