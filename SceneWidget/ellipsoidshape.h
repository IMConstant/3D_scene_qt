#ifndef ELLIPSOIDSHAPE_H
#define ELLIPSOIDSHAPE_H

#include "shape.h"

namespace gl {

class EllipsoidShape : public Shape {
public:
    EllipsoidShape(GLfloat a = 1.0f, GLfloat b = 1.0f, GLfloat c = 1.0f,
              GLuint fragmentationPhi = 30, GLuint fragmentationTheta = 30,
              GLfloat endPhi = 2 * std::acos(-1));
};

} // namespace gl

#endif // ELLIPSOIDSHAPE_H
