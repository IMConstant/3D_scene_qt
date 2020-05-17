#ifndef SHAPE_H
#define SHAPE_H

#include <QVector>
#include <QVector3D>

#include <QGL>

#include "vertex3d.h"
#include "color.h"

#include "drawable.h"
#include "transformable.h"
#include "transform.h"

#include "objfileparser.h"


namespace gl {

struct Triangle {
    Vertex3D v1;
    Vertex3D v2;
    Vertex3D v3;

    Triangle() = default;
    Triangle(QVector3D p1, QVector3D p2, QVector3D p3) {
        QVector3D A = p2 - p1;
        QVector3D B = p3 - p1;
        QVector3D N = QVector3D::crossProduct(A, B);

        v1 = Vertex3D(p1, N, Color());
        v2 = Vertex3D(p2, N, Color());
        v3 = Vertex3D(p3, N, Color());
    }
};

class Shape : public Drawable, public Transformable  {
    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_normals;
    QVector<Color>     m_colors;

public:
    Shape();

    void loadFromFile(const QString &fileName);
    void setFillColor(Color color);

    const QVector<QVector3D> &vertices() const;
    const QVector<QVector3D> &normals() const;
    const QVector<Color> &colors() const;

protected:
    void addTriangle(Triangle triangle);
    void clear();

protected:
    void draw(Renderer &renderer, RenderOptions options) const;
};

} // namespace gl

#endif // SHAPE_H
