//
// Created by arjun on 10/22/25.
//
#include "scene.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_dynamic_array/cda.h"
Scene initialize_scene() {
    Scene scene;
    scene.objects = array_init(100, sizeof(Mesh));
    scene.totalObjects = 0;
    return scene;
}
void add_mesh(Scene *scene, Mesh mesh){
    __array_append(&scene->objects, &mesh);
    scene->totalObjects++;
}

void remove_mesh(Scene *scene, Mesh *mesh) {
    iterable_t found = array_find_type(&scene->objects, Mesh *, mesh);
    if (found.valid) {
        array_remove(&scene->objects, found);
    }
}