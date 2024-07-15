CFLAGS=-Iinclude -Wall -Wextra -Werror
.PHONY:all clean

all: obj lab-04_intrusive-list
clean:
	rm -rf obj lab-04_intrusive-list

obj:
	mkdir -p obj

lab-04_intrusive-list: obj/clist.o obj/main.o
	gcc $(CFLAGS) -g obj/clist.o obj/main.o -o lab-04_intrusive-list

obj/clist.o: src/clist.c include/clist.h
	gcc $(CFLAGS) -g -c src/clist.c -o obj/clist.o

obj/main.o: src/main.c
	gcc $(CFLAGS) -g -c src/main.c -o obj/main.o


