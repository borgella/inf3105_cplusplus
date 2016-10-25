# Makefile pour INF3105 / TP3

#OPTIONS = -Wall           # option standard
#OPTIONS = -g -O0 -Wall    # pour rouler dans gdb
OPTIONS = -O2 -Wall        # pour optimiser

#
all : tp3

tp3 : tp3.cpp carte.h carte.o coordonnee.h coordonnee.o
	g++ ${OPTIONS} -o tp3 tp3.cpp coordonnee.o carte.o

carte.o : carte.cpp carte.h coordonnee.h
	g++ ${OPTIONS} -c -o carte.o carte.cpp

coordonnee.o : coordonnee.cpp coordonnee.h
	g++ ${OPTIONS} -c -o coordonnee.o coordonnee.cpp

clean:
	rm -rf tp3 *~ *.o

