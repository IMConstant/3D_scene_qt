#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "shader.h"
#include "color.h"
#include "transform.h"

#include "camera.h"

#include <QVector>

#include <QVector3D>
#include <QMatrix4x4>

#include <GL/glu.h>

namespace gl {

class ShaderProgram {
    QGLContext *mContext;

    GLuint mProgram;
    QVector<Shader *> mShaders;
    GLuint *vboIds;
    int iter;
    QGLFunctions glFuncs;

public:
    ShaderProgram() = delete;
    ShaderProgram(QGLContext *contex);

    ~ShaderProgram();

    bool addShader(Shader *shader);
    bool addShaderFromSourceCode(ShaderType type, const QString &source);
    bool addShaderFromSourceFile(ShaderType type, const QString &fileName);

    GLuint attributeLocation(const QString &attribute);
    GLuint uniformLocation(const QString &uniform);

    void enableAttributeArray(GLuint attribute);
    void disableAttributeArray(GLuint attribute);

    void setAttributeArray(GLuint attribute, const gl::Color *values, int size);
    void setAttributeArray(GLuint attribute, const GLfloat *values, int tupleSize, int size);
    void setAttributeArray(GLuint attribute, const QVector3D *values, int size);

    void setUniformValue(GLuint uniform, Transform transform);
    void setUniformValue(GLuint uniform, QVector3D vector);
    void setUniformValue(GLuint uniform, float value);
    void setUniformValue(GLuint uniform, GLuint value);

    bool link();
    void bind();
    void release();

    static void useDefault();
};

} // namespace gl

#endif // SHADERPROGRAM_H
