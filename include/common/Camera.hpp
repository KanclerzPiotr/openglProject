#ifndef COMMON_CAMERA_HPP
#define COMMON_CAMERA_HPP

#include <glm/glm.hpp>

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    DOWN,
    UP,
    LEFT,
    RIGHT
};

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateCameraVectors();

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f);
    
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float width, float height) const;
};

#endif // COMMON_CAMERA_HPP