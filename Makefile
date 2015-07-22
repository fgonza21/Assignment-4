hw4: list.o histogram.o hw4.c 
	gcc -std=c99 hw4.c -o hw4 list.o histogram.o -lplot -L/usr/include

list.o: list.c list.h 
	gcc -c -std=c99 list.c 

histogram.o: histogram.h histogram.c 
	gcc -c -std=c99 histogram.c -lplot -L/usr/include  
