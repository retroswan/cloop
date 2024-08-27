include .env

CC?=gcc
CFLAGS_DEBUG?=-g -pedantic -std=c99 -Wall -Wextra -Wmissing-prototypes -Wold-style-definition
CFLAGS_RELEASE?=-O2 -std=c99
CFLAGS?=${CFLAGS_DEBUG}
EXT?=so
INCS?=
LIBS?=
PLATFORM?=Debug
RPATH?=-Wl,-rpath=./

.PHONY=build
build:
	mkdir -p bin
	mkdir -p bin/${PLATFORM}
	mkdir -p working-directory
	${CC} ${CFLAGS} -c src/Cloop/Cloop.c -o src/Cloop/Cloop.o ${INCS}
	${CC} src/Cloop/Cloop.o -shared -o working-directory/libcloop.${EXT} ${LIBS}
	${CC} ${CFLAGS} -c src/main.c -o src/main.o ${INCS}
	${CC} src/main.o -o bin/${PLATFORM}/main ${LIBS} -L`pwd`/working-directory -lcloop ${RPATH}

.PHONY=debug
debug:
	make build
	
.PHONY=release
release:
	make build CFLAGS="${CFLAGS_RELEASE}" PLATFORM="Release"

.PHONY=clean
clean:
	rm -f ${OBJ}
	rm -f bin/Debug/main
	rm -f bin/Release/main

.PHONY=valgrind
valgrind:
	valgrind --leak-check=full bin/Debug/main &> valgrind.txt
