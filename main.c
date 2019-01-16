#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "ai.h"
#include <winsock2.h>
#include <unistd.h>

#define PORT 8080

int tryconnect(){

    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);   //initialisation of socket use
    SOCKET sock;
    SOCKET csock;
    SOCKADDR_IN sin;
    SOCKADDR_IN csin;
    char buffer[255];
    struct hostent *hostinfo = NULL;
    const char *hostname = "127.0.0.1";
    hostinfo = gethostbyname(hostname);

    sin.sin_addr.s_addr	= inet_addr("127.0.0.1");
    sin.sin_family		= AF_INET;
    sin.sin_port		= htons(6667);

    sock = socket(AF_INET,SOCK_STREAM,0);
    //bind(sock, (SOCKADDR *)&sin, sizeof(sin));
    connect(sock, (SOCKADDR *)&sin, sizeof(sin));

    printf("You are connected ! ");

    char MyBoard[10][10], MarkBoard[10][10];
    int decision;

    initplate(MyBoard);
    initplate(MarkBoard);
    printf("Init board\n");
    printf("[0] Manually | [1] Randomly ==> ");
    scanf("%d", &decision);

    if(decision == 0)
        initships(MyBoard, 0);
    else
            initships(MyBoard, 1);

    printGame(MyBoard, MarkBoard);

    Action action;
    char position[3];
    printf("\n\n");
        /// Player's turn
        //action = player_turn(MyBoard, MarkBoard);
        printf("Please enter a position : ");
        scanf("%s", &position);

        int sizeof_csin = sizeof(csin);
        int z = 0;
        if((csock = accept(sock, (SOCKADDR *)&csin, &sizeof_csin)) != INVALID_SOCKET)            //if accepted
        {
            do{
                /// sending position to server
                z = send(sock, "position", 8, 0);
                if(z == -1)
                    printf("erroooor");
                printf("position sent");
            } while(z == -1);

            printf("\nn = %d", z);
            printf("\n buffer:%s\n",buffer );

            closesocket(csock);
        }

        //printGame(MyBoard, MarkBoard);
        printf("\n\n");

    //int n = recv(sock, buffer, sizeof buffer - 1, 0);
    //buffer[n] = '\0';
    //printf("%s", buffer);
    //getchar();
    scanf("%d");
    closesocket(sock);

    WSACleanup();
}


int server(){
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);   //initialisation of socket use

    SOCKET sock;
    SOCKET csock;
    SOCKADDR_IN sin;
    SOCKADDR_IN csin;
    sin.sin_addr.s_addr	= INADDR_ANY;
    sin.sin_family		= AF_INET;
    sin.sin_port		= htons(6667);
    sock = socket(AF_INET,SOCK_STREAM,0);     //socket creation
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));    //link socket and port

    listen(sock, 0);             //listen to the socket port
    char MyBoard[10][10], MarkBoard[10][10];
    char buffer[255];
    int decision;

    initplate(MyBoard);
    initplate(MarkBoard);
    printf("Init board\n");
    printf("[0] Manually | [1] Randomly ==> ");
    scanf("%d", &decision);

    if(decision == 0)
        initships(MyBoard, 0);
    else
            initships(MyBoard, 1);

        printGame(MyBoard, MarkBoard);

    Action action;
    printf("\n\n");
    /// Player's turn
    //action = player_turn(board, mark);
    int n = recv(csock, buffer, sizeof buffer - 1, 0);
    buffer[n] = '\0';
    printf("%s", buffer);
    getchar();
    //fire_missile(action, Cpboard, mark);
    //printGame(board, mark);
    printf("\n\n");

    send(csock, "Hello world!\r\n", 14, 0);
    printf("Hello world sent");

    int valread;
    printf("Reading buffer");
    printf("\n buffer:%s\n",buffer );
    int sizeof_csin = sizeof(csin);
    if((csock = accept(sock, (SOCKADDR *)&csin, &sizeof_csin)) != INVALID_SOCKET)            //if accepted
    {
        do{
            n = recv(sock, buffer, sizeof buffer - 1, 0);
        } while(n == -1);

        printf("\nn = %d", n);
        printf("\n buffer:%s\n",buffer );

        closesocket(csock);
    }

/*
    while(1)
    {
        int sizeof_csin = sizeof(csin);
        if((csock = accept(sock, (SOCKADDR *)&csin, &sizeof_csin)) != INVALID_SOCKET)            //if accepted
        {
            send(csock, "Hello world!\r\n", 14, 0);

            closesocket(csock);
        }
    }*/
    scanf("%d");

    WSACleanup();      //end of socket use
    return 0;
}

int main()
{
    int choice;
    printf("\n\n \t Battleship game \n\n");

    printf("\t 1. Host a game\n");
    printf("\t 2. Join a game\n");
    printf("\t 3. Challenge the computer\n");

    do {
        printf("\t\n Your choice : ");
        scanf("%d", &choice);
    } while(choice != 1 && choice != 2 && choice != 3);

    if(choice == 1){
        server();
    }
    else if(choice == 2)
        tryconnect();
    else if(choice == 3){
        srand(time(NULL));
        char MyBoard[10][10], CpBoard[10][10];
        char MarkBoard[10][10], CpMarkBoard[10][10];
        int choice;

        /// HUMAN PLAYER
        initplate(MyBoard);
        initplate(MarkBoard);
        printGame(MyBoard, MarkBoard);

        printf("Init board\n");
        printf("[0] Manually | [1] Randomly ==> ");
        scanf("%d", &choice);
        if(choice == 0)
            initships(MyBoard, 0);
        else
            initships(MyBoard, 1);

        printGame(MyBoard, MarkBoard);

        /// COMPUTER
        initplate(CpBoard);
        initplate(CpMarkBoard);
        //printGame(CpBoard, CpMarkBoard);
        initships(CpBoard, 1); /// generated randomly

        //play_game(MyBoard, CpBoard, MarkBoard, CpMarkBoard);
    }

    return 0;
}
