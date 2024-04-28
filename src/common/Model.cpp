#include <common/Model.hpp>
#include <fmt/core.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>
#include <common/TextureManager.hpp>



Model::Model(std::string_view path, std::vector<std::string_view> textures) {
    this->path = path;
    
    loadModel();
    loadTextures(textures);

}

void Model::loadTextures(std::vector<std::string_view> textures) {
    if(textures.size() > 5) {
        fmt::print("Model: Too many textures for model: {}\n", path);
    }

    for(auto& texture : textures) {
        this->textures.emplace_back(TextureManager::getTexture(std::string{texture}));
    }
}   

void Model::loadModel() {
    tinyobj::ObjReaderConfig reader_config;
    reader_config.triangulate = true; 
    reader_config.mtl_search_path = "./";

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path.data(), reader_config)) {
        if (!reader.Error().empty()) {
            fmt::print("TinyObjReader: {}\n", reader.Error());
        }
        fmt::print("Failed to load/parse model: {}\n", path);
    }    

    if (!reader.Warning().empty()) {
        fmt::print("TinyObjReader: {} for {}\n", reader.Warning(), path);
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    parseShapes(shapes, attrib);
}

void Model::parseShapes(const std::vector<tinyobj::shape_t>& shapes, const tinyobj::attrib_t& attrib) {
    
    for(auto& shape : shapes) {
    
        std::vector<Vertex> vertices;
        std::vector<int> indices;
    
        size_t index_offset = 0;
        for(unsigned int polygon_size : shape.mesh.num_face_vertices) {
            for(unsigned int i = 0; i < polygon_size; i++) {

                tinyobj::index_t idx = shape.mesh.indices[index_offset + i];
                Vertex vertex;
                vertex.position = {
                    attrib.vertices[3*idx.vertex_index + 0],
                    attrib.vertices[3*idx.vertex_index + 1],
                    attrib.vertices[3*idx.vertex_index + 2]
                };
                if (idx.normal_index >= 0) {
                    vertex.normal = {
                        attrib.normals[3*idx.normal_index + 0],
                        attrib.normals[3*idx.normal_index + 1],
                        attrib.normals[3*idx.normal_index + 2]
                    };
                } else {
                    vertex.normal = {0.0f, 0.0f, 0.0f};
                }
                
                if (idx.texcoord_index >= 0) {
                    vertex.texCoords = {
                        attrib.texcoords[2*idx.texcoord_index + 0],
                        attrib.texcoords[2*idx.texcoord_index + 1]
                    };
                } else {
                    vertex.texCoords = {0.0f, 0.0f};
                }
                indices.emplace_back(index_offset + i);
                vertices.emplace_back(vertex);
            }

            index_offset += polygon_size;
        }    
        meshes.emplace_back(Mesh<Vertex>{std::move(vertices), std::move(indices), TRIANGLES});
    }
}

glm::mat4 Model::getModelMatrix() const {
    return modelMatrix;
}

glm::mat3 Model::getNormalMatrix() const {
    return glm::transpose(glm::inverse(modelMatrix));
}

void Model::setModelMatrix(const glm::mat4& modelMatrix) {
    this->modelMatrix = modelMatrix;
}

void Model::translate(const glm::vec3& translation) {
    modelMatrix = glm::translate(modelMatrix, translation);
}

void Model::rotate(const glm::vec3& rotation) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Model::rotate(const glm::vec3& rotation, const glm::vec3& axis) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), axis);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), axis);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), axis);
};

void Model::rotateX(float angle) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Model::rotateY(float angle) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Model::rotateZ(float angle) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Model::scaleUp(const glm::vec3& scale) {
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Model::setTextureUniforms(GLSLProgram& program) {
    for(int i = 0; i < textures.size(); i++) {
        textures[i]->bind(i);
        program.setUniform(fmt::format("texture{}", i), i);
    }
}

void Model::draw() {
    for (auto& mesh : meshes) {
        mesh.draw();
    }

    for(int i = 0; i < textures.size(); i++) {
        textures[i]->unbind();
    }
}

