//
// Created by Ben White on 1/28/23.
//

#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(int width, int height, glm::vec3 initialPosition, bool isPerspective)
    : _isPerspective{isPerspective},
    _position { initialPosition }, _lookDirection ( -1.f * initialPosition),
    _width {width}, _height {height} {

    recalculateVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(_position, _position + _lookDirection, _upDirection);
}

glm::mat4 Camera::GetProjectionMatrix() {
    auto aspectRatio = (float)_width / (float)_height;
    if (_isPerspective) {
        return glm::perspective(glm::radians(_fieldOfView), aspectRatio, _nearClip, _farClip);
    }
    return glm::ortho(-aspectRatio, aspectRatio, -1.f, 1.f, _nearClip, _farClip);
}

void Camera::MoveCamera(Camera::MoveDirection direction, float moveAmount) {
    glm::vec3 moveDirection {};

    switch (direction) {
        case MoveDirection::Forward: {
            moveDirection = _lookDirection;
            break;
        }
        case MoveDirection::Backward: {
            moveDirection = -_lookDirection;
            break;
        }
        case MoveDirection::Left: {
            moveDirection = -glm::normalize(glm::cross(_lookDirection, _upDirection));
            break;
        }
        case MoveDirection::Right: {
            moveDirection = glm::normalize(glm::cross(_lookDirection, _upDirection));
            break;
        }
        case MoveDirection::Up: {
            moveDirection = -glm::normalize(glm::cross(_lookDirection, _rightDirection));
            break;
        }
        case MoveDirection::Down: {
            moveDirection = glm::normalize(glm::cross(_lookDirection, _rightDirection));
            break;
        }
        default:
            break;
    }

    _position += moveDirection * moveAmount;
}

void Camera::RotateBy(float yaw, float pitch) {
    _yaw += yaw;
    _pitch += pitch;

    _pitch = std::clamp(_pitch, -89.f, 89.f);

    recalculateVectors();

}

void Camera::recalculateVectors() {
    _lookDirection = glm::normalize(
        glm::vec3{
          std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)),
          std::sin(glm::radians(_pitch)),
          std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch))
        }
    );

    _rightDirection = glm::normalize(glm::cross(_lookDirection, glm::vec3(0.0f, 1.f, 0.f)));
    _upDirection = glm::normalize(glm::cross(_rightDirection, _lookDirection));
}

void Camera::IncrementZoom(float amount) {
    _fieldOfView += amount;

    _fieldOfView = std::clamp(_fieldOfView, 1.f, 75.f);
}


