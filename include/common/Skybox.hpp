#ifndef COMMON_SKYBOX_HPP
#define COMMON_SKYBOX_HPP

#include <common/GLSLProgram.hpp>
#include <string_view>
#include <vector>


class Skybox
{
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int textureId;
    GLSLProgram program;

    void createVAO();
    void createTexture(const std::vector<std::string_view>& texturePaths);

public:
    Skybox(std::string_view vertexPath, std::string_view fragmentPath, const std::vector<std::string_view>& texturePaths);
    ~Skybox();
    void draw(const glm::mat4& view, const glm::mat4& projection);
    void bindTexture(int index = 0);

};

#endif // COMMON_SKYBOX_HPP
