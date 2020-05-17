#include "ellipsoidshape.h"


namespace gl {

EllipsoidShape::EllipsoidShape(GLfloat a, GLfloat b, GLfloat c,
                     GLuint fragmentationPhi, GLuint fragmentationTheta,
                     GLfloat endPhi) {
    const double pi = std::acos(-1);
    float delta_phi = 2 * pi / static_cast<float>(fragmentationPhi);
    float delta_theta = pi / static_cast<float>(fragmentationTheta);

    for (float phi = 0.0f; phi <= 2 * pi; phi += delta_phi) {
        float last_polygon = false;

        if (phi + delta_phi >= endPhi) {
            delta_phi = endPhi - phi;
            last_polygon = true;
        }

        for (float theta = -pi / 2.0f; theta <= pi / 2.0f; theta += delta_theta) {
            Triangle t1;
            Triangle t2;

            QVector3D p1(a * std::cos(theta) * std::cos(phi), c * std::sin(theta), b * std::cos(theta) * std::sin(phi));
            QVector3D p2(a * std::cos(theta + delta_theta) * std::cos(phi), c * std::sin(theta + delta_theta), b * std::cos(theta + delta_theta) * std::sin(phi));
            QVector3D p3(a * std::cos(theta) * std::cos(phi + delta_phi), c * std::sin(theta), b * std::cos(theta) * std::sin(phi + delta_phi));
            QVector3D p4(a * std::cos(theta + delta_theta) * std::cos(phi + delta_phi), c * std::sin(theta + delta_theta), b * std::cos(theta + delta_theta) * std::sin(phi + delta_phi));

            addTriangle(Triangle(p2, p3, p1));
            addTriangle(Triangle(p4, p3, p2));
        }

        if (last_polygon) {
            break;
        }
    }
}

} // namespace gl
