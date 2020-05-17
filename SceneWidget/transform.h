#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix4x4>
#include <QVector3D>

#include <QGL>

namespace gl {

class Transform {
    friend Transform operator*(const Transform &t1, const Transform &t2) {
        return Transform(t1.m_matrix * t2.m_matrix);
    }

    QMatrix4x4 m_matrix;

public:
    Transform();
    Transform(const Transform &other);
    Transform(const QMatrix4x4 &matrix);

    Transform &operator=(const Transform &other);

    void rotate(float angle, float x, float y, float z = 0.0f);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

    float *data();
    const float *data() const;
};

} // namespace gl

#endif // TRANSFORM_H
