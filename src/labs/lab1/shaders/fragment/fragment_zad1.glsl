#version 330 core
in vec3 vertexColor; // Zmienna wejściowa z shadera wierzchołków

out vec4 FragColor; // Wyjście koloru fragmentu

void main() {
    FragColor = vec4(vertexColor, 1.0); // Ustawienie koloru fragmentu
}