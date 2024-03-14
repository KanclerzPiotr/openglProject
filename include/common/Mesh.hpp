#ifndef COMMON_MESH_HPP
#define COMMON_MESH_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "common/Vertex.hpp"

enum PrimitiveType
{
    POINTS,
    LINES,
    LINE_STRIP,
    LINE_LOOP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN
};

template<typename T>
class Mesh
{
private:
    unsigned int VBO;
    unsigned int EBO; 
    PrimitiveType primitiveType;

void bindAttribPointers()
{
    if (std::is_same<T, Vertex>::value) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);
    } else if (std::is_same<T, SimpleVertex>::value) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)0);
        glEnableVertexAttribArray(0);
    } else if (std::is_same<T, ColorVertex>::value) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, color));
        glEnableVertexAttribArray(1);
    }
}

public:
    std::vector<T> vertices;
    std::vector<int> indices;
    unsigned int VAO;

Mesh(std::vector<T> vertices, std::vector<int> indices, PrimitiveType primitiveType)
{
    this->vertices = vertices;
    this->indices = indices;
    this->primitiveType = primitiveType;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    bindAttribPointers();

    glBindVertexArray(0);
}

~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void draw()
{
    glBindVertexArray(VAO);
    glDrawElements(primitiveType, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawArrays()
{
    glBindVertexArray(VAO);
    glDrawArrays(primitiveType, 0, vertices.size());
    glBindVertexArray(0);
};

void drawArrays(int first, int count)
{
    glBindVertexArray(VAO);
    glDrawArrays(primitiveType, first, count);
    glBindVertexArray(0);
};

void drawArrays(int first, int count, PrimitiveType primitive)
{
    glBindVertexArray(VAO);
    glDrawArrays(primitive, first, count);
    glBindVertexArray(0);
};

};

#endif // COMMON_MESH_HPP
