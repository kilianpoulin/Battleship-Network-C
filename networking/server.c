#include <stdio.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include "server.h"
#include <arpa/inet.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
  
// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
	Action action;
	int result = 0;

	char MyBoard[10][10];
    char MarkBoard[10][10];

	char miss = 'm';
	char hit = 'h';
	init_game(MyBoard, MarkBoard);
  
	 write(sockfd, buff, sizeof(buff));  
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 

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
	if(buff[0] == 'w'){
		printf("\n \t Congratulations, you won !!! \n");
		break;
	}
	
	
	// ------ PLAYER'S TURN

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

	printf("\n  Number of hits left to win : %d\n", count_remaining(MarkBoard, 1));
	printf("\n  Number of hits remaining for your opponent to win : %d\n", count_remaining(MyBoard, 2));


	/// checking if we have a loser 
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
	bzero(buff, MAX);

        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
	close(sockfd);
} 


void server() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;  

    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 

	printf("Your IP is %s\n", inet_ntoa(servaddr.sin_addr));

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
    
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 

    
  
    // Function for chatting between client and server 
    func(connfd); 

    
  	
    // After chatting close the socket 
    close(sockfd); 
} 

