#version 330 core

out vec4 FragColor; 

vec3 colorLUT[9] = vec3[](
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 1.0, 1.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 1.0),
    vec3(1.0, 1.0, 0.0),
    vec3(1.0, 1.0, 1.0),
    vec3(0.5, 0.5, 0.5)
);


void main() {

    FragColor = vec4(colorLUT[gl_PrimitiveID%9], 1.0); 
}