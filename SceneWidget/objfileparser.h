#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#include <QVector>
#include <QVector3D>
#include <QGL>

#include <QFile>
#include <QStringList>
#include <QTextStream>

#include <QApplication>
#include <QDebug>

#include "vertex3d.h"

namespace gl {
struct ObjectVertex {
    QVector3D vertex;
    QVector3D normal;

    ObjectVertex() = default;
    ObjectVertex(QVector3D _vertex, QVector3D _normal) : vertex(_vertex), normal(_normal) {}
};

QVector<ObjectVertex> OBJFileParser(const QString &fileName);

} // namespace gl

#endif // OBJFILEPARSER_H
