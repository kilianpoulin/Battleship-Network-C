all: Battleship

Battleship: server.o main.o client.o board.o ship.o ai.o
	gcc -o Battleship server.o main.o client.o board.o ship.o ai.o

server.o: networking/server.c
	gcc -o server.o -c networking/server.c

main.o: main/main.c
	gcc -o main.o -c main/main.c

client.o: networking/client.c
	gcc -o client.o -c networking/client.c 

board.o: board/board.c
	gcc -o board.o -c board/board.c

ship.o: ship/ship.c
	gcc -o ship.o -c ship/ship.c 

ai.o: ai/ai.c
	gcc -o ai.o -c ai/ai.c

clean:
	rm -f *.o core

mrproper:
	rm -f Battleship *.o core
