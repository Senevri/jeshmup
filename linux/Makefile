OS=linux

.phony: all 

all:
	@cd ./src && make BUILD=release

debug:
	@cd ./src && make BUILD=debug
	
test:
	@cd ./src && make "DEFS=-DDEBUG -D_TEST" test

clean:
	@cd ./src && make clean

