//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_VEC3_H
#define C_3D_RENDERING_ENGINE_VEC3_H

 struct vec3 {
    float x;
    float y;
    float z;
} ;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec3d;

struct vec3 init_vec3(float x, float y, float z);
void copyVec3(struct vec3 *dest, struct vec3 *src);
void normalizeVec3(struct vec3 *v);
#endif //C_3D_RENDERING_ENGINE_VEC3_H