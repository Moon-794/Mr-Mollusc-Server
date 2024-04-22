#include "X11/Xlib.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <iostream>

#include <errno.h>

int main()
{
    struct addrinfo hints;
    struct addrinfo* serverInfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status;
    status = getaddrinfo(NULL, "3500", &hints, &serverInfo);

    if(status == 0)
    {
        std::cout << "Address Info retrieved succesfully\n";
    }
    else
    {
        std::cout << "Failed to retrieve address info...\n";
        return -1;
    }
    
    int socketfd = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
    
    if(socketfd == -1)
    {
        std::cout << "Error: Failed to get socket file descriptor.\n";
    }
    else
    {
        std::cout << "Socket created.\n";
    }
    
    status = 0;
    status = bind(socketfd, serverInfo->ai_addr, serverInfo->ai_addrlen);
    
    if(status == -1)
    {
        std::cout << "Error binding socket...\n";
    }
    else
    {
        std::cout << "Socket bound to port.\n";
    }
    
    //Set the socket to re-use the port.
    int reuse = 1; //1 = yes, 0 = no
    if(setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        std::cout << "Failed setting option: reuse socket\n";
    }
    
    if(listen(socketfd, 5) == -1)
    {
        std::cout << "Socket error encountered while attempting to listen\n";
    }
    else
    {
        std::cout << "Socket is now listening...\n";
    }

    freeaddrinfo(serverInfo);
    return 0;
}


