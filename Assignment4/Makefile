# I pledge my honor that I have abided by the Stevens Honor System. -Eric Altenburg

all : cs392_echoserver cs392_echoclient

cs392_echoserver : cs392_echoserver.o
	gcc -o cs392_echoserver cs392_echoserver.o

cs392_echoclient : cs392_echoclient.o
	gcc -o cs392_echoclient cs392_echoclient.o -pthread

cs392_echoserver.o : cs392_echoserver.c
	gcc -c cs392_echoserver.c

cs392_echoclient.o : cs392_echoclient.c
	gcc -c cs392_echoclient.c

clean:
		rm *.o cs392_socket.log cs392_echoserver cs392_echoclient