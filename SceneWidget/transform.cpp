#include "transform.h"


namespace gl {

Transform::Transform() {}

Transform::Transform(const QMatrix4x4 &matrix) {
    m_matrix = matrix;
}

Transform::Transform(const Transform &other) {
    m_matrix = other.m_matrix;
}

Transform &Transform::operator=(const Transform &other) {
    m_matrix = other.m_matrix;

    return *this;
}

void Transform::translate(float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadMatrixf(m_matrix.data());
    glTranslatef(x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix.data());

    glPopMatrix();
}

void Transform::scale(float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadMatrixf(m_matrix.data());
    glScalef(x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix.data());

    glPopMatrix();
}

void Transform::rotate(float angle, float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadMatrixf(m_matrix.data());
    glRotatef(angle, x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix.data());

    glPopMatrix();
}

float *Transform::data() {
    return m_matrix.data();
}

const float *Transform::data() const {
    return m_matrix.data();
}

} // namespace gl
