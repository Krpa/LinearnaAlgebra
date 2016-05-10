CC=g++
CFLAGS=-std=c++11 -o
OUT=main.o

build: main.cpp Matrix.h Vector.cpp Vector.h
	$(CC) $(CFLAGS) $(OUT) main.cpp Vector.cpp

clean:
	rm $(OUT)
