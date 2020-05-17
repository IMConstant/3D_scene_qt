#include "transformable.h"

namespace gl {

Transformable::Transformable() {}

const Transform Transformable::getTransform() const {
    return Transform(m_translation * m_rotation * m_scale);
}

void Transformable::setTranslation(float x, float y, float z) {
    m_translation.setToIdentity();

    translate(x, y, z);
}

void Transformable::setScale(float x, float y, float z) {
    m_scale.setToIdentity();

    scale(x, y, z);
}

void Transformable::setRotation(float angle, float x, float y, float z) {
    m_rotation.setToIdentity();

    rotate(angle, x, y, z);
}

void Transformable::translate(float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadMatrixf(m_translation.data());
    glTranslatef(x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_translation.data());

    glPopMatrix();
}

void Transformable::scale(float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadMatrixf(m_scale.data());
    glScalef(x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_scale.data());

    glPopMatrix();
}

void Transformable::rotate(float angle, float x, float y, float z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadMatrixf(m_rotation.data());
    glRotatef(angle, x, y, z);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_rotation.data());

    glPopMatrix();
}

} // namespace gl
