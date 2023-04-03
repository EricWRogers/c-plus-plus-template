#include "Camera.hpp"

namespace Engine
{

    Camera::Camera(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = _position;
        worldUp = _up;
        yaw = _yaw;
        pitch = _pitch;
        UpdateCameraVectors();
    }

    Camera::Camera(float _posX, float _posY, float _posZ, float _upX, float _upY, float _upZ, float _yaw, float _pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = glm::vec3(_posX, _posY, _posZ);
        worldUp = glm::vec3(_upX, _upY, _upZ);
        yaw = _yaw;
        pitch = _pitch;
        UpdateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
            position += front * velocity;
        if (direction == BACKWARD)
            position -= front * velocity;
        if (direction == LEFT)
            position -= right * velocity;
        if (direction == RIGHT)
            position += right * velocity;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // update front, right and Up Vectors using the updated Euler angles
        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset)
    {
        zoom -= (float)yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;
    }

    void Camera::UpdateCameraVectors()
    {
        // calculate the new front vector
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
        // also re-calculate the right and Up vector
        right = glm::normalize(glm::cross(front, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up = glm::normalize(glm::cross(right, front));
    }

} // end of Engine namespace