#include "vertex3d.h"

namespace gl {

Vertex3D::Vertex3D(QVector3D _position, Color _color) :
    position(position), color(color) {}

Vertex3D::Vertex3D(float x, float y, float z, Color _color) {
    Vertex3D(QVector3D(x, y, z), _color);
}

Vertex3D::Vertex3D(QVector3D _position, QVector3D _normal, Color _color) :
    position(_position), normal(_normal), color(_color) {}

} // namespace gl
