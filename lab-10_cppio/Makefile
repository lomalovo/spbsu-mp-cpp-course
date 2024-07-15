CFLAGS=-O2 -Wall -Werror -std=c++11 -Iinclude
.PHONY:all clean

all: obj lab-10_cppio
clean:
	rm -rf obj lab-10_cppio
obj:
	mkdir -p obj

lab-10_cppio: obj/employees.o obj/main.o obj/bin_manip.o
	g++ $(CFLAGS) -g obj/employees.o obj/bin_manip.o obj/main.o -o lab-10_cppio

obj/employees.o: src/employees.cpp include/employees.h
	g++ $(CFLAGS) -g -c src/employees.cpp -o obj/employees.o

obj/bin_manip.o: src/bin_manip.cpp include/bin_manip.h
	g++ $(CFLAGS) -g -c src/bin_manip.cpp -o obj/bin_manip.o

obj/main.o: src/main.cpp
	g++ $(CFLAGS) -g -c src/main.cpp -o obj/main.o
