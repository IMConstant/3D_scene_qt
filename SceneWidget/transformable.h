#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <QGL>

#include "transform.h"


namespace gl {

class Transformable {
    QMatrix4x4 m_translation;
    QMatrix4x4 m_rotation;
    QMatrix4x4 m_scale;

    Transform m_transform;

public:
    Transformable();

    void rotate(float angle, float x, float y, float z = 0.0f);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

    void setRotation(float angle, float x, float y, float z = 0.0f);
    void setTranslation(float x, float y, float z);
    void setScale(float x, float y, float z);

    const Transform getTransform() const;
};

}

#endif // TRANSFORMABLE_H
