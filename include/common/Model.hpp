#ifndef COMMON_MODEL_HPP
#define COMMON_MODEL_HPP

#include <common/Mesh.hpp>
#include <tinyobjloader/tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Model
{
private:
    std::vector<Mesh<Vertex>> meshes;
    std::string path;
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    void parseShapes(const std::vector<tinyobj::shape_t>& shapes, const tinyobj::attrib_t& attrib);

public:
    Model(std::string_view path);
    ~Model() = default;

    glm::mat4 getModelMatrix() const;

    void setModelMatrix(const glm::mat4& modelMatrix);

    void translate(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void rotate(const glm::vec3& rotation, const glm::vec3& axis);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scaleUp(const glm::vec3& scale);

    void draw();
};

#endif // COMMON_MODEL_HPP