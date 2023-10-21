#
# Specifiy the target
all:	simplefork

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
simplefork:	simplefork.o
	gcc -Wall -o prog2tree simplefork.o

simplefork.o: simplefork.c
	gcc -Wall -c simplefork.c

#sorter:	mainS.o
#	gcc -Wall -o prog1sorter mainS.o

# Specify how the object files should be created from source files
#mainS.o: mainS.c
#	gcc -Wall -g -c mainS.c

#main.o:	main.c
#	gcc -Wall -g -c main.c

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *.gch prog2tree
