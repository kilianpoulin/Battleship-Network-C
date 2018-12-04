#include <unistd.h>
#include <stdio.h>
#include <winsock2.h>

#define PORT 8080

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
    while(1)
    {
        int sizeof_csin = sizeof(csin);
        if((csock = accept(sock, (SOCKADDR *)&csin, &sizeof_csin)) != INVALID_SOCKET)            //if accepted
        {
            printf("bite");
            send(csock, "Hello world!\r\n", 14, 0);
            scanf("%d");
            closesocket(csock);
        }
    }


    WSACleanup();      //end of socket use
    return 0;
}
