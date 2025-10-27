//
// Created by arjun on 10/23/25.
//

#include "Rect.h"

#include <stdlib.h>

Rect* init_rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4) {
    Rect* r = (Rect*)malloc(sizeof(Rect));
    r->s1 = init_triangle_3(p1, p2, p3);
    r->s2 = init_triangle_3(p3, p4, p1);
    return r;
}
Mesh* get_rect_mesh(Rect* r, vec3 *colors, int num_colors) {
    Mesh* rect = initialize_mesh();
    Object *side1 = get_triangle_object_filled(r->s1, colors, num_colors);
    Object *side2 = get_triangle_object_filled(r->s2, colors, num_colors);
    // add_object(rect, side1);
    // add_object(rect, side2);
    return rect;
}