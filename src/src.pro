TARGET = jeshmup
TEMPLATE = app
DESTDIR = ../.
QT -= gui core #No qt is used

LIBS += -lSDL -lUnitTest++

SOURCES += game.cpp \
  	   world.cpp \
	   main.cpp \
	   object.cpp \

HEADERS += game.h \
	world.h \
	object.h \
