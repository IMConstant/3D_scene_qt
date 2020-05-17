#include "scenewidget.h"

SceneWidget::SceneWidget(QWidget *parent) : QGLWidget(parent) {
    updateTimer = new QTimer(this);
    isDark = false;

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateScene()));

    updateTimer->start(5);
}

SceneWidget::~SceneWidget() {
    delete camera;
    delete staticCamera;
    delete renderer;
    delete shaderProgram;
    delete updateTimer;
}

void SceneWidget::initializeGL() {
    qglClearColor(Qt::black);
    initializeGLFunctions();

    shaderProgram = new gl::ShaderProgram(this->context());
    shaderProgram->addShaderFromSourceFile(gl::VertexShader, "./vertex.vsh");
    shaderProgram->addShaderFromSourceFile(gl::FragmentShader, "./fragment.fsh");
    shaderProgram->link();

    object = new gl::EllipsoidShape(1.0f, 1.0f, 1.0f, 120, 120);
    object->setFillColor(gl::Color::White);
    mush = new gl::Shape;
    mush->loadFromFile("./a2.obj");
    mush->setFillColor(gl::Color::White);

    camera = new gl::Camera(QVector3D(1.5f, 1.425f, 3.6f), QVector3D(0.0f, 0.0f, 0.0f));

    renderer = new gl::Renderer(this->context());
    renderer->setView(gl::View::Default);
    renderer->useCamera(camera);

    qDebug() << renderer;

    usingShaders = false;

    gl::Light light = gl::Light(QVector3D(0.0f, 0.0f, 1.0f));
    light.setDiffuse(0.7f);
    light.setAmbient(0.0f);
    renderer->setLight(gl::Light0, light);
    light.setPosition(QVector3D(0.0f, 2.0f, 0.0f));
    renderer->setLight(gl::Light1, light);

    renderer->enableLight(gl::Light0);
    renderer->enableLight(gl::Light1);


    grid = Grid(400);
    predatorAndPrey = PredatorAndPrey(100, 1, 100);

    axis = gl::VertexArray(gl::Lines);
    int count = 200;
    float step = 0.1f;
    gl::Color x_color(1.0f, 0.5f, 0.5f);
    gl::Color z_color(0.5f, 1.0f, 0.5f);

    for (int i = 0; i < count + 1; i++) {
        if (i == count / 2.0f) {
            continue;
        }

        gl::Color color(0.5f, 0.5f, 0.5f);

        if (i % 10 == 0) {
            if (isDark) {
                color = gl::Color(0.25f, 0.25f, 0.25f);
            }
            else {
                color = gl::Color(0.75f, 0.75f, 0.75f);
            }
        }
        else {
            color = gl::Color(0.5f, 0.5f, 0.5f);
        }

        gl::Vertex x_v1(QVector3D(-step * (count / 2.0f), 0.0f, -step * (count / 2.0f) + i * step),
                        QVector3D(0, 0, 1),
                        color);

        gl::Vertex x_v2(QVector3D(0.0f, 0.0f, -step * (count / 2.0f) + i * step),
                        QVector3D(0, 0, 1),
                        color);

        gl::Vertex x_v3(QVector3D(step * (count / 2.0f), 0.0f, -step * (count / 2.0f) + i * step),
                        QVector3D(0, 0, 1),
                        color);

        gl::Vertex z_v1(QVector3D(-step * (count / 2.0f) + i * step, 0.0f, -step * (count / 2.0f)),
                        QVector3D(0, 0, 1),
                        color);

        gl::Vertex z_v2(QVector3D(-step * (count / 2.0f) + i * step, 0.0f, 0.0f),
                        QVector3D(0, 0, 1),
                        color);

        gl::Vertex z_v3(QVector3D(-step * (count / 2.0f) + i * step, 0.0f, step * (count / 2.0f)),
                        QVector3D(0, 0, 1),
                        color);

        axis.append(x_v1);
        axis.append(x_v2);
        axis.append(x_v2);
        axis.append(x_v3);
        axis.append(z_v1);
        axis.append(z_v2);
        axis.append(z_v2);
        axis.append(z_v3);
    }

    gl::Vertex x_v1(QVector3D(-step * (count / 2.0f), 0.0f, 0.0f),
                    QVector3D(0, 0, 1),
                    x_color);

    gl::Vertex x_v2(QVector3D(0.0f, 0.0f, 0.0f),
                    QVector3D(0, 0, 1),
                    x_color);

    gl::Vertex x_v3(QVector3D(step * (count / 2.0f), 0.0f, 0.0f),
                    QVector3D(0, 0, 1),
                    x_color);

    gl::Vertex z_v1(QVector3D(0.0f, 0.0f, -step * (count / 2.0f)),
                    QVector3D(0, 0, 1),
                    z_color);

    gl::Vertex z_v2(QVector3D(0.0f, 0.0f, 0.0f),
                    QVector3D(0, 0, 1),
                    z_color);

    gl::Vertex z_v3(QVector3D(0.0f, 0.0f, step * (count / 2.0f)),
                    QVector3D(0, 0, 1),
                    z_color);

    axis.append(x_v1);
    axis.append(x_v2);
    axis.append(x_v2);
    axis.append(x_v3);
    axis.append(z_v1);
    axis.append(z_v2);
    axis.append(z_v2);
    axis.append(z_v3);

    updateAxis();

    emit glInitialized();
}

