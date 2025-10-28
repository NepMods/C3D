#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 cColor;
out vec3 FragPos;
out vec3 Normal;

void main(){
     vec4 worldPos = model * vec4(aPos, 1.0);  // object → world space
    FragPos = worldPos.xyz;
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    cColor = vec4(aColor, 1.0);
    //gl_Position = vec4(aPos, 1.0);
}