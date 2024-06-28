#ifndef COMMON_TEXTUREMANAGER_HPP
#define COMMON_TEXTUREMANAGER_HPP

#include <map>
#include <string>
#include <memory>

#include <common/Texture.hpp>

class TextureManager
{
public:
    static std::shared_ptr<Texture> getTexture(const std::string& path);

private:
    static std::map<std::string, std::shared_ptr<Texture>> m_textures;
    static void loadTexture(const std::string& path);
};


#endif // COMMON_TEXTUREMANAGER_HPP

