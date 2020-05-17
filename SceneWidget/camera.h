#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>


namespace gl {

class Camera {
    QVector3D m_position;
    QVector3D m_look;

public:
    explicit Camera(QVector3D position, QVector3D look = QVector3D(0.0f, 0.0f, 0.0f));

    void setPosition(QVector3D position);
    void setPosition(float x, float y, float z);

    void setLook(QVector3D look);
    void setLook(float x, float y, float z);

    const QVector3D &position() const;
    const QVector3D &look() const;
};

} // namespace gl

#endif // CAMERA_H
