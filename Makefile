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
	${CC} ${CFLAGS} -c src/Cloop/Cloop.c -o src/Cloop/Cloop.o ${INCS}
	${CC} src/Cloop/Cloop.o -shared -o bin/${PLATFORM}/libcloop.${EXT} ${LIBS}
	${CC} ${CFLAGS} -c src/main.c -o src/main.o ${INCS} -I`pwd`/include
	${CC} src/main.o -o bin/${PLATFORM}/main ${LIBS} -L`pwd`/bin/${PLATFORM} -lcloop ${RPATH}

.PHONY=debug
debug:
	make build
	
.PHONY=release
release:
	make build CFLAGS="${CFLAGS_RELEASE}" PLATFORM="Release"

.PHONY=clean
clean:
	rm -f src/Cloop/Cloop.o
	rm -f src/main.o
	rm -rf bin

.PHONY=valgrind
valgrind:
	valgrind --leak-check=full bin/Debug/main &> valgrind.txt
