#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "primitives.h"
#include "drawable.h"
#include "vertex3d.h"


namespace gl {

class VertexArray : public gl::Drawable {
    QVector<Vertex> m_array;
    Primitive m_type;

public:
    VertexArray(Primitive type = Primitive::Points, int num = 0);

    void append(const Vertex &vertex);
    Vertex &operator[](int index);

    int size() const;

    void setPrimitive(Primitive type);
    Primitive getPrimitive() const;

protected:
    void draw(Renderer &renderer, RenderOptions options) const;
};

} // namespace gl

#endif // VERTEXARRAY_H
