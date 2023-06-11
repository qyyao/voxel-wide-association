CC=g++
CFLAGS=-I./libraries/nifti_clib/include -L./libraries/nifti_clib/lib
LIBS=-lniftiio -lznz -lz -lm

all: main

main: main.cpp read_nifti.cpp
	$(CC) $(CFLAGS) -o main main.cpp read_nifti.cpp $(LIBS)

clean:
	rm -f *.o main
