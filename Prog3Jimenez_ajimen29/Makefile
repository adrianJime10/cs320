all: prog1generator

prog1generator: gdriver.o
	g++ gdriver.o -o prog3

gdriver.o: gdriver.cpp
	g++ -c gdriver.cpp

clean:
	rm -f *.o prog3
