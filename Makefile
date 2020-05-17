CC = gcc
CFLAGS = -Wall -lm

build: movies

movies.o: movies.c utils.h
	$(CC) $(CFLAGS) -c movies.c

movies: movies.o
	$(CC) $(CFLAGS) movies.o -o movies

run: movies
	./movies

clean:
	rm -rf movies *.o
