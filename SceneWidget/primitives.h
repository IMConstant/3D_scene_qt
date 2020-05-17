#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <QGL>


namespace gl {
    enum Primitive {
        Points        = GL_POINTS,
        Lines         = GL_LINES,
        LineLoop      = GL_LINE_LOOP,
        LineStrip     = GL_LINE_STRIP,
        Polygon       = GL_POLYGON,
        Quads         = GL_QUADS,
        QuadStrip     = GL_QUAD_STRIP,
        Triangles	  = GL_TRIANGLES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleFan   = GL_TRIANGLE_FAN
    };
} // namespace gl



#endif // PRIMITIVES_H
