//
// Created by arjun on 10/22/25.
//
#include "scene.h"
#include <stdlib.h>
#include <string.h>

Scene *initialize_scene() {
    Scene *scene = malloc(sizeof(Scene));
    scene->totalObjects = 0;
    scene->objects = NULL;
    return scene;
}
void add_mesh(Scene *scene, Mesh *mesh){
    scene->objects = realloc(scene->objects, sizeof(Mesh) * (scene->totalObjects + 1));
    if (!scene->objects) {
        scene->totalObjects = 0;
        return;
    }
    // Copy the new Object into the array
    scene->objects[scene->totalObjects] = mesh;
    scene->totalObjects++;
}

void remove_mesh(Scene *scene, Mesh *mesh) {
    if (!mesh ||scene->totalObjects == 0) return;

    int found_index = -1;
    for (int i = 0; i <scene->totalObjects; i++) {
        if (memcmp(&scene->objects[i], mesh, sizeof(Mesh)) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) return;
    for (int i = found_index; i <scene->totalObjects - 1; i++) {
        scene->objects[i] = scene->objects[i + 1];
    }

   scene->totalObjects--;
    if (mesh->vertices->vertex_count > 0) {
        scene->objects = realloc(scene->objects, sizeof(Mesh) *scene->totalObjects);
    } else {
        free(scene->objects);
        scene->objects = NULL;
    }
}