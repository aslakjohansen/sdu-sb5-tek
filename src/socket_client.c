#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include "shared.h"

int main (int argc, char* argv) {
    // create
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1) die("Error creating socket");
    
    // bind
    struct sockaddr* addr = get_local_addr(CLIENT_PORT);
    if (bind(fd, addr, sizeof(*addr)) < 0) die("Error binding socket");
    
    // connect
    struct sockaddr* server_addr = get_remote_addr(SERVER_HOST, SERVER_PORT);
    if (connect(fd, server_addr, sizeof(*server_addr)) < 0) die("Error connecting");
    
    // send initial time
    time_t t0 = time(NULL);
    if (send(fd, &t0, sizeof(t0), 0) != sizeof(t0)) die("Error sending initial timestamp");
    
    // iterate across ticks
    while (1) {
        time_t t1;
        if (recv(fd, &t1, sizeof(t1), 0) == -1) die("Error recieving");
        printf("Received tick %u\n", t1-t0);
    }
    
    return 0;
}

