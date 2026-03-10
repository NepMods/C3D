#include "matrix4x4.h"

#include <stdio.h>

#include "math.h"


matrix4x4 multiplyMatrix4x4(matrix4x4 m1, matrix4x4 m2) {
    matrix4x4 result = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.a[i][j] =
                m1.a[i][0] * m2.a[0][j] +
                m1.a[i][1] * m2.a[1][j] +
                m1.a[i][2] * m2.a[2][j] +
                m1.a[i][3] * m2.a[3][j];
        }
    }
    return result;
}

vec3d multiplyMatrix4x4AndVec3(struct vec3 in, matrix4x4 m) {
    vec3d out = {0};

    out.x = in.x * m.a[0][0] + in.y * m.a[1][0] + in.z * m.a[2][0] + m.a[3][0];
    out.y = in.x * m.a[0][1] + in.y * m.a[1][1] + in.z * m.a[2][1] + m.a[3][1];
    out.z = in.x * m.a[0][2] + in.y * m.a[1][2] + in.z * m.a[2][2] + m.a[3][2];
    out.w = in.x * m.a[0][3] + in.y * m.a[1][3] + in.z * m.a[2][3] + m.a[3][3];

    if (out.w != 0.0f) {
        out.x /= out.w;
        out.y /= out.w;
        out.z /= out.w;

    }

    return out;
}


matrix4x4 rotX(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = 1;
    m.a[1][1] = cos(angle); m.a[1][2] = -sin(angle);
    m.a[2][1] = sin(angle); m.a[2][2] = cos(angle);
    m.a[3][3] = 1;
    return m;
}
matrix4x4 rotY(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = cos(angle);  m.a[0][2] = sin(angle);
    m.a[1][1] = 1;
    m.a[2][0] = -sin(angle); m.a[2][2] = cos(angle);
    m.a[3][3] = 1;
    return m;
}


matrix4x4 rotZ(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = cos(angle); m.a[0][1] = -sin(angle);
    m.a[1][0] = sin(angle); m.a[1][1] = cos(angle);
    m.a[2][2] = 1; m.a[3][3] = 1;
    return m;
}
matrix4x4 mat4_identity() {
    matrix4x4 m = {0};
    m.a[0][0] = 1.0f;
    m.a[1][1] = 1.0f;
    m.a[2][2] = 1.0f;
    m.a[3][3] = 1.0f;
    return m;
}

matrix4x4 translate(struct vec3 t) {
    matrix4x4 m = mat4_identity();
    m.a[0][3] = t.x;
    m.a[1][3] = t.y;
    m.a[2][3] = t.z;
    return m;
}


#ifndef EPSILON
#define EPSILON 1e-6f
#endif

