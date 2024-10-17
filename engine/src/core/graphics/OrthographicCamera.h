#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "glm/glm.hpp"

namespace engine {
    class OrthographicCamera {
    public:
        OrthographicCamera();
        ~OrthographicCamera() = default;

        void SetProjection(float left, float right, float bottom, float top);
        void SetProjection(int width, int height);

        void SetPosition(float x, float y, float z);
        inline const glm::vec3& GetPosition() const { return _position; }

        void SetRotation(float rotation);
        inline float GetRotation() const { return _rotation; }

        inline const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
        inline const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
        inline const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _viewProjectionMatrix;

        glm::vec3 _position;
        float _rotation;
    };
}

#endif