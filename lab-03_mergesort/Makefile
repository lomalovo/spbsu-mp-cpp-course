CFLAGS=-Iinclude -Wall -Wextra -Werror
.PHONY:all clean

all: obj lab-03_mergesort
clean:
	rm -rf obj lab-03_mergesort

obj:
	mkdir -p obj

lab-03_mergesort: obj/mergesort.o obj/main.o
	gcc $(CFLAGS) -g obj/mergesort.o obj/main.o -o lab-03_mergesort

obj/mergesort.o: src/mergesort.c include/mergesort.h
	gcc $(CFLAGS) -g -c src/mergesort.c -o obj/mergesort.o

obj/main.o: src/main.c
	gcc $(CFLAGS) -g -c src/main.c -o obj/main.o

