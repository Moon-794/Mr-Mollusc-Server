#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT "27015"

//1 > first get a single single talking to server
//2 > refactor into scalable system, with an acceptor thread and handler thread

void Cleanup();

int main(int argc, char** args)
{
    WSADATA wsa;
    SOCKET listener = INVALID_SOCKET;

    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsa);

    if (iResult != 0) 
    {
        printf("WSAStartup failed: %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised winsock...\n");

    //Create socket
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    listener = socket(result->ai_family, result->ai_socktype, result ->ai_protocol);

    if (listener == INVALID_SOCKET) 
    {
        printf("Error at socket(): %d", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(listener, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) 
    {
        printf("bind failed with error: %d", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listener);
        WSACleanup();
        return 1;
    }

    if (listen(listener, SOMAXCONN ) == SOCKET_ERROR ) 
    {
        printf( "Listen failed with error: %d", WSAGetLastError() );
        closesocket(listener);
        WSACleanup();
        return 1;
    }

    SOCKET ClientSocket = INVALID_SOCKET;

    // Accept a client socket
    ClientSocket = accept(listener, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d", WSAGetLastError());
        closesocket(listener);
        WSACleanup();
        return 1;
    }

    Cleanup();
    return 0;
}

void Cleanup()
{
    WSACleanup();
}