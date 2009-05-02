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
OBJS:=$(patsubst %.cpp,$(bindir)/%.o, $(SRCS))


.PHONY : all test clean

TARGETS:=all test


$(bindir)/%.o: %.cpp
	@[ -d $(bindir) ] || mkdir -p $(bindir)
	$(CC) -o $@ -c $< $(CFLAGS) $(DEFS) $(INCLUDES)


test: $(OBJS:main.o=test.o)
	$(CC) -o $(bindir)/$@ $(OBJS:main.o=test.o) $(LIBS) $(LIBDIRS)
	-$(bindir)/$@

all: $(OBJS)
	$(CC) -o $(bindir)/$(outfile) $(OBJS) $(LIBS) $(LIBDIRS)
		

clean:
	rm -f $(TARGETS) *.o $(bindir)/*
	-rmdir $(bindir)
