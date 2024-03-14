#version 330 core

out vec4 FragColor; 

uniform vec2 resolution;

void main() {

    float red = gl_FragCoord.x / resolution.x;
    float green = gl_FragCoord.y / resolution.y;
    float blue = 1.0f; 
    FragColor = vec4(red, green, blue, 1.0); 
}