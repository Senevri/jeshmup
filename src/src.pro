TARGET = jeshmup
TEMPLATE = app
DESTDIR = ../.
QT -= gui core #No qt is used

LIBS += -lSDL -lUnitTest++ -lGL -lGLU

SOURCES += game.cpp \
  	   world.cpp \
	   main.cpp \
	   object.cpp \
	   GLScene.h \

HEADERS += game.h \
	world.h \
	object.h \
	GLScene.h \
