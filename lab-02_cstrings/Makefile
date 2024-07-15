CFLAGS=-Iinclude -Wall -Wextra -Werror
.PHONY:all clean

all: obj lab-02_cstrings
clean:
	rm -rf obj lab-02_cstrings

obj:
	mkdir -p obj

lab-02_cstrings: obj/test.o obj/test_str.o obj/str.o 
	gcc $(CFLAGS) obj/test.o obj/test_str.o obj/str.o -o lab-02_cstrings

obj/str.o: src/str.c  include/str.h
	gcc $(CFLAGS) -c src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c include/test_str.h
	gcc $(CFLAGS) -c src/test_str.c -o obj/test_str.o

obj/test.o: src/test.c
	gcc $(CFLAGS) -c src/test.c -o obj/test.o
