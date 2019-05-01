CFLAGS=-g -Wall
CC = gcc -Wall -Wextra
CXX = g++ -Wall -Wextra

run: analyse
	./analyse 


val: analyse
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./analyse

analyse: analyse.o fonctions.o 
	gcc ${CFLAGS} analyse.o fonctions.o -o analyse

analyse.o: analyse.c analyse.h
	gcc ${CFLAGS} -c analyse.c		
	
fonctions.o: fonctions.c fonctions.h 
	gcc ${CFLAGS} -c fonctions.c


clean: 
	rm -f analyse
	rm -f similarite.distribution
	rm -f *.o
	rm -f *.data
	rm  -f Dossier/*.data

