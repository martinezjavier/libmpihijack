
CC=mpicc

all:
	$(CC) -shared -ldl -fPIC libmpihijack.c -o libmpihijack.so
