//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_RENDERER_H
#define C_3D_RENDERING_ENGINE_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/scene/scene.h"
#include "engine/core/Light/Light.h"
typedef struct {
    int initialized;


    GLFWwindow* window;
    GLuint shaderProgram;
    GLuint VAO, VBO;
    Scene *currentScene;

    double currentTime;
    double deltaTime;

    struct Light mainLight;

    int width, height;
    struct vec3 cameraFront;
    GLint modelLoc, viewLoc, projLoc, lightDirLoc, lightColorLoc;
} Renderer;

void setRendererWindowData(int height, int width, char *title);
Renderer *get_main_renderer();
Renderer __create_renderer();
Renderer init_renderer(int height, int width, char *title);
void destroy_renderer(Renderer *renderer);

void renderer_polling(Renderer *r);

#endif //C_3D_RENDERING_ENGINE_RENDERER_H