CC:=g++
SDL:=/usr/local/include/SDL

CFLAGS:= -g -Wall
INCLUDES:=-I$(SDL)
LIBS:=-lSDL

TARGETS:=test

all: test

test: main.o
	$(CC) -o $@ $? $(LIBS)

main.o: main.cpp
	$(CC) -c $? $(CFLAGS) $(INCLUDES)

clean:
	rm -f $(TARGETS) *.o
