#include "light.h"


namespace gl {

Light::Light() {
    m_spot_cutoff    = 180.0f;
    m_spot_exponent  = 0;
    m_spot_direction = QVector3D(0, 0, -1);

    m_diffuse  = QVector4D(0, 0, 0, 1);
    m_ambient  = QVector4D(0, 0, 0, 1);
    m_specular = QVector4D(0, 0, 0, 1);

    m_point_source = false;
    m_position = QVector4D(0, 0, 1, 0);
}

Light::Light(QVector3D position, bool point_source) {
    Light();

    setPointSource(point_source);
    setPosition(position);
}

void Light::setPosition(QVector3D position) {
    m_position = QVector4D(position, static_cast<float>(m_point_source));
}

void Light::setPointSource(bool value) {
    m_point_source = value;
    setPosition(QVector3D(m_position));
}

void Light::setDiffuse(float diffuse) {
    m_diffuse = QVector4D(diffuse, diffuse, diffuse, diffuse);
}

void Light::setSpecular(float specular) {
    m_specular = QVector4D(specular, specular, specular, specular);
}

void Light::setAmbient(float ambient) {
    m_ambient = QVector4D(ambient, ambient, ambient, ambient);
}

void Light::setSpotExponent(float value) {
    m_spot_exponent = value;
}

QVector3D Light::getPosition() const {
    return QVector3D(m_position);
}

QVector3D Light::getComponents() const {
    return QVector3D(m_diffuse.x(), m_specular.x(), m_ambient.x());
}

} // namespace gl
