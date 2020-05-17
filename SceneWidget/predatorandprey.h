#ifndef PREDATORANDPREY_H
#define PREDATORANDPREY_H

#include "drawable.h"
#include "transformable.h"

#include "renderer.h"
#include "vertexarray.h"

#include "ellipsoidshape.h"


class PredatorAndPrey : public gl::Drawable {
public:
    enum Type {
        Predator,
        Prey,
        Null
    };

    struct Cell {
        float health;
        Type type;

        Cell() = default;
        Cell(float _health, Type _type) : health(_health), type(_type) {}
    };

    using Field3D = QVector<QVector<QVector<Cell>>>;

    PredatorAndPrey(int _x = 10, int _y = 10, int _z = 10) :x(_x), y(_y), z(_z) {
        for (int i = 0; i < x; i++) {
            field.append(QVector<QVector<Cell>>());

            for (int j = 0; j < y; j++) {
                field[i].append(QVector<Cell>());

                for (int k = 0; k < z; k++) {
                    if (std::rand() % 10 == 0) {
                        field[i][j].append(std::rand() % 10 == 0 ? Cell(30, Predator) : Cell(100, Prey));
                    }
                    else {
                        field[i][j].append(Cell(0, Null));
                    }
                }
            }
        }
    }

    void update() {
        //Field3D newField = field;

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    if (field[i][j][k].type != Null) {
                        QVector<QVector3D> nbs;

                        if (field[i][j][k].type == Prey) {
                            nbs = getNeighbours(QVector3D(i, j, k));

                            if (nbs.isEmpty()) continue;

                            QVector3D nextPosition = nbs[std::rand() % nbs.size()];

                            field[i][j][k].health += 1.75f;
                            field[nextPosition.x()][nextPosition.y()][nextPosition.z()] = field[i][j][k];

                            if (field[i][j][k].health >= 200.0f) {
                                field[nextPosition.x()][nextPosition.y()][nextPosition.z()] = Cell(100.0f, Prey);
                                field[i][j][k].health = 100.0f;
                            }
                            else {
                                field[i][j][k].type = Null;
                            }
                        }
                        else if (field[i][j][k].type == Predator) {
                            nbs = getNeighbours(QVector3D(i, j, k), Prey);

                            if (!nbs.isEmpty()) {
                                QVector3D nextPosition = nbs[std::rand() % nbs.size()];

                                field[i][j][k].health += 20.0f;

                                if (field[i][j][k].health >= 100.0f) {
                                    field[nextPosition.x()][nextPosition.y()][nextPosition.z()] = field[i][j][k];
                                    field[nextPosition.x()][nextPosition.y()][nextPosition.z()].health = 30.0f;
                                    field[i][j][k].health = 30.0f;
                                }
                                else {
                                    field[nextPosition.x()][nextPosition.y()][nextPosition.z()] = field[i][j][k];
                                    field[i][j][k].type = Null;
                                }
                            }
                            else {
                                nbs = getNeighbours(QVector3D(i, j, k));

                                if (!nbs.isEmpty()) {
                                    QVector3D nextPosition = nbs[std::rand() % nbs.size()];

                                    field[i][j][k].health -= 0.55f;

                                    if (field[i][j][k].health <= 0) {
                                        field[i][j][k].type = Null;
                                    }
                                    else {
                                        field[nextPosition.x()][nextPosition.y()][nextPosition.z()] = field[i][j][k];
                                        field[i][j][k].type = Null;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    QVector<QVector3D> getNeighbours(QVector3D point, Type type = Null) {
        QVector3D up(point.x(), point.y() + 1, point.z());
        QVector3D down(point.x(), point.y() - 1, point.z());
        QVector3D left(point.x() - 1, point.y(), point.z());
        QVector3D right(point.x() + 1, point.y(), point.z());
        QVector3D front(point.x(), point.y(), point.z() - 1);
        QVector3D back(point.x(), point.y(), point.z() + 1);

        QVector3D directions[6] = {
            up, down, left, right, front, back
        };

        QVector<QVector3D> nbs;

        for (int i = 0; i < 6; i++) {
            QVector3D direction = directions[i];

            if (direction.x() < 0) {
                direction.setX(x - 1);
            }
            if (direction.y() < 0) {
                direction.setY(y - 1);
            }
            if (direction.z() < 0) {
                direction.setZ(z - 1);
            }
            if (direction.x() >= x) {
                direction.setX(0);
            }
            if (direction.y() >= y) {
                direction.setY(0);
            }
            if (direction.z() >= z) {
                direction.setZ(0);
            }

            if (direction.x() >= 0 && direction.x() < x &&
                    direction.y() >= 0 && direction.y() < y &&
                    direction.z() >= 0 && direction.z() < z) {

                if (field[direction.x()][direction.y()][direction.z()].type == type) {
                    nbs.append(direction);
                }
            }
        }

        return nbs;
    }

protected:
    void draw(gl::Renderer &renderer, gl::RenderOptions options) const override {
        gl::VertexArray vertexArray(gl::Points);

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < z; k++) {
                    if (field[i][j][k].type != Null) {
                        QVector3D position(i * (1.0f / static_cast<float>(x)),
                                           j * (1.0f / static_cast<float>(y)),
                                           k * (1.0f / static_cast<float>(z)));

                        gl::Color color;

                        if (field[i][j][k].type == Predator) {
                            color = gl::Color(1.0f, 0.0f, 1.0f, 1.6f);
                        }
                        else if (field[i][j][k].type == Prey) {
                            color = gl::Color(0.0f, 1.0f, 0.0f, 1.6f);
                        }

                        gl::Vertex vertex(position, QVector3D(0, 0, 1), color);
                        vertexArray.append(vertex);
                    }
                }
            }
        }

        renderer.draw(vertexArray, options);
    }

private:
    int x;
    int y;
    int z;

    Field3D field;
};

#endif // PREDATORANDPREY_H
