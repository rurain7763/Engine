#include "OrthographicCamera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../utils/Math.h"

namespace engine {
    OrthographicCamera::OrthographicCamera() 
        : _projectionMatrix(1.0f), _viewMatrix(1.0f), _viewProjectionMatrix(1.0f), _position(0.0f), _rotation(0.0f) { }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
        _projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetProjection(int width, int height) {
        // y축 반전(좌상단이 0, 0)을 원하면 bot = 0, top = height로 설정하면 됨.
        _projectionMatrix = glm::ortho(
            0.f, 
            static_cast<float>(width), 
            0.f, 
            static_cast<float>(height), 
            -1.0f, 
            1.0f
        );
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetPosition(float x, float y, float z) {
        _position = {x, y, z};
        RecalculateViewMatrix();
    }

    void OrthographicCamera::SetRotation(float rotation) {
        _rotation = rotation;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));
        _viewMatrix = glm::inverse(transform);
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }
}