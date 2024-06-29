#ifndef COMMON_GLSLPROGRAM_HPP
#define COMMON_GLSLPROGRAM_HPP

#include <string>
#include <string_view>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>


namespace GLSLShader
{
    enum GLSLShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESS_CONTROL,
        TESS_EVALUATION
    };
};

class GLSLProgram
{
private:
    int handle;
    bool linked;
    std::map<std::string, int> uniformLocations;
    std::map<std::string, int> uniformBlockLocations;
    int getUniformLocation(std::string_view name);
    int getUniformBlockLocation(std::string_view name);
    bool fileExists(std::string_view &fileName);
    int createShader(GLSLShader::GLSLShaderType type);


public:
    GLSLProgram();
    GLSLProgram(std::string_view vertexShader, std::string_view fragmentShader);
    bool compileShaderFromFile(std::string_view fileName,
                               GLSLShader::GLSLShaderType type);
    bool compileShaderFromString(std::string_view fileName,
                                 std::string_view source,
                                 GLSLShader::GLSLShaderType type);
    bool link();
    void use();
    int getHandle();
    bool isLinked();

    void setUniform(std::string_view name, const glm::vec2 &v);
    void setUniform(std::string_view name, const glm::vec3 &v);
    void setUniform(std::string_view name, const glm::vec4 &v);
    void setUniform(std::string_view name, const glm::mat4 &m);
    void setUniform(std::string_view name, const glm::mat3 &m);
    void setUniform(std::string_view name, float val);
    void setUniform(std::string_view name, int val);
    void setUniform(std::string_view name, unsigned int val);
    void setUniform(std::string_view name, bool val);
    void setUniform(std::string_view name, int count, float val);
    void setUniform(std::string_view name, int count, int val);

    void bindUniformBlockToBindingPoint(std::string_view blockName, unsigned int bindingPoint);

};

#endif // COMMON_GLSLPROGRAM_HPP