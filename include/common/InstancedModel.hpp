#ifndef COMMON_INSTANCEDMODEL_HPP
#define COMMON_INSTANCEDMODEL_HPP

#include <common/Model.hpp>

class InstancedModel
{
    private:
        Model model;
        std::vector<glm::mat4> modelMatrices;
        unsigned int instanceVBO;
    public:
    InstancedModel(Model&& model, std::vector<glm::mat4> modelMatrices);

    InstancedModel(const InstancedModel&) = delete;
    InstancedModel& operator=(const InstancedModel&) = delete;

    void draw();
    void setModelMatrices(const std::vector<glm::mat4>& modelMatrices);
    void setTextureUniforms(GLSLProgram& program);
    glm::mat3 getNormalMatrix();

};


#endif // COMMON_INSTANCEDMODEL_HPP