matrix4x4 Inverse(matrix4x4 m) {
    matrix4x4 inv;
    float invOut[16];
    float det;
    float invDet;
    float mat[16];
    int i;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            mat[r * 4 + c] = m.a[r][c];
        }
    }

    invOut[0] = mat[5]  * mat[10] * mat[15] -
                mat[5]  * mat[11] * mat[14] -
                mat[9]  * mat[6]  * mat[15] +
                mat[9]  * mat[7]  * mat[14] +
                mat[13] * mat[6]  * mat[11] -
                mat[13] * mat[7]  * mat[10];

    invOut[4] = -mat[4]  * mat[10] * mat[15] +
                 mat[4]  * mat[11] * mat[14] +
                 mat[8]  * mat[6]  * mat[15] -
                 mat[8]  * mat[7]  * mat[14] -
                 mat[12] * mat[6]  * mat[11] +
                 mat[12] * mat[7]  * mat[10];

    invOut[8] = mat[4]  * mat[9] * mat[15] -
                mat[4]  * mat[11] * mat[13] -
                mat[8]  * mat[5] * mat[15] +
                mat[8]  * mat[7] * mat[13] +
                mat[12] * mat[5] * mat[11] -
                mat[12] * mat[7] * mat[9];

    invOut[12] = -mat[4]  * mat[9] * mat[14] +
                  mat[4]  * mat[10] * mat[13] +
                  mat[8]  * mat[5] * mat[14] -
                  mat[8]  * mat[6] * mat[13] -
                  mat[12] * mat[5] * mat[10] +
                  mat[12] * mat[6] * mat[9];

    invOut[1] = -mat[1]  * mat[10] * mat[15] +
                 mat[1]  * mat[11] * mat[14] +
                 mat[9]  * mat[2] * mat[15] -
                 mat[9]  * mat[3] * mat[14] -
                 mat[13] * mat[2] * mat[11] +
                 mat[13] * mat[3] * mat[10];

    invOut[5] = mat[0]  * mat[10] * mat[15] -
                mat[0]  * mat[11] * mat[14] -
                mat[8]  * mat[2] * mat[15] +
                mat[8]  * mat[3] * mat[14] +
                mat[12] * mat[2] * mat[11] -
                mat[12] * mat[3] * mat[10];

    invOut[9] = -mat[0]  * mat[9] * mat[15] +
                 mat[0]  * mat[11] * mat[13] +
                 mat[8]  * mat[1] * mat[15] -
                 mat[8]  * mat[3] * mat[13] -
                 mat[12] * mat[1] * mat[11] +
                 mat[12] * mat[3] * mat[9];

    invOut[13] = mat[0]  * mat[9] * mat[14] -
                 mat[0]  * mat[10] * mat[13] -
                 mat[8]  * mat[1] * mat[14] +
                 mat[8]  * mat[2] * mat[13] +
                 mat[12] * mat[1] * mat[10] -
                 mat[12] * mat[2] * mat[9];

    invOut[2] = mat[1]  * mat[6] * mat[15] -
                mat[1]  * mat[7] * mat[14] -
                mat[5]  * mat[2] * mat[15] +
                mat[5]  * mat[3] * mat[14] +
                mat[13] * mat[2] * mat[7] -
                mat[13] * mat[3] * mat[6];

    invOut[6] = -mat[0]  * mat[6] * mat[15] +
                 mat[0]  * mat[7] * mat[14] +
                 mat[4]  * mat[2] * mat[15] -
                 mat[4]  * mat[3] * mat[14] -
                 mat[12] * mat[2] * mat[7] +
                 mat[12] * mat[3] * mat[6];

    invOut[10] = mat[0]  * mat[5] * mat[15] -
                 mat[0]  * mat[7] * mat[13] -
                 mat[4]  * mat[1] * mat[15] +
                 mat[4]  * mat[3] * mat[13] +
                 mat[12] * mat[1] * mat[7] -
                 mat[12] * mat[3] * mat[5];

    invOut[14] = -mat[0]  * mat[5] * mat[14] +
                  mat[0]  * mat[6] * mat[13] +
                  mat[4]  * mat[1] * mat[14] -
                  mat[4]  * mat[2] * mat[13] -
                  mat[12] * mat[1] * mat[6] +
                  mat[12] * mat[2] * mat[5];

    invOut[3] = -mat[1] * mat[6] * mat[11] +
                 mat[1] * mat[7] * mat[10] +
                 mat[5] * mat[2] * mat[11] -
                 mat[5] * mat[3] * mat[10] -
                 mat[9] * mat[2] * mat[7] +
                 mat[9] * mat[3] * mat[6];

    invOut[7] = mat[0] * mat[6] * mat[11] -
                mat[0] * mat[7] * mat[10] -
                mat[4] * mat[2] * mat[11] +
                mat[4] * mat[3] * mat[10] +
                mat[8] * mat[2] * mat[7] -
                mat[8] * mat[3] * mat[6];

    invOut[11] = -mat[0] * mat[5] * mat[11] +
                  mat[0] * mat[7] * mat[9] +
                  mat[4] * mat[1] * mat[11] -
                  mat[4] * mat[3] * mat[9] -
                  mat[8] * mat[1] * mat[7] +
                  mat[8] * mat[3] * mat[5];

    invOut[15] = mat[0] * mat[5] * mat[10] -
                 mat[0] * mat[6] * mat[9] -
                 mat[4] * mat[1] * mat[10] +
                 mat[4] * mat[2] * mat[9] +
                 mat[8] * mat[1] * mat[6] -
                 mat[8] * mat[2] * mat[5];

    det = mat[0] * invOut[0] + mat[1] * invOut[4] + mat[2] * invOut[8] + mat[3] * invOut[12];

    if (fabsf(det) < EPSILON) {
        for (i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                inv.a[i][j] = 0.0f;
        return inv;
    }

    invDet = 1.0f / det;

    for (i = 0; i < 16; i++)
        invOut[i] *= invDet;

    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            inv.a[r][c] = invOut[r * 4 + c];

    return inv;
}

void printMatrix4x4(matrix4x4 m) {
    for (int i = 0; i < 4; i++) {
        printf("| ");
        for (int j = 0; j < 4; j++) {
            printf("%8.3f ", m.a[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}