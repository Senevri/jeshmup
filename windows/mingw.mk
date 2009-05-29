SHELL:=/bin/sh
CC:=g++
CP:=copy

SDL:=d:\dev\SDL\SDL-1.2.13
# UNITTEST:=D:\dev\ext\UnitTest++
# Various build-types here: debug, release 
BUILD:=debug

SDL_CFLAGS := -I$(SDL)\include\SDL -I$(SDL)\include
SDL_LDFLAGS := -L$(SDL)\lib -lSDLMain

CFLAGS:=-g -Wall -O3 
LDFLAGS:=-L$(MINGW32_PATH)\lib -lmingw32 -mwindows 

CFLAGS:= -g -Wall
INCLUDES:=$(SDL_CFLAGS) 
LIBS:=$(LDFLAGS) $(SDL_LDFLAGS) -lSDL -lopengl32 -lglu32 -lSDL
DEFS:=
bindir:=..\bin\$(BUILD)
outfile:=jeshmup

ifeq ($(BUILD), release)
	CFLAGS:=$(CFLAGS) -O2
	DEFS:=-DRELEASE -DNOTEST
else 
	CFLAGS:=$(CFLAGS) 
	DEFS:=-DDEBUG -DNOTEST
endif	

SRCS:=main.cpp game.cpp object.cpp world.cpp GLScene.cpp Mesh.cpp InputHandler.cpp util\RawLoader.cpp
OBJS:=$(patsubst %.cpp,$(bindir)\\%.o, $(SRCS))

TARGETS:=test

$(bindir)\\%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(DEFS) $(INCLUDES)


.PHONY : all

dirs:
	-mkdir $(bindir)
	-mkdir $(bindir)\\util

test: $(patsubst main.o,test.o, $(OBJS))
	$(CC) -o $(bindir)\$@ $(OBJS) $(LIBS) $(LIBDIRS)
	-$(CP) $(SDL)\bin\SDL.dll $(bindir)

all: $(OBJS)
	$(CC) -o $(bindir)\$(outfile) $(OBJS) $(LIBS) $(INCLUDES)
	-$(CP) $(SDL)\bin\SDL.dll $(bindir)


clean:
	rm -f $(TARGETS) *.o $(bindir)/*
	rmdir $(bindir)
