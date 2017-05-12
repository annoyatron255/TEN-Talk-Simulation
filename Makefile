IDIR=./
# IDIR=include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -m64

# ODIR=obj
LDIR=./
# LDIR=lib

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIBS=-lSDL2
endif
ifeq ($(UNAME), Darwin)
LIBS=-F/Users/`whoami`/Library/Frameworks/ -framework SDL2
endif

make:
	$(CC) -o build *.cpp $(CFLAGS) $(LIBS)
