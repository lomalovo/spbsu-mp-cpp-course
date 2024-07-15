CFLAGS=-Wall -Werror -std=c++17 -Iinclude
CMPL = g++
.PHONY:all clean testHuff

all: obj test hw-02_huffman testHuff
clean:
	rm -rf obj hw-02_huffman test/doctest.h testHuff.dSYM testHuff
obj:
	mkdir -p obj

hw-02_huffman: obj/main.o obj/HuffmanArchiver.o obj/binManip.o
	$(CMPL) $(CFLAGS) -g obj/main.o obj/HuffmanArchiver.o obj/binManip.o -o hw-02_huffman

obj/main.o: src/main.cpp
	$(CMPL) $(CFLAGS) -g -c src/main.cpp -o obj/main.o

obj/HuffmanArchiver.o: src/HuffmanArchiver.cpp include/HuffmanArchiver.h include/HuffmanNode.h
	$(CMPL) $(CFLAGS) -g -c src/HuffmanArchiver.cpp -o obj/HuffmanArchiver.o

obj/binManip.o: src/binManip.cpp include/binManip.h
	$(CMPL) $(CFLAGS) -g -c src/binManip.cpp -o obj/binManip.o

test/doctest.h:
	@echo "Downloading doctest..."
	@wget -q https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h -O test/doctest.h

testHuff: obj/HuffmanArchiver.o obj/binManip.o test/test.cpp test/doctest.h
	$(CMPL) $(CFLAGS) -g obj/HuffmanArchiver.o obj/binManip.o test/test.cpp -o testHuff


