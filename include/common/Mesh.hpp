#ifndef COMMON_MESH_HPP
#define COMMON_MESH_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <fmt/core.h>
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

    void bindAttribPointers();
public:
    std::vector<T> vertices;
    std::vector<int> indices;
    unsigned int VAO;

    Mesh(std::vector<T>&& vertices, std::vector<int>&& indices, PrimitiveType primitiveType);
    Mesh(const Mesh& other);
    Mesh(Mesh&& other);
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh&& other);
    ~Mesh();
    void draw();
    void drawArrays();
    void drawArrays(int first, int count);
    void drawArrays(int first, int count, PrimitiveType primitive);
};

template<typename T>
Mesh<T>::Mesh(std::vector<T>&& vertices, std::vector<int>&& indices, PrimitiveType primitiveType)
{
    this->vertices = vertices;
    this->indices = indices;
    this->primitiveType = primitiveType;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), this->indices.data(), GL_STATIC_DRAW);

    bindAttribPointers();

    glBindVertexArray(0);
}

template<typename T>
Mesh<T>::Mesh(const Mesh& other)
{
    this->vertices = other.vertices;
    this->indices = other.indices;
    this->primitiveType = other.primitiveType;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), this->indices.data(), GL_STATIC_DRAW);

    bindAttribPointers();

    glBindVertexArray(0);
}

template<typename T>
Mesh<T>::Mesh(Mesh&& other)
{
    this->vertices = std::move(other.vertices);
    this->indices = std::move(other.indices);
    this->primitiveType = other.primitiveType;
    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->EBO = other.EBO;
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
}

template<typename T>
Mesh<T>& Mesh<T>::operator=(const Mesh& other)
{
    this->vertices = other.vertices;
    this->indices = other.indices;
    this->primitiveType = other.primitiveType;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), this->indices.data(), GL_STATIC_DRAW);

    bindAttribPointers();

    glBindVertexArray(0);

    return *this;
}

template<typename T>
Mesh<T>& Mesh<T>::operator=(Mesh&& other)
{
    this->vertices = std::move(other.vertices);
    this->indices = std::move(other.indices);
    this->primitiveType = other.primitiveType;
    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->EBO = other.EBO;
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;

    return *this;
}

template<typename T>
Mesh<T>::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

template<typename T>
void Mesh<T>::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(primitiveType, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

template<typename T>
void Mesh<T>::drawArrays()
{
    glBindVertexArray(VAO);
    glDrawArrays(primitiveType, 0, vertices.size());
    glBindVertexArray(0);
}

template<typename T>
void Mesh<T>::drawArrays(int first, int count)
{
    glBindVertexArray(VAO);
    glDrawArrays(primitiveType, first, count);
    glBindVertexArray(0);
}

template<typename T>
void Mesh<T>::drawArrays(int first, int count, PrimitiveType primitive)
{
    glBindVertexArray(VAO);
    glDrawArrays(primitive, first, count);
    glBindVertexArray(0);
}



// template<typename T>
// void Mesh<T>::bindAttribPointers()
// {
//     if (std::is_same<T, Vertex>::value) {
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
//         glEnableVertexAttribArray(1);
//         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
//         glEnableVertexAttribArray(2);
//     } else if (std::is_same<T, SimpleVertex>::value) {
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)0);
//         glEnableVertexAttribArray(0);
//     } else if (std::is_same<T, ColorVertex>::value) {
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)offsetof(ColorVertex, color));
//         glEnableVertexAttribArray(1);
//     }
// }

#endif // COMMON_MESH_HPP
