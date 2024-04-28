#ifndef COMMON_UNIFORMBUFFER_HPP
#define COMMON_UNIFORMBUFFER_HPP

#include <glad/glad.h>
#include <vector>
#include <fmt/core.h>

#include "common/GLSLProgram.hpp"

template <typename T>
class UniformBuffer
{
private:
    unsigned int UBO;
    int size;
    std::vector<T> data;
public:
    UniformBuffer(std::vector<T>&& data);
    ~UniformBuffer();

    void bind(unsigned int bindingPoint) const;
    int getSize() const;
};


template <typename T>
UniformBuffer<T>::UniformBuffer(std::vector<T>&& data)
{
    this->size = this->data.size();
    if (size > 10)
    {
        fmt::print("UniformBuffer size is bigger than 10: {}\n", size);
        return;
    }
    this->data = std::move(data);
    

    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, size * sizeof(T), this->data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

template <typename T>
UniformBuffer<T>::~UniformBuffer()
{
    glDeleteBuffers(1, &UBO);
}

template <typename T>
void UniformBuffer<T>::bind(unsigned int bindingPoint) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);
}

template <typename T>
int UniformBuffer<T>::getSize() const
{
    return size;
}




#endif // COMMON_UNIFORMBUFFER_HPP