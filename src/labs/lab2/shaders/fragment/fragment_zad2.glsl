#version 330 core

out vec4 FragColor; 

uniform float N;

void main() {

    float color = gl_PrimitiveID / N;
    FragColor = vec4(color, color, color, 1.0); 
}