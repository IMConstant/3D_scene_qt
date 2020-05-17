#include "objfileparser.h"

namespace gl {

QVector<ObjectVertex> OBJFileParser(const QString &fileName) {
    QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw;
    }

    QTextStream in(&file);

    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<ObjectVertex> faces;

    QStringList vertexComponents;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line[0] == 'v' && line[1] == ' ') {
            vertexComponents = line.split(" ");
            QVector3D vertex;
            vertex.setX(vertexComponents.at(1).toFloat());
            vertex.setY(vertexComponents.at(2).toFloat());
            vertex.setZ(vertexComponents.at(3).toFloat());
            vertices.push_back(vertex);
        }
        else if (line[0] == 'v' && line[1] == 'n') {
            vertexComponents = line.split(" ");
            QVector3D normal;
            normal.setX(vertexComponents.at(1).toFloat());
            normal.setY(vertexComponents.at(2).toFloat());
            normal.setZ(vertexComponents.at(3).toFloat());
            normals.push_back(normal);
        }
        else if (line[0] == 'f') {
            vertexComponents = line.split(" ");
            faces.push_back(ObjectVertex(vertices.at(vertexComponents.at(1).split("/").at(0).toInt() - 1),
                            normals.at(vertexComponents.at(1).split("/").at(2).toInt() - 1)));
            faces.push_back(ObjectVertex(vertices.at(vertexComponents.at(2).split("/").at(0).toInt() - 1),
                            normals.at(vertexComponents.at(2).split("/").at(2).toInt() - 1)));
            faces.push_back(ObjectVertex(vertices.at(vertexComponents.at(3).split("/").at(0).toInt() - 1),
                            normals.at(vertexComponents.at(3).split("/").at(2).toInt() - 1)));
        }
    }

    return faces;
}

} // namespace gl
