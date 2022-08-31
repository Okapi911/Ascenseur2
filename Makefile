all :
	make elev

main.o : main.c elevator.h person.h
	gcc -c main.c

elevator.o : elevator.c elevator.h person.h
	gcc -c elevator.c

person.o : person.c person.h
	gcc -c person.c 

elev : main.o elevator.o person.o 
	gcc -g -o elev main.o elevator.o person.o -lncurses
	gdb elev

run : elev
	./elev

clean :
	rm -f elev *.o