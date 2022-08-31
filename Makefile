main.o : main.c elevator.c person.c
	gcc -c main.c elevator.c person.c

elev : main.o elevator.o person.o 
	gcc -g -o elev main.o elevator.o person.o -lncurses
	gdb elev

run : elev
	./elev

clean :
	rm -f elev *.o