#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void die (char* message)
{
    printf("Fatal[%u/%s]: %s\n", errno, strerror(errno), message);
    exit(1);
}

struct sockaddr* get_local_addr (int port)
{
    struct sockaddr_in* addr = (struct sockaddr_in *) malloc(sizeof(addr));
    
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    
    return (struct sockaddr*) addr;
}

struct sockaddr* get_remote_addr (char* host, int port)
{
    struct hostent* hostinfo = gethostbyname(host);
    if (!hostinfo) die("Error looking up host");
    
    struct sockaddr_in* addr = (struct sockaddr_in *) malloc(sizeof(addr));
    
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_addr = *(struct in_addr *) hostinfo->h_addr;
    
    return (struct sockaddr*) addr;
}

