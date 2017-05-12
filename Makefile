IDIR=./
# IDIR=include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -m64

# ODIR=obj
LDIR=./
# LDIR=lib

LIBS=-lSDL2

make:
	$(CC) -o build *.cpp $(CFLAGS) $(LIBS)
