//
// Created by arjun on 10/22/25.
//

#include "Triangle.h"

#include <stdio.h>
#include "math.h"
#include "engine/helper/helper.h"

struct Triangle init_triangle(struct vec2 a, struct vec2 b, struct vec2 c) {
    struct Triangle t;
    t.a = vec2ToVec3(a);
    t.b = vec2ToVec3(b);
    t.c = vec2ToVec3(c);
    return t;
}
struct Triangle init_triangle_3(struct vec3 a, struct vec3 b, struct vec3 c) {
    struct Triangle t;
    t.a = (a);
    t.b = (b);
    t.c = (c);
    return t;
}
struct  vec3 getNormalVector(struct  Triangle t) {
    struct vec3 line1 = vec3_sub(t.b, t.a);

    struct vec3 line2 = vec3_sub(t.c, t.a);
    struct vec3 cross = vec3_cross(line1, line2);
    float l = vec3_len(cross);
    struct vec3 normalized = vec3_div(cross, l);

    return normalized;
}
void calculate_triangle_vertices(struct  Triangle t, struct Vertices *vertices) {
    struct vec3 normal = getNormalVector(t);
    int v1 = add_vertex(vertices, initialize_vertex_with_normal(t.a, getColor().red, normal));
    int v2 = add_vertex(vertices, initialize_vertex_with_normal(t.b, getColor().red, normal));
    int v3 = add_vertex(vertices, initialize_vertex_with_normal(t.c, getColor().red, normal));
    int indices[] = {v1, v2, v3};
    add_indices(vertices, indices, 3, 3);
}
void print_triangle(const struct Triangle *t) {
    if (!t) {
        printf("Triangle: (null)\n");
        return;
    }

    printf("Triangle:\n");
    printf("  A: (%.3f, %.3f, %.3f)\n", t->a.x, t->a.y, t->a.z);
    printf("  B: (%.3f, %.3f, %.3f)\n", t->b.x, t->b.y, t->b.z);
    printf("  C: (%.3f, %.3f, %.3f)\n", t->c.x, t->c.y, t->c.z);
}