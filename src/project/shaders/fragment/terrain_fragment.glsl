#version 330 core

out vec4 FragColor; 

in vec2 fragTexCoords;
in float height;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    vec4 c1 = texture(texture0, fragTexCoords);
    vec4 c2 = texture(texture1, fragTexCoords);
    vec4 c3 = texture(texture2, fragTexCoords);

    if (height < 0.17) {
        FragColor = c3;
    } else if (height < 0.23) {
        FragColor = mix(c3, c2, (height - 0.17) / 0.06);
    } else if (height < 0.35) {
        FragColor = c2;
    } else if (height < 0.41) {
        FragColor = mix(c2, c1, (height - 0.35) / 0.06);
    } else {
        FragColor = c1;
    }
    
}