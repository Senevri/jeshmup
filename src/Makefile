SHELL:=/bin/sh
CC:=g++

SDL:=/usr/local/include/SDL
UNITTEST:=/usr/local/src/UnitTest++
# Various build-types here: debug, release 
BUILD:=debug

CFLAGS:= -g -Wall
INCLUDES:=-I$(SDL) -I$(UNITTEST)/src
LIBS:=-lSDL -lUnitTest++
LIBDIRS:=-L$(UNITTEST)
DEFS:=
bindir:=../bin/$(BUILD)
outfile:=jeshmup

ifeq ($(BUILD), release)
	CFLAGS:=$(CFLAGS) -O2
	DEFS:=-DRELEASE
else 
	CFLAGS:=$(CFLAGS) 
	DEFS:=-DDEBUG
endif	

SRCS:=main.cpp game.cpp object.cpp world.cpp
OBJS:=$(SRCS:.cpp=.o)

TARGETS:=all

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(DEFS) $(INCLUDES)


.PHONY : all

test: $(OBJS:main.o=test.o)
	-mkdir -p $(bindir)
	$(CC) -o $(bindir)/$@ $(OBJS:main.o=test.o) $(LIBS) $(LIBDIRS)
	-$(bindir)/$@

all: $(OBJS)
	-mkdir -p $(bindir)
	$(CC) -o $(bindir)/$(outfile) $(OBJS) $(LIBS) $(LIBDIRS)
		

clean:
	rm -f $(TARGETS) *.o $(bindir)/*
	-rmdir $(bindir)
