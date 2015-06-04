
all : msgserver msgclient

msgserver : creat.o msgserver.o recv.o remove.o send.o
	gcc -o msgserver creat.o msgserver.o recv.o remove.o send.o

creat.o : creat.c
	gcc -c creat.c
msgserver.o : msgserver.c
	gcc -c msgserver.c
recv.o : recv.c
	gcc -c recv.c
remove.o : remove.c
	gcc -c remove.c
send.o : send.c
	gcc -c send.c



msgclient : creat.o msgclient.o recv.o remove.o send.o
	gcc -o msgclient creat.o msgclient.o recv.o remove.o send.o
msgclient.o : msgclient.c
	gcc -c msgclient.c

clean :
	rm -rf *.o
	rm -rf msgclient
	rm -rf msgserver
