
#include "vec3.h"
#include <math.h>
struct vec3 init_vec3(float x, float y, float z) {
    return (struct vec3) {x, y, z};
}
void normalizeVec3(struct vec3 *v) {
    float len = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
    if (len > 0.0f) {
        v->x /= len;
        v->y /= len;
        v->z /= len;
    }
}

void copyVec3(struct vec3 *dest, struct vec3 *src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}