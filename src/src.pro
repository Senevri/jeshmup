TARGET = jeshmup
TEMPLATE = app
DESTDIR = ../.
QT -= gui core # No qt is used

DEFINES += DEBUG

LIBS += -lSDL -lGL -lGLU

DEPENDPATH += util
INCLUDEPATH += util

# main source
SOURCES += game.cpp \
    world.cpp \
    main.cpp \
    object.cpp \
    MeshObject.cpp \
    GLScene.cpp \
    Mesh.cpp \
    MeshMaterial.cpp \
    InputHandler.cpp \
    Light.cpp \
    DirectionalLight.cpp \
    LevelFactory.cpp \
    Level.cpp \
    DrawEngine.cpp

HEADERS += game.h \
    world.h \
    object.h \
    MeshObject.h \
    GLScene.h \
    Mesh.h \
    MeshMaterial.h \
    InputHandler.h \
    Definitions.h \
    Light.h \
    Point3d.h \
    Color.h \
    DirectionalLight.h \
    Vector.h \
    LevelFactory.h \
    Level.h \
    DrawEngine.h

#include(../libs/SOIL.pri)
include(../libs/UnitTest++.pri)

include($$PWD/util/utils.pri)
include($$PWD/tests/tests.pri)

