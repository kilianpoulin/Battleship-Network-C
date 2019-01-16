
// Write CPP code here 
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client.h"
#define MAX 80
#define PORT 8080 
#define SA struct sockaddr 
void funct(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
	int result;
Action action;

char MyBoard[10][10];
    char MarkBoard[10][10];
char miss = 'm';
	char hit = 'h';
	init_game(MyBoard, MarkBoard);
	
	printf("\t Waiting for your opponent...\n\n");
	 read(sockfd, buff, sizeof(buff)); 
	
    for (;;) { 
        bzero(buff, sizeof(buff)); 

	// PLAYER'S TURN

	printGame(MyBoard, MarkBoard);
        action = player_turn(MarkBoard, buff);
        write(sockfd, buff, sizeof(buff)); 
	
	
	// receives result of missile
	
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 

	if(buff[0] == 'h')
		result = 1;
	else
		result = 0;

	// updates mark board
	fire_missile(result, action, MarkBoard);
	
	printGame(MyBoard, MarkBoard);

	/// checkinf if we have a loser 
	bzero(buff, MAX);
	if(game_on(MyBoard) == 0){
		printf("\n \t Sorry, you are the unlucky loser\n");
		buff[0] = 'w';
	}
	else
		buff[0] = 'n';

	write(sockfd, buff, sizeof(buff));
	if(buff['0'] == 'w')
		break;
	
	// ----- OPPONENT'S TURN
	

        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
	
	printf("\t Enemy Move : %s\n", buff);

	action = convert_to_action(buff);

	// updates player's board
	result = receive_missile(action, MyBoard);

	bzero(buff, MAX);
	n = 0; 


	if(result == 1)
		buff[0] = hit; 
	else 
		buff[0] = miss;
		
	write(sockfd, buff, sizeof(buff)); 

	// check if we have a winner
	bzero(buff, MAX);
	read(sockfd, buff, sizeof(buff)); 
	if(buff[0] = 'w'){
		printf("\n \t Congratulations, you won !!! \n");
		break;
	}
        
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
void client() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
	char address[16];
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    printf("\t Please enter address of server (ex : 127.0.0.1) :");
	scanf("%s", address);
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(address); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    funct(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 

