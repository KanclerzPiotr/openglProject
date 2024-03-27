#include <common/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up,float yaw, float pitch) : 
    position(position),
    front(glm::vec3(0.0f, 0.0f, -1.0f)), 
    worldUp(up),
    yaw(yaw),
    pitch(pitch),
    movementSpeed(2.5f), 
    mouseSensitivity(0.1f), 
    zoom(45.0f) 
    {
            updateCameraVectors();
    }

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD)
        position += front * velocity;
    if (direction == CameraMovement::BACKWARD)
        position -= front * velocity;
    if (direction == CameraMovement::UP)
        position += worldUp * velocity;
    if (direction == CameraMovement::DOWN)
        position -= worldUp * velocity;
    if (direction == CameraMovement::LEFT)
        position -= right * velocity;
    if (direction == CameraMovement::RIGHT)
        position += right * velocity;
}
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float width, float height) const
{
    return glm::perspective(glm::radians(zoom), width / height, 0.1f, 100.0f);
}
