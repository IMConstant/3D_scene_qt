#include "shaderprogram.h"

namespace gl {

ShaderProgram::ShaderProgram(QGLContext *context) :
    mContext(context),
    glFuncs(QGLFunctions(context)),
    vboIds(new GLuint[16]),
    iter(0) {
    glFuncs.initializeGLFunctions();
    mProgram = glFuncs.glCreateProgram();

    glFuncs.glGenBuffers(16, vboIds);
}

ShaderProgram::~ShaderProgram() {
    delete vboIds;
}

bool ShaderProgram::addShader(Shader *shader) {
    mShaders.push_back(shader);
    glFuncs.glAttachShader(mProgram, shader->id());

    return true;
}

bool ShaderProgram::addShaderFromSourceCode(ShaderType type, const QString &source) {

}

bool ShaderProgram::addShaderFromSourceFile(ShaderType type, const QString &fileName) {
    Shader *shader = new Shader(type, mContext);

    if (!shader->compileSourceFile(fileName)) {
        return false;
    }
    else {
        return addShader(shader);
    }
}

GLuint ShaderProgram::attributeLocation(const QString &attribute) {
    return glFuncs.glGetAttribLocation(mProgram, attribute.toLocal8Bit().data());
}

GLuint ShaderProgram::uniformLocation(const QString &uniform) {
    return glFuncs.glGetUniformLocation(mProgram, uniform.toLocal8Bit().data());
}

void ShaderProgram::enableAttributeArray(GLuint attribute) {
    glFuncs.glEnableVertexAttribArray(attribute);
}

void ShaderProgram::disableAttributeArray(GLuint attribute) {
    glFuncs.glDisableVertexAttribArray(attribute);
    iter--;
}

void ShaderProgram::setAttributeArray(GLuint attribute, const Color *values, int size) {
    glFuncs.glBindBuffer(GL_ARRAY_BUFFER, vboIds[iter++]);
    glFuncs.glBufferData(GL_ARRAY_BUFFER, 4 * size * sizeof(float), values, GL_STATIC_DRAW);
    glFuncs.glVertexAttribPointer(attribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ShaderProgram::setAttributeArray(GLuint attribute, const GLfloat *values, int tupleSize, int size) {
    glFuncs.glBindBuffer(GL_ARRAY_BUFFER, vboIds[iter++]);
    glFuncs.glBufferData(GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);
    glFuncs.glVertexAttribPointer(attribute, tupleSize, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ShaderProgram::setAttributeArray(GLuint attribute, const QVector3D *values, int size) {
    glFuncs.glBindBuffer(GL_ARRAY_BUFFER, vboIds[iter++]);
    glFuncs.glBufferData(GL_ARRAY_BUFFER, 3 * size * sizeof(GLfloat), values, GL_STATIC_DRAW);
    glFuncs.glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ShaderProgram::setUniformValue(GLuint uniform, Transform transform) {
    glFuncs.glUniformMatrix4fv(uniform, 1, false, transform.data());
}

void ShaderProgram::setUniformValue(GLuint uniform, QVector3D vector) {
    glFuncs.glUniform3f(uniform, vector.x(), vector.y(), vector.z());
}

void ShaderProgram::setUniformValue(GLuint uniform, float value) {
    glFuncs.glUniform1f(uniform, value);
}

void ShaderProgram::setUniformValue(GLuint uniform, GLuint value) {
    glFuncs.glUniform1i(uniform, value);
}

bool ShaderProgram::link() {
    glFuncs.glLinkProgram(mProgram);

    GLint rez = GL_FALSE;
    glFuncs.glGetShaderiv(mProgram, GL_LINK_STATUS, &rez);

    return rez != GL_FALSE;
}

void ShaderProgram::bind() {
    glFuncs.glUseProgram(mProgram);
}

void ShaderProgram::release() {
    glFuncs.glUseProgram(0);
}

void ShaderProgram::useDefault() {

}

} // namespace gl
