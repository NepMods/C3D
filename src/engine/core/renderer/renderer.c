//
// Created by arjun on 10/22/25.
//
#include <stdio.h>
#include "renderer.h"
#include "engine/core/shader/shader.h"
#include <stdlib.h>
#include <math.h>

#include "engine/core/Camera/Camera.h"
#include "engine/helper/helper.h"
#include "engine/object/object.h"

#include "glad/glad.h"

static void error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int width = 800;
int height = 800;
char *title = "C3D";
Renderer *main_renderer;

void setRendererWindowData(int height_p, int width_p, char *title_p) {
    width = width_p;
    height = height_p;
    title = title_p;
}
Renderer *get_main_renderer() {
    if (main_renderer) {
        return main_renderer;
    }

    main_renderer = init_renderer(height, width, "Hello World");
    return main_renderer;
}

Renderer *__create_renderer() {
    Renderer *r = (Renderer *) malloc(sizeof(Renderer));
    r->width = 0;
    r->height = 0;
    r->initialized = 0;
    r->window = NULL;
    r->shaderProgram = 1;
    r->VAO = -1;
    r->VBO = -1;
    r->cameraFront = (vec3){0.0f, 0.0f, -1.0f};
    return r;
}

void destroy_renderer(Renderer *renderer) {
    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glDeleteProgram(renderer->shaderProgram);
    glfwDestroyWindow(renderer->window);
    glfwTerminate();
    free(renderer);
}
Renderer *init_renderer(int height, int width, char *title) {

    /*
     * INITIALIZE THE Renderer
     */
    Renderer *r = __create_renderer();

    /*
     * INITIALIZE OPENGL
     */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return r;


    /*
     * SET OPENGL VERSION
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /*
     * INITIALIZE OPENGL WINDOW
     */
    r->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!r->window) { glfwTerminate(); return r; }

    glfwMakeContextCurrent(r->window);
    glfwSetFramebufferSizeCallback(r->window, framebuffer_size_callback);

    /*
     * INITIALIZE OPENGL RENDERER
     */

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        r->initialized = 0;
        return r;
    }

    /*
     * INITIALIZE SHADER PROGRAM AND COMPILE SHADERS
     */
    r->shaderProgram = create_shader_program();
    glUseProgram(r->shaderProgram);


    // --------------------------
    // VAO/VBO setup
    // --------------------------

    glGenVertexArrays(1, &r->VAO);
    glGenBuffers(1, &r->VBO);
    glBindVertexArray(r->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBufferData(GL_ARRAY_BUFFER, 10240 * sizeof(Vertex), 0, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    /*
     * GET WINDOW SIZE
     */
    int width_win, height_win;
    glfwGetWindowSize(r->window, &width_win, &height_win);
    r->width = width_win;
    r->height = height_win;

    r->initialized = 1;
    return  r;
}

int print = 0;

void renderer_polling(Renderer *r) {
    while (!glfwWindowShouldClose(r->window)) {
        glfwPollEvents();
        if (glfwGetKey(r->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(r->window, 1);

        Camera *camera = get_main();
        camera_update(camera);

        glClearColor(0.1f,0.12f,0.15f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double time = glfwGetTime();
        double deltaTime = time - r->currentTime;
        r->currentTime = time;
        r->deltaTime = deltaTime;
        glUseProgram(r->shaderProgram);
        r->modelLoc = glGetUniformLocation(r->shaderProgram, "model");
        r->viewLoc = glGetUniformLocation(r->shaderProgram, "view");
        r->projLoc = glGetUniformLocation(r->shaderProgram, "projection");
        glBindVertexArray(r->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, r->VBO);



        glUniformMatrix4fv(r->viewLoc, 1, GL_TRUE, (float *)camera->view.a);
        glUniformMatrix4fv(r->projLoc, 1, GL_TRUE, (float *)camera->projection.a);
        if (!print) {
            printf("View Matrix: \n");
            printMatrix4x4(camera->view);

            printf("Projection Matrix: \n");
            printMatrix4x4(camera->projection);
        }
        for (int i = 0; i < r->currentScene->totalObjects; i++) {
            Mesh *curMesh =  r->currentScene->objects[i];
            curMesh->update(curMesh, r->deltaTime);

            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(curMesh->VAO);

            glUniformMatrix4fv(r->modelLoc, 1, GL_TRUE, (float *)curMesh->transform->model.a);
            if (!print) {

                printf("Model Matrix: \n");
                printMatrix4x4(curMesh->transform->model);
                print = 1;
            }

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, curMesh->num_indexes, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // for (int i = 0; i < curMesh->num_objects; i ++) {
            //     Object *obj = curMesh->objects[i];
            //     matrix4x4 projectionMatrix = get_projection_matrix(r->height, r->width, 90.0f, 1000.0f, 0.1f);
            //     VertexArray new_vertex = get_vertex_screen(obj, projectionMatrix, r->height, r->width);
            //     if (new_vertex.rendered) {
            //          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //          glBufferSubData(GL_ARRAY_BUFFER, 0, obj->total_vertices * sizeof(Vertex), new_vertex.vertex);
            //          glDrawArrays(GL_TRIANGLES, 0, obj->total_vertices);
            //      }
            //      free(new_vertex.vertex);
            // }

        }

        glfwSwapBuffers(r->window);
    }
}