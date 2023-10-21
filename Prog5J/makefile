all: main

main: driver.o setup.o functions.o
	g++ -g driver.o setup.o functions.o -o prog


setup.o: setup.cpp
	g++ -c -g setup.cpp

driver.o: driver.cpp
	g++ -c -g driver.cpp

functions.o: functions.cpp
	g++ -c -g functions.cpp

clean:
	rm -f *.o prog
	rm -r DRIVE
