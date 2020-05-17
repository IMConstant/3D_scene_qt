#ifndef SCENEWIGET_H
#define SCENEWIGET_H


#include <QGLWidget>
#include <QGLFunctions>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

#include <QTimer>

#include "shaderprogram.h"

#include "color.h"

#include "renderer.h"
#include "rendergroup.h"
#include "view.h"

#include "shape.h"
#include "torusshape.h"
#include "ellipsoidshape.h"

#include "light.h"

#include "vertexarray.h"

#include "grid.h"
#include "predatorandprey.h"



struct SceneObjectData {
    QString name;
    QString type;

    bool enabled;

    QVector3D position;
    QVector3D components;

    SceneObjectData() = default;
    SceneObjectData(QString _name, QString _type, bool _enabled, QVector3D _position, QVector3D _components) :
        name(_name), type(_type), enabled(_enabled), position(_position), components(_components) {}
};

Q_DECLARE_METATYPE(SceneObjectData)



class SceneWidget : public QGLWidget, protected QGLFunctions {
    Q_OBJECT

    gl::Renderer *renderer;
    bool usingShaders;

    QVector3D objectComponents;
    gl::Shape *object;
    gl::Shape *mush;
    gl::VertexArray axis;
    gl::Camera *camera;
    gl::Camera *staticCamera;
    QVector2D cameraMoveBegin;

    Grid grid;
    PredatorAndPrey predatorAndPrey;

    gl::ShaderProgram *shaderProgram;

    bool isDark;

    QTimer *updateTimer;

public:
    SceneWidget(QWidget *parent);
    virtual ~SceneWidget();

    void clear(gl::Color color = gl::Color::Black);
    void updateAxis();

public:
    void setProjection(gl::Projection projection);
    QVector<SceneObjectData> getLight() const;
    void updateLight(SceneObjectData data);

    void useShaders(bool value);
    void setDark(int style);

signals:
    void glInitialized();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;


protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void updateScene();
};

#endif // SCENEWIGET_H
