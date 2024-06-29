#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include <common/GLSLProgram.hpp>
#include <common/Model.hpp>
#include <common/Camera.hpp>

#include "HeightMap.hpp"
#include <map>
#include <mutex>


class TileManager
{
    GLSLProgram m_program;
    std::map<std::pair<int, int>, Model> m_tiles;
    float scale;

    public:
    TileManager(GLSLProgram&& program, glm::vec3 position, float scale);

    void draw(const Camera& camera, int screenWidth, int screenHeight);

    template<typename T>
    void setUniform( const std::string& name, const T& value);
};

TileManager::TileManager(GLSLProgram&& program, glm::vec3 position, float scale)
    : m_program(std::move(program))
    , scale(scale)
{

    int x = std::round(position.x/scale);
    int z = std::round(position.z/scale);

    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            auto idx = std::make_pair(x + i, z + j);
            m_tiles.emplace(idx, Model{generateHeightMap(256, 256, (x + i), (z+j)), {"grass.jpg", "sand.jpg", "water.jpg"}});
            m_tiles[idx].translate({(x + i) * scale, 0.0f, (z + j) * scale});
            m_tiles[idx].scaleUp({scale + 0.1f, 1.0f, scale + 0.1f});
        }
    }
}

void TileManager::draw(const Camera& camera, int screenWidth, int screenHeight)
{
        m_program.use();
        m_program.setUniform("view", camera.getViewMatrix());
        m_program.setUniform("projection", camera.getProjectionMatrix(screenWidth, screenHeight));
        m_program.setUniform("cameraPos", camera.getPosition());

        int x = std::round(camera.getPosition().x/scale);
        int z = std::round(camera.getPosition().z/scale);


        for(int i = x - 1 ; i <= x + 1; i++)
        {
            for(int j = z - 1; j <= z + 1; j++)
            {
                auto idx = std::make_pair(i, j);
                if(m_tiles.find(idx) == m_tiles.end())
                {
                    Model m = Model{generateHeightMap(256, 256, i, j), {"grass.jpg", "sand.jpg", "water.jpg"}};
                    m.translate({i * scale, 0.0f, j * scale});
                    m.scaleUp({scale + 0.1f, 1.0f, scale + 0.1f});
                    m_tiles.emplace(idx, std::move(m));
                }

                auto& tile = m_tiles[idx];
                m_program.setUniform("normalMatrix", tile.getNormalMatrix());
                m_program.setUniform("model", tile.getModelMatrix());
                tile.setTextureUniforms(m_program);
                tile.draw();
            }
        }
}

template<typename T>
void TileManager::setUniform(const std::string& name, const T& value)
{
    m_program.setUniform(name, value);
}

#endif // TILEMANAGER_HPP