#version 330 core

uniform vec3 lightDir;
uniform vec3 lightColor;

in vec4 cColor;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;
void main(){
       vec3 norm = normalize(Normal);
        float diff = max(dot(norm, -normalize(lightDir)), 0.0);
        vec3 color = diff * lightColor;
        FragColor = vec4(color, 1.0);
}