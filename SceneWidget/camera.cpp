#include "camera.h"


namespace gl {

Camera::Camera(QVector3D position, QVector3D look) : m_position(position), m_look(look) {}

void Camera::setPosition(QVector3D position) {
    m_position = position;
}

void Camera::setPosition(float x, float y, float z) {
    m_position = QVector3D(x, y, z);
}

void Camera::setLook(QVector3D look) {
    m_look = look;
}

void Camera::setLook(float x, float y, float z) {
    m_look = QVector3D(x, y, z);
}

const QVector3D &Camera::position() const {
    return m_position;
}

const QVector3D &Camera::look() const {
    return m_look;
}

} // namespace gl
