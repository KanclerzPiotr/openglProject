#version 330 core

out vec4 FragColor; 
in float height;


void main() {

    if (height < 0.1) {
        FragColor = vec4(0.647, 0.165, 0.165, 1.0);
    } else 
        FragColor = vec4(0.0, 1.0, 0.0, 1.0); 
}