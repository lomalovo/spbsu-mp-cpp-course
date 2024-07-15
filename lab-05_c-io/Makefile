CFLAGS=-Iinclude -Wall -Wextra -Werror
.PHONY:all clean

all: obj lab-05_c-io
clean:
	rm -rf obj lab-05_c-io

obj:
	mkdir -p obj

lab-05_c-io: obj/clist.o obj/point_list.o obj/main.o
	gcc $(CFLAGS) -g obj/clist.o obj/point_list.o obj/main.o -o lab-05_c-io

obj/clist.o: src/clist.c include/clist.h
	gcc $(CFLAGS) -g -c src/clist.c -o obj/clist.o

obj/point_list.o: src/point_list.c include/point_list.h
	gcc $(CFLAGS) -g -c src/point_list.c -o obj/point_list.o

obj/main.o: src/main.c
	gcc $(CFLAGS) -g -c src/main.c -o obj/main.o


