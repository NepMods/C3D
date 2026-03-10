//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_MATRIX4X4_H
#define C_3D_RENDERING_ENGINE_MATRIX4X4_H
#include "engine/vec3/vec3.h"

typedef struct {
    float a[4][4];
} matrix4x4;

/*
 *  Generates a 4x4 Identity Matrix
 */
matrix4x4 mat4_identity();

/*
 *  Translate vec3 to matrix
 */
matrix4x4 translate(struct vec3 t);

/*
 * Multiply Matrix -> matrix4x4
 * Multiply Matrix with vector -> vec3d
 */
matrix4x4 multiplyMatrix4x4(matrix4x4 m1, matrix4x4 m2);
vec3d multiplyMatrix4x4AndVec3(struct vec3 in, matrix4x4 m);

/*
 * Rotate Matrix
 */
matrix4x4 rotX(double angle);
matrix4x4 rotY(double angle);
matrix4x4 rotZ(double angle);

/*
 *  Inverse
 */
matrix4x4 Inverse(matrix4x4 m);

/*
 * Debug Print Func
 */
void printMatrix4x4(matrix4x4 m);

#endif //C_3D_RENDERING_ENGINE_MATRIX4X4_H