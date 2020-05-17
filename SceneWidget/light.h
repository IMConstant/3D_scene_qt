#ifndef LIGHT_H
#define LIGHT_H

#include <QVector4D>
#include <QVector3D>

#include <QGL>


namespace gl {

enum LightIndex {
    Light0,
    Light1,
    Light2,
    Light3,
    Light4,
    Light5,
    Light6,
    Light7
};

class Light {
    friend class Renderer;

    QVector4D m_position;

    QVector4D m_diffuse;
    QVector4D m_specular;
    QVector4D m_ambient;

    float     m_spot_cutoff;
    float     m_spot_exponent;
    QVector3D m_spot_direction;

    bool m_point_source;

public:
    Light();
    Light(QVector3D position, bool point_source = false);

    void setPosition(QVector3D position);

    void setDiffuse(QVector4D diffuse);
    void setDiffuse(float diffuse);
    void setSpecular(QVector4D specular);
    void setSpecular(float specular);
    void setAmbient(QVector4D ambient);
    void setAmbient(float ambient);

    QVector3D getPosition() const;
    QVector3D getComponents() const;

    void setSpotCutoff(float angle);
    void setSpotExponent(float value);
    void setSpotDirection(QVector3D direction);

    void setPointSource(bool value);
};

} // namespace gl

#endif // LIGHT_H
