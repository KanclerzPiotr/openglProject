#include <common/TextureManager.hpp>
#include <fmt/core.h>

std::map<std::string, std::shared_ptr<Texture>> TextureManager::m_textures;

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& path)
{

    auto it = m_textures.find(path);
    if(it == m_textures.end())
    {
        loadTexture(path);
        it = m_textures.find(path);
    }

    return it->second;
}

void TextureManager::loadTexture(const std::string& path)
{
    m_textures[path] = std::make_shared<Texture>(path);
}