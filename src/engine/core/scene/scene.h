//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_SCENE_H
#define C_3D_RENDERING_ENGINE_SCENE_H
#include "c_dynamic_array/cda.h"
#include "engine/Mesh/mesh.h"


typedef  struct {
    int totalObjects;
    d_array objects;
}Scene;

Scene initialize_scene();
void add_mesh(Scene *scene, Mesh mesh);
void remove_mesh(Scene *scene, Mesh *mesh);

#endif //C_3D_RENDERING_ENGINE_SCENE_H