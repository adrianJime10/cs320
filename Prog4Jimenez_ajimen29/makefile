all: readwrite

readwrite: llc.o driver.o threads.o node.o
	g++ -g -Wall llc.o driver.o threads.o node.o -o readwrite -lpthread

llc.o: llc.cpp
	g++ -c -g llc.cpp

node.o: node.cpp
	g++ -c -g node.cpp

threads.o: threads.cpp
	g++ -c -g threads.cpp

driver.o: driver.cpp
	g++ -c -g driver.cpp

clean:
	rm -f *.o *.txt readwrite
