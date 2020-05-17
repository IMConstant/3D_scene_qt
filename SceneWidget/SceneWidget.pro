#-------------------------------------------------
#
# Project created by QtCreator 2020-05-07T20:30:54
#
#-------------------------------------------------

QT       += core gui opengl

LIBS += -lopengl32 -lglut32 -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SceneWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawable.cpp \
    renderer.cpp \
    transformable.cpp \
    transform.cpp \
    camera.cpp \
    shape.cpp \
    color.cpp \
    torusshape.cpp \
    vertex3d.cpp \
    objfileparser.cpp \
    scenewidget.cpp \
    shader.cpp \
    shaderprogram.cpp \
    rendergroup.cpp \
    ellipsoidshape.cpp \
    light.cpp \
    vertexarray.cpp \
    view.cpp \
    scene.cpp \
    grid.cpp \
    predatorandprey.cpp

HEADERS  += mainwindow.h \
    drawable.h \
    renderer.h \
    transformable.h \
    transform.h \
    camera.h \
    shape.h \
    color.h \
    torusshape.h \
    vertex3d.h \
    objfileparser.h \
    scenewidget.h \
    shader.h \
    shaderprogram.h \
    rendergroup.h \
    ellipsoidshape.h \
    light.h \
    vertexarray.h \
    primitives.h \
    view.h \
    scene.h \
    grid.h \
    predatorandprey.h

FORMS    += mainwindow.ui

DISTFILES += \
    fragment.fsh \
    vertex.vsh
