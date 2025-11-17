//
// Created by arjun on 10/23/25.
//

#include "Rect.h"

#include <stdlib.h>

Rect* init_rect(struct vec3 p1, struct vec3 p2, struct vec3 p3, struct vec3 p4) {
    Rect* r = (Rect*)malloc(sizeof(Rect));
    r->s1 = init_triangle_3(p1, p2, p3);
    r->s2 = init_triangle_3(p3, p4, p1);
    return r;
}
void calculate_rect_vertices(Rect* r, struct Vertices *vertices) {
    calculate_triangle_vertices(r->s1, vertices);
    calculate_triangle_vertices(r->s2, vertices);
}