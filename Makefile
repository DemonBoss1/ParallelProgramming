#
# This is my first Makefile
#

main: main.o func1.o func2.o 
	gcc -pthread -o  main main.o func1.o func2.o
	
main.o: main.c main_header.h 
	gcc -O0 -g3 -Wall -c -pthread main.c

func1.o: func1.c 
	gcc -O0 -g3 -Wall -c func1.c

func2.o: func2.c 
	gcc -O0 -g3 -Wall -c func2.c

clean:
	@echo "This is clean action"
	rm -rf main *.o

all: main