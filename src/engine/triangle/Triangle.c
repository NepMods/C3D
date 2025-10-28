//
// Created by arjun on 10/22/25.
//

#include "Triangle.h"

#include <stdio.h>
#include "math.h"
#include "engine/helper/helper.h"

Triangle init_triangle(vec2 a, vec2 b, vec2 c) {
    Triangle t;
    t.a = vec2ToVec3(a);
    t.b = vec2ToVec3(b);
    t.c = vec2ToVec3(c);
    return t;
}
Triangle init_triangle_3(vec3 a, vec3 b, vec3 c) {
    Triangle t;
    t.a = (a);
    t.b = (b);
    t.c = (c);
    return t;
}
vec3 getNormalVector(Triangle t) {
    vec3 line1 = vec3_sub(t.b, t.a);

    vec3 line2 = vec3_sub(t.c, t.a);
    vec3 cross = vec3_cross(line1, line2);
    float l = vec3_len(cross);
    vec3 normalized = vec3_div(cross, l);

    return normalized;
}
void calculate_triangle_vertices(Triangle t, Vertices *vertices) {
    // int v1 = add_vertex(vertices, t.a);
    // int v2 = add_vertex(vertices, t.b);
    // int v3 = add_vertex(vertices, t.c);

    // int indices[] = {v1, v2, v3};
    // add_indices(vertices, indices, 3, 3);
}