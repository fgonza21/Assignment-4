hw4: list.o list.h histogram.o hw4.c 
	gcc -std=c99 hw4.c -o hw4 list.o histogram.o

list.o: list.c list.h 
	gcc -c list.o 

histogram.o: histogram.h histogram.c 
	gcc -c histogram.c -lplot -L/usr/includes  
