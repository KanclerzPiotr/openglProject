#version 330 core

out vec4 FragColor; 

in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main() {
    vec4 c1 = texture(texture1, texCoords);
    vec4 c2 = texture(texture2, texCoords);
    vec4 c3 = texture(texture3, texCoords);

    if (c3.r < 0.8 && c3.g < 0.8 && c3.b < 0.8) {
        FragColor = vec4(0.0, 1.0, 1.0, 1.0);
    } else {
        FragColor =  0.5 * c1 + 0.5 * c2;
    }
}