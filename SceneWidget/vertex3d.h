#ifndef VERTEX3D_H
#define VERTEX3D_H

#include <QVector3D>

#include "color.h"


namespace gl {

#pragma pack(push, 1)

struct Vertex3D {
    QVector3D position;
    QVector3D normal;
    Color     color;

    Vertex3D() = default;
    Vertex3D(QVector3D _position, Color _color = gl::Color::White);
    Vertex3D(float x, float y, float z, Color _color = gl::Color::White);
    Vertex3D(QVector3D _position, QVector3D _normal, gl::Color color);
};

#pragma pack(pop)

using Vertex = Vertex3D;

} // namespace gl

#endif // VERTEX3D_H
