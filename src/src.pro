TARGET = jeshmup
TEMPLATE = app
DESTDIR = ../.
QT -= gui \
    core # No qt is used
DEFINES += DEBUG
LIBS += -lSDL \
    -lUnitTest++ \
    -lGL \
    -lGLU

# main source
SOURCES += game.cpp \
    world.cpp \
    main.cpp \
    object.cpp \
    GLScene.cpp \
    Mesh.cpp \
    InputHandler.cpp \
    Light.cpp \

HEADERS += \
    game.h \
    world.h \
    object.h \
    GLScene.h \
    Mesh.h \
    InputHandler.h \
    Definitions.h \
    Light.h \
    Point3D.h

# utils
SOURCES += util/RawLoader.cpp \
    util/3dsLoader.cpp
HEADERS += util/RawLoader.h \
    util/3dsFileFormat.h \
    util/3dsLoader.h \
    util/Logging.h
