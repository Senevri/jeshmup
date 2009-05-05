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
LIBS:=$(LDFLAGS) $(SDL_LDFLAGS) -lSDL 
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

SRCS:=main.cpp game.cpp
OBJS:=$(SRCS:.cpp=.o)

TARGETS:=test

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(DEFS) $(INCLUDES)


.PHONY : all

test: $(OBJS)
	-mkdir $(bindir)
	$(CC) -o $(bindir)\$@ $(OBJS) $(LIBS) $(LIBDIRS)
	-$(CP) $(SDL)\bin\SDL.dll $(bindir)

all: $(OBJS)
	-mkdir $(bindir)
	$(CC) -o $(bindir)\$(outfile) $(OBJS) $(LDFLAGS) $(INCLUDES)

clean:
	rm -f $(TARGETS) *.o $(bindir)/*
	rmdir $(bindir)
