#include "torusshape.h"


namespace gl {

TorusShape::TorusShape(GLfloat _R, GLfloat _r, GLuint fragmentationPhi, GLuint fragmentationTheta) :
    R(_R), r(_r), m_fragmentationPhi(fragmentationPhi), m_fragmentationTheta(fragmentationTheta) {
    double pi = std::acos(-1);
    float delta_phi = 2 * pi / static_cast<float>(m_fragmentationPhi);
    float delta_theta = 2 * pi / static_cast<float>(m_fragmentationTheta);

    QVector<Triangle> triangles;

    for (float phi = -pi; phi < pi; phi += delta_phi) {
        for (float theta = 0.0f; theta < 2 * pi; theta += delta_theta) {
            QVector3D p1((R + r * std::cos(theta)) * std::cos(phi),
                         r * std::sin(theta),
                         (R + r * std::cos(theta)) * std::sin(phi));
            QVector3D p2((R + r * std::cos(theta + delta_theta)) * std::cos(phi),
                         r * std::sin(theta + delta_theta),
                         (R + r * std::cos(theta + delta_theta)) * std::sin(phi));
            QVector3D p3((R + r * std::cos(theta)) * std::cos(phi + delta_phi),
                         r * std::sin(theta),
                         (R + r * std::cos(theta)) * std::sin(phi + delta_phi));
            QVector3D p4((R + r * std::cos(theta + delta_theta)) * std::cos(phi + delta_phi),
                         r * std::sin(theta + delta_theta),
                         (R + r * std::cos(theta + delta_theta)) * std::sin(phi + delta_phi));

            addTriangle(Triangle(p2, p3, p1));
            addTriangle(Triangle(p4, p3, p2));
        }
    }
}

} // namespace gl
