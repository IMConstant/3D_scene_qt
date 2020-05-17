#ifndef SHADER_H
#define SHADER_H

#include <QDebug>

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

#include <QGL>
#include <QGLContext>
#include <QGLFunctions>

namespace gl {

enum ShaderType {
    VertexShader   = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER
};

class Shader {
    GLuint mId;
    ShaderType mType;
    QString mSource;

    QGLFunctions glFuncs;

public:
    Shader() = delete;
    Shader(ShaderType type, QGLContext *context);

    bool compileSourceCode(const QString &source);
    bool compileSourceFile(const QString &fileName);

    GLuint id() const;
};

} // namespace gl

#endif // SHADER_H
