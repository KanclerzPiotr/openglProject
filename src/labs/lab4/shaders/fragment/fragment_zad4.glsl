#version 330 core

out vec4 FragColor; 

in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main() {

    vec4 color = texture(texture1, texCoords);
    FragColor = color;
    // FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    
}