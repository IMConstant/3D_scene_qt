#ifndef GRID_H
#define GRID_H

#include "drawable.h"
#include "transformable.h"

#include "ellipsoidshape.h"
#include "vertexarray.h"


struct Entity {
    QVector3D position;
    QVector3D direction;

    Entity() = default;
    Entity(QVector3D _position, QVector3D _direction) :
        position(_position), direction(_direction) {}
};


class Grid : public gl::Drawable, public gl::Transformable {
    QVector<Entity> points;

    int n;

public:
    Grid(int N = 10) : n(N) {
        for (int i = 0; i < n; i++) {
            points.append(Entity(QVector3D(1000.0f * std::rand() / static_cast<float>(RAND_MAX),
                                           1000.0f * std::rand() / static_cast<float>(RAND_MAX),
                                           1000.0f * std::rand() / static_cast<float>(RAND_MAX)),
                                 QVector3D(std::rand() / static_cast<float>(RAND_MAX),
                                           std::rand() / static_cast<float>(RAND_MAX),
                                           std::rand() / static_cast<float>(RAND_MAX))));
        }
    }

    void update() {
        for (int i = 0; i < n; i++) {
            auto &entity = points[i];

            entity.position += 0.0001f * entity.direction.normalized();

//            if (entity.position.x() > 1.0f) {
//                entity.position.setX(0.0f);
//            }
//            if (entity.position.y() > 1.0f) {
//                entity.position.setY(0.0f);
//            }
//            if (entity.position.z() > 1.0f) {
//                entity.position.setZ(0.0f);
//            }

//            if (entity.position.x() < 0.0f) {
//                entity.position.setX(1.0f);
//            }
//            if (entity.position.y() < 0.0f) {
//                entity.position.setY(1.0f);
//            }
//            if (entity.position.z() < 0.0f) {
//                entity.position.setZ(1.0f);
//            }
        }
    }

protected:
    void draw(gl::Renderer &renderer, gl::RenderOptions options) const override;
};

#endif // GRID_H
