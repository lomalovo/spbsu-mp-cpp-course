CFLAGS=-O2 -Wall -Werror -std=c++11 -Iinclude -std=c++17
.PHONY:all clean

all: obj lab-14_linq
clean:
	rm -rf obj lab-14_linq
obj:
	mkdir -p obj

lab-14_linq: obj/test.o
	g++ $(CFLAGS) -g obj/test.o -o lab-14_linq

obj/smoke_test.o: src/smoke_test.cpp
	g++ $(CFLAGS) -g -c src/smoke_test.cpp -o obj/smoke_test.o

obj/test.o: src/test.cpp
	g++ $(CFLAGS) -g -c src/test.cpp -o obj/test.o



