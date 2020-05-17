#include "vertexarray.h"


namespace gl {

VertexArray::VertexArray(Primitive type, int size) : m_type(type), m_array(QVector<Vertex>(size)) {}

void VertexArray::append(const Vertex &vertex) {
    m_array.append(vertex);
}

Vertex &VertexArray::operator[](int index) {
    return m_array[index];
}

void VertexArray::setPrimitive(Primitive type) {
    m_type = type;
}

Primitive VertexArray::getPrimitive() const {
    return m_type;
}

int VertexArray::size() const {
    return m_array.size();
}


void VertexArray::draw(Renderer &renderer, RenderOptions options) const {
    Transform modelView = options.transform;
    Transform projection;
    Transform modelViewProjection;

    glGetFloatv(GL_PROJECTION_MATRIX, projection.data());

    modelViewProjection = projection * modelView;

    QVector<QVector3D> positions;
    QVector<QVector3D> normals;
    QVector<Color> colors;

    for (auto &vertex: m_array) {
        positions.append(vertex.position);
        normals.append(vertex.normal);
        colors.append(vertex.color);
    }

    if (options.shaderProgram) {
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("u_transformation"), modelView);
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("u_modelViewMatrix"), modelView);
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("u_modelViewProjectionMatrix"), modelViewProjection);

        options.shaderProgram->enableAttributeArray(options.shaderProgram->attributeLocation("coord3d"));
        options.shaderProgram->setAttributeArray(options.shaderProgram->attributeLocation("coord3d"), positions.data(), positions.size());
        options.shaderProgram->enableAttributeArray(options.shaderProgram->attributeLocation("normal"));
        options.shaderProgram->setAttributeArray(options.shaderProgram->attributeLocation("normal"), normals.data(), normals.size());
        options.shaderProgram->enableAttributeArray(options.shaderProgram->attributeLocation("color"));
        options.shaderProgram->setAttributeArray(options.shaderProgram->attributeLocation("color"), colors.data(), colors.size());

        glDrawArrays(m_type, 0, positions.size());

        options.shaderProgram->disableAttributeArray(options.shaderProgram->attributeLocation("coord3d"));
        options.shaderProgram->disableAttributeArray(options.shaderProgram->attributeLocation("normal"));
        options.shaderProgram->disableAttributeArray(options.shaderProgram->attributeLocation("color"));
    }
    else {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixf(modelView.data());

        glVertexPointer(3, GL_FLOAT, 0,  positions.data());
        glColorPointer(4, GL_FLOAT,  0, colors.data());

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glDrawArrays(m_type, 0, m_array.size());

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glPopMatrix();
    }
}

} // namespace gl
