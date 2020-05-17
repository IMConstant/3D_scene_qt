#ifndef RENDERER_H
#define RENDERER_H

#include <QGL>
#include <GL/glu.h>
#include <QGLFunctions>
#include <QGLContext>

#include "transform.h"
#include "drawable.h"

#include "camera.h"
#include "color.h"

#include "shaderprogram.h"
#include "view.h"

#include "light.h"


namespace gl {
class Drawable;


enum Projection {
    Perspective,
    Orthogonal
};


class RenderOptions {
public:
    RenderOptions();
    RenderOptions(Transform _transform);
    RenderOptions(ShaderProgram *_shaderProgram);
    RenderOptions(Transform _transform, ShaderProgram *_shaderProgram);

public:
    static const RenderOptions Default;

    Transform transform;
    ShaderProgram *shaderProgram;
};


class Renderer : protected QGLFunctions {
    Camera *m_camera;

    bool lighting;
    Light  *m_light_array;
    bool   *m_light_mask;

    QGLFunctions glFuncs;

    Projection m_projection;
    View m_view;

public:
    Renderer(QGLContext *contex);
    ~Renderer();

    void useCamera(Camera *camera);

    void setLight(LightIndex index, Light &light);
    void enableLight(LightIndex index);
    void disableLight(LightIndex index);
    bool isEnabled(LightIndex index) const;

    Light getLight(LightIndex index) const;

    void setLighting(bool value);
    void enableLighting();
    void disableLighting();

    LightIndex getFreeLightIndex();

    void setProjection(Projection projection);
    void setView(const View &view);

    void draw(const Drawable &target, RenderOptions options = RenderOptions::Default);

private:
    void initLight();
};

} // namespace gl

#endif // RENDERER_H
