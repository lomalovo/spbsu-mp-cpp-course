CFLAGS=-O2 -Wall -Werror -std=c++11 -Iinclude
.PHONY:all clean

all: obj lab-13_array
clean:
	rm -rf obj lab-13_array
obj:
	mkdir -p obj

lab-13_array: obj/main.o
	g++ $(CFLAGS) -g obj/main.o -o lab-13_array

obj/main.o: src/main.cpp include/my_array.h
	g++ $(CFLAGS) -g -c src/main.cpp -o obj/main.o

obj/smoke_compile.o: src/smoke_compile.cpp
	g++ $(CFLAGS) -g -c src/smoke_compile.cpp -o obj/smoke_compile.o


