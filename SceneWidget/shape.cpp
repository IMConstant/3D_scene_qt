#include "shape.h"


namespace gl {

Shape::Shape() : Transformable() {}

void Shape::clear() {
    m_vertices.clear();
    m_normals.clear();
    m_colors.clear();
}

void Shape::loadFromFile(const QString &fileName) {
    clear();

    auto objectData = OBJFileParser(fileName);

    for (auto &data: objectData) {
        m_vertices.push_back(data.vertex);
        m_normals.push_back(data.normal);
        m_colors.push_back(Color::Blue);
    }
}

const QVector<QVector3D> &Shape::vertices() const {
    return m_vertices;
}

const QVector<QVector3D> &Shape::normals() const {
    return m_normals;
}

const QVector<Color> &Shape::colors() const {
    return m_colors;
}

void Shape::setFillColor(Color color) {
    std::size_t size = m_colors.size();

    m_colors.clear();

    for (int i = 0; i < size; i++) {
        m_colors.append(color);
    }
}

void Shape::addTriangle(Triangle triangle) {
    m_vertices.append(triangle.v1.position);
    m_vertices.append(triangle.v2.position);
    m_vertices.append(triangle.v3.position);

    m_normals.append(triangle.v1.normal);
    m_normals.append(triangle.v2.normal);
    m_normals.append(triangle.v3.normal);

    m_colors.append(triangle.v1.color);
    m_colors.append(triangle.v2.color);
    m_colors.append(triangle.v3.color);
}

void Shape::draw(Renderer &renderer, RenderOptions options) const {
    Transform modelView = options.transform * this->getTransform();
    Transform projection;
    Transform modelViewProjection;

    glGetFloatv(GL_PROJECTION_MATRIX, projection.data());

    modelViewProjection = projection * modelView;

    if (options.shaderProgram) {
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("u_transformation"), modelView);
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("u_modelViewMatrix"), modelView);
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("u_modelViewProjectionMatrix"), modelViewProjection);

        options.shaderProgram->enableAttributeArray(options.shaderProgram->attributeLocation("coord3d"));
        options.shaderProgram->setAttributeArray(options.shaderProgram->attributeLocation("coord3d"), vertices().data(), vertices().size());
        options.shaderProgram->enableAttributeArray(options.shaderProgram->attributeLocation("normal"));
        options.shaderProgram->setAttributeArray(options.shaderProgram->attributeLocation("normal"), normals().data(), normals().size());
        options.shaderProgram->enableAttributeArray(options.shaderProgram->attributeLocation("color"));
        options.shaderProgram->setAttributeArray(options.shaderProgram->attributeLocation("color"), colors().data(), colors().size());

        glDrawArrays(GL_TRIANGLES, 0, vertices().size());

        options.shaderProgram->disableAttributeArray(options.shaderProgram->attributeLocation("coord3d"));
        options.shaderProgram->disableAttributeArray(options.shaderProgram->attributeLocation("normal"));
        options.shaderProgram->disableAttributeArray(options.shaderProgram->attributeLocation("color"));
    }
    else {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixf(modelView.data());

        glVertexPointer(3, GL_FLOAT, 0, vertices().data());
        glNormalPointer(GL_FLOAT, 0, normals().data());
        glColorPointer(4, GL_FLOAT, 0, colors().data());

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, vertices().size());

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glPopMatrix();
    }
}

} // namespace gl
