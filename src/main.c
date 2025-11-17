#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/renderer/renderer.h"
#include "math.h"
#include "engine/core/Camera/Camera.h"
#include "engine/core/transform/transform.h"
#include "engine/helper/helper.h"
#include "engine/triangle/Triangle.h"
#include "engine/vec2/vec2.h"
#include "engine/core/matrix4x4/matrix4x4.h"
#include "engine/Mesh/mesh.h"
#include "engine/Rect/Rect.h"
#include "engine/vec3/vec3.h"

Renderer *renderer;
double lastX = 0, lastY = 0;
float yaw = 0.0f, pitch = 0.0f;
int firstMouse = 1;
float sensitivity = 0.03f;
int mouseMoved = 0;
float rotationSpeed = 1.0f;

int invertYaw = 1;
int invertPitch = 1;



void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
        return;
    }

    mouseMoved = 1;

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (invertYaw)  xoffset = -xoffset;
    if (invertPitch) yoffset = -yoffset;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    struct vec3 front;
    front.x = cos(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);
    front.y = sin(pitch * M_PI / 180.0);
    front.z = sin(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);

    normalizeVec3(&front);
    copyVec3(&renderer->cameraFront, &front);
}
void rotate_triangle(void *mesh_p, double deltaTime) {
    Mesh *mesh = (Mesh *)mesh_p;
    mesh->transform.rotation.y += 1.0f * deltaTime;

    // transform_update(mesh->transform);
}
Mesh get_Ship() {
    Mesh ship = load_from_file("../VideoShip.obj");

    on_update_mesh(&ship, rotate_triangle);

    // on_update_mesh(ship, rotateCube3d);
    return  ship;
}

Mesh getTeapot() {
    Mesh ship = load_from_file("../dragon.obj");
    on_update_mesh(&ship, rotate_triangle);
    return  ship;
}

Mesh getAxis() {
    Mesh ship = load_from_file("../axis.obj");

    on_update_mesh(&ship, rotate_triangle);
    return  ship;
}




Mesh old_get3dCube() {
    Mesh cube = initialize_mesh();

    // FRONT (Z = 0)
    calculate_rect_vertices(init_rect(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(1, 1, 0), Vec3(1, 0, 0)), &cube.vertices);

    // // LEFT (X = 0)
    calculate_rect_vertices(init_rect(Vec3(0, 0, 1), Vec3(0, 1, 1), Vec3(0, 1, 0), Vec3(0, 0, 0)), &cube.vertices);

    // BACK (Z = 1)
    calculate_rect_vertices(init_rect(Vec3(1, 0, 1), Vec3(1, 1, 1), Vec3(0, 1, 1), Vec3(0, 0, 1)), &cube.vertices);

    // RIGHT (X = 1)
    calculate_rect_vertices(init_rect(Vec3(1, 0, 0), Vec3(1, 1, 0), Vec3(1, 1, 1), Vec3(1, 0, 1)), &cube.vertices);

    // TOP (Y = 1)
    calculate_rect_vertices(init_rect(Vec3(0, 1, 0), Vec3(0, 1, 1), Vec3(1, 1, 1), Vec3(1, 1, 0)), &cube.vertices);

    // BOTTOM (Y = 0)
    calculate_rect_vertices(init_rect(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(1, 0, 1)), &cube.vertices);

    // Rotation hook
    on_update_mesh(&cube, rotate_triangle);

    return cube;
}


Mesh basic_triangle() {
    Mesh mesh = initialize_mesh();
    struct Triangle triangle = init_triangle((struct vec2){0, 0}, (struct  vec2){0, 1}, ( struct vec2){2, 0}) ;
    calculate_triangle_vertices(triangle, &mesh.vertices);
    on_update_mesh(&mesh, rotate_triangle);
    return mesh;
}


int main(void) {
    setRendererWindowData(800, 800, "C3D Rendering Engine");

    Scene scene = initialize_scene();

    renderer = get_main_renderer();
    renderer->currentScene = &scene;
    Mesh teapot = getTeapot();
    add_mesh(&scene, teapot);
    // print_vertices(&teapot.vertices);



    // glfwSetCursorPosCallback(renderer->window, mouse_callback);
    // glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    renderer_polling(renderer);
    destroy_renderer(renderer);
    // free(scene);

    return 0;
}
