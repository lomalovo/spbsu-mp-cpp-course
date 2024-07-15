CFLAGS=-Iinclude -Wall -Wextra -Werror
.PHONY:all clean

all: obj lab-06_int-vector
clean:
	rm -rf obj lab-06_int-vector

obj:
	mkdir -p obj

lab-06_int-vector: obj/my_vector.o obj/main.o
	g++ $(CFLAGS) -g obj/my_vector.o obj/main.o -o lab-06_int-vector

obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp
	g++ $(CFLAGS) -g -c src/my_vector.cpp -o obj/my_vector.o

obj/main.o: src/main.cpp
	g++ $(CFLAGS) -g -c src/main.cpp -o obj/main.o


