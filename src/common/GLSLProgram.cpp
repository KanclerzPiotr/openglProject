#include <common/GLSLProgram.hpp>
#include <fstream>
#include <fmt/core.h>
#include <glm/gtc/type_ptr.hpp>


std::string to_string(GLSLShader::GLSLShaderType type) {
    switch (type) {
    case GLSLShader::VERTEX:
        return "VERTEX";
    case GLSLShader::FRAGMENT:
        return "FRAGMENT";
    case GLSLShader::GEOMETRY:
        return "GEOMETRY";
    case GLSLShader::TESS_CONTROL:
        return "TESS_CONTROL";
    case GLSLShader::TESS_EVALUATION:
        return "TESS_EVALUATION";
    default:
        return "UNKNOWN";
    }
}

int GLSLProgram::getUniformLocation(std::string_view name) {

    if(uniformLocations.find(name.data()) == uniformLocations.end()) {
        uniformLocations[name.data()] = glGetUniformLocation(handle, name.data());
    }
    return uniformLocations[name.data()];
}

int GLSLProgram::getUniformBlockLocation(std::string_view name) {
    if(uniformBlockLocations.find(name.data()) == uniformBlockLocations.end()) {
        uniformBlockLocations[name.data()] = glGetUniformBlockIndex(handle, name.data());
    }
    return uniformBlockLocations[name.data()];
}

bool GLSLProgram::fileExists(std::string_view &fileName) {
    std::ifstream f(fileName.data());
    return f.good();
}

int GLSLProgram::createShader(GLSLShader::GLSLShaderType type) {
    switch (type) {
    case GLSLShader::VERTEX:
        return glCreateShader(GL_VERTEX_SHADER);
    case GLSLShader::FRAGMENT:
        return glCreateShader(GL_FRAGMENT_SHADER);
    case GLSLShader::GEOMETRY:
        return glCreateShader(GL_GEOMETRY_SHADER);
    case GLSLShader::TESS_CONTROL:
        return glCreateShader(GL_TESS_CONTROL_SHADER);
    case GLSLShader::TESS_EVALUATION:
        return glCreateShader(GL_TESS_EVALUATION_SHADER);
    default:
        return false;
    }
}

GLSLProgram::GLSLProgram() {
    handle = glCreateProgram();
    linked = false;
}

GLSLProgram::GLSLProgram(std::string_view vertexShader, std::string_view fragmentShader) {
    handle = glCreateProgram();
    linked = false;
    compileShaderFromFile(vertexShader, GLSLShader::VERTEX);
    compileShaderFromFile(fragmentShader, GLSLShader::FRAGMENT);
    link();
}

bool GLSLProgram::compileShaderFromFile(std::string_view fileName, GLSLShader::GLSLShaderType type) {
    if (!fileExists(fileName)) {
        fmt::println("Nie znaleziono pliku: {}", fileName);
        return false;
    }
    std::ifstream f(fileName.data());
    std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    return compileShaderFromString(fileName, str, type);
}

bool GLSLProgram::compileShaderFromString(std::string_view fileName, std::string_view source, GLSLShader::GLSLShaderType type) {
    
    GLuint shader = createShader(type);

    const char *c_str = source.data();
    glShaderSource(shader, 1, &c_str, nullptr);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int infolen = 0;
        int charsWritten = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolen);
        if (infolen > 0) {
            char *infoLog = new char[infolen];
            glGetShaderInfoLog(shader, infolen, &charsWritten, infoLog);
            fmt::println("{} Blad kompilacji shadera: {}", fileName, infoLog);
            delete[] infoLog;
        }
        return false;
    }
    glAttachShader(handle, shader);
    return true; 
}

bool GLSLProgram::link() {
    glLinkProgram(handle);
    int status;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        int infolen = 0;
        int charsWritten = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infolen);
        if (infolen > 0) {
            char *infoLog = new char[infolen];
            glGetProgramInfoLog(handle, infolen, &charsWritten, infoLog);
            fmt::println("Blad linkowania programu: {}", infoLog);
            delete[] infoLog;
        }
        return false;
    }
    linked = true;
    return true;

}

void GLSLProgram::use() {
    if(linked)
        glUseProgram(handle);
}

int GLSLProgram::getHandle() {
    return handle;
}

bool GLSLProgram::isLinked() {
    return linked;
}

void GLSLProgram::setUniform(std::string_view name, const glm::vec2 &v) {
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(v));
}
void GLSLProgram::setUniform(std::string_view name, const glm::vec3 &v) {
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(v));
}
void GLSLProgram::setUniform(std::string_view name, const glm::vec4 &v) {
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(v));
}
void GLSLProgram::setUniform(std::string_view name, const glm::mat4 &m) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}
void GLSLProgram::setUniform(std::string_view name, const glm::mat3 &m) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}
void GLSLProgram::setUniform(std::string_view name, float val) {
    glUniform1f(getUniformLocation(name), val);
}
void GLSLProgram::setUniform(std::string_view name, int val) {
    glUniform1i(getUniformLocation(name), val);
}
void GLSLProgram::setUniform(std::string_view name, unsigned int val) {
    glUniform1ui(getUniformLocation(name), val);
}
void GLSLProgram::setUniform(std::string_view name, bool val) {
    glUniform1i(getUniformLocation(name), val);
}
void GLSLProgram::setUniform(std::string_view name, int count, float val){
    glUniform1fv(getUniformLocation(name), count, &val);
}
void GLSLProgram::setUniform(std::string_view name, int count, int val){
    glUniform1iv(getUniformLocation(name), count, &val);
}

void GLSLProgram::bindUniformBlockToBindingPoint(std::string_view blockName, unsigned int bindingPoint) {
    glUniformBlockBinding(handle, getUniformBlockLocation(blockName), bindingPoint);
}


