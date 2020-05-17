#include "renderer.h"

namespace gl {

RenderOptions::RenderOptions() : shaderProgram(nullptr) {}

RenderOptions::RenderOptions(Transform _transform) : transform(_transform), shaderProgram(nullptr) {}

RenderOptions::RenderOptions(ShaderProgram *_shaderProgram) : shaderProgram(_shaderProgram) {}

RenderOptions::RenderOptions(Transform _transform, ShaderProgram *_shaderProgram) :
    transform(_transform), shaderProgram(_shaderProgram) {}

const RenderOptions RenderOptions::Default = RenderOptions();



Renderer::Renderer(QGLContext *contex) :
    m_projection(Perspective),
    lighting(false) {
    glFuncs = QGLFunctions(contex);

    m_light_array = new Light[8];
    m_light_mask  = new bool[8];

    memset(m_light_mask, 0, 8);
}

Renderer::~Renderer() {
    delete [] m_light_array;
    delete [] m_light_mask;
}

void Renderer::useCamera(Camera *camera) {
    m_camera = camera;
}

void Renderer::setLight(LightIndex index, Light &light) {
    m_light_array[index] = light;
}

void Renderer::enableLight(LightIndex index) {
    m_light_mask[index] = true;
}

void Renderer::disableLight(LightIndex index) {
    m_light_mask[index] = false;
}

Light Renderer::getLight(LightIndex index) const {
    return m_light_array[index];
}

bool Renderer::isEnabled(LightIndex index) const {
    return m_light_mask[index];
}

void Renderer::setProjection(Projection projection) {
    m_projection = projection;
}

void Renderer::setView(const View &view) {
    m_view = view;
}

void Renderer::draw(const Drawable &target, RenderOptions options) {
    if (options.shaderProgram) {
        options.shaderProgram->setUniformValue(options.shaderProgram->uniformLocation("camera_position"), m_camera->position());
    }

    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    QRect viewPort = m_view.getViewPort();
    glViewport(viewPort.x(), viewPort.y(), viewPort.width(), viewPort.height());
    switch (m_projection) {
        case Perspective:
            gluPerspective(m_view.getAngle(), viewPort.width() / static_cast<float>(viewPort.height()),
                           0.1f, 10000.0f);
            break;
        case Orthogonal:
            glOrtho(m_view.getXScale().x(), m_view.getXScale().y(),
                    m_view.getYScale().x(), m_view.getYScale().y(),
                    0.1f, 10000.0f);
            break;
    }

    gluLookAt(m_camera->position().x(), m_camera->position().y(), m_camera->position().z(),
              m_camera->look().x(), m_camera->look().y(), m_camera->look().z(),
              0, 1, 0);

    if (lighting) {
        initLight();
        enableLighting();

        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_SPECULAR | GL_AMBIENT | GL_DIFFUSE);
        glShadeModel(GL_SMOOTH);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    target.draw(*this, options);

    disableLighting();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Renderer::initLight() {
    for (int i = 0; i < 8; i++) {
        GLenum lightIndex = GL_LIGHT0 + static_cast<GLenum>(i);
        Light &light = m_light_array[i];

        glLightfv(lightIndex, GL_POSITION, reinterpret_cast<GLfloat *>(&light.m_position));

        glLightfv(lightIndex, GL_DIFFUSE,  reinterpret_cast<GLfloat *>(&light.m_diffuse));
        glLightfv(lightIndex, GL_SPECULAR, reinterpret_cast<GLfloat *>(&light.m_specular));
        glLightfv(lightIndex, GL_AMBIENT,  reinterpret_cast<GLfloat *>(&light.m_ambient));

        glLightfv(lightIndex, GL_SPOT_DIRECTION, reinterpret_cast<GLfloat *>(&light.m_spot_direction));
        glLightf (lightIndex, GL_SPOT_EXPONENT,  light.m_spot_exponent);
        //glLightf (lightIndex, GL_SPOT_CUTOFF,    light.m_spot_cutoff);
    }
}

void Renderer::setLighting(bool value) {
    lighting = value;
}

LightIndex Renderer::getFreeLightIndex() {
    for (int i = 0; i < 8; i++) {
        if (!m_light_mask[i]) {
            return static_cast<LightIndex>(i);
        }
    }
}

void Renderer::enableLighting() {
    glEnable(GL_LIGHTING);

    for (int i = 0; i < 8; i++) {
        if (m_light_mask[i]) {
            glEnable(GL_LIGHT0 + static_cast<GLenum>(i));
        }
    }
}

void Renderer::disableLighting() {
    glDisable(GL_LIGHTING);

    for (int i = 0; i < 8; i++) {
        if (m_light_mask[i]) {
            glDisable(GL_LIGHT0 + static_cast<GLenum>(i));
        }
    }
}

} // namespace gl
