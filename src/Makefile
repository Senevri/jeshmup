SHELL:=/bin/sh
CC:=g++

SDL:=/usr/local/include/SDL
UNITTEST:=/usr/local/src/UnitTest++
# Various build-types here: debug, release 
BUILD:=debug

CFLAGS:= -g -Wall
INCLUDES:=-I$(SDL) -I$(UNITTEST)/src
LIBS:=-lSDL -L$(UNITTEST)/libUnitTest++.a
DEFS:=
bindir:=../bin/$(BUILD)

ifeq ($(BUILD), release)
	CFLAGS:=$(CFLAGS) -O2
	DEFS:=-DRELEASE
else 
	CFLAGS:=$(CFLAGS) 
	DEFS:=-DDEBUG
endif	

TARGETS:=test

all: test

test: main.o
	-mkdir -p $(bindir)
	$(CC) -o $(bindir)/$@ $? $(LIBS)

main.o: main.cpp
	$(CC) -c $? $(CFLAGS) $(DEFS) $(INCLUDES)

clean:
	rm -f $(TARGETS) *.o $(bindir)/*
	rmdir $(bindir)
