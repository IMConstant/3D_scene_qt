#include "shader.h"

namespace gl {

Shader::Shader(ShaderType type, QGLContext *context) :
    mType(type),
    glFuncs(QGLFunctions(context)) {
    glFuncs.initializeGLFunctions();
}

bool Shader::compileSourceCode(const QString &source) {
    const auto *cSource = source.toLocal8Bit().data();

    mId = glFuncs.glCreateShader(mType);
    glFuncs.glShaderSource(mId, 1, &cSource, nullptr);
    glFuncs.glCompileShader(mId);

    GLint rez = GL_FALSE;
    glFuncs.glGetShaderiv(mId, GL_COMPILE_STATUS, &rez);

    return rez != GL_FALSE;
}

bool Shader::compileSourceFile(const QString &fileName) {
    QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    QString source = in.readAll();

    return compileSourceCode(source);
}

GLuint Shader::id() const {
    return mId;
}

} // namespace gl
