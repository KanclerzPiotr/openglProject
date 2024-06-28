#include <common/Texture.hpp>

#include <glad/glad.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb/stb_image.h>
#include <fmt/core.h>

Texture::Texture(std::string_view path)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char* data = stbi_load(path.data(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        if (nrChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (nrChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            fmt::print("{}: Unsupported number of channels: {}\n", path, nrChannels);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        

        stbi_image_free(data);
    }
    else
    {
        fmt::print("Failed to load texture: {}\n", path);
    }
}

void Texture::bind(int index) const
{
    if(m_id != 0)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}  

Texture::~Texture()
{
    fmt::print("Texture: Destroying texture: {}\n", m_id);
    glDeleteTextures(1, &m_id);
}