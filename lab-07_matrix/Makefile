CFLAGS=-Iinclude -Wall -Wextra -Werror
.PHONY:all clean

all: obj lab-07_matrix
clean:
	rm -rf obj lab-07_matrix
obj:
	mkdir -p obj

lab-07_matrix: obj/matrix.o obj/main.o
	g++ $(CFLAGS) -g obj/matrix.o obj/main.o -o lab-07_matrix

obj/matrix.o: src/matrix.cpp include/matrix.hpp
	g++ $(CFLAGS) -g -c src/matrix.cpp -o obj/matrix.o

obj/main.o: src/main.cpp
	g++ $(CFLAGS) -g -c src/main.cpp -o obj/main.o


