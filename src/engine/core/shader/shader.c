//
// Created by arjun on 10/22/25.
//

#include "shader.h"

#include <stdlib.h>
#include <string.h>

#include "stdio.h"
#include "vertex_shader.h"
#include "fragment_shader.h"

GLuint create_shader_program() {

    char* vs_str = malloc(assets_shaders_vertex_shader_glsl_len + 1);
    memcpy(vs_str, assets_shaders_vertex_shader_glsl, assets_shaders_vertex_shader_glsl_len);
    vs_str[assets_shaders_vertex_shader_glsl_len] = '\0';

    char* fr_str = malloc(assets_shaders_fragment_shader_glsl_len + 1);
    memcpy(fr_str, assets_shaders_fragment_shader_glsl, assets_shaders_fragment_shader_glsl_len);
    fr_str[assets_shaders_fragment_shader_glsl_len] = '\0';

    GLuint vs = compile_shader(GL_VERTEX_SHADER, vs_str);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fr_str);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        fprintf(stderr, "Program link error: %s\n", log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        fprintf(stderr, "Shader compile error: %s\n", log);
        return 0;
    }
    return shader;
}
