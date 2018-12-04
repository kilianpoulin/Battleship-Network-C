
#include <winsock2.h>

int tryconnect(){

    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);   //initialisation of socket use
    SOCKET sock;
    SOCKADDR_IN sin;
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
    printf("bite2");
    int n = recv(sock, buffer, sizeof buffer - 1, 0);
    buffer[n] = '\0';
    printf("%s", buffer);
    getchar();
    closesocket(sock);

    WSACleanup();

}
