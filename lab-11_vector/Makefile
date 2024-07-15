CFLAGS=-O2 -Wall -Werror -std=c++11 -Iinclude
.PHONY:all clean

all: obj lab-11_vector
clean:
	rm -rf obj lab-11_vector
obj:
	mkdir -p obj

lab-11_vector: src/main.cpp include/my_vector_impl.hpp include/my_vector.hpp
	g++ $(CFLAGS) src/main.cpp -o lab-11_vector
