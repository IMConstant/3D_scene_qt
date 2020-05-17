#include "grid.h"

void Grid::draw(gl::Renderer &renderer, gl::RenderOptions options) const {
    gl::VertexArray vertexArray(gl::Lines);

//    for (int i = 0; i < n - 1; i++) {
//        for (int j = 1; j < n; j++) {
//            auto &e1 = points.at(i);
//            auto &e2 = points.at(j);

//            if (e1.position.distanceToPoint(e2.position) < 0.4f) {
//                gl::Vertex v1(e1.position,
//                              e1.direction.normalized(),
//                              gl::Color(e1.position.x(),
//                                        e1.position.y(),
//                                        e1.position.z()));
//                gl::Vertex v2(e2.position,
//                              e2.direction.normalized(),
//                              gl::Color(e2.position.x(),
//                                        e2.position.y(),
//                                        e2.position.z()));

//                vertexArray.append(v1);
//                vertexArray.append(v2);
//            }
//        }
//    }

    renderer.draw(vertexArray, options);

    gl::EllipsoidShape sphere(1.2f, 1.2f, 1.2f, 3, 3);

    for (int i = 0; i < n; i++) {
        auto &e = points.at(i);

        sphere.setTranslation(e.position.x(), e.position.y(), e.position.z());
        sphere.setFillColor(gl::Color(1.0f, e.direction.y(), 0.0f));

        renderer.draw(sphere, options);
    }
}
