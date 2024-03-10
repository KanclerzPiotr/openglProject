#version 330 core

out vec4 FragColor; 

uniform int N;
uniform vec2 resolution;

void main() {

    float red = gl_FragCoord.x / resolution.x;
    float green = gl_FragCoord.y / resolution.y;
    float blue = gl_PrimitiveID / N; 
    FragColor = vec4(red, green, blue, 1.0); 
}