TARGET = jeshmup
TEMPLATE = app
DESTDIR = ../bin
QT -= gui core # No qt is used


DEFINES += DEBUG

CXX_FLAGS += -g -Wall

win32 {
LIBS += -lmingw32 -lOPENGL32 -lGLU32 -lSDLmain -lticpp -lSDL_ttf
INCLUDEPATH += $$PWD/../libs/windows/SDL-1.2.15/include/SDL $$PWD/../src $$PWD/../libs/sources/ticpp
CONFIG -= qt

}

unix {
LIBS += -lGL -lGLU -lticpp -lSDL_ttf -lfreetype
INCLUDEPATH += $$PWD/../libs/sources/ticpp
CONFIG += link_pkgconfig
PKGCONFIG += sdl

}

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

#jinclude(../libs/SOIL.pri)
#include($$PWD/../libs/UnitTest++.pri)
#include(../libs/SDL_ttf.pri)
include($$PWD/../libs/TiCPP.pri)

include($$PWD/../libs/SDL_ttf.pri)

include($$PWD/util/utils.pri)

unix {
   include($$PWD/../libs/UnitTest++.pri)
   include($$PWD/tests/tests.pri)
   INCLUDEPATH += /usr/include/SDL
}


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/windows/SDL-1.2.14/lib -lSDL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/windows/SDL-1.2.14/lib -lSDL

INCLUDEPATH += $$PWD/../libs/windows
DEPENDPATH += $$PWD/../libs/windows