void SceneWidget::paintGL() {
    clear(isDark ? gl::Color(0.2f, 0.2f, 0.2f) : gl::Color(0.8f, 0.8f, 0.8f));

    gl::Transform sceneTransform;
    //sceneTransform.translate(-0.5f, 0.0f, -0.5f);

    gl::RenderOptions renderOptions(sceneTransform, (usingShaders ? shaderProgram : nullptr));

    if (usingShaders) {
        shaderProgram->bind();
        QVector3D lightPosition(0.0f, 1.0f, 0.0f);
        shaderProgram->setUniformValue(shaderProgram->uniformLocation("light_position"), lightPosition);
    }
    else {
        shaderProgram->release();
    }

    //mush->setScale(0.001f, 0.001f, 0.001f);

    renderer->setLighting(false);
    renderer->draw(axis, renderOptions);
    renderer->setLighting(true);
    renderer->draw(*mush, renderOptions);
}

void SceneWidget::resizeGL(int w, int h) {
    gl::View view;
    view.setViewPort(QRect(0, 0, w, h));
    renderer->setView(view);
}

void SceneWidget::clear(gl::Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneWidget::updateAxis() {
    for (int i = 0; i < axis.size(); i++) {
        float length = 4.5f;
        float distance = axis[i].position.distanceToPoint(camera->position());

        float p = std::max(0.0f, std::min(1.0f, distance / length));

        axis[i].color.a = 1.0f - p;
    }
}




void SceneWidget::setDark(int style) {
    isDark = style;
}

void SceneWidget::useShaders(bool value) {
    usingShaders = value;
}

void SceneWidget::setProjection(gl::Projection projection) {
    this->renderer->setProjection(projection);
}

QVector<SceneObjectData> SceneWidget::getLight() const {
    QVector<SceneObjectData> data;

    for (int i = 0; i < 8; i++) {
        gl::LightIndex index = static_cast<gl::LightIndex>(i);
        gl::Light light = renderer->getLight(index);

        data.append(SceneObjectData("light" + QString::number(i),
                                    "light",
                                    renderer->isEnabled(index),
                                    light.getPosition(),
                                    light.getComponents()));
    }

    return data;
}

void SceneWidget::updateLight(SceneObjectData data) {
    gl::LightIndex index = static_cast<gl::LightIndex>((data.name[data.name.size() - 1].digitValue()));

    gl::Light light;
    light.setPosition(data.position);
    light.setDiffuse(data.components.x());
    light.setSpecular(data.components.y());
    light.setAmbient(data.components.z());

    renderer->setLight(index, light);

    if (data.enabled) {
        renderer->enableLight(index);
    }
    else {
        renderer->disableLight(index);
    }
}




void SceneWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_W) {
        QVector3D cameraVector = camera->look() - camera->position();
        QVector3D look = camera->look() + 1.0f * cameraVector.normalized();
        QVector3D position = camera->position() + 1.0f * cameraVector.normalized();

        camera->setPosition(position);
        camera->setLook(look);
    }
}

void SceneWidget::mousePressEvent(QMouseEvent *e) {
    this->cameraMoveBegin = QVector2D(e->pos());
}

void SceneWidget::mouseReleaseEvent(QMouseEvent *event) {

}

void SceneWidget::mouseMoveEvent(QMouseEvent *event) {
    QVector2D cameraMoveEnd(event->pos());
    QVector2D vector = cameraMoveEnd - cameraMoveBegin;
    float vectorLength = vector.length() / 20.0f;
    vector.normalize();

    constexpr static float pi = std::acos(-1);

    QVector3D cameraVector = camera->position() - camera->look();
    float r = cameraVector.length();
    float phi = std::atan2(cameraVector.x(), cameraVector.z());
    float theta = std::acos(cameraVector.y() / r);
    float delta_phi = -0.01 * vectorLength * pi * vector.x();
    float delta_theta = -0.01 * vectorLength * pi * vector.y();
    float new_theta = theta + delta_theta;

    if (theta + delta_theta < 0.00001f) {
        new_theta = 0.00001f;
    }
    else if (theta + delta_theta >= pi) {
        new_theta = pi - 0.00001f;
    }

    camera->setPosition(camera->look() + QVector3D(r * std::sin(new_theta) * std::sin(phi + delta_phi),
                                                   r * std::cos(new_theta),
                                                   r * std::sin(new_theta) * std::cos(phi + delta_phi)));

    cameraMoveBegin = cameraMoveEnd;

    updateAxis();
}

void SceneWidget::wheelEvent(QWheelEvent *event) {
    QVector3D lookVector = camera->look() - camera->position();
    float lookVectorLength = lookVector.length();
    float step = 0.1f * std::min(static_cast<float>(std::pow(lookVectorLength, 2)) / 1.0f, 1.0f);
    lookVector.normalize();

    camera->setPosition(camera->position() + step * event->angleDelta().y() / std::fabs(event->angleDelta().y()) * lookVector);

    updateAxis();
}


// SLOTS

void SceneWidget::updateScene() {
    this->updateGL();
}
