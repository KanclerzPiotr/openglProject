#version 330 core

out vec4 FragColor; 

void main() {
    FragColor = vec4(1.0f/gl_PrimitiveID, 0.0f, 1.0f - (1.0f/gl_PrimitiveID), 1); 
}