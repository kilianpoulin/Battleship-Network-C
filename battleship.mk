all: Battleship

Battleship: server.o main.o client.o board.o ship.o ai.o
	gcc -o Battleship server.o main.o client.o board.o ship.o ai.o

server.o: server.c
	gcc -o server.o -c server.c -Wall

main.o: main.c
	gcc -o main.o -c main.c -Wall

client.o: client.c
	gcc -o client.o -c client.c -Wall

board.o: board.c
	gcc -o board.o -c board.c -Wall

ship.o: ship.c
	gcc -o ship.o -c ship.c -Wall

ai.o: ai.c
	gcc -o ai.o -c ai.c -Wall

