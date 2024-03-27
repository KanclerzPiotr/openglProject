#include <common/Mesh.hpp>

template<>
void Mesh<Vertex>::bindAttribPointers() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);
}

template<>
void Mesh<SimpleVertex>::bindAttribPointers() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)0);
    glEnableVertexAttribArray(0);
}

template<>
void Mesh<ColorVertex>::bindAttribPointers() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, color));
    glEnableVertexAttribArray(1);
}