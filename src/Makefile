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

SRCS:=main.cpp game.cpp
OBJS:=$(SRCS:.cpp=.o)

TARGETS:=test

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(DEFS) $(INCLUDES)


.PHONY : all

test: $(OBJS)
	-mkdir -p $(bindir)
	$(CC) -o $(bindir)/$@ $(OBJS) $(LIBS) $(LIBDIRS)

all: $(OBJS)
	-mkdir -p $(bindir)
	$(CC) -o $(bindir)/$(outfile) $(OBJS) $(LDFLAGS) $(INCLUDES)
		

clean:
	rm -f $(TARGETS) *.o $(bindir)/*
	rmdir $(bindir)
