#ifndef COMMON_MODEL_HPP
#define COMMON_MODEL_HPP

#include <common/Mesh.hpp>
#include <common/Texture.hpp>
#include <common/GLSLProgram.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

class Model
{
private:
    std::vector<std::shared_ptr<Texture>> textures;
    std::vector<Mesh<Vertex>> meshes;
    std::string path;
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    void parseShapes(const std::vector<tinyobj::shape_t>& shapes, const tinyobj::attrib_t& attrib);
    void loadModel();
    void loadTextures(std::vector<std::string_view> textures);
public:
    Model(std::string_view path, std::vector<std::string_view> textures = {});
    Model(Mesh<Vertex>&& mesh, std::vector<std::string_view> textures = {});
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = default;
    ~Model();
    // ~Model() = default;

    glm::mat4 getModelMatrix() const;
    glm::mat3 getNormalMatrix() const;

    void setModelMatrix(const glm::mat4& modelMatrix);
    void bindInstancedArray();

    void translate(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void rotate(const glm::vec3& rotation, const glm::vec3& axis);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scaleUp(const glm::vec3& scale);
    void setTextureUniforms(GLSLProgram& program);

    void draw();
    void drawInstanced(int count);

    void bind();

};

#endif // COMMON_MODEL_HPP