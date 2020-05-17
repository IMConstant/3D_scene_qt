#ifndef TORUSSHAPE_H
#define TORUSSHAPE_H

#include "shape.h"


namespace gl {

class TorusShape : public Shape {
    GLfloat r;
    GLfloat R;
    GLuint m_fragmentationPhi;
    GLuint m_fragmentationTheta;

public:
    TorusShape(GLfloat R, GLfloat r,
          GLuint fragmentationPhi = 30, GLuint fragmentationTheta = 30);
};

} // namespace gl

#endif // TORUSSHAPE_H
