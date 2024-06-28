#ifndef COMMON_TEXTURE_HPP
#define COMMON_TEXTURE_HPP

#include <string_view>

class Texture
{
public:
    Texture(std::string_view path);
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) = default;
    Texture& operator=(Texture&&) = default;
    ~Texture();

    void bind(int index = 0) const;
    void unbind() const;
    unsigned int getID() const { return m_id; }

private:
    unsigned int m_id;
};

#endif // COMMON_TEXTURE_HPP