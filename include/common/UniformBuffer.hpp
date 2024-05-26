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
    void updateData(std::vector<T>&& data);
    void updateData(int index, T&& data);
    void updateData(int index, const T& data);
    int getSize() const;
    const std::vector<T>& getData() const { return data; }
};


template <typename T>
UniformBuffer<T>::UniformBuffer(std::vector<T>&& data)
{
    if (this->data.size() > 10)
    {
        fmt::print("UniformBuffer size is bigger than 10: {}\n", size);
        return;
    }
    this->data = std::move(data);

    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, this->data.size() * sizeof(T), this->data.data(), GL_STATIC_DRAW);
}

template <typename T>
UniformBuffer<T>::~UniformBuffer()
{
    fmt::print("Deleting UniformBuffer\n");
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
    return data.size();
}

template <typename T>
void UniformBuffer<T>::updateData(std::vector<T>&& data)
{
    if (data.size() != this->data.size())
    {
        fmt::print("Data size is different from the current data size\n");
        return;
    }
    this->data = std::move(data);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, this->data.size() * sizeof(T), this->data.data());
}

template <typename T>
void UniformBuffer<T>::updateData(int index, T&& data)
{
    if (index >= this->data.size())
    {
        fmt::print("Index is out of range\n");
        return;
    }
    this->data[index] = std::move(data);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(T), sizeof(T), &this->data[index]);
}

template <typename T>
void UniformBuffer<T>::updateData(int index, const T& data)
{
    if (index >= this->data.size())
    {
        fmt::print("Index is out of range\n");
        return;
    }
    this->data[index] = data;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(T), sizeof(T), &this->data[index]);
}



#endif // COMMON_UNIFORMBUFFER_HPP