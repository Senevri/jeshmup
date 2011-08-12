TARGET = jeshmup
TEMPLATE = app
DESTDIR = ../.
QT -= gui core # No qt is used

DEFINES += DEBUG

CXX_FLAGS += -g -Wall

LIBS += -lGL -lGLU -lUnitTest++

CONFIG += link_pkgconfig
PKGCONFIG += sdl

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
    DrawEngine.cpp \
    UI.cpp

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
    DrawEngine.h \
    UI.h \
    Point2d.h

#include(../libs/SOIL.pri)
include(../libs/UnitTest++.pri)
include(../libs/SDL_ttf.pri)

include($$PWD/util/utils.pri)
include($$PWD/tests/tests.pri)
unix {
	INCLUDEPATH += /usr/include/SDL
}